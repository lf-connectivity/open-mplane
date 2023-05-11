/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFeature.h
 * \brief     Virtual interface to feature support
 *
 *
 * \details   Licensed SW is licensed to support one or more registered features. Attempting to use a feature that
 * 				this setup is not licensed for will result in an error
 *
 */


#ifndef IFEATURE_H_
#define IFEATURE_H_

#include <iostream>
#include <memory>
#include <string>
#include "IKey.h"

#include "IFeatureBase.h"

namespace Mplane {

class IFeature : public virtual IFeatureBase {
public:
	IFeature() {}
	virtual ~IFeature() {}

	/**
	 * Wave block data type. Raw IQ data or compressed/encrypted
	 */
	enum class FeatureType {
		NO_FEATURES		    = 0,
		LTE_TDD_TM			= 1<<0,
		LTE_FDD_TM			= 1<<1,
		LTE_TDD_FRCA		= 1<<2,
		LTE_FDD_FRCA		= 1<<3,

		// Client/GUI options persisted on the CART - do not affect the CART performance.
		LTE_GUI_RX_BER      = 1<<31
	};

	/**
	 * Convert single feature bit into a string
	 * @param feature
	 */
//	static std::string featureName(FeatureType feature) ;

	/**
	 * Factory for making feature objects
	 * @param key
	 */
	static std::shared_ptr<IFeature> factory(std::shared_ptr<IKey> key) ;

	/**
	 * Factory for making supported feature object using the bitset of supported features
	 * @param key
	 * @param features
	 */
	static std::shared_ptr<IFeature> factory(std::shared_ptr<IKey> key, FeatureType features) ;

	/**
	 * Factory for making supported feature object using the encoded public string
	 * @param key
	 * @param encodedFeatures
	 */
	static std::shared_ptr<IFeature> factory(std::shared_ptr<IKey> key, const std::string& encodedFeatures) ;

	/**
	 * Singleton (created using the IKey singleton)
	 */
	static std::shared_ptr<IFeature> getInstance() ;

	/**
	 * Convert single feature bit into a string
	 * @param feature
	 */
	virtual std::string featureName(FeatureType feature) const =0 ;

	/**
	 * Are the features initialised?
	 */
	virtual bool isSet() const =0 ;

	/**
	 * Specify the license key to use
	 */
	virtual void setKey(std::shared_ptr<IKey> key) =0 ;

	/**
	 * Enable the specified feature (or features)
	 * @param features	Bitset of features to enable
	 */
	virtual bool enableFeature(FeatureType features) =0 ;

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
	 * Get the bitset of supported features
	 */
	virtual FeatureType supportedFeatures() const =0 ;

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


inline IFeature::FeatureType
operator&(IFeature::FeatureType __a, IFeature::FeatureType __b)
{ return IFeature::FeatureType(static_cast<int>(__a) & static_cast<int>(__b)); }

inline IFeature::FeatureType
operator|(IFeature::FeatureType __a, IFeature::FeatureType __b)
{ return IFeature::FeatureType(static_cast<int>(__a) | static_cast<int>(__b)); }

inline IFeature::FeatureType
operator^(IFeature::FeatureType __a, IFeature::FeatureType __b)
{ return IFeature::FeatureType(static_cast<int>(__a) ^ static_cast<int>(__b)); }

inline IFeature::FeatureType&
operator|=(IFeature::FeatureType& __a, IFeature::FeatureType __b)
{ return __a = __a | __b; }

inline IFeature::FeatureType&
operator&=(IFeature::FeatureType& __a, IFeature::FeatureType __b)
{ return __a = __a & __b; }

inline IFeature::FeatureType&
operator^=(IFeature::FeatureType& __a, IFeature::FeatureType __b)
{ return __a = __a ^ __b; }

inline IFeature::FeatureType
operator~(IFeature::FeatureType __a)
{ return IFeature::FeatureType(~static_cast<int>(__a)); }

}

#endif /* IFEATURE_H_ */
