/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantInt.h
 * \brief     Provides access methods for INT type
 *
 *
 * \details   Provides the methods used to access the DataVariant as an INT
 *
 */

#ifndef DATAVARIANTINT_H_
#define DATAVARIANTINT_H_

#include "DataVariantTypeBase.h"
#include "IDvInt.h"

namespace Mplane {

class DataVariantInt : public DataVariantTypeBase, public virtual IDvInt {
 public:
  explicit DataVariantInt(std::shared_ptr<IDvType>& dv);
  virtual ~DataVariantInt();

  /**
   * Set the value of the the variant to the integer value. If the variant
   * is type Float, the value is cast to a float internally.
   *
   *
   * @param value
   */
  virtual bool setInt(int value) override;

  /**
   * Method returns the current variant value as an integer
   *
   * @return variant value as an integer
   */
  virtual int toInt() const override;
};

} // namespace Mplane

#endif /* DATAVARIANTINT_H_ */
