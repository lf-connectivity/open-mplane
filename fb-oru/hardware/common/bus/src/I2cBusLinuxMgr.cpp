/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusLinuxMgr.cpp
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
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "Path.h"
#include "stringfunc.hpp"

#include "BusSettings.hpp"
#include "BusLock.hpp"
#include "I2cBusLinux.h"

#include "I2cBusLinuxMgr.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<II2cBusMgr> II2cBusMgr::singleton()
{
static std::shared_ptr<II2cBusMgr> instance( std::make_shared<I2cBusLinuxMgr>() ) ;
	return instance ;
}


//=============================================================================================================
// LOCAL
//=============================================================================================================

#ifdef OFF_TARGET
const std::map<std::string, std::string> SIM_MAP{
	{ "/0", 			"/dev/i2c-0" },
	{ "/1", 			"/dev/i2c-1" },
	{ "/2", 			"/dev/i2c-2" },
	{ "/0/mux:0:0", 	"/dev/i2c-3" },
	{ "/0/mux:0:1", 	"/dev/i2c-4" },
	{ "/0/mux:0:2", 	"/dev/i2c-5" },
	{ "/0/mux:0:3", 	"/dev/i2c-6" },
	{ "/1/mux:0:0", 	"/dev/i2c-7" },
	{ "/1/mux:0:1", 	"/dev/i2c-8" },
	{ "/1/mux:0:2", 	"/dev/i2c-9" },
	{ "/1/mux:0:3", 	"/dev/i2c-10" },
	{ "/1/mux:0:4", 	"/dev/i2c-11" },
	{ "/1/mux:0:5", 	"/dev/i2c-12" },
	{ "/1/mux:0:6", 	"/dev/i2c-13" },
	{ "/1/mux:0:7", 	"/dev/i2c-14" },
	{ "/1/mux:1:0", 	"/dev/i2c-15" },
	{ "/1/mux:1:1", 	"/dev/i2c-16" },
	{ "/1/mux:1:2", 	"/dev/i2c-17" },
	{ "/1/mux:1:3", 	"/dev/i2c-18" },
	{ "/1/mux:1:4", 	"/dev/i2c-19" },
	{ "/1/mux:1:5", 	"/dev/i2c-20" },
	{ "/1/mux:1:6", 	"/dev/i2c-21" },
	{ "/1/mux:1:7", 	"/dev/i2c-22" },
};

#else
//-------------------------------------------------------------------------------------------------------------
namespace {

	struct I2cInfo {
		I2cInfo() :
		number(0), devPath(), name(), unifiedName(), subNodes(), parent(-1), bus(-1), muxNumber(-1)
		{}

		I2cInfo(unsigned num, const std::string& path) :
		number(num), devPath(path), name(), unifiedName(), subNodes(), parent(-1), bus(-1), muxNumber(-1)
		{}

