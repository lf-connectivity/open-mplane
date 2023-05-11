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
	for (auto session : mSrSessions)
		session->session_stop();

	// sysrepo disconnection is handled in Connection destructor.
}

YangResult_E RadioDatastoreSysrepo::initialise(void)
{
	YangResult_E result = YangResult_E::OK;

	try
	{
#ifdef OFF_TARGET
		if (std::string(SYSREPO_REPO_PATH).empty())
			throw std::runtime_error("SYSREPO_REPO_PATH must be set in the projects CMakeLists.txt file.");
		if (std::string(SCRIPTS_PATH).empty())
			throw std::runtime_error("SCRIPTS_PATH must be set in the projects CMakeLists.txt file.");
		if (std::string(NETOPEER_PATH).empty())
			throw std::runtime_error("NETOPEER_PATH must be set in the projects CMakeLists.txt file.");


// ToDo: In host build, need to kill netopeer if it is running!
		// Install netopeer modules - mirrors the target netopeer startup script
		// Run script using "source", otherwise permission denied.
		const std::string scriptpath = SCRIPTS_PATH;
		const std::string scriptname = "installNetopeer.sh";
		const std::string cmdInstallNetopeer = "source " + scriptpath + "/" + scriptname + " " + SYSREPO_REPO_PATH + " " + NETOPEER_PATH + " " + SCRIPTS_PATH ;
		system(cmdInstallNetopeer.c_str());
#endif

		// Connect to the sysrepo datastore
		mSrConnection = std::make_shared<sysrepo::Connection>();

		if (!mSrConnection)
			result = YangResult_E::FAIL;

		setState(State_E::INITIALISED);
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "initialise()");
	}

	if(result != YangResult_E::OK)
		setState(State_E::SETUP_FAILURE);

	return result;
}

