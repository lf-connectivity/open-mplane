/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Application.cpp
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
#include "IAlarmsList.h"
#include "IFaultsList.h"

#include "Tokeniser.h"

#include "ITroubleshootMgr.h"
#include "ITraceMgr.h"
#include "IBootTimer.h"
#include "BuildFeatureList.h"
#include "Application.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#ifdef OFF_TARGET
const char* LOGFILE{"/tmp/console.log"} ;
#else
const char* LOGFILE{"/var/log/console.log"} ;
#endif


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Application::Application() :
	mAppSettings(),
	mAppOpts(),
	mAppControl()
{
	// Redirect stdout/stderr
#ifndef OFF_TARGET
	// cppcheck-suppress leakReturnValNotUsed
	freopen(LOGFILE, "a", stdout) ;
	// cppcheck-suppress leakReturnValNotUsed
	freopen(LOGFILE, "a", stderr) ;
#endif

	// start timing the app startup time
	std::shared_ptr<IBootTimer> bootTimer(IBootTimer::getInstance()) ;

	// Ensure that the troubleshooting and trace managers are created ready for adding files.
	// NOTE: This isn't currently strictly necessary, but doesn't hurt!
	(void)ITroubleshootMgr::singleton() ;
	(void)ITraceMgr::singleton() ;
}

//-------------------------------------------------------------------------------------------------------------
Application::~Application()
{
}


//-------------------------------------------------------------------------------------------------------------
int Application::run(
		const std::string& name,
		int argc, const char** argv,
		const std::vector<std::shared_ptr<IAppOptionSpec> >& extraOptions)
{
	int rc(0) ;

	// start
	rc = appStart() ;
	if (rc != 0)
		return rc ;

	// options
	rc = appOptions(name, argc, argv, extraOptions) ;
	if (rc != 0)
		return rc ;

	// wait
	rc = appWait() ;
	if (rc != 0)
		return rc ;

	// init
	rc = appInit() ;
	if (rc != 0)
		return rc ;

	// post-init
	rc = appPostInit() ;
	if (rc != 0)
		return rc ;

	// stop timing the app startup time
	std::shared_ptr<IBootTimer> bootTimer(IBootTimer::getInstance()) ;
	bootTimer->appStarted() ;

	// pre-run
	rc = appPreRun() ;
	if (rc != 0)
		return rc ;

	// run
	rc = appRun() ;
	if (rc != 0)
		return rc ;

	// end
	rc = appEnd() ;
	if (rc != 0)
		return rc ;


	return 0 ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int Application::appStart()
{
	// Initialise features
	BuildFeatureList::getInstance()->initBuildFeatures(this) ;

	std::shared_ptr<BuildFeatureList> featureList(BuildFeatureList::getInstance()) ;

	// start
	if (!featureList->appStart())
		return -1 ;

	mAppSettings = IAppSettingsFactory::getInterface() ;
	std::cerr << "Starting " <<
		mAppSettings->getAppString() << " application for " <<
		mAppSettings->getBoardString() << " hardware" <<
		std::endl;
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appOptions(
		const std::string& name,
		int argc, const char** argv,
		const std::vector<std::shared_ptr<IAppOptionSpec> >& extraOptions)
{
	std::shared_ptr<BuildFeatureList> featureList(BuildFeatureList::getInstance()) ;

	// pre-options
	std::vector<std::shared_ptr<IAppOptionSpec> > options(extraOptions) ;

	if (!featureList->appPreOptions(options))
		return -1 ;

	// Add the default options
	options.push_back(
		IAppOptionSpec::factory("port", DataVariantType::Int, "TIF port", "49500", "TIFPORT")
	) ;

	// Allow logging to be enabled right from the start of the program
	options.push_back(
		IAppOptionSpec::factory("grouplog", DataVariantType::String, "Logging for groups (name=level:name=level..)", "", ILoggable::GROUP_LOG_ENV_VARNAME)
	) ;
	options.push_back(
		IAppOptionSpec::factory("instlog", DataVariantType::String, "Logging for instances (name=level:name=level..)", "", ILoggable::INST_LOG_ENV_VARNAME)
	) ;


	// Define expected options and process the command line
	mAppOpts = IAppOptions::createInstance(argc, argv, name, options) ;

	// Handle any logging settings
	processLogging() ;

	return 0 ;

}

//-------------------------------------------------------------------------------------------------------------
int Application::appWait()
{
	std::shared_ptr<BuildFeatureList> featureList(BuildFeatureList::getInstance()) ;

	// pre-wait
	if (!featureList->appPreWait())
		return -1 ;

	// wait
	::sleep(1);
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appInit()
{
	std::shared_ptr<BuildFeatureList> featureList(BuildFeatureList::getInstance()) ;

	// pre-init
	if (!featureList->appPreInit())
		return -1 ;

	// Create services
	mAppControl = IAppControlFactory::getInterface() ;

	// start up services
	mAppControl->start();

	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appPostInit()
{
	std::shared_ptr<BuildFeatureList> featureList(BuildFeatureList::getInstance()) ;

	// post-init
	if (!featureList->appPostInit())
		return -1 ;

	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appPreRun()
{
	std::shared_ptr<BuildFeatureList> featureList(BuildFeatureList::getInstance()) ;

	// pre-run
	if (!featureList->appPreRun())
		return -1 ;

	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appRun()
{
	// close registration of any more Loggable objects
	ILoggable::closeRegistration() ;

	// run
	try
	{
		mAppControl->run();
	}
	catch(...)
	{
		return -1 ;
	}

	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appEnd()
{
	std::shared_ptr<BuildFeatureList> featureList(BuildFeatureList::getInstance()) ;

	// end
	if (!featureList->appEnd())
		return -1 ;
	return 0 ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Application::processLogging()
{
	// Group and instance strings can be of the form:
	//
	//   <name>=<level>[:<name>=<level>..]
	//
	std::string groupLogging( mAppOpts->getOption("grouplog").toString() ) ;
	if (!groupLogging.empty())
	{
		processLoggingStr(groupLogging, ILoggable::setGroupLogDebugLevel) ;
	}
	std::string instLogging( mAppOpts->getOption("instlog").toString() ) ;
	if (!instLogging.empty())
	{
		processLoggingStr(instLogging, ILoggable::setInstanceLogDebugLevel) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
void Application::processLoggingStr(const std::string& str, SetLogFunc setLog)
{
	Tokeniser tokens(str, ":") ;
	std::vector<std::string> varVals(tokens.getTokens()) ;
	for (auto varVal : varVals)
	{
		Tokeniser toks(varVal, "=") ;
		std::vector<std::string> nameLevel(toks.getTokens()) ;
		if (nameLevel.size() != 2)
			continue ;

		setLog(ILoggable::strToLevel(nameLevel[1]), nameLevel[0]) ;
	}
}
