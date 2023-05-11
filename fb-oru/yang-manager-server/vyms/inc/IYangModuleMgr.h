/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangModuleMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VYMS_INC_IYANGMODULEMGR_H_
#define VYMS_INC_IYANGMODULEMGR_H_

#include <memory>
#include "YangTypes.h"

#include "IYangModule.h"
#include "IRadioDataStore.h"

namespace Mplane {

/*!
 * \class  IYangModuleMgr
 * \brief
 * \details
 *
 */
class IYangModuleMgr {
public:

	/**
	 * Singleton
	 */
	static std::shared_ptr<IYangModuleMgr> singleton() ;


	enum class Status_E : uint8_t
	{
		UNINITIALISED,
		INITIALISED,
		FAILED,
	};

	using YangHandlerCallback = std::function<bool(const std::string & , std::shared_ptr<DataVariant> )>;

	IYangModuleMgr() {}
	virtual ~IYangModuleMgr() {}

	/**
	 * Get the data store
	 */
	virtual std::shared_ptr<IRadioDataStore> dataStore() const =0 ;

	/**
	 * Module manager status methods
	 */
	virtual Status_E getStaus(void) const = 0;
	virtual void setStaus(Status_E status) = 0;
	virtual bool isInitialised(void) const = 0;

	/**
	 * Initialise the modules
	 */
	virtual YangResult_E initialise(void) = 0;

	/**
	 * Get a list of installed module names
	 */
	virtual std::vector<std::string> getSupportedModuleList(void) = 0;

	/**
	 * Get a particular installed module by it's name
	 */
	virtual std::shared_ptr<IYangModule> getModule(const std::string & name) = 0;

	/**
	 * Get a particular module by it's id
	 */
	virtual std::shared_ptr<IYangModule> getModule(uint32_t id) = 0;

	/**
	 * Get the number of modules (i.e. max module ID + 1)
	 */
	virtual uint32_t getNumModules(void) const = 0;

	/**
	 * Set search path for YANG modules
	 */
	virtual void setSearchPath(const std::string & path) = 0;

	/**
	 * get a single item
	 */
	virtual YangResult_E getItem(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParam> & param) = 0;
	virtual YangResult_E getItem(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParam> & param) = 0;

	/**
	 * get multiple items
	 */
	virtual YangResult_E getItems(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParams> & params) = 0;
	virtual YangResult_E getItems(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParams> & params) = 0;

	/**
	 * set a single item
	 */
	virtual YangResult_E setItem(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParam> param) = 0;
	virtual YangResult_E setItem(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParam> param) = 0;

	/**
	 * set multiple items
	 */
	virtual YangResult_E setItems(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParams> params) = 0;
	virtual YangResult_E setItems(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParams> params) = 0;

	/**
	 * Is feature enabled?
	 */
	virtual bool isFeatureEnabled(const std::string & moduleName, const std::string & feature) = 0;
	virtual bool isFeatureEnabled(uint32_t moduleId, const std::string & feature) = 0;

	/**
	 * Add a callback function for this xpath (and any variables underneath it)
	 */
	virtual bool registerCallback(uint32_t moduleId, const std::string & xpath, YangHandlerCallback callback) = 0;

	/**
	 * Process events
	 */
	virtual void processEvents(void) = 0;

	/**
	 * Debug
	 */
	virtual bool testCallback(uint32_t moduleId, const std::string & xpath, std::shared_ptr<DataVariant> value) = 0;

} ;

}

#endif /* VYMS_INC_IYANGMODULEMGR_H_ */
