#include "StreamNotificationsTestFixture.h"

#include "Common.h"

#include <chrono>
#include <sstream>
#include <thread>

#include <gflags/gflags.h>
#include <glog/logging.h>

DECLARE_string(netconfHost);
DECLARE_int32(netconfPort);
DECLARE_string(netconfUser);
DECLARE_string(netconfPassword);

namespace {
const uint32_t kNetconfRpcTimeoutSec = 1;
}

void StreamNotificationsTest::SetUp() {
  // Initialize a connection
  std::optional<mpclient::ConnectResponse> response =
      client_.connect(FLAGS_netconfHost, FLAGS_netconfPort, FLAGS_netconfUser,
                      std::nullopt, std::nullopt, FLAGS_netconfPassword);
  ASSERT_TRUE(response.has_value());
  ASSERT_TRUE(response->success());
  checkSessionId(response->sessionid());
  sessionId_ = response->sessionid();
}

void StreamNotificationsTest::subscribe() {
  // Subscribe to all notifications (i.e. "NETCONF" stream)
  std::string request =
      "<create-subscription "
      "xmlns=\"urn:ietf:params:xml:ns:netconf:notification:1.0\"/>";
  std::optional<mpclient::NetconfRpcResponse> response =
      client_.netconfRpc(sessionId_, request, kNetconfRpcTimeoutSec);
  ASSERT_TRUE(response.has_value());
  ASSERT_EQ(response->status(), mpclient::NetconfRpcResponse::SUCCESS);
  ASSERT_EQ(response->returntype(), mpclient::NetconfRpcResponse::OK);
}

void StreamNotificationsTest::streamNotifications() {
  // Listen for notifications in a separate thread; this is necessary because
  // notifications have to be created by RPC, which is synchronous and does not
  // return until the notification is sent
  notificationsFuture_ = std::async(std::launch::async, [this]() {
    return client_.streamNotifications(sessionId_);
  });
  // Give notification stream time to register itself
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void StreamNotificationsTest::disconnect() {
  std::optional<mpclient::DisconnectResponse> response =
      client_.disconnect(sessionId_);
  ASSERT_TRUE(response.has_value());
  ASSERT_TRUE(response->success());
}

std::vector<mpclient::StreamNotificationsResponse>
StreamNotificationsTest::getNotifications() {
  // The notifications listening loop should end very quickly
  std::future_status status =
      notificationsFuture_.wait_for(std::chrono::seconds(1));
  if (status != std::future_status::ready) {
    LOG(INFO) << "streamNotifications is hanging... exiting";
    exit(-1);
  }
  return notificationsFuture_.get();
}

void StreamNotificationsTest::mockNotification(const std::string &contents) {
  std::stringstream requestStream;
  requestStream
      << "<invoke-notification "
         "xmlns=\"urn:o-ran-sc:params:xml:ns:yang:nts:network:function\">"
      << "<notification-format>json</notification-format>"
      << "<notification-object>" << contents << "</notification-object>"
      << "</invoke-notification>";
  std::optional<mpclient::NetconfRpcResponse> response = client_.netconfRpc(
      sessionId_, requestStream.str(), kNetconfRpcTimeoutSec);
  ASSERT_TRUE(response.has_value());
  ASSERT_EQ(response->status(), mpclient::NetconfRpcResponse::SUCCESS);
  ASSERT_EQ(response->returntype(), mpclient::NetconfRpcResponse::DATA);
  ASSERT_EQ(response->message(),
            std::string("<status "
                        "xmlns=\"urn:o-ran-sc:params:xml:ns:yang:nts:network:"
                        "function\">SUCCESS</status>\n"));
  // Give notification time to trigger
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
