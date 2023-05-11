/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleMgr.cpp
 * \brief     YANG module manager
 *
 *
 * \details   Manages YANG modules stored in the radio datastore
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <memory>
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <sys/stat.h>

#include "IBootTimer.h"
#include "Tokeniser.h"

#include "YangModuleMgr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangModuleMgr::YangModuleMgr() :
	Loggable("YangModuleMgr","YANG"),
	mRadioDs(),
	mYangCfg(),
	mSearchPath(),
	mModMapName(),
	mModNames(),
	mModMapId(),
	mModIds(),
	mStatus(Status_E::UNINITIALISED),
	netopeerMonService(INetopeerMonService::singleton())
{
}

//-------------------------------------------------------------------------------------------------------------
YangModuleMgr::~YangModuleMgr()
{
}

// ------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRadioDataStore> Mplane::YangModuleMgr::dataStore() const
{
	return mRadioDs ;
}

// ------------------------------------------------------------------------------------------------------------
YangModuleMgr::Status_E YangModuleMgr::getStaus(void) const
{
	return mStatus;
}

// ------------------------------------------------------------------------------------------------------------
void YangModuleMgr::setStaus(YangModuleMgr::Status_E status)
{
	mStatus = status;
}

// ------------------------------------------------------------------------------------------------------------
bool YangModuleMgr::isInitialised(void) const
{
	return(mStatus == Status_E::INITIALISED);
}

