/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleMgr.h
 * \brief     YANG module manager
 *
 *
 * \details   Manages YANG modules stored in the radio datastore
 *
 */

#ifndef YANG_MODULEMGR_H_
#define YANG_MODULEMGR_H_

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cstdint>
#include <memory>
#include <map>

#include "IYangModuleMgr.h"
#include "IYangConfig.h"
#include "IYangModule.h"
#include "INetopeerMonService.h"

#include "Loggable.h"

#include "YangTypes.h"
#include "RadioDatastore.h"

namespace Mplane {

/*!
 * \class  YangModuleMgr
 * \brief
 * \details
 *
 */
class YangModuleMgr : public virtual IYangModuleMgr, public Loggable
{
public:
	YangModuleMgr();
	virtual ~YangModuleMgr();

	/**
	 * Get the data store
	 */
	virtual std::shared_ptr<IRadioDataStore> dataStore() const override ;


	virtual Status_E getStaus(void) const override;
	virtual void setStaus(Status_E status) override;
	virtual bool isInitialised(void) const override;

	/**
	 * Initialise the module manager
	 */
	virtual YangResult_E initialise(void) override;

	/**
	 * Get a list of installed module names
	 */
	virtual std::vector<std::string> getSupportedModuleList(void) override;

	/**
	 * Get a particular installed module by it's name
	 */
	virtual std::shared_ptr<IYangModule> getModule(const std::string & name) override;

	/**
	 * Get a particular module by it's id
	 */
	virtual std::shared_ptr<IYangModule> getModule(uint32_t id) override;

	/**
	 * Get the number of modules (i.e. max module ID + 1)
	 */
	virtual uint32_t getNumModules(void) const override;

	/**
	 * Set search path for YANG modules
	 */
	virtual void setSearchPath(const std::string & path) override;

	/**
	 * get a single item
	 */
	virtual YangResult_E getItem(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParam> & param) override;
	virtual YangResult_E getItem(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParam> & param) override;

	/**
	 * get multiple items
	 */
	virtual YangResult_E getItems(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParams> & params) override;
	virtual YangResult_E getItems(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParams> & params) override;

	/**
	 * set a single item
	 */
	virtual YangResult_E setItem(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParam> param) override;
	virtual YangResult_E setItem(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParam> param) override;

	/**
	 * set multiple items
	 */
	virtual YangResult_E setItems(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParams> params) override;
	virtual YangResult_E setItems(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParams> params) override;

	/**
	 * Is feature enabled?
	 */
	virtual bool isFeatureEnabled(const std::string & moduleName, const std::string & feature) override;
	virtual bool isFeatureEnabled(uint32_t moduleId, const std::string & feature) override;

	/**
	 * Add a callback function for this xpath (and any variables underneath it)
	 */
	virtual bool registerCallback(uint32_t moduleId, const std::string & xpath, YangHandlerCallback callback) override;

	/**
	 * Process events
	 */
	virtual void processEvents(void) override;

	/**
	 * Debug
	 */
	virtual bool testCallback(uint32_t moduleId, const std::string & xpath, std::shared_ptr<DataVariant> value) override;

protected:
	/**
	 * Create modules
	 */
	virtual YangResult_E createDatastore(void) = 0;

	/**
	 * Create modules
	 */
	virtual YangResult_E createModules(void) = 0;

	/**
	 * Add module to manager
	 */
	virtual void addModule(std::shared_ptr<IYangModule> module);

	/**
	 * Datastore
	 */
	std::shared_ptr<IRadioDataStore> mRadioDs;

	/**
	 * YANG module configuration
	 */
	std::shared_ptr<IYangConfig> mYangCfg;

	/**
	 * YANG module file search path
	 */
	std::string mSearchPath;

	/**
	 * List of YANG modules - Modules accessed using module string
	 */
	std::map<std::string, std::shared_ptr<IYangModule>> mModMapName;

	/**
	 * List of YANG module names
	 */
	std::vector<std::string> mModNames;

	/**
	 * List of YANG modules - Modules accessed using module ID
	 */
	std::map<uint32_t, std::shared_ptr<IYangModule>> mModMapId;

	/**
	 * List of YANG module IDs
	 */
	std::vector<uint32_t> mModIds;

private:
	/**
	 * Install configured modules
	 */
	YangResult_E installModules(void);

	/**
	 * Install modules from a list
	 */
	YangResult_E installModules(const std::vector<std::string>& modules);

	/**
	 * Get a list of available module names
	 */
	std::map<std::string, std::string> getModuleNamesAvailable(void);

	/**
	 * Get a list of configured modules
	 */
	std::vector<std::string> getModuleNamesConfigured(void);

	/**
	 * Get a list of installed modules
	 */
	std::vector<std::string> getModuleNamesInstalled(void);

	/**
	 * Get a list of installed modules
	 */
	YangResult_E enableFeatures(const std::string & name);

	/**
	 * Construct full xpath from modulename and parameter path
	 */
	std::string getPath(const std::string & moduleName, const std::string & xpath);

	Status_E mStatus;

	std::shared_ptr<INetopeerMonService> netopeerMonService;
};

} /* namespace Mplane */

#endif /* YANG_MODULEMGR_H_ */
