/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdData.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdData.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdData::DpdData()
{
}

//-------------------------------------------------------------------------------------------------------------
DpdData::~DpdData()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DpdData::predicate(const std::map<std::string, DataVariant>& attributes)
{
	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool DpdData::checkVariables(const std::vector<std::string>& variableNames,
		const std::map<std::string, DataVariant>& attributes) const
{
	for (auto name : variableNames)
	{
		if (!variablePresent(name, attributes))
			return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdData::variablePresent(const std::string& variableName,
		const std::map<std::string, DataVariant>& attributes) const
{
	auto entry(attributes.find(variableName)) ;
	return entry != attributes.end() ;
}
