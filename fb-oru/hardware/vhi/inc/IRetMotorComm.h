/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRetMotorComm.h
 * \brief     Ret Motor communication virtual interface
 *
 *
 * \details
 *
 */


#ifndef IRETMOTORCOMM_H_
#define IRETMOTORCOMM_H_


#include <memory>
#include <vector>
#include <string>
#include <map>
#include "ISerialDriver.h"

namespace Mplane
{

class IRetMotorComm
{
public:

	virtual ~IRetMotorComm(){};

	enum MotorStatus_T
	{
		DEVICE_INIT,
		DEVICE_READY,
		DEVICE_RUN,
		DEVICE_FAIL,
		DEVICE_ERROR
	};

	enum MotorEvents_T
	{
		NO_EVT,
		EVT_RUN,
		EVT_TIMEOUT,
		EVT_RESPONSE_RECD,
		EVT_RESPONSE_FAIL
	};

	static const char* statusToStr(MotorStatus_T status);

	enum InitSubStates_T
	{
		ASSIGN_ADDRESS,
		CONNECT_TO_DEVICE,
		WAIT_COMPLETION,
		SETUP_COMPLETE,
		SETUP_FAILED
	};

	enum InitEvents_T
	{
		NO_INIT_EVT,
		EVT_ADDRESS_ASSIGNED,
		EVT_INIT_TIMEOUT,
		EVT_CONNECTED
	};

	enum Req_T
	{
		NO_CMD,
		XID_ADDRESS,
		CMD_RESET,
		CMD_CONNECT,
		CMD_DISCONNECT,
		GET_INFORMATION,
		ALARM_SUBSCRIBE,
		CMD_CALIBRATE,
		GET_TILT,
		SET_TILT,
		ALARM_INDICATION,
		GET_ALARM_STATUS,
		GET_MIN_TILT,
		GET_MAX_TILT,
		GET_NUM_ANTENNAE,
		CMD_ANTENNA_CALIBRATE,
		GET_ANTENNA_TILT,
		SET_ANTENNA_TILT,
		ANTENNA_ALARM_INDICATION,
		GET_ANTENNA_ALARM_STATUS,
		GET_ANTENNA_MIN_TILT,
		GET_ANTENNA_MAX_TILT
	};

	enum RetType_T
	{
		SINGLE_RET = 0x01,
		MULTI_RET = 0x11
	};

	static const char* deviceTypeToStr(RetType_T type);

	enum FrameType_T
	{
		FRAME_TYPE_I,
		FRAME_TYPE_S,
		FRAME_TYPE_U
	};

	static const unsigned char FLAG_START;		/* Starts each frame */
	static const unsigned char FLAG_STOP; 		/* Ends each frame */
	static const unsigned char ESC_ASYNC; 		/* Escapes special chars (0x7d, 0x7e, 0x7f) */
	static const unsigned char ESC_COMPL; 		/* XORed with special chars in data */
	static const unsigned char Iframe_MASK;
	static const unsigned char Sframe_MASK;
	static const unsigned char PF_MASK;
	static const unsigned char RR_MASK;
	static const unsigned char RNR_MASK;

	//I request frame Command IDs
	static const unsigned char COMMAND_ID_RESET;
	static const unsigned char COMMAND_ID_GET_INFORMATION;
	static const unsigned char COMMAND_ID_ALARM_SUBSCRIBE;
	static const unsigned char COMMAND_ID_CALIBRATE;
	static const unsigned char COMMAND_ID_GET_TILT;
	static const unsigned char COMMAND_ID_SET_TILT;
	static const unsigned char COMMAND_ID_GET_ALARM_STATUS;
	static const unsigned char COMMAND_ID_ALARM_INDICATION;
	static const unsigned char COMMAND_ID_GET_DEVICE_DATA;
	static const unsigned char COMMAND_ID_GET_NUM_ANTENNAE;
	static const unsigned char COMMAND_ID_ANTENNA_CALIBRATE;
	static const unsigned char COMMAND_ID_GET_ANTENNA_TILT;
	static const unsigned char COMMAND_ID_SET_ANTENNA_TILT;
	static const unsigned char COMMAND_ID_GET_ANTENNA_ALARM_STATUS;
	static const unsigned char COMMAND_ID_ANTENNA_ALARM_INDICATION;
	static const unsigned char COMMAND_ID_GET_ANTENNA_DEVICE_DATA;
	static const unsigned char FIELD_CODE_MIN_TILT;
	static const unsigned char FIELD_CODE_MAX_TILT;
	static const unsigned char TX_FRAME_ADDRESS_POS;
	static const unsigned char TX_FRAME_CONTROL_POS;

