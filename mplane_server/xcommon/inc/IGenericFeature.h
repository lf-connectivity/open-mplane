/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IGenericFeature.h
 * \brief     Virtual interface to generic feature support
 *
 *
 * \details   Licensed SW is licensed to support one or more registered
 * features. Attempting to use a feature that this setup is not licensed for
 * will result in an error. The generic feature allows the application to
 * dynamically define the bits used and the name strings associated with those
 * bits (rather than defining them at build time using a static enum).
 *
 */

#ifndef IGENERICFEATURE_H_
#define IGENERICFEATURE_H_

#include "IKey.h"
#include <iostream>
#include <memory>
#include <string>

#include "IFeatureBase.h"

namespace Mplane {

class IGenericFeature : public virtual IFeatureBase {
 public:
  IGenericFeature() {}
  virtual ~IGenericFeature() {}

  /**
   * Generic feature bits
   */
  enum class GenericFeatureType {
    NO_FEATURES = 0,
  };

  /**
   * Factory for making feature objects
   * @param key
   */
  static std::shared_ptr<IGenericFeature> factory(
      const std::vector<std::string>& featureNames, std::shared_ptr<IKey> key);

  /**
   * Factory for making feature objects
   * @param key
   */
  static std::shared_ptr<IGenericFeature> factory(
      const std::map<std::string, unsigned>& featureNames,
      std::shared_ptr<IKey> key);

  /**
   * Factory for making supported feature object using the bitset of supported
   * features
   * @param key
   * @param features
   */
  static std::shared_ptr<IGenericFeature> factory(
      const std::vector<std::string>& featureNames,
      std::shared_ptr<IKey> key,
      GenericFeatureType features);

  /**
   * Factory for making supported feature object using the bitset of supported
   * features
   * @param key
   * @param features
   */
  static std::shared_ptr<IGenericFeature> factory(
      const std::map<std::string, unsigned>& featureNames,
      std::shared_ptr<IKey> key,
      GenericFeatureType features);

  /**
   * Factory for making supported feature object using the encoded public string
   * @param key
   * @param encodedFeatures
   */
  static std::shared_ptr<IGenericFeature> factory(
      const std::vector<std::string>& featureNames,
      std::shared_ptr<IKey> key,
      const std::string& encodedFeatures);

  /**
   * Factory for making supported feature object using the encoded public string
   * @param key
   * @param encodedFeatures
   */
  static std::shared_ptr<IGenericFeature> factory(
      const std::map<std::string, unsigned>& featureNames,
      std::shared_ptr<IKey> key,
      const std::string& encodedFeatures);

  /**
   * Singleton (created using the IKey singleton)
   */
  static std::shared_ptr<IGenericFeature> getInstance();

  /**
   * Convert single feature bit into a string
   * @param feature
   */
  virtual std::string featureName(GenericFeatureType feature) const = 0;

  /**
   * Are the features initialised?
   */
  virtual bool isSet() const = 0;

  /**
   * Specify the license key to use
   */
  virtual void setKey(std::shared_ptr<IKey> key) = 0;

  /**
   * Enable the specified feature (or features)
   * @param features    Bitset of features to enable
   */
  virtual bool enableFeature(GenericFeatureType features) = 0;

  /**
   * Enable the specified feature using the feature name
   * @param features    Bitset of features to enable
   */
  virtual bool enableFeature(const std::string& featureName) = 0;

  /**
   * Convert the supported features into a public string suitable for sharing
   * @return
   */
  virtual std::string encodeFeatures() const = 0;

  /**
   * Set up supported features from an encoded public string
   * @param encodedFeatures
   * @return false if invalid string
   */
  virtual bool setFeatures(const std::string& encodedFeatures) = 0;

  /**
   * Get the bitset of supported features
   */
  virtual GenericFeatureType supportedFeatures() const = 0;

  /**
   * Check that the supplied feature name is enabled
   * @param featureName
   * @return true if feature enabled
   */
  virtual bool checkSupported(const std::string& featureName) const = 0;

  /**
   * Display the complete list of all possible features and whether they are
   * enabled
   * @param os    Output stream
   */
  virtual void show(std::ostream& os = std::cout) const = 0;
};

inline IGenericFeature::GenericFeatureType
operator&(
    IGenericFeature::GenericFeatureType __a,
    IGenericFeature::GenericFeatureType __b) {
  return IGenericFeature::GenericFeatureType(
      static_cast<int>(__a) & static_cast<int>(__b));
}

inline IGenericFeature::GenericFeatureType
operator|(
    IGenericFeature::GenericFeatureType __a,
    IGenericFeature::GenericFeatureType __b) {
  return IGenericFeature::GenericFeatureType(
      static_cast<int>(__a) | static_cast<int>(__b));
}

inline IGenericFeature::GenericFeatureType
operator^(
    IGenericFeature::GenericFeatureType __a,
    IGenericFeature::GenericFeatureType __b) {
  return IGenericFeature::GenericFeatureType(
      static_cast<int>(__a) ^ static_cast<int>(__b));
}

inline IGenericFeature::GenericFeatureType&
operator|=(
    IGenericFeature::GenericFeatureType& __a,
    IGenericFeature::GenericFeatureType __b) {
  return __a = __a | __b;
}

inline IGenericFeature::GenericFeatureType&
operator&=(
    IGenericFeature::GenericFeatureType& __a,
    IGenericFeature::GenericFeatureType __b) {
  return __a = __a & __b;
}

inline IGenericFeature::GenericFeatureType&
operator^=(
    IGenericFeature::GenericFeatureType& __a,
    IGenericFeature::GenericFeatureType __b) {
  return __a = __a ^ __b;
}

inline IGenericFeature::GenericFeatureType
operator~(IGenericFeature::GenericFeatureType __a) {
  return IGenericFeature::GenericFeatureType(~static_cast<int>(__a));
}

} // namespace Mplane

// Convert any other value into the required GenericFeatureType
#define GENERIC_FEATURE(val) \
  static_cast<IGenericFeature::GenericFeatureType>(val)

#endif /* IGENERICFEATURE_H_ */
