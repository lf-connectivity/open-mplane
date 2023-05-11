/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RetMotorControl.h
 * \brief     Motor control implementation
 *
 *
 * \details
 *
 */

#ifndef RETMOTORCONTROL_H_
#define RETMOTORCONTROL_H_

#include "IRetMotorControl.h"
#include "IRetMotorComm.h"
#include "Mutex.h"
#include "AisgSerialDriver.h"
#include "ISerialDriver.h"
#include "ISerialDataReceived.h"
#include "Observer.hpp"
#include "Loggable.h"

namespace Mplane {

class RetMotorControl: public IRetMotorControl, public Observer<ISerialDataReceived>, public Loggable {
public:

	static const unsigned int MAX_RX_BUFF_SIZE;
	static const std::string AISG_DEV_PATH;

	enum ResponseStates_T {
		WAITING_FOR_START_FLAG, RECEIVING_DATA
	};

	enum ExecuteEvents_T {
		TIMER_UPDATE, RESET_REQ, RX_DATA
	};

	/**
	 * Constructor for MotorControl
	 */
	RetMotorControl();

	/**
	 * Destructor for MotorControl
	 */
	virtual ~RetMotorControl();

	/**
	 * Static method used to create a singleton instance of an object that implements the IRetMotorControl interface.
	 */
	static std::shared_ptr<IRetMotorControl> getInstance(void);

	/**
	 * Method to reset the devices on the AISG bus
	 */
	virtual bool reset(void) override;

	/**
	 * Method to reset a specific device on the AISG bus
	 */
	virtual bool reset(unsigned char address) override;

	/**
	 * Method to connect to the communication port
	 */
	virtual bool connect(void) override;

	/**
	 * Method to check if communication port is connected
	 */
	virtual bool isConnected(void) override;

	/**
	 * Method to disconnect communication port
	 */
	virtual bool disconnect(void) override;

	/**
	 * Method used to retreive the Motor controller information
	 */
	virtual bool getMasterInfo(std::string& serialNum,
			std::string& softwareVersion) override;

	/**
	 * Method to scan the AISG bus for devices
	 */
	virtual bool scan(void) override;

	/**
	 * Method to read the number of devices on the AISG bus
	 */
	virtual int getNumDevices(void) override;

	/**
	 * Method used to retreive the Ret motor information
	 */
	virtual bool getDeviceInfo(unsigned char address, std::string& uid,
			std::string& productNum, std::string& serialNum,
			std::string& hardwareVersion, std::string& softwareVersion,
			std::string& vendorCode, std::string& deviceType) override;

	/**
	 * Method to read the number of subunits on a specific device
	 */
	virtual bool getNumSubunits(unsigned char address, unsigned & numSubUnits)
			override;

	/**
	 * Method to read the minimum supported electrical tilt
	 */
	virtual bool getMinTilt(unsigned char address, double & minTilt,
			int antenna = -1) override;

	/**
	 * Method to read the maximum supported electrical tilt
	 */
	virtual bool getMaxTilt(unsigned char address, double & maxTilt,
			int antenna = -1) override;

	/**
	 * Method to start calibration
	 */
	virtual bool calibrate(unsigned char address, int antenna = -1) override;

	/**
	 * Method to get the current tilt value
	 */
	virtual bool getTilt(unsigned char address, double& tilt, int antenna = -1)
			override;

	/**
	 * Method to set a tilt value
	 */
	virtual bool setTilt(unsigned char address, double tilt, int antenna = -1)	override;

	/**
	 * Method to get the status of the master controller
	 */
	virtual std::string status(void) override;

	/**
	 * Method to get the status of a device
	 */
	virtual std::string status(unsigned char address) override;

	/**
	 * Method to get the alarm status
	 */
	virtual bool getAlarmStatus(unsigned char address,
			std::string & alarmStatus, int antenna = -1) override;

	/**
	 * This method that gets called periodically to perform routine tasks
	 */
	virtual void timerUpdate(void) override;

protected:

	/**
	 * This method is the execution method that performs tasks as per the received event
	 */
	void execute(ExecuteEvents_T evt);

	/**
	 * This method to receive the data from the communication bus
	 */
    void receiveData(void);

	/**
	 * This method to perform routine timely checks
	 */
    void performRoutineTask(void);

	/**
	 * Method to write the status variable
	 */
	void setStatus(MasterStatus_T status);

    /*!
     *
     * Method to allow serial received data to be notified to us.
     *
     */
	virtual void update(ISerialDataReceived& subject);

	virtual const char* name() const ;

	std::shared_ptr<ISerialDriver> mAisgDrv;            //!> Pointer to Aisg serial driver

	std::vector<IRetMotorComm*> mMotorDevices;          //!> Vector of MotorComm objects - one for each motor device

	bool mConnected;                                    //!> Whether communication port is opened

	Mutex mMutex;                                       //!> Mutex to protect the status variable
	Mutex mExeMutex;                                    //!> Mutex to protect the execute method
	MasterStatus_T mStatus;                             //!> Status of the master

	ResponseStates_T mResponseState;                    //!> Response state
	std::vector<unsigned char> mResponseFrame;          //!> Response frame
	std::vector<unsigned char> mFormattedResponseFrame; //!> Response frame processed for escaped characters

private:

	unsigned long mScanStartTime;

	void processRxData(char* data, unsigned long length);
	bool formatRxData(void);
	bool checkScanResponse(void);
	void checkScanTimeout(void);
	void removeDevices(void);
	void disconnectWithErr(void);
	void executeDisconnect(void);
};
}

#endif //RETMOTORCONTROL_H_