//-------------------------------------------------------------------------------------------------------------
YangResult_E YangModuleMgr::initialise()
{
	YangResult_E result = YangResult_E::FAIL;

	eventInfo("Initialising YANG Manager");

	// Get access to the YANG config service
	if((mYangCfg = IYangConfig::getConfigSingleton()) == nullptr)
	{
		eventError("Failed to initialise YANG config service");
	}

	// Create YANG modules
	else if((result = createModules()) != YangResult_E::OK)
	{
		eventError("Failed to created module(s)");
	}

	// Create datastore
	else if((result = createDatastore()) != YangResult_E::OK)
	{
		eventError("Failed to create datastore");
	}

	// Initialise datastore
	else if((result = mRadioDs->initialise()) != YangResult_E::OK)
	{
		eventError("Failed to initialise datastore");
	}

	// Locate and install each configured module, enabling features and loading startup data
	else if((result = installModules()) != YangResult_E::OK)
	{
		eventError("Module installation fault");
	}

	// Activate the radio datastore
	else if((result = mRadioDs->activate()) != YangResult_E::OK)
	{
		eventError("Failed to activate radio datastore");
	}

	else
	{
		// Attempt to start netopeer2-server using the monitoring service.
		ReturnType::State startState = netopeerMonService->startService();

		if((result = ((startState == ReturnType::RT_OK) ? YangResult_E::OK : YangResult_E::FAIL)) != YangResult_E::OK)
		{
			eventError("Failed to start netopeer2");
		}
	}

	// set timing
	IBootTimer::getInstance()->nameComplete("yang") ;

	if(result == YangResult_E::OK)
	{
		setStaus(Status_E::INITIALISED);
	}
	else
	{
		setStaus(Status_E::FAILED);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------------------
std::vector<std::string> YangModuleMgr::getSupportedModuleList(void)
{
	return mRadioDs->getListOfInstalledModules();
}

// ------------------------------------------------------------------------------------------------------------
void YangModuleMgr::setSearchPath(const std::string & path)
{
	mSearchPath = path;
}

// ------------------------------------------------------------------------------------------------------------
/**
 * get a single item
 */
YangResult_E YangModuleMgr::getItem(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParam> & param)
{
	YangResult_E result = YangResult_E::FAIL;

	std::shared_ptr<IYangModule> mod = getModule(moduleName);
	if(mod)
	{
		// Retrieve parameter from datastore
		result = mRadioDs->getItem(getPath(mod->getName(), xpath), param);
	}

	return result;
}
YangResult_E YangModuleMgr::getItem(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParam> & param)
{
	YangResult_E result = YangResult_E::FAIL;

	std::shared_ptr<IYangModule> mod = getModule(moduleId);
	if(mod)
	{
		// Retrieve parameter from datastore
		result = mRadioDs->getItem(getPath(mod->getName(), xpath), param);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------------------
/**
 * get multiple items
 */
YangResult_E YangModuleMgr::getItems(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParams> & params)
{
	YangResult_E result = YangResult_E::FAIL;

	std::shared_ptr<IYangModule> module = getModule(moduleName);
	if(module)
	{
		// Retrieve parameters from datastore
		result = mRadioDs->getItems(getPath(module->getName(), xpath), params);
	}

	return result;
}
YangResult_E YangModuleMgr::getItems(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParams> & params)
{
	YangResult_E result = YangResult_E::FAIL;

	std::shared_ptr<IYangModule> mod = getModule(moduleId);
	if(mod)
	{
		// Retrieve parameters from datastore
		result = mRadioDs->getItems(getPath(mod->getName(), xpath), params);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------------------
/**
 * set a single item
 */
YangResult_E YangModuleMgr::setItem(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParam> param)
{
	YangResult_E result = YangResult_E::FAIL;

	std::shared_ptr<IYangModule> mod = getModule(moduleName);
	if(mod)
	{
		// Set parameter in datastore
		result = mRadioDs->setItem(getPath(mod->getName(), xpath), param);
	}

	return result;
}
YangResult_E YangModuleMgr::setItem(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParam> param)
{
	YangResult_E result = YangResult_E::FAIL;

	std::shared_ptr<IYangModule> mod = getModule(moduleId);
	if(mod)
	{
		// Set parameter in datastore
		result = mRadioDs->setItem(getPath(mod->getName(), xpath), param);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------------------
/**
 * set multiple items
 */
YangResult_E YangModuleMgr::setItems(const std::string & moduleName, const std::string & xpath, std::shared_ptr<YangParams> params)
{
	YangResult_E result = YangResult_E::FAIL;

	std::shared_ptr<IYangModule> mod = getModule(moduleName);
	if(mod)
	{
		// Set parameters in datastore
		result = mRadioDs->setItems(getPath(mod->getName(), xpath), params);
	}

	return result;
}
YangResult_E YangModuleMgr::setItems(uint32_t moduleId, const std::string & xpath, std::shared_ptr<YangParams> params)
{
	YangResult_E result = YangResult_E::FAIL;

	std::shared_ptr<IYangModule> mod = getModule(moduleId);
	if(mod)
	{
		// Set parameters in datastore
		result = mRadioDs->setItems(getPath(mod->getName(), xpath), params);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------------------
bool YangModuleMgr::isFeatureEnabled(const std::string & moduleName, const std::string & feature)
{
	bool enabled = false;

	std::shared_ptr<IYangModule> mod = getModule(moduleName);
	if(mod)
	{
		enabled = mod->isFeatureEnabled(feature);
	}

	return enabled;
}

// ------------------------------------------------------------------------------------------------------------
bool YangModuleMgr::isFeatureEnabled(uint32_t moduleId, const std::string & feature)
{
	bool enabled = false;

	std::shared_ptr<IYangModule> mod = getModule(moduleId);
	if(mod)
	{
		enabled = mod->isFeatureEnabled(feature);
	}

	return enabled;
}

// ------------------------------------------------------------------------------------------------------------
bool YangModuleMgr::registerCallback(uint32_t moduleId, const std::string & xpath, YangHandlerCallback callback)
{
	bool success = false;

	std::shared_ptr<IYangModule> mod = getModule(moduleId);
	if(mod)
	{
		// Register callback path with module
		success = mod->registerCallback(getPath(mod->getName(), xpath), callback);
	}

	return success;
}

// ------------------------------------------------------------------------------------------------------------
/**
 * Process events
 */
void YangModuleMgr::processEvents(void)
{
	//eventError("YangModuleMgr::processEvents()");

	RadDsEvt_t event;
	while(mRadioDs->getNextEvent(event))
	{
		//eventError("Processing " << event.module << " event...");

		// Search module for changes

		// Call registered callbacks, if the change matches the callback path

	}

	//eventError("No more events");
}

// ------------------------------------------------------------------------------------------------------------
bool YangModuleMgr::testCallback(uint32_t moduleId, const std::string & xpath, std::shared_ptr<DataVariant> value)
{
	bool success = false;

	std::shared_ptr<IYangModule> mod = getModule(moduleId);
	if(mod)
	{
		// Test callback path
		success = mod->testCallback(getPath(mod->getName(), xpath), value);
	}

	return success;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

// ------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangModule> YangModuleMgr::getModule(const std::string & name)
{
	//eventError("Finding module " << name << " ....");
	auto entry(mModMapName.find(name));
	if(entry == mModMapName.end())
	{
		eventWarning("Module %s not found", name.c_str());
		return std::shared_ptr<IYangModule>();
	}

	return entry->second;
}

// ------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangModule> YangModuleMgr::getModule(uint32_t id)
{
	//eventError("Finding module " << id << " ....");
	auto entry(mModMapId.find(id));
	if(entry == mModMapId.end())
	{
		eventWarning("Module %i not found", id);
		return std::shared_ptr<IYangModule>();
	}

	return entry->second;
}

// ------------------------------------------------------------------------------------------------------------
uint32_t YangModuleMgr::getNumModules(void) const
{
	return mModIds.size();
}

//-------------------------------------------------------------------------------------------------------------
void YangModuleMgr::addModule(std::shared_ptr<IYangModule> module)
{
	if(!module)
		return;

	//eventError("YangModuleMgr::addModule(" << module->getId() << ") " << module->getName() << ", " << module->getFilename());

	mModNames.push_back(module->getName());
	mModMapName[mModNames.back()] = module;

	mModIds.push_back(module->getId());
	mModMapId[mModIds.back()] = module;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangResult_E YangModuleMgr::installModules(void)
{
	// Ensure iana & ietf modules are installed ready
	std::vector<std::string> requiredModules{
		// should already be installed
		"ietf-crypto-types",
		"ietf-inet-types",
		"ietf-netconf-acm",
		"ietf-netconf-monitoring",
		"ietf-yang-types",
		"ietf-yang-library",
		"iana-if-type",
		"iana-hardware",

		// install these
		"ietf-interfaces",
		"ietf-dhcpv6-types",
		"ietf-hardware",
		"ietf-ip",
	} ;
	if (installModules(requiredModules) != YangResult_E::OK)
		return YangResult_E::FAIL ;

	// Install each configured available module
	if (installModules(getModuleNamesConfigured()) != YangResult_E::OK)
		return YangResult_E::FAIL ;

	return YangResult_E::OK;
}


//-------------------------------------------------------------------------------------------------------------
YangResult_E YangModuleMgr::installModules(const std::vector<std::string>& modules)
{
	YangResult_E result(YangResult_E::FAIL) ;
	uint32_t successCount(0) ;

	std::map<std::string, std::string> modsAvailable(getModuleNamesAvailable()) ;

	// Install each configured available module
	for(auto name : modules)
	{
		if (mRadioDs->isModuleInstalled(name))
		{
			successCount++;
			continue ;
		}

		std::string filename(modsAvailable[name]);

		eventInfo("Installing %s module ....", name.c_str());

		// Is the module available to install?
		if(modsAvailable.find(name) == modsAvailable.end())
		{
			eventError("Unable to find %s module", name.c_str());
			continue ;
		}


		// Install datastore module
// ToDo: Fix the module installation to enable features during installing
		// An empty feature list is passed to installModule() as it fails to enable features.
		// Features enabled after install.
		std::vector<std::string> features;

		// Install module
		if (mRadioDs->installModule(name, mSearchPath, filename, features) != YangResult_E::OK)
		{
			eventError("Install failure: %s", filename.c_str());
			continue ;
		}

		// Activate module
		mModMapName[name]->activate();

		// Enable module features
		if((result = enableFeatures(name)) != YangResult_E::OK)
		{
			eventError("Failed to enable module features");
			break ;
		}

		eventInfo("Installed: %s/%s", mSearchPath.c_str(), filename.c_str());

		successCount++;
	}

	if(successCount == modules.size())
	{
		result = YangResult_E::OK;
	}

	return result;
}




//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> YangModuleMgr::getModuleNamesAvailable(void)
{
	std::map<std::string, std::string> modFileMap;

	// Check search path
	struct stat info;
	if((stat(mSearchPath.c_str(), &info) != 0) || 	// Invalid path
	   (!(info.st_mode & S_IFDIR)))               	// Not a directory
	{
		eventError("Invalid YANG file Path: %s", mSearchPath.c_str());
	}
	else
	{
		// Locate each available module
		for(uint32_t idx = 0; idx < mModNames.size(); idx++)
		{
			std::shared_ptr<IYangModule> mod = mModMapName[mModNames[idx]];
			if(mod == nullptr)
			{
				eventError("Invalid module : %i", idx);
			}
			else
			{
				// Check module yang file exists
				std::string fileAbs = mSearchPath + "/" + mod->getFilename();
				if(stat(fileAbs.c_str(), &info) != 0)
				{
					eventError("Invalid yang file: %s", fileAbs.c_str());
				}
				else if(!(info.st_mode & S_IFMT))
				{
					eventError("Not a file: %s", fileAbs.c_str());
				}
				else
				{
					// Add map of yang module and filename with full path to list
					modFileMap[mod->getName()] = mod->getFilename();
				}
			}
		}
	}

#if 0
	eventInfo ("Available modules: %lu", mModNames.size());
	for(uint32_t idx = 0; idx < mModNames.size(); idx++)
	{
		eventInfo("\tModule: %s", mModNames[idx].c_str());
	}
#endif

	return modFileMap;
}

//-------------------------------------------------------------------------------------------------------------
// DEBUG - Enable definition to use hardcoded list, overriding config file.
//#define ORAN_MODULE_LIST_PHASE1  "ietf-interfaces,iana-hardware,ietf-hardware,ietf-netconf-acm,ietf-crypto-types,ietf-dhcpv6-types,ietf-inet-types,ietf-ip,iana-if-type,o-ran-interfaces,                                                                   o-ran-operations,                                                o-ran-processing-element,o-ran-compression-factors,o-ran-module-cap,                          o-ran-delay-management,          o-ran-laa-operations,                                                                        o-ran-uplane-conf,o-ran-ald-port,o-ran-ald,                      o-ran-trace,o-ran-transceiver,o-ran-mplane-int,o-ran-dhcp,                 o-ran-sync,"
//#define ORAN_MODULE_LIST_PHASE2  "ietf-interfaces,iana-hardware,ietf-hardware,ietf-netconf-acm,ietf-crypto-types,ietf-dhcpv6-types,ietf-inet-types,ietf-ip,iana-if-type,o-ran-interfaces,                                 o-ran-hardware,                   o-ran-operations,                                                o-ran-processing-element,o-ran-compression-factors,o-ran-module-cap,                          o-ran-delay-management,          o-ran-laa-operations,o-ran-lbm,                                                              o-ran-uplane-conf,o-ran-ald-port,o-ran-ald,                      o-ran-trace,o-ran-transceiver,o-ran-mplane-int,o-ran-dhcp,                 o-ran-sync,"
//#define ORAN_MODULE_LIST_PHASE3  "ietf-interfaces,iana-hardware,ietf-hardware,ietf-netconf-acm,ietf-crypto-types,ietf-dhcpv6-types,ietf-inet-types,ietf-ip,iana-if-type,o-ran-interfaces,o-ran-supervision,o-ran-usermgmt,o-ran-hardware,          o-ran-fm,o-ran-operations,o-ran-file-management,o-ran-software-management,o-ran-processing-element,o-ran-compression-factors,o-ran-module-cap,                          o-ran-delay-management,          o-ran-laa-operations,o-ran-lbm,                                 o-ran-performance-management,o-ran-uplane-conf,o-ran-ald-port,o-ran-ald,o-ran-troubleshooting,o-ran-trace,o-ran-transceiver,o-ran-mplane-int,o-ran-dhcp,                 o-ran-sync,"
//#define ORAN_MODULE_LIST_FULL    "ietf-interfaces,iana-hardware,ietf-hardware,ietf-netconf-acm,ietf-crypto-types,ietf-dhcpv6-types,ietf-inet-types,ietf-ip,iana-if-type,o-ran-interfaces,o-ran-supervision,o-ran-usermgmt,o-ran-hardware,o-ran-fan,o-ran-fm,o-ran-operations,o-ran-file-management,o-ran-software-management,o-ran-processing-element,o-ran-compression-factors,o-ran-module-cap,o-ran-antenna-calibration,o-ran-delay-management,o-ran-laa,o-ran-laa-operations,o-ran-lbm,o-ran-udp-echo,o-ran-ecpri-delay,o-ran-performance-management,o-ran-uplane-conf,o-ran-ald-port,o-ran-ald,o-ran-troubleshooting,o-ran-trace,o-ran-transceiver,o-ran-mplane-int,o-ran-dhcp,o-ran-externalio,o-ran-sync,"

std::vector<std::string> YangModuleMgr::getModuleNamesConfigured(void)
{
	std::string moduleListStr = "\0";

#if defined (ORAN_MODULE_LIST_PHASE1)
	moduleListStr = ORAN_MODULE_LIST_PHASE1;
#elif defined (ORAN_MODULE_LIST_PHASE2)
	moduleListStr = ORAN_MODULE_LIST_PHASE2;
#elif defined (ORAN_MODULE_LIST_PHASE3)
	moduleListStr = ORAN_MODULE_LIST_PHASE3;
#elif defined (ORAN_MODULE_LIST_FULL)
	moduleListStr = ORAN_MODULE_LIST_FULL;
#else
	mYangCfg->listSupportedModules(moduleListStr);
#endif

	const std::string delimiters = ", \t\n\r";
	Tokeniser tokens(moduleListStr, delimiters);

	std::vector<std::string> modules(tokens.getTokens());

#if 0
	eventInfo("Configured modules: %lu", modules.size());
	for(uint32_t idx = 0; idx < modules.size(); idx++)
	{
		eventInfo("\tModule: %s", modules[idx].c_str());
	}
#endif

	return modules;
}

std::string YangModuleMgr::getPath(const std::string & moduleName, const std::string & xpath)
{
	std::string fullpath = "/" + moduleName + ":" + xpath;
	return fullpath;
}

//-------------------------------------------------------------------------------------------------------------
YangResult_E YangModuleMgr::enableFeatures(const std::string & name)
{
	YangResult_E result = YangResult_E::OK;

	// Get list of enabled features from parser
	std::map<std::string, bool> featureList;

	mYangCfg->listModuleFeatures(name, featureList);

	if (featureList.size() == 0)
	{
		eventInfo("Feature: NONE");
		return YangResult_E::OK;
	}

	// Enable/Disable each feature in from the list
	for (auto &feature : featureList)
	{
		if (feature.second == true)
		{
			if(mRadioDs->enableFeature(name, feature.first) != YangResult_E::OK)
			{
				eventError("Failed to enable %s module feature: %s", name.c_str(), feature.first.c_str());
				result = YangResult_E::FAIL;
			}
			else
			{
				eventInfo("Feature: %s - ENABLED", feature.first.c_str());
			}
		}
#if 0
		else
		{
			eventError("Feature: %s - DISABLED", feature.first.c_str());
		}
#endif
	}

	return result;
}
