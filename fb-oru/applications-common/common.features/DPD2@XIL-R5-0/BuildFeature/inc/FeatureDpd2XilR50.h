/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureDpd2XilR50.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef FeatureDpd2XilR50_H_
#define FeatureDpd2XilR50_H_

#include <memory>

#include "BuildFeature.h"
#include "IEmbeddedMgr.h"

namespace Mplane {

class FeatureDpd2XilR50 : public BuildFeature {
public:
	FeatureDpd2XilR50() ;
	virtual ~FeatureDpd2XilR50() ;

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
	 * Prior to application wait
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreWait() override ;

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

private:
	std::shared_ptr<IEmbeddedMgr> mMgr ;
} ;

}

#endif /* FeatureDpd2XilR50_H_ */
