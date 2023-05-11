/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModule.cpp
 * \brief     YANG Module classes
 *
 *
 * \details   YANG module classes, providing methods to describe YANG modules.
 *
 */

// *****************************************************************************
// Includes
// *****************************************************************************
#include <iostream>

#include "YangModule.h"

using namespace Mplane;

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// YANG Item Classes
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        YangItem
// Description:  YANG item factory base class.
// -----------------------------------------------------------------------------
YangItem::YangItem()
    : mName("Empty"), mId(ITEM_NULL), mType(YangItemType_E::EMPTY) {}

YangItem::YangItem(YangItem& item)
    : mName(item.mName), mId(item.mId), mType(item.mType) {}

YangItem::YangItem(
    std::string name, uint32_t id, IYangItem::YangItemType_E type)
    : mName(name), mId(id), mType(type) {}

YangItem::~YangItem() {}

uint32_t
YangItem::getId(void) const {
  return mId;
}

IYangItem::YangItemType_E
YangItem::getType(void) const {
  return mType;
}

std::string
YangItem::getName(void) const {
  return mName;
}

void
YangItem::dump(unsigned level) const {
  std::string indent(level * 4, ' ');
  std::cout << indent << typeStr(mType) << " " << mName << " [" << mId << "]"
            << std::endl;
}

std::string
YangItem::typeStr(IYangItem::YangItemType_E type) {
  switch (type) {
    case YangItemType_E::UNKNOWN:
      return "UNKNOWN";
    case YangItemType_E::LEAF:
      return "LEAF";
    case YangItemType_E::REFERENCE:
      return "REFERENCE";
    case YangItemType_E::GROUP:
      return "GROUP";
    case YangItemType_E::LIST:
      return "LIST";
    case YangItemType_E::CHOICE:
      return "CHOICE";
    case YangItemType_E::CHOICE_OPTION:
      return "CHOICE_OPTION";
    case YangItemType_E::NOTIFICATION:
      return "NOTIFICATION";
    case YangItemType_E::CONTAINER:
      return "CONTAINER";
    case YangItemType_E::MODULE:
      return "MODULE";
    case YangItemType_E::EMPTY:
      return "EMPTY";
    default:
      break;
  }
  return "<<INVALID>>";
}

// make: LEAF
// SR_BINARY_E, SR_BITS_E, SR_ENUM_E, SR_IDENTITYREF_E,
// SR_INSTANCEID_E, SR_STRING_E, SR_BOOL_E, SR_DECIMAL64_E,
// SR_INT8_E, SR_INT16_E, SR_INT32_E, SR_INT64_E,
// SR_UINT8_E, SR_UINT16_E, SR_UINT32_E, SR_UINT64_E,
std::shared_ptr<YangLeaf>
YangItem::makeLeaf(YangLeaf& leaf) const {
  std::shared_ptr<YangLeaf> item = std::make_shared<YangLeaf>(leaf);
  return item;
}

// make: REFERENCE
std::shared_ptr<YangReference>
YangItem::makeReference(YangReference& reference) const {
  std::shared_ptr<YangReference> item =
      std::make_shared<YangReference>(reference);
  return item;
}

// make: CONTAINER
std::shared_ptr<YangContainer>
YangItem::makeContainer(YangContainer& container) const {
  std::shared_ptr<YangContainer> item =
      std::make_shared<YangContainer>(container);
  return item;
}

// make: GROUPING
std::shared_ptr<YangGroup>
YangItem::makeGroup(YangGroup& group) const {
  std::shared_ptr<YangGroup> item = std::make_shared<YangGroup>(group);
  return item;
}

// make: LIST
std::shared_ptr<YangList>
YangItem::makeList(YangList& list) const {
  std::shared_ptr<YangList> item = std::make_shared<YangList>(list);
  return item;
}

// make: CHOICE
std::shared_ptr<YangChoice>
YangItem::makeChoice(YangChoice& choice) const {
  std::shared_ptr<YangChoice> item = std::make_shared<YangChoice>(choice);
  return item;
}

