/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeString.h
 * \brief     Represents DataVariant type "STRING"
 *
 *
 * \details
 *
 */

#ifndef DvTypeString_H_
#define DvTypeString_H_

#include "DvTypeBase.h"
#include "IDvString.h"

namespace Mplane {

class DvTypeString : public virtual IDvString, public DvTypeBase {
 public:
  explicit DvTypeString(const std::string& typeStr = "");
  virtual ~DvTypeString();

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
   * Get the DataVariant type as a string, ie, INT, FLOAT, HEXINT, STRING, ENUM
   * @return variant type as a string
   */
  virtual const std::string getTypeStr() const override;

  /**
   * Get the DataVariant type
   * @return variant type
   */
  virtual const DataVariantType::Type getType() const override;

  /**
   * Method used to return the data variant value string
   *
   * @return value string
   */
  virtual std::string getValue() const override;

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
};

} // namespace Mplane

#endif /* DvTypeString_H_ */
