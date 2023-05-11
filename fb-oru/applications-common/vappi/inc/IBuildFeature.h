/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBuildFeature.h
 * \brief     virtual boolerface to application BuildFeature
 *
 *
 * \details   A BuildFeature can be enabled/disabled via the build configuration. The application
 * 			will automatically build with the correct BuildFeature settings and pull in the appropriate
 * 			classes
 *
 */


#ifndef IBuildFeature_H_
#define IBuildFeature_H_

#include "IApplication.h"

namespace Mplane {

class IBuildFeature {
public:
	IBuildFeature() {}
	virtual ~IBuildFeature() {}

	/**
	 * Initialise the BuildFeature
	 * @return true if ok
	 */
	virtual bool init(IApplication* app) =0 ;


	// Hooks provided at various stages in the application run process

	/**
	 * Application start
	 * @return true if ok; false otherwise
	 */
	virtual bool appStart() =0 ;


	/**
	 * Prior to application options. Allows for plugin to add extra options
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options) =0 ;

	/**
	 * Prior to application wait
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreWait() =0 ;

	/**
	 * Prior to application init
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreInit() =0 ;

	/**
	 * Hook called just before IApplicationPlugin::appPostInit() is called
	 * @return true if ok; false otherwise
	 */
	virtual bool appPostInit() =0 ;

	/**
	 * Prior to application run
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreRun() =0 ;

	/**
	 * Application end
	 * @return true if ok; false otherwise
	 */
	virtual bool appEnd() =0 ;
} ;

}

#endif /* IBuildFeature_H_ */
