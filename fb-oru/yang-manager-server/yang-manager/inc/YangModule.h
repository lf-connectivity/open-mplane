/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModule.h
 * \brief     YANG Module classes
 *
 *
 * \details   YANG module classes, providing methods to describe YANG modules.
 *
 */

#ifndef YANG_MODULE_H_
#define YANG_MODULE_H_

// *****************************************************************************
// Includes
// *****************************************************************************
#include <cstdint>
#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <string>

#include "IYangModule.h"

#include "RadioDatastore.h"

namespace Mplane {

class YangLeaf;
class YangReference;
class YangContainer;
class YangGroup;
class YangList;
class YangChoice;
class YangNotif;
class YangFeature;

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
class YangItem : public virtual IYangItem
{
public:
	YangItem();
	YangItem(YangItem & item);
	YangItem(std::string name, uint32_t id, IYangItem::YangItemType_E type);
	virtual ~YangItem();

	/**
	 * Get item ID
	 */
	virtual uint32_t getId(void) const override;

	/**
	 * Get item type
	 */
	virtual IYangItem::YangItemType_E getType(void) const override;

	/**
	 * Get item name
	 */
	virtual std::string getName(void) const override;

	/**
	 * Debug
	 */
	virtual void dump(unsigned level=0) const override;

	static std::string typeStr(YangItemType_E type);

protected:
	// make: LEAF
	// SR_BINARY_E, SR_BITS_E, SR_ENUM_E, SR_IDENTITYREF_E,
	// SR_INSTANCEID_E, SR_STRING_E, SR_BOOL_E, SR_DECIMAL64_E,
	// SR_INT8_E, SR_INT16_E, SR_INT32_E, SR_INT64_E,
	// SR_UINT8_E, SR_UINT16_E, SR_UINT32_E, SR_UINT64_E,
	virtual std::shared_ptr<YangLeaf> makeLeaf(YangLeaf & leaf) const;

	// make: REFERENCE
	virtual std::shared_ptr<YangReference> makeReference(YangReference & reference) const;

	// make: CONTAINER
	virtual std::shared_ptr<YangContainer> makeContainer(YangContainer & container) const;

	// make: GROUPING
	virtual std::shared_ptr<YangGroup> makeGroup(YangGroup & group) const;

	// make: LIST
	virtual std::shared_ptr<YangList> makeList(YangList & list) const;

	// make: CHOICE
	virtual std::shared_ptr<YangChoice> makeChoice(YangChoice & choice) const;

	// make: NOTIFICATION
	virtual std::shared_ptr<YangNotif> makeNotification(YangNotif & notif) const;

	// make: FEATURE
	virtual std::shared_ptr<YangFeature> makeFeature(YangFeature & feature) const;

private:
	std::string mName;
	uint32_t mId;
	YangItemType_E mType;
};

// -----------------------------------------------------------------------------
// Module:      YangItems
// Description:  YANG multiple item base class.
// -----------------------------------------------------------------------------
class YangItems : public YangItem
{
public:
	YangItems(std::string name, uint32_t id, YangItemType_E type, const std::vector<std::shared_ptr<YangItem>> & items = {});
	~YangItems();

	// add: LEAF
	// SR_BINARY_E, SR_BITS_E, SR_ENUM_E, SR_IDENTITYREF_E,
	// SR_INSTANCEID_E, SR_STRING_E, SR_BOOL_E, SR_DECIMAL64_E,
	// SR_INT8_E, SR_INT16_E, SR_INT32_E, SR_INT64_E,
	// SR_UINT8_E, SR_UINT16_E, SR_UINT32_E, SR_UINT64_E,
	virtual YangResult_E addLeaf(YangLeaf & leaf);

	// add: REFERENCE
	virtual YangResult_E addReference(YangReference & reference);

	// add: CONTAINER
	virtual YangResult_E addContainer(YangContainer & container);

	// add: GROUPING
	virtual YangResult_E addGroup(YangGroup & group);

	// add: LIST
	virtual YangResult_E addList(YangList & list);

	// add: CHOICE
	virtual YangResult_E addChoice(YangChoice & choice);

	// add: NOTIFICATION
	virtual YangResult_E addNotification(YangNotif & notif);

	// add: FEATURE
	virtual YangResult_E addFeature(YangFeature & feature);

	uint32_t getNumItems(void) const;
	std::shared_ptr<YangItem> getItem(uint32_t index) const;
	std::vector<std::shared_ptr<YangItem>> getItemList(void) const;
	IYangItem::YangItemType_E getItemType(uint32_t index) const;

