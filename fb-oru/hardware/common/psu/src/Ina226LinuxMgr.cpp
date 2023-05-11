/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ina226LinuxMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Path.h"
#include "Ina226Linux.h"
#include "Ina226LinuxMgr.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#ifdef OFF_TARGET
// for debug, create a normal directory hierarchy containing files with the power/volt/current values
const std::string HWMON("/tmp/hwmon") ;
#else
const std::string HWMON("/sys/class/hwmon") ;
#endif

#ifdef OFF_TARGET
namespace {
	void writeFile(const std::string& path, const std::string& value)
	{
		std::ofstream file ;
		file.open(path, std::ios::trunc) ;
		if (!file)
			return ;
		file << value ;
		file.close() ;
	}
	void writeUnsigned(const std::string& path, unsigned value)
	{
		writeFile(path, std::to_string(value)) ;
	}
}
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Ina226LinuxMgr::Ina226LinuxMgr() :
	mMonitors(),
	mSysFs(HWMON)
{
	init() ;
}

//-------------------------------------------------------------------------------------------------------------
Ina226LinuxMgr::Ina226LinuxMgr(const std::map<std::string, std::string> &names) :
	mMonitors(),
	mSysFs(HWMON)
{
	init() ;
	setMapping(names) ;
}

//-------------------------------------------------------------------------------------------------------------
Ina226LinuxMgr::~Ina226LinuxMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
void Ina226LinuxMgr::setMapping(const std::map<std::string, std::string> &names)
{
	mMonitors.clear() ;

	// Need to rescan the sysfs looking for possible devices
	std::vector<std::string> contents(Path::dirContents(mSysFs)) ;
	for (auto d : contents)
	{
//		std::cerr << "DIR " << d << std::endl ;

		std::shared_ptr<Ina226Linux> driver(std::make_shared<Ina226Linux>(d)) ;
		if (!driver->isValid())
			continue ;

		// match the driver name
		auto entry(names.find(driver->name())) ;
		if (entry == names.end())
			continue ;

		mMonitors[entry->second] = driver ;
	}
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IPsuMonitorDriver> Ina226LinuxMgr::getMonitor(const std::string &name)
{
	auto entry(mMonitors.find(name)) ;

	if (entry == mMonitors.end())
		return std::shared_ptr<IPsuMonitorDriver>() ;

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
void Ina226LinuxMgr::setSysfs(const std::string &sysfs)
{
	mSysFs = sysfs ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Ina226LinuxMgr::init()
{
#ifdef OFF_TARGET
	// create a dummy directory hierarchy
	const float POWER_CONST(0.000001) ;
	const float VOLT_CONST(0.001) ;
	const float CURRENT_CONST(0.001) ;

    std::map<std::string, std::string> hwmon_names{
    	{ "ina226_u59", "0" },
    	{ "ina226_u61", "1" },
    	{ "ina226_u63", "2" },
    	{ "ina226_u66", "3" },
    	{ "ina226_u60", "4" },
    	{ "ina226_u3",  "5" },
    	{ "ina226_u64", "6" },
    	{ "ina226_u65", "7" },
    	{ "ina226_u67", "8" },
    	{ "ina226_u69", "9" },
    	{ "ina226_u71", "10" },
    	{ "ina226_u73", "11" },
    	{ "ina226_u77", "12" },
    	{ "ina226_u79", "13" },
    } ;

    std::map<std::string, std::string> names{
    	{ "ina226_u59", "VCCINT_IO_BRAM_PS_SDFEC" },
    	{ "ina226_u61", "VCC1V8" },
    	{ "ina226_u63", "VCCINT_RF" },
    	{ "ina226_u66", "MGT1V2" },
    	{ "ina226_u60", "VCC1V2" },
    	{ "ina226_u3",  "DAC_AVTT" },
    	{ "ina226_u64", "VADJ_FMC" },
    	{ "ina226_u65", "MGT1V8" },
    	{ "ina226_u67", "VCCINT" },
    	{ "ina226_u69", "MGTAVCC" },
    	{ "ina226_u71", "DAC_AVCCAUX" },
    	{ "ina226_u73", "ADC_AVCCAUX" },
    	{ "ina226_u77", "ADC_AVCC" },
    	{ "ina226_u79", "DAC_AVCC" },
    } ;

	std::map<std::string, std::vector<float>> values{
		{ "DAC_AVTT", { 1.252, 0.262, 0.212 } },
		{ "VCCINT_IO_BRAM_PS_SDFEC", { 0.85, 1.5, 1.755 } },
		{ "VCC1V2", { 1.198, 0.437, 0.368 } },
		{ "VCC1V8", { 1.805, 0.8, 0.441 } },
		{ "VCCINT_RF", { 0.848, 2.725, 3.199 } },
		{ "VADJ_FMC", { 0.098, 0, 0 } },
		{ "MGT1V8", { 1.795, 0.087, 0.05 } },
		{ "MGT1V2", { 1.202, 0.55, 0.453 } },
		{ "VCCINT", { 0.857, 12.906, 15.053 } },
		{ "MGTAVCC", { 0.903, 0.156, 0.155 } },
		{ "DAC_AVCCAUX", { 1.805, 0.312, 0.172 } },
		{ "ADC_AVCCAUX", { 1.815, 2.462, 1.356 } },
		{ "ADC_AVCC", { 0.927, 1.15, 1.23 } },
		{ "DAC_AVCC", { 0.928, 1.087, 1.168 } },
	} ;

	for (auto entry : hwmon_names)
	{
		std::string path(HWMON + "/hwmon" + entry.second) ;
		std::string name(names[entry.first]) ;
		std::cout << "INA226: " << name << " Creating dummy hwmon : " << path << std::endl ;
		Path::mkpath(path) ;

		writeFile(path + "/name", entry.first) ;

		auto inputs(values[name]) ;
		writeUnsigned(path + "/in2_input", inputs[0] / VOLT_CONST ) ;
		writeUnsigned(path + "/power1_input", inputs[1] / POWER_CONST ) ;
		writeUnsigned(path + "/curr1_input", inputs[2] / CURRENT_CONST ) ;
	}

#endif
}
