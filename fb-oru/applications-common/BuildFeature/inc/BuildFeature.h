/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BuildFeature.h
 * \brief     Generic base class
 *
 *
 * \details
 *
 */


#ifndef BUILDFEATURE_H_
#define BUILDFEATURE_H_

#include "IBuildFeature.h"

namespace Mplane {

/*!
 * \class BuildFeature
 */
class BuildFeature : public virtual IBuildFeature {
public:
	BuildFeature() ;
	virtual ~BuildFeature() ;

	/**
	 * Initialise the BuildFeature
	 * @return true if ok
	 */
	virtual bool init(IApplication* app) =0 ;


	/**
	 * Application start
	 * @return true if ok; false otherwise
	 */
	virtual bool appStart() override ;


	/**
	 * Prior to application options. Allows for plugin to add extra options
	 * @return true if ok; false otherwise
	 */
	virtual bool appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options) override ;

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
	 * Application end
	 * @return true if ok; false otherwise
	 */
	virtual bool appEnd() override ;


} ;

}

#endif /* BUILDFEATURE_H_ */
