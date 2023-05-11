// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#pragma once

#include "ConnectionTestFixture.h"

class NetconfRpcTest : public ConnectionTest {
public:
  NetconfRpcTest();

protected:
  static int32_t sessionId_;
};
