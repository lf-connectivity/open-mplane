/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantUint.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DvTypeFactory.h"
#include "DataVariantUint.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantUint::DataVariantUint(std::shared_ptr<IDvType>& dv) :
	DataVariantTypeBase(dv)
{
}

//-------------------------------------------------------------------------------------------------------------
DataVariantUint::~DataVariantUint()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DataVariantUint::setUint(unsigned value)
{
	/* If currently no type, then create an instance of Uint */
	updateType(DataVariantType::Uint) ;

	/* Need to convert from specific type to intermediate value. use intermediate value to set */
	return mDvRef->fromInterInt(static_cast<IDvAccess::InterInt>(value)) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned DataVariantUint::toUint() const
{
	/* return the unsigned */
	return static_cast<unsigned>(mDvRef->toInterInt()) ;
}
