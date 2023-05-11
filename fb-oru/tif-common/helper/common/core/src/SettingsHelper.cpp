/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SettingsHelper.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "xstringfunc.hpp"
#include "IDataVariantSettings.h"

#include "IRadio.h"
#include "IFibre.h"
#include "ICarrier.h"
#include "ICalDownloadManagement.h"

#include "SettingsHelper.h"

// Use the build-specific config file to determine feature settings
#include "config.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::SettingsHelper::SettingsHelper()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SettingsHelper::~SettingsHelper()
{
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::SettingsHelper::commonSettings()
{
	std::shared_ptr<IDataVariantSettings> settings(IDataVariantSettings::getInstance()) ;

	std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
	if (!radio)
		return ;

	std::shared_ptr<IFibre> fibres(IFibre::getInterface());

	// set all settings supported by the application
	if (settings->isSetting("NUM_TX_PORTS"))
		settings->setSetting("NUM_TX_PORTS", std::to_string(radio->getNumberOfTxPorts())) ;
	if (settings->isSetting("NUM_RX_PORTS"))
		settings->setSetting("NUM_RX_PORTS", std::to_string(radio->getNumberOfRxPorts())) ;
	if (settings->isSetting("NUM_SRX_PORTS"))
		settings->setSetting("NUM_SRX_PORTS", std::to_string(radio->getNumberOfSRxPorts())) ;
	if (settings->isSetting("NUM_FIBRES"))
		settings->setSetting("NUM_FIBRES", std::to_string(fibres->getNumPorts())) ;
	if (settings->isSetting("MAX_FIBRE"))
		settings->setSetting("MAX_FIBRE", std::to_string(fibres->getNumPorts()-1)) ;

	// Get the list of supported ICalDownload types and create a TIF ENUM() so user can only select the installed types
	if (settings->isSetting("CAL_FILE_TYPES"))
	{
		std::shared_ptr<ICalDownloadManagement> calMgr( ICalDownloadManagement::getInstance() ) ;
		settings->setSetting("CAL_FILE_TYPES", join(calMgr->getTypes(), ':')) ;
	}

	// Restrict the displayed carrier types to just those suitable for the application
	// Default is just the RRH types (e.g. LTE5 etc)
	// If PIM feature is enabled then show the pim set
#ifdef FEAT_PIM_XILINX
	if (settings->isSetting("CARRIER_TYPES"))
		settings->setSetting("CARRIER_TYPES", join(ICarrier::getPimTypes(), ':')) ;
#else
	if (settings->isSetting("CARRIER_TYPES"))
		settings->setSetting("CARRIER_TYPES", join(ICarrier::getRrhTypes(), ':')) ;
#endif

	if (settings->isSetting("CARRIER_SIGNALS"))
		settings->setSetting("CARRIER_SIGNALS", join(ICarrier::getAllSignals(), ':')) ;
	if (settings->isSetting("CARRIER_STATES"))
		settings->setSetting("CARRIER_STATES", join(ICarrier::getAllStates(), ':')) ;

}
