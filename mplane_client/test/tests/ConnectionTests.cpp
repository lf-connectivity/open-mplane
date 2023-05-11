// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "ConnectionTestFixture.h"

#include "Common.h"

#include <gflags/gflags.h>

DECLARE_string(netconfHost);
DECLARE_int32(netconfPort);
DECLARE_string(netconfUser);
DECLARE_string(netconfPassword);
DECLARE_int32(netconfCallhomePort);
DECLARE_string(netconfPublicKeyPath);
DECLARE_string(netconfPrivateKeyPath);

namespace {
const std::string kBadUsername = "nobody";

// Short timeout so that Call Home tests move quickly
const uint32_t kCallhomeTimeoutSec = 3;
} // namespace

TEST_F(ConnectionTest, Connect_CorrectWithPublickey) {
  // Most basic connection possible which should succeed
  std::optional<mpclient::ConnectResponse> responseConnect = client_.connect(
      FLAGS_netconfHost, FLAGS_netconfPort, FLAGS_netconfUser,
      FLAGS_netconfPublicKeyPath, FLAGS_netconfPrivateKeyPath, std::nullopt);
  ASSERT_TRUE(responseConnect.has_value());
  ASSERT_TRUE(responseConnect->success());
  checkSessionId(responseConnect->sessionid());

  // Disconnect the session
  std::optional<mpclient::DisconnectResponse> responseDisconnect =
      client_.disconnect(responseConnect->sessionid());
  ASSERT_TRUE(responseDisconnect.has_value());
  ASSERT_TRUE(responseDisconnect->success());

  // Try to disconnect the same session twice which should fail
  responseDisconnect = client_.disconnect(responseConnect->sessionid());
  ASSERT_TRUE(responseDisconnect.has_value());
  ASSERT_FALSE(responseDisconnect->success());
}

TEST_F(ConnectionTest, Connect_CorrectWithPassword) {
  // Most basic connection possible which should succeed
  std::optional<mpclient::ConnectResponse> responseConnect =
      client_.connect(FLAGS_netconfHost, FLAGS_netconfPort, FLAGS_netconfUser,
                      std::nullopt, std::nullopt, FLAGS_netconfPassword);
  ASSERT_TRUE(responseConnect.has_value());
  ASSERT_TRUE(responseConnect->success());
  checkSessionId(responseConnect->sessionid());

  // Disconnect the session
  std::optional<mpclient::DisconnectResponse> responseDisconnect =
      client_.disconnect(responseConnect->sessionid());
  ASSERT_TRUE(responseDisconnect.has_value());
  ASSERT_TRUE(responseDisconnect->success());
}

TEST_F(ConnectionTest, Connect_BadTargetAddr) {
  // Try to connect to NETCONF on a bogus port
  std::optional<mpclient::ConnectResponse> response = client_.connect(
      FLAGS_netconfHost, FLAGS_netconfPort + 10, FLAGS_netconfUser,
      FLAGS_netconfPublicKeyPath, FLAGS_netconfPrivateKeyPath, std::nullopt);
  ASSERT_TRUE(response.has_value());
  ASSERT_FALSE(response->success());
}

TEST_F(ConnectionTest, Connect_BadUsername) {
  // Try to connect to NETCONF with a bad username
  std::optional<mpclient::ConnectResponse> response = client_.connect(
      FLAGS_netconfHost, FLAGS_netconfPort, kBadUsername,
      FLAGS_netconfPublicKeyPath, FLAGS_netconfPrivateKeyPath, std::nullopt);
  ASSERT_TRUE(response.has_value());
  ASSERT_FALSE(response->success());
}

TEST_F(ConnectionTest, Connect_NoAuth) {
  // Try to connect without authentication
  std::optional<mpclient::ConnectResponse> response =
      client_.connect(FLAGS_netconfHost, FLAGS_netconfPort, FLAGS_netconfUser,
                      std::nullopt, std::nullopt, std::nullopt);
  ASSERT_TRUE(response.has_value());
  ASSERT_FALSE(response->success());
}

TEST_F(ConnectionTest, Listen_CorrectWithPublicKey) {
  // There is a single NETCONF server trying to call home which should succeed
  std::vector<mpclient::ListenResponse> listenResponses = client_.listen(
      FLAGS_netconfHost, FLAGS_netconfCallhomePort, FLAGS_netconfUser,
      FLAGS_netconfPublicKeyPath, FLAGS_netconfPrivateKeyPath, std::nullopt,
      kCallhomeTimeoutSec);
  ASSERT_EQ(listenResponses.size(), 1);
  mpclient::ListenResponse &listenResponse = listenResponses[0];
  checkSessionId(listenResponse.sessionid());
  ASSERT_GT(listenResponse.host().size(), 0);

  // The single NETCONF server has already called home, nothing should happen
  listenResponses = client_.listen(
      FLAGS_netconfHost, FLAGS_netconfCallhomePort, FLAGS_netconfUser,
      FLAGS_netconfPublicKeyPath, FLAGS_netconfPrivateKeyPath, std::nullopt,
      kCallhomeTimeoutSec);
  ASSERT_EQ(listenResponses.size(), 0);

  // Disconnect the session produced from Call Home which should succeed
  std::optional<mpclient::DisconnectResponse> disconnectResponse =
      client_.disconnect(listenResponse.sessionid());
  ASSERT_TRUE(disconnectResponse.has_value());
  ASSERT_TRUE(disconnectResponse->success());
}

TEST_F(ConnectionTest, Listen_CorrectWithPassword) {
  // There is a single NETCONF server trying to call home which should succeed
  std::vector<mpclient::ListenResponse> listenResponses = client_.listen(
      FLAGS_netconfHost, FLAGS_netconfCallhomePort, FLAGS_netconfUser,
      std::nullopt, std::nullopt, FLAGS_netconfPassword, kCallhomeTimeoutSec);
  ASSERT_EQ(listenResponses.size(), 1);
  mpclient::ListenResponse &listenResponse = listenResponses[0];
  checkSessionId(listenResponse.sessionid());
  ASSERT_GT(listenResponse.host().size(), 0);

  // Disconnect the session produced from Call Home which should succeed
  std::optional<mpclient::DisconnectResponse> disconnectResponse =
      client_.disconnect(listenResponse.sessionid());
  ASSERT_TRUE(disconnectResponse.has_value());
  ASSERT_TRUE(disconnectResponse->success());
}

TEST_F(ConnectionTest, Listen_BadUsername) {
  // Try to listen without authentication
  std::vector<mpclient::ListenResponse> listenResponses =
      client_.listen(FLAGS_netconfHost, FLAGS_netconfCallhomePort, kBadUsername,
                     FLAGS_netconfPublicKeyPath, FLAGS_netconfPrivateKeyPath,
                     std::nullopt, kCallhomeTimeoutSec);
  ASSERT_EQ(listenResponses.size(), 0);
}

TEST_F(ConnectionTest, Listen_NoAuth) {
  // Try to listen without authentication
  std::vector<mpclient::ListenResponse> listenResponses = client_.listen(
      FLAGS_netconfHost, FLAGS_netconfCallhomePort, FLAGS_netconfUser,
      std::nullopt, std::nullopt, std::nullopt, kCallhomeTimeoutSec);
  ASSERT_EQ(listenResponses.size(), 0);
}
