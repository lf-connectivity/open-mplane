/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierHardwareIeq.h
 * \brief     Inverse Equalisation carrier hardware virtual interface
 *
 *
 * \details
 *
 */


#ifndef ICARRIERHARDWAREIEQ_H_
#define ICARRIERHARDWAREIEQ_H_

#include <vector>
#include <complex>
#include <memory>

namespace Mplane {

/*!
 * \class ICarrierHardwareIeq
 */
class ICarrierHardwareIeq {
public:
	ICarrierHardwareIeq() {}
	virtual ~ICarrierHardwareIeq() {}

	/**
	 * Using the carrier index and antenna number, set the IEQ coefficients on the appropriate DL stream
	 * @param carrierIndex
	 * @param antenna
	 * @param coeffs
	 * @param failReason
	 * @return false and sets failReason on error; true on success
	 */
	virtual bool setIeqCoeffs(unsigned carrierIndex, unsigned antenna, const std::vector<std::complex<float>>& coeffs,
			std::string& failReason) =0 ;

	/**
	 * Using the carrier index and antenna number, gets the current IEQ coefficients from the appropriate DL stream
	 * @param carrierIndex
	 * @param antenna
	 * @param coeffs
	 * @param failReason
	 * @return false and sets failReason on error; true on success
	 */
	virtual bool getIeqCoeffs(unsigned carrierIndex, unsigned antenna, std::vector<std::complex<float>>& coeffs,
			std::string& failReason) const =0 ;

} ;

}

#endif /* ICARRIERHARDWAREIEQ_H_ */
