// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#pragma once

#include <TestClient.h>

#include <gtest/gtest.h>

/**
 * Wrapper around the client class and a Google Test class. This can also serve
 * as a foundation for more complex fixtures.
 */
class ConnectionTest : public testing::Test {
public:
  ConnectionTest();

  /**
   * Check that session IDs are strictly increasing.
   */
  void checkSessionId(const uint32_t sessionId);

protected:
  TestClient client_;
  static int32_t maxSessionId_;
};
