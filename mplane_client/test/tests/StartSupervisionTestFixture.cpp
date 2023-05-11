// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "StartSupervisionTestFixture.h"

void StartSupervisionTest::SetUp() {
  StreamNotificationsTest::SetUp();
  std::optional<mpclient::StartSupervisionResponse> response =
      client_.startSupervision(sessionId_);
  ASSERT_TRUE(response.has_value());
  ASSERT_TRUE(response->success());
  streamNotifications();
  // startSupervision creates a subscription, so there is no need to do so here;
  // if we receive notifications, then that subscription worked
}

void StartSupervisionTest::mockSupervisionNotification() {
  mockNotification("{\"o-ran-supervision:supervision-notification\": {}}");
}
