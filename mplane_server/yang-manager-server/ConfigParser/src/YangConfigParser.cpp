/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangConfigParser.cpp
 * \brief     Yang Manger Server configuration file parser
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "YangConfigParser.h"
#include "IConfigDownloadManagement.h"

using namespace Mplane;

// ====================================================================================================
YangConfigParser::YangConfigParser()
    : CommonConfigBase("YangConfigParser", "YANG") {
  mConfigFileLoaded = false;
}

// ====================================================================================================
YangConfigParser::~YangConfigParser() {}

// ====================================================================================================
ReturnType::State
YangConfigParser::load(void) {
  ReturnType::State status = ReturnType::RT_OK;

  mConfigFileLoaded = false;

  // Get the config file path
  std::string filePath = getPath();

  if (filePath == "") {
    eventError("File path not set");
    return ReturnType::RT_NOT_INITIALISED;
  }

  eventInfo("Load file %s", filePath.c_str());

  // Parse the final expanded file
  tinyxml2::XMLDocument doc;
  if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_NO_ERROR) {
    eventError("Could not parse file %s", filePath.c_str());
    return ReturnType::RT_NOT_FOUND;
  }

  tinyxml2::XMLElement* root_element = doc.RootElement();
  if (root_element == NULL) {
    eventError("Invalid xml format in file %s ", filePath.c_str());
    return ReturnType::RT_NOT_FOUND;
  }

  if (!parseConfig(root_element)) {
    eventError("Syntax error in cal file %s ", filePath.c_str());
    return ReturnType::RT_SYNTAX_ERROR;
  }

  // If we got this far then the file has loaded with no problems.
  mConfigFileLoaded = true;

  mConfig->setConfigLoaded(true);

  eventInfo("Load file %s successful", filePath.c_str());

  return status;
}

// ====================================================================================================
bool
YangConfigParser::isConfigFileLoaded(void) {
  return mConfigFileLoaded;
}

const std::string _mXmlElementDelimiterStr = "-";
const std::string YangConfigParser::mXmlElementDelimiterStr = _mXmlElementDelimiterStr;
const std::string YangConfigParser::mXmlModuleFeatureDelimiterStr = ".";
const std::string YangConfigParser::mXmlValueStr = "value";
const std::string YangConfigParser::mXmlAccessStr = "access";
const std::string YangConfigParser::mXmlRefStr = "ref";

// ====================================================================================================
const std::string YangConfigParser::mXmlModuleStr = "module";
const std::string YangConfigParser::mXmlFileVersionStr = "file-version";
const std::string YangConfigParser::mXmlFeatureStr = "feature";
const std::string YangConfigParser::mXmlIfFeatureStr = "if_feature";

bool
Mplane::YangConfigParser::extractModule(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  bool returnValue = true;

  std::string moduleName;

  do {
    bool findResult = findElementNoAttributes(node, mXmlModuleStr, moduleName);

    if (true == findResult) {
      logDebugNormal(mXmlModuleStr + " - " + moduleName);

      std::shared_ptr<IYangElement> module =
          parentElement->makeElement(mXmlModuleStr, moduleName);
      parentElement->addChildElement(module);

      tinyxml2::XMLElement* childElementNode = node->FirstChildElement();

      // Make sure this is not a nullptr, some modules have no child elements.
      if (nullptr != childElementNode) {
        returnValue = findElementAndExtract(childElementNode, module, module);
      }
    }

    // Now we are done move on to the next sibling
    node = node->NextSiblingElement();
  } while (nullptr != node);

  return returnValue;
}

// ====================================================================================================
void
YangConfigParser::extractAllFeatures(tinyxml2::XMLElement* node) {
  std::string moduleName;

  do {
    bool findResult = findElementNoAttributes(node, mXmlModuleStr, moduleName);

    if (true == findResult) {
      tinyxml2::XMLElement* childElementNode = node->FirstChildElement();

      // Make sure this is not a nullptr, some modules have no child elements.
      if (nullptr != childElementNode) {
        do {
          // Get the element type from the node
          std::string elementType("");
          std::string elementName("");
          std::string elementAttrValue("");
          getElementType(childElementNode->Name(), elementType);

          // If the child node is a feature, then add it into the feature map
          if (elementType == mXmlFeatureStr) {
            // Get the feature name and attribute
            if (findElementWithAttributes(
                    childElementNode,
                    mXmlFeatureStr,
                    elementName,
                    elementAttrValue)) {
              logDebugNormal(
                  mXmlModuleStr + " - " + moduleName + " , " + mXmlFeatureStr +
                  " - " + elementName + " = " + elementAttrValue);

              mModuleFeatureMap[moduleName][elementName] =
                  (elementAttrValue == "true" ? true : false);
            }
          }
          // Move to the next sibling
          childElementNode = childElementNode->NextSiblingElement();

        } while (nullptr != childElementNode);
      }
    }

    // Now we are done move on to the next sibling
    node = node->NextSiblingElement();
  } while (nullptr != node);
}

