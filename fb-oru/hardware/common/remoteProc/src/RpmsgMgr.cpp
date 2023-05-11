/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RpmsgMgr.cpp
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
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#ifndef OFF_TARGET
#include <linux/rpmsg.h>
#endif

#include <algorithm>
#include <iterator>

#include "Path.h"
#include "Task.h"
#include "stringfunc.hpp"
#include "RemoteProc.h"
#include "RpmsgMgr.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string RPMSG_DEV("/dev/rpmsg") ;
const std::string RPMSG_DRIVER("rpmsg_char") ;
const std::string RPMSG_SYS_BUS("/sys/bus/rpmsg") ;
const std::string RPMSG_SYS_BUS_DEVICES(RPMSG_SYS_BUS + "/devices") ;
const std::string RPMSG_SYS_BUS_CHRDEV(RPMSG_SYS_BUS + "/drivers/rpmsg_chrdev") ;
const std::string RPMSG_CTRL_PREFIX("rpmsg_ctrl") ;
const std::string RPMSG_SYS_CLASS("/sys/class/rpmsg") ;


#define DEBUG_RMSG
#ifdef DEBUG_RMSG
#define RMSG_COUT	std::cerr
#else
#define RMSG_COUT	if (false) std::cerr
#endif


namespace {

	void showContents(const std::string& title, const std::vector<std::string>& contents)
	{
		std::cerr << "DIR CONTENTS: " << title << std::endl ;
		for (auto& file : contents)
			std::cerr << " * " << file << std::endl ;
	}

}

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<RpmsgMgr> RpmsgMgr::singleton()
{
	static std::shared_ptr<RpmsgMgr> instance(std::make_shared<RpmsgMgr>()) ;
	return instance ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RpmsgMgr::RpmsgMgr() :
	mDeviceMap(),
	mDevices()
{
	RMSG_COUT << std::endl << "NEW RpmsgMgr @ " << this << std::endl ;

	// ensure driver isn't running
	stopDriver() ;
}

//-------------------------------------------------------------------------------------------------------------
RpmsgMgr::~RpmsgMgr()
{
	RMSG_COUT << "DEL RpmsgMgr @ " << this << std::endl ;

	// ensure driver isn't running
	stopDriver() ;
}

//-------------------------------------------------------------------------------------------------------------
bool RpmsgMgr::addingDevice(unsigned index)
{
	RMSG_COUT << std::endl << "RpmsgMgr::addingDevice " << index << std::endl ;
	mDevices[index] = Path::dirContents(RPMSG_SYS_BUS_DEVICES) ;

	showContents("before add", mDevices[index]) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RpmsgMgr::addDevice(unsigned index)
{
	RMSG_COUT << std::endl << "RpmsgMgr::addDevice " << index << std::endl ;

	if (mDeviceMap.find(index) != mDeviceMap.end())
		return false ;

	// wait for device to appear
	std::string serviceName ;
	std::string device ;
	for(unsigned tryCount=1; tryCount <= 10; ++tryCount)
	{
		Task::msSleep(100) ;

		// e.g. /sys/bus/rpmsg/devices/virtio0.rpmsg-openamp-demo-channel.-1.0
		std::vector<std::string> newDirContents(Path::dirContents(RPMSG_SYS_BUS_DEVICES)) ;
		std::vector<std::string> diff ;
		std::set_difference(newDirContents.begin(), newDirContents.end(), mDevices[index].begin(), mDevices[index].end(),
				std::inserter(diff, diff.begin())) ;

		showContents("after add", newDirContents) ;
		showContents("diff", diff) ;

		if (diff.empty())
			continue ;

		// assume we want the first in the list if there are more than 1 dir in diffs
		device = Path::basename(diff[0]) ;

		// get the names of the service for this device
		RemoteProc::readSysFile(RPMSG_SYS_BUS_DEVICES + "/" + device + "/name", serviceName) ;

		RMSG_COUT << std::endl << "RpmsgMgr::addDevice service name=" << serviceName << std::endl ;
		break ;
	}

	// if device still not present then stop
	if (device.empty())
	{
		std::cerr << "RpmsgMgr::addDevice no diff in sys devices after starting firmware" << std::endl ;
		return false ;
	}

	RMSG_COUT << std::endl << "RpmsgMgr::addDevice " << index << " sys bus device " << device << std::endl ;

	// start device driver
	if (mDeviceMap.empty())
		startDriver() ;

	// Bind
	// e.g. echo rpmsg_chrdev > /sys/bus/rpmsg/devices/virtio0.rpmsg-openamp-demo-channel.-1.0/driver_override
	RMSG_COUT << std::endl << "RpmsgMgr::addDevice - write driver_override..." << std::endl ;
	if (!RemoteProc::writeSysFile(RPMSG_SYS_BUS_DEVICES + "/" + device + "/driver_override", "rpmsg_chrdev"))
	{
		std::cerr << "Unable to write driver override" << std::endl ;
		return false ;
	}

	// e.g. echo virtio0.rpmsg-openamp-demo-channel.-1.0 > /sys/bus/rpmsg/drivers/rpmsg_chrdev/bind
	// TODO: How does this work when running both R5-0 and R5-1 ?
	RMSG_COUT << std::endl << "RpmsgMgr::addDevice - write bind..." << std::endl ;
	if (!RemoteProc::writeSysFile(RPMSG_SYS_BUS_CHRDEV + "/bind", device))
	{
		std::cerr << "Unable to write driver bind" << std::endl ;
		return false ;
	}


	// Open the rpmsg control
	std::string rpmsgCtrlName ;
	RMSG_COUT << std::endl << "RpmsgMgr::addDevice - open rpmsg control..." << std::endl ;
	int ctrlFd(openRpmsgCtrl(device, rpmsgCtrlName)) ;
	if (ctrlFd < 0)
	{
		std::cerr << "Cannot open rpmsg control" << std::endl ;
		return false ;
	}

	// create endpoint
	RMSG_COUT << std::endl << "RpmsgMgr::addDevice - create endpoint..." << std::endl ;
	bool eptOk = createRpmsgEndpoint(ctrlFd, serviceName) ;
	close(ctrlFd) ;
	if (!eptOk)
	{
		std::cerr << "Cannot create endpoint" << std::endl ;
		return false ;
	}

	std::string devPath ;
	RMSG_COUT << std::endl << "RpmsgMgr::addDevice - get endpoint device name..." << std::endl ;
	if (!getEndpointDevPath(rpmsgCtrlName, serviceName, devPath))
	{
		std::cerr << "Cannot get endpoint device name" << std::endl ;
		return false ;
	}

	RMSG_COUT << std::endl << "RpmsgMgr::addDevice " << index << " => " << devPath << std::endl ;

	mDeviceMap[index] = devPath ;

	RMSG_COUT << std::endl << "RpmsgMgr::addDevice - DONE" << std::endl ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RpmsgMgr::delDevice(unsigned index)
{
	RMSG_COUT << std::endl << "RpmsgMgr::delDevice " << index << std::endl ;

	if (mDeviceMap.find(index) == mDeviceMap.end())
		return false ;

	mDeviceMap.erase(index) ;

	if (mDeviceMap.empty())
		stopDriver() ;

	RMSG_COUT << std::endl << "RpmsgMgr::delDevice - DONE" << std::endl ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RpmsgMgr::getDevice(unsigned index)
{
	if (mDeviceMap.find(index) == mDeviceMap.end())
		return "" ;

	return mDeviceMap[index] ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RpmsgMgr::startDriver()
{
//std::cerr << std::endl << "RpmsgMgr::startDriver " << std::endl ;

	std::string cmd("modprobe " + RPMSG_DRIVER) ;

	errno = 0 ;
	int rc = system(cmd.c_str()) ;

	RMSG_COUT << std::endl << "RpmsgMgr::startDriver - cmd: " << cmd << " rc=" << rc << " errno=" << errno << std::endl ;

	// wait to ensure device is probed
	sleep(1) ;

	RMSG_COUT << std::endl << "RpmsgMgr::startDriver - DONE" << std::endl ;

	return rc == 0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool RpmsgMgr::stopDriver()
{
//std::cerr << std::endl << "RpmsgMgr::stopDriver " << std::endl ;

	std::string cmd("modprobe -r -v " + RPMSG_DRIVER) ;

	errno = 0 ;
	int rc = system(cmd.c_str()) ;

	RMSG_COUT << std::endl << "RpmsgMgr::stopDriver - cmd: " << cmd << " rc=" << rc << " errno=" << errno << std::endl ;

	RMSG_COUT << std::endl << "RpmsgMgr::stopDriver - DONE" << std::endl ;

	return rc == 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int RpmsgMgr::openRpmsgCtrl(const std::string &device, std::string& rpmsgCtrlName)
{
	RMSG_COUT << std::endl << "RpmsgMgr::openRpmsgCtrl" << std::endl ;

	// e.g. /sys/bus/rpmsg/devices/virtio0.rpmsg-openamp-demo-channel.-1.0/rpmsg
	std::string dir(RPMSG_SYS_BUS + "/devices/" + device + "/rpmsg") ;
	std::vector<std::string> contents(Path::dirContents(dir)) ;

	// TODO: How does this work when running both R5-0 and R5-1 ?
	for (auto& path : contents)
	{
		std::string file(Path::basename(path));
		RMSG_COUT << std::endl << " * file " << file << std::endl ;

		// find the rpmsg control name
		// e.g. /sys/bus/rpmsg/devices/virtio0.rpmsg-openamp-demo-channel.-1.0/rpmsg/rpmsg_ctrl0
		if (!startsWith(file, RPMSG_CTRL_PREFIX))
			continue ;

		// try opening the corresponding device
		// e.g. /dev/rpmsg_ctrl0
		std::string devPath("/dev/" + file) ;
		int fd = open(devPath.c_str(), O_RDWR | O_NONBLOCK) ;
		if (fd < 0)
			return fd ;

		rpmsgCtrlName = file ;
		return fd ;
	}

	return -1 ;
}

//-------------------------------------------------------------------------------------------------------------
bool RpmsgMgr::createRpmsgEndpoint(int ctrlFd, const std::string &serviceName)
{
#ifndef OFF_TARGET
	struct rpmsg_endpoint_info eptinfo ;
	strcpy(eptinfo.name, serviceName.c_str());
	eptinfo.src = 0;
	eptinfo.dst = 0xFFFFFFFF;

	int ret = ioctl(ctrlFd, RPMSG_CREATE_EPT_IOCTL, &eptinfo);
	if (ret)
	{
		std::cerr << "Failed to create endpoint:" << ret << std::endl ;
		return false ;
	}
#endif

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RpmsgMgr::getEndpointDevPath(const std::string &rpmsgCtrlName, const std::string& eptName, std::string &devPath)
{
	for (unsigned i = 0; i < 128; i++)
	{
		std::string eptNamePath(RPMSG_SYS_CLASS + "/" + rpmsgCtrlName + "/rpmsg" + std::to_string(i) + "/name") ;
std::cerr << "Checking: " << eptNamePath << std::endl ;

		std::string svcName ;
		RemoteProc::readSysFile(eptNamePath, svcName) ;

		if (svcName != eptName)
			continue ;

		devPath = "/dev/rpmsg" + std::to_string(i) ;
		return true ;
	}

	return false ;
}
