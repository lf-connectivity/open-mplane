// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#pragma once

#include "StreamNotificationsTestFixture.h"

class StartSupervisionTest : public StreamNotificationsTest {
public:
  void SetUp() override;

  /**
   * Trigger a mock supervision notification
   */
  void mockSupervisionNotification();
};
