/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanAldPort.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <string>
#include <algorithm>

#include "stringfunc.hpp"

#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "Zcu111FbcOranrrhHandlerORanAldPort.h"
#include "RadioDatastoreSysrepo.h"
#include "IRadio.h"
#include "CommonAldPort.h"


using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanAldPort::Zcu111FbcOranrrhHandlerORanAldPort(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-ald-port", moduleMgr, "Zcu111FbcOranrrhHandlerORanAldPort")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path("ald-ports-io")))
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanAldPort::~Zcu111FbcOranrrhHandlerORanAldPort()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanAldPort::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	int numPorts = IRadioFactory::getInterface()->getNumberOfAldPorts();
	for (int index = 0; index < numPorts; index++)
	{
		createReadWriteData(index);
		createReadOnlyData(index);
		registerOverCurrent(index);
		initDcStatus(index);
	}

	// Add the over current supported leaf
	auto overCurrentSupportFunc = [this](const std::string& leafName)->std::string {
		IAldPort& aldPort = IRadioFactory::getInterface()->getAldPort(0);
		return (aldPort.isOvercurrentDetectionSupported() ? "true" : "false");
	} ;

	std::shared_ptr<ILeafContainer> parent(mCallback) ;
	parent->addLeaf("over-current-supported", overCurrentSupportFunc);

	// Register callbacks
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe() ;

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanAldPort::valueChange(const std::string & xpath,
                                                       std::shared_ptr<YangParam> oldValue,
                                                       std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanAldPort::valueChange() - %s", xpath.c_str());
	std::string error ;

	std::string listName ;
	std::string key ;
	std::string index ;
	std::string value ;
	std::string leaf ;
	bool isList = false;

	if (oldValue)
	{
		value = YangParamUtils::toString(oldValue, error) ;
		//std::cerr << " + OLD: " << oldValue->name() << " = " << value << std::endl ;
		isList = listIndex(oldValue->name(), listName, key, index) ;
		leaf = leafName(oldValue->name()) ;
	}
	if (newValue)
	{
		value = YangParamUtils::toString(newValue, error) ;
		//std::cerr << " + NEW: " << newValue->name() << " = " << value << std::endl ;
		isList = listIndex(newValue->name(), listName, key, index) ;
		leaf = leafName(newValue->name()) ;
	}

	if ( isList)
	{
		if (listName == "ald-port-dc-control")
		{
			if (leaf == "dc-enabled")
			{
				// Set the DC enable/disable
				int portIndex = getAldPortIndexFromName(index);
				IAldPort& aldPort = IRadioFactory::getInterface()->getAldPort(portIndex);
				aldPort.setDCPower(value == "true" ? true : false);

				monitorDcStatus();
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanAldPort::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	int ret = SR_ERR_OK;

	for (unsigned i=0; i < params->getNumParams(); ++i)
	{
		std::shared_ptr<YangParam> param(params->getParam(i)) ;

		std::string listName ;
		std::string key ;
		std::string index ;
		std::string error;
		std::string leaf;
		bool isList = false;

		isList = listIndex(param->name(), listName, key, index) ;
		leaf = leafName(param->name());

		if (isList)
		{
			if (listName == "ald-port-dc-control")
			{
				if (leaf == "dc-enabled")
				{
					int portIndex = getAldPortIndexFromName(index);
					// If port does not exist, then return error
					if (portIndex < 0)
					{
						ret = SR_ERR_VALIDATION_FAILED;
						break;
					}
				}
			}
		}
	}
	return ret ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanAldPort::createReadOnlyData(int index)
{
	//	module: o-ran-ald-port
	//	  +--rw ald-ports-io
	//	     +--ro over-current-supported? boolean
	//	     +--ro ald-port* [name]
	//	     |  +--ro name                 string
	//	     |  +--ro port-id              uint8
	//	     |  +--ro dc-control-support   boolean
	//	     |  +--ro dc-enabled-status?   boolean
	//	     |  +--ro supported-connector  enumeration
	//	     +--rw ald-port-dc-control* [name]
	//	        +--rw name        leafref
	//	        +--rw dc-enabled? boolean

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	std::vector< std::shared_ptr<IAldPort> > ports = IAldPortFactory::getPorts();
	std::string name = std::dynamic_pointer_cast<CommonAldPort>(ports[index])->getName();

	auto aldPortList = parent->addContainerList("ald-port");
	aldPortList->addLeaf("name", name);
	aldPortList->addLeaf("port-id", std::to_string(index));

	auto dcControlSupportFunc = [this, index](const std::string& leafName)->std::string {
		IAldPort& aldPort = IRadioFactory::getInterface()->getAldPort(index);
		return (aldPort.isDCPowerControlSupported() ? "true" : "false");
	} ;

	auto dcEnableStatusFunc = [this, index](const std::string& leafName)->std::string {
		IAldPort& aldPort = IRadioFactory::getInterface()->getAldPort(index);
		return (aldPort.isDCPowerOn() ? "true" : "false");
	} ;

	aldPortList->addLeaf("dc-control-support", dcControlSupportFunc);
	aldPortList->addLeaf("dc-enabled-status", dcEnableStatusFunc);
	aldPortList->addLeaf("supported-connector", "RS485_PORT");

}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanAldPort::createReadWriteData(int index)
{
//	module: o-ran-ald-port
//	  +--rw ald-ports-io
//	     +--ro over-current-supported? boolean
//	     +--ro ald-port* [name]
//	     |  +--ro name                 string
//	     |  +--ro port-id              uint8
//	     |  +--ro dc-control-support   boolean
//	     |  +--ro dc-enabled-status?   boolean
//	     |  +--ro supported-connector  enumeration
//	     +--rw ald-port-dc-control* [name]
//	        +--rw name        leafref
//	        +--rw dc-enabled? boolean

	IAldPort& aldPort = IRadioFactory::getInterface()->getAldPort(index);
	std::vector< std::shared_ptr<IAldPort> > ports = IAldPortFactory::getPorts();
	std::string name = std::dynamic_pointer_cast<CommonAldPort>(ports[index])->getName();
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	std::string aldPortDcControl = mCallback->path() + "/ald-port-dc-control";
	ds->createListEntry(aldPortDcControl, "name", name,
			std::map<std::string, std::string>{
				{"dc-enabled", (aldPort.isDCPowerOn() ? "true" : "false")}
			});
}

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanAldPort::getAldPortIndexFromName(std::string name)
{
	std::vector< std::shared_ptr<IAldPort> > ports = IAldPortFactory::getPorts();

	int numPorts = IRadioFactory::getInterface()->getNumberOfAldPorts();
	for (int index = 0; index < numPorts; index++)
	{
		std::string portName = std::dynamic_pointer_cast<CommonAldPort>(ports[index])->getName();
		if (portName == name)
		{
			return index;
		}
	}

	return -1;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanAldPort::registerOverCurrent(int index)
{
	IAldPort& aldPort = IRadioFactory::getInterface()->getAldPort(index);

	if (aldPort.isOvercurrentDetectionSupported())
	{
		auto overCurrentCb = [this, index](bool overCurrent){
//			  notifications:
//			    +---n overcurrent-report         {OVERCURRENT-SUPPORTED}?
//			    |  +--ro overload-condition
//			    |     +--ro overloaded-ports* leafref

			if (overCurrent)
			{
				const std::string notifPath( path("overcurrent-report") ) ;

				std::vector< std::shared_ptr<IAldPort> > ports = IAldPortFactory::getPorts();
				std::string name = std::dynamic_pointer_cast<CommonAldPort>(ports[index])->getName();

				std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;

				params->addParam(name, notifPath + "/overload-condition/overloaded-ports") ;

				sendNotification(notifPath, params) ;
			}
		};
		aldPort.registerOvercurrentCb(overCurrentCb);
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanAldPort::initDcStatus(int index)
{
	// Create a map of DC power status to send notifications later on
	IAldPort& aldPort = IRadioFactory::getInterface()->getAldPort(index);
	std::vector< std::shared_ptr<IAldPort> > ports = IAldPortFactory::getPorts();
	std::string name = std::dynamic_pointer_cast<CommonAldPort>(ports[index])->getName();

	mAldPortDcStatus[name] = aldPort.isDCPowerOn();
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanAldPort::monitorDcStatus(void)
{
	bool sendNotif = false;

	//			    +---n dc-enabled-status-change
	//			       +--ro ald-port* [name]
	//			          +--ro name               leafref
	//			          +--ro dc-enabled-status? leafref
	const std::string notifPath( path("dc-enabled-status-change") ) ;

	std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;

	int numPorts = IRadioFactory::getInterface()->getNumberOfAldPorts();
	for (int index = 0; index < numPorts; index++)
	{
		IAldPort& aldPort = IRadioFactory::getInterface()->getAldPort(index);
		std::vector< std::shared_ptr<IAldPort> > ports = IAldPortFactory::getPorts();
		std::string name = std::dynamic_pointer_cast<CommonAldPort>(ports[index])->getName();

		// If name if found, then check if the port status has changed
		if (mAldPortDcStatus.find(name) != mAldPortDcStatus.end())
		{
			bool status = aldPort.isDCPowerOn();
			if (status != mAldPortDcStatus[name])
			{
				std::string listName = notifPath + "/ald-port[name='" + name + "']";
				params->addParam(name, listName + "/name") ;
				params->addParam((status == true ? "true" : "false"), listName + "/dc-enabled-status") ;

				sendNotif = true;
				mAldPortDcStatus[name] = status;
			}
		}
	}

	if (sendNotif)
	{
		sendNotification(notifPath, params);
	}
}
