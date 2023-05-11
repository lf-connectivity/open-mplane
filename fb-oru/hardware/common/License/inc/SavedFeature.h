/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedFeature.h
 * \brief     Implements IFeature saved in u-boot env - Feature bits are specific to ART
 *
 *
 * \details
 *
 */


#ifndef SAVEDFEATURE_H_
#define SAVEDFEATURE_H_

#include "Feature.h"

namespace Mplane {

class SavedFeature : public Feature {
public:
	using super = Feature ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<IFeature> getInstance() ;

	SavedFeature() ;
	virtual ~SavedFeature() ;

	/**
	 * Set up supported features from an encoded public string
	 * @param encodedFeatures
	 * @return false if invalid string
	 */
	virtual bool setFeatures(const std::string& encodedFeatures) override ;

} ;

}

#endif /* SAVEDFEATURE_H_ */
