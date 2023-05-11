/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerMgr.cpp
 * \brief     Sets up the handlers for a variety of RU modules.
 *
 *
 * \details   Registered handlers are stored in a vector for the class.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Zcu111FbcOranrrhHandlerMgr.h"

#include "Zcu111FbcOranrrhHandlerIetfHardware.h"
#include "Zcu111FbcOranrrhHandlerIetfInterfaces.h"
#include "Zcu111FbcOranrrhHandlerIetfNetconfAcm.h"
#include "Zcu111FbcOranrrhHandlerIetfNetconfServer.h"
#include "Zcu111FbcOranrrhHandlerORanUplaneConf.h"
#include "Zcu111FbcOranrrhHandlerORanProcessingElement.h"
#include "Zcu111FbcOranrrhHandlerORanModuleCap.h"
#include "Zcu111FbcOranrrhHandlerORanSync.h"
#include "Zcu111FbcOranrrhHandlerORanDelayManagement.h"
#include "Zcu111FbcOranrrhHandlerORanDhcp.h"
#include "Zcu111FbcOranrrhHandlerORanMplaneInt.h"
#include "Zcu111FbcOranrrhHandlerORanOperations.h"
#include "Zcu111FbcOranrrhHandlerORanFm.h"
#include "Zcu111FbcOranrrhHandlerORanSupervision.h"
#include "Zcu111FbcOranrrhHandlerORanFileManagement.h"
#include "Zcu111FbcOranrrhHandlerORanTransceiver.h"
#include "Zcu111FbcOranrrhHandlerORanSoftwareManagement.h"
#include "Zcu111FbcOranrrhHandlerORanPerformanceMgmt.h"
#include "Zcu111FbcOranrrhHandlerORanUserMgmt.h"
#include "Zcu111FbcOranrrhHandlerORanLbm.h"
#include "Zcu111FbcOranrrhHandlerORanTroubleshooting.h"
#include "Zcu111FbcOranrrhHandlerORanTrace.h"
#include "Zcu111FbcOranrrhHandlerORanAldPort.h"
#include "Zcu111FbcOranrrhHandlerORanAld.h"


using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangHandlerMgr> IYangHandlerMgr::create(std::shared_ptr<IYangModuleMgr> moduleMgr)
{
	static std::shared_ptr<IYangHandlerMgr> instance(std::make_shared<Zcu111FbcOranrrhHandlerMgr>(moduleMgr)) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangHandlerMgr> IYangHandlerMgr::singleton()
{
	// pass in dummy (unused) variable
	return create(std::shared_ptr<IYangModuleMgr>()) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerMgr::Zcu111FbcOranrrhHandlerMgr(std::shared_ptr<IYangModuleMgr> moduleMgr) :
	YangHandlerMgr(moduleMgr)
{
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerIetfInterfaces>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerIetfNetconfAcm>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerIetfNetconfServer>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanUplaneConf>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanProcessingElement>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanModuleCap>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanSync>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanDelayManagement>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanDhcp>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanMplaneInt>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanOperations>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerIetfHardware>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanFm>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanSupervision>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanTransceiver>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanFileManagement>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanSoftwareManagement>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanPerformanceMgmt>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanUserMgmt>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanLbm>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanTroubleshooting>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanTrace>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanAldPort>(moduleMgr));
	registerHandler(std::make_shared<Zcu111FbcOranrrhHandlerORanAld>(moduleMgr));

}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerMgr::~Zcu111FbcOranrrhHandlerMgr()
{
}
