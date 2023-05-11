/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegModel.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RegModel.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RegModel::RegModel(const std::string& name, unsigned numAddressBits, unsigned numDataBits, unsigned addressLSB) :
	mName(name),
	mAddrWidth( numAddressBits ),
	mDataWidth( numDataBits ),
	mAddrLSB( addressLSB ),
	mNumRegs( 1 << mAddrWidth ),
	mDataMask( (uint32_t)(((uint64_t)1 << mDataWidth)-1) ),
	mRegs(mNumRegs, SetVal<uint32_t>())
{
	IRegModelMgr::singleton()->addModel(this) ;
}

//-------------------------------------------------------------------------------------------------------------
RegModel::~RegModel()
{
	IRegModelMgr::singleton()->delModel(this) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RegModel::name() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned RegModel::addressWidth() const
{
	return mAddrWidth ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned RegModel::dataWidth() const
{
	return mDataWidth ;
}

//-------------------------------------------------------------------------------------------------------------
bool RegModel::isPaged() const
{
	return false;
}

//-------------------------------------------------------------------------------------------------------------
void RegModel::setReadPage(unsigned page)
{
	// NO OP
}

//-------------------------------------------------------------------------------------------------------------
uint32_t RegModel::regValue(uint32_t regNumber) const
{
	if (regNumber >= mNumRegs)
		return 0 ;

	return mRegs.at(regNumber).get() ;
}

//-------------------------------------------------------------------------------------------------------------
bool RegModel::regIsSet(uint32_t regNumber) const
{
	if (regNumber >= mNumRegs)
		return false ;

	return mRegs.at(regNumber).isSet() ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<SetVal<uint32_t> > RegModel::regs() const
{
	return mRegs ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint32_t> RegModel::regValues() const
{
	std::vector<uint32_t> values(mNumRegs, 0) ;
	for (unsigned i=0; i < mNumRegs; ++i)
	{
		if (!mRegs.at(i).isSet())
			continue ;
		values[i] = mRegs.at(i).get() ;
	}
	return values ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint32_t> RegModel::deviceValues() const
{
	// see if data needs to be shifted
	unsigned dataShift(0) ;
	if ( mDataWidth > mAddrLSB )
	{
		dataShift = mAddrWidth + mAddrLSB ;
	}

	// Create the set of register values as if read from device (i.e. with address and data inserted into the appropriate bits)
	std::vector<uint32_t> values(mNumRegs, 0) ;
	for (unsigned i=0; i < mNumRegs; ++i)
	{
		if (!mRegs.at(i).isSet())
			continue ;

		uint32_t data(mRegs.at(i).get()) ;
		if (dataShift > 0)
			data <<= dataShift ;

		values[i] = data;

		//Check if address LSB is within the range of the register size
		if (addressLSB() < (sizeof(uint32_t) << 3))
			values[i] |= (i << addressLSB()) ;
	}
	return values ;
}

//-------------------------------------------------------------------------------------------------------------
void RegModel::updateWrite(uint32_t offset, uint32_t data)
{
	updateModel(offset, data) ;
}

//-------------------------------------------------------------------------------------------------------------
void RegModel::updateWrite(uint32_t offset, const std::vector<uint8_t> &data)
{
	// NO OP
}

//-------------------------------------------------------------------------------------------------------------
void RegModel::updateWrite(const std::vector<uint8_t> &data)
{
	// NO OP
}

//-------------------------------------------------------------------------------------------------------------
void RegModel::updateRead(uint32_t offset, uint32_t data)
{
	updateModel(offset, data) ;
}

//-------------------------------------------------------------------------------------------------------------
void RegModel::updateRead(uint32_t offset, const std::vector<uint8_t> &data)
{
	// NO OP
}

//-------------------------------------------------------------------------------------------------------------
void RegModel::updateRead(const std::vector<uint8_t> &data)
{
	// NO OP
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void RegModel::updateModel(uint32_t offset, uint32_t data)
{
	if (offset >= mNumRegs)
		return ;

	mRegs[offset] = data & mDataMask ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned RegModel::addressLSB() const
{
	return mAddrLSB;
}

//-------------------------------------------------------------------------------------------------------------
unsigned RegModel::dataMask() const
{
	return mDataMask;
}

//-------------------------------------------------------------------------------------------------------------
unsigned RegModel::numRegs() const
{
	return mNumRegs;
}
