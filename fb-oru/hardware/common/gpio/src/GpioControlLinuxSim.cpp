/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GpioControlLinuxSim.cpp
 * \brief     GPIO control for host simulation
 *
 *
 * \details   Implements the GPIO control.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "GpioControlLinux.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Path.h"
#include "stringfunc.hpp"

using namespace Mplane;
using namespace std;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
GpioControlLinux::GpioControlLinux(const std::string& classPath, const std::string& devPath,
		const std::string& label, unsigned base, unsigned ngpio) :
	mDevicePath(devPath),
	mGpioPath(classPath),
	mError(""),
	mLabel(label),
	mMutex(),
	mExportedPins(),
	mBaseIndex(base),
	mNumGpios(ngpio),
	mDebug(true)
{
	for (unsigned index = 0; index < ngpio; index++)
	{
		mPinValue[index] = 1;
		mPinDir[index] = GpioDirection::DIR_IN;
	}
}

//-------------------------------------------------------------------------------------------------------------
GpioControlLinux::~GpioControlLinux()
{
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::setDirection(unsigned index, GpioDirection dir)
{
	// Check if index is valid
	if (!isPinIndexValid(index))
	{
		return false;
	}

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Set direction
	mPinDir[index] = dir;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::getDirection(unsigned index, GpioDirection& dir)
{
	// Check if index is valid
	if (!isPinIndexValid(index))
	{
		return false;
	}

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// get direction
	dir = mPinDir[index];

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::setValue(unsigned index, int value)
{
	// Check if index is valid
	if (!isPinIndexValid(index))
	{
		return false;
	}

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Set value
	mPinValue[index] = value;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::getValue(unsigned index, int& value)
{
	// Check if index is valid
	if (!isPinIndexValid(index))
	{
		return false;
	}

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// get value
	value = mPinValue[index];

	return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string GpioControlLinux::error()
{
	std::string err ;
	using std::swap ;
	swap(err, mError) ;
	return err ;
}

//-------------------------------------------------------------------------------------------------------------
void GpioControlLinux::setDebug(bool debug)
{
	mDebug = debug ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::setError(const std::string &error)
{
	if (!mError.empty())
	{
		mError += "\n" ;
	}
	mError += error ;

	if (mDebug)
	{
		std::cerr << "GpioChip[" << mLabel << ":" << mDevicePath << "] Error: " << error << std::endl ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::debug() const
{
	return mDebug ;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::isPinIndexValid(unsigned index)
{
	// Check if index is valid
	if (index >= mNumGpios)
	{
		return setError("Pin index is out of range - " + std::to_string(index) + ", Valid range : 0 to " + std::to_string(mNumGpios));
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doExport(unsigned pinIndex)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doUnexport(unsigned pinIndex)
{
	return true;
}


//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doSetDirection(unsigned pinIndex, GpioDirection dir)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doGetDirection(unsigned pinIndex, GpioDirection& dir)
{
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doSetValue(unsigned pinIndex, int value)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doGetValue(unsigned pinIndex, int& value)
{
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::isExported(unsigned pinIndex)
{
	return false;
}