// make: NOTIFICATION
std::shared_ptr<YangNotif>
YangItem::makeNotification(YangNotif& notif) const {
  std::shared_ptr<YangNotif> item = std::make_shared<YangNotif>(notif);
  return item;
}

// make: FEATURE
std::shared_ptr<YangFeature>
YangItem::makeFeature(YangFeature& feature) const {
  std::shared_ptr<YangFeature> item = std::make_shared<YangFeature>(feature);
  return item;
}

// -----------------------------------------------------------------------------
// Module:      YangItems
// Description:  YANG multiple item base class.
// -----------------------------------------------------------------------------
YangItems::YangItems(
    std::string name,
    uint32_t id,
    YangItemType_E type,
    const std::vector<std::shared_ptr<YangItem>>& items)
    : YangItem(name, id, type), mItems(items) {}

YangItems::~YangItems() {}

void
YangItems::dump(unsigned level) const {
  this->YangItem::dump(level);
  for (auto& item : mItems) {
    item->dump(level + 1);
  }
}

// add: LEAF
// SR_BINARY_E, SR_BITS_E, SR_ENUM_E, SR_IDENTITYREF_E,
// SR_INSTANCEID_E, SR_STRING_E, SR_BOOL_E, SR_DECIMAL64_E,
// SR_INT8_E, SR_INT16_E, SR_INT32_E, SR_INT64_E,
// SR_UINT8_E, SR_UINT16_E, SR_UINT32_E, SR_UINT64_E,
YangResult_E
YangItems::addLeaf(YangLeaf& leaf) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangLeaf> item = makeLeaf(leaf);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    mItems.push_back(item);
  }

  return result;
}

// add: REFERENCE
YangResult_E
YangItems::addReference(YangReference& reference) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangReference> item = makeReference(reference);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    mItems.push_back(item);
  }

  return result;
}

// add: CONTAINER
YangResult_E
YangItems::addContainer(YangContainer& container) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangContainer> item = makeContainer(container);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    mItems.push_back(item);
  }

  return result;
}

// add: GROUPING
YangResult_E
YangItems::addGroup(YangGroup& group) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangGroup> item = makeGroup(group);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    mItems.push_back(item);
  }

  return result;
}

// add: LIST
YangResult_E
YangItems::addList(YangList& list) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangList> item = makeList(list);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    mItems.push_back(item);
  }

  return result;
}

// add: CHOICE
YangResult_E
YangItems::addChoice(YangChoice& choice) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangChoice> item = makeChoice(choice);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    mItems.push_back(item);
  }

  return result;
}

// add: NOTIFICATION
YangResult_E
YangItems::addNotification(YangNotif& notif) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangNotif> item = makeNotification(notif);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    mItems.push_back(item);
  }

  return result;
}

// add: FEATURE
YangResult_E
YangItems::addFeature(YangFeature& feature) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangFeature> item = makeFeature(feature);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    mItems.push_back(item);
  }

  return result;
}

uint32_t
YangItems::getNumItems(void) const {
  return mItems.size();
}

IYangItem::YangItemType_E
YangItems::getItemType(uint32_t index) const {
  return mItems[index]->getType();
}

std::shared_ptr<YangItem>
YangItems::getItem(uint32_t index) const {
  return mItems[index];
}

std::vector<std::shared_ptr<YangItem>>
YangItems::getItemList(void) const {
  return mItems;
}

// -----------------------------------------------------------------------------
// Class:        YangLeaf
// Description:  YANG leaf base class
// -----------------------------------------------------------------------------
YangLeaf::YangLeaf(YangLeaf& leaf)
    : YangItem(leaf.getName(), leaf.getId(), YangItemType_E::LEAF) {}

YangLeaf::YangLeaf(std::string name, uint32_t id)
    : YangItem(name, id, YangItemType_E::LEAF) {}

YangLeaf::~YangLeaf() {}

