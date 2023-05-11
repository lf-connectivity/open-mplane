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
#include "IAppOptions.h"
#include "IAppControl.h"

#include "Tokeniser.h"

#include "IBootTimer.h"
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
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IApplication> IApplication::getInstance()
{
	static std::shared_ptr<Application> instance(new Application());
	return instance;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Application::Application() :
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

//-------------------------------------------------------------------------------------------------------------
void Application::quit()
{
	mAppControl->shutdown();
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int Application::appStart()
{
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appOptions(
		const std::string& name,
		int argc, const char** argv,
		const std::vector<std::shared_ptr<IAppOptionSpec> >& extraOptions)
{
	std::vector<std::shared_ptr<IAppOptionSpec> > options(extraOptions) ;

	// Allow logging to be enabled right from the start of the program
	options.push_back(
		IAppOptionSpec::factory("grouplog", DataVariantType::String, "Logging for groups (name=level:name=level..)", "", ILoggable::GROUP_LOG_ENV_VARNAME)
	) ;
	options.push_back(
		IAppOptionSpec::factory("instlog", DataVariantType::String, "Logging for instances (name=level:name=level..)", "", ILoggable::INST_LOG_ENV_VARNAME)
	) ;
	options.push_back(
		IAppOptionSpec::factory("cfg-data-path", DataVariantType::String, "Path to YANG configuration data (required)", "")
	) ;
	options.push_back(
		IAppOptionSpec::factory("yang-mods-path", DataVariantType::String, "Path to YANG modules (required)", "")
	) ;
	options.push_back(
		IAppOptionSpec::factory("netopeer-path", DataVariantType::String, "Path to Netopeer2 application (required)", "")
	) ;
	options.push_back(
		IAppOptionSpec::factory("netopeerdbg", DataVariantType::Int, "NETCONF server debug level (0-2)", "1", "NETCONFDBG")
	) ;
	options.push_back(
		IAppOptionSpec::factory("call-home-clients", DataVariantType::String, "File path containing call home client information", "")
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
	// wait
	::sleep(1);
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appInit()
{
	// Create services
	mAppControl = IAppControlFactory::getInterface() ;

	// start up services
	try
	{
		mAppControl->start();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appPostInit()
{
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appPreRun()
{
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
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int Application::appEnd()
{
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