YangResult_E RadioDatastoreSysrepo::activate(void)
{
	YangResult_E result = YangResult_E::OK;

	if (!mSrConnection)
	{
		result = exceptionHandler(sr_error_t::SR_ERR_INTERNAL, "activate() - no connection");
	}
	else
	{
		try
		{
			// Reset connection to sysrepo datastore
			resetConnection();

			if (mSrConnection)
			{
				// Add datastore sessions for RUNNING and OPERATIONAL data
				std::vector<sr_datastore_t> sessionIds
				{
					SR_DS_RUNNING,
					SR_DS_OPERATIONAL,
				};
				for (auto sessionId : sessionIds)
				{
					std::shared_ptr<sysrepo::Session> session(std::make_shared<sysrepo::Session>(mSrConnection, sessionId));
					if (session)
					{
						mSrSessions.push_back(session);
					}
					else
					{
						result = exceptionHandler(sr_error_t::SR_ERR_INTERNAL, "activate() - no session");
					}
				}
				if (result == YangResult_E::OK)
				{
					result = RadioDatastore::activate();
				}
			}
			else
			{
				result = exceptionHandler(sr_error_t::SR_ERR_INTERNAL, "activate() - no connection");
			}
		}
		catch(const sysrepo::sysrepo_exception & exception)
		{
			result = exceptionHandler(exception, "activate()", true);
		}
	}

	if (result == YangResult_E::FAIL)
	{
		setState(State_E::SETUP_FAILURE);
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::getItem(const std::string & xpath, std::shared_ptr<YangParam>& param, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	param.reset() ;

	try
	{
		sysrepo::S_Val val = mSrSessions[datastoreId]->get_item(xpath.c_str());

		if (val == nullptr)
		{
			result = YangResult_E::NOT_FOUND;
		}
		else
		{
			switch (val->type()) {
			case SR_UNKNOWN_T:
			case SR_CONTAINER_T:
			case SR_CONTAINER_PRESENCE_T:
			case SR_LIST_T:
			case SR_LEAF_EMPTY_T:
				return YangResult_E::INVALID_TYPE ;

			default:
				break;
			}

			param = std::make_shared<YangParamSysrepo>(val);
		}
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "getItem()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::getItems(const std::string & xpath, std::shared_ptr<YangParams>& params, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	params.reset() ;

	try
	{
		sysrepo::S_Vals vals = mSrSessions[datastoreId]->get_items(xpath.c_str());

		if(vals == nullptr)
		{
			result = YangResult_E::NOT_FOUND;
		}
		else if (vals->val_cnt())
		{
			// Multiple
			params = std::make_shared<YangParams>() ;
			for(uint32_t idx = 0; idx < vals->val_cnt(); idx++)
			{
				sysrepo::S_Val val = vals->val(idx);
				switch (val->type()) {
				case SR_UNKNOWN_T:
				case SR_CONTAINER_T:
				case SR_CONTAINER_PRESENCE_T:
				case SR_LIST_T:
				case SR_LEAF_EMPTY_T:
					continue;

				default:
					break;
				}

				auto param = std::make_shared<YangParamSysrepo>(val) ;
				params->addParam(param) ;
			}
		}
		else
		{
			logDebugVerbose("GetItems " + xpath + " - No items returned");
		}
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "getItems()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::getListItems(const std::string & listXpath, std::vector<std::string>& keyValues, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		sysrepo::S_Vals vals = mSrSessions[datastoreId]->get_items(listXpath.c_str());

		if(vals == nullptr)
		{
			result = YangResult_E::NOT_FOUND;
		}
		else if (vals->val_cnt())
		{
			// Multiple
			for(uint32_t idx = 0; idx < vals->val_cnt(); idx++)
			{
				sysrepo::S_Val val = vals->val(idx);
				switch (val->type()) {
				case SR_LIST_T:
				{
					std::string listInstancePath = val->xpath();
					size_t listPathLen = listInstancePath.size();
					unsigned int pos = 0;

					// Loop through the string
					while (pos <= listPathLen)
					{
						// Key-value pair is between [ and ]
						size_t keyStartPos = listInstancePath.find_first_of('[', pos);
						size_t keyEndPos = listInstancePath.find_first_of(']', keyStartPos);

						if (keyStartPos != std::string::npos &&
							keyEndPos != std::string::npos)
						{
							std::string keyValuePair = listInstancePath.substr(keyStartPos + 1, keyEndPos - keyStartPos - 1);

							// Add the key-value pair to the reference parameter
							keyValues.push_back(keyValuePair);
						}
						else
						{
							break;
						}

						pos = keyEndPos;
					}
				}
				break;

				default:
					break;
				}
			}
		}
		else
		{
			logDebugVerbose("GetListItems " + listXpath + " - No items returned");
		}
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "getListItems()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::setItem(const std::string & xpath, std::shared_ptr<YangParam> param, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		std::shared_ptr<YangParamSysrepo> paramPtr(std::make_shared<YangParamSysrepo>(param)) ;
		sysrepo::S_Val val = paramPtr->getSysrepo();

		logDebugNormal("setItem() - " + xpath + "='" + val->to_string() + "'");

		mSrSessions[datastoreId]->set_item(xpath.c_str(), val);
		mSrSessions[datastoreId]->apply_changes();
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "setItem()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::setItemStr(const std::string &xpath, const std::string &value, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		logDebugNormal("setItemStr() - " + xpath + "='" + value + "'");

		mSrSessions[datastoreId]->set_item_str(xpath.c_str(), value.c_str());
		mSrSessions[datastoreId]->apply_changes();
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "setItemStr()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::setItems(const std::string & xpath, std::shared_ptr<YangParams> params, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		for(uint32_t i = 0; i < params->getNumParams(); i++)
		{
			std::shared_ptr<YangParamSysrepo> paramPtr(std::make_shared<YangParamSysrepo>(params->getParam(i))) ;
			sysrepo::S_Val value = paramPtr->getSysrepo();

			logDebugNormal("setItems() - " + xpath + "='" + value->to_string() + "'");

			mSrSessions[datastoreId]->set_item(xpath.c_str(), value);
		}
		mSrSessions[datastoreId]->apply_changes();
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "setItems()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::deleteItem(const std::string & xpath, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		mSrSessions[datastoreId]->delete_item(xpath.c_str());
		mSrSessions[datastoreId]->apply_changes();
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "deleteItem()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::sendNotification(const std::string &xpath, std::shared_ptr<YangParams> params, uint16_t datastoreId)
{
	YangResult_E result(YangResult_E::OK);

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		sysrepo::S_Vals in_vals(SysrepoUtils::paramsToVals(params)) ;
		mSrSessions[datastoreId]->event_notif_send(xpath.c_str(), in_vals);
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "sendNotification()");
	}

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
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		sysrepo::S_Subscribe subscribe(new sysrepo::Subscribe(mSrSessions[datastoreId]));
		subscribe->oper_get_items_subscribe(moduleName.c_str(), path.c_str(), callback, privateData);
		mSubscriptions.push_back(subscribe) ;
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "getItemsSubscribe()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::itemsChangeSubscribe(const std::string &moduleName, sysrepo::S_Callback callback,
		const std::string& xpath, void *privateData, sr_subscr_flag_t subscribeFlag, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		sysrepo::S_Subscribe subscribe(new sysrepo::Subscribe(mSrSessions[datastoreId]));
		const char* xp = nullptr ;
		if (!xpath.empty())
			xp = xpath.c_str() ;
		subscribe->module_change_subscribe(moduleName.c_str(), callback, xp, privateData, 0, subscribeFlag);
		mSubscriptions.push_back(subscribe) ;
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "itemsChangeSubscribe()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::rpcSubscribe(const std::string &path, sysrepo::S_Callback callback, uint16_t datastoreId)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	try
	{
		sysrepo::S_Subscribe subscribe(new sysrepo::Subscribe(mSrSessions[datastoreId]));
		subscribe->rpc_subscribe(path.c_str(), callback);
		mSubscriptions.push_back(subscribe) ;
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "rpcSubscribe()");
	}

	return result;
}

YangResult_E RadioDatastoreSysrepo::createListEntry(const std::string &xpath,
		std::map<std::string, std::string> values,
		uint16_t datastoreId)
{
	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	YangResult_E result(YangResult_E::FAIL);
	try
	{
		mSrSessions[datastoreId]->set_item(xpath.c_str());
		for (auto entry : values)
		{
			std::string path(xpath + "/" + entry.first) ;

			logDebugNormal("createListEntry() - " + path + "='" + entry.second + "'");

			mSrSessions[datastoreId]->set_item_str(path.c_str(), entry.second.c_str());
		}
		mSrSessions[datastoreId]->apply_changes();

		result = YangResult_E::OK;
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "createListEntry()", true);
	}
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
	if (!isState(State_E::ACTIVE))
		return YangResult_E::FAIL;
	if (datastoreId >= mSrSessions.size())
		return YangResult_E::FAIL;
	if (!mSrSessions[datastoreId])
		return YangResult_E::FAIL;

	YangResult_E result(YangResult_E::FAIL);
	try
	{
		mSrSessions[datastoreId]->set_item(xpath.c_str());
		for (auto entry : values)
		{
			std::string path(xpath + "/" + entry.first) ;

			if (entry.second != nullptr)
			{
				logDebugNormal("createListEntry() - " + path + "='" + *entry.second + "'");

				mSrSessions[datastoreId]->set_item_str(path.c_str(), (entry.second)->c_str());
			}
			else
			{
				logDebugNormal("createListEntry() - " + path);

				mSrSessions[datastoreId]->set_item(path.c_str());
			}
		}
		mSrSessions[datastoreId]->apply_changes();

		result = YangResult_E::OK;
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "createListEntry()", false);
	}
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
	if (!mSrConnection)
		return YangResult_E::FAIL;

	std::string modulePathName = path + "/" + filename;

	const char * pathp(nullptr);
	if( !path.empty() && (path != ".") )
	{
		pathp = path.c_str();
	}

	//eventInfo("Installing: %s", modulePathName.c_str());
	try
	{
// ToDo: Fix module installation to enable features correctly
		// Install module
		mSrConnection->install_module(modulePathName.c_str(), pathp, features);

		// Add installed module to installed list
		addInstalledModule(name);

		// Reset connection install module
		result = resetConnection();
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "installModule()", true);
		if(result == YangResult_E::EXISTS)
			result = YangResult_E::OK;
	}

	return result;
}

