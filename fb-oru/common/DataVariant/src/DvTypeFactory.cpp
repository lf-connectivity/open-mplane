/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeFactory.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>
#include "Mutex.h"
#include "DvTypeNone.h"
#include "DvTypeInt.h"
#include "DvTypeFloat.h"
#include "DvTypeComplex.h"
#include "DvTypeString.h"
#include "DvTypeEnum.h"
#include "DvTypeBool.h"
#include "DvTypeEnum.h"
#include "DvTypeFreq.h"
#include "DvTypePower.h"
#include "DvTypeDouble.h"
#include "DvTypeLong.h"
#include "DvTypeUint.h"

#include "DvTypeFactory.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANT
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Order of types is used when trying to determine the type from a string. Each type is passed the string to see
// if that string is valid for the type. The first type that can accept the string is used.
const std::vector<DataVariantType::Type> TYPE_ORDER{
	DataVariantType::Int,
	DataVariantType::Uint,
	DataVariantType::Float,
	DataVariantType::Complex,

	DataVariantType::Enum,
	DataVariantType::Bool,
	DataVariantType::String,

	// can't determine these types from the string
	DataVariantType::Freq,
	DataVariantType::Power,
	DataVariantType::Long,
	DataVariantType::Double,

	// Final fallback
	DataVariantType::None,
} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IDvType> > DvTypeFactory::getTypes()
{
	static std::vector<std::shared_ptr<IDvType> > list ;

	// First time round create list
	if (list.empty())
	{
		for (auto type : TYPE_ORDER)
		{
			list.push_back(factory(type)) ;
		}
	}

	return list ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDvType> DvTypeFactory::factory(DataVariantType::Type type, const std::string& typeStr)
{
// Only need one instance of "NONE"
static std::shared_ptr<IDvType> nullType(std::make_shared<DvTypeNone>()) ;

	switch (type)
	{
	case DataVariantType::Int:
		return std::make_shared<DvTypeInt>(typeStr) ;

	case DataVariantType::Float:
		return std::make_shared<DvTypeFloat>(typeStr) ;

	case DataVariantType::Complex:
		return std::make_shared<DvTypeComplex>(typeStr) ;

	case DataVariantType::Uint:
		return std::make_shared<DvTypeUint>(typeStr) ;

	case DataVariantType::Long:
		return std::make_shared<DvTypeLong>(typeStr) ;

	case DataVariantType::Double:
		return std::make_shared<DvTypeDouble>(typeStr) ;

	case DataVariantType::Enum:
		return std::make_shared<DvTypeEnum>(typeStr) ;

	case DataVariantType::Bool:
		return std::make_shared<DvTypeBool>(typeStr) ;

	case DataVariantType::String:
		return std::make_shared<DvTypeString>(typeStr) ;

	case DataVariantType::Freq:
		return std::make_shared<DvTypeFreq>(typeStr) ;

	case DataVariantType::Power:
		return std::make_shared<DvTypePower>(typeStr) ;

	case DataVariantType::None:
	default:
		return nullType ;
	}

	// should never get here!
	return std::shared_ptr<IDvType>() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDvType> DvTypeFactory::factory(const std::string& typeStr)
{
	// Uses the singleton list of all known types to call "static" methods to see if we can create a type using this type string
	std::vector<std::shared_ptr<IDvType> > types(getTypes()) ;
	for (auto dv : types)
	{
		if (!dv->canSetType(typeStr))
			continue ;

		// create a new instance of this type
		return factory(dv->getType(), typeStr) ;
	}

	// If all else fails just return a "NONE"
	return factory(DataVariantType::None) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDvType> DvTypeFactory::copy(std::shared_ptr<IDvType> rhs)
{
	// create a copy of the type
	std::shared_ptr<IDvType> dv(factory(rhs->getType(), rhs->getTypeStr())) ;

	// set the value
	dv->setUnits(rhs->getUnits()) ;
	dv->set(rhs->toString()) ;

	return dv ;
}
