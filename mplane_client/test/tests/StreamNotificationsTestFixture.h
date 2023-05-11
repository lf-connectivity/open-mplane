// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#pragma once

#include "ConnectionTestFixture.h"

#include <future>

class StreamNotificationsTest : public ConnectionTest {
public:
  void SetUp() override;

  /**
   * Subscribe to all notifications.
   */
  void subscribe();

  /**
   * Initiate the notifications streaming.
   */
  void streamNotifications();

  /**
   * Close the session.
   */
  void disconnect();

  /**
   * Retrieve the notifications; assertion will fail if there is a timeout on
   * the streaming loop exiting.
   */
  std::vector<mpclient::StreamNotificationsResponse> getNotifications();

  /**
   * Create a mock notification using the invoke-notification RPC. The contents
   * are YANG serialized as JSON.
   */
  void mockNotification(const std::string &contents);

protected:
  int32_t sessionId_ = -1;
  std::future<std::vector<mpclient::StreamNotificationsResponse>>
      notificationsFuture_;
};
