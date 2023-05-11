// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#pragma once

#include "mpclient.pb.h"

#include <functional>
#include <future>
#include <mutex>
#include <string>
#include <vector>

#include <nc_client.h>

/**
 * Class for establishing and managing a NETCONF session.
 */
class NetconfSession {
public:
  /**
   * Initialize a NETCONF session with a `Config` object.
   */
  NetconfSession();
  ~NetconfSession();

  // Disable copying
  NetconfSession(const NetconfSession &) = delete;
  NetconfSession operator=(const NetconfSession &) = delete;

  /**
   * Use captured parameters to connect over SSH. Returns true if the connection
   * is successful.
   */
  bool connect(const mpclient::ConnectRequest *request);

  /**
   * Listen for a Call Home. Blocking. Returns true if the connection is
   * successful.
   */
  bool listen(const mpclient::ListenRequest *request);

  /**
   * Perform a NETCONF RPC. Blocking.
   */
  void netconfRpc(const mpclient::NetconfRpcRequest *request,
                  mpclient::NetconfRpcResponse *response);

  /**
   * Add a callback for passing notifications. The future returned by this
   * method is fulfilled when the object instance destroys. The std::string
   * overload is called after the notification YANG is serialized.
   */
  std::future<void> addNotificationCallback(
      const std::function<void(const struct nc_notif *)> &callback);
  std::future<void> addNotificationCallback(
      const std::function<void(const std::string &)> &callback);

  /**
   * Get the host of the NETCONF connection.
   */
  std::string getHost() const;

  /**
   * Get the port of the NETCONF connection.
   */
  uint32_t getPort() const;

private:
  /**
   * Initialize the NETCONF environment for a connection.
   */
  static bool initConnect(const mpclient::Authentication *auth);

  /**
   * Initialize the NETCONF environment to listen for a Call Home
   */
  static bool initListen(const mpclient::Authentication *auth);

  /**
   * Check whether the session is valid. Throws an error if not.
   */
  void checkSession() const;

  /**
   * NETCONF session context.
   */
  struct nc_session *session_ = nullptr;

  /**
   * Signal to notification listeners when this session is done.
   */
  std::vector<std::promise<void>> sessionDonePromises_;
  std::mutex notificationStateMutex_;
};