// ====================================================================================================
const std::string YangConfigParser::mXmlRootStr = "root";
const std::string YangConfigParser::mXmlYangVersionStr = "yang-version";
const std::string YangConfigParser::mXmlGeneralStr = "General";
const std::string YangConfigParser::mXmlOranVersionStr = "oranVersion";
const std::string YangConfigParser::mXmlProductStr = "product";
const std::string YangConfigParser::mXmlVarientStr = "variant";
const std::string YangConfigParser::mXmlFormatVersionStr = "formatVersion";
const std::string YangConfigParser::mXmlCompanyStr = "company";

bool
YangConfigParser::parseConfig(tinyxml2::XMLElement* node) {
  bool returnValue = true;

  mConfig = IYangConfig::getConfigSingleton();
  mFile = mConfig->getConfigFile();

  // The first node that we are looking at is the yangConfig
  if (mXmlRootStr == node->Name()) {
    // Move to the first child - general
    node = node->FirstChildElement();

    if (mXmlGeneralStr == node->Name()) {
      tinyxml2::XMLElement* generalNode = node;

      // Extract the Oran Information attributes
      generalNode = generalNode->FirstChildElement();

      {
        std::map<std::string, std::string> attributes;
        attributes[mXmlOranVersionStr] = "";
        attributes[mXmlProductStr] = "";
        attributes[mXmlVarientStr] = "";

        for (auto& entry : attributes) {
          const char* attr(generalNode->Attribute(entry.first.c_str()));

          if (attr) {
            entry.second = std::string(attr);
          }
        }

        mOranVersion = attributes[mXmlOranVersionStr];
        mProduct = attributes[mXmlProductStr];
        mVarient = attributes[mXmlVarientStr];

        logDebugNormal("Oran Version   : " + mOranVersion);
        logDebugNormal("Product        : " + mProduct);
        logDebugNormal("Variant        : " + mVarient);

        mConfig->setOranVersion(mOranVersion);
        mConfig->setProduct(mProduct);
        mConfig->setVariant(mVarient);
      }

      // Extract the Product Information Attributes
      generalNode = generalNode->NextSiblingElement();

      {
        std::map<std::string, std::string> attributes;
        attributes[mXmlFormatVersionStr] = "";
        attributes[mXmlCompanyStr] = "";

        for (auto& entry : attributes) {
          const char* attr(generalNode->Attribute(entry.first.c_str()));

          if (attr) {
            entry.second = std::string(attr);
          }
        }

        mFormatVersion = attributes[mXmlFormatVersionStr];
        mCompany = attributes[mXmlCompanyStr];

        logDebugNormal("Format Version :" + mFormatVersion);
        logDebugNormal("Company        :" + mCompany);

        mConfig->setFormatVersion(mFormatVersion);
        mConfig->setCompanyName(mCompany);
      }
    }

    // Move to the version information
    node = node->NextSiblingElement();

    if (mXmlYangVersionStr == node->Name()) {
      mYangVersion = node->Attribute(mXmlValueStr.c_str());

      logDebugNormal("YANG Version       :" + mYangVersion);

      mConfig->setYangVersion(mYangVersion);
    }

    // Move on to the first modules
    node = node->NextSiblingElement();

    // Extract all features before parsing the entire file
    extractAllFeatures(node);

    // Extract the module information
    returnValue = extractModule(node, mFile);
  } else {
    returnValue = false;
  }
  return returnValue;
}