// -----------------------------------------------------------------------------
// Class:        YangReference
// Description:  YANG Reference base class
// -----------------------------------------------------------------------------
YangReference::YangReference(YangReference& reference)
    : YangItem(
          reference.getName(), reference.getId(), YangItemType_E::REFERENCE) {}

YangReference::YangReference(std::string name, uint32_t id, std::string path)
    : YangItem(name, id, YangItemType_E::REFERENCE), mPath(path) {}

YangReference::~YangReference() {}

std::string
YangReference::getPath(void) {
  return mPath;
}

void
YangReference::setPath(std::string path) {
  mPath = path;
}

// -----------------------------------------------------------------------------
// Class:        YangContainer
// Description:  YANG container base class
// -----------------------------------------------------------------------------
YangContainer::YangContainer(YangContainer& container)
    : YangItems(
          container.getName(),
          container.getId(),
          YangItemType_E::CONTAINER,
          container.getItemList()) {}

YangContainer::YangContainer(std::string name, uint32_t id)
    : YangItems(name, id, YangItemType_E::CONTAINER) {}

YangContainer::~YangContainer() {}

// -----------------------------------------------------------------------------
// Class:        YangGroup
// Description:  YANG group base class
// -----------------------------------------------------------------------------
YangGroup::YangGroup(YangGroup& group)
    : YangItems(
          group.getName(),
          group.getId(),
          YangItemType_E::GROUP,
          group.getItemList()) {}

YangGroup::YangGroup(std::string name, uint32_t id)
    : YangItems(name, id, YangItemType_E::GROUP) {}

YangGroup::~YangGroup() {}

// -----------------------------------------------------------------------------
// Class:        YangList
// Description:  YANG List base class
// -----------------------------------------------------------------------------
YangList::YangList(YangList& list)
    : YangItems(
          list.getName(),
          list.getId(),
          YangItemType_E::LIST,
          list.getItemList()) {}

YangList::YangList(std::string name, uint32_t id)
    : YangItems(name, id, YangItemType_E::LIST) {}

YangList::~YangList() {}

void
YangList::addEntry(std::string entry) {
  mKeys.push_back(entry);
}

std::string
YangList::getKeyName(void) const {
  return mKeyName;
}

std::string
YangList::getEntryName(uint32_t index) const {
  return mKeys[index];
}

std::string
YangList::getEntryPath(uint32_t index) const {
  return (getName() + "[" + getKeyName() + "='" + getEntryName(index) + "']");
}

std::vector<std::string>
YangList::getEntryList(void) const {
  return mKeys;
}

void
YangList::setKeyName(std::string keyName) {
  mKeyName = keyName;
}

// -----------------------------------------------------------------------------
// Class:        YangChoiceOption
// Description:  YANG Choice Option base class
// -----------------------------------------------------------------------------
YangChoiceOption::YangChoiceOption(std::string name, uint32_t id)
    : YangItems(name, id, YangItemType_E::CHOICE_OPTION) {}

YangChoiceOption::~YangChoiceOption() {}

// -----------------------------------------------------------------------------
// Class:        YangChoice
// Description:  YANG Choice base class
// -----------------------------------------------------------------------------
YangChoice::YangChoice(YangChoice& choice)
    : YangItems(
          choice.getName(),
          choice.getId(),
          YangItemType_E::CHOICE,
          choice.getItemList()) {}

YangChoice::YangChoice(std::string name, uint32_t id)
    : YangItems(name, id, YangItemType_E::CHOICE) {}

YangChoice::~YangChoice() {}

YangResult_E
YangChoice::addOption(YangChoiceOption& option) {
  YangResult_E result = YangResult_E::OK;
  std::shared_ptr<YangChoiceOption> item = makeOption(option);
  if (item == nullptr) {
    result = YangResult_E::FAIL;
  } else {
    getItemList().push_back(item);
  }

  return result;
}

