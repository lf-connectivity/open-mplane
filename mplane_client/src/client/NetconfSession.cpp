// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "NetconfSession.h"

#include <shared_mutex>
#include <sstream>
#include <thread>

#include <glog/logging.h>

namespace {
const std::string kCloseSessionRpc =
    "<close-session xmlns=\"urn:ietf:params:xml:ns:netconf:base:1.0\"/>";

// Empty callback to rubber-stamp host SSH identity
int fakeHostkeyCallback(const char *hostname, ssh_session session, void *priv) {
  return 0;
}

// Callback to grab the password from an Authentication protobuf
char *passwordCallback(const char *username, const char *hostname, void *priv) {
  return reinterpret_cast<char *>(priv);
}

std::string serializeYang(const struct lyd_node *tree) {
  char *rawString = nullptr;
  lyd_print_mem(&rawString, tree, LYD_XML,
                LYP_WITHSIBLINGS | LYP_NETCONF | LYP_FORMAT);
  std::string output(rawString);
  free(rawString);
  return output;
}

// Global notification handler which receives notifications belonging to all
// NETCONF sessions and uses a callback table to pass them to the correct
// NetconfSession; this is necessary because nc_recv_notif_dispatch only accepts
// C functions, and capturing lambdas/std::function cannot satisfy this
// requirement.
std::shared_mutex globalNotificationMutex;
std::map<const struct nc_session *,
         std::vector<std::function<void(const struct nc_notif *)>>>
    globalNotificationCallbacks;

void addGlobalNotificationCallback(
    const struct nc_session *session,
    const std::function<void(const struct nc_notif *)> &callback) {
  std::unique_lock writeLock(globalNotificationMutex);
  auto sessionIt =
      globalNotificationCallbacks
          .emplace(session,
                   std::vector<std::function<void(const struct nc_notif *)>>())
          .first;
  sessionIt->second.push_back(callback);
  LOG(INFO) << "Added notification callback to session " << (void *)session
            << " on " << nc_session_get_host(session) << ":"
            << nc_session_get_port(session);
}

void removeGlobalNotificationCallbacks(const struct nc_session *session) {
  std::unique_lock writeLock(globalNotificationMutex);
  globalNotificationCallbacks.erase(session);
}

void globalNotificationHandler(struct nc_session *session,
                               const struct nc_notif *notif) {
  std::shared_lock readLock(globalNotificationMutex);
  auto sessionIt = globalNotificationCallbacks.find(session);
  if (sessionIt != globalNotificationCallbacks.end()) {
    for (auto &callback : sessionIt->second) {
      callback(notif);
    }
  }
}
} // namespace

NetconfSession::NetconfSession() {}

NetconfSession::~NetconfSession() {
  if (session_) {
    LOG(INFO) << "Closing session on " << getHost() << ":" << getPort();
    removeGlobalNotificationCallbacks(session_);
    {
      std::unique_lock lock(notificationStateMutex_);
      for (auto &&promise : sessionDonePromises_) {
        promise.set_value();
      }
    }

    // Send a <close-session> RPC before freeing the session; not using
    // netconfRpc because this does not receive a reply
    uint64_t messageId;
    struct nc_rpc *closeSessionRpc =
        nc_rpc_act_generic_xml(kCloseSessionRpc.c_str(), NC_PARAMTYPE_CONST);
    const NC_MSG_TYPE sendCode = nc_send_rpc(
        session_, closeSessionRpc,
        1000 /* short, arbitrary timeout of 1 second */, &messageId);
    if (sendCode == NC_MSG_ERROR || sendCode == NC_MSG_WOULDBLOCK) {
      LOG(WARNING) << "<close-session/> RPC failed";
    }

    nc_session_free(session_, nullptr);
    session_ = nullptr;
  }
}

bool NetconfSession::connect(const mpclient::ConnectRequest *request) {
  // Launch the process in a new thread (std::launch::async forces a new thread
  // to be made) so that each NETCONF call has its own thread environment,
  // preventing cross-contamination. This means that keys, etc. do not need to
  // be cleared between connections.
  std::future<bool> result = std::async(std::launch::async, [this, request]() {
    if (initConnect(&request->auth())) {
      session_ = nc_connect_ssh(request->host().c_str(), request->port(), NULL);
      return session_ != nullptr;
    }
    return false;
  });
  bool success = result.get();
  if (success) {
    LOG(INFO) << "Opened session " << (void *)session_ << " on " << getHost()
              << ":" << getPort();
  } else {
    LOG(ERROR) << "Could not open session on " << request->host() << ":"
               << request->port();
  }
  return success;
}

