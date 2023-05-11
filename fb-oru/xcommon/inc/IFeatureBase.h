/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFeatureBase.h
 * \brief     Virtual interface to base methods for feature support
 *
 *
 * \details   Licensed SW is licensed to support one or more registered features. Attempting to use a feature that
 * 				this setup is not licensed for will result in an error. The generic feature allows the application
 * 				to dynamically define the bits used and the name strings associated with those bits (rather than
 * 				defining them at build time using a static enum).
 *
 */


#ifndef IFEATUREBASE_H_
#define IFEATUREBASE_H_

#include <iostream>
#include <memory>
#include <string>
#include "IKey.h"

namespace Mplane {

class IFeatureBase {
public:
	IFeatureBase() {}
	virtual ~IFeatureBase() {}

	/**
	 * Singleton (created using the IKey singleton)
	 */
	static std::shared_ptr<IFeatureBase> getInstance() ;


	/**
	 * Are the features initialised?
	 */
	virtual bool isSet() const =0 ;

	/**
	 * Specify the license key to use
	 */
	virtual void setKey(std::shared_ptr<IKey> key) =0 ;

	/**
	 * Enable the specified feature using the feature name
	 * @param features	Bitset of features to enable
	 */
	virtual bool enableFeature(const std::string& featureName) =0 ;

	/**
	 * Convert the supported features into a public string suitable for sharing
	 * @return
	 */
	virtual std::string encodeFeatures() const =0 ;

	/**
	 * Set up supported features from an encoded public string
	 * @param encodedFeatures
	 * @return false if invalid string
	 */
	virtual bool setFeatures(const std::string& encodedFeatures) =0 ;

	/**
	 * Check that the supplied feature name is enabled
	 * @param featureName
	 * @return true if feature enabled
	 */
	virtual bool checkSupported(const std::string& featureName) const =0 ;

	/**
	 * Display the complete list of all possible features and whether they are enabled
	 * @param os	Output stream
	 */
	virtual void show(std::ostream& os = std::cout) const =0 ;

} ;

}

#endif /* IFEATUREBASE_H_ */
