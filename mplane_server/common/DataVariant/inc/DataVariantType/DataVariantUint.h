/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantUint.h
 * \brief     Provides access methods for UINT type
 *
 *
 * \details   Provides the methods used to access the DataVariant as an UINT
 *
 */

#ifndef DATAVARIANTUINT_H_
#define DATAVARIANTUINT_H_

#include "DataVariantTypeBase.h"
#include "IDvUint.h"

namespace Mplane {

class DataVariantUint : public DataVariantTypeBase, public virtual IDvUint {
 public:
  explicit DataVariantUint(std::shared_ptr<IDvType>& dv);
  virtual ~DataVariantUint();

  /**
   * Set the value of the the variant to the unsigned value. If the variant
   * is type Uint, the value is cast to a unsigned internally.
   *
   *
   * @param value
   */
  virtual bool setUint(unsigned value) override;

  /**
   * Method returns the current variant value as an unsigned
   *
   * @return variant value as an unsigned
   */
  virtual unsigned toUint() const override;
};

} // namespace Mplane

#endif /* DATAVARIANTUINT_H_ */