// ====================================================================================================
void
Mplane::YangConfigParser::getYangVersion(std::string& yangVersion) {
  yangVersion = mYangVersion;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::findElementNoAttributes(
    tinyxml2::XMLElement* node,
    std::string elementTypeToFind,
    std::string& elementName) {
  unsigned int elementSize = elementTypeToFind.size();

  std::string moduleName(node->Name());

  std::size_t delimiterPos = moduleName.find(mXmlElementDelimiterStr);

  if (elementSize == delimiterPos) {
    std::string type = moduleName.substr(0, delimiterPos);
    std::string name =
        moduleName.substr(delimiterPos + 1, (moduleName.size() - delimiterPos));

    if (type == elementTypeToFind) {
      elementName = name;
      return true;
    }
  }

  return false;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::findElementWithAttributes(
    tinyxml2::XMLElement* node,
    std::string elementTypeToFind,
    std::string& elementName,
    std::string& elementValue) {
  unsigned int elementSize = elementTypeToFind.size();

  std::string moduleName(node->Name());

  std::size_t delimiterPos = moduleName.find(mXmlElementDelimiterStr);

  if (elementSize == delimiterPos) {
    std::string type = moduleName.substr(0, delimiterPos);
    std::string name =
        moduleName.substr(delimiterPos + 1, (moduleName.size() - delimiterPos));

    if (type == elementTypeToFind) {
      elementName = name;
      elementValue = node->Attribute(mXmlValueStr.c_str());

      return true;
    }
  }

  return false;
}

// ====================================================================================================
const std::string YangConfigParser::mXmlContainerStr = "container";
const std::string YangConfigParser::mXmlSubContainerStr = "container";
const std::string YangConfigParser::mXmlListStr = "list";
const std::string YangConfigParser::mXmlChoiceStr = "choice";
const std::string YangConfigParser::mXmlListEntryStr = "listEntry";
const std::string YangConfigParser::mXmlLeafStr = "leaf";
const std::string YangConfigParser::mXmlListLeafStr = "listLeaf";
const std::string YangConfigParser::mXmlEntryStr = "entry";
const std::string YangConfigParser::mXmlCaseStr = "case";

bool
Mplane::YangConfigParser::findElementAndExtract(
    tinyxml2::XMLElement* node,
    std::shared_ptr<IYangElement> parentElement,
    std::shared_ptr<IYangElement> moduleElement) {
  bool returnValue = true;

  do {
    returnValue =
        callExtractMethod(node->Name(), node, parentElement, moduleElement);

    // Move to the next sibling
    node = node->NextSiblingElement();

  } while (nullptr != node);

  return returnValue;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::callExtractMethod(
    const std::string nodeName,
    tinyxml2::XMLElement* node,
    std::shared_ptr<IYangElement> parentElement,
    std::shared_ptr<IYangElement> moduleElement) {
  bool returnValue = true;

  // If the child element is the file version, then set the file version for the
  // module
  if (mXmlFileVersionStr == nodeName) {
    std::string fileVersion = node->Attribute(mXmlValueStr.c_str());

    logDebugNormal(mXmlFileVersionStr + " - " + fileVersion);

    moduleElement->setVersion(fileVersion);
  } else {
    // Get the element type from the node
    std::string elementType;
    returnValue = getElementType(nodeName, elementType);

    ExtractElements element(mModuleFeatureMap);

    // Call the handler for this type
    element.call(elementType, node, parentElement);
  }

  return returnValue;
}

// ====================================================================================================
void
Mplane::YangConfigParser::getOranVersion(std::string& oranVersion) {
  oranVersion = mOranVersion;
}

// ====================================================================================================
void
Mplane::YangConfigParser::getProduct(std::string& product) {
  product = mProduct;
}

// ====================================================================================================
void
Mplane::YangConfigParser::getVarient(std::string& variant) {
  variant = mVarient;
}

// ====================================================================================================
void
Mplane::YangConfigParser::getFormatVersion(std::string& formatVersion) {
  formatVersion = mFormatVersion;
}

// ====================================================================================================
void
Mplane::YangConfigParser::getCompany(std::string& company) {
  company = mCompany;
}

//=====================================================================================================
bool 
_getElementType(std::string nodeName, std::string& elementType)
{
   std::size_t delimiterPos = nodeName.find(_mXmlElementDelimiterStr);

  if (0 != delimiterPos) {
    std::string type = nodeName.substr(0, delimiterPos);

    elementType = type;
    return true;
  }

  return false;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::getElementType(
    std::string nodeName, std::string& elementType) {
      
      return _getElementType(nodeName, elementType);
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::getElementType(
    std::string nodeName, std::string& elementType) {

  return _getElementType(nodeName, elementType);
}

// ====================================================================================================
Mplane::YangConfigParser::ExtractElements::ExtractElements(
    std::map<std::string, std::map<std::string, bool>> featureMap)
    : Loggable("ExtractElements", "YANG") {
  extractMethodMap.insert(std::make_pair(
      mXmlSubContainerStr.c_str(), &ExtractElements::extractSubContainer));
  extractMethodMap.insert(
      std::make_pair(mXmlListStr.c_str(), &ExtractElements::extractList));
  extractMethodMap.insert(
      std::make_pair(mXmlChoiceStr.c_str(), &ExtractElements::extractChoice));
  extractMethodMap.insert(std::make_pair(
      mXmlListEntryStr.c_str(), &ExtractElements::extractListEntry));
  extractMethodMap.insert(
      std::make_pair(mXmlLeafStr.c_str(), &ExtractElements::extractLeaf));
  extractMethodMap.insert(std::make_pair(
      mXmlListLeafStr.c_str(), &ExtractElements::extractListLeaf));
  extractMethodMap.insert(
      std::make_pair(mXmlEntryStr.c_str(), &ExtractElements::extractEntry));
  extractMethodMap.insert(
      std::make_pair(mXmlCaseStr.c_str(), &ExtractElements::extractCase));
  extractMethodMap.insert(
      std::make_pair(mXmlFeatureStr.c_str(), &ExtractElements::extractFeature));
  extractMethodMap.insert(std::make_pair(
      mXmlIfFeatureStr.c_str(), &ExtractElements::extractIfFeature));

  mFeatureMap = featureMap;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::getElementName(
    std::string nodeName, std::string& elementName) {
  std::size_t delimiterPos = nodeName.find(mXmlElementDelimiterStr);

  if (0 != delimiterPos) {
    std::string name =
        nodeName.substr(delimiterPos + 1, (nodeName.size() - delimiterPos));

    elementName = name;
    return true;
  }

  return false;
}

// ====================================================================================================
bool
YangConfigParser::ExtractElements::isFeatureEnabled(
    std::string moduleName, std::string featureName) {
  // Check if the feature is listed for the module and is enabled
  bool featureEnabled = false;

  // Check if the module is present in the feature map
  if (mFeatureMap.find(moduleName) != mFeatureMap.end()) {
    // Check if the feature is present for the given module
    if (mFeatureMap[moduleName].find(featureName) !=
        mFeatureMap[moduleName].end()) {
      // Return the feature status
      featureEnabled = mFeatureMap[moduleName][featureName];
    }
  }

  return featureEnabled;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractSubContainer(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;

  // Extract the list name
  getElementName(node->Name(), elementName);

  std::shared_ptr<IYangElement> subContainer =
      parentElement->makeElement(mXmlSubContainerStr, elementName);
  parentElement->addChildElement(subContainer);

  if (parentElement->getType() == mXmlModuleStr) {
    logDebugNormal("Container - " + elementName);
  } else {
    logDebugNormal("SubContainer - " + elementName);
  }

  // Advance to the first child and see what we have
  node = node->FirstChildElement();

  // Call the common extract method
  return extractCommon(node, subContainer);
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractList(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;

  // Extract the list name
  getElementName(node->Name(), elementName);

  std::shared_ptr<IYangElement> list =
      parentElement->makeElement(mXmlListStr, elementName);
  parentElement->addChildElement(list);

  logDebugNormal("List - " + elementName);

  // Advance to the first child and see what we have
  node = node->FirstChildElement();

  // Call the common extract method
  return extractCommon(node, list);
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractChoice(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;

  // Extract the list name
  getElementName(node->Name(), elementName);

  std::shared_ptr<IYangElement> choice =
      parentElement->makeElement(mXmlChoiceStr, elementName);
  parentElement->addChildElement(choice);

  logDebugNormal("Choice - " + elementName);

  // Advance to the first child and see what we have
  node = node->FirstChildElement();

  // Call the common extract method
  return extractCommon(node, choice);
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractListEntry(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;

  // Extract the list name
  getElementName(node->Name(), elementName);

  std::shared_ptr<IYangElement> listEntry =
      parentElement->makeElement(mXmlListEntryStr);
  parentElement->addChildElement(listEntry);

  logDebugNormal(mXmlListEntryStr);

  // Advance to the first child and see what we have
  node = node->FirstChildElement();

  // Call the common extract method
  return extractCommon(node, listEntry);
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractLeaf(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;

  // Extract the leaf name
  getElementName(node->Name(), elementName);

  // Do we have a value attribute?
  if (nullptr != node->Attribute(mXmlValueStr.c_str())) {
    std::string elementAttrValue;
    const char* accessOrNull;
    std::string elementAttrAccess;

    elementAttrValue = node->Attribute(mXmlValueStr.c_str());
    accessOrNull = node->Attribute(mXmlAccessStr.c_str());
    if (accessOrNull != nullptr) {
      elementAttrAccess = accessOrNull;
    }

    std::shared_ptr<IYangElement> leaf = parentElement->makeElement(
        mXmlLeafStr, elementName, elementAttrValue, elementAttrAccess);
    parentElement->addChildElement(leaf);

    logDebugNormal(
        mXmlLeafStr + " - " + elementName + " ; value = " + elementAttrValue +
        " ; access = " + elementAttrAccess);
  }
  // Or do we have a ref attribute
  else if (nullptr != node->Attribute(mXmlRefStr.c_str())) {
    std::string elementAttrRef;

    elementAttrRef = node->Attribute(mXmlRefStr.c_str());

    std::shared_ptr<IYangElement> leaf =
        parentElement->makeElement(mXmlLeafStr, elementName, elementAttrRef);
    parentElement->addChildElement(leaf);

    logDebugNormal(
        mXmlLeafStr + " - " + elementName + " ; ref = " + elementAttrRef);
  } else {
    eventError(
        "Mplane::YangConfigParser::ExtractElements::extractLeaf() - neither "
        "value or ref found!");
  }

  return true;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractListLeaf(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;

  // Extract the list name
  getElementName(node->Name(), elementName);

  std::shared_ptr<IYangElement> listLeaf =
      parentElement->makeElement(mXmlListLeafStr, elementName);
  parentElement->addChildElement(listLeaf);

  logDebugNormal(mXmlListLeafStr + " - " + elementName);

  // Advance to the first child and see what we have
  node = node->FirstChildElement();

  // Call the common extract method
  return extractCommon(node, listLeaf);
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractCase(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;

  // Extract the list name
  getElementName(node->Name(), elementName);

  std::shared_ptr<IYangElement> caseElement =
      parentElement->makeElement(mXmlCaseStr, elementName);
  parentElement->addChildElement(caseElement);

  logDebugNormal(mXmlCaseStr + " - " + elementName);

  // Advance to the first child and see what we have
  node = node->FirstChildElement();

  // The case may not have a leaf etc
  if (nullptr != node) {
    // Call the common extract method
    return extractCommon(node, caseElement);
  }

  return true;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractEntry(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;
  std::string elementAttrValue;

  // Extract the leaf name
  getElementName(node->Name(), elementName);

  // For the moment we as expecting there to be an attribute called value
  elementAttrValue = node->Attribute(mXmlValueStr.c_str());

  std::shared_ptr<IYangElement> entry =
      parentElement->makeElement(mXmlEntryStr, elementName, elementAttrValue);
  parentElement->addChildElement(entry);

  logDebugNormal(
      mXmlEntryStr + " - " + elementName + " ; value = " + elementAttrValue);

  return true;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractFeature(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;
  std::string elementAttrValue;

  // Extract the feature name
  getElementName(node->Name(), elementName);

  // For the moment we as expecting there to be an attribute called value
  elementAttrValue = node->Attribute(mXmlValueStr.c_str());

  std::shared_ptr<IYangElement> entry =
      parentElement->makeElement(mXmlFeatureStr, elementName, elementAttrValue);
  parentElement->addChildElement(entry);

  logDebugNormal(
      mXmlFeatureStr + " - " + elementName + " ; value = " + elementAttrValue);

  return true;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractIfFeature(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  std::string elementName;
  std::string elementAttrValue;

  // Extract the feature name
  getElementName(node->Name(), elementName);

  // Remove the unique number appended to the feature name in the if_feature
  // node string
  std::size_t pos = elementName.find_last_of(mXmlElementDelimiterStr);
  if (pos != 0 && pos != std::string::npos) {
    elementName = elementName.substr(0, pos);
  }

  logDebugNormal(mXmlIfFeatureStr + " - " + elementName);

  // Parse the module name and the feature name from the if-feature statement
  pos = elementName.find(mXmlModuleFeatureDelimiterStr);
  if (pos != std::string::npos) {
    std::string moduleName = elementName.substr(0, pos);
    std::string featureName = elementName.substr(pos + 1);

    logDebugNormal(
        mXmlIfFeatureStr + " : Module = " + moduleName +
        ", Feature = " + featureName);

    // Process the children of the if-feature block only if the feature is
    // enabled
    if (isFeatureEnabled(moduleName, featureName)) {
      // Advance to the first child and see what we have
      node = node->FirstChildElement();

      // Call the common extract method
      return extractCommon(node, parentElement);
    }
  }
  return true;
}

// ====================================================================================================
bool
Mplane::YangConfigParser::ExtractElements::extractCommon(
    tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement) {
  bool returnValue = false;

  do {
    // Get the element type and call the handler
    std::string elementType;
    returnValue = getElementType(node->Name(), elementType);

    ExtractElements element(mFeatureMap);

    // Call the handler for this element type
    returnValue = element.call(elementType, node, parentElement);

    // Move to the next sibling if there is one
    node = node->NextSiblingElement();

  } while (nullptr != node);

  return returnValue;
}
