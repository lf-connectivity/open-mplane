/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangElement.cpp
 * \brief     Yang Element methods and interfaces
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "YangElement.h"
#include "IYangElement.h"

using namespace Mplane;

// ====================================================================================================
YangElement::YangElement(std::string type) {
  elementType = type;
  elementName = "\0";
  elementValue = "\0";
  elementVersion = "\0";
  elementAccessPermissions = "\0";
}

// ====================================================================================================
YangElement::YangElement(std::string type, std::string name) {
  elementType = type;
  elementName = name;
  elementValue = "\0";
  elementVersion = "\0";
  elementAccessPermissions = "\0";
}

// ====================================================================================================
YangElement::YangElement(
    std::string type, std::string name, std::string value) {
  elementType = type;
  elementName = name;
  elementValue = value;
  elementVersion = "\0";
  elementAccessPermissions = "\0";
}

// ====================================================================================================
YangElement::YangElement(
    std::string type, std::string name, std::string value, std::string access) {
  elementType = type;
  elementName = name;
  elementValue = value;
  elementVersion = "\0";
  elementAccessPermissions = access;
}

// ====================================================================================================
std::string
YangElement::getType(void) {
  return elementType;
}

// ====================================================================================================
std::string
YangElement::getName(void) {
  return elementName;
}

// ====================================================================================================
std::string
YangElement::getValue(void) {
  return elementValue;
}

// ====================================================================================================
std::string
YangElement::getVersion(void) {
  return elementVersion;
}

// ====================================================================================================
void
YangElement::setVersion(std::string version) {
  elementVersion = version;
}

// ====================================================================================================
std::string
Mplane::YangElement::getAccess(void) {
  return elementAccessPermissions;
}

// ====================================================================================================
std::shared_ptr<IYangElement>
YangElement::getElement(std::string type) {
  std::shared_ptr<IYangElement> elementFound;

  for (auto iter : childElements) {
    std::string itType = iter->getType();

    if (type == itType) {
      elementFound = iter;

      // Exit early
      break;
    }
  }

  return elementFound;
}

// ====================================================================================================
std::shared_ptr<IYangElement>
YangElement::getElement(std::string type, std::string name) {
  std::shared_ptr<IYangElement> elementFound;

  for (auto iter : childElements) {
    std::string itType = iter->getType();
    std::string itName = iter->getName();

    if (type == itType && name == itName) {
      elementFound = iter;

      // Exit early
      break;
    }
  }

  return elementFound;
}

// ====================================================================================================
std::shared_ptr<IYangElement>
YangElement::getElement(std::string type, unsigned int number) {
  std::shared_ptr<IYangElement> elementFound;

  unsigned int iterNum = 0;

  for (auto iter : childElements) {
    std::string itType = iter->getType();

    if (type == itType && iterNum == number) {
      elementFound = iter;

      // Exit early
      break;
    }

    iterNum++;
  }

  return elementFound;
}

// ====================================================================================================
void
YangElement::listElements(std::string& list) {
  for (auto iter : childElements) {
    list += iter->getType() + ",";
  }
}

// ====================================================================================================
void
YangElement::listElements(std::string type, std::string& list) {
  for (auto iter : childElements) {
    std::string itType = iter->getType();
    std::string itName = iter->getName();

    if (type == itType) {
      list += itName + ",";
    }
  }
}

// ====================================================================================================
void
YangElement::addChildElement(std::shared_ptr<IYangElement> elementToAdd) {
  childElements.push_back(elementToAdd);
}

// ====================================================================================================
unsigned int
YangElement::getNumberOfChildElements(void) {
  return (unsigned int)childElements.size();
}

// ====================================================================================================
void
Mplane::YangElement::getChildElements(
    std::vector<std::shared_ptr<IYangElement>>& childElementVector) {
  childElementVector = childElements;
}
