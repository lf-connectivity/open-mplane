/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantFloat.cpp
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
#include "DataVariantFloat.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantFloat::DataVariantFloat(std::shared_ptr<IDvType>& dv) :
	DataVariantTypeBase(dv)
{
}

//-------------------------------------------------------------------------------------------------------------
DataVariantFloat::~DataVariantFloat()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DataVariantFloat::setFloat(float value)
{
	/* If currently no type, then create an instance of Float */
	updateType(DataVariantType::Float) ;

	/* Need to convert from specific type to intermediate value. use intermediate value to set */
	return mDvRef->fromInterFloat(static_cast<IDvAccess::InterFloat>(value)) ;
}

//-------------------------------------------------------------------------------------------------------------
float DataVariantFloat::toFloat() const
{
	/* return the float */
	return static_cast<float>(mDvRef->toInterFloat()) ;
}
