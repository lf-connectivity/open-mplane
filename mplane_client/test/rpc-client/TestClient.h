// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#pragma once

#include "mpclient.grpc.pb.h"

#include <future>

/**
 * Implementation of a client; this is the layer that interacts with the
 * mpclient server. All mpclient RPCs are implemented in this class.
 */
class TestClient {
public:
  TestClient(std::shared_ptr<grpc::Channel> channel);

  std::optional<mpclient::ConnectResponse>
  connect(const mpclient::ConnectRequest &request);
  std::optional<mpclient::ConnectResponse>
  connect(const std::string &host, const uint32_t port, const std::string &user,
          const std::optional<std::string> &publicKeyPath,
          const std::optional<std::string> &privateKeyPath,
          const std::optional<std::string> &password);

  std::vector<mpclient::ListenResponse>
  listen(const mpclient::ListenRequest &request);
  std::vector<mpclient::ListenResponse>
  listen(const std::string &host, const uint32_t port, const std::string &user,
         const std::optional<std::string> &publicKeyPath,
         const std::optional<std::string> &privateKeyPath,
         const std::optional<std::string> &password, const uint32_t timeoutSec);

  std::optional<mpclient::DisconnectResponse>
  disconnect(const mpclient::DisconnectRequest &request);
  std::optional<mpclient::DisconnectResponse>
  disconnect(const uint32_t sessionId);

  std::optional<mpclient::NetconfRpcResponse>
  netconfRpc(const mpclient::NetconfRpcRequest &request);
  std::optional<mpclient::NetconfRpcResponse>
  netconfRpc(const uint32_t sessionId, const std::string &serializedYang,
             const uint32_t timeoutSec);

  std::future<void> streamNotifications(
      const mpclient::StreamNotificationsRequest &request,
      const std::function<void(const mpclient::StreamNotificationsResponse &)>
          &callback);
  std::vector<mpclient::StreamNotificationsResponse>
  streamNotifications(const mpclient::StreamNotificationsRequest &request);
  std::vector<mpclient::StreamNotificationsResponse>
  streamNotifications(const uint32_t sessionId);

  std::optional<mpclient::StartSupervisionResponse>
  startSupervision(const mpclient::StartSupervisionRequest &request);
  std::optional<mpclient::StartSupervisionResponse>
  startSupervision(const uint32_t sessionId);

private:
  std::unique_ptr<mpclient::Mpclient::Stub> stub_;
};
