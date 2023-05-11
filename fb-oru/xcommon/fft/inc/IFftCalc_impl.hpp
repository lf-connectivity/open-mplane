/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFftCalc_impl.hpp
 * \brief     Hidden intermediate template class used as a building block
 *
 *
 */


#ifndef FFT_INC_IMPL_IFFTCALC_IMPL_HPP_
#define FFT_INC_IMPL_IFFTCALC_IMPL_HPP_

#include "IFftCalc.h"

namespace Mplane {

/*!
 * \class  IFftCalc_impl
 * \brief
 * \details
 *
 */
template<typename T, unsigned N>
class IFftCalc_impl : public IFftCalc<T> {
public:
	IFftCalc_impl() {}
	virtual ~IFftCalc_impl() {}

	virtual void fft(T* /* data */) override {}

	virtual void fftshift(T* /* data */) override {}

	inline virtual unsigned size() const override
	{
		return N ;
	}

} ;

}

#endif /* FFT_INC_IMPL_IFFTCALC_IMPL_HPP_ */
