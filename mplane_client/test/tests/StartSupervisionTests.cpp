// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "StartSupervisionTestFixture.h"

TEST_F(StartSupervisionTest, Correct) {
  // Send a supervision-notification and check that it actually appeared as a
  // notification
  mockSupervisionNotification();
  disconnect();
  std::vector<mpclient::StreamNotificationsResponse> responses =
      getNotifications();
  ASSERT_EQ(responses.size(), 1);
}