std::shared_ptr<YangChoiceOption>
YangChoice::makeOption(YangChoiceOption& option) const {
  std::shared_ptr<YangChoiceOption> item =
      std::make_shared<YangChoiceOption>(option.getName(), option.getId());
  return item;
}

// -----------------------------------------------------------------------------
// Class:        YangNotif
// Description:  YANG Notification base class
// -----------------------------------------------------------------------------
YangNotif::YangNotif(YangNotif& notif)
    : YangItems(
          notif.getName(),
          notif.getId(),
          YangItemType_E::NOTIFICATION,
          notif.getItemList()) {}

YangNotif::YangNotif(std::string name, uint32_t id)
    : YangItems(name, id, YangItemType_E::NOTIFICATION) {}

YangNotif::~YangNotif() {}

// -----------------------------------------------------------------------------
// Class:        YangFeature
// Description:  YANG feature base class
// -----------------------------------------------------------------------------
YangFeature::YangFeature(YangFeature& feature)
    : YangItem(feature.getName(), feature.getId(), YangItemType_E::FEATURE) {}

YangFeature::YangFeature(std::string name, uint32_t id)
    : YangItem(name, id, YangItemType_E::FEATURE) {}

YangFeature::~YangFeature() {}

// *****************************************************************************
// YANG Paths
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        YangPathEle
// Description:  YANG path element base class
// -----------------------------------------------------------------------------
YangPathEle::YangPathEle(
    YangPathType type, const std::string& p1, const std::string& p2)
    : mType(type) {
  if (mType == YangPathType::PARAMETER) {
    mParam = p1;
  } else if (mType == YangPathType::MODULE) {
    mModule = p1;
  } else if (mType == YangPathType::MODULE_PARAMETER) {
    mModule = p1;
    mParam = p2;
  } else
    mType = YangPathType::UNKNOWN;
}

YangPathEle::YangPathEle(
    YangPathType type,
    const std::string& p1,
    std::pair<std::string, std::string> key)
    : mType(type) {
  if (mType == YangPathType::LIST) {
    mParam = p1;
    mKeyList.push_back(key);
  } else
    mType = YangPathType::UNKNOWN;
}

YangPathEle::YangPathEle(
    YangPathType type,
    const std::string& p1,
    const std::string& p2,
    std::pair<std::string, std::string> key)
    : mType(type) {
  if (mType == YangPathType::LIST) {
    mModule = p1;
    mParam = p2;
    mKeyList.push_back(key);
  } else
    mType = YangPathType::UNKNOWN;
}

YangPathEle::YangPathEle(
    YangPathType type,
    const std::string& p1,
    std::vector<std::pair<std::string, std::string>> keyList)
    : mType(type) {
  if (mType == YangPathType::LIST) {
    mParam = p1;
    for (auto key : keyList) {
      mKeyList.push_back(key);
    }
  } else
    mType = YangPathType::UNKNOWN;
}

YangPathEle::YangPathEle(
    YangPathType type,
    const std::string& p1,
    const std::string& p2,
    std::vector<std::pair<std::string, std::string>> keyList)
    : mType(type) {
  if (mType == YangPathType::LIST) {
    mModule = p1;
    mParam = p2;
    for (auto key : keyList) {
      mKeyList.push_back(key);
    }
  } else
    mType = YangPathType::UNKNOWN;
}

YangPathEle::~YangPathEle() {}

std::string
YangPathEle::path(bool postSlash) {
  std::string pathStr;

  if (!mModule.empty())
    pathStr += mModule + ":";
  if (!mParam.empty()) {
    pathStr += mParam;
    for (auto key : mKeyList) {
      pathStr += "[" + key.first + "='" + key.second + "']";
    }
    if (postSlash) {
      pathStr += "/";
    }
  }

  return pathStr;
}

std::string
YangPathEle::parameter() {
  std::string parameterStr;

  if (!mModule.empty())
    parameterStr += mModule + ":";
  if (!mParam.empty())
    parameterStr += mParam;

  return parameterStr;
}