// Uninstall Module
YangResult_E RadioDatastoreSysrepo::uninstallModule(const std::string & name)
{
	YangResult_E result = YangResult_E::OK;

	setState(State_E::CONFIGURING);

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;
	if (!mSrConnection)
		return YangResult_E::FAIL;

	//eventInfo("Uninstalling : %s", name.c_str());
	try
	{
		mSrConnection->remove_module(name.c_str());
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "uninstallModule()", true);
	}

	return result;
}

// Enable module data
YangResult_E RadioDatastoreSysrepo::installModuleData(const std::string & name, const std::string & data, const std::string & data_path)
{
	YangResult_E result = YangResult_E::OK;

	setState(State_E::CONFIGURING);

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;
	if (!mSrConnection)
		return YangResult_E::FAIL;

	try
	{
		if (data == "")
		{
			//eventInfo("Installing module %s data from %s", name.c_str(), data_path.c_str());
			mSrConnection->install_module_data(name.c_str(), NULL, data_path.c_str(), LYD_FORMAT::LYD_XML);
		}
		else
		{
			//eventInfo("Installing module %s data: %s", name.c_str(), data.c_str());
			mSrConnection->install_module_data(name.c_str(), data.c_str(), NULL, LYD_FORMAT::LYD_XML);
		}
		result = YangResult_E::OK;
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "installModuleData()", true);
	}

	return result;
}

