/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PagedRegModel.cpp
 * \brief     Model of a register set in a paged device
 *
 *
 * \details   Models the register set of any generic device with a paged register set
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PagedRegModel.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PagedRegModel::PagedRegModel(const std::string& name, unsigned numAddressBits, unsigned numDataBits,
		unsigned addressLSB, unsigned numPageBits, unsigned pageRegOffset) :
		RegModel(name, numAddressBits, numDataBits, addressLSB),
	mNumPages(1 << numPageBits),
	mReadPage(0),
	mWritePage(0),
	mPagedRegOffset(pageRegOffset)
{
	//Build the map with all supported page numbers
	for (unsigned index = 0; index < mNumPages; index++)
	{
		mRegs[index] = std::vector< SetVal<uint32_t> >(numRegs(), SetVal<uint32_t>());
	}
	IRegModelMgr::singleton()->addModel(this) ;
}

//-------------------------------------------------------------------------------------------------------------
PagedRegModel::~PagedRegModel()
{
	IRegModelMgr::singleton()->delModel(this) ;
}

//-------------------------------------------------------------------------------------------------------------
bool PagedRegModel::isPaged() const
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void PagedRegModel::setReadPage(unsigned page)
{
	if (page < mNumPages)
		mReadPage = page;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t PagedRegModel::regValue(uint32_t regNumber) const
{
	if (regNumber >= numRegs())
		return 0 ;

	return mRegs.at(mReadPage).at(regNumber).get() ;
}

//-------------------------------------------------------------------------------------------------------------
bool PagedRegModel::regIsSet(uint32_t regNumber) const
{
	if (regNumber >= numRegs())
		return false ;

	return mRegs.at(mReadPage).at(regNumber).isSet() ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<SetVal<uint32_t> > PagedRegModel::regs() const
{
	return mRegs.at(mReadPage) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint32_t> PagedRegModel::regValues() const
{
	std::vector<uint32_t> values(numRegs(), 0) ;
	for (unsigned i=0; i < numRegs(); ++i)
	{
		if (!mRegs.at(mReadPage).at(i).isSet())
			continue ;
		values[i] = mRegs.at(mReadPage).at(i).get() ;
	}
	return values ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint32_t> PagedRegModel::deviceValues() const
{
	// see if data needs to be shifted
	unsigned dataShift(0) ;
	if ( dataWidth() > addressLSB() )
	{
		dataShift = addressWidth() + addressLSB() ;
	}

	// Create the set of register values as if read from device (i.e. with address and data inserted into the appropriate bits)
	std::vector<uint32_t> values(numRegs(), 0) ;
	for (unsigned i=0; i < numRegs(); ++i)
	{
		if (!mRegs.at(mReadPage).at(i).isSet())
			continue ;

		uint32_t data(mRegs.at(mReadPage).at(i).get()) ;
		if (dataShift > 0)
			data <<= dataShift ;

		values[i] = data;

		//Check if address LSB is within the range of the register size
		if (addressLSB() < (sizeof(uint32_t) << 3))
			values[i] |= (i << addressLSB()) ;
	}
	return values ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void PagedRegModel::updateModel(uint32_t offset, uint32_t data)
{
	if (offset >= numRegs())
		return ;

	//Check if page number is being updated
	if (offset == mPagedRegOffset)
		mWritePage = data;

	//Add the data to the map
	mRegs[mWritePage][offset] = data & dataMask() ;
}