		unsigned number ;
		std::string devPath ;
		std::string name ;
		std::string unifiedName ;
		std::vector<unsigned> subNodes ;
		int parent ;
		int bus ;
		int muxNumber ;
	};

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
	std::vector<std::string> getBusNumbers(const std::vector<std::string>& contents)
	{
		std::vector<std::string> busNums(contents.size(), "") ;
		for (auto& d : contents)
		{
			// d will be of the form: /sys/class/i2c-dev/i2c-15
			std::size_t pos(d.find_last_of('-')) ;
			if (pos == std::string::npos)
				continue ;

			unsigned busNum( stoul(d.substr(pos+1)) ) ;

			while (busNum >= busNums.size())
				busNums.push_back("") ;

			busNums[busNum] = d.substr(pos-3) ;
		}

		return busNums ;
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

	//---------------------------------------------------------------------------------------------------------
	std::vector<I2cInfo> getBusInfo(const std::string& classI2c, const std::vector<std::string>& busNums)
	{
		std::vector<I2cInfo> busInfo ;
		for (unsigned i=0; i < busNums.size(); ++i)
		{
			busInfo.push_back(I2cInfo(i, "/dev/" + busNums[i])) ;
		}
		for (unsigned i=0; i < busNums.size(); ++i)
		{
			if (busNums.empty())
				continue ;

			// Look in device directory for this bus: /sys/class/i2c-dev/i2c-XX/device/
			//
			// In a leaf node the contents will be like:
			//		# ls /sys/class/i2c-dev/i2c-12/device
			//		12-002f  delete_device	device	i2c-dev  mux_device  name  new_device  of_node	power  subsystem  uevent
			//
			// In a bus node the contents will be like:
			//		# ls /sys/class/i2c-dev/i2c-0/device
			//		0-0020	0-0075	delete_device  device  i2c-3  i2c-4  i2c-5  i2c-6  i2c-dev  name  new_device  of_node  power  subsystem  uevent
			//
			busInfo[i].name = readFile(classI2c + "/" + busNums[i] + "/device/name") ;

			// Look for the directory: /sys/class/i2c-dev/i2c-XX/device/i2c-??
			// Start by getting the contents of directory /sys/class/i2c-dev/i2c-XX/device/
			std::string dir(classI2c + "/" + busNums[i] + "/device") ;
			std::vector<std::string> contents(Path::dirContents(dir)) ;
			for (auto d : contents)
			{
				// look for /sys/class/i2c-dev/i2c-XX/device/i2c-??
				std::vector<std::string> fields(splitStr(d, '/')) ;
				if (fields.empty())
					continue ;

				std::string dd(fields[fields.size()-1]) ;
				std::size_t pos(dd.find("i2c-")) ;
				if (pos == std::string::npos)
					continue ;

				// check this is of the form: i2c-12 rather than i2c-dev
				if (!isdigit(dd[pos+4]))
					continue ;

				unsigned num(stoul(dd.substr(pos+4))) ;

				// Now read the file 'name' under this directory
				busInfo[i].subNodes.push_back(num) ;

				// tell this subnode that we're it's parent
				busInfo[num].parent = i ;
			}

		}

		return busInfo ;
	}

	//---------------------------------------------------------------------------------------------------------
	void createUnified(const std::vector<unsigned>& nodes, std::vector<I2cInfo>& busInfo)
	{
		for (auto parent : nodes)
		{
			std::sort(busInfo[parent].subNodes.begin(), busInfo[parent].subNodes.end());
			for (auto node : busInfo[parent].subNodes)
			{
				std::string name(busInfo[node].name) ;

				// TODO: Handle non-bus and non-mux ?

				// look for: i2c-0-mux (chan_id 0)
				std::size_t pos(name.find("-mux (chan_id ")) ;
				std::size_t epos(name.find(')', pos)) ;
				if (pos == std::string::npos)
					continue ;
				if (epos == std::string::npos)
					continue ;

				pos += 14 ;
				unsigned chan(stoul(name.substr(pos, epos-pos))) ;
				if (chan == 0)
					busInfo[parent].muxNumber++ ;

				busInfo[node].unifiedName = busInfo[parent].unifiedName + "/mux:" +
						std::to_string(busInfo[parent].muxNumber) + ":" +
						std::to_string(chan) ;

				// do any subnodes of this node
				if (!busInfo[node].subNodes.empty())
					createUnified(busInfo[node].subNodes, busInfo) ;
			}
		}
	}

}
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
I2cBusLinuxMgr::I2cBusLinuxMgr() :
	I2cBusMgr(),
	mNameMap()
{
	gatherI2cBusses() ;
}

//-------------------------------------------------------------------------------------------------------------
I2cBusLinuxMgr::~I2cBusLinuxMgr()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<II2cBus> I2cBusLinuxMgr::createBus(const std::string &unifiedBusName, unsigned i2cAddress, unsigned bus,
		std::shared_ptr<IBusLock> busLock, std::shared_ptr<IBusSettings> busSettings)
{
	std::string devpath(devicePath(unifiedBusName)) ;

	if (devpath.empty())
		return std::shared_ptr<II2cBus>();

	return std::make_shared<I2cBusLinux>(devpath, i2cAddress, busLock, busSettings) ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#ifdef OFF_TARGET
void I2cBusLinuxMgr::gatherI2cBusses()
{
	mNameMap = SIM_MAP ;
	createBuses(2) ;
}
#else
void I2cBusLinuxMgr::gatherI2cBusses()
{
	std::string sysfs(findSysfs()) ;
	if (sysfs.empty())
	{
		return ;
	}

	std::string classI2c(sysfs + "/class/i2c-dev") ;
	if (!Path::exists(classI2c))
	{
		return ;
	}

	std::vector<std::string> contents(Path::dirContents(classI2c)) ;
	if (contents.empty())
		return ;

	// get the list of device numbers
	std::vector<std::string> busNums(getBusNumbers(contents)) ;

	// get the device names
	std::vector<I2cInfo> busInfo(getBusInfo(classI2c, busNums)) ;

	// Now that we have the info, see how many busses we have
	// These are the nodes with no parent
	unsigned bus(0) ;
	std::vector<unsigned> busses ;
	for (unsigned i=0; i < busNums.size(); ++i)
	{
		if (busInfo[i].parent != -1)
			continue ;

		busInfo[i].bus = bus++ ;
		busInfo[i].unifiedName = "/" + std::to_string(busInfo[i].bus) ;
		busses.push_back(i) ;
	}

	// Create the unified names
	createUnified(busses, busInfo) ;

	// Map the names
	for (auto info : busInfo)
	{
		mNameMap[info.unifiedName] = info.devPath ;
		std::cout << "Unified name : " << info.unifiedName << ", Device path : " << info.devPath << std::endl;
	}

	// Create a lock and setting object for each bus
	createBuses(busses.size()) ;

}
#endif

//-------------------------------------------------------------------------------------------------------------
std::string I2cBusLinuxMgr::devicePath(const std::string &unifiedBusName) const
{
	if (mNameMap.find(unifiedBusName) == mNameMap.end())
		return "" ;

	return mNameMap.at(unifiedBusName) ;
}
