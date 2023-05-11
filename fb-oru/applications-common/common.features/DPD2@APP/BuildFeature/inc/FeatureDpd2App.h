/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureDpd2App.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef FEATUREDPDAPP_H_
#define FEATUREDPDAPP_H_

#include "BuildFeature.h"

namespace Mplane {

class FeatureDpd2App : public BuildFeature {
public:
	FeatureDpd2App() ;
	virtual ~FeatureDpd2App() ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<IBuildFeature> getInstance() ;

	/**
	 * Initialise the feature
	 * @return true if ok
	 */
	virtual bool init(IApplication* app) override ;

	/**
	 * Prior to application init
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreInit() override ;

	/**
	 * Hook called just before IApplicationPlugin::appPostInit() is called
	 * @return true if ok; false otherwise
	 */
	virtual bool appPostInit() override ;

	/**
	 * Prior to application run
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreRun() override ;

	/**
	 * Used to autoload class
	 */
	static int handle ;
} ;

}

#endif /* FEATUREDPDAPP_H_ */
