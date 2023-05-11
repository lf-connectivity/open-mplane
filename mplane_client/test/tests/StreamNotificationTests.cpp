#include "StreamNotificationsTestFixture.h"

#include <glog/logging.h>

TEST_F(StreamNotificationsTest, CorrectExit) {
  // Check that notification streaming starts and stops correctly
  streamNotifications();
  disconnect();
  std::vector<mpclient::StreamNotificationsResponse> notifications =
      getNotifications();
  ASSERT_EQ(notifications.size(), 0);
}

TEST_F(StreamNotificationsTest, CorrectNotification) {
  // Trigger a single notification
  streamNotifications();
  subscribe();
  mockNotification("{\"o-ran-supervision:supervision-notification\": {}}");
  disconnect();
  std::vector<mpclient::StreamNotificationsResponse> notifications =
      getNotifications();
  ASSERT_EQ(notifications.size(), 1);
  ASSERT_EQ(
      notifications[0].serializedyang(),
      "<supervision-notification xmlns=\"urn:o-ran:supervision:1.0\"/>\n");
}

TEST_F(StreamNotificationsTest, BadSessionId) {
  // Since the session ID is invalid, nothing should happen
  uint32_t realSessionId = sessionId_;
  sessionId_ = 1000000;
  streamNotifications();
  std::vector<mpclient::StreamNotificationsResponse> notifications =
      getNotifications();
  ASSERT_EQ(notifications.size(), 0);
  sessionId_ = realSessionId;
  disconnect();
}
