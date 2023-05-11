/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeNone.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DvTypeNone.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeNone::DvTypeNone(const std::string& typeStr) :
	DvTypeBase(typeStr)
{
}

//-------------------------------------------------------------------------------------------------------------
DvTypeNone::~DvTypeNone()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeNone::canSetValue(const std::string& value) const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeNone::canSetType(const std::string& type) const
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeNone::getTypeStr() const
{
	return "NONE" ;
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type DvTypeNone::getType() const
{
	return DataVariantType::None ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeNone::set(const std::string& value)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt DvTypeNone::toInterInt() const
{
	return IDvAccess::InterInt() ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat DvTypeNone::toInterFloat() const
{
	return IDvAccess::InterFloat() ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeNone::fromInterInt(const IDvAccess::InterInt& value)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeNone::fromInterFloat(const IDvAccess::InterFloat& value)
{
	return false ;
}