bool NetconfSession::listen(const mpclient::ListenRequest *request) {
  // See connect().
  std::future<bool> result = std::async(std::launch::async, [this, request]() {
    if (initListen(&request->auth()) &&
        nc_client_ssh_ch_add_bind_listen(request->host().c_str(),
                                         request->port()) == 0) {
      LOG(INFO) << "Listening for call home on " << request->host() << ":"
                << request->port();
      // Scale timeout from seconds to milliseconds
      nc_accept_callhome(request->timeoutsec() * 1000, nullptr, &session_);
      nc_client_ssh_ch_del_bind(request->host().c_str(), request->port());
    } else {
      LOG(ERROR) << "Could not listen on " << request->host() << ":"
                 << request->port();
    }
    return session_ != nullptr;
  });
  bool success = result.get();
  if (success) {
    LOG(INFO) << "Opened session " << (void *)session_ << " on " << getHost()
              << ":" << getPort();
  }
  return success;
}

void NetconfSession::netconfRpc(const mpclient::NetconfRpcRequest *request,
                                mpclient::NetconfRpcResponse *response) {
  checkSession(); // Throws an error if session_ is NULL

  // Send the RPC
  uint64_t messageId;
  struct nc_rpc *rpc = nc_rpc_act_generic_xml(request->serializedyang().c_str(),
                                              NC_PARAMTYPE_CONST);
  const NC_MSG_TYPE sendCode = nc_send_rpc(
      session_, rpc, request->timeoutsec() * 1000 /* Scale to milliseconds */,
      &messageId);
  if (sendCode == NC_MSG_ERROR) {
    response->set_status(mpclient::NetconfRpcResponse::ERROR);
    return;
  } else if (sendCode == NC_MSG_WOULDBLOCK) {
    response->set_status(mpclient::NetconfRpcResponse::TIMEOUT);
    return;
  }

  // Wait for the response; this code is only valid for libnetconf v1.x
  struct nc_reply *reply;
  NC_MSG_TYPE receiveCode = NC_MSG_ERROR;
  do {
    receiveCode =
        nc_recv_reply(session_, rpc, messageId,
                      request->timeoutsec() * 1000 /* Scale to milliseconds */,
                      LYD_OPT_DESTRUCT | LYD_OPT_NOSIBLINGS, &reply);
    if (receiveCode == NC_MSG_ERROR) {
      response->set_status(mpclient::NetconfRpcResponse::ERROR);
      return;
    } else if (receiveCode == NC_MSG_WOULDBLOCK) {
      response->set_status(mpclient::NetconfRpcResponse::TIMEOUT);
      return;
    } else if (receiveCode == NC_MSG_NOTIF) {
      continue;
    } else if (receiveCode == NC_MSG_REPLY_ERR_MSGID) {
      nc_reply_free(reply);
      continue;
    }

    // Parse response
    response->set_status(mpclient::NetconfRpcResponse::SUCCESS);
    if (reply->type == NC_RPL_OK) {
      response->set_returntype(mpclient::NetconfRpcResponse::OK);
    } else {
      if (reply->type == NC_RPL_DATA) {
        response->set_returntype(mpclient::NetconfRpcResponse::DATA);
        struct nc_reply_data *dataReply =
            reinterpret_cast<struct nc_reply_data *>(reply);
        response->set_message(serializeYang(dataReply->data));
      } else if (reply->type == NC_RPL_ERROR) {
        response->set_returntype(mpclient::NetconfRpcResponse::RPC_ERROR);
        struct nc_reply_error *errorReply =
            reinterpret_cast<struct nc_reply_error *>(reply);
        std::stringstream ss;
        for (int i = 0; i < errorReply->count; ++i) {
          ss << "<rpc-error>" << std::endl;
          if (errorReply->err[i].type) {
            ss << "  <error-type>" << errorReply->err[i].type << "</error-type>"
               << std::endl;
          }
          if (errorReply->err[i].tag) {
            ss << "  <error-tag>" << errorReply->err[i].tag << "</error-tag>"
               << std::endl;
          }
          if (errorReply->err[i].severity) {
            ss << "  <error-severity>" << errorReply->err[i].severity
               << "</error-severity>" << std::endl;
          }
          if (errorReply->err[i].apptag) {
            ss << "  <error-app-tag>" << errorReply->err[i].apptag
               << "</error-app-tag>" << std::endl;
          }
          if (errorReply->err[i].path) {
            ss << "  <error-path>" << errorReply->err[i].path << "</error-path>"
               << std::endl;
          }
          if (errorReply->err[i].message) {
            ss << "  <error-message";
            if (errorReply->err[i].message_lang) {
              ss << " xml:lang=\"" << errorReply->err[i].message_lang << "\"";
            }
            ss << ">" << errorReply->err[i].message << "</error-message>"
               << std::endl;
          }
          ss << "  <error-info>" << std::endl;
          if (errorReply->err[i].sid) {
            ss << "    <session-id>" << errorReply->err[i].sid
               << "</session-id>" << std::endl;
          }
          for (int j = 0; j < errorReply->err[i].attr_count; ++j) {
            ss << "    <bad-attr>" << errorReply->err[i].attr[j]
               << "</bad-attr>" << std::endl;
          }
          for (int j = 0; j < errorReply->err[i].elem_count; ++j) {
            ss << "    <bad-element>" << errorReply->err[i].elem[j]
               << "</bad-element>" << std::endl;
          }
          for (int j = 0; j < errorReply->err[i].ns_count; ++j) {
            ss << "    <bad-namespace>" << errorReply->err[i].ns[j]
               << "</bad-namespace>" << std::endl;
          }
          for (int j = 0; j < errorReply->err[i].other_count; ++j) {
            char *xmlStr;
            lyxml_print_mem(&xmlStr, errorReply->err[i].other[j], 0);
            ss << "    " << xmlStr;
            free(xmlStr);
          }
          ss << "  </error-info>" << std::endl;
          ss << "</rpc-error>" << std::endl;
        }
        response->set_message(ss.str());
      }
    }
    nc_reply_free(reply);
  } while (receiveCode == NC_MSG_NOTIF ||
           receiveCode == NC_MSG_REPLY_ERR_MSGID);
}

