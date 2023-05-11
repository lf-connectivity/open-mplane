#ifndef _DATAVARIANTBASE_H_
#define _DATAVARIANTBASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantBase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <complex>
#include <memory>
#include <string>
#include <vector>

#include "IDvType.h"

#include "DataVariant/Limits.hpp"
#include "DataVariantType/DataVariantTypes.h"

namespace Mplane {

//----------------------------------------------------------------------------------------------------------------------
/**
 * The Mplane::DataVariant class is used to carry data between the RTI and the
 * underlying application code that implements the actual functions that call
 * the code base.
 *
 * The intermediate function, depending on its parameter requirements, is passed
 * a list of one or more DataVariant object. The values of the objects are set
 * and passed into the function and the function may also set the value to be
 * return to the caller.
 *
 * For more details of how the DataVariant is used by the RTI please see the
 * higher level RTI documentation.
 */
class DataVariantBase : public DataVariantTypes {
 public:
  // used in unit testing
  friend class DataVariantTestCase;

  /**
   * Create an unnamed empty data variant object with no type or valid data,
   * this type is usually used to make copies of data variants.
   */
  DataVariantBase();
  /**
   * Create a named data variant.
   *
   * If the name contains an equals sign then the string on the right hand side
   * will be used to set the value and type of the variant. See the set method
   * for details of the value.
   *
   * @param name
   */
  explicit DataVariantBase(const std::string& name);
  /**
   * Create a named data variant using a named typed, eg, INT, FLOAT, STRING or
   * ENUM.
   *
   * If the type is not valid the type will default to type INT.
   *
   * @param name
   * @param type
   */
  DataVariantBase(const std::string& name, const std::string& type);
  /**
   * Create a named data variant using a named typed
   *
   * If the type is not valid the type will default to type INT.
   *
   * @param type
   * @param name
   * @param value    Optional default value
   */
  DataVariantBase(
      const DataVariantType::Type& type,
      const std::string& name,
      const std::string& value = "");

  /**
   * Copy constructor used to create an instance of a data variant based upon an
   * existing variant.
   *
   * @param value variant to copy
   */
  DataVariantBase(const DataVariantBase& value);

  /**
   * Destructor
   */
  virtual ~DataVariantBase();

  /**
   * Equals operator used to assign the value of a variant from another
   * @param rhs
   * @return a reference to the object.
   */
  virtual DataVariantBase& operator=(const DataVariantBase& rhs);

  /**
   * Return a reference to the name string assigned to this object.
   *
   * @return variant name
   */
  virtual const std::string getName() const;

  /**
   * Return a lowercase copy of the name string assigned to this object.
   *
   * @return variant name in lowercase
   */
  virtual const std::string getLowerName() const;

  /**
   * Get the DataVariant type as a string, ie, INT, FLOAT, HEXINT, STRING, ENUM
   * @return variant type as a string
   */
  virtual const std::string getTypeStr() const;

  /**
   * Get the DataVariant limits as a string, "{min..max/step}"
   * @return limits as a string
   */
  virtual const std::string getLimitsStr() const;

  /**
   * Get the DataVariant limits minimum setting as a string
   * @return minimum as a string or empty string if not set
   */
  virtual const std::string getLimitsMin() const;

  /**
   * Get the DataVariant limits maximum setting as a string
   * @return maximum as a string or empty string if not set
   */
  virtual const std::string getLimitsMax() const;

  /**
   * Get the DataVariant limits step setting as a string
   * @return step as a string or empty string if not set
   */
  virtual const std::string getLimitsStep() const;

  /**
   * Get the DataVariant type
   * @return variant type
   */
  virtual const DataVariantType::Type getType() const;

  /**
   * Get the units string
   * @return units string (which may be empty)
   */
  virtual const std::string getUnits() const;

  /**
   * Is the value hex
   * @return true if value is in hex
   */
  virtual const bool isHex() const;

  /**
   * Method returns the current value of the variant as a string
   *
   * @return variant value as a string
   */
  virtual std::string toString() const;

