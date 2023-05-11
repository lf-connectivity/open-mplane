/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GenericFeature.h
 * \brief     Supported features class
 *
 *
 * \details   Licensed SW is licensed to support one or more registered
 * features. Attempting to use a feature that this setup is not licensed for
 * will result in an error. The generic feature allows the application to
 * dynamically define the bits used and the name strings associated with those
 * bits (rather than defining them at build time using a static enum).
 *
 */

#ifndef GENERICFEATURE_H_
#define GENERICFEATURE_H_

#include <map>
#include <vector>

#include "IGenericFeature.h"

namespace Mplane {

class GenericFeature : public virtual IGenericFeature {
 public:
  explicit GenericFeature(const std::vector<std::string>& featureNames);
  explicit GenericFeature(const std::map<std::string, unsigned>& featureNames);
  virtual ~GenericFeature();

  /**
   * Convert single feature bit into a string
   * @param feature
   */
  virtual std::string featureName(GenericFeatureType feature) const override;

  /**
   * Are the features initialised?
   */
  virtual bool isSet() const override;

  /**
   * Specify the license key to use
   */
  virtual void setKey(std::shared_ptr<IKey> key) override;

  /**
   * Enable the specified feature (or features)
   * @param features    Bitset of features to enable
   */
  virtual bool enableFeature(
      IGenericFeature::GenericFeatureType features) override;

  /**
   * Enable the specified feature using the feature name
   * @param features    Bitset of features to enable
   */
  virtual bool enableFeature(const std::string& featureName) override;

  /**
   * Convert the supported features into a public string suitable for sharing
   * @return
   */
  virtual std::string encodeFeatures() const override;

  /**
   * Set up supported features from an encoded public string
   * @param encodedFeatures
   * @return false if invalid string
   */
  virtual bool setFeatures(const std::string& encodedFeatures) override;

  /**
   * Get the bitset of supported features
   */
  virtual IGenericFeature::GenericFeatureType supportedFeatures()
      const override;

  /**
   * Check that the supplied feature name is enabled
   * @param featureName
   * @return true if feature enabled
   */
  virtual bool checkSupported(const std::string& featureName) const override;

  /**
   * Display the complete list of all possible features and whether they are
   * enabled
   * @param os    Output stream
   */
  virtual void show(std::ostream& os = std::cout) const override;

 private:
  void init();
  IGenericFeature::GenericFeatureType nameToFeature(
      const std::string& featureName) const;

 private:
  std::shared_ptr<IKey> mKey;
  IGenericFeature::GenericFeatureType mFeatures;
  std::map<std::string, unsigned> mFeatureNames;
  IGenericFeature::GenericFeatureType mValidFeatures;
  IGenericFeature::GenericFeatureType mInvalidFeatures;
};

} // namespace Mplane

#endif /* GENERICFEATURE_H_ */
