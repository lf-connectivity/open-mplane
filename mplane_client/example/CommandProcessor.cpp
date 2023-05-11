// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "CommandProcessor.h"

#include <sstream>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/util/json_util.h>

DECLARE_string(netconfHost);
DECLARE_int32(netconfPort);
DECLARE_string(netconfUser);
DECLARE_string(netconfPassword);
DECLARE_string(netconfCallhomeHost);
DECLARE_int32(netconfCallhomePort);
DECLARE_string(netconfPublicKeyPath);
DECLARE_string(netconfPrivateKeyPath);

namespace {
const std::string kTermColorDefault = "\033[0m";
const std::string kTermColorGreen = "\033[0;32m";
const std::string kTermColorRed = "\033[0;31m";
const std::string kTermColorCyan = "\033[0;36m";
const std::string kTermColorYellow = "\033[0;33m";

std::string protobufToJson(const google::protobuf::Message &message) {
  std::string output;
  google::protobuf::util::JsonPrintOptions options;
  options.always_print_primitive_fields = true;
  options.preserve_proto_field_names = true;
  google::protobuf::util::MessageToJsonString(message, &output, options);
  return output;
}
} // namespace

CommandProcessor::CommandProcessor(std::shared_ptr<grpc::Channel> channel)
    : client_(channel) {}

CommandProcessor::~CommandProcessor() {
  waitForNotifications();
  if (sessionId_.has_value()) {
    client_.disconnect(*sessionId_);
  }
}

void CommandProcessor::processCommand(
    mpclient::CommandSequence::OneOf command) {
  std::unique_lock lock(loggingMutex_);
  numCommands_++;
  bool success = false;

  // The process for all commands follows the same basic structure:
  //  1. If required, set the session ID
  //  2. Perform the command
  //  3. Check that a reply was received over the M-Plane
  //  4. Check that the logic of the reply makes sense/do things with reply
  switch (command.data_case()) {
  case mpclient::CommandSequence::OneOf::kConnect:
    success = performConnect(command.mutable_connect());
    break;
  case mpclient::CommandSequence::OneOf::kListen:
    success = performListen(command.mutable_listen());
    break;
  case mpclient::CommandSequence::OneOf::kDisconnect:
    success = performDisconnect(command.mutable_disconnect());
    break;
  case mpclient::CommandSequence::OneOf::kNetconfRpc:
    success = performNetconfRpc(command.mutable_netconfrpc());
    break;
  case mpclient::CommandSequence::OneOf::kStreamNotifications:
    success = performStreamNotifications(command.mutable_streamnotifications());
    break;
  case mpclient::CommandSequence::OneOf::kStartSupervision:
    success = performStartSupervision(command.mutable_startsupervision());
    break;
  default:
    LOG(WARNING) << "Command " << numCommands_ << ": " << kTermColorYellow
                 << "unrecognized command" << kTermColorDefault;
    success = false;
    break;
  }

  if (success) {
    LOG(INFO) << "Command " << numCommands_ << ": " << kTermColorGreen
              << "SUCCESS" << kTermColorDefault;
  }
}

void CommandProcessor::waitForNotifications() {
  for (auto &future : rpcFutures_) {
    future.get();
  }
  rpcFutures_.clear();
}

bool CommandProcessor::performConnect(mpclient::ConnectRequest *request) {
  LOG(INFO) << "Command " << numCommands_ << ": connect...";
  if (!gflags::GetCommandLineFlagInfoOrDie("netconfHost").is_default) {
    request->set_host(FLAGS_netconfHost);
  } else if (request->host() == "") {
    // The flag was not set and the command has no value for this field
    LOG(WARNING) << "Command " << numCommands_ << ": " << kTermColorYellow
                 << "missing 'host'" << kTermColorDefault;
  }
  if (request->port() == 0 ||
      !gflags::GetCommandLineFlagInfoOrDie("netconfPort").is_default) {
    request->set_port(FLAGS_netconfPort);
  } else {
    // The flag was not set and the command has no value for this field
    LOG(WARNING) << "Command " << numCommands_ << ": " << kTermColorYellow
                 << "missing 'port'" << kTermColorDefault;
  }
  fillInAuth(request->mutable_auth());
  LOG(INFO) << "Command " << numCommands_
            << ": connection params: " << protobufToJson(*request);
  auto response = client_.connect(*request);
  if (!checkMpclientRpcResponse(response)) {
    return false;
  } else if (!response->success()) {
    LOG(ERROR) << "Command " << numCommands_ << ": " << kTermColorRed
               << "connect failed" << kTermColorDefault;
    return false;
  }
  sessionId_ = response->sessionid();
  return true;
}

bool CommandProcessor::performListen(mpclient::ListenRequest *request) {
  LOG(INFO) << "Command " << numCommands_ << ": listen...";
  if (!gflags::GetCommandLineFlagInfoOrDie("netconfCallhomeHost").is_default) {
    request->set_host(FLAGS_netconfCallhomeHost);
  } else if (request->host() == "") {
    // The flag was not set and the command has no value for this field
    LOG(WARNING) << "Command " << numCommands_ << ": " << kTermColorYellow
                 << "missing 'host'" << kTermColorDefault;
  }
  if (!request->port() == 0 ||
      !gflags::GetCommandLineFlagInfoOrDie("netconfCallhomePort").is_default) {
    request->set_port(FLAGS_netconfCallhomePort);
  } else {
    // The flag was not set and the command has no value for this field
    LOG(WARNING) << "Command " << numCommands_ << ": " << kTermColorYellow
                 << "missing 'port'" << kTermColorDefault;
  }
  fillInAuth(request->mutable_auth());
  LOG(INFO) << "Command " << numCommands_
            << ": connection params: " << protobufToJson(*request);
  auto responses = client_.listen(*request);
  if (responses.size() != 1) {
    LOG(WARNING) << "Command " << numCommands_ << ": " << kTermColorYellow
                 << "listen produced " << responses.size() << " sessions"
                 << kTermColorDefault;
    return false;
  }
  LOG(INFO) << "Command " << numCommands_ << ": new session on "
            << responses.begin()->host() << ":" << responses.begin()->port();
  return true;
}