  /**
   * Set the type based on a type string
   * @param type
   */
  virtual void setType(const std::string& type);

  /**
   * Set the value of a variant from another
   * @param rhs
   */
  virtual void set(const DataVariantBase& rhs);

  /**
   * Set the value of a variant from another
   * @param rhs
   */
  virtual void set(const DataVariantBase* rhs);

  /**
   * Set the value of a variant from another
   * @param rhs
   */
  virtual void set(const std::shared_ptr<DataVariantBase>& rhs);

  /**
   * Set the value of the variant using a pointer to a C style string.
   *
   * This function will set the value for the appropriate variant type
   * as defined by the constructor. If the type is not yet determined
   * then the string is parsed to decide on the type.
   *
   * @note Enum type values cannot be determined here, the Enum type must be set
   * prior to calling this method so that the valid enumeration values can be
   * determined.
   *
   * @note It will not changed the type of a variant once established.
   *
   * @param value
   */
  virtual void set(const std::string& value);

  /**
   * Force the "optional" flag to this state
   * @param optional Set optional flag to this state
   */
  void setOptional(bool optional);

  /**
   * Set default value using string
   * @param value
   */
  virtual void setDefault(const std::string& value);

  /**
   * Set the units string
   * @param units string representing the value units (e.g. "dB", "W", "kHz"
   * etc)
   */
  virtual void setUnits(const std::string& units);

  /**
   * Method used to return the data variant value string
   *
   * @return value string
   */
  virtual std::string getValue() const;

  /**
   * Method used to return the data variant value string. If the variable is
   * optional and an empty string then returns an empty string
   *
   * @return value string; or "" for empty optional variable
   */
  virtual std::string getValueOptional() const;

  /**
   * Method used to return the data variant name and its value as a pair,
   * separated with an equals sign.
   *
   * @param name Optional name that allows you to override the variable name for
   * display purposes
   * @return string in the form "name=value"
   */
  virtual std::string getNameValuePair(const std::string& name = "") const;

  /**
   * Method used to return the data variant name and its value as a pair,
   * separated with an equals sign. If the variable is optional and an empty
   * string then returns an empty string
   *
   * @param name Optional name that allows you to override the variable name for
   * display purposes
   * @return string in the form "name=value"; or "" for empty optional variable
   */
  virtual std::string getNameValuePairOptional(
      const std::string& name = "") const;

  /**
   * Get default value string
   * @return default value or empty string
   */
  virtual std::string getDefault() const;

  /**
   * Has the value been initialised
   * @return true if the value has been initialised
   */
  virtual bool isSet() const;

  /**
   * Is this an optional variable
   * @return true if optional flag set
   */
  virtual bool isOptional() const;

  /**
   * Clear out the value (so that it is no longer set)
   */
  virtual void clear();

  /**
   * Resets the variable to the empty state (type set to None) and all
   * values/flags cleared
   */
  virtual void reset();

  /**
   * Sets limits for either an INT or FLOAT type; does nothing for any other
   * type
   * @param limitsStr    String in the format "min..max/step"
   * @return true if set ok (or type not INT/FLOAT); false on error
   */
  virtual bool setLimits(const std::string& limitsStr);

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
      const std::string& stepStr);

  /**
   * Check the INT/FLOAT type current value against any set limits. Note that
   * this method may adjust the value based on the limits setting.
   * @return false if INT/FLOAT value does not match limits; true otherwise
   */
  virtual bool checkLimits(std::string& error);
  virtual bool checkLimits();

 private:
  /**
   * Is the optional string empty
   */
  bool isEmptyOptionalString() const;

 protected:
  std::string mName;
  std::string mLowerName; // used for comparisons

  std::shared_ptr<IDvType> mDv; // Actually implements the DataVariant value

  bool mIsOptional; //<! used by application for optional arguments

  // Default value (if not empty)
  std::string mDefault;
};

} // namespace Mplane

#endif /* _DATAVARIANTBASE_H_ */
