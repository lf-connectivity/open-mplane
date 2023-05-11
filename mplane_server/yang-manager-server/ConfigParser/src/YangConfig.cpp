/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangConfig.cpp
 * \brief     Yang Manger Server configuration access methods and interfaces
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

#include "IYangConfig.h"
#include "IYangElement.h"

#include "YangConfig.h"
#include "YangConfigParser.h"

using namespace Mplane;

// ====================================================================================================
YangConfig::YangConfig()
    : Loggable("YangConfig", "YANG"),
      mIsConfigLoaded(false),
      mYangVersion("/0"),
      mOranVersion("/0"),
      mProductName("/0"),
      mVarientName("/0"),
      mFormatVersion("/0"),
      mCompanyName("/0") {
  // Create an initial element from which we can build the configuration from
  mConfig = IYangElement::makeElement("config");
}

// ====================================================================================================
const std::string YangConfig::pathDelimiterStr = "/";
const std::string YangConfig::listDelimiterStr = "[";
const std::string YangConfig::typeNameDelimiterStr = "-";

const std::string YangConfig::leafStr = "leaf";
const std::string YangConfig::listStr = "list";
const std::string YangConfig::entryStr = "entry";
const std::string YangConfig::moduleStr = "module";
const std::string YangConfig::listLeafStr = "listLeaf";
const std::string YangConfig::listEntryStr = "listEntry";
const std::string YangConfig::featureStr = "feature";

// ====================================================================================================
std::string
Mplane::YangConfig::getAccess(std::string path) {
  std::string value;
  std::string access;

  commonGet(path, value, access);

  return access;
}

// ====================================================================================================
std::string
YangConfig::getValue(std::string path) {
  std::string value;
  std::string access;

  commonGet(path, value, access);

  return value;
}

// ====================================================================================================
void
Mplane::YangConfig::commonGet(
    std::string path, std::string& value, std::string& access) {

  bool searchComplete = false;
  bool searchAbort = false;

  // We need our starting point in the configuration structure
  std::shared_ptr<IYangElement> elementSearch = mConfig;

  // Take a copy of the path to work with
  std::string pathCopy = path;

  do {
    std::size_t pathDelimiterPos = std::string::npos;
    bool foundListDelimiter = false;
    std::string type = "\0";
    std::string indexStr = "\0";

    std::shared_ptr<IYangElement> elementFound;

    commonSearch(
        elementSearch,
        pathCopy,
        foundListDelimiter,
        elementFound,
        type,
        indexStr,
        pathDelimiterPos);

    if (nullptr != elementFound) {
      // Is this the leaf that we are looking for?
      if (type == leafStr) {
        // Return the string value
        value = elementFound->getValue();
        access = elementFound->getAccess();

        searchComplete = true;
      }
      // Is this the list that we are looking for?
      else if (type == listStr) {
        // Now look for the list index
        if (true == foundListDelimiter) {
          // Convert the index string to decimal
          unsigned int index = (unsigned int)std::stoi(indexStr, nullptr, 0);

          // See if we can find it in the element structure at this point
          elementFound = elementFound->getElement(listEntryStr, index);

          if (nullptr == elementFound) {
            // We didn't find it
            searchAbort = true;
          }
        } else {
          // We didn't find it
          searchAbort = true;
        }
      }
      // Is this the listLeaf that we are looking for?
      else if (type == listLeafStr) {
        // Now look for the list index
        if (true == foundListDelimiter) {
          // Convert the index string to decimal
          unsigned int index = (unsigned int)std::stoi(indexStr, nullptr, 0);

          // See if we can find it in the element structure at this point
          elementFound = elementFound->getElement(entryStr, index);

          if (nullptr == elementFound) {
            // We didn't find it
            searchAbort = true;
          } else {
            // List leafs are a bit different. They have no leaf but have a
            // entry with a value
            searchComplete = true;

            // Return the string value
            value = elementFound->getValue();
            access = elementFound->getAccess();
          }
        } else {
          // We didn't find it
          searchAbort = true;
        }
      }
      // Is this the feature that we are looking for?
      else if (type == featureStr) {
        // Return the string value
        value = elementFound->getValue();

        searchComplete = true;
      }

      if ((false == searchComplete) && (false == searchAbort)) {
        // Found this part move on
        elementSearch = elementFound;

        pathCopy.erase(0, pathDelimiterPos + 1);

        logDebugNormal("New path - " + pathCopy);
      }
    } else {
      // Cannot find the element
      searchAbort = true;
    }

  } while (false == searchComplete && false == searchAbort);
}

