// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "MpclientImpl.h"

#include <future>

#include <glog/logging.h>

namespace {
// An arbitrary (but short) time to wait for a general NETCONF RPC to complete
const uint32_t kRpcTimeoutSec = 3;

// NETCONF RPC to reset the watchdog
const std::string kRpcResetWatchdog = "<supervision-watchdog-reset "
                                      "xmlns=\"urn:o-ran:supervision:1.0\"/>";

// NETCONF RPC to subscribe to notifications matching "supervision-notification"
const std::string kRpcSubscribeSupervisionNotifications =
    "<create-subscription "
    "xmlns=\"urn:ietf:params:xml:ns:netconf:notification:1.0\"><stream>o-ran-"
    "supervision</stream></create-subscription>";
} // namespace

MpclientImpl::MpclientImpl() {}

grpc::Status MpclientImpl::connect(grpc::ServerContext *context,
                                   const mpclient::ConnectRequest *request,
                                   mpclient::ConnectResponse *response) {
  auto session = std::make_shared<NetconfSession>();
  if (session->connect(request)) {
    uint32_t sessionId = addSession(session);
    response->set_success(true);
    response->set_sessionid(sessionId);
  } else {
    response->set_success(false);
    response->clear_sessionid();
  }
  return grpc::Status::OK;
}

grpc::Status
MpclientImpl::listen(grpc::ServerContext *context,
                     const mpclient::ListenRequest *request,
                     grpc::ServerWriter<mpclient::ListenResponse> *writer) {
  while (true) {
    auto session = std::make_shared<NetconfSession>();
    if (session->listen(request)) {
      mpclient::ListenResponse response;
      response.set_host(session->getHost());
      response.set_port(session->getPort());
      uint32_t sessionId = addSession(session);
      response.set_sessionid(sessionId);
      writer->Write(response);
      // Iterate again to see if there is another device waiting to Call Home
    } else {
      // Stop listening if there is timeout or error
      break;
    }
  }
  return grpc::Status::OK;
}

grpc::Status
MpclientImpl::disconnect(grpc::ServerContext *context,
                         const mpclient::DisconnectRequest *request,
                         mpclient::DisconnectResponse *response) {
  std::shared_ptr<NetconfSession> session = removeSession(request->sessionid());
  response->set_success(session.get() != nullptr);
  return grpc::Status::OK;
}

grpc::Status
MpclientImpl::netconfRpc(grpc::ServerContext *context,
                         const mpclient::NetconfRpcRequest *request,
                         mpclient::NetconfRpcResponse *response) {
  std::shared_lock readLock(sessionsMutex_);
  auto sessionIt = sessions_.find(request->sessionid());
  if (sessionIt == sessions_.end()) {
    response->set_status(mpclient::NetconfRpcResponse::INVALID_SESSION);
  } else {
    sessionIt->second->netconfRpc(request, response);
  }
  return grpc::Status::OK;
}

grpc::Status MpclientImpl::streamNotifications(
    grpc::ServerContext *context,
    const mpclient::StreamNotificationsRequest *request,
    grpc::ServerWriter<mpclient::StreamNotificationsResponse> *writer) {
  std::shared_lock readLock(sessionsMutex_);
  auto sessionIt = sessions_.find(request->sessionid());
  if (sessionIt != sessions_.end()) {
    // Attach a callback to the NETCONF session; wait for session to finish
    std::future<void> doneFuture = sessionIt->second->addNotificationCallback(
        [request, writer](const std::string &serializedYang) {
          mpclient::StreamNotificationsResponse response;
          response.set_serializedyang(serializedYang);
          writer->Write(response);
        });
    readLock.unlock();
    doneFuture.get();
  }
  return grpc::Status::OK;
}

grpc::Status
MpclientImpl::startSupervision(grpc::ServerContext *context,
                               const mpclient::StartSupervisionRequest *request,
                               mpclient::StartSupervisionResponse *response) {
  std::shared_lock readLock(sessionsMutex_);
  auto sessionIt = sessions_.find(request->sessionid());
  if (sessionIt == sessions_.end()) {
    response->set_success(false);
    return grpc::Status::OK;
  }

  // Add a notification callback
  // Use a weak_ptr to access the session but not prevent it from being deleted
  std::weak_ptr<NetconfSession> sessionRef = sessionIt->second;
  uint32_t sessionId = request->sessionid();
  sessionIt->second->addNotificationCallback(
      [sessionRef, sessionId](const struct nc_notif *notification) {
        // Send a watchdog reset RPC when this kind of notification is received
        const std::string name(notification->tree->schema->name);
        if (name == "supervision-notification") {
          auto session = sessionRef.lock();
          if (session) {
            mpclient::NetconfRpcRequest watchdogRequest;
            mpclient::NetconfRpcResponse watchdogResponse;
            watchdogRequest.set_sessionid(sessionId);
            watchdogRequest.set_serializedyang(kRpcResetWatchdog);
            watchdogRequest.set_timeoutsec(kRpcTimeoutSec);
            session->netconfRpc(&watchdogRequest, &watchdogResponse);
            if (watchdogResponse.status() !=
                mpclient::NetconfRpcResponse::SUCCESS) {
              LOG(WARNING) << "Failed to reset watchdog on session "
                           << sessionId;
            } else {
              LOG(INFO) << "Reset watchdog on session " << sessionId << ": "
                        << (watchdogResponse.has_message()
                                ? watchdogResponse.message()
                                : "OK");
            }
          }
        }
      });

  // Subscribe to notifications using filter
  mpclient::NetconfRpcRequest subscribeRequest;
  mpclient::NetconfRpcResponse subscribeResponse;
  subscribeRequest.set_sessionid(sessionId);
  subscribeRequest.set_serializedyang(kRpcSubscribeSupervisionNotifications);
  subscribeRequest.set_timeoutsec(kRpcTimeoutSec);
  sessionIt->second->netconfRpc(&subscribeRequest, &subscribeResponse);
  if (subscribeResponse.status() != mpclient::NetconfRpcResponse::SUCCESS ||
      subscribeResponse.returntype() != mpclient::NetconfRpcResponse::OK) {
    LOG(ERROR) << subscribeResponse.message();
    response->set_success(false);
    return grpc::Status::OK;
  }

  response->set_success(true);
  return grpc::Status::OK;
}

uint32_t MpclientImpl::addSession(std::shared_ptr<NetconfSession> session) {
  std::unique_lock writeLock(sessionsMutex_);
  const uint32_t sessionId = sessionsCounter_++;
  sessions_.emplace(sessionId, session);
  return sessionId;
}

std::shared_ptr<NetconfSession>
MpclientImpl::removeSession(const uint32_t sessionId) {
  std::unique_lock writeLock(sessionsMutex_);
  auto sessionIt = sessions_.find(sessionId);
  if (sessionIt != sessions_.end()) {
    auto output = sessionIt->second;
    sessions_.erase(sessionIt);
    return output;
  } else {
    return std::shared_ptr<NetconfSession>(nullptr);
  }
}
