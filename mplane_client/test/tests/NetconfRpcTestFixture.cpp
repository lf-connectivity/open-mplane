// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "NetconfRpcTestFixture.h"

#include "Common.h"

#include <gflags/gflags.h>

DECLARE_string(netconfHost);
DECLARE_int32(netconfPort);
DECLARE_string(netconfUser);
DECLARE_string(netconfPassword);

int32_t NetconfRpcTest::sessionId_ = -1;

NetconfRpcTest::NetconfRpcTest() {
  // Only make a new connection once so that tests go more quickly
  if (sessionId_ < 0) {
    std::optional<mpclient::ConnectResponse> response =
        client_.connect(FLAGS_netconfHost, FLAGS_netconfPort, FLAGS_netconfUser,
                        std::nullopt, std::nullopt, FLAGS_netconfPassword);
    if (response.has_value() && response->success()) {
      checkSessionId(response->sessionid());
      sessionId_ = response->sessionid();
    } else {
      throw std::runtime_error("Could not open a session");
    }
  }
}
