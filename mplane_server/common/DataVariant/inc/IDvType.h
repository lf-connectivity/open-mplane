/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvType.h
 * \brief     Interface to DataVariant types
 *
 *
 * \details
 *
 */

#ifndef IDVTYPE_H_
#define IDVTYPE_H_

#include <complex>
#include <memory>
#include <string>

#include "DataVariantType.h"
#include "IDvAccess.h"

namespace Mplane {

class IDvType : public virtual IDvAccess {
 public:
  IDvType() {}
  virtual ~IDvType() {}

  /**
   * Can we set the value of this particular type using the specified string?
   * @param value string
   * @return true if the value string is valid for setting this type
   */
  virtual bool canSetValue(const std::string& value) const = 0;

  /**
   * Can we set this particular type using the specified string?
   * @param type string
   * @return true if the type string is valid for setting this type
   */
  virtual bool canSetType(const std::string& type) const = 0;

  /**
   * Can this type have units (e.g. KHz)
   */
  virtual bool canHaveUnits() const = 0;

  /**
   * Clears out any current value
   */
  virtual void clear() = 0;

  /**
   * Has the value been initialised
   * @return true if the value has been initialised
   */
  virtual bool isSet() const = 0;

  /**
   * Get the DataVariant type as a string, ie, INT, FLOAT, HEXINT, STRING, ENUM
   * @return variant type as a string
   */
  virtual const std::string getTypeStr() const = 0;

  /**
   * Get the DataVariant limits as a string, "{min..max/step}"
   * @return limits as a string
   */
  virtual const std::string getLimitsStr() const = 0;

  /**
   * Get the DataVariant limits minimum setting as a string
   * @return minimum as a string or empty string if not set
   */
  virtual const std::string getLimitsMin() const = 0;

  /**
   * Get the DataVariant limits maximum setting as a string
   * @return maximum as a string or empty string if not set
   */
  virtual const std::string getLimitsMax() const = 0;

  /**
   * Get the DataVariant limits step setting as a string
   * @return step as a string or empty string if not set
   */
  virtual const std::string getLimitsStep() const = 0;

  /**
   * Get the DataVariant type
   * @return variant type
   */
  virtual const DataVariantType::Type getType() const = 0;

  /**
   * Is the value hex
   * @return true if value is in hex
   */
  virtual const bool isHex() const = 0;

  /**
   * Sets limits for either an INT or FLOAT type ; does nothing for any other
   * type
   * @param limitsStr    String in the format "min..max/step"
   * @return true if set ok (or type not INT/FLOAT); false on error
   */
  virtual bool setLimits(const std::string& limitsStr) = 0;

  /**
   * Set limits from min/max/step strings
   * @param minStr
   * @param maxStr
   * @param stepStr
   * @return true if set ok (or type not INT/FLOAT); false on error
   */
  virtual bool setLimits(
      const std::string& minStr,
      const std::string& maxStr,
      const std::string& stepStr) = 0;

  /**
   * Check the INT/FLOAT type current value against any set limits. Note that
   * this method may adjust the value based on the limits setting.
   * @return false if INT/FLOAT value does not match limits; true otherwise
   */
  virtual bool checkLimits(std::string& error) = 0;
  virtual bool checkLimits() = 0;

  /**
   * Method used to return the data variant value string
   *
   * @return value string
   */
  virtual std::string getValue() const = 0;

  /**
   * Set the units string
   * @param units string representing the value units (e.g. "dB", "W", "kHz"
   * etc)
   */
  virtual void setUnits(const std::string& units) = 0;

  /**
   * Get the units string
   * @return units string (which may be empty)
   */
  virtual const std::string getUnits() const = 0;
};

} // namespace Mplane

#endif /* IDVTYPE_H_ */
