// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "NetconfRpcTestFixture.h"

#include "Common.h"

#include <limits>

#include <glog/logging.h>
#include <gtest/gtest.h>

namespace {
// Short timeout so that Call Home tests move quickly
const uint32_t kNetconfRpcTimeoutSec = 1;
} // namespace

TEST_F(NetconfRpcTest, CorrectOk) {
  // Perform a NETCONF RPC which should give back OK
  std::string request =
      "<discard-changes xmlns=\"urn:ietf:params:xml:ns:netconf:base:1.0\"/>";
  std::optional<mpclient::NetconfRpcResponse> response =
      client_.netconfRpc(sessionId_, request, kNetconfRpcTimeoutSec);
  ASSERT_TRUE(response.has_value());
  ASSERT_EQ(response->status(), mpclient::NetconfRpcResponse::SUCCESS);
  ASSERT_TRUE(response->has_returntype());
  ASSERT_EQ(response->returntype(), mpclient::NetconfRpcResponse::OK);
  ASSERT_FALSE(response->has_message());
}

TEST_F(NetconfRpcTest, CorrectData) {
  // Perform a NETCONF RPC which should give back actual data
  std::string request = loadFile("tests/cases/01_get-config_request.xml");
  std::string actualResponse =
      loadFile("tests/cases/01_get-config_response.xml");
  std::optional<mpclient::NetconfRpcResponse> response =
      client_.netconfRpc(sessionId_, request, kNetconfRpcTimeoutSec);
  ASSERT_TRUE(response.has_value());
  ASSERT_EQ(response->status(), mpclient::NetconfRpcResponse::SUCCESS);
  ASSERT_TRUE(response->has_returntype());
  ASSERT_EQ(response->returntype(), mpclient::NetconfRpcResponse::DATA);
  ASSERT_TRUE(response->has_message());
  ASSERT_EQ(response->message(), actualResponse);
}

TEST_F(NetconfRpcTest, CorrectDataError) {
  // Perform an RPC which gives an error (edit-config touches bogus fields)
  std::string request = loadFile("tests/cases/02_edit-config_request.xml");
  std::string actualResponse =
      loadFile("tests/cases/02_edit-config_response.xml");
  std::optional<mpclient::NetconfRpcResponse> response =
      client_.netconfRpc(sessionId_, request, kNetconfRpcTimeoutSec);
  ASSERT_TRUE(response.has_value());
  ASSERT_EQ(response->status(), mpclient::NetconfRpcResponse::SUCCESS);
  ASSERT_TRUE(response->has_returntype());
  ASSERT_EQ(response->returntype(), mpclient::NetconfRpcResponse::RPC_ERROR);
  ASSERT_TRUE(response->has_message());
  ASSERT_EQ(response->message(), actualResponse);
}

TEST_F(NetconfRpcTest, CorrectError) {
  // NETCONF RPC does not get executed because the XML has no namespace
  std::string request = "<discard-changes/>";
  std::optional<mpclient::NetconfRpcResponse> response =
      client_.netconfRpc(sessionId_, request, kNetconfRpcTimeoutSec);
  ASSERT_TRUE(response.has_value());
  ASSERT_EQ(response->status(), mpclient::NetconfRpcResponse::ERROR);
  ASSERT_FALSE(response->has_returntype());
  ASSERT_FALSE(response->has_message());
}

TEST_F(NetconfRpcTest, BadSessionId) {
  // Try to call the RPC on a (probably) invalid session
  std::string request = loadFile("tests/cases/01_get-config_request.xml");
  std::optional<mpclient::NetconfRpcResponse> response =
      client_.netconfRpc(1000000, request, kNetconfRpcTimeoutSec);
  ASSERT_TRUE(response.has_value());
  ASSERT_EQ(response->status(), mpclient::NetconfRpcResponse::INVALID_SESSION);
  ASSERT_FALSE(response->has_returntype());
  ASSERT_FALSE(response->has_message());
}
