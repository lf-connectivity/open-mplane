/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GenericFeature.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cstdint>
#include <map>
#include <bitset>
#include <algorithm>

#include "GenericFeature.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGenericFeature> IGenericFeature::factory(const std::vector<std::string>& featureNames,
		std::shared_ptr<IKey> key)
{
	std::shared_ptr<IGenericFeature> feature(std::make_shared<GenericFeature>(featureNames)) ;
	if (!feature)
		return feature ;

	feature->setKey(key) ;
	return feature ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGenericFeature> IGenericFeature::factory(const std::vector<std::string>& featureNames,
		std::shared_ptr<IKey> key, IGenericFeature::GenericFeatureType features)
{
	std::shared_ptr<IGenericFeature> feature(IGenericFeature::factory(featureNames, key)) ;
	if (!feature)
		return feature ;

	feature->enableFeature(features) ;
	return feature ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGenericFeature> IGenericFeature::factory(const std::vector<std::string>& featureNames,
		std::shared_ptr<IKey> key, const std::string& encodedFeatures)
{
	std::shared_ptr<IGenericFeature> feature(IGenericFeature::factory(featureNames, key)) ;
	if (!feature)
		return feature ;

	if (!feature->setFeatures(encodedFeatures))
		return std::shared_ptr<IGenericFeature>() ;

	return feature ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGenericFeature> IGenericFeature::factory(const std::map<std::string, unsigned>& featureNames,
		std::shared_ptr<IKey> key)
{
	std::shared_ptr<IGenericFeature> feature(std::make_shared<GenericFeature>(featureNames)) ;
	if (!feature)
		return feature ;

	feature->setKey(key) ;
	return feature ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGenericFeature> IGenericFeature::factory(const std::map<std::string, unsigned>& featureNames,
		std::shared_ptr<IKey> key, IGenericFeature::GenericFeatureType features)
{
	std::shared_ptr<IGenericFeature> feature(IGenericFeature::factory(featureNames, key)) ;
	if (!feature)
		return feature ;

	feature->enableFeature(features) ;
	return feature ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGenericFeature> IGenericFeature::factory(const std::map<std::string, unsigned>& featureNames,
		std::shared_ptr<IKey> key, const std::string& encodedFeatures)
{
	std::shared_ptr<IGenericFeature> feature(IGenericFeature::factory(featureNames, key)) ;
	if (!feature)
		return feature ;

	if (!feature->setFeatures(encodedFeatures))
		return std::shared_ptr<IGenericFeature>() ;

	return feature ;
}




//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
GenericFeature::GenericFeature(const std::vector<std::string>& featureNames) :
	mKey(),
	mFeatures( IGenericFeature::GenericFeatureType::NO_FEATURES ),
	mFeatureNames(),
	mValidFeatures( IGenericFeature::GenericFeatureType::NO_FEATURES ),
	mInvalidFeatures( IGenericFeature::GenericFeatureType::NO_FEATURES )
{
	for (unsigned bit=0; bit < featureNames.size(); ++bit)
	{
		mFeatureNames[featureNames[bit]] = bit ;
	}

	init() ;
}

//-------------------------------------------------------------------------------------------------------------
GenericFeature::GenericFeature(const std::map<std::string, unsigned>& featureNames) :
	mKey(),
	mFeatures( IGenericFeature::GenericFeatureType::NO_FEATURES ),
	mFeatureNames(featureNames),
	mValidFeatures( IGenericFeature::GenericFeatureType::NO_FEATURES ),
	mInvalidFeatures( IGenericFeature::GenericFeatureType::NO_FEATURES )
{
	init() ;
}


//-------------------------------------------------------------------------------------------------------------
GenericFeature::~GenericFeature()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string GenericFeature::featureName(IGenericFeature::GenericFeatureType feature) const
{
	auto entry(
		std::find_if(mFeatureNames.begin(), mFeatureNames.end(),
			[feature](const std::pair<std::string, unsigned>& p) {
				return static_cast<IGenericFeature::GenericFeatureType>(1<<p.second) == feature;
			}
		)
	) ;

	if (entry == mFeatureNames.end())
		return "" ;

	return entry->first ;

}


//-------------------------------------------------------------------------------------------------------------
bool GenericFeature::enableFeature(IGenericFeature::GenericFeatureType features)
{
	// see if it set any invalid bits
	if ( (features & mInvalidFeatures) != IGenericFeature::GenericFeatureType::NO_FEATURES)
		return false ;

	// only copy those bits which are valid
	mFeatures |= (mValidFeatures & features) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool GenericFeature::enableFeature(const std::string& featureName)
{
	IGenericFeature::GenericFeatureType feature(nameToFeature(featureName)) ;
	if (feature == IGenericFeature::GenericFeatureType::NO_FEATURES)
		return false ;

	return enableFeature(feature) ;
}


//-------------------------------------------------------------------------------------------------------------
std::string GenericFeature::encodeFeatures() const
{
	if (!mKey)
		return "" ;

	// use the key to encode the features
	return mKey->encode32bits( static_cast<uint32_t>(mFeatures) ) ;
}

//-------------------------------------------------------------------------------------------------------------
bool GenericFeature::setFeatures(const std::string& encodedFeatures)
{
	if (!mKey)
		return false ;

	// decode the string
	uint32_t decoded32bits{0} ;
	if (!mKey->decode32bits(encodedFeatures, decoded32bits))
		return false ;

	// see if it set any invalid bits
	if ( (decoded32bits & static_cast<uint32_t>(mInvalidFeatures)) != 0)
		return false ;

	// Only valid feature bits so set them
	mFeatures = static_cast<IGenericFeature::GenericFeatureType>(decoded32bits) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
IGenericFeature::GenericFeatureType GenericFeature::supportedFeatures() const
{
	return mFeatures ;
}

//-------------------------------------------------------------------------------------------------------------
void GenericFeature::setKey(std::shared_ptr<IKey> key)
{
	mKey = key ;
}

//-------------------------------------------------------------------------------------------------------------
bool GenericFeature::isSet() const
{
	if (!mKey)
		return false ;

	if (mFeatures == IGenericFeature::GenericFeatureType::NO_FEATURES)
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void GenericFeature::show(std::ostream& os) const
{
	os << "Features Set?.............: " << (isSet() ? "YES" : "NO") << std::endl ;
	os << "Features Code.............: " << encodeFeatures() << std::endl ;
	os << "Features: " << std::endl ;

	const unsigned WIDTH{24} ;
	const unsigned WIDTH_STEP{8} ;

	uint32_t validMask(static_cast<uint32_t>(mValidFeatures)) ;

	unsigned width(WIDTH) ;
	for (unsigned bit=0; bit < 32; ++bit)
	{
		uint32_t mask{1u<<bit} ;
		if (! (mask & validMask) )
			continue ;

		std::string name(featureName(static_cast<IGenericFeature::GenericFeatureType>(mask))) ;
		if (width < name.size())
			width = WIDTH + (((name.size() - WIDTH) / WIDTH_STEP) + 1) * WIDTH_STEP ;
	}

	std::bitset<32> bits( static_cast<uint32_t>(mFeatures) ) ;
	for (unsigned bit=0; bit < 32; ++bit)
	{
		uint32_t mask{1u<<bit} ;
		if (! (mask & validMask) )
			continue ;

		std::string name(featureName(static_cast<IGenericFeature::GenericFeatureType>(mask))) ;
		std::string pad( width - name.size(), '.') ;
		os << "  " << name << pad << ": " << (bits[bit] ? "Enabled" : "Not enabled") << std::endl ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool GenericFeature::checkSupported(const std::string& featureName) const
{
	IGenericFeature::GenericFeatureType feature(nameToFeature(featureName)) ;
	if (feature == IGenericFeature::GenericFeatureType::NO_FEATURES)
		return false ;

	// see if bit set
	return ( (feature & mFeatures) != IGenericFeature::GenericFeatureType::NO_FEATURES ) ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void GenericFeature::init()
{
	for (auto entry : mFeatureNames)
	{
		mValidFeatures |= static_cast<IGenericFeature::GenericFeatureType>(1<<entry.second) ;
	}

	mInvalidFeatures = static_cast<IGenericFeature::GenericFeatureType>(
			~static_cast<IGenericFeature::GenericFeatureType>(mValidFeatures)
		) ;
}

//-------------------------------------------------------------------------------------------------------------
IGenericFeature::GenericFeatureType GenericFeature::nameToFeature(const std::string& featureName) const
{
	auto entry(mFeatureNames.find(featureName)) ;
	if (entry == mFeatureNames.end())
		return IGenericFeature::GenericFeatureType::NO_FEATURES ;

	return static_cast<IGenericFeature::GenericFeatureType>(1<<(entry->second)) ;
}
