// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "TestClient.h"

#include <thread>

#include <grpcpp/grpcpp.h>

TestClient::TestClient(std::shared_ptr<grpc::Channel> channel)
    : stub_(mpclient::Mpclient::NewStub(channel)) {}

std::optional<mpclient::ConnectResponse>
TestClient::connect(const mpclient::ConnectRequest &request) {
  mpclient::ConnectResponse response;
  grpc::ClientContext context;
  grpc::Status status = stub_->connect(&context, request, &response);
  if (status.ok()) {
    return std::optional<mpclient::ConnectResponse>(response);
  } else {
    return std::nullopt;
  }
}

std::optional<mpclient::ConnectResponse>
TestClient::connect(const std::string &host, const uint32_t port,
                    const std::string &user,
                    const std::optional<std::string> &publicKeyPath,
                    const std::optional<std::string> &privateKeyPath,
                    const std::optional<std::string> &password) {
  mpclient::ConnectRequest request;
  request.set_host(host);
  request.set_port(port);
  mpclient::Authentication *auth = request.mutable_auth();
  auth->set_user(user);
  if (publicKeyPath.has_value() && privateKeyPath.has_value()) {
    mpclient::KeyPair *keypair = auth->add_keys();
    keypair->set_publicpath(*publicKeyPath);
    keypair->set_privatepath(*privateKeyPath);
  }
  if (password.has_value()) {
    auth->set_password(*password);
  }
  return connect(request);
}

std::vector<mpclient::ListenResponse>
TestClient::listen(const mpclient::ListenRequest &request) {
  mpclient::ListenResponse response;
  std::vector<mpclient::ListenResponse> output;
  grpc::ClientContext context;
  std::unique_ptr<grpc::ClientReader<mpclient::ListenResponse>> reader(
      stub_->listen(&context, request));
  while (reader->Read(&response)) {
    output.push_back(response);
  }
  return output;
}

std::vector<mpclient::ListenResponse> TestClient::listen(
    const std::string &host, const uint32_t port, const std::string &user,
    const std::optional<std::string> &publicKeyPath,
    const std::optional<std::string> &privateKeyPath,
    const std::optional<std::string> &password, const uint32_t timeoutSec) {
  mpclient::ListenRequest request;
  request.set_host(host);
  request.set_port(port);
  request.set_timeoutsec(timeoutSec);
  mpclient::Authentication *auth = request.mutable_auth();
  auth->set_user(user);
  if (publicKeyPath.has_value() && privateKeyPath.has_value()) {
    mpclient::KeyPair *keypair = auth->add_keys();
    keypair->set_publicpath(*publicKeyPath);
    keypair->set_privatepath(*privateKeyPath);
  }
  if (password.has_value()) {
    auth->set_password(*password);
  }
  return listen(request);
}

std::optional<mpclient::DisconnectResponse>
TestClient::disconnect(const mpclient::DisconnectRequest &request) {
  mpclient::DisconnectResponse response;
  grpc::ClientContext context;
  grpc::Status status = stub_->disconnect(&context, request, &response);
  if (status.ok()) {
    return std::optional<mpclient::DisconnectResponse>(response);
  } else {
    return std::nullopt;
  }
}

std::optional<mpclient::DisconnectResponse>
TestClient::disconnect(const uint32_t sessionId) {
  mpclient::DisconnectRequest request;
  request.set_sessionid(sessionId);
  return disconnect(request);
}

std::optional<mpclient::NetconfRpcResponse>
TestClient::netconfRpc(const mpclient::NetconfRpcRequest &request) {
  mpclient::NetconfRpcResponse response;
  grpc::ClientContext context;
  grpc::Status status = stub_->netconfRpc(&context, request, &response);
  if (status.ok()) {
    return std::optional<mpclient::NetconfRpcResponse>(response);
  } else {
    return std::nullopt;
  }
}

std::optional<mpclient::NetconfRpcResponse>
TestClient::netconfRpc(const uint32_t sessionId,
                       const std::string &serializedYang,
                       const uint32_t timeoutSec) {
  mpclient::NetconfRpcRequest request;
  request.set_sessionid(sessionId);
  request.set_serializedyang(serializedYang);
  request.set_timeoutsec(timeoutSec);
  return netconfRpc(request);
}

std::future<void> TestClient::streamNotifications(
    const mpclient::StreamNotificationsRequest &request,
    const std::function<void(const mpclient::StreamNotificationsResponse &)>
        &callback) {
  return std::async(std::launch::async, [this, request, callback]() {
    mpclient::StreamNotificationsResponse response;
    std::vector<mpclient::StreamNotificationsResponse> output;
    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReader<mpclient::StreamNotificationsResponse>>
        reader(stub_->streamNotifications(&context, request));
    while (reader->Read(&response)) {
      callback(response);
    }
  });
}

std::vector<mpclient::StreamNotificationsResponse>
TestClient::streamNotifications(
    const mpclient::StreamNotificationsRequest &request) {
  mpclient::StreamNotificationsResponse response;
  std::vector<mpclient::StreamNotificationsResponse> output;
  grpc::ClientContext context;
  std::unique_ptr<grpc::ClientReader<mpclient::StreamNotificationsResponse>>
      reader(stub_->streamNotifications(&context, request));
  while (reader->Read(&response)) {
    output.push_back(response);
  }
  return output;
}

std::vector<mpclient::StreamNotificationsResponse>
TestClient::streamNotifications(const uint32_t sessionId) {
  mpclient::StreamNotificationsRequest request;
  request.set_sessionid(sessionId);
  return streamNotifications(request);
}

std::optional<mpclient::StartSupervisionResponse>
TestClient::startSupervision(const mpclient::StartSupervisionRequest &request) {
  mpclient::StartSupervisionResponse response;
  grpc::ClientContext context;
  grpc::Status status = stub_->startSupervision(&context, request, &response);
  if (status.ok()) {
    return std::optional<mpclient::StartSupervisionResponse>(response);
  } else {
    return std::nullopt;
  }
}

std::optional<mpclient::StartSupervisionResponse>
TestClient::startSupervision(const uint32_t sessionId) {
  mpclient::StartSupervisionRequest request;
  request.set_sessionid(sessionId);
  return startSupervision(request);
}
