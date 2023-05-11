/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioDatastoreSysrepo.cpp
 * \brief     Radio datastore for sysrepo datastores
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

// *****************************************************************************
// Includes
// *****************************************************************************
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <string.h>

#include "Path.h"
#include "RadioDatastoreSysrepo.h"
#include "YangParamUtils.h"
#include "SysrepoUtils.h"
#include "YangParamSysrepo.h"

using namespace Mplane;

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// sysrepo Radio Datastore
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        RadioDatastoreSysrepo
// Description:  sysrepo Radio Datastore driver class.
// -----------------------------------------------------------------------------

//=============================================================================================================
// PUBLIC
//=============================================================================================================

RadioDatastoreSysrepo::RadioDatastoreSysrepo()
	: RadioDatastore()
{
}

RadioDatastoreSysrepo::~RadioDatastoreSysrepo()
{
}

YangResult_E RadioDatastoreSysrepo::initialise(void)
{
	YangResult_E result = YangResult_E::OK;

	setState(State_E::INITIALISED);

	return result;
}

YangResult_E RadioDatastoreSysrepo::activate(void)
{
	YangResult_E result = YangResult_E::OK;

	result = RadioDatastore::activate();

	return result;
}

YangResult_E RadioDatastoreSysrepo::getItem(const std::string & xpath, std::shared_ptr<YangParam>& param, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::getItems(const std::string & xpath, std::shared_ptr<YangParams>& params, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::getListItems(const std::string & listXpath, std::vector<std::string>& keyValues, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::setItem(const std::string & xpath, std::shared_ptr<YangParam> param, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::setItemStr(const std::string &xpath, const std::string &value, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::setItems(const std::string & xpath, std::shared_ptr<YangParams> params, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::deleteItem(const std::string & xpath, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::sendNotification(const std::string &xpath, std::shared_ptr<YangParams> params, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::getItemsSubscribe(
		const std::string &moduleName, const std::string &path,
		sysrepo::S_Callback callback, void *privateData,
		uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::itemsChangeSubscribe(const std::string &moduleName, sysrepo::S_Callback callback,
		const std::string& xpath, void *privateData, sr_subscr_flag_t subscribeFlag, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::rpcSubscribe(const std::string &path, sysrepo::S_Callback callback, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::createListEntry(const std::string &xpath,
		std::map<std::string, std::string> values,
		uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::createListEntry(const std::string &xpath, const std::string &key,
		const std::string &keyval, std::map<std::string, std::string> values,
		uint16_t datastoreId)
{
	std::string path(xpath + "[" + key + "='" + keyval + "']") ;
	std::map<std::string, std::string> valuesWithKey(values) ;
	return createListEntry(path, valuesWithKey, datastoreId) ;
}

YangResult_E RadioDatastoreSysrepo::createListEntry(const std::string & xpath,
			std::map<std::string, std::shared_ptr<std::string>> values,
			uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;

	return result;
}

YangResult_E RadioDatastoreSysrepo::createListEntry(const std::string & xpath, const std::string& key, const std::string& keyval,
			std::map<std::string, std::shared_ptr<std::string>> values,
			uint16_t datastoreId)
{
	std::string path(xpath + "[" + key + "='" + keyval + "']") ;
	std::map<std::string, std::shared_ptr<std::string>> valuesWithKey(values) ;
	return createListEntry(path, valuesWithKey, datastoreId) ;
}

// ToDo: Update to pass in and set optional startup data.
// Install Module
YangResult_E RadioDatastoreSysrepo::installModule(const std::string & name, const std::string & path,
		const std::string & filename, std::vector<std::string> features)
{
	YangResult_E result = YangResult_E::OK;

	setState(State_E::CONFIGURING);

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;

	return result;
}

// Uninstall Module
YangResult_E RadioDatastoreSysrepo::uninstallModule(const std::string & name)
{
	YangResult_E result = YangResult_E::OK;

	setState(State_E::CONFIGURING);

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;

	return result;
}

// Enable module data
YangResult_E RadioDatastoreSysrepo::installModuleData(const std::string & name, const std::string & data, const std::string & data_path)
{
	YangResult_E result = YangResult_E::OK;

	setState(State_E::CONFIGURING);

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;

	return result;
}

// Enable module feature
YangResult_E RadioDatastoreSysrepo::enableFeature(const std::string & name, const std::string & feature)
{
	YangResult_E result = YangResult_E::OK;

	setState(State_E::CONFIGURING);

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;

	return result;
}

// Disable module feature
YangResult_E RadioDatastoreSysrepo::disableFeature(const std::string & name, const std::string & feature)
{
	YangResult_E result = YangResult_E::OK;

	setState(State_E::CONFIGURING);

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;

	return result;
}


bool RadioDatastoreSysrepo::isModuleInstalled(const std::string& name) const
{
	return true;
}

std::string RadioDatastoreSysrepo::typeStr(sr_error_t type)
{
	switch(type)
	{
		case SR_ERR_OK:                return "SR_ERR_OK";
		case SR_ERR_INVAL_ARG:         return "SR_ERR_INVAL_ARG";
		case SR_ERR_LY:                return "SR_ERR_LY";
		case SR_ERR_SYS:               return "SR_ERR_SYS";
		case SR_ERR_NOMEM:             return "SR_ERR_NOMEM";
		case SR_ERR_NOT_FOUND:         return "SR_ERR_NOT_FOUND";
		case SR_ERR_EXISTS:            return "SR_ERR_EXISTS";
		case SR_ERR_INTERNAL:          return "SR_ERR_INTERNAL";
		case SR_ERR_UNSUPPORTED:       return "SR_ERR_UNSUPPORTED";
		case SR_ERR_VALIDATION_FAILED: return "SR_ERR_VALIDATION_FAILED";
		case SR_ERR_OPERATION_FAILED:  return "SR_ERR_OPERATION_FAILED";
		case SR_ERR_UNAUTHORIZED:      return "SR_ERR_UNAUTHORIZED";
		case SR_ERR_LOCKED:            return "SR_ERR_LOCKED";
		case SR_ERR_TIME_OUT:          return "SR_ERR_TIME_OUT";
		case SR_ERR_CALLBACK_FAILED:   return "SR_ERR_CALLBACK_FAILED";
		case SR_ERR_CALLBACK_SHELVE:   return "SR_ERR_CALLBACK_SHELVE";
	}
	return "<<INVALID>>";
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

YangResult_E RadioDatastoreSysrepo::exceptionHandler(const sysrepo::sysrepo_exception & exception, const std::string & desc, bool halt)
{
	return YangResult_E::OK;
}

YangResult_E RadioDatastoreSysrepo::exceptionHandler(sr_error_t errType, const std::string & desc, bool halt)
{
	YangResult_E result = YangResult_E::OK;

	if(errType == SR_ERR_EXISTS)
	{
		//eventWarning("Datastore exception (%s): %s", typeStr(errType).c_str(), desc.c_str());
		result = YangResult_E::EXISTS;
	}
	else if(errType != SR_ERR_OK)
	{
		eventError("Datastore exception (%s): %s", typeStr(errType).c_str(), desc.c_str());
		result = YangResult_E::FAIL;
		if (halt) { throw; }
	}

	return result;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
YangResult_E RadioDatastoreSysrepo::resetConnection(void)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;

	eventInfo("Datastore resetting sysrepo connection");

	return result;
}
