#ifndef _COMMON_SPLINE_H_
#define _COMMON_SPLINE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Spline.hpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <vector>

namespace Mplane
{

class Spline
{

public:

    Spline();

    ~Spline();

    void addpoint(float vx, float vy);

    float getY(float atX);

    float getX(float atY);

    float getMaxX();

    float getMinX();

    float getPenultimateX();

    void reset();

    float getYlinExtrap(float atX);

private:

    int calculateSecondDerivativesY();

    int calculateSecondDerivativesX();

    bool yderivitives_exist;

    bool xderivitives_exist;

    int n;

    std::vector<float> mXSrcData;

    std::vector<float> mYSrcData;

    std::vector<float> y2;

    std::vector<float> x2;

    std::vector<float> uu;

    float yp1;
    float ypn;

    float xp1;
    float xpn;

};

}

#endif /* _SPLINE_HPP_ */
