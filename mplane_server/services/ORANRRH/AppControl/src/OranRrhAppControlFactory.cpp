/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranRrhAppControlFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "OranRrhAppControl.h"

using namespace Mplane;

std::shared_ptr<IAppControl>
IAppControlFactory::getInterface() {
  static std::shared_ptr<IAppControl> appControl(new OranRrhAppControl());
  return appControl;
}
