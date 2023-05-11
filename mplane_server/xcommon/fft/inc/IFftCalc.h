/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFftCalc.h
 * \brief     Virtual interface to FFT
 *
 *
 */

#ifndef FFT_INC_IFftCalc_H_
#define FFT_INC_IFftCalc_H_

namespace Mplane {

/*!
 * \class  IFftCalc
 * \brief
 * \details
 *
 */
template <typename T>
class IFftCalc {
 public:
  IFftCalc() {}
  virtual ~IFftCalc() {}

  /**
   * Apply FFT to data array. Data is in the form of a vector. For float/double
   * types, IQ data will be stored as I followed by Q in pairs; for std::complex
   * types each entry is an IQ pair. FFT is performed in-place, the results
   * being returned in the same data array
   */
  virtual void fft(T* /* data */){};

  /**
   * Shift zero-frequency component to center of spectrum
   */
  virtual void fftshift(T* /* data */){};

  /**
   * Get the number of points used for this FFT
   */
  virtual unsigned
  size() const {
    return 0;
  };
};

} // namespace Mplane

#endif /* FFT_INC_IFftCalc_H_ */
