/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangeElementFactories.cpp
 * \brief     Yang Element Factories
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IYangElement.h"
#include "YangElement.h"

using namespace Mplane;

// ====================================================================================================
std::shared_ptr<IYangElement>
IYangElement::makeElement(
    std::string type, std::string name, std::string value, std::string access) {
  std::shared_ptr<IYangElement> instance(
      std::make_shared<YangElement>(type, name, value, access));
  return instance;
}

// ====================================================================================================
std::shared_ptr<IYangElement>
IYangElement::makeElement(
    std::string type, std::string name, std::string value) {
  std::shared_ptr<IYangElement> instance(
      std::make_shared<YangElement>(type, name, value));
  return instance;
}

// ====================================================================================================
std::shared_ptr<IYangElement>
IYangElement::makeElement(std::string type, std::string name) {
  std::shared_ptr<IYangElement> instance(
      std::make_shared<YangElement>(type, name));
  return instance;
}

// ====================================================================================================
std::shared_ptr<IYangElement>
IYangElement::makeElement(std::string type) {
  std::shared_ptr<IYangElement> instance(std::make_shared<YangElement>(type));
  return instance;
}
