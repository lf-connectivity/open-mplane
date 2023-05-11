/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BuildFeatureList.h
 * \brief     Manage the BuildFeatures
 *
 *
 * \details   Keeps track of the BuildFeatures built into the application
 *
 */


#ifndef BuildFeatureLIST_H_
#define BuildFeatureLIST_H_

#include <memory>
#include <vector>
#include <functional>

#include "IApplication.h"
#include "IBuildFeature.h"

namespace Mplane {

class BuildFeatureList {
public:
	BuildFeatureList() ;
	virtual ~BuildFeatureList() ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<BuildFeatureList> getInstance() ;

	/**
	 * Function for creating a new IBuildFeature
	 */
	using BuildFeatureCreate = std::function< std::shared_ptr<IBuildFeature>() > ;

	/**
	 * Registration method - called to register the creation method for this BuildFeature
	 * @param init
	 * @return handle to registered BuildFeature
	 */
	virtual int registerBuildFeature(BuildFeatureCreate create) ;

	/**
	 * Creates all the registered BuildFeatures and initialises them
	 * @return true if all is ok
	 */
	virtual bool initBuildFeatures(IApplication* app) ;


	/**
	 * Application start
	 * @return true if ok; false otherwise
	 */
	virtual bool appStart()  ;


	/**
	 * Prior to application options. Allows for plugin to add extra options
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options)  ;

	/**
	 * Prior to application wait
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreWait()  ;

	/**
	 * Prior to application init
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreInit()  ;

	/**
	 * Hook called just before IApplicationPlugin::appPostInit() is called
	 * @return true if ok; false otherwise
	 */
	virtual bool appPostInit() ;

	/**
	 * Prior to application run
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreRun() ;

	/**
	 * Application end
	 * @return true if ok; false otherwise
	 */
	virtual bool appEnd() ;



	/**
	 * Returns number of registered BuildFeatures
	 */
	virtual unsigned numBuildFeatures() const ;

private:
	std::vector<BuildFeatureCreate> mCreateList ;
	std::vector<std::shared_ptr<IBuildFeature>> mBuildFeatureList ;
} ;

}

#endif /* BuildFeatureLIST_H_ */
