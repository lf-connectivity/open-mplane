/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantEnum.h
 * \brief     Provides access methods for INT type
 *
 *
 * \details   Provides the methods used to access the DataVariant as an ENUM
 *
 */

#ifndef DataVariantEnum_H_
#define DataVariantEnum_H_

#include "DataVariantTypeBase.h"
#include "DvType/IDvEnum.h"

namespace Mplane {

class DataVariantEnum : public DataVariantTypeBase, public virtual IDvEnum {
 public:
  explicit DataVariantEnum(std::shared_ptr<IDvType>& dv);
  virtual ~DataVariantEnum();

  // IDvEnum

  /**
   * Set the value of the the variant to the integer value of the enumeration
   *
   * @param value
   */
  virtual bool setEnum(int value) override;

  /**
   * Method returns the current variant value as an integer (representing the
   * enumeration value)
   *
   * @return variant value as an integer
   */
  virtual int toEnum() const override;
};

} // namespace Mplane

#endif /* DataVariantEnum_H_ */