	/**
	 * Debug
	 */
	virtual void dump(unsigned level=0) const override;

protected:

private:
	std::vector<std::shared_ptr<YangItem>> mItems;
};

// -----------------------------------------------------------------------------
// Class:        YangLeaf
// Description:  YANG leaf base class
// -----------------------------------------------------------------------------
class YangLeaf : public YangItem
{
public:
	YangLeaf(YangLeaf & leaf);
	~YangLeaf();

protected:
	YangLeaf(std::string name, uint32_t id);

private:

};

// -----------------------------------------------------------------------------
// Class:        YangReference
// Description:  YANG Reference base class
// -----------------------------------------------------------------------------
class YangReference : public YangItem
{
public:
	YangReference(YangReference & name);
	~YangReference();

	std::string getPath(void);

protected:
	YangReference(std::string name, uint32_t id, std::string path);

	void setPath(std::string path);

private:
	std::string mPath;
};

// -----------------------------------------------------------------------------
// Class:        YangContainer
// Description:  YANG container base class
// -----------------------------------------------------------------------------
class YangContainer : public YangItems
{
public:
	YangContainer(YangContainer & container);
	~YangContainer();

protected:
	YangContainer(std::string name, uint32_t id);

private:

};

// -----------------------------------------------------------------------------
// Class:        YangGroup
// Description:  YANG group base class
// -----------------------------------------------------------------------------
class YangGroup : public YangItems
{
public:
	YangGroup(YangGroup & group);
	~YangGroup();

protected:
	YangGroup(std::string name, uint32_t id);

private:

};

// -----------------------------------------------------------------------------
// Class:        YangList
// Description:  YANG List base class
// -----------------------------------------------------------------------------
class YangList : public YangItems
{
public:
	YangList(YangList & list);
	~YangList();

	std::string getKeyName(void) const;

	void addEntry(std::string entry);

	std::string getEntryName(uint32_t index) const;
	std::string getEntryPath(uint32_t index) const;
	std::vector<std::string> getEntryList(void) const;

protected:
	YangList(std::string name, uint32_t id);

	void setKeyName(std::string keyName);

private:
	std::string mKeyName;
	std::vector<std::string> mKeys;
};

// -----------------------------------------------------------------------------
// Class:        YangChoiceOption
// Description:  YANG Choice Option base class
// -----------------------------------------------------------------------------
class YangChoiceOption : public YangItems
{
public:
	YangChoiceOption(std::string name, uint32_t id);
	~YangChoiceOption();

protected:

private:

};

// -----------------------------------------------------------------------------
// Class:        YangChoice
// Description:  YANG Choice base class
// -----------------------------------------------------------------------------
class YangChoice : public YangItems
{
public:
	YangChoice(YangChoice & choice);
	~YangChoice();

	YangResult_E addOption(YangChoiceOption & option);

protected:
	YangChoice(std::string name, uint32_t id);

private:
	std::shared_ptr<YangChoiceOption> makeOption(YangChoiceOption & option) const;
};

// -----------------------------------------------------------------------------
// Class:        YangNotif
// Description:  YANG Notification base class
// -----------------------------------------------------------------------------
class YangNotif : public YangItems
{
public:
	YangNotif(YangNotif & notif);
	~YangNotif();

protected:
	YangNotif(std::string notifName, uint32_t id);

private:

};

// -----------------------------------------------------------------------------
// Class:        YangFeature
// Description:  YANG feature base class
// -----------------------------------------------------------------------------
class YangFeature : public YangItem
{
public:
	YangFeature(YangFeature & feature);
	~YangFeature();

protected:
	YangFeature(std::string name, uint32_t id);

private:

};

// *****************************************************************************
// YANG Paths
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        YangPathEle
// Description:  YANG path element base class
// -----------------------------------------------------------------------------
class YangPathEle
{
public:
	enum class YangPathType
	{
		UNKNOWN,
		PARAMETER,
		MODULE,
		MODULE_PARAMETER,
		LIST,
		OPTION,
	};

	// PARAMETER, MODULE, MODULE_PARAMETER
	YangPathEle(YangPathType type,
	            const std::string & p1,
	            const std::string & p2 = std::string());

	// LIST - single dimension
	YangPathEle(YangPathType type,
	            const std::string & p1,
	            std::pair<std::string, std::string> key);
	YangPathEle(YangPathType type,
	            const std::string & p1,
	            const std::string & p2,
	            std::pair<std::string, std::string> key);

	// LIST - multiple dimension
	YangPathEle(YangPathType type,
	            const std::string & p1,
	            std::vector<std::pair<std::string, std::string>> keyList);
	YangPathEle(YangPathType type,
	            const std::string & p1,
	            const std::string & p2,
	            std::vector<std::pair<std::string, std::string>> keyList);


