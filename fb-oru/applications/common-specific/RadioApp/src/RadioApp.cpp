/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioApp.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdio.h>
#include <unistd.h>

#include "ILoggable.h"
#include "IAppSettings.h"
#include "IAppSettingsFactory.h"
#include "IAppOptions.h"
#include "IAppControl.h"
#include "IRadio.h"
#include "IAlarmsList.h"
#include "IFaultsList.h"

#include "CommonPostInit.h"

#ifdef OFF_TARGET
#ifdef BUILD_IF_CPRI
#include "CpriFibreEmu.h"
#endif
#include "ISpiEmu.h"
#include "LatchedAlarmEmu.h"
#include "LatchedAntennaAlarmEmu.h"
#endif

#include "IBootTimer.h"
#include "RadioApp.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRadioPostInit> IRadioPostInit::getInterface(void)
{
	// Just use the common object
    return CommonPostInit::getInterface() ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RadioApp::RadioApp() :
	Application(),
	mRadioPostInit()
#ifdef OFF_TARGET
#ifdef BUILD_IF_CPRI
	,mFibreEmu()
#endif
	,mSpiEmu(ISpiEmu::getInstance())
	,mLatchedAlarmEmu(std::make_shared<LatchedAlarmEmu>())
	,mAntAlarmEmu()
#endif
{
#ifdef OFF_TARGET
#ifdef BUILD_IF_CPRI
#define MAX_FIBRES 2
// Create emulators for the cpri fibre fpga interface on each fibre
for (unsigned fibre=0; fibre < MAX_FIBRES; ++fibre)
{
	// Allow 2 socket connections to each fibre emulator
	mFibreEmu.push_back(std::make_shared<CpriFibreEmu>(fibre, 2)) ;
}
#endif

#define MAX_ANTENNAS 2
// Create emulators for the antenna latched alarms on each antenna
for (unsigned ant=0; ant < MAX_ANTENNAS; ++ant)
{
	mAntAlarmEmu.push_back(std::make_shared<LatchedAntennaAlarmEmu>(ant)) ;
}
#endif

}

//-------------------------------------------------------------------------------------------------------------
RadioApp::~RadioApp()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int RadioApp::appOptions(
		const std::string& name,
		int argc, const char** argv,
		const std::vector<std::shared_ptr<IAppOptionSpec> >& extraOptions)
{
	std::vector<std::shared_ptr<IAppOptionSpec> > radioOptions(extraOptions) ;

	radioOptions.push_back(
		IAppOptionSpec::factory("ethbb",  DataVariantType::String, "Ethernet interface name (over baseband)", "eth1", "ETHBB")
	) ;
	radioOptions.push_back(
		IAppOptionSpec::factory("ethcdi", DataVariantType::String, "Ethernet interface name (control and debug)", "eth0", "ETHCDI")
	) ;
	radioOptions.push_back(
		IAppOptionSpec::factory("netopeerdbg", DataVariantType::Int, "NETCONF server debug level (0-2)", "1", "NETCONFDBG")
	) ;
//	radioOptions.push_back(
//		IAppOptionSpec::factory("maxtxpower", DataVariantType::Float, "Maximum transmit power (dB)", "43.1", "TXPORTPOWER")
//	) ;

	return Application::appOptions(name, argc, argv, radioOptions) ;
}

//-------------------------------------------------------------------------------------------------------------
int RadioApp::appInit()
{
	// Ensure Alarms and Faults are created
	std::shared_ptr<Mplane::IAlarmsList> alarmsList(Mplane::IAlarmsList::getInstance()) ;
	std::shared_ptr<Mplane::IFaultsList> faultsList(Mplane::IFaultsList::getInstance()) ;
	(void)alarmsList ;
	(void)faultsList ;

	int rc = Application::appInit() ;
	if (rc != 0)
		return rc ;

	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int RadioApp::appPostInit()
{
	int rc = Application::appPostInit() ;
	if (rc != 0)
		return rc ;

	// call the post init object
	mRadioPostInit = IRadioPostInit::getInterface();

	ReturnType::State state = (*mRadioPostInit)();
	if (state != ReturnType::RT_OK)
		return static_cast<int>(state) ;

	return 0 ;
}
