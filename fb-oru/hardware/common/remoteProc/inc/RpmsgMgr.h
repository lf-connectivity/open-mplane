/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RpmsgMgr.h
 * \brief     Manages the access to the rpmsg driver
 *
 *
 * \details   Ensures the rpmsg_user_dev_driver is running and manages access to the rpmsg devices
 * 			depending on the order in which the channels have been started up. Access is via an index (which
 * 			can be anything, but for ARM R5 it is useful to make the index 0 and 1 corresponding to R5 0 and R5 1)
 *
 */


#ifndef _RPMSGMGR_H_
#define _RPMSGMGR_H_

#include <memory>
#include <map>
#include <vector>
#include <string>

namespace Mplane {

/*!
 * \class  RpmsgMgr
 * \brief
 * \details
 *
 */
class RpmsgMgr {
public:

	/** All access should be via the singleton **/
	static std::shared_ptr<RpmsgMgr> singleton() ;

	RpmsgMgr() ;
	virtual ~RpmsgMgr() ;

	/**
	 * Called before remote software is started. Get's a snapshot of the sys bus rpmsg devices currently created.
	 * addDevice() will then be called once the software has started so that the newly created device can be found
	 */
	bool addingDevice(unsigned index) ;

	/**
	 * Called when a channel is started up. The /dev/rpmsgX device will be associated with this index
	 */
	bool addDevice(unsigned index) ;

	/**
	 * Called when a channel is shut down. If there are no devices then the rpmsg_user_dev_driver is removed
	 */
	bool delDevice(unsigned index) ;

	/**
	 * get the device name of the rpmsg for this index
	 */
	std::string getDevice(unsigned index) ;

private:
	bool startDriver() ;
	bool stopDriver() ;
	int openRpmsgCtrl(const std::string& device, std::string& rpmsgCtrlName) ;
	bool createRpmsgEndpoint(int ctrlFd, const std::string& serviceName) ;
	bool getEndpointDevPath(const std::string& rpmsgCtrlName, const std::string& eptName, std::string& devPath) ;

private:
	std::map<unsigned, std::string> mDeviceMap ;
	std::map<unsigned, std::vector<std::string>> mDevices ;
} ;

}

#endif /* _RPMSGMGR_H_ */
