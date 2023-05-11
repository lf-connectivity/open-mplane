/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SplineInterpolator.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "Spline.h"


using namespace Mplane;


Spline::Spline()
{
    yp1 = ypn = 1e32f; //set boundary conditions to ensure a natural spline extension

    xp1 = xpn = 1e32f; //set boundary conditions to ensure a natural spline extension

    //yp1 = ypn = 0.0f; // creates sharp point, first derivative should not be zero

    reset();
}

Spline::~Spline()
{
    reset();
}
void Spline::addpoint(float vx, float vy)
{
    mXSrcData.push_back(vx);

    mYSrcData.push_back(vy);

    // std::cout << n << ", " << vx << ", " << vy << std::endl;

    n++;

    yderivitives_exist = false;
    xderivitives_exist = false;
}

float Spline::getY(float atX)
{

    //basic checks to ensure we can calculate something

    if (n < 2)
        return 0.0f;

    if (!yderivitives_exist)
        calculateSecondDerivativesY();

    //We will find the right place in the table by means of bisection. This is optimal if sequential calls to this

    //routine are at random values of x. If sequential calls are in order, and closely spaced, one would do better

    //to store previous values of klo and khi and test if they remain appropriate on the next call.


    int klo = 0;

    int khi = n - 1;

    while ( (khi - klo) > 1)
    {
        int k = (khi + klo) >> 1;

        if (((mXSrcData[k] > atX) && (mXSrcData[n-1] >= mXSrcData[0]))|| ((mXSrcData[k] < atX) && (mXSrcData[n-1] <= mXSrcData[0])))
            khi = k;
        else
            klo = k;

    }

    // klo and khi now bracket the input value of x.

    float h = mXSrcData[khi] - mXSrcData[klo];

    if (h == 0.0f)
        return 0.0f; //The xa's must be distinct

    float a = (mXSrcData[khi] - atX) / h;

    float b = (atX - mXSrcData[klo]) / h; //Cubic spline polynomial is now evaluated.

    float yinterp = a * mYSrcData[klo] + b * mYSrcData[khi]
            + ((a * a * a - a) * y2[klo] + (b * b * b - b) * y2[khi])
                    * (h * h) / 6.0f;

//    std::cout << "atX, " << yinterp << std::endl;

    return yinterp;

}

float Spline::getX(float atY)
{
    //basic checks to ensure we can calculate something

    if (n < 2)
        return 0.0f;
    if (!xderivitives_exist)
        calculateSecondDerivativesX();

    //We will find the right place in the table by means of bisection. This is optimal if sequential calls to this
    //routine are at random values of x. If sequential calls are in order, and closely spaced, one would do better
    //to store previous values of klo and khi and test if they remain appropriate on the next call.

    int klo = 0;

    int khi = n - 1;

    while ( (khi - klo) > 1 )
    {
        int k = (khi + klo) >> 1;

        if (((mYSrcData[k] > atY) && (mYSrcData[n-1] >= mYSrcData[0]))|| ((mYSrcData[k] < atY) && (mYSrcData[n-1] <= mYSrcData[0])))
            khi = k;
        else
            klo = k;

    }

    // klo and khi now bracket the input value of y.

    float h = mYSrcData[khi] - mYSrcData[klo];

    if (h == 0.0f)
        return 0.0f; //The ya's must be distinct

    float a = (mYSrcData[khi] - atY) / h;

    float b = (atY - mYSrcData[klo]) / h; //Cubic spline polynomial is now evaluated.

    float xinterp = a * mXSrcData[klo] + b * mXSrcData[khi]
            + ((a * a * a - a) * x2[klo] + (b * b * b - b) * x2[khi])
                    * (h * h) / 6.0f;

//    std::cout << "atY, " << xinterp << std::endl;

    return xinterp;
}

float Spline::getMaxX()
{
	if ( mXSrcData[n - 1] > mXSrcData[0] )
	{
		return mXSrcData[n - 1];
	}
	else
	{
		return mXSrcData[0];
	}
}

float Spline::getMinX()
{
	if( mXSrcData[n - 1] < mXSrcData[0] )
	{
		return mXSrcData[n - 1];
	}
	else
	{
		return mXSrcData[0];
	}
}

float Spline::getPenultimateX()
{
    return mXSrcData[n - 2];
}

void Spline::reset()
{
    n = 0;
    mXSrcData.clear();
    mYSrcData.clear();
    y2.clear();
    x2.clear();
    uu.clear();
    yderivitives_exist = false;
    xderivitives_exist = false;
}