	//I response frame contents and positions
	static const unsigned char RX_FRAME_ADDRESS_POS;
	static const unsigned char RX_FRAME_CONTROL_POS;
	static const unsigned char RX_FRAME_COMMAND_POS;
	static const unsigned char RX_FRAME_LEN_POS;
	static const unsigned char RX_FRAME_SINGLE_RET_RESP_CODE_POS;
	static const unsigned char RX_FRAME_SINGLE_RET_DATA_START_POS;
	static const unsigned char RX_FRAME_MULTI_RET_ANTENNA_NUM_POS;
	static const unsigned char RX_FRAME_MULTI_RET_RESP_CODE_POS;
	static const unsigned char RX_FRAME_MULTI_RET_DATA_START_POS;

	//XID request frame contents and positions
	static const unsigned char BROADCAST_ADDRESS;
	static const unsigned char COMMAND_ID_CONNECT;
	static const unsigned char COMMAND_ID_DISCONNECT;
	static const unsigned char XID_COMMAND;
	static const unsigned char XID_FORMAT_IDENTIFIER;
	static const unsigned char XID_GROUP_IDENTIFIER;
	static const unsigned char XID_GROUP_LEN_POS;
	static const unsigned char XID_PI_UID;
	static const unsigned char XID_PI_ADDRESS;
	static const unsigned char XID_PL_ADDRESS;
	static const unsigned char XID_PI_DEVICE_TYPE;
	static const unsigned char XID_PL_DEVICE_TYPE;
	static const unsigned char XID_PI_VENDOR_CODE;
	static const unsigned char XID_PL_VENDOR_CODE;

	//XID response frame contents and positions
	static const unsigned char XID_RESPONSE;
	static const unsigned char UA_RESPONSE;

	//Constants for response timeouts
	static const unsigned long TIME_OPERATION;
	static const unsigned long TIME_SCAN;
	static const unsigned long TIME_CALIBRATION;
	static const unsigned long TIME_SET_TILT;
	static const unsigned long KEEP_ALIVE_TIMEOUT;

	/**
	* Method to disconnect Ret Motor
	*/
	virtual bool disconnect(void) = 0;

	/**
	* Method to reset the system
	*/
	static bool resetAll(std::shared_ptr<ISerialDriver> aisgDrv);

	/**
	* Method to scan the bus for devices
	*/
	static bool scan(std::shared_ptr<ISerialDriver> aisgDrv);

	/**
	* Method to get the frame type given the control byte
	*/
	static FrameType_T getFrameType(unsigned char control);

	/**
	* Method to process XID frame and and decode content
	*/
	static bool decode_xid_frame(std::vector<unsigned char> response, std::string & uid,
		std::string & vendorCode, unsigned char& type);

	/**
	* Method to resett the Ret Motor
	*/
	virtual bool reset(void) = 0;

	/**
	* Method to reinitialize the Motor so that it gets connected and assigned the address
	* This method is used when the physical layer reconnects
	*/
	virtual void reInitialize(void) = 0;

	/**
	* Method to setup the motor by assigning address, connecting and subscribing alarms
	*/
	virtual void stateMachineMotor(unsigned char address) = 0;

	/**
	* Method used to retreive the Ret motor information.
	*/
	virtual bool getDeviceInfo(std::string& uid, std::string & productNum, std::string & serialNum,
		std::string & hardwareVersion, std::string & softwareVersion, std::string & vendorCode,
		std::string & deviceType) = 0;

	/**
	* Method to read the number of subunits
	*/
	virtual bool getNumSubunits(unsigned & numSubunits) = 0;

	/**
	* Method to read the minimum supported electrical tilt
	*/
	virtual bool getMinTilt(double & minTilt, int antenna = -1) = 0;

	/**
	* Method to read the maximum supported electrical tilt
	*/
	virtual bool getMaxTilt(double & maxTilt, int antenna = -1) = 0;

	/**
	* Method to start calibration
	*/
	virtual bool calibrate(int antenna = -1) = 0;

	/**
	* Method to get the current tilt value
	*/
	virtual bool getTilt(double& tilt, int antenna = -1) = 0;

	/**
	* Method to set a tilt value
	*/
	virtual bool setTilt(double tilt, int antenna = -1) = 0;

	/**
	* Method to get the status of the device
	*/
	virtual unsigned status(void) = 0;

	/**
	* Method to get the alarm status
	*/
	virtual bool getAlarmStatus(std::string & alarmStatus, int antenna = -1) = 0;

	/**
	* Method to process the response
	*/
	virtual void processResponse(std::vector<unsigned char> response) = 0;

	/**
	* Method to check whether the motor details match with the passed parameters
	*/
	virtual bool isThisMotor(std::string uid, std::string vendorCode, unsigned char deviceType) = 0;
};
}

#endif //IRETMOTORCOMM_H_
