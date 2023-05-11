/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FftComplex.hpp
 * \brief
 *
 *
 */


#ifndef FFT_INC_IMPL_FFTCOMPLEX_HPP_
#define FFT_INC_IMPL_FFTCOMPLEX_HPP_

#include <algorithm>
#include <complex>

#include "IFftCalc_impl.hpp"
#include "SinCos.hpp"

namespace Mplane {

template<typename T, unsigned N>
class DanielsonLanczosCx {
public:
   void apply(std::complex<T>* cx) {

	  unsigned Nby2(N >> 1) ;
      next.apply(cx);
      next.apply(cx+Nby2);

      T wtemp,tempr,tempi,wr,wi,wpr,wpi;
      wtemp = Sin<T, 1, N>::value();
      wpr = (T)-2.0*wtemp*wtemp;
      wpi = -Sin<T, 2, N>::value();
      wr = 1.0;
      wi = 0.0;
      for (unsigned i=0; i<Nby2; ++i) {
        tempr = cx[i+Nby2].real()*wr - cx[i+Nby2].imag()*wi;
        tempi = cx[i+Nby2].real()*wi + cx[i+Nby2].imag()*wr;

        cx[i+Nby2] = std::complex<T>(cx[i].real()-tempr, cx[i].imag()-tempi) ;
        cx[i] = std::complex<T>(cx[i].real()+tempr, cx[i].imag()+tempi) ;

        wtemp = wr;
        wr += wr*wpr - wi*wpi;
        wi += wi*wpr + wtemp*wpi;
      }

   }

private:
   DanielsonLanczosCx<T, N/2> next;

};

template<typename T>
class DanielsonLanczosCx<T, 1> {
public:
   void apply(std::complex<T>* /* cx */) { }
};


template<typename T, unsigned N, unsigned Inverse=0>
class FftCx : public IFftCalc_impl<std::complex<T>, N> {
public:
	FftCx()
	{}

	virtual ~FftCx() {}

	virtual void fft(std::complex<T>* cx) override
	{
		const unsigned Nx2(N >> 1) ;

	    // reverse-binary re indexing
		unsigned j = 0;
		for (unsigned i=0; i < N-1; ++i)
		{
			if (i < j)
			{
				using std::swap ;
				swap(cx[i], cx[j]) ;
			}

			unsigned k = Nx2;
			while (k <= j)
			{
				j -= k;
				k >>= 1;
			}
			j += k;
		}

	    // The Danielson-Lanczos section
		if (!Inverse)
		{
			dl.apply(cx) ;
			return ;
		}

		// Inverse FFT
		std::complex<T>* cxp(cx) ;
		for (unsigned i=0; i < N; ++i, ++cxp)
		{
			*cxp = std::complex<T>(cxp->imag(), cxp->real()) ;
		}

		dl.apply(cx) ;

		// scale by 1/N
		T scale(1.0 / N) ;
		cxp = cx ;
		for (unsigned i=0; i < N; ++i, ++cxp)
		{
			*cxp = std::complex<T>(cxp->imag() * scale, cxp->real() * scale) ;
		}

	}

	virtual void fftshift(std::complex<T>* cx) override
	{
		unsigned halfSamples(N/2) ;
		std::complex<T>* cxp1(cx) ;
		std::complex<T>* cxp2(cx + halfSamples) ;
		for (unsigned i=0; i < halfSamples; ++i)
		{
			using std::swap ;
			swap(*cxp1++, *cxp2++) ;
		}
	}

	inline virtual unsigned size() const override
	{
		return N ;
	}

private:
   DanielsonLanczosCx<T, N> dl;

};

// Specialisations

template<unsigned N, unsigned Inverse>
class FftCalc<std::complex<float>, N, Inverse> : public FftCx<float, N, Inverse> {
public:
	FftCalc() : FftCx<float, N, Inverse>()
	{}

	virtual ~FftCalc() {}

	virtual void fft(std::complex<float>* data) override
	{
		FftCx<float, N, Inverse>::fft(data) ;
	}

	virtual void fftshift(std::complex<float>* data) override
	{
		FftCx<float, N, Inverse>::fftshift(data) ;
	}

};

template<unsigned N, unsigned Inverse>
class FftCalc<std::complex<double>, N, Inverse> : public FftCx<double, N, Inverse> {
public:
	FftCalc() : FftCx<double, N, Inverse>()
	{}

	virtual ~FftCalc() {}

	virtual void fft(std::complex<double>* data) override
	{
		FftCx<double, N, Inverse>::fft(data) ;
	}

	virtual void fftshift(std::complex<double>* data) override
	{
		FftCx<double, N, Inverse>::fftshift(data) ;
	}

};



}

#endif /* FFT_INC_IMPL_FFTCOMPLEX_HPP_ */