// -----------------------------------------------------------------------------
// Class:        YangPath
// Description:  YANG path base class
// -----------------------------------------------------------------------------
YangPath::YangPath() : mPaths() {}

// path
YangPath::YangPath(YangPath& path) { add(path); }

// parameter
YangPath::YangPath(const std::string& parameter) { add(parameter); }

// module, parameter
YangPath::YangPath(const std::string& module, const std::string& parameter) {
  add(module, parameter);
}

// parameter, key
YangPath::YangPath(
    const std::string& parameter, std::pair<std::string, std::string> key) {
  add(parameter, key);
}

// module, parameter, key
YangPath::YangPath(
    const std::string& module,
    const std::string& parameter,
    std::pair<std::string, std::string> key) {
  add(module, parameter, key);
}

// parameter, keyList
YangPath::YangPath(
    const std::string& parameter,
    std::vector<std::pair<std::string, std::string>> keyList) {
  add(parameter, keyList);
}

// module, parameter, keyList
YangPath::YangPath(
    const std::string& module,
    const std::string& parameter,
    std::vector<std::pair<std::string, std::string>> keyList) {
  add(module, parameter, keyList);
}

YangPath::~YangPath() {}

// path
void
YangPath::add(YangPath& pathParent) {
  for (auto path : pathParent.paths())
    mPaths.push_back(path);
}

// parameter
void
YangPath::add(const std::string& parameter) {
  mPaths.push_back(
      YangPathEle(YangPathEle::YangPathType::PARAMETER, parameter));
}

// module, parameter
void
YangPath::add(const std::string& module, const std::string& parameter) {
  mPaths.push_back(YangPathEle(
      YangPathEle::YangPathType::MODULE_PARAMETER, module, parameter));
}

// parameter, key
void
YangPath::add(
    const std::string& parameter, std::pair<std::string, std::string> key) {
  mPaths.push_back(
      YangPathEle(YangPathEle::YangPathType::LIST, parameter, key));
}

// module, parameter, key
void
YangPath::add(
    const std::string& module,
    const std::string& parameter,
    std::pair<std::string, std::string> key) {
  mPaths.push_back(
      YangPathEle(YangPathEle::YangPathType::LIST, module, parameter, key));
}

// parameter, keylist
void
YangPath::add(
    const std::string& parameter,
    std::vector<std::pair<std::string, std::string>> keyList) {
  mPaths.push_back(
      YangPathEle(YangPathEle::YangPathType::LIST, parameter, keyList));
}

// module, parameter, keylist
void
YangPath::add(
    const std::string& module,
    const std::string& parameter,
    std::vector<std::pair<std::string, std::string>> keyList) {
  mPaths.push_back(
      YangPathEle(YangPathEle::YangPathType::LIST, module, parameter, keyList));
}

// module
void
YangPath::addModule(const std::string& module) {
  mPaths.push_back(YangPathEle(YangPathEle::YangPathType::MODULE, module));
}

std::string
YangPath::pathRoot() {
  return (path(true, false, false));
}

std::string
YangPath::pathParam(bool postDot) {
  return (path(false, true, postDot));
}

std::string
YangPath::pathRootParam(bool postDot) {
  return (path(true, true, postDot));
}

std::string
YangPath::parameter() {
  return mPaths[mPaths.size() - 1].parameter();
}

std::string
YangPath::parameter(uint32_t index) {
  std::string parameter;
  if (index < mPaths.size())
    parameter = mPaths[index].parameter();
  return parameter;
}

uint32_t
YangPath::numberOfParameters() {
  return mPaths.size();
}