// ====================================================================================================
bool
YangConfig::isModuleSupported(std::string module) {
  std::shared_ptr<IYangElement> found = mConfig->getElement(moduleStr, module);

  if (nullptr != found) {
    return true;
  } else {
    return false;
  }
}

// ====================================================================================================
void
YangConfig::listSupportedModules(std::string& moduleList) {
  mConfig->listElements(moduleStr, moduleList);
}

// ====================================================================================================
void
YangConfig::listModuleFeatures(
    std::string module, std::map<std::string, bool>& featureList) {
  std::shared_ptr<IYangElement> moduleElement =
      mConfig->getElement(moduleStr, module);

  // Check if module is supported
  if (nullptr != moduleElement) {
    // Get list of features for the module
    std::vector<std::shared_ptr<IYangElement>> moduleChildren;
    moduleElement->getChildElements(moduleChildren);

    for (auto& elem : moduleChildren) {
      // Check if feature belongs to the module
      if (elem->getType() == featureStr) {
        featureList[elem->getName()] =
            (elem->getValue() == "true" ? true : false);
      }
    }
  }
}

// ====================================================================================================
void
YangConfig::listModuleFeatures(std::string module, std::string& featureList) {
  std::shared_ptr<IYangElement> moduleElement =
      mConfig->getElement(moduleStr, module);

  // Check if module is supported
  if (nullptr != moduleElement) {
    // Get list of features for the module
    std::vector<std::shared_ptr<IYangElement>> moduleChildren;
    moduleElement->getChildElements(moduleChildren);

    for (auto& elem : moduleChildren) {
      // Check if feature belongs to the module
      if (elem->getType() == featureStr) {
        featureList += elem->getName() + "=" + elem->getValue() + ",";
      }
    }
  }
}

// ====================================================================================================
bool
YangConfig::isModuleFeatureEnabled(std::string module, std::string feature) {
  bool featureEnabled = false;
  std::map<std::string, bool> featureList;

  listModuleFeatures(module, featureList);
  if (featureList.find(feature) != featureList.end()) {
    featureEnabled = featureList[feature];
  }

  return featureEnabled;
}

// ====================================================================================================
std::shared_ptr<IYangElement>
YangConfig::getConfigFile(void) {
  return mConfig;
}

// ====================================================================================================
std::string
Mplane::YangConfig::getModuleVersion(std::string module) {
  std::shared_ptr<IYangElement> found = mConfig->getElement(moduleStr, module);

  if (nullptr != found) {
    return found->getVersion();
  } else {
    return "\0";
  }
}

// ====================================================================================================
const std::string Mplane::YangConfig::caseStr = "case";
const std::string Mplane::YangConfig::choiceStr = "choice";

std::string
Mplane::YangConfig::getChoiceCaseName(std::string path) {
  bool searchComplete = false;
  bool searchAbort = false;

  std::string returnValue = "\0";

  // We need our starting point in the configuration structure
  std::shared_ptr<IYangElement> elementSearch = mConfig;

  // Take a copy of the path to work with
  std::string pathCopy = path;

  do {
    std::size_t pathDelimiterPos = std::string::npos;
    bool foundListDelimiter = false;
    std::string type = "\0";
    std::string indexStr = "\0";

    std::shared_ptr<IYangElement> elementFound;

    commonSearch(
        elementSearch,
        pathCopy,
        foundListDelimiter,
        elementFound,
        type,
        indexStr,
        pathDelimiterPos);

    if (nullptr != elementFound) {
      // Is this the choice that we are looking for?
      if (type == choiceStr) {
        searchComplete = true;

        // See if we can find it in the element structure at this point
        elementFound = elementFound->getElement(caseStr);

        if (nullptr == elementFound) {
          // We didn't find it
          searchAbort = true;
        } else {
          returnValue = elementFound->getName();
        }
      }
      // This might not be the string we are looking for but lists are
      // everywhere and we need to deal with them!
      else if (type == listStr) {
        // Now look for the list index
        if (true == foundListDelimiter) {
          // Convert the index string to decimal
          unsigned int index = (unsigned int)std::stoi(indexStr, nullptr, 0);

          // See if we can find it in the element structure at this point
          elementFound = elementFound->getElement(listEntryStr, index);

          if (nullptr == elementFound) {
            // We didn't find it
            searchAbort = true;
          }
        } else {
          // We didn't find it
          searchAbort = true;
        }
      }

      if ((false == searchComplete) && (false == searchAbort)) {
        // Found this part move on
        elementSearch = elementFound;

        pathCopy.erase(0, pathDelimiterPos + 1);

        logDebugNormal("New path - " + pathCopy);
      }
    } else {
      // Cannot find the element
      searchAbort = true;
    }

  } while (false == searchComplete && false == searchAbort);

  return returnValue;
}

