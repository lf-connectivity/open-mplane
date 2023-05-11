/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      singleton.cpp
 * \brief     Netopeer Monitoring service singleton
 *
 *
 * \details
 *
 */
#include "NetopeerMonService.h"

using namespace Mplane;

std::shared_ptr<INetopeerMonService>
Mplane::INetopeerMonService::singleton(void) {
  static std::shared_ptr<NetopeerMonService> instance(
      std::make_shared<NetopeerMonService>());
  return instance;
}