// std::string path(bool preSlash = false, bool postSlash = true, bool postDot =
// false);
std::string
YangPath::path(bool preSlash, bool postSlash, bool postDot) {
  std::string pathStr;

  for (uint32_t pathIdx = 0; pathIdx < mPaths.size(); pathIdx++) {
    bool moreParameters = false;
    // Add a slash, if more parameters
    if (postSlash || (pathIdx < (mPaths.size() - 1)))
      moreParameters = true;
    pathStr += mPaths[pathIdx].path(moreParameters);
  }
  // Add a slash to the start of the path
  if (!pathStr.empty()) {
    if (preSlash)
      pathStr = "/" + pathStr;
    if (postDot)
      pathStr += "/.";
  }

  return pathStr;
}

std::vector<YangPathEle>
YangPath::paths() {
  return mPaths;
}

// *****************************************************************************
// YANG Modules
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      YangModule
// Description:  YANG module base class.
// -----------------------------------------------------------------------------
YangModule::YangModule(YangModule& module)
    : YangItems(
          module.getName(),
          module.getId(),
          YangItemType_E::MODULE,
          module.getItemList()),
      mFilename(module.getFilename()),
      mModulePrefix(module.getPrefix()),
      mModuleNS(module.getNamespace()),
      mActive(false),
      mFeatures(),
      mCallbacks() {}

YangModule::YangModule(
    const std::string& name,
    const std::string& filename,
    const std::string& prefix,
    const std::string& moduleNS,
    uint32_t id)
    : YangItems(name, (uint32_t)id, YangItemType_E::MODULE),
      mFilename(filename),
      mModulePrefix(prefix),
      mModuleNS(moduleNS),
      mActive(false),
      mFeatures(),
      mCallbacks() {}

YangModule::~YangModule() {}

// get module filename
std::string
YangModule::getFilename(void) const {
  return mFilename;
}

// get module prefix
std::string
YangModule::getPrefix(void) {
  return mModulePrefix;
}

// get module namespace
std::string
YangModule::getNamespace(void) const {
  return mModuleNS;
}

// get module ID
uint32_t
YangModule::getModuleId(void) const {
  return getId();
}

// Activate module
void
YangModule::activate(void) {
  mActive = true;
}

// Deactivate module
void
YangModule::deactivate(void) {
  mActive = false;
}

// Is module active?
bool
YangModule::isActive(void) const {
  return mActive;
}

/**
 * Set feature state, enabled/disabled
 */
bool
YangModule::setFeature(const std::string& feature, bool enabled) {
  if (!isActive()) {
    std::cerr << "[warning] Unable to set feature " << getName()
              << " module: inactive" << std::endl;
    return false;
  }
  mFeatures[feature] = enabled;
  return true;
}

/**
 * Is feature enabled?
 */
bool
YangModule::isFeatureEnabled(const std::string& feature) {
  return mFeatures[feature];
}

bool
YangModule::registerCallback(
    const std::string& xpath, YangHandlerCallback callback) {
  if (!isActive()) {
    std::cerr << "[warning] Unable to register " << getName()
              << " module callback: inactive" << std::endl;
  }
  mCallbacks[xpath] = callback;
  return true;
}

bool
YangModule::testCallback(
    const std::string& xpath, std::shared_ptr<DataVariant> value) {
  // find closest match
  std::map<std::string, YangHandlerCallback>::reverse_iterator it;
  for (it = mCallbacks.rbegin(); it != mCallbacks.rend(); it++) {
    std::cerr << "YangItem::testCallback " << getName() << " search='" << xpath
              << "' this='" << it->first << "'" << std::endl;
    // does the entry path match the beginning of this variable full path?
    if (xpath.find(it->first) != 0)
      continue;

    // match
    std::cerr << "YangItem::testCallback : MATCH" << std::endl;
    return it->second(xpath, value);
  }

  // not found
  return false;
}

std::vector<std::shared_ptr<YangItem>>
YangModule::nextItem(std::shared_ptr<YangItem> item) {
  std::vector<std::shared_ptr<YangItem>> nextItemList;

  std::shared_ptr<YangItems> itemsPtr =
      std::dynamic_pointer_cast<YangItems>(item);
  if (itemsPtr) {
    nextItemList = itemsPtr->getItemList();
  }

  return (nextItemList);
}
