/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SinCos.hpp
 * \brief
 *
 *
 */

#ifndef FFT_INC_SINCOS_HPP_
#define FFT_INC_SINCOS_HPP_

#define _USE_MATH_DEFINES
#include <cmath>

// For reasons best known to themselves, the Windows cmath doesn't export the common defines. You have to add the _USE_MATH_DEFINES
// nonsense, and even then it doesn't always work (you have to make sure *everything* also defines _USE_MATH_DEFINES to ensure
// cmath sees it the first time it's actually loaded). It's just much easier to define the bloody thing myself!
#ifndef M_PI
#define M_PI 3.14159265358979323846 /* pi */
#endif

namespace Mplane {

/*!
 * \class  SinCos
 * \brief
 * \details
 *
 */
template <typename T, unsigned M>
struct SinCosSeries {
  inline static T
  value() {
    static T value(sin(M_PI / (T)M));
    return value;
  }
};

template <typename T>
struct SinCosSeries<T, 1> {
  inline static T
  value() {
    return 0.0;
  }
};

template <typename T>
struct SinCosSeries<T, 2> {
  inline static T
  value() {
    return 1.0;
  }
};

template <>
struct SinCosSeries<float, 4> {
  inline static float
  value() {
    return 0.707106781187f;
  }
};

template <>
struct SinCosSeries<float, 8> {
  inline static float
  value() {
    return 0.382683432365f;
  }
};

template <>
struct SinCosSeries<float, 16> {
  inline static float
  value() {
    return 0.195090322016f;
  }
};

template <>
struct SinCosSeries<float, 32> {
  inline static float
  value() {
    return 0.09801714033f;
  }
};

template <>
struct SinCosSeries<float, 64> {
  inline static float
  value() {
    return 0.049067674327f;
  }
};

template <>
struct SinCosSeries<float, 128> {
  inline static float
  value() {
    return 0.024541228523f;
  }
};

template <>
struct SinCosSeries<float, 256> {
  inline static float
  value() {
    return 0.012271538286f;
  }
};

template <>
struct SinCosSeries<float, 512> {
  inline static float
  value() {
    return 0.006135884649f;
  }
};

template <>
struct SinCosSeries<float, 1024> {
  inline static float
  value() {
    return 0.003067956763f;
  }
};

template <>
struct SinCosSeries<float, 2048> {
  inline static float
  value() {
    return 0.001533980186f;
  }
};

template <>
struct SinCosSeries<float, 4096> {
  inline static float
  value() {
    return 0.000766990319f;
  }
};

template <>
struct SinCosSeries<float, 8192> {
  inline static float
  value() {
    return 0.000383495188f;
  }
};

template <>
struct SinCosSeries<float, 16384> {
  inline static float
  value() {
    return 0.000191747597f;
  }
};

template <>
struct SinCosSeries<float, 32768> {
  inline static float
  value() {
    return 9.58737990959773e-05f;
  }
};

//-----------------------------------------------------
template <typename T, unsigned A, unsigned N>
struct Sin {
  inline static T
  value() {
    return SinCosSeries<T, N / A>::value();
  }
};

template <typename T>
struct Sin<T, 2, 1> {
  inline static T
  value() {
    return 0.0;
  }
};
}

#endif /* FFT_INC_SINCOS_HPP_ */
