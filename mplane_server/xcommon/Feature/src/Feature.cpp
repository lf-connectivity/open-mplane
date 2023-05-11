/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Feature.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>
#include <bitset>
#include <cstdint>
#include <map>

#include "Feature.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const std::map<std::string, unsigned> FEATURE_NAMES{
    {"LTE_TDD_TM", 0},
    {"LTE_FDD_TM", 1},
    {"LTE_TDD_FRCA", 2},
    {"LTE_FDD_FRCA", 3},
    {"LTE_GUI_RX_BER", 31}};

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFeature>
IFeature::factory(std::shared_ptr<IKey> key) {
  std::shared_ptr<IFeature> feature(std::make_shared<Feature>());
  if (!feature)
    return feature;

  feature->setKey(key);
  return feature;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFeature>
IFeature::factory(std::shared_ptr<IKey> key, IFeature::FeatureType features) {
  std::shared_ptr<IFeature> feature(IFeature::factory(key));
  if (!feature)
    return feature;

  feature->enableFeature(features);
  return feature;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFeature>
IFeature::factory(
    std::shared_ptr<IKey> key, const std::string& encodedFeatures) {
  std::shared_ptr<IFeature> feature(IFeature::factory(key));
  if (!feature)
    return feature;

  if (!feature->setFeatures(encodedFeatures))
    return std::shared_ptr<IFeature>();

  return feature;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Feature::Feature() : mGenericFeature(FEATURE_NAMES) {}

//-------------------------------------------------------------------------------------------------------------
Feature::~Feature() {}

//-------------------------------------------------------------------------------------------------------------
std::string
Feature::featureName(IFeature::FeatureType feature) const {
  return mGenericFeature.featureName(GENERIC_FEATURE(feature));
}

//-------------------------------------------------------------------------------------------------------------
bool
Feature::enableFeature(IFeature::FeatureType features) {
  return mGenericFeature.enableFeature(GENERIC_FEATURE(features));
}

//-------------------------------------------------------------------------------------------------------------
bool
Feature::enableFeature(const std::string& featureName) {
  return mGenericFeature.enableFeature(featureName);
}

//-------------------------------------------------------------------------------------------------------------
std::string
Feature::encodeFeatures() const {
  return mGenericFeature.encodeFeatures();
}

//-------------------------------------------------------------------------------------------------------------
bool
Feature::setFeatures(const std::string& encodedFeatures) {
  return mGenericFeature.setFeatures(encodedFeatures);
}

//-------------------------------------------------------------------------------------------------------------
IFeature::FeatureType
Feature::supportedFeatures() const {
  return static_cast<IFeature::FeatureType>(
      mGenericFeature.supportedFeatures());
}

//-------------------------------------------------------------------------------------------------------------
void
Feature::setKey(std::shared_ptr<IKey> key) {
  mGenericFeature.setKey(key);
}

//-------------------------------------------------------------------------------------------------------------
bool
Feature::isSet() const {
  return mGenericFeature.isSet();
}

//-------------------------------------------------------------------------------------------------------------
void
Feature::show(std::ostream& os) const {
  mGenericFeature.show(os);
}

//-------------------------------------------------------------------------------------------------------------
bool
Feature::checkSupported(const std::string& featureName) const {
  return mGenericFeature.checkSupported(featureName);
}