bool CommandProcessor::performDisconnect(mpclient::DisconnectRequest *request) {
  LOG(INFO) << "Command " << numCommands_ << ": disconnect...";
  if (!checkSessionId()) {
    return false;
  }
  request->set_sessionid(*sessionId_);
  auto response = client_.disconnect(*request);
  if (!checkMpclientRpcResponse(response)) {
    return false;
  } else if (!response->success()) {
    LOG(ERROR) << "Command " << numCommands_ << ": " << kTermColorRed
               << "disconnect failed" << kTermColorDefault;
    return false;
  }
  sessionId_ = std::nullopt;
  return true;
}

bool CommandProcessor::performNetconfRpc(mpclient::NetconfRpcRequest *request) {
  LOG(INFO) << "Command " << numCommands_ << ": netconfRpc...";
  if (!checkSessionId()) {
    return false;
  }
  request->set_sessionid(*sessionId_);
  auto response = client_.netconfRpc(*request);
  if (!checkMpclientRpcResponse(response)) {
    return false;
  } else if (response->status() == mpclient::NetconfRpcResponse::ERROR) {
    LOG(ERROR) << "Command " << numCommands_ << ": " << kTermColorRed
               << "error before response received from NETCONF server"
               << kTermColorDefault;
    return false;
  } else if (response->status() == mpclient::NetconfRpcResponse::TIMEOUT) {
    LOG(ERROR) << "Command " << numCommands_ << ": " << kTermColorRed
               << "timeout communicating with NETCONF server"
               << kTermColorDefault;
    return false;
  } else if (response->returntype() == mpclient::NetconfRpcResponse::OK) {
    LOG(INFO) << "Command " << numCommands_ << ": OK";
  } else {
    printYang(response->message(), numCommands_);
  }
  return true;
}

bool CommandProcessor::performStreamNotifications(
    mpclient::StreamNotificationsRequest *request) {
  LOG(INFO) << "Command " << numCommands_ << ": streamNotifications...";
  if (!checkSessionId()) {
    return false;
  }
  request->set_sessionid(*sessionId_);
  // Discarding the future is OK because a disconnect is performed in the
  // destructor and all threads receiving notifications should exit when the
  // session disconnects.
  rpcFutures_.push_back(client_.streamNotifications(
      *request,
      [this, commandNum = numCommands_ /* capture current command number */](
          const mpclient::StreamNotificationsResponse &response) {
        std::unique_lock lock(loggingMutex_);
        printYang(response.serializedyang(), commandNum);
      }));
  return true;
}

bool CommandProcessor::performStartSupervision(
    mpclient::StartSupervisionRequest *request) {
  LOG(INFO) << "Command " << numCommands_ << ": startSupervision...";
  request->set_sessionid(*sessionId_);
  auto response = client_.startSupervision(*request);
  if (!checkMpclientRpcResponse(response)) {
    return false;
  } else if (!response->success()) {
    LOG(ERROR) << "Command " << numCommands_ << ": " << kTermColorRed
               << "startSupervision failed" << kTermColorDefault;
    return false;
  }
  return true;
}

void CommandProcessor::fillInAuth(mpclient::Authentication *auth) const {
  if (!gflags::GetCommandLineFlagInfoOrDie("netconfUser").is_default) {
    auth->set_user(FLAGS_netconfUser);
  }
  if (!gflags::GetCommandLineFlagInfoOrDie("netconfPassword").is_default) {
    auth->set_password(FLAGS_netconfPassword);
  }
  if (!gflags::GetCommandLineFlagInfoOrDie("netconfPublicKeyPath").is_default &&
      !gflags::GetCommandLineFlagInfoOrDie("netconfPrivateKeyPath")
           .is_default) {
    mpclient::KeyPair *keys = auth->add_keys();
    keys->set_publicpath(FLAGS_netconfPublicKeyPath);
    keys->set_privatepath(FLAGS_netconfPrivateKeyPath);
  }
}

template <typename ResponseType>
bool CommandProcessor::checkMpclientRpcResponse(
    const std::optional<ResponseType> &response) const {
  if (!response.has_value()) {
    LOG(ERROR) << "Command " << numCommands_ << ": " << kTermColorCyan
               << "the mpclient RPC response was not received"
               << kTermColorDefault;
    return false;
  }
  return true;
}

bool CommandProcessor::checkSessionId() const {
  if (!sessionId_.has_value()) {
    LOG(ERROR) << "Command " << numCommands_ << ": " << kTermColorCyan
               << "an active session is required but not open"
               << kTermColorDefault;
    return false;
  }
  return true;
}

void CommandProcessor::printYang(const std::string &yang,
                                 const uint32_t commandNum) const {
  std::stringstream stream;
  stream << yang;
  std::string line;
  while (std::getline(stream, line)) {
    LOG(INFO) << "Command " << commandNum << ": " << line;
  }
}
