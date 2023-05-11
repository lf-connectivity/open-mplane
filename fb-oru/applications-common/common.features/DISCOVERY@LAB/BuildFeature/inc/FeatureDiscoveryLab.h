/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureDiscoveryLab.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef FEATUREDISCOVERYLAB_H_
#define FEATUREDISCOVERYLAB_H_

#include "BuildFeature.h"

namespace Mplane {

/*!
 * \class FeatureDiscoveryLab
 */
class FeatureDiscoveryLab : public BuildFeature {
public:
	FeatureDiscoveryLab() ;
	virtual ~FeatureDiscoveryLab() ;

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
	 * Prior to application options. Allows for plugin to add extra options
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options) override ;

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

#endif /* FeatureDiscoveryLab_H_ */
