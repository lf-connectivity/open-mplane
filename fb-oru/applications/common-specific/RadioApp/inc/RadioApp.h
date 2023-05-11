/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioApp.h
 * \brief     The radio application class
 *
 *
 * \details   Radio-specific application
 *
 */


#ifndef RADIOAPP_H_
#define RADIOAPP_H_
#include <functional>

#include "Application.h"

namespace Mplane {

class IRadioPostInit ;

#ifdef OFF_TARGET
#ifdef BUILD_IF_CPRI
class CpriFibreEmu ;
#endif
class ISpiEmu ;
class LatchedAlarmEmu ;
class LatchedAntennaAlarmEmu ;
#endif


/**
 * The Mplane::Application class provides a base implementation of the
 * Mplane::IApplication pure virtual radio application interface. This is
 * intended to be used as the base class of all Mplane Software Platform
 * application.
 *
 */
class RadioApp : public Application {
public:
    /**
     * Default constructor
     */
	RadioApp() ;
	/**
	 * Default destructor
	 */
	virtual ~RadioApp() ;

protected:
	/**
	 * Application options - process the command line options
	 * @return true if ok; false otherwise
	 */
	virtual int appOptions(
			const std::string& name,
			int argc, const char** argv,
			const std::vector<std::shared_ptr<IAppOptionSpec> >& options) override ;


	/**
	 * Hook called just before IApplicationPlugin::appInit() is called
	 * @return true if ok; false otherwise
	 */
	virtual int appInit() override ;

	/**
	 * Hook called just before IApplicationPlugin::appPostInit() is called
	 * @return true if ok; false otherwise
	 */
	virtual int appPostInit() override ;

private:
	std::shared_ptr<IRadioPostInit> mRadioPostInit ;
#ifdef OFF_TARGET
#ifdef BUILD_IF_CPRI
	std::vector <std::shared_ptr<CpriFibreEmu>> mFibreEmu ;
#endif
	std::shared_ptr<ISpiEmu> mSpiEmu ;
	std::shared_ptr<LatchedAlarmEmu> mLatchedAlarmEmu ;
	std::vector <std::shared_ptr<LatchedAntennaAlarmEmu>> mAntAlarmEmu ;
#endif

} ;

}

#endif /* RADIOAPP_H_ */
