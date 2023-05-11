/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FftBuilders.hpp
 * \brief
 *
 *
 */


#ifndef FFT_INC_IMPL_FFTBUILDERS_HPP_
#define FFT_INC_IMPL_FFTBUILDERS_HPP_

#include <memory>

namespace Mplane {

template<typename T>
class FftCalcBuilder {
public:

	//=============================================================================================================
	// FACTORY
	//=============================================================================================================

	//-------------------------------------------------------------------------------------------------------------
	inline static std::shared_ptr<IFftCalc<T>> factory(unsigned numPoints)
	{
		switch(numPoints)
		{
		case 32768:
			return std::make_shared< FftCalc<T, 32768, 0> >() ;
			break ;
		case 16384:
			return std::make_shared< FftCalc<T, 16384, 0> >() ;
			break ;
		case 8192:
			return std::make_shared< FftCalc<T, 8192, 0> >() ;
			break ;
		case 4096:
			return std::make_shared< FftCalc<T, 4096, 0> >() ;
			break ;
		case 2048:
			return std::make_shared< FftCalc<T, 2048, 0> >() ;
			break ;
		case 1024:
			return std::make_shared< FftCalc<T, 1024, 0> >() ;
			break ;
		case 512:
			return std::make_shared< FftCalc<T, 512, 0> >() ;
			break ;
		case 256:
			return std::make_shared< FftCalc<T, 256, 0> >() ;
			break ;
		case 128:
			return std::make_shared< FftCalc<T, 128, 0> >() ;
			break ;
		case 64:
			return std::make_shared< FftCalc<T, 64, 0> >() ;
			break ;
		case 32:
			return std::make_shared< FftCalc<T, 32, 0> >() ;
			break ;
		case 16:
			return std::make_shared< FftCalc<T, 16, 0> >() ;
			break ;
		case 8:
			return std::make_shared< FftCalc<T, 8, 0> >() ;
			break ;
		default:
			break ;
		}

		return std::shared_ptr<IFftCalc<T>>() ;
	}

};

template<typename T>
class InverseFftCalcBuilder {
public:

	//=============================================================================================================
	// FACTORY
	//=============================================================================================================

	//-------------------------------------------------------------------------------------------------------------
	inline static std::shared_ptr<IFftCalc<T>> factory(unsigned numPoints)
	{
		switch(numPoints)
		{
		case 32768:
			return std::make_shared< FftCalc<T, 32768, 1> >() ;
			break ;
		case 16384:
			return std::make_shared< FftCalc<T, 16384, 1> >() ;
			break ;
		case 8192:
			return std::make_shared< FftCalc<T, 8192, 1> >() ;
			break ;
		case 4096:
			return std::make_shared< FftCalc<T, 4096, 1> >() ;
			break ;
		case 2048:
			return std::make_shared< FftCalc<T, 2048, 1> >() ;
			break ;
		case 1024:
			return std::make_shared< FftCalc<T, 1024, 1> >() ;
			break ;
		case 512:
			return std::make_shared< FftCalc<T, 512, 1> >() ;
			break ;
		case 256:
			return std::make_shared< FftCalc<T, 256, 1> >() ;
			break ;
		case 128:
			return std::make_shared< FftCalc<T, 128, 1> >() ;
			break ;
		case 64:
			return std::make_shared< FftCalc<T, 64, 1> >() ;
			break ;
		case 32:
			return std::make_shared< FftCalc<T, 32, 1> >() ;
			break ;
		case 16:
			return std::make_shared< FftCalc<T, 16, 1> >() ;
			break ;
		case 8:
			return std::make_shared< FftCalc<T, 8, 1> >() ;
			break ;
		default:
			break ;
		}

		return std::shared_ptr<IFftCalc<T>>() ;
	}

};


// Generate compiler error if attempting to build INT fft
template<>
class FftCalcBuilder<int> {
	enum {
		ERROR_invalid_FFT_type_INT = 1 / 5,
	};
} ;

template<>
class InverseFftCalcBuilder<int> {
	enum {
		ERROR_invalid_IFFT_type_INT = 1 / 5,
	};
} ;

}

#endif /* FFT_INC_IMPL_FFTBUILDERS_HPP_ */
