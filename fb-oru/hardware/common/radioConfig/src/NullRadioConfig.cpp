/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NullRadioConfig.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "NullRadioConfig.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NullRadioConfig::NullRadioConfig()
{
}

//-------------------------------------------------------------------------------------------------------------
NullRadioConfig::NullRadioConfig(const std::string &path,
		const std::map<std::string, std::string> defaults)
{
}

//-------------------------------------------------------------------------------------------------------------
NullRadioConfig::~NullRadioConfig()
{
}

//-------------------------------------------------------------------------------------------------------------
void NullRadioConfig::setLimits(const std::map<std::string, std::shared_ptr<DataVariant> > &limits)
{
}

//-------------------------------------------------------------------------------------------------------------
bool NullRadioConfig::isValid() const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NullRadioConfig::value(const std::string &varname) const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullRadioConfig::isVariable(const std::string &varname) const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
double NullRadioConfig::doubleValue(const std::string &varname) const
{
	return 0.0 ;
}

//-------------------------------------------------------------------------------------------------------------
int NullRadioConfig::intValue(const std::string &varname) const
{
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::pair<std::string, std::string> > NullRadioConfig::values() const
{
	return std::vector<std::pair<std::string, std::string> >() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullRadioConfig::setValue(const std::string &varname, const std::string &value)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullRadioConfig::save()
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullRadioConfig::isDoubleValue(const std::string &varname) const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool NullRadioConfig::isIntValue(const std::string &varname) const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NullRadioConfig::error()
{
	return "" ;
}
