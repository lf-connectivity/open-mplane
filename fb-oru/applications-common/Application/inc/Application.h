/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Application.h
 * \brief     The application class
 *
 *
 * \details
 *
 */


#ifndef APPLICATION_H_
#define APPLICATION_H_
#include <functional>

#include "ILoggable.h"

#include "IApplication.h"

namespace Mplane {

class IAppSettings ;
class IAppOptions ;
class IAppControl ;


/**
 * The Mplane::Application class provides a base implementation of the
 * Mplane::IApplication pure virtual radio application interface. This is
 * intended to be used as the base class of all Mplane Software Platform
 * application.
 *
 */
class Application : public virtual IApplication {
public:
    /**
     * Default constructor
     */
	Application() ;
	/**
	 * Default destructor
	 */
	virtual ~Application() ;

	/**
	 * Run the application. When running this class will call a number of hooks to allow
	 * derived objects to add additional behaviour, or override default behaviour
	 * @param name descriptive name of the application
	 * @param argc
	 * @param argv
	 * @param extraOptions - Optionally supply additional options
	 * @return exit code
	 */
	virtual int run(
		const std::string& name,
		int argc, const char** argv,
		const std::vector< std::shared_ptr<IAppOptionSpec> >& extraOptions = {}) override ;

protected:
	/**
	 * Application start
	 * @return true if ok; false otherwise
	 */
	virtual int appStart();

	/**
	 * Application options - process the command line options
	 * @return true if ok; false otherwise
	 */
	virtual int appOptions(
			const std::string& name,
			int argc, const char** argv,
			const std::vector<std::shared_ptr<IAppOptionSpec> >& options) ;


	/**
	 * Application wait (waits for a second or so to allow for correct start up)
	 * @return true if ok; false otherwise
	 */
	virtual int appWait() ;


	/**
	 * Hook called just before IApplicationPlugin::appInit() is called
	 * @return true if ok; false otherwise
	 */
	virtual int appInit() ;

	/**
	 * Hook called just before IApplicationPlugin::appPostInit() is called
	 * @return true if ok; false otherwise
	 */
	virtual int appPostInit() ;

	/**
	 * Application pre-run - called to set up any remaining TIF etc before running the application
	 * @return true if ok; false otherwise
	 */
	virtual int appPreRun() ;

	/**
	 * Application run
	 * @return true if ok; false otherwise
	 */
	virtual int appRun() ;


	/**
	 * Application end
	 * @return true if ok; false otherwise
	 */
	virtual int appEnd() ;

private:
	/**
	 * Handle any logging level settings
	 */
	void processLogging() ;

	/**
	 * Process log setting string of the form <name>=<level>[:<name>=<level>..]
	 */
	using SetLogFunc = std::function<void(ILoggable::LogDebugLevel level, const std::string& name)> ;
	void processLoggingStr(const std::string& str, SetLogFunc setLog) ;

private:
	std::shared_ptr<IAppSettings> mAppSettings ;
	std::shared_ptr<IAppOptions> mAppOpts ;
	std::shared_ptr<IAppControl> mAppControl ;

} ;

}

#endif /* APPLICATION_H_ */
