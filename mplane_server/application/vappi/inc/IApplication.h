/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IApplication.h
 * \brief     Virtual interface to the application object
 *
 *
 * \details   Application processes the command line arguments, sets up the application and runs it
 *
 */


#ifndef IAPPLICATION_H_
#define IAPPLICATION_H_

#include <memory>
#include <string>
#include <vector>

#include "IAppOptions.h"

namespace Mplane {

/**
 * This pure virtual class defines the interface that all applications must
 * support to be considered to be an Mplane Software Platform application.
 */
class IApplication {
public:
	IApplication() {}
	virtual ~IApplication() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IApplication> getInstance() ;

	/**
	 * Run the application. When running this class will call a number of hooks to allow
	 * derived objects to add additional behaviour, or override default behaviour
	 * @param argc
	 * @param argv
	 * @param extraOptions - Optionally supply additional options
	 * @return exit code
	 */
	virtual int run(
		const std::string& name,
		int argc, const char** argv,
		const std::vector< std::shared_ptr<IAppOptionSpec> >& extraOptions = {}) =0 ;

	/**
	 * Quit the application
	 */
	virtual void quit() =0;

} ;

}

#endif /* IAPPLICATION_H_ */
