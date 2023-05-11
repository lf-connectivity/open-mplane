/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RetMotorComm.h
 * \brief     Ret Motor device class (represents a single Motor)
 *
 *
 * \details
 *
 */


#ifndef RETMOTORCOMM_H_
#define RETMOTORCOMM_H_

#include <memory>
#include <mutex>
#include <condition_variable>

#include "IRetMotorComm.h"
#include "AisgCommand.h"
#include "Conditional.h"
#include "ISerialDriver.h"
#include "Loggable.h"

namespace Mplane {

class RetMotorComm: public IRetMotorComm, public Loggable
{
public:

	static const std::map<unsigned char, std::string> mAlarmCodeToString;

	/**
	* Constructor for RetMotorComm
	*/
	RetMotorComm(std::string uid,
		std::string vendorCode, unsigned deviceType,
		std::shared_ptr<ISerialDriver> aisgDrv);

	/**
	* Destructor for RetMotorComm
	*/
	virtual ~RetMotorComm();

	/**
	* Method to reinitialize the Motor so that it gets connected and assigned the address
	* This method is used when the physical layer reconnects
	*/
	virtual void reInitialize(void) override;

	/**
	* Method to resett the Ret Motor
	*/
	virtual bool reset(void) override;

	/**
	* Method to setup the motor by assigning address, connecting and subscribing alarms
	*/
	virtual void stateMachineMotor(unsigned char address) override;

	/**
	* Method used to retreive the Ret motor information.
	*/
	virtual bool getDeviceInfo(std::string& uid, std::string& productNum, std::string& serialNum,
		std::string& hardwareVersion, std::string& softwareVersion, std::string& vendorCode,
		std::string & deviceType) override;

	/**
	* Method to read the number of subunits
	*/
	virtual bool getNumSubunits(unsigned& numSubunits) override;

	/**
	* Method to read the minimum supported electrical tilt
	*/
	virtual bool getMinTilt(double & minTilt, int antenna = -1) override;

	/**
	* Method to read the maximum supported electrical tilt
	*/
	virtual bool getMaxTilt(double & maxTilt, int antenna = -1) override;

	/**
	* Method to start calibration
	*/
	virtual bool calibrate(int antenna = -1) override;

	/**
	* Method to disconnect Ret Motor
	*/
	virtual bool disconnect(void) override;

	/**
	* Method to get the current tilt value
	*/
	virtual bool getTilt(double& tilt, int antenna = -1) override;

	/**
	* Method to set a tilt value
	*/
	virtual bool setTilt(double tilt, int antenna = -1) override;
	/**
	* Method to get the status of the device
	*/
	virtual unsigned status(void) override;

	/**
	* Method to get the alarm status
	*/
	virtual bool getAlarmStatus(std::string& alarmStatus, int antenna = -1) override;

	/**
	* Method to process the response
	*/
	virtual void processResponse(std::vector<unsigned char> response) override;

	/**
	* Method to check whether the motor details match with the passed parameters
	*/
	virtual bool isThisMotor(std::string uid, std::string vendorCode, unsigned char deviceType) override;

protected:

	std::mutex mMutex;
	std::mutex mAccessMutex;
	std::condition_variable mReqCond;
	//std::condition_variable mDevStatCond;

	unsigned char mAddress;                             //!> Address of the motor
	std::string mSerialNumber;                          //!> Serial number of the motor
	std::string mProductNumber;                         //!> Product number of the motor
	std::string mUid;                                   //!> Unique ID of the motor
	std::string mSoftwareVer;                           //!> Software version of the motor
	std::string mHardwareVer;                           //!> Hardware version of the motor
	std::string mVendorCode;                            //!> Vendor code of the motor
	RetType_T mType;                                    //!> Device type
	unsigned char mNr;                                  //!> Received sequence number
	unsigned char mNs;                                  //!> Next expected sequence number
	bool mConnected;                                    //!> Connection flag
	Req_T mReq;                                         //!> Current/Last request
	unsigned long mReqStartTime;                        //!> Tick count at which request was sent
	std::vector<unsigned char> mReqFrame;               //!> Request frame containing the start/stop flags, Crc and data
	std::vector<unsigned char> mReqData;                //!> Request data only
	std::map<unsigned char, double> mResponseTilt;      //!> Get tilt response
	unsigned int mNumSubunits;                          //!> If device is multi-ret, then this stores the number of antennae
	std::map<unsigned char, double> mMinTilt;           //!> Minimum supported electrical tilt
	std::map<unsigned char, double> mMaxTilt;           //!> Maximum supported electrical tilt
	std::map<unsigned char, std::vector<unsigned char>> mAlarmStatus;  //!> Current Alarm status for the device

	MotorStatus_T mStatus;                              //!> Status of the object
	MotorEvents_T mEvent;                               //!> Event to signal the main state machine
	InitSubStates_T mInitSubState;                      //!> Substates while the device is being setup
	InitEvents_T mInitEvent;                            //!> Event to signal to the init sub states

	std::shared_ptr<ISerialDriver> mAisgDrv;            //!> Pointer to Aisg serial driver

	void setStatus(MotorStatus_T status);
	void setEvent(MotorEvents_T evt);
	void setInitEvent(InitEvents_T evt);
	void setReq(Req_T req);

	/**
	* Method to assign address of the Ret Motor
	*/
	bool assignAddress(unsigned char address);

	/**
	* Method to connect to Ret Motor
	*/
	bool connect(void);

	/**
	* Method to subscribe alarms
	*/
	bool alarmsSubscribe(void);

	/**
	* Method to check response timeout. This method has to be called
	by the creator periodically
	*/
	void checkResponseTimeout(void);

	/**
	* Method to keep alive the link
	*/
	void keepLinkAlive(void);

private:
	void populateElementaryProc(unsigned char command_id, unsigned char* data, unsigned length);
	void populateElementaryProc(unsigned char command_id, unsigned char antenna, unsigned char* data, unsigned length);
	bool sendRequest(void);
	bool checkByte(unsigned char& result, unsigned char input);
	void i_frame_process(std::vector<unsigned char> response);
	void s_frame_process(std::vector<unsigned char> response);
	void u_frame_process(std::vector<unsigned char> response);
	void recordStartTime(void);

	std::map<Req_T, std::unique_ptr<AisgCommand>> mCommandMap;
	unsigned char getCommndId(Req_T command);
	unsigned long getCommandTimeout(Req_T command);
	AisgCommand::respCallback getResponseCallback(Req_T command);
	Req_T getRequestFromCommandId(unsigned char);

	bool sendKeepAlive(void);

	//Response Callback functions
	void cb_no_action(std::vector<unsigned char> response);
	void cb_getInformation(std::vector<unsigned char> response);
	void cb_getTilt(std::vector<unsigned char> response);
	void cb_getNumAntennae(std::vector<unsigned char> response);
	void cb_getAlarmIndication(std::vector<unsigned char> response);
	void cb_getAlarmStatus(std::vector<unsigned char> response);
	void cb_getDeviceData(std::vector<unsigned char> response);
	void cb_generic(std::vector<unsigned char> response);
	void cb_antennaGetTilt(std::vector<unsigned char> response);
	void cb_antennaGetAlarmStatus(std::vector<unsigned char> response);
	void cb_antennaGeneric(std::vector<unsigned char> response);
	void cb_antennaGetAlarmIndication(std::vector<unsigned char> response);
	void cb_antennaGetDeviceData(std::vector<unsigned char> response);
};
}

#endif //RETMOTORCOMM_H_