// ====================================================================================================
unsigned int
Mplane::YangConfig::getNumOfListEntries(std::string path) {
  return commonGetNumEntries(path, listStr);
}

// ====================================================================================================
unsigned int
Mplane::YangConfig::getNumOfListLeafEntries(std::string path) {
  return commonGetNumEntries(path, listLeafStr);
}

// ====================================================================================================
void
YangConfig::commonSearch(
    std::shared_ptr<IYangElement> elementSearch,
    std::string& path,
    bool& foundListDelimiter,
    std::shared_ptr<IYangElement>& elementFound,
    std::string& type,
    std::string& index,
    std::size_t& pathDelimiterPos) {
  pathDelimiterPos = path.find(pathDelimiterStr);

  if (0 != pathDelimiterPos) {
    // Is there a type and name?
    std::size_t typeDelimiterPos = path.find(typeNameDelimiterStr);

    if (0 != typeDelimiterPos) {
      // We have a type and name in the path. Extract what those are
      type = path.substr(0, typeDelimiterPos);
      std::string name = path.substr(
          typeDelimiterPos + 1, (pathDelimiterPos - typeDelimiterPos) - 1);

      std::size_t listDelimiterPos = name.find(listDelimiterStr);
      std::size_t listSize = 0;

      if ((0 != listDelimiterPos) && (std::string::npos != listDelimiterPos)) {
        // How big is it?
        listSize = name.size() - listDelimiterPos;

        // Whilst we are here we might as well grab its value
        index = name.substr(((name.size() - listSize) + 1), (listSize - 2));

        // Remove it from the name
        name.erase((name.size() - listSize), listSize);

        foundListDelimiter = true;
      }

      // See if we can find it in the element structure at this point
      elementFound = elementSearch->getElement(type, name);
    }
  }
}

// ====================================================================================================
bool
Mplane::YangConfig::getConfigLoaded(void) {
  return mIsConfigLoaded;
}

// ====================================================================================================
void
Mplane::YangConfig::setConfigLoaded(bool configLoaded) {
  mIsConfigLoaded = configLoaded;
}

// ====================================================================================================
void
Mplane::YangConfig::listConfigTree(std::string& configTree) {
  // We need our starting point in the configuration structure
  std::shared_ptr<IYangElement> treeSearch = mConfig;

  // Call the recursive search to expose the tree
  recursiveElementSearch(treeSearch, configTree, 0);
}

