/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangModule.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VYMS_INC_IYANGMODULE_H_
#define VYMS_INC_IYANGMODULE_H_

#include <string>
#include <functional>

#include "DataVariant.h"
#include "YangTypes.h"
#include "YangParam.h"

namespace Mplane {

/*!
 * \class  IYangItem
 * \brief
 * \details
 *
 */
class IYangItem {
public:
	enum class YangItemType_E
	{
		UNKNOWN,
		LEAF,
		REFERENCE,
		CONTAINER,
		GROUP,
		LIST,
		CHOICE,
		CHOICE_OPTION,
		NOTIFICATION,
		FEATURE,
		MODULE,
		EMPTY
	};

	IYangItem() {}
	virtual ~IYangItem() {}

	/**
	 * Get item ID
	 */
	virtual uint32_t getId(void) const = 0;

	/**
	 * Get item type
	 */
	virtual YangItemType_E getType(void) const = 0;

	/**
	 * Get item name
	 */
	virtual std::string getName(void) const = 0;

	/**
	 * Debug
	 */
	virtual void dump(unsigned level=0) const = 0;

} ;


/*!
 * \class  IYangModule
 * \brief
 * \details
 *
 */
class IYangModule : public virtual IYangItem {
public:
	IYangModule() {}
	virtual ~IYangModule() {}

	using YangHandlerCallback = std::function<bool(const std::string& , std::shared_ptr<DataVariant> )> ;

	/**
	 * Get module YANG file name
	 */
	virtual std::string getFilename(void) const = 0;

	/**
	 * Get module prefix
	 */
	virtual std::string getPrefix(void) = 0;

	/**
	 * Get module namespace
	 */
	virtual std::string getNamespace(void) const = 0;

	/**
	 * Get module ID
	 */
	virtual uint32_t getModuleId(void) const = 0;

	/**
	 * Activate module
	 */
	virtual void activate(void) = 0;

	/**
	 * Deactivate module
	 */
	virtual void deactivate(void) = 0;

	/**
	 * Is module active?
	 */
	virtual bool isActive(void) const = 0;

	/**
	 * Add feature state
	 */
	virtual bool setFeature(const std::string & feature, bool enabled = true) = 0;

	/**
	 * Is feature enabled?
	 */
	virtual bool isFeatureEnabled(const std::string & feature) = 0;

	/**
	 * Add a callback function for this xpath (and any variables underneath it)
	 */
	virtual bool registerCallback(const std::string & xpath, YangHandlerCallback callback) = 0;

	/**
	 * Debug
	 */
	virtual bool testCallback(const std::string & xpath, std::shared_ptr<DataVariant> value) = 0;
} ;

}

#endif /* VYMS_INC_IYANGMODULE_H_ */
