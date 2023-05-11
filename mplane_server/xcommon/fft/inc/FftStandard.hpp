/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FftStandard.hpp
 * \brief     Template that implements FFT. Data is stored as I followed by Q in pairs
 *
 *
 */


#ifndef FFT_INC_IMPL_FFTSTANDARD_HPP_
#define FFT_INC_IMPL_FFTSTANDARD_HPP_

#include <algorithm>

#include "IFftCalc_impl.hpp"
#include "SinCos.hpp"

namespace Mplane {

template<typename T, unsigned N>
class DanielsonLanczosStd {
public:
   void apply(T* data) {
      next.apply(data);
      next.apply(data+N);

      T wtemp,tempr,tempi,wr,wi,wpr,wpi;
      wtemp = Sin<T, 1, N>::value();
      wpr = (T)-2.0*wtemp*wtemp;
      wpi = -Sin<T, 2, N>::value();
      wr = 1.0;
      wi = 0.0;
      for (unsigned i=0; i<N; i+=2) {
        tempr = data[i+N]*wr - data[i+N+1]*wi;
        tempi = data[i+N]*wi + data[i+N+1]*wr;
        data[i+N] = data[i]-tempr;
        data[i+N+1] = data[i+1]-tempi;
        data[i] += tempr;
        data[i+1] += tempi;

        wtemp = wr;
        wr += wr*wpr - wi*wpi;
        wi += wi*wpr + wtemp*wpi;
      }
   }

private:
   DanielsonLanczosStd<T, N/2> next;

};

template<typename T>
class DanielsonLanczosStd<T, 1> {
public:
   void apply(T* /* data */) { }
};


template<typename T, unsigned N, unsigned Inverse=0>
class FftCalc : public IFftCalc_impl<T, N> {
public:
 FftCalc() {}

 virtual ~FftCalc() {}

 virtual void
 fft(T* data) override {
   // reverse-binary re indexing
   unsigned n = N << 1;

   unsigned j = 1;
   for (unsigned i = 1; i < n; i += 2) {
     if (j > i) {
       using std::swap;
       swap(data[j - 1], data[i - 1]);
       swap(data[j], data[i]);
     }
     unsigned m = N;
     while (m >= 2 && j > m) {
       j -= m;
       m >>= 1;
     }
     j += m;
   };

   // The Danielson-Lanczos section
   if (!Inverse) {
     dl.apply(data);
     return;
   }

   // swap I & Q
   for (unsigned i = 1; i < n; i += 2) {
     using std::swap;
     swap(data[i - 1], data[i]);
   }

   // Inverse FFT
   dl.apply(data);

   // scale by 1/N and swap back
   T scale(1.0 / N);
   for (unsigned i = 1; i < n; i += 2) {
     T di = data[i] * scale;
     T di_1 = data[i - 1] * scale;

     data[i] = di_1;
     data[i - 1] = di;
   }
 }

 virtual void
 fftshift(T* data) override {
   // data is I&Q, so number data entries = 2 * mNumSamples
   unsigned halfSamples(N);
   T* dp1(data);
   T* dp2(data + halfSamples);
   for (unsigned i = 0; i < halfSamples; ++i) {
     using std::swap;
     swap(*dp1++, *dp2++);
   }
 }

 inline virtual unsigned
 size() const override {
   return N;
 }

private:
   DanielsonLanczosStd<T, N> dl;

};


}

#endif /* FFT_INC_IMPL_FFTSTANDARD_HPP_ */
