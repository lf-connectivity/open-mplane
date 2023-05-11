/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GpioControlLinux.cpp
 * \brief     GPIO control using Linux devices
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

	// Offset the index by the base value for this device
	unsigned pinIndex = index + mBaseIndex;

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Export pin
	if (!doExport(pinIndex))
	{
		return false;
	}

	// Set direction
	if (!doSetDirection(pinIndex, dir))
	{
		return false;
	}

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

	// Offset the index by the base value for this device
	unsigned pinIndex = index + mBaseIndex;

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Export pin
	if (!doExport(pinIndex))
	{
		return false;
	}

	// get direction
	if (!doGetDirection(pinIndex, dir))
	{
		return false;
	}

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

	// Offset the index by the base value for this device
	unsigned pinIndex = index + mBaseIndex;

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Export pin
	if (!doExport(pinIndex))
	{
		return false;
	}

	// Set value
	if (!doSetValue(pinIndex, value))
	{
		return false;
	}

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

	// Offset the index by the base value for this device
	unsigned pinIndex = index + mBaseIndex;

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Export pin
	if (!doExport(pinIndex))
	{
		return false;
	}

	// get value
	if (!doGetValue(pinIndex, value))
	{
		return false;
	}

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
	// If pin is already exported, then return
    if (isExported(pinIndex) == 0)
    {
        // Open the export file in the gpio path
        std::string path = mGpioPath + "/export";

        std::ofstream file(path);
        if (!file.is_open())
        {
        	return setError("Error exporting pin " + std::to_string(pinIndex));
        }

        // Write the exported pin name in this file and close it
        file << pinIndex;

        file.close();

		mExportedPins[pinIndex] = true;
    }
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doUnexport(unsigned pinIndex)
{
    // Open the unexport file in the gpio path
    std::string path = mGpioPath + "/unexport";

    std::ofstream file(path);
    if (!file.is_open())
    {
    	return setError("Error unexporting pin " + std::to_string(pinIndex));
    }

    // Write the pin name to be unexported in this file and close it
    file << pinIndex;

    file.close();

	mExportedPins[pinIndex] = false;

	return true;
}


//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doSetDirection(unsigned pinIndex, GpioDirection dir)
{
    // Open the direction file in the gpio path
    std::string path = mGpioPath + "/gpio" + std::to_string(pinIndex) + "/direction";

    std::ofstream file(path);
    if (!file.is_open())
    {
    	return setError("Error setting direction for pin " + std::to_string(pinIndex));
    }

    // Write the pin direction in this file and close it
    file << ((dir == GpioDirection::DIR_IN) ? "in" : "out");

    file.close();

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doGetDirection(unsigned pinIndex, GpioDirection& dir)
{
    // Read the direction file in the gpio path
    std::string path = mGpioPath + "/gpio" + std::to_string(pinIndex) + "/direction";

    std::string pinDir("");

	std::ifstream file(path) ;
	if (file.is_open())
	{
		getline(file, pinDir) ;
	}
	file.close() ;

    if (pinDir.empty())
    {
    	return setError("Error reading direction for pin " + std::to_string(pinIndex));
    }
    else if (pinDir == "out")
    {
    	dir = GpioDirection::DIR_OUT;
    }
    else
    {
    	dir = GpioDirection::DIR_IN;
    }

    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doSetValue(unsigned pinIndex, int value)
{
    // Open the value file in the gpio path
    std::string path = mGpioPath + "/gpio" + std::to_string(pinIndex) + "/value";

    std::ofstream file(path);
    if (!file.is_open())
    {
    	return setError("Error writing value for pin " + std::to_string(pinIndex));
    }

    // Write the pin value in this file and close it
    file << value;

    file.close();

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::doGetValue(unsigned pinIndex, int& value)
{
    // Read the value file in the gpio path
    std::string path = mGpioPath + "/gpio" + std::to_string(pinIndex) + "/value";

    std::string pinVal("");

	std::ifstream file(path) ;
	if (file.is_open())
	{
		getline(file, pinVal) ;
	}
	file.close() ;

    if (pinVal.empty())
    {
    	return setError("Error reading value for pin " + std::to_string(pinIndex));
    }

    value = stoi(pinVal);

    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GpioControlLinux::isExported(unsigned pinIndex)
{
	// Check if pinIndex exists in the map
	if (mExportedPins.find(pinIndex) != mExportedPins.end())
	{
		return mExportedPins[pinIndex];
	}
	else
	{
		return false;
	}
}
