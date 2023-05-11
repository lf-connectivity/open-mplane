/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantDouble.cpp
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
#include "DataVariantDouble.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataVariantDouble::DataVariantDouble(std::shared_ptr<IDvType>& dv) :
	DataVariantTypeBase(dv)
{
}

//-------------------------------------------------------------------------------------------------------------
DataVariantDouble::~DataVariantDouble()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DataVariantDouble::setDouble(double value)
{
	/* If currently no type, then create an instance of Double */
	updateType(DataVariantType::Double) ;

	/* Need to convert from specific type to intermediate value. use intermediate value to set */
	return mDvRef->fromInterFloat(static_cast<IDvAccess::InterFloat>(value)) ;
}

//-------------------------------------------------------------------------------------------------------------
double DataVariantDouble::toDouble() const
{
	/* return the double */
	return static_cast<double>(mDvRef->toInterFloat()) ;
}
