/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Feature.h
 * \brief     Supported features class
 *
 *
 * \details   Licensed SW is licensed to support one or more registered features. Attempting to use a feature that
 * 				this setup is not licensed for will result in an error
 *
 */


#ifndef FEATURE_H_
#define FEATURE_H_

#include "IFeature.h"
#include "GenericFeature.h"

namespace Mplane {

class Feature : public virtual IFeature {
public:
	Feature() ;
	virtual ~Feature() ;

	/**
	 * Convert single feature bit into a string
	 * @param feature
	 */
	virtual std::string featureName(FeatureType feature) const override ;

	/**
	 * Are the features initialised?
	 */
	virtual bool isSet() const override ;

	/**
	 * Specify the license key to use
	 */
	virtual void setKey(std::shared_ptr<IKey> key) override ;

	/**
	 * Enable the specified feature (or features)
	 * @param features	Bitset of features to enable
	 */
	virtual bool enableFeature(IFeature::FeatureType features) override ;

	/**
	 * Enable the specified feature using the feature name
	 * @param features	Bitset of features to enable
	 */
	virtual bool enableFeature(const std::string& featureName) override ;

	/**
	 * Convert the supported features into a public string suitable for sharing
	 * @return
	 */
	virtual std::string encodeFeatures() const override ;

	/**
	 * Set up supported features from an encoded public string
	 * @param encodedFeatures
	 * @return false if invalid string
	 */
	virtual bool setFeatures(const std::string& encodedFeatures) override ;

	/**
	 * Get the bitset of supported features
	 */
	virtual IFeature::FeatureType supportedFeatures() const override ;

	/**
	 * Check that the supplied feature name is enabled
	 * @param featureName
	 * @return true if feature enabled
	 */
	virtual bool checkSupported(const std::string& featureName) const override ;

	/**
	 * Display the complete list of all possible features and whether they are enabled
	 * @param os	Output stream
	 */
	virtual void show(std::ostream& os = std::cout) const override ;

private:
	GenericFeature mGenericFeature ;
} ;

}

#endif /* FEATURE_H_ */
