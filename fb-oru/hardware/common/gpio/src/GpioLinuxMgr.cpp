/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GpioLinuxMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Path.h"
#include "stringfunc.hpp"

#include "GpioLinuxMgr.h"
#include "GpioControlLinux.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGpioLinuxMgr> IGpioLinuxMgr::singleton()
{
    static std::shared_ptr<IGpioLinuxMgr> instance( std::make_shared<GpioLinuxMgr>() ) ;
	return instance ;
}

#ifndef OFF_TARGET
namespace{

	//---------------------------------------------------------------------------------------------------------
	std::string findSysfs()
	{
		std::ifstream file("/proc/mounts") ;
		if (!file.is_open())
			return "" ;

		std::string sysfs("") ;
		std::string line ;
		while (getline(file, line))
		{
			std::vector<std::string> fields(splitStr(line)) ;
			if (fields.size() <= 2)
				continue ;

			if (fields[0] != "sysfs")
				continue ;

			sysfs = fields[1] ;
			break ;
		}
		file.close() ;

		return sysfs ;
	}

	//---------------------------------------------------------------------------------------------------------
	std::string readFile(const std::string& path)
	{
		std::ifstream file(path) ;
		if (!file.is_open())
			return "" ;

		std::string sysfs("") ;
		std::string line ;
		getline(file, line) ;
		file.close() ;

		return line ;
	}
}
#endif


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
GpioLinuxMgr::GpioLinuxMgr() :
	mGpiochipInfo(),
	mGpioDevices(),
	mNames()
{
#ifdef OFF_TARGET
	mGpiochipInfo.push_back(GpioChipInfo("/dev/gpiochip1", "tca6416", 322, 16));
#else
	// Find sysfs path
	std::string sysfs(findSysfs()) ;
	if (sysfs.empty())
	{
		std::cerr << "Cannot find sysfs" << std::endl;
		return ;
	}

	// Check if gpio class directory exists
	std::string classGpio(sysfs + "/class/gpio") ;
	if (!Path::exists(classGpio))
	{
		std::cerr << "Gpio path does not exist - " << classGpio << std::endl;
		return ;
	}

	mGpioSysPath = classGpio;

	// Read contents of sysfs + /class/gpio directory
	std::vector<std::string> gpioContents(Path::dirContents(classGpio)) ;
	if (gpioContents.empty())
	{
		std::cerr << "Directory empty " << classGpio << std::endl;
		return ;
	}

	// Look for the device index directory to get the base index and the number of gpios for this device
	for (auto& d : gpioContents)
	{
		// Look for directory with name gpiochipXXX
		std::string gpioChipDir("gpiochip");

		std::size_t pos = d.find(gpioChipDir) ;

		// If this is not a gpiochipXXX dir, then skip it
		if (pos == std::string::npos)
		{
			continue ;
		}

		std::string basePath(d + "/base");
		std::string nGpioPath(d + "/ngpio");
		std::string labelPath(d + "/label");

		if (!Path::exists(basePath) ||
			!Path::exists(nGpioPath) ||
			!Path::exists(labelPath))
		{
			continue ;
		}

		// Note down the base index if this is our device
		unsigned baseIndex( stoul(readFile(basePath)) ) ;

		// Note the number of gpios if this is our device
		unsigned numGpios( stoul(readFile(nGpioPath)));

		// Note the label if this is our device
		std::string label = readFile(labelPath);

		// If it's available then read the device/name and use that as the label
		// This is because in Petalinux 2020.1 build the label because meaningless and we need to rely on the name
		// This is backwards compatible with Petalinux 2018.3
		std::string namePath(d + "/device/name");
		if (Path::exists(namePath))
		{
			std::string name(readFile(namePath)) ;
			if (!name.empty())
				label = name ;
		}


		// Navigate to device folder inside the gpiochip dir
		std::string dir(d + "/device") ;
		std::vector<std::string> deviceContents(Path::dirContents(dir)) ;

		// Look for gpiochipN folder
		for (auto& deviceDir : deviceContents)
		{
			std::string gpiochipDevice("/device/gpiochip");

			pos = deviceDir.find(gpiochipDevice) ;

			if (pos == std::string::npos)
			{
				continue ;
			}

			// Get the gpiochip index
			unsigned gpioChipIndex( stoul(deviceDir.substr(pos + gpiochipDevice.size())) ) ;
			std::string devPath = "/dev/gpiochip" + std::to_string(gpioChipIndex);
			mGpiochipInfo.push_back(GpioChipInfo(devPath, label, baseIndex, numGpios));
			break;
		}
	}
#endif
}

//-------------------------------------------------------------------------------------------------------------
GpioLinuxMgr::~GpioLinuxMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
void GpioLinuxMgr::registerNames(const std::map<std::string, std::string> &namesMap)
{
	mNames.insert(namesMap.begin(), namesMap.end()) ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> GpioLinuxMgr::getRegisteredNames() const
{
	return mNames ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGpioControl> GpioLinuxMgr::getDeviceFromName(const std::string &name)
{
	if (mNames.find(name) == mNames.end())
		return std::shared_ptr<IGpioControl>() ;

	return getDeviceFromLabel(mNames[name]) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGpioControl> GpioLinuxMgr::getDeviceFromLabel(const std::string &label)
{
	// start by seeing if this device is cached
	if (mGpioDevices.find(label) != mGpioDevices.end())
		return mGpioDevices[label] ;

	// try using all lowercase name
	std::string lower(toLower(label)) ;
	if (mGpioDevices.find(lower) != mGpioDevices.end())
		return mGpioDevices[lower] ;

	// need to create device (if possible)

	for (auto &info : mGpiochipInfo)
	{
		if (info.devLabel == label)
		{
			std::shared_ptr<IGpioControl> gpioControl(std::make_shared<GpioControlLinux>(
					mGpioSysPath, info.devPath, info.devLabel, info.baseIndex, info.numGpios));
			mGpioDevices[lower] = gpioControl;

			return gpioControl;
		}
	}

	return std::shared_ptr<IGpioControl>() ;
}
