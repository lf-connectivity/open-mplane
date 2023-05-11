/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BusSettings.h
 * \brief     Base-level implementation of IBusSettings
 *
 *
 * \details   Set and read the bus transport endianess. Defaults to BIG endian
 *
 */


#ifndef COMMON_BUS_INC_BUSSETTINGS_H_
#define COMMON_BUS_INC_BUSSETTINGS_H_

#include "IBusSettings.h"

namespace Mplane {

/*!
 * \class  BusSettings
 * \brief
 * \details
 *
 */
class BusSettings : public virtual IBusSettings {
public:
	BusSettings() :
		mBigEndian(true),
		mOffsetNumBits(8)
	{}
	virtual ~BusSettings() {}

	// IBusSettings interface

	/**
	 * Data transported over the bus MS first
	 */
	virtual bool setBigEndian() override
	{
		mBigEndian = true ;
		return true ;
	}


	/**
	 * Data transported over the bus LS first
	 */
	virtual bool setLittleEndian() override
	{
		mBigEndian = false ;
		return true ;
	}

	/**
	 * Number of bits of offset used in read/write operations
	 */
	virtual bool setOffsetNumBits(unsigned size) override
	{
		mOffsetNumBits = size;
		return true;
	}


	// IBusReadonlySettings interface

	/**
	 * Is the data transported over the bus MS first?
	 * NOTE: This is only the data transport over the bus. The endpoint device may
	 * use the data in any endian
	 */
	virtual bool isBigEndian() const override
	{
		return mBigEndian ;
	}


	/**
	 * Is the data transported over the bus LS first?
	 * NOTE: This is only the data transport over the bus. The endpoint device may
	 * use the data in any endian
	 */
	virtual bool isLittleEndian() const override
	{
		return !mBigEndian ;
	}

	/**
	 * For read and write operations from an offset, this method indicates the
	 * size of the offset parameter in number of bits.
	 */
	virtual unsigned getOffsetNumBits() const override
	{
		return mOffsetNumBits;
	}

private:
	bool mBigEndian ;
	unsigned mOffsetNumBits;
} ;

}

#endif /* COMMON_BUS_INC_BUSSETTINGS_H_ */
