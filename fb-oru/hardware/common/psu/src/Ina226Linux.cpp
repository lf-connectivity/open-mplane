/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ina226Linux.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>

#include "stringfunc.hpp"
#include "Path.h"
#include "Ina226Linux.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const float POWER_CONST(0.000001) ;
const float VOLT_CONST(0.001) ;
const float CURRENT_CONST(0.001) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Ina226Linux::Ina226Linux(const std::string &sysfsPath) :
	mSysfsPath(sysfsPath),
	mName(""),
	mValid(true)	// valid until it isn't - allows sub-methods to work
{
	mValid = readSysfs() ;
	if (!mValid)
		return ;

	if (!startsWith(mName, "ina226_"))
		mValid = false ;
}

//-------------------------------------------------------------------------------------------------------------
Ina226Linux::~Ina226Linux()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Ina226Linux::isValid() const
{
	return mValid ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Ina226Linux::initialise(void)
{
	return ReturnType::RT_OK ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Ina226Linux::name() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
void Ina226Linux::show(void)
{
}

//-------------------------------------------------------------------------------------------------------------
float Ina226Linux::power()
{
	unsigned val(readSysfsUnsigned("power1_input")) ;
	return (float)val * POWER_CONST ;
}

//-------------------------------------------------------------------------------------------------------------
float Ina226Linux::voltage()
{
	unsigned val(readSysfsUnsigned("in2_input")) ;
	return (float)val * VOLT_CONST ;
}

//-------------------------------------------------------------------------------------------------------------
float Ina226Linux::current()
{
	unsigned val(readSysfsUnsigned("curr1_input")) ;
	return (float)val * CURRENT_CONST ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ina226Linux::isPowerSupported() const
{
	// supports operation unless it's an invalid object
	return mValid ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ina226Linux::isVoltageSupported() const
{
	// supports operation unless it's an invalid object
	return mValid ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ina226Linux::isCurrentSupported() const
{
	// supports operation unless it's an invalid object
	return mValid ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Ina226Linux::readSysfs()
{
	if (!Path::exists(mSysfsPath))
		return false ;

	mName = readSysfsFile("name") ;
	return !mName.empty() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Ina226Linux::readSysfsFile(const std::string &name)
{
	if (!mValid)
		return "" ;

	std::string path(mSysfsPath + "/" + name) ;

	std::ifstream file(path) ;
	if (!file.is_open())
		return "" ;

	std::string line ;
	getline(file, line) ;
	file.close() ;

	return line ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Ina226Linux::readSysfsUnsigned(const std::string &name)
{
	if (!mValid)
		return 0 ;

	std::string str(readSysfsFile(name)) ;
	if (str.empty())
		return 0 ;

	return (unsigned)stoul(str) ;
}