	~YangPathEle();

	// returns parameter path
	std::string path(bool postSlash);

	// returns parameter
	std::string parameter();

protected:

private:
	YangPathEle::YangPathType mType;
	std::string mModule;
	std::string mParam;
	std::vector<std::pair<std::string, std::string>> mKeyList;
};

// -----------------------------------------------------------------------------
// Class:        YangPath
// Description:  YANG path base class
// -----------------------------------------------------------------------------
class YangPath
{
public:
	// No path
	YangPath();

	// path
	YangPath(YangPath & path);

	// parameter
	YangPath(const std::string & parameter);

	// module, parameter
	YangPath(const std::string & module,
	         const std::string & parameter);

	// parameter, key
	YangPath(const std::string & parameter,
	         std::pair<std::string, std::string> key);

	// module, parameter, key
	YangPath(const std::string & module,
	         const std::string & parameter,
	         std::pair<std::string, std::string> key);

	// parameter, keyList
	YangPath(const std::string & parameter,
	         std::vector<std::pair<std::string, std::string>> keyList);

	// module, parameter, keyList
	YangPath(const std::string & module,
	         const std::string & parameter,
	         std::vector<std::pair<std::string, std::string>> keyList);

	~YangPath();

	// path
	void add(YangPath & pathParent);

	// parameter
	void add(const std::string & parameter);

	// module, parameter
	void add(const std::string & module,
	         const std::string & parameter);

	// parameter, key
	void add(const std::string & parameter,
	         std::pair<std::string, std::string> key);

	// module, parameter, key
	void add(const std::string & module,
	         const std::string & parameter,
	         std::pair<std::string, std::string> key);

	// parameter, keyList
	void add(const std::string & parameter,
	         std::vector<std::pair<std::string, std::string>> keyList);

	// module, parameter, keyList
	void add(const std::string & module,
	         const std::string & parameter,
	         std::vector<std::pair<std::string, std::string>> keyList);

	// module
	void addModule(const std::string & module);

	// returns path
	std::string pathRoot();
	std::string pathParam(bool postDot = false);
	std::string pathRootParam(bool postDot = false);

	// parameters
	std::string parameter();
	std::string parameter(uint32_t index);
	uint32_t numberOfParameters();

protected:

private:
	std::string path(bool preSlash = false, bool postSlash = true, bool postDot = false);
	std::vector<YangPathEle> paths();

	std::vector<YangPathEle> mPaths;
};

// *****************************************************************************
// YANG Module Classes
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      YangModule
// Description:  YANG module base class.
// -----------------------------------------------------------------------------
class YangModule : public virtual IYangModule, public YangItems
{
public:
	YangModule(YangModule & module);
	YangModule(const std::string & name,
	           const std::string & filename,
	           const std::string & prefix,
	           const std::string & moduleNS,
	           uint32_t id);
	~YangModule();

	/**
	 * Get module YANG filename
	 */
	virtual std::string getFilename(void) const override;

	/**
	 * Get module prefix
	 */
	virtual std::string getPrefix(void) override;

	/**
	 * Get module namespace
	 */
	virtual std::string getNamespace(void) const override;

	/**
	 * Get module ID
	 */
	virtual uint32_t getModuleId(void) const override;

	/**
	 * Activate module
	 */
	virtual void activate(void) override;

	/**
	 * Deactivate module
	 */
	virtual void deactivate(void) override;

	/**
	 * Is module active?
	 */
	virtual bool isActive(void) const override;

	/**
	 * Set feature state, enabled/disabled
	 */
	virtual bool setFeature(const std::string & feature, bool enabled = true) override;

	/**
	 * Is feature enabled?
	 */
	virtual bool isFeatureEnabled(const std::string & feature) override;

	/**
	 * Add a callback function for this xpath (and any variables underneath it)
	 */
	virtual bool registerCallback(const std::string & xpath, YangHandlerCallback callback) override;

	/**
	 * Get callback function for specified path
	 */
	//virtual bool getCallback(const std::string & xpath, YangHandlerCallback & callback) override;

	/**
	 * Debug
	 */
	virtual bool testCallback(const std::string & xpath, std::shared_ptr<DataVariant> value) override;

protected:

private:
	std::vector<std::shared_ptr<YangItem>> nextItem(std::shared_ptr<YangItem> item);

	std::string mFilename;
	std::string mModulePrefix;
	std::string mModuleNS;
	bool mActive;
	std::map<std::string, bool> mFeatures;
	std::map<std::string, YangHandlerCallback> mCallbacks;
};

} /* namespace Mplane */

#endif /* YANG_MODULE_H_ */
