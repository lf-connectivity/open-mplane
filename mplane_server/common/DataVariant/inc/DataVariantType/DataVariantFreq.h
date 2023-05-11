/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantFreq.h
 * \brief
 *
 *
 * \details
 *
 */

#ifndef DATAVARIANTFREQ_H_
#define DATAVARIANTFREQ_H_

#include "DataVariantTypeBase.h"
#include "IDvFreq.h"

namespace Mplane {

class DataVariantFreq : public DataVariantTypeBase, public virtual IDvFreq {
 public:
  explicit DataVariantFreq(std::shared_ptr<IDvType>& dv);
  virtual ~DataVariantFreq();

  /**
   * Set the value of the the variant to the frequency value.
   *
   * @param value
   */
  virtual bool setFreq(const Frequency& value) override;

  /**
   * Method returns the current variant value as a frequency
   *
   * @return variant value as a frequency
   */
  virtual Frequency toFreq() const override;
};

} // namespace Mplane

#endif /* DATAVARIANTFREQ_H_ */
