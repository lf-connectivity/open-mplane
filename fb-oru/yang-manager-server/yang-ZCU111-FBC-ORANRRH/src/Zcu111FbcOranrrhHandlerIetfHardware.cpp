/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerIetfHardware.cpp
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
#include <memory>

#include "IAppSettingsFactory.h"
#include "ILoggable.h"
#include "IBootEnv.h"
#include "YangMgrServer.h"
#include "SysrepoGetitemsCallback.h"

#include "Zcu111FbcOranrrhHandlerIetfHardware.h"

using namespace Mplane;
using namespace std;

const std::string Zcu111FbcOranrrhHandlerIetfHardware::mRadioCardHardwareName("radioCard");

/*
 module: ietf-hardware
 +--rw hardware
 +--rw component* [name]
 +--rw name                            string									Radio card
 +--rw class                           identityref								"module" from https://tools.ietf.org/html/rfc6933 OBJECT entPhysicalClass
 +--ro description?                    string									Mplane ORAN Remote Radio Head
 +--ro firmware-rev?                   string									FPGA system regs read combination of read_fpgaBuildNum() and read_fpgaBuildNum()
 +--ro software-rev?                   string									IAppSettings for "Board-Customer-Application-Version-Build"
 +--ro serial-num?                     string									I2C env variable "hwBoardSerialNum"
 +--ro mfg-name?                       string									Mplane
 +--ro model-name?                     string									IAppSettings for "Board-Customer-Application"
 +--ro is-fru?                         boolean									False
 +--ro o-ran-hw:label-content
 |  +--ro o-ran-hw:model-name?    boolean										True
 |  +--ro o-ran-hw:serial-number? boolean										True
 +--ro o-ran-hw:product-code           string									I2C env variable "productCode"
 +--rw o-ran-hw:o-ran-name             leafref									Please double check but this might be O-RU-COMPONENT
 */

//=============================================================================================================
// LOCAL
//=============================================================================================================
//=============================================================================================================
// PUBLIC
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerIetfHardware::Zcu111FbcOranrrhHandlerIetfHardware(std::shared_ptr<IYangModuleMgr> moduleMgr)
: YangHandlerSysrepo("ietf-hardware", moduleMgr, "Zcu111FbcOranrrhHandlerIetfHardware")
, mCallback(std::make_shared <SysrepoGetitemsCallback> (path("hardware")))
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfHardware::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false;

	// Grab all firmware & software revision from other parts of the program(works)
	auto appSettings = IAppSettingsFactory::getInterface();
	string firmwareRev = appSettings->getFpgaPart() + "-" + appSettings->getFpgaBuild();
	string buildNumber = to_string(appSettings->getBuildNumber());
	string softwareRev = appSettings->getBoard() + "-" + appSettings->getCustomerString() + "-";
	softwareRev += appSettings->getAppString() + "-" + appSettings->getBuildVersion() + "-" + buildNumber;


	// Grab serial number from i2cenv(works)
	const string ENV_SERIALNUM = "hwBoardSerialNum";
	auto bootEnv(IBootEnv::getInstance());
	string serialNumber = bootEnv->getVar(ENV_SERIALNUM);

	// Add radio card RW information(works)
	map<string, string> themap;
	themap["component[name='" + mRadioCardHardwareName + "']/class"] = "o-ran-hardware:O-RAN-RADIO";		// This line works as long as o-ran-name set up
	themap["component[name='" + mRadioCardHardwareName + "']/o-ran-hardware:o-ran-name"] = mRadioCardHardwareName;	// A leafref for 'name'
	createListEntry(mCallback->path(), themap);

	// Add the read only nodes
	auto component = mCallback->addContainer("component");
	component->addLeaf("name", mRadioCardHardwareName);//Without this netopeer crashes with. sr_lyd_child: Assertion `child->schema == (struct lys_node *)slist->keys[i]' failed
											//Yet this is meant to be a RW node, and setting the 'name' to 'radioCard' above is not enough
	component->addLeaf("description", "Mplane ORAN Remote Radio Head");
	component->addLeaf("firmware-rev", firmwareRev);		// combination of IAppSettings getFpgaPart() and getFpgaBuild().
	component->addLeaf("software-rev", softwareRev);		// IAppSettings for "Board-Customer-Application-Version-Build"
	component->addLeaf("serial-num", serialNumber);			// I2C env variable "hwBoardSerialNum"
	component->addLeaf("mfg-name", "Mplane");
	component->addLeafBool("is-fru", false);

	// Add in the augmented RO nodes
	component->addLeaf("o-ran-hardware:product-code", PRODUCT_CODE);
	auto labelContent = component->addContainer("o-ran-hardware:label-content");
	labelContent->addLeafBool("o-ran-hardware:model-name", true);
	labelContent->addLeafBool("o-ran-hardware:serial-number", true);

	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe();
	logDebugVerbose("oran hardware done");

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerIetfHardware::valueChange(const std::string &xpath,
		std::shared_ptr<YangParam> oldValue,
		std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerIetfHardware::valueChange() - %s", xpath.c_str());
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