int Spline::calculateSecondDerivativesY()
{

    int i, k;

    float qn, un;

    if (n > (int) y2.size())
    {
        y2.clear();
        uu.clear();
        y2.resize(n);
        uu.resize(n);
    }

    if (yp1 > 0.99e30) //The lower boundary condition is set either to be "natural"
    {
        y2[0] = uu[0] = 0.0f;
    }
    else
    { //Or else specify the second derivative

        y2[0] = -0.5f;

        uu[0] = (3.0f / (mXSrcData[1] - mXSrcData[0]))
                * ((mYSrcData[1] - mYSrcData[0])
                        / (mXSrcData[1] - mXSrcData[0]) - yp1);

    }

    for (i = 1; i <= n - 2; i++)
    { //This is the decomposition loop of the tridiagonal algorithm. y2 and u are used for temporary storage of the decomposed factors.

        float sig = (mXSrcData[i] - mXSrcData[i - 1])
                / (mXSrcData[i + 1] - mXSrcData[i - 1]);

        float p = sig * y2[i - 1] + 2.0f;

        y2[i] = (sig - 1.0f) / p;

        uu[i] = (mYSrcData[i + 1] - mYSrcData[i])
                / (mXSrcData[i + 1] - mXSrcData[i])
                - (mYSrcData[i] - mYSrcData[i - 1])
                        / (mXSrcData[i] - mXSrcData[i - 1]);

        uu[i] = (6.0f * uu[i] / (mXSrcData[i + 1] - mXSrcData[i - 1])
                - sig * uu[i - 1]) / p;

    }

    if (ypn > 0.99e30) //The upper boundary condition is set either to be "natural"
    {
        qn = un = 0.0f;
    }
    else
    { // or else a specified first derivitive

        qn = 0.5f;

        un = (3.0f / (mXSrcData[n - 1] - mXSrcData[n - 2]))
                * (ypn
                        - (mYSrcData[n - 1] - mYSrcData[n - 2])
                                / (mXSrcData[n - 1] - mXSrcData[n - 2]));

    }

    y2[n - 1] = (un - qn * uu[n - 2]) / (qn * y2[n - 2] + 1.0f);

    for (k = n - 2; k >= 0; k--) //This is the backsubstitution loop of the tridiagonal algorithm.

        y2[k] = y2[k] * y2[k + 1] + uu[k];

    yderivitives_exist = true;

    return 1;

}

int Spline::calculateSecondDerivativesX()
{

    int i, k;

    float qn, un;

    if (n > (int) x2.size())
    {
        x2.clear();
        uu.clear();
        x2.resize(n);
        uu.resize(n);
    }

    if (xp1 > 0.99e30) //The lower boundary condition is set either to be "natural"
    {
        x2[0] = uu[0] = 0.0f;
    }
    else
    { //Or else specify the second derivative

        x2[0] = -0.5f;

        uu[0] = (3.0f / (mYSrcData[1] - mYSrcData[0]))
                * ((mXSrcData[1] - mXSrcData[0])
                        / (mYSrcData[1] - mYSrcData[0]) - xp1);

    }

    for (i = 1; i <= n - 2; i++)
    { //This is the decomposition loop of the tridiagonal algorithm. x2 and ux are used for temporary storage of the decomposed factors.

        float sig = (mYSrcData[i] - mYSrcData[i - 1])
                / (mYSrcData[i + 1] - mYSrcData[i - 1]);

        float p = sig * x2[i - 1] + 2.0f;

        x2[i] = (sig - 1.0f) / p;

        uu[i] = (mXSrcData[i + 1] - mXSrcData[i])
                / (mYSrcData[i + 1] - mYSrcData[i])
                - (mXSrcData[i] - mXSrcData[i - 1])
                        / (mYSrcData[i] - mYSrcData[i - 1]);

        uu[i] = (6.0f * uu[i] / (mYSrcData[i + 1] - mYSrcData[i - 1])
                - sig * uu[i - 1]) / p;

    }

    if (xpn > 0.99e30) //The upper boundary condition is set either to be "natural"
    {
        qn = un = 0.0f;
    }
    else
    { // or else a specified first derivitive

        qn = 0.5f;

        un = (3.0f / (mYSrcData[n - 1] - mYSrcData[n - 2]))
                * (xpn
                        - (mXSrcData[n - 1] - mXSrcData[n - 2])
                                / (mYSrcData[n - 1] - mYSrcData[n - 2]));

    }

    x2[n - 1] = (un - qn * uu[n - 2]) / (qn * x2[n - 2] + 1.0f);

    for (k = n - 2; k >= 0; k--) //This is the back substitution loop of the tridiagonal algorithm.

        x2[k] = x2[k] * x2[k + 1] + uu[k];

    xderivitives_exist = true;

    return 1;

}

float Spline::getYlinExtrap(float atX)
{
	if (((atX < mXSrcData[0]) && (mXSrcData[0] < mXSrcData[n-1])) || ((atX > mXSrcData[0]) && (mXSrcData[0] > mXSrcData[n-1])))
	{
		return (atX-mXSrcData[0])*(mYSrcData[0]-mYSrcData[1])/(mXSrcData[0]-mXSrcData[1])+mYSrcData[0]; // extrapolate point before XSrcData[0]
	}
	else if (((atX > mXSrcData[n-1]) && (mXSrcData[n-1] > mXSrcData[0])) || ((atX < mXSrcData[n-1]) && (mXSrcData[n-1] < mXSrcData[0])))
	{
		return (atX-mXSrcData[n-1])*(mYSrcData[n-1]-mYSrcData[n-2])/(mXSrcData[n-1]-mXSrcData[n-2])+mYSrcData[n-1]; // extrapolate point after XSrcData[n-1]
	}
	else
	{
		return getY(atX); // do original spline interpolation
	}
}