std::future<void> NetconfSession::addNotificationCallback(
    const std::function<void(const struct nc_notif *)> &callback) {
  std::unique_lock lock(notificationStateMutex_);

  // Add the callback to the global list
  checkSession(); // Throws an error if session_ is NULL
  addGlobalNotificationCallback(session_, callback);
  // Check whether NETCONF is already running a notification callback thread; if
  // not, run the global handler in that thread. It is important to have exactly
  // one of this thread, otherwise undefined behavior/multiple callback
  // invokation on a single notification is possible.
  if (!nc_session_ntf_thread_running(session_)) {
    nc_recv_notif_dispatch(session_, globalNotificationHandler);
  }

  // Create a future to let the calling thread know when this session is done
  std::promise<void> promise;
  std::future<void> future = promise.get_future();
  sessionDonePromises_.push_back(std::move(promise));
  return future;
}

std::future<void> NetconfSession::addNotificationCallback(
    const std::function<void(const std::string &)> &callback) {
  return addNotificationCallback(
      [callback](const struct nc_notif *notification) {
        callback(serializeYang(notification->tree));
      });
}

std::string NetconfSession::getHost() const {
  checkSession(); // Throws an error if session_ is NULL
  return std::string(nc_session_get_host(session_));
}

uint32_t NetconfSession::getPort() const {
  checkSession(); // Throws an error if session_ is NULL
  return nc_session_get_port(session_);
}

bool NetconfSession::initConnect(const mpclient::Authentication *auth) {
  nc_client_ssh_set_auth_hostkey_check_clb(fakeHostkeyCallback, nullptr);

  if (auth->keys().empty() && !auth->has_password()) {
    // There is no authentication provided
    LOG(ERROR) << "No authentication";
    return false;
  }

  for (const auto &keypair : auth->keys()) {
    if (nc_client_ssh_add_keypair(keypair.publicpath().c_str(),
                                  keypair.privatepath().c_str()) < 0) {
      LOG(ERROR) << "Could not add key pair";
      return false;
    }
  }

  if (auth->has_password()) {
    // The memory allocated by strdup is freed by NETCONF
    nc_client_ssh_set_auth_password_clb(
        passwordCallback,
        reinterpret_cast<void *>(strdup(auth->password().c_str())));
    const_cast<mpclient::Authentication *>(auth)->clear_password();
  } else {
    // Disable password authentication
    nc_client_ssh_set_auth_pref(NC_SSH_AUTH_PASSWORD, -1);
  }

  if (nc_client_ssh_set_username(auth->user().c_str()) < 0) {
    LOG(ERROR) << "Could not set username";
    return false;
  }

  // Disable interactive authentication
  nc_client_ssh_set_auth_pref(NC_SSH_AUTH_INTERACTIVE, -1);
  return true;
}

bool NetconfSession::initListen(const mpclient::Authentication *auth) {
  nc_client_ssh_ch_set_auth_hostkey_check_clb(fakeHostkeyCallback, nullptr);

  if (auth->keys().empty() && !auth->has_password()) {
    // There is no authentication provided
    LOG(ERROR) << "No authentication";
    return false;
  }

  for (const auto &keypair : auth->keys()) {
    // The memory allocated by strdup is freed by NETCONF
    if (nc_client_ssh_ch_add_keypair(keypair.publicpath().c_str(),
                                     keypair.privatepath().c_str()) < 0) {
      LOG(ERROR) << "Could not add key pair";
      return false;
    }
  }

  if (auth->has_password()) {
    nc_client_ssh_ch_set_auth_password_clb(
        passwordCallback,
        reinterpret_cast<void *>(strdup(auth->password().c_str())));
    const_cast<mpclient::Authentication *>(auth)->clear_password();
  } else {
    // Disable password authentication
    nc_client_ssh_ch_set_auth_pref(NC_SSH_AUTH_PASSWORD, -1);
  }

  if (nc_client_ssh_ch_set_username(auth->user().c_str()) < 0) {
    LOG(ERROR) << "Could not set username";
    return false;
  }

  // Disable interactive authentication
  nc_client_ssh_ch_set_auth_pref(NC_SSH_AUTH_INTERACTIVE, -1);
  return true;
}

void NetconfSession::checkSession() const {
  if (!session_) {
    throw std::runtime_error("Session is not valid");
  }
}
