/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeDouble.h
 * \brief     Represents DataVariant type "DOUBLE"
 *
 *
 * \details
 *
 */

#ifndef DvTypeDouble_H_
#define DvTypeDouble_H_

#include "DvTypeBase.h"
#include "IDvDouble.h"

namespace Mplane {

class DvTypeDouble : public virtual IDvDouble, public DvTypeBase {
 public:
  explicit DvTypeDouble(const std::string& typeStr = "");
  virtual ~DvTypeDouble();

  /**
   * Can this type have units (e.g. KHz)
   */
  virtual bool canHaveUnits() const override;

  /**
   * Can we set the value of this particular type using the specified string?
   * @param value string
   * @return true if the value string is valid for setting this type
   */
  virtual bool canSetValue(const std::string& value) const override;

  /**
   * Can we set this particular type using the specified string?
   * @param type string
   * @return true if the type string is valid for setting this type
   */
  virtual bool canSetType(const std::string& type) const override;

  /**
   * Clears out any current value
   */
  virtual void clear() override;

  /**
   * Get the DataVariant type as a string, ie, INT, DOUBLE, HEXINT, STRING, ENUM
   * @return variant type as a string
   */
  virtual const std::string getTypeStr() const override;

  /**
   * Get the DataVariant limits as a string, "{min..max/step}"
   * @return limits as a string
   */
  virtual const std::string getLimitsStr() const override;

  /**
   * Get the DataVariant limits minimum setting as a string
   * @return minimum as a string or empty string if not set
   */
  virtual const std::string getLimitsMin() const override;

  /**
   * Get the DataVariant limits maximum setting as a string
   * @return maximum as a string or empty string if not set
   */
  virtual const std::string getLimitsMax() const override;

  /**
   * Get the DataVariant limits step setting as a string
   * @return step as a string or empty string if not set
   */
  virtual const std::string getLimitsStep() const override;

  /**
   * Get the DataVariant type
   * @return variant type
   */
  virtual const DataVariantType::Type getType() const override;

  /**
   * Sets limits for either an INT or DOUBLE type ; does nothing for any other
   * type
   * @param limitsStr    String in the format "min..max/step"
   * @return true if set ok (or type not INT/DOUBLE); false on error
   */
  virtual bool setLimits(const std::string& limitsStr) override;

  /**
   * Set limits from min/max/step strings
   * @param minStr
   * @param maxStr
   * @param stepStr
   * @return true if set ok (or type not INT/DOUBLE); false on error
   */
  virtual bool setLimits(
      const std::string& minStr,
      const std::string& maxStr,
      const std::string& stepStr) override;

  /**
   * Check the INT/DOUBLE type current value against any set limits. Note that
   * this method may adjust the value based on the limits setting.
   * @return false if INT/DOUBLE value does not match limits; true otherwise
   */
  virtual bool checkLimits(std::string& error) override;

  // IDvDouble

  /**
   * Method returns the current variant value as a double
   *
   * @return variant value as a double.
   */
  virtual double toDouble() const override;

  /**
   * Set the value of the variant to the double value. If the variant is
   * type Int, the value is cast to an integer internally.
   *
   * @param value
   */
  virtual bool setDouble(double value) override;

  // IDvAccess

  /**
   * Set value using string
   * @param value
   * @return true if value string is valid
   */
  virtual bool set(const std::string& value) override;

  /**
   * Convert from specific type to intermediate type
   */
  virtual IDvAccess::InterInt toInterInt() const override;

  /**
   * Convert from specific type to intermediate type
   */
  virtual IDvAccess::InterFloat toInterFloat() const override;

  /**
   * Convert from intermediate type to specific type
   * @param value
   * @return false on error
   */
  virtual bool fromInterInt(const IDvAccess::InterInt& value) override;

  /**
   * Convert from intermediate type to specific type
   * @param value
   * @return false on error
   */
  virtual bool fromInterFloat(const IDvAccess::InterFloat& value) override;

 private:
  double mDouble; //<! DOUBLE

  // INT limits
  Limits<double> mLimits;
};

} // namespace Mplane

#endif /* DvTypeDouble_H_ */
