/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedFeature.h
 * \brief     Implements IFeature saved in u-boot env - uses GenericFeature so feature bits are tailored to each app
 *
 *
 * \details
 *
 */


#ifndef SAVEDGENERICFEATURE_H_
#define SAVEDGENERICFEATURE_H_

#include "GenericFeature.h"

namespace Mplane {

class SavedGenericFeature : public GenericFeature {
public:
	using super = GenericFeature ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<IGenericFeature> factory(const std::vector<std::string>& featureNames) ;
	static std::shared_ptr<IGenericFeature> factory(const std::map<std::string, unsigned>& featureNames) ;

	explicit SavedGenericFeature(const std::vector<std::string>& featureNames) ;
	explicit SavedGenericFeature(const std::map<std::string, unsigned>& featureNames) ;

	virtual ~SavedGenericFeature() ;

	/**
	 * Set up supported features from an encoded public string
	 * @param encodedFeatures
	 * @return false if invalid string
	 */
	virtual bool setFeatures(const std::string& encodedFeatures) override ;

private:
	void init() ;
} ;

}

#endif /* SAVEDGENERICFEATURE_H_ */
