/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureWebsockEnable.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef FEATUREWEBSOCKTRUE_H_
#define FEATUREWEBSOCKTRUE_H_

#include "BuildFeature.h"

namespace Mplane {

/*!
 * \class FeatureWebsockEnable
 */
class FeatureWebsockEnable : public BuildFeature {
public:
	FeatureWebsockEnable() ;
	virtual ~FeatureWebsockEnable() ;

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


#endif /* FEATUREWEBSOCKTRUE_H_ */
