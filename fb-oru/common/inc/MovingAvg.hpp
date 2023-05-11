#ifndef _MOVINGAVG_HPP_
#define _MOVINGAVG_HPP_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MovingAvg.hpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "stddef.h"
#include <vector>

namespace Mplane
{

template<class T>
class MovingAvg
{
public:
    /**
     * Constructor
     */
    MovingAvg( ):
        mSize( 10 ),
        mInitialised(false)
    {
        mData.resize( mSize );
    }
    /**
     * Virtual destructor
     */
    virtual ~MovingAvg()
    {
    }

    void setSize( size_t size )
    {
        if( mInitialised )
        {
            std::vector<T> copyData;
            copyData = mData;
            unsigned int fromIndex = mSize - 1;
            mData.resize( size );
            if( size != mSize  )
            {
                T avg(0);
                for( int index = size - 1; index >= 0 ; index--, fromIndex-- )
                {

                    mData[index ] = copyData[fromIndex];
                    if( size > mSize && fromIndex == 0)
                    {
                        fromIndex++;    // keep copying the oldest
                    }
                    if( index == (int)(size - 1 ))
                    {
                        avg = mData[index];
                    }
                    else
                    {
                        avg += mData[index];
                    }
                }

                avg = avg / (T) size;
                mAvg = avg;

            }
        }
        else
        {
            mData.resize(size);
        }
        mSize = size;

    }


    void add(T value)
    {
        if( mInitialised )
        {
            moveDown( value );  // this will change the min max values.
        }
        else
        {
            // first time in with first value so make this min and max
            mMin = value;
            mMax = value;
            fill ( value );
            mInitialised = true;
        }
    }

    T get()
    {
        return mAvg;
    }

    T variation()
    {
        return mMax - mMin;
    }

protected:

    void fill( T& value )
    {
        T avg = mData[0] = value;
        for( unsigned int count = 1; count  < mSize; count++ )
        {
            mData[ count ] = value;
            avg += value;
        }
        avg = avg / (T) mSize;
        mAvg = avg;
    }

    void moveDown( T& value )
    {
        /* remove the lowest bin value (mData[0]), shift remaining
           values up by one, then set top bin to the new value.
           Calculate the average on completion */
    	T avg;

    	if (mSize>1)
    	{
    		avg = mData[1];
    	}
    	else
    	{
    		avg = value;
    	}

        for( unsigned int count = 0; count  < mSize; count++ )
        {
            if( count < (mSize - 1))
            {
                mData[count] = mData[count + 1];
            }
            else
            {
                mData[count] = value;
            }
            if( count > 0)
            {
                avg += mData[count];
            }
            setMinMax( mData[count] );
        }
        avg = avg / (T) mSize;
        mAvg = avg;
    }

    void setMinMax( T& value )
    {
        if( value < mMin )
        {
            mMin = value;
        }
        if( value > mMax )
        {
            mMax = value;
        }
    }

    size_t mSize;
    std::vector<T> mData;
    bool mInitialised;
    T mAvg;
    T mMax;
    T mMin;
};



}




#endif /* _MOVINGAVG_HPP_ */