// ====================================================================================================
void
Mplane::YangConfig::recursiveElementSearch(
    std::shared_ptr<IYangElement> parentElement,
    std::string& resultString,
    unsigned int indent) {
  std::string elementType;

  std::vector<std::shared_ptr<IYangElement>> childElementVector;
  parentElement->getChildElements(childElementVector);

  for (std::vector<std::shared_ptr<IYangElement>>::iterator iter =
           childElementVector.begin();
       iter != childElementVector.end();
       iter++) {
    std::shared_ptr<IYangElement> element = *iter;

    elementType = element->getType();

    // If this is a module then reset the indentation
    if (moduleStr == elementType) {
      indent = 0;
    } else {
      // Put in some indentation to make it look pretty!
      for (unsigned int indentLoop = 0; indentLoop <= indent; ++indentLoop) {
        resultString += " ";
      }
    }

    // Append the data on to the string
    resultString += elementType + " " + element->getName() + " " +
                    element->getValue() + " " + element->getVersion() + "\n";

    // Increase the indentation if this is not a leaf, a module or a list leaf
    // entry.
    if ((leafStr != elementType) && (moduleStr != elementType) &&
        (entryStr != elementType)) {
      indent++;
    }

    // Call ourselves again to progress through the tree
    recursiveElementSearch(*iter, resultString, indent);

    // For list leaf we have to handle it correctly, otherwise subsequent
    // elements at that level are incorrectly indented.
    if (listLeafStr == elementType) {
      indent--;
    }
  }

  indent--;
}

// ====================================================================================================
unsigned int
Mplane::YangConfig::commonGetNumEntries(
    std::string path, std::string elementType) {
  bool searchAbort = false;

  unsigned int returnValue = 0x0;

  // We need our starting point in the configuration structure
  std::shared_ptr<IYangElement> elementSearch = mConfig;

  // Take a copy of the path to work with
  std::string pathCopy = path;

  do {
    std::size_t pathDelimiterPos = std::string::npos;
    bool foundListDelimiter = false;
    std::string type = "\0";
    std::string indexStr = "\0";

    std::shared_ptr<IYangElement> elementFound;

    commonSearch(
        elementSearch,
        pathCopy,
        foundListDelimiter,
        elementFound,
        type,
        indexStr,
        pathDelimiterPos);

    if (nullptr != elementFound) {
      // This is a list, but might not the list that we are looking for, save
      // it as return value until a deeper list is found
      if (type == elementType) {
        returnValue = elementFound->getNumberOfChildElements();
      }
      // This might not be the string we are looking for but lists are
      // everywhere and we need to deal with them!
      if (type == listStr) {
        // Now look for the list index
        if (true == foundListDelimiter) {
          // Convert the index string to decimal
          unsigned int index = (unsigned int)std::stoi(indexStr, nullptr, 0);

          // See if we can find it in the element structure at this point
          elementFound = elementFound->getElement(listEntryStr, index);

          if (nullptr == elementFound) {
            // We didn't find the element we were looking for (done searching
            // for deeper lists)
            searchAbort = true;
          }
        }
      }
      elementSearch = elementFound;

      pathCopy.erase(0, pathDelimiterPos + 1);

      logDebugNormal("New path - " + pathCopy);
    } else {
      // Cannot find the element (or done searching)
      searchAbort = true;
    }

  } while (false == searchAbort);

  return returnValue;
}

// ====================================================================================================
void
Mplane::YangConfig::setYangVersion(std::string yangVersion) {
  mYangVersion = yangVersion;
}

// ====================================================================================================
void
Mplane::YangConfig::setOranVersion(std::string oranVersion) {
  mOranVersion = oranVersion;
}

// ====================================================================================================
void
Mplane::YangConfig::setProduct(std::string productName) {
  mProductName = productName;
}

// ====================================================================================================
void
Mplane::YangConfig::setVariant(std::string productVariant) {
  mVarientName = productVariant;
}

// ====================================================================================================
void
Mplane::YangConfig::setFormatVersion(std::string formatVersion) {
  mFormatVersion = formatVersion;
}

// ====================================================================================================
void
Mplane::YangConfig::setCompanyName(std::string companyName) {
  mCompanyName = companyName;
}

// ====================================================================================================
std::string
Mplane::YangConfig::getYangVersion(void) {
  return mYangVersion;
}

// ====================================================================================================
std::string
Mplane::YangConfig::getOranVersion(void) {
  return mOranVersion;
}

// ====================================================================================================
std::string
Mplane::YangConfig::getProduct(void) {
  return mProductName;
}

// ====================================================================================================
std::string
Mplane::YangConfig::getVariant(void) {
  return mVarientName;
}

// ====================================================================================================
std::string
Mplane::YangConfig::getFormatVersion(void) {
  return mFormatVersion;
}

// ====================================================================================================
std::string
Mplane::YangConfig::getCompanyName(void) {
  return mCompanyName;
}
