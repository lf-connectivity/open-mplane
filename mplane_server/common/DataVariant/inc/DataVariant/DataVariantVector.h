/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantVector.h
 * \brief     Utility class for converting DataVariants into std::vectors
 *
 *
 * \details   Class containing only static methods which use DataVariant methods
 * to convert a DataVariant into the appropriate std::vector
 *
 */

#ifndef DATAVARIANTVECTOR_H_
#define DATAVARIANTVECTOR_H_

#include "DataVariantClass.h"
#include "Frequency.h"
#include "Power.h"

namespace Mplane {

class DataVariantVector {
 public:
  /**
   * Checks to see that all elements in the vector (from min entry to max entry)
   * are set to some value. Returns false with the error string set if any
   * elements are not set
   * @param dv
   * @param error
   * @return true if all elements are set
   */
  static bool isVectorComplete(const DataVariant& dv, std::string& error);
  static bool isVectorComplete(const DataVariant* dv, std::string& error);

  // Convert from DataVariant vector into X

  /**
   * Convert a DataVariant array into a std::vector of ints.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<int> or empty vector with error string set on error
   */
  static std::vector<int> toIntVector(
      const DataVariant& dv, std::string& error);
  static std::vector<int> toIntVector(
      const DataVariant* dv, std::string& error);

  /**
   * Convert a DataVariant array into a std::vector of floats.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<float> or empty vector with error string set on error
   */
  static std::vector<float> toFloatVector(
      const DataVariant& dv, std::string& error);
  static std::vector<float> toFloatVector(
      const DataVariant* dv, std::string& error);

  /**
   * Convert a DataVariant array into a std::vector of complexs.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<std::complex<float>> or empty vector with error string
   * set on error
   */
  static std::vector<std::complex<float>> toComplexVector(
      const DataVariant& dv, std::string& error);
  static std::vector<std::complex<float>> toComplexVector(
      const DataVariant* dv, std::string& error);

  /**
   * Convert a DataVariant array into a std::vector of std::strings.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<std::string> or empty vector with error string set on
   * error
   */
  static std::vector<std::string> toStringVector(
      const DataVariant& dv, std::string& error);
  static std::vector<std::string> toStringVector(
      const DataVariant* dv, std::string& error);

  /**
   * Convert a DataVariant array into a std::vector of bools.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<bool> or empty vector with error string set on error
   */
  static std::vector<bool> toBoolVector(
      const DataVariant& dv, std::string& error);
  static std::vector<bool> toBoolVector(
      const DataVariant* dv, std::string& error);

  /**
   * Convert a DataVariant array into a std::vector of unsigned ints.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<unsigned> or empty vector with error string set on
   * error
   */
  static std::vector<unsigned> toUnsignedVector(
      const DataVariant& dv, std::string& error);
  static std::vector<unsigned> toUnsignedVector(
      const DataVariant* dv, std::string& error);

  /**
   * Convert a DataVariant array into a std::vector of Frequency objects.
   * Expects the DataVariant to optionally have a Frequency units specified.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<Frequency> or empty vector with error string set on
   * error
   */
  static std::vector<Frequency> toFrequencyVector(
      const DataVariant& dv, std::string& error);
  static std::vector<Frequency> toFrequencyVector(
      const DataVariant* dv, std::string& error);

  /**
   * Convert a DataVariant array into a std::vector of Power objects. Expects
   * the DataVariant to optionally have a Power units specified.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<Power> or empty vector with error string set on error
   */
  static std::vector<Power> toPowerVector(
      const DataVariant& dv, std::string& error);
  static std::vector<Power> toPowerVector(
      const DataVariant* dv, std::string& error);

  // Convert from X into DataVariant vector

  /**
   * Fill a DataVariant array from a std::vector of ints.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<int> or empty vector with error string set on error
   */
  static bool fromIntVector(
      const std::vector<int>& vec, DataVariant& dv, std::string& error);
  static bool fromIntVector(
      const std::vector<int>& vec, DataVariant* dv, std::string& error);

  /**
   * Fill a DataVariant array from a std::vector of floats.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<float> or empty vector with error string set on error
   */
  static bool fromFloatVector(
      const std::vector<float>& vec, DataVariant& dv, std::string& error);
  static bool fromFloatVector(
      const std::vector<float>& vec, DataVariant* dv, std::string& error);

  /**
   * Fill a DataVariant array from a std::vector of complexs.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<std::complex<float>> or empty vector with error string
   * set on error
   */
  static bool fromComplexVector(
      const std::vector<std::complex<float>>& vec,
      DataVariant& dv,
      std::string& error);
  static bool fromComplexVector(
      const std::vector<std::complex<float>>& vec,
      DataVariant* dv,
      std::string& error);

  /**
   * Fill a DataVariant array from a std::vector of std::strings.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<std::string> or empty vector with error string set on
   * error
   */
  static bool fromStringVector(
      const std::vector<std::string>& vec, DataVariant& dv, std::string& error);
  static bool fromStringVector(
      const std::vector<std::string>& vec, DataVariant* dv, std::string& error);

  /**
   * Fill a DataVariant array from a std::vector of bools.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<bool> or empty vector with error string set on error
   */
  static bool fromBoolVector(
      const std::vector<bool>& vec, DataVariant& dv, std::string& error);
  static bool fromBoolVector(
      const std::vector<bool>& vec, DataVariant* dv, std::string& error);

  /**
   * Fill a DataVariant array from a std::vector of unsigned ints.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<unsigned> or empty vector with error string set on
   * error
   */
  static bool fromUnsignedVector(
      const std::vector<unsigned>& vec, DataVariant& dv, std::string& error);
  static bool fromUnsignedVector(
      const std::vector<unsigned>& vec, DataVariant* dv, std::string& error);

  /**
   * Fill a DataVariant array from a std::vector of Frequency objects. Expects
   * the DataVariant to optionally have a Frequency units specified.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<Frequency> or empty vector with error string set on
   * error
   */
  static bool fromFrequencyVector(
      const std::vector<Frequency>& vec, DataVariant& dv, std::string& error);
  static bool fromFrequencyVector(
      const std::vector<Frequency>& vec, DataVariant* dv, std::string& error);

  /**
   * Fill a DataVariant array from a std::vector of Power objects. Expects the
   * DataVariant to optionally have a Power units specified.
   * @param dv    The DataVariant
   * @param error    Error string set on error
   * @return std::vector<Power> or empty vector with error string set on error
   */
  static bool fromPowerVector(
      const std::vector<Power>& vec, DataVariant& dv, std::string& error);
  static bool fromPowerVector(
      const std::vector<Power>& vec, DataVariant* dv, std::string& error);
};

} // namespace Mplane

#endif /* DATAVARIANTVECTOR_H_ */
