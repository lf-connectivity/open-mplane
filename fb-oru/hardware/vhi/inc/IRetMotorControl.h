/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRetMotorControl.h
 * \brief     Ret Motor control virtual interface
 *
 *
 * \details
 *
 */


#ifndef IRETMOTORCONTROL_H_
#define IRETMOTORCONTROL_H_

#include <memory>
#include <vector>
#include <string>
#include <map>

namespace Mplane {

class IRetMotorControl
{
public:

	virtual ~IRetMotorControl() {};

	enum MasterStatus_T
	{
		MASTER_INIT,
		MASTER_CONN,
		MASTER_SCAN,
		MASTER_READY,
		MASTER_ERROR
	};

	static const char* statusToStr(MasterStatus_T status);

	/**
	* Static method used to create a singleton instance of an object that implements the IRetMotorControl interface.
	*/
	static std::shared_ptr<IRetMotorControl> getInstance(void);

	/**
	* Method to reset the devices on the AISG bus
	*/
	virtual bool reset(void) = 0;

	/**
	* Method to reset a specific device on the AISG bus
	*/
	virtual bool reset(unsigned char address) = 0;

	/**
	* Method to connect to the communication port
	*/
	virtual bool connect(void) = 0;

	/**
	* Method to check if communication port is connected
	*/
	virtual bool isConnected(void) = 0;

	/**
	* Method to disconnect communication port
	*/
	virtual bool disconnect(void) = 0;

	/**
	* Method used to retreive the Motor controller information
	*/
	virtual bool getMasterInfo(std::string& serialNum, std::string& softwareVersion) = 0;

	/**
	* Method to scan the AISG bus for devices
	*/
	virtual bool scan(void) = 0;

	/**
	* Method to read the number of devices on the AISG bus
	*/
	virtual int getNumDevices(void) = 0;

	/**
	* Method used to retreive the Ret motor information
	*/
	virtual bool getDeviceInfo(unsigned char address, std::string& uid, std::string& productNum, std::string& serialNum,
		std::string& hardwareVersion, std::string& softwareVersion, std::string& vendorCode, std::string& deviceType) = 0;

	/**
	* Method to read the number of subunits on a specific device
	*/
	virtual bool getNumSubunits(unsigned char address, unsigned & numSubUnits) = 0;

	/**
	* Method to read the minimum supported electrical tilt
	*/
	virtual bool getMinTilt(unsigned char address, double & minTilt, int antenna = -1) = 0;

	/**
	* Method to read the maximum supported electrical tilt
	*/
	virtual bool getMaxTilt(unsigned char address, double & maxTilt, int antenna = -1) = 0;

	/**
	* Method to start calibration
	*/
	virtual bool calibrate(unsigned char address, int antenna = -1) = 0;

	/**
	* Method to get the current tilt value
	*/
	virtual bool getTilt(unsigned char address, double& tilt, int antenna = -1) = 0;

	/**
	* Method to set a tilt value
	*/
	virtual bool setTilt(unsigned char address, double tilt, int antenna = -1) = 0;

	/**
	* Method to get the status of the master controller
	*/
	virtual std::string status(void) = 0;

	/**
	* Method to get the status of a device
	*/
	virtual std::string status(unsigned char address) = 0;

	/**
	* Method to get the alarm status
	*/
	virtual bool getAlarmStatus(unsigned char address, std::string & alarmStatus, int antenna = -1) = 0;

	/**
	 * This method that gets called periodically to perform routine tasks
	 */
	virtual void timerUpdate(void) = 0;

};

}

#endif /* IRETMOTORCONTROL_H_ */