// Enable module feature
YangResult_E RadioDatastoreSysrepo::enableFeature(const std::string & name, const std::string & feature)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;
	if (!mSrConnection)
		return YangResult_E::FAIL;

	//eventInfo("Enable %s feature: %s", name.c_str(), feature.c_str());
	try
	{
		mSrConnection->enable_module_feature(name.c_str(), feature.c_str());
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		eventError("Enable %s feature: %s", name.c_str(), feature.c_str());
		result = exceptionHandler(exception, "enableFeature()", true);
	}

	return result;
}

// Disable module feature
YangResult_E RadioDatastoreSysrepo::disableFeature(const std::string & name, const std::string & feature)
{
	YangResult_E result = YangResult_E::OK;

	if (!isState(State_E::CONFIGURING))
		return YangResult_E::FAIL;
	if (!mSrConnection)
		return YangResult_E::FAIL;

	//eventInfo("Disable %s feature: %s", name.c_str(), feature.c_str());
	try
	{
		mSrConnection->disable_module_feature(name.c_str(), feature.c_str());
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "disableFeature()", true);
	}

	return result;
}


bool RadioDatastoreSysrepo::isModuleInstalled(const std::string& name) const
{
	libyang::S_Context lyContext(mSrConnection->get_context()) ;
	libyang::S_Module module(lyContext->get_module(name.c_str(), nullptr, 0)) ;
	if (!module)
		return false ;

	/*
	 * Implemented = 0 means imported (i)
	 * Implemented = 1 means implemented (I)
	 *
	 * so actually we can accept either
	 *
	 */
//	if (module->implemented() == 0)
//		return false ;

	return true ;
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
	return exceptionHandler(exception.error_code(), desc, halt);
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
	if (!mSrConnection)
		return YangResult_E::FAIL;

	eventInfo("Datastore resetting sysrepo connection");
	try
	{
		// Force disconnection from the sysrepo datastore
		mSrConnection.reset();

		// Reconnect to the sysrepo datastore
		if (!mSrConnection)
			mSrConnection = std::make_shared<sysrepo::Connection>();
	}
	catch(const sysrepo::sysrepo_exception & exception)
	{
		result = exceptionHandler(exception, "resetConnection()");
	}

	return result;
}
