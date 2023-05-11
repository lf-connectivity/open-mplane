/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RetMotorComm.cpp
 * \brief     Ret Motor device class (represents a single Motor)
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iterator>
#include <map>
#include <vector>
#include <algorithm>
#include <sys/time.h>

#include "RetMotorComm.h"
#include "fcs.h"
#include "ILoggable.h"
#include "Task.h"

using namespace Mplane;
using namespace std;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned char IRetMotorComm::FLAG_START(0x7E);		/* Starts each frame */
const unsigned char IRetMotorComm::FLAG_STOP(0x7E); 		/* Ends each frame */
const unsigned char IRetMotorComm::ESC_ASYNC(0x7D); 		/* Escapes special chars (0x7d, 0x7e, 0x7f) */
const unsigned char IRetMotorComm::ESC_COMPL(0x20); 		/* XORed with special chars in data */
const unsigned char IRetMotorComm::Iframe_MASK(0x00);
const unsigned char IRetMotorComm::Sframe_MASK(0x01);
const unsigned char IRetMotorComm::PF_MASK(0x10);
const unsigned char IRetMotorComm::RR_MASK(0x00);
const unsigned char IRetMotorComm::RNR_MASK(0x04);

//I frame request command IDs
const unsigned char IRetMotorComm::COMMAND_ID_RESET(0x03);
const unsigned char IRetMotorComm::COMMAND_ID_GET_INFORMATION(0x05);
const unsigned char IRetMotorComm::COMMAND_ID_ALARM_SUBSCRIBE(0x12);
const unsigned char IRetMotorComm::COMMAND_ID_CALIBRATE(0x31);
const unsigned char IRetMotorComm::COMMAND_ID_GET_TILT(0x34);
const unsigned char IRetMotorComm::COMMAND_ID_SET_TILT(0x33);
const unsigned char IRetMotorComm::COMMAND_ID_ALARM_INDICATION(0x07);
const unsigned char IRetMotorComm::COMMAND_ID_GET_ALARM_STATUS(0x04);
const unsigned char IRetMotorComm::COMMAND_ID_GET_DEVICE_DATA(0x0F);
const unsigned char IRetMotorComm::COMMAND_ID_GET_NUM_ANTENNAE(0x88);
const unsigned char IRetMotorComm::COMMAND_ID_ANTENNA_CALIBRATE(0x80);
const unsigned char IRetMotorComm::COMMAND_ID_GET_ANTENNA_TILT(0x82);
const unsigned char IRetMotorComm::COMMAND_ID_SET_ANTENNA_TILT(0x81);
const unsigned char IRetMotorComm::COMMAND_ID_ANTENNA_ALARM_INDICATION(0x85);
const unsigned char IRetMotorComm::COMMAND_ID_GET_ANTENNA_ALARM_STATUS(0x87);
const unsigned char IRetMotorComm::COMMAND_ID_GET_ANTENNA_DEVICE_DATA(0x84);
const unsigned char IRetMotorComm::FIELD_CODE_MIN_TILT(0x07);
const unsigned char IRetMotorComm::FIELD_CODE_MAX_TILT(0x06);
const unsigned char IRetMotorComm::TX_FRAME_ADDRESS_POS(1);
const unsigned char IRetMotorComm::TX_FRAME_CONTROL_POS(2);

//I frame response contents and positions
const unsigned char IRetMotorComm::RX_FRAME_ADDRESS_POS(1);
const unsigned char IRetMotorComm::RX_FRAME_CONTROL_POS(2);
const unsigned char IRetMotorComm::RX_FRAME_COMMAND_POS(3);
const unsigned char IRetMotorComm::RX_FRAME_LEN_POS(4);
const unsigned char IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS(6);
const unsigned char IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS(7);
const unsigned char IRetMotorComm::RX_FRAME_MULTI_RET_ANTENNA_NUM_POS(6);
const unsigned char IRetMotorComm::RX_FRAME_MULTI_RET_RESP_CODE_POS(7);
const unsigned char IRetMotorComm::RX_FRAME_MULTI_RET_DATA_START_POS(8);

//XID frame request contents and positions
const unsigned char IRetMotorComm::BROADCAST_ADDRESS(0xFF);
const unsigned char IRetMotorComm::COMMAND_ID_CONNECT(0x93);
const unsigned char IRetMotorComm::COMMAND_ID_DISCONNECT(0x53);
const unsigned char IRetMotorComm::XID_COMMAND(0xBF);
const unsigned char IRetMotorComm::XID_FORMAT_IDENTIFIER(0x81);
const unsigned char IRetMotorComm::XID_GROUP_IDENTIFIER(0xF0);
const unsigned char IRetMotorComm::XID_GROUP_LEN_POS(4);
const unsigned char IRetMotorComm::XID_PI_UID(1);
const unsigned char IRetMotorComm::XID_PI_ADDRESS(2);
const unsigned char IRetMotorComm::XID_PL_ADDRESS(1);
const unsigned char IRetMotorComm::XID_PI_DEVICE_TYPE(4);
const unsigned char IRetMotorComm::XID_PL_DEVICE_TYPE(1);
const unsigned char IRetMotorComm::XID_PI_VENDOR_CODE(6);
const unsigned char IRetMotorComm::XID_PL_VENDOR_CODE(2);

//XID frame response contents and positions
const unsigned char IRetMotorComm::XID_RESPONSE(0xBF);
const unsigned char IRetMotorComm::UA_RESPONSE(0x73);

//Command timeouts
const unsigned long IRetMotorComm::TIME_OPERATION(1000);
const unsigned long IRetMotorComm::TIME_SCAN(1000);
const unsigned long IRetMotorComm::TIME_CALIBRATION(240000);
const unsigned long IRetMotorComm::TIME_SET_TILT(120000);
const unsigned long IRetMotorComm::KEEP_ALIVE_TIMEOUT(120000);

//Map for alarm codes and their descriptions
const std::map<unsigned char, std::string> RetMotorComm::mAlarmCodeToString =
{
	{0x01, "Actuator Detection Fail"},
	{0x02, "Motor Jam"},
	{0x03, "Actuator Jam"},
	{0x04, "Block Number Sequence Error"},
	{0x05, "Command not executed - Busy"},
	{0x06, "Command not executed - Checksum Error"},
	{0x07, "Command Sequence Error" },
	{0x08, "Data Error" },
	{0x09, "Device Disabled" },
	{0x0a, "EEPROM Error" },
	{0x0b, "Command failed" },
	{0x0c, "Flash Erase Error" },
	{0x0d, "Flash Error" },
	{0x0e, "Not Calibrated"},
	{0x0f, "Not Configured"},
	{0x11, "Hardware Error"},
	{0x12, "Software Error"},
	{0x13, "Out of Range"},
	{0x14, "Position Lost"},
	{0x19, "Unknown Procedure"},
	{0x1d, "Read Only"},
	{0x1e, "Unknown Parameter"},
	{0x21, "Working Software Missing"},
	{0x22, "Invalid File Content"},
	{0x24, "Format Error"},
	{0x25, "Unsupported Procedure"},
	{0x26, "Invalid Procedure Sequence"},
	{0x27, "Actuator Interference"}
};

//=============================================================================================================
// Constructor and Destructor
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
RetMotorComm::RetMotorComm(std::string uid,
	std::string vendorCode, unsigned deviceType, std::shared_ptr<ISerialDriver> aisgDrv):
	Loggable("RetMotorComm", "RetMotor"),
	mMutex(),
	mAccessMutex(),
	mReqCond(),
	//mDevStatCond(),
	mAddress(),
	mSerialNumber(),
	mProductNumber(),
	mUid(uid),
	mSoftwareVer(),
	mHardwareVer(),
	mVendorCode(vendorCode),
	mType(static_cast<IRetMotorComm::RetType_T>(deviceType)),
	mNr(0),
	mNs(0),
	mConnected(false),
	mReq(NO_CMD),
	mReqStartTime(0),
	mReqFrame(),
	mReqData(),
	mResponseTilt(),
	mNumSubunits(0),
	mMinTilt(),
	mMaxTilt(),
	mAlarmStatus(),
	mStatus(DEVICE_INIT),
	mEvent(MotorEvents_T::NO_EVT),
	mInitSubState(InitSubStates_T::ASSIGN_ADDRESS),
	mInitEvent(InitEvents_T::NO_INIT_EVT),
	mAisgDrv(aisgDrv)
{
	mReqStartTime = 0;
	mReqFrame.clear();
	mReqData.clear();
	mAlarmStatus.clear();
	mResponseTilt.clear();
	//For each command, a Command class object is created that stores the command ID, timeout and a response callback
	//To pass a member function callback to another class, it is necessary to bind the member function pointer to a particular instance of a class
	//To make this binding std::bind is used. It binds the current instance of the RetMotorComm object to the callback function pointer.
	//This ensures that when the member function callback is called, the hidden parameter "this" gets passed to the callback
	mCommandMap[XID_ADDRESS] = std::make_unique<AisgCommand>(XID_COMMAND, TIME_OPERATION, std::bind(&RetMotorComm::cb_no_action, this, std::placeholders::_1));
	mCommandMap[CMD_CONNECT] = std::make_unique<AisgCommand>(COMMAND_ID_CONNECT, TIME_OPERATION, std::bind(&RetMotorComm::cb_no_action, this, std::placeholders::_1));
	mCommandMap[CMD_DISCONNECT] = std::make_unique<AisgCommand>(COMMAND_ID_DISCONNECT, TIME_OPERATION, std::bind(&RetMotorComm::cb_no_action, this, std::placeholders::_1));
	mCommandMap[CMD_RESET] = std::make_unique<AisgCommand>(COMMAND_ID_RESET, TIME_OPERATION, std::bind(&RetMotorComm::cb_generic, this, std::placeholders::_1));
	mCommandMap[GET_INFORMATION] = std::make_unique<AisgCommand>(COMMAND_ID_GET_INFORMATION, TIME_OPERATION, std::bind(&RetMotorComm::cb_getInformation, this, std::placeholders::_1));
	mCommandMap[ALARM_SUBSCRIBE] = std::make_unique<AisgCommand>(COMMAND_ID_ALARM_SUBSCRIBE, TIME_OPERATION, std::bind(&RetMotorComm::cb_generic, this, std::placeholders::_1));
	mCommandMap[CMD_CALIBRATE] = std::make_unique<AisgCommand>(COMMAND_ID_CALIBRATE, TIME_CALIBRATION, std::bind(&RetMotorComm::cb_generic, this, std::placeholders::_1));
	mCommandMap[GET_TILT] = std::make_unique<AisgCommand>(COMMAND_ID_GET_TILT, TIME_OPERATION, std::bind(&RetMotorComm::cb_getTilt, this, std::placeholders::_1));
	mCommandMap[SET_TILT] = std::make_unique<AisgCommand>(COMMAND_ID_SET_TILT, TIME_SET_TILT, std::bind(&RetMotorComm::cb_generic, this, std::placeholders::_1));
	mCommandMap[ALARM_INDICATION] = std::make_unique<AisgCommand>(COMMAND_ID_ALARM_INDICATION, TIME_OPERATION, std::bind(&RetMotorComm::cb_getAlarmIndication, this, std::placeholders::_1));
	mCommandMap[GET_ALARM_STATUS] = std::make_unique<AisgCommand>(COMMAND_ID_GET_ALARM_STATUS, TIME_OPERATION, std::bind(&RetMotorComm::cb_getAlarmStatus, this, std::placeholders::_1));
	mCommandMap[GET_MIN_TILT] = std::make_unique<AisgCommand>(COMMAND_ID_GET_DEVICE_DATA, TIME_OPERATION, std::bind(&RetMotorComm::cb_getDeviceData, this, std::placeholders::_1));
	mCommandMap[GET_MAX_TILT] = std::make_unique<AisgCommand>(COMMAND_ID_GET_DEVICE_DATA, TIME_OPERATION, std::bind(&RetMotorComm::cb_getDeviceData, this, std::placeholders::_1));
	mCommandMap[GET_NUM_ANTENNAE] = std::make_unique<AisgCommand>(COMMAND_ID_GET_NUM_ANTENNAE, TIME_OPERATION, std::bind(&RetMotorComm::cb_getNumAntennae, this, std::placeholders::_1));
	mCommandMap[CMD_ANTENNA_CALIBRATE] = std::make_unique<AisgCommand>(COMMAND_ID_ANTENNA_CALIBRATE, TIME_CALIBRATION, std::bind(&RetMotorComm::cb_antennaGeneric, this, std::placeholders::_1));
	mCommandMap[GET_ANTENNA_TILT] = std::make_unique<AisgCommand>(COMMAND_ID_GET_ANTENNA_TILT, TIME_OPERATION, std::bind(&RetMotorComm::cb_antennaGetTilt, this, std::placeholders::_1));
	mCommandMap[SET_ANTENNA_TILT] = std::make_unique<AisgCommand>(COMMAND_ID_SET_ANTENNA_TILT, TIME_SET_TILT, std::bind(&RetMotorComm::cb_antennaGeneric, this, std::placeholders::_1));
	mCommandMap[ANTENNA_ALARM_INDICATION] = std::make_unique<AisgCommand>(COMMAND_ID_ANTENNA_ALARM_INDICATION, TIME_OPERATION, std::bind(&RetMotorComm::cb_antennaGetAlarmIndication, this, std::placeholders::_1));
	mCommandMap[GET_ANTENNA_ALARM_STATUS] = std::make_unique<AisgCommand>(COMMAND_ID_GET_ANTENNA_ALARM_STATUS, TIME_OPERATION, std::bind(&RetMotorComm::cb_antennaGetAlarmStatus, this, std::placeholders::_1));
	mCommandMap[GET_ANTENNA_MIN_TILT] = std::make_unique<AisgCommand>(COMMAND_ID_GET_ANTENNA_DEVICE_DATA, TIME_OPERATION, std::bind(&RetMotorComm::cb_antennaGetDeviceData, this, std::placeholders::_1));
	mCommandMap[GET_ANTENNA_MAX_TILT] = std::make_unique<AisgCommand>(COMMAND_ID_GET_ANTENNA_DEVICE_DATA, TIME_OPERATION, std::bind(&RetMotorComm::cb_antennaGetDeviceData, this, std::placeholders::_1));
}

//-------------------------------------------------------------------------------------------------------------
RetMotorComm::~RetMotorComm()
{
	mCommandMap.clear();
	mReqFrame.clear();
	mReqData.clear();
	mAlarmStatus.clear();
	mResponseTilt.clear();
}

//=============================================================================================================
// Static functions
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
const char * IRetMotorComm::statusToStr(MotorStatus_T status)
{
	switch (status)
	{
	case DEVICE_INIT:
		return "INIT";

	case DEVICE_READY:
		return "READY";

	case DEVICE_RUN:
		return "RUN";

	case DEVICE_FAIL:
		return "FAIL";

	case DEVICE_ERROR:
		return "ERROR";
	}

	return "UNKNOWN";
}

//-------------------------------------------------------------------------------------------------------------
const char* IRetMotorComm::deviceTypeToStr(IRetMotorComm::RetType_T type)
{
	switch (type)
	{
	case IRetMotorComm::SINGLE_RET:
		return "SINGLE-RET";

	case IRetMotorComm::MULTI_RET:
		return "MULTI-RET";
	}

	return "UNKNOWN-DEVICE-TYPE";
}


//-------------------------------------------------------------------------------------------------------------
bool IRetMotorComm::resetAll(std::shared_ptr<ISerialDriver> aisgDrv)
{
	std::vector<unsigned char> reqFrame;
	std::vector<unsigned char> reqData;
	unsigned short crc;					/* The crc value */
	unsigned char crc_l, crc_h;			/* The crc bytes */

	reqFrame.clear();
	reqData.clear();

	//Add start flag
	reqFrame.push_back(FLAG_START);

	//create request data vector
	reqData.push_back(BROADCAST_ADDRESS);
	reqData.push_back(XID_COMMAND);
	reqData.push_back(XID_FORMAT_IDENTIFIER);
	reqData.push_back(XID_GROUP_IDENTIFIER);
	reqData.push_back(0x02); //Data length
	reqData.push_back(0x07); //reset PI
	reqData.push_back(0x00); //data length = 0 for reset PI

	//Copy data into request frame
	for (std::vector<unsigned char>::iterator it = reqData.begin(); it != reqData.end(); ++it)
	{
		reqFrame.push_back(*it);
	}

	//calculate crc on data vector
	crc = fcs::fcs16(fcs::INITFCS16, &reqData[0], reqData.size());
	crc ^= 0xffff;

	crc_l = crc & 0xFF;
	crc_h = (crc >> 8) & 0xFF;

	//Copy crc to request frame
	if (crc_l == ESC_ASYNC)
	{
		reqFrame.push_back(ESC_ASYNC);
		reqFrame.push_back(crc_l ^ ESC_COMPL);
	}
	else
	{
		reqFrame.push_back(crc_l);
	}

	if (crc_h == ESC_ASYNC)
	{
		reqFrame.push_back(ESC_ASYNC);
		reqFrame.push_back(crc_h ^ ESC_COMPL);
	}
	else
	{
		reqFrame.push_back(crc_h);
	}

	//Add stop flag
	reqFrame.push_back(FLAG_STOP);

	//Send the frame over serial
	if (aisgDrv->write(reqFrame.data(), reqFrame.size()))
	{
		Task::msSleep(100);
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool IRetMotorComm::scan(std::shared_ptr<ISerialDriver> aisgDrv)
{
	std::vector<unsigned char> reqFrame;
	std::vector<unsigned char> reqData;
	unsigned short crc;					/* The crc value */
	unsigned char crc_l, crc_h;			/* The crc bytes */

	reqFrame.clear();
	reqData.clear();

	//Add start flag
	reqFrame.push_back(FLAG_START);

	//create request data vector
	reqData.push_back(BROADCAST_ADDRESS);
	reqData.push_back(XID_COMMAND);
	reqData.push_back(XID_FORMAT_IDENTIFIER);
	reqData.push_back(XID_GROUP_IDENTIFIER);
	reqData.push_back(0x04); //Data length
	reqData.push_back(0x01); //Scan request for all secondary devices in NoAddress state
	reqData.push_back(0x00);
	reqData.push_back(0x03);
	reqData.push_back(0x00);

	//Copy data into request frame
	for (std::vector<unsigned char>::iterator it = reqData.begin(); it != reqData.end(); ++it)
	{
		reqFrame.push_back(*it);
	}

	//calculate crc on data vector
	crc = fcs::fcs16(fcs::INITFCS16, &reqData[0], reqData.size());
	crc ^= 0xffff;

	crc_l = crc & 0xFF;
	crc_h = (crc >> 8) & 0xFF;

	//Copy crc to request frame
	if (crc_l == ESC_ASYNC)
	{
		reqFrame.push_back(ESC_ASYNC);
		reqFrame.push_back(crc_l ^ ESC_COMPL);
	}
	else
	{
		reqFrame.push_back(crc_l);
	}

	if (crc_h == ESC_ASYNC)
	{
		reqFrame.push_back(ESC_ASYNC);
		reqFrame.push_back(crc_h ^ ESC_COMPL);
	}
	else
	{
		reqFrame.push_back(crc_h);
	}

	//Add stop flag
	reqFrame.push_back(FLAG_STOP);

	//_SLEEP(25);

	//Send the frame over serial
	return (aisgDrv->write(reqFrame.data(), reqFrame.size()));
}

//-------------------------------------------------------------------------------------------------------------
IRetMotorComm::FrameType_T IRetMotorComm::getFrameType(unsigned char control)
{
	if (!(control & 0x01))
	{
		return FRAME_TYPE_I;
	}
	else if (!(control & 0x02))
	{
		return FRAME_TYPE_S;
	}
	else
	{
		return FRAME_TYPE_U;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool IRetMotorComm::decode_xid_frame(std::vector<unsigned char> response, std::string & uid,
	std::string & vendorCode, unsigned char& type)
{
	try
	{
		char fieldLen = response[5];

		for (char i = 0; i < fieldLen; )
		{
			char param = response[6 + i];
			char paramLen = response[7 + i];

			switch (param)
			{
			case 1: //UID
				uid = "";
				for (char j = 0; j < paramLen; j++)
				{
					uid.push_back(response[8 + i + j]);
				}
				break;

			case 4: //Device type
				type = response[8 + i];
				break;

			case 6: //Vendor code
				for (char j = 0; j < paramLen; j++)
				{
					vendorCode.push_back(response[8 + i + j]);
				}
				break;
			};

			i += paramLen + 2;
		}
	}
	catch (...)
	{
		//Do not process frame
		return false;
	}

	return true;
}

//=============================================================================================================
// Public functions
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::stateMachineMotor(unsigned char address)
{
	switch (mStatus)
	{
	case DEVICE_INIT:
		switch (mInitSubState)
		{
			//Assign address
		case InitSubStates_T::ASSIGN_ADDRESS:
			mInitEvent = InitEvents_T::NO_INIT_EVT;
			//Try to get exclusive access to send a request
			if (mAccessMutex.try_lock())
			{
				if (assignAddress(address) == true)
				{
					mInitSubState = InitSubStates_T::CONNECT_TO_DEVICE;
				}
				else
				{
					ILoggable::logEventInfo("Motor assign address failed");
					mInitSubState = InitSubStates_T::SETUP_FAILED;
				}
				mAccessMutex.unlock();
			}
			//If mutex is locked, then wait till next execution
			break;

			//Connect to the motor
		case InitSubStates_T::CONNECT_TO_DEVICE:
			if (mInitEvent == InitEvents_T::EVT_ADDRESS_ASSIGNED)
			{
				logDebugNormal("Motor assigned address %d", address);
				mInitEvent = InitEvents_T::NO_INIT_EVT;
				//Try to get exclusive access to send a request
				if (mAccessMutex.try_lock())
				{
					if (connect() == true)
					{
						mInitSubState = InitSubStates_T::WAIT_COMPLETION;
					}
					else
					{
						ILoggable::logEventInfo("Motor connect command failed");
						mInitSubState = InitSubStates_T::SETUP_FAILED;
					}
					mAccessMutex.unlock();
				}
				//If mutex is locked, then wait till next execution
			}
			else if (mInitEvent == InitEvents_T::EVT_INIT_TIMEOUT)
			{
				ILoggable::logEventInfo("Motor assign address timeout");
				mInitEvent = InitEvents_T::NO_INIT_EVT;
				mInitSubState = InitSubStates_T::SETUP_FAILED;
			}
			else
			{
				checkResponseTimeout();
			}
			break;

			//Wait for the Motor to be connected
		case InitSubStates_T::WAIT_COMPLETION:
			if (mInitEvent == InitEvents_T::EVT_CONNECTED)
			{
				logDebugNormal("Motor connected");
				mConnected = true;
				mNr = 0;
				mNs = 0;
				mInitEvent = InitEvents_T::NO_INIT_EVT;
				mInitSubState = InitSubStates_T::SETUP_COMPLETE;
			}
			else if (mInitEvent == InitEvents_T::EVT_INIT_TIMEOUT)
			{
				ILoggable::logEventInfo("Motor connect command timeout");
				mConnected = false;
				mInitEvent = InitEvents_T::NO_INIT_EVT;
				mInitSubState = InitSubStates_T::SETUP_FAILED;
			}
			else
			{
				checkResponseTimeout();
			}
			break;

		case InitSubStates_T::SETUP_FAILED:
			mInitSubState = InitSubStates_T::ASSIGN_ADDRESS;
			mInitEvent = InitEvents_T::NO_INIT_EVT;
			setEvent(NO_EVT);
			setReq(NO_CMD);
			setStatus(DEVICE_FAIL);
			break;

		case InitSubStates_T::SETUP_COMPLETE:
			mInitSubState = InitSubStates_T::ASSIGN_ADDRESS;
			mInitEvent = InitEvents_T::NO_INIT_EVT;
			setEvent(NO_EVT);
			setReq(NO_CMD);
			setStatus(DEVICE_READY);
			alarmsSubscribe();
			break;
		}
		break;

	case DEVICE_READY:
	case DEVICE_FAIL:
		if (mEvent == EVT_RUN)
		{
			setEvent(NO_EVT);
			setStatus(DEVICE_RUN);
		}
		else
		{
			keepLinkAlive();
		}
		break;

	case DEVICE_RUN:
		if (mEvent == EVT_RESPONSE_RECD)
		{
			if (mReq == CMD_RESET)
			{
				setStatus(DEVICE_INIT);
			}
			else
			{
				setStatus(DEVICE_READY);
			}
			setEvent(NO_EVT);
			setReq(NO_CMD);
		}
		else if (mEvent == EVT_TIMEOUT || mEvent == EVT_RESPONSE_FAIL)
		{
			setEvent(NO_EVT);
			setStatus(DEVICE_FAIL);
			setReq(NO_CMD);
		}
		else
		{
			checkResponseTimeout();
		}
		break;

	default:
		mInitSubState = ASSIGN_ADDRESS;
		setInitEvent(NO_INIT_EVT);
		setStatus(DEVICE_INIT);
		setEvent(NO_EVT);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::reInitialize(void)
{
	mNr = 0;
	mNs = 0;
	mStatus = DEVICE_INIT;
	mEvent = MotorEvents_T::NO_EVT;
	mInitSubState = InitSubStates_T::ASSIGN_ADDRESS;
	mInitEvent = InitEvents_T::NO_INIT_EVT;
	mConnected = false;
	mReq = NO_CMD;
	mNumSubunits = 0;

	mReqStartTime = 0;
	mReqFrame.clear();
	mReqData.clear();
	mAlarmStatus.clear();
	mResponseTilt.clear();
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::reset(void)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;
	bool ret = false;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		//Set the current request
		setReq(IRetMotorComm::Req_T::CMD_RESET);

		//Populate request data
		populateElementaryProc(getCommndId(mReq), NULL, 0);

		//Record start time
		recordStartTime();
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		else
		{
			//Wait till either response is received or it times out
			while (mReq != NO_CMD)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mReqCond.wait(lk);
				lk.unlock();
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::getDeviceInfo(std::string& uid, std::string & productNum, std::string & serialNum, std::string & hardwareVersion,
	std::string & softwareVersion, std::string & vendorCode, std::string & deviceType)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;
	bool ret = false;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		//Set the current request
		setReq(Req_T::GET_INFORMATION);

		//Populate request data
		populateElementaryProc(getCommndId(mReq), NULL, 0);

		//Record start time
		recordStartTime();
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		else
		{
			//Wait till either response is received or it times out
			while (mReq != NO_CMD)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mReqCond.wait(lk);
				lk.unlock();
			}

			//If response is received successfully, then return information
			if (mStatus == DEVICE_READY)
			{
				uid = mUid;
				productNum = mProductNumber;
				serialNum = mSerialNumber;
				hardwareVersion = mHardwareVer;
				softwareVersion = mSoftwareVer;
				vendorCode = mVendorCode;
				deviceType = deviceTypeToStr(mType);
			}
			else
			{
				ret = false;
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::getNumSubunits(unsigned & numSubunits)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	//For single ret devices, the number of sub-units is 1
	if (mType == SINGLE_RET)
	{
		numSubunits = 1;
		return true;
	}

	MotorStatus_T status = mStatus;
	bool ret = false;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		//Set the current request
		setReq(Req_T::GET_NUM_ANTENNAE);

		//Populate request data
		populateElementaryProc(getCommndId(mReq), NULL, 0);

		//Record start time
		recordStartTime();
		//Set status to Run
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		else
		{
			//Wait till either response is received or it times out
			while (mReq != NO_CMD)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mReqCond.wait(lk);
				lk.unlock();
			}

			//If response is received successfully, then return information
			if (mStatus == DEVICE_READY)
			{
				numSubunits = mNumSubunits;
			}
			else
			{
				ret = false;
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::getMinTilt(double & minTilt, int antenna)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;
	bool ret = false;
	unsigned char data = 0;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		if ((mType == MULTI_RET && antenna == -1) ||
			(mType == SINGLE_RET && antenna != -1))
		{
			return false;
		}

		if (antenna == -1)
		{
			//Set the current request
			setReq(Req_T::GET_MIN_TILT);
			data = FIELD_CODE_MIN_TILT;

			//Populate request data
			populateElementaryProc(getCommndId(mReq), &data, 1);
		}
		else
		{
			//Set the current request
			setReq(Req_T::GET_ANTENNA_MIN_TILT);
			data = FIELD_CODE_MIN_TILT;

			//Populate request data
			populateElementaryProc(getCommndId(mReq), static_cast<unsigned char>(antenna), &data, 1);
		}

		//Record start time
		recordStartTime();
		//Set status to Run
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		else
		{
			//Wait till either response is received or it times out
			while (mReq != NO_CMD)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mReqCond.wait(lk);
				lk.unlock();
			}

			//If response is received successfully, then return information
			if (mStatus == DEVICE_READY)
			{
				if (antenna == -1)
				{
					if (mMinTilt.find(0) != mMinTilt.end())
					{
						minTilt = mMinTilt[0];
					}
					else
					{
						ret = false;
					}
				}
				else
				{
					if (mMinTilt.find(static_cast<unsigned char>(antenna)) != mMinTilt.end())
					{
						minTilt = mMinTilt[static_cast<unsigned char>(antenna)];
					}
					else
					{
						ret = false;
					}
				}
			}
			else
			{
				ret = false;
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::getMaxTilt(double & maxTilt, int antenna)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;
	bool ret = false;
	unsigned char data = 0;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		if ((mType == MULTI_RET && antenna == -1) ||
			(mType == SINGLE_RET && antenna != -1))
		{
			return false;
		}

		if (antenna == -1)
		{
			//Set the current request
			setReq(Req_T::GET_MAX_TILT);
			data = FIELD_CODE_MAX_TILT;

			//Populate request data
			populateElementaryProc(getCommndId(mReq), &data, 1);
		}
		else
		{
			//Set the current request
			setReq(Req_T::GET_ANTENNA_MAX_TILT);
			data = FIELD_CODE_MAX_TILT;

			//Populate request data
			populateElementaryProc(getCommndId(mReq), static_cast<unsigned char>(antenna), &data, 1);
		}

		//Record start time
		recordStartTime();
		//Set status to Run
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		else
		{
			//Wait till either response is received or it times out
			while (mReq != NO_CMD)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mReqCond.wait(lk);
				lk.unlock();
			}

			//If response is received successfully, then return information
			if (mStatus == DEVICE_READY)
			{
				if (antenna == -1)
				{
					if (mMaxTilt.find(0) != mMaxTilt.end())
					{
						maxTilt = mMaxTilt[0];
					}
					else
					{
						ret = false;
					}
				}
				else
				{
					if (mMaxTilt.find(static_cast<unsigned char>(antenna)) != mMaxTilt.end())
					{
						maxTilt = mMaxTilt[static_cast<unsigned char>(antenna)];
					}
					else
					{
						ret = false;
					}
				}
			}
			else
			{
				ret = false;
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::calibrate(int antenna)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;

	bool ret = false;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		if ((mType == MULTI_RET && antenna == -1) ||
			(mType == SINGLE_RET && antenna != -1))
		{
			return false;
		}

		if (antenna == -1)
		{
			//Set the current request
			setReq(IRetMotorComm::Req_T::CMD_CALIBRATE);

			//Populate request data
			populateElementaryProc(getCommndId(mReq), NULL, 0);
		}
		else
		{
			//Set the current request
			setReq(IRetMotorComm::Req_T::CMD_ANTENNA_CALIBRATE);

			//Populate request data
			populateElementaryProc(getCommndId(mReq), static_cast<unsigned char>(antenna), NULL, 0);
		}

		//Record start time
		recordStartTime();
		//Set status to Run
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		/*else
		{
			//Wait till the calibrate request is started
			while (mStatus != DEVICE_RUN)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mDevStatCond.wait(lk);
				lk.unlock();
			}
		}*/
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::disconnect(void)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;
	bool ret = false;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		//Set the current request
		setReq(Req_T::CMD_DISCONNECT);

		mReqData.clear();

		//Add address and command
		mReqData.push_back(mAddress);
		mReqData.push_back(getCommndId(mReq));

		//Record start time
		recordStartTime();
		//Set status to Run
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		else
		{
			//Wait till either response is received or it times out
			while (mReq != NO_CMD)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mReqCond.wait(lk);
				lk.unlock();
			}

			//If response is received successfully, then reset connected flag
			if (mStatus == DEVICE_READY)
			{
				mConnected = false;
				mNr = 0;
				mNs = 0;
			}
			else
			{
				ret = false;
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::getTilt(double & tilt, int antenna)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;

	bool ret = false;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		if ((mType == MULTI_RET && antenna == -1) ||
			(mType == SINGLE_RET && antenna != -1))
		{
			return false;
		}

		if (antenna == -1)
		{
			//Set the current request
			setReq(IRetMotorComm::Req_T::GET_TILT);

			//Populate request data
			populateElementaryProc(getCommndId(mReq), NULL, 0);
		}
		else
		{
			//Set the current request
			setReq(IRetMotorComm::Req_T::GET_ANTENNA_TILT);

			//Populate request data
			populateElementaryProc(getCommndId(mReq), static_cast<unsigned char>(antenna), NULL, 0);
		}

		//Record start time
		recordStartTime();
		//Set status to Run
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		else
		{
			//Wait till either response is received or it times out
			while (mReq != NO_CMD)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mReqCond.wait(lk);
				lk.unlock();
			}

			//If response is received successfully, then return tilt value
			if (mStatus == DEVICE_READY)
			{
				if (antenna == -1)
				{
					if (mResponseTilt.find(0) != mResponseTilt.end())
					{
						tilt = mResponseTilt[0];
					}
					else
					{
						ret = false;
					}
				}
				else
				{
					if (mResponseTilt.find(static_cast<unsigned char>(antenna)) != mResponseTilt.end())
					{
						tilt = mResponseTilt[static_cast<unsigned char>(antenna)];
					}
					else
					{
						ret = false;
					}
				}
			}
			else
			{
				ret = false;
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::setTilt(double tilt, int antenna)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;

	bool ret = false;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		unsigned char data[2] = { 0 };

		if ((mType == MULTI_RET && antenna == -1) ||
			(mType == SINGLE_RET && antenna != -1))
		{
			return false;
		}

		tilt = tilt * 10;
		unsigned intTilt = static_cast<unsigned>(tilt);
		data[0] = intTilt & 0xFF;
		data[1] = (intTilt & 0xFF00) >> 8;

		if (antenna == -1)
		{
			//Set the current request
			setReq(IRetMotorComm::Req_T::SET_TILT);

			//Populate request data
			populateElementaryProc(getCommndId(mReq), data, 2);
		}
		else
		{
			//Set the current request
			setReq(IRetMotorComm::Req_T::SET_ANTENNA_TILT);

			//Populate request data
			populateElementaryProc(getCommndId(mReq), static_cast<unsigned char>(antenna), data, 2);
		}

		//Record start time
		recordStartTime();
		//Set status to Run
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
unsigned RetMotorComm::status(void)
{
	return mStatus;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::getAlarmStatus(std::string & alarmStatus, int antenna)
{
	std::lock_guard<std::mutex> guard(mAccessMutex);

	MotorStatus_T status = mStatus;

	bool ret = false;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		if ((mType == MULTI_RET && antenna == -1) ||
			(mType == SINGLE_RET && antenna != -1))
		{
			return false;
		}

		if (antenna == -1)
		{
			//Set the current request
			setReq(IRetMotorComm::Req_T::GET_ALARM_STATUS);

			//Populate request data
			populateElementaryProc(getCommndId(mReq), NULL, 0);
		}
		else
		{
			//Set the current request
			setReq(IRetMotorComm::Req_T::GET_ANTENNA_ALARM_STATUS);

			//Populate request data
			populateElementaryProc(getCommndId(mReq), static_cast<unsigned char>(antenna), NULL, 0);
		}

		//Record start time
		recordStartTime();
		//Set status to Run
		setStatus(DEVICE_RUN);;

		//Populate frame and send
		ret = sendRequest();

		//If sending fails, then set status to fail
		if (!ret)
		{
			setStatus(DEVICE_FAIL);
		}
		else
		{
			//Wait till either response is received or it times out
			while (mReq != NO_CMD)
			{
				std::unique_lock<std::mutex> lk(mMutex);
				mReqCond.wait(lk);
				lk.unlock();
			}

			//If response is received successfully, then read alarms
			if (mStatus == DEVICE_READY)
			{
				unsigned char pos = 0;
				if (antenna == -1)
				{
					if (mType == SINGLE_RET)
					{
						pos = 0;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (mType == MULTI_RET)
					{
						pos = static_cast<unsigned char>(antenna);
					}
					else
					{
						return false;
					}
				}

				alarmStatus = "";
				if (mAlarmStatus.find(pos) != mAlarmStatus.end())
				{
					for (std::vector<unsigned char>::iterator it = mAlarmStatus[pos].begin(); it != mAlarmStatus[pos].end(); ++it)
					{
						if (alarmStatus.size() != 0)
						{
							alarmStatus.append(", ");
						}
						if (RetMotorComm::mAlarmCodeToString.find((*it)) != RetMotorComm::mAlarmCodeToString.end())
						{
							alarmStatus.append(RetMotorComm::mAlarmCodeToString.find(*it)->second.c_str());
						}
						else
						{
							int code = static_cast<int>(*it);
							alarmStatus.append("Unknown alarm code - ");
							alarmStatus.append(std::to_string(code));
						}
					}
				}
			}
			else
			{
				ret = false;
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::processResponse(std::vector<unsigned char> response)
{
	FrameType_T frameType = IRetMotorComm::getFrameType(response[IRetMotorComm::RX_FRAME_CONTROL_POS]);

	switch (frameType)
	{
	case FRAME_TYPE_I:
		i_frame_process(response);
		break;

	case FRAME_TYPE_S:
		s_frame_process(response);
		break;

	case FRAME_TYPE_U:
		u_frame_process(response);
		break;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::isThisMotor(std::string uid, std::string vendorCode, unsigned char deviceType)
{
	if (uid == mUid && vendorCode == mVendorCode && deviceType == mType)
	{
		return true;
	}

	return false;
}

//=============================================================================================================
// Protected functions
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::setStatus(MotorStatus_T status)
{
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mStatus = status;
	}
	//mDevStatCond.notify_all();
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::setEvent(MotorEvents_T evt)
{
	std::lock_guard<std::mutex> lock(mMutex);
	mEvent = evt;
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::setInitEvent(InitEvents_T evt)
{
	std::lock_guard<std::mutex> lock(mMutex);
	mInitEvent = evt;
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::setReq(Req_T req)
{
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mReq = req;
	}
	mReqCond.notify_all();
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::checkResponseTimeout(void)
{
	unsigned long currentTime;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	currentTime = (tv.tv_sec * 1000) + (tv.tv_usec/1000);

	if ((currentTime - mReqStartTime) > getCommandTimeout(mReq))
	{
		if (mStatus == DEVICE_RUN)
		{
			setEvent(EVT_TIMEOUT);
		}
		else if (mStatus == DEVICE_INIT)
		{
			setInitEvent(EVT_INIT_TIMEOUT);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::keepLinkAlive(void)
{
	unsigned long currentTime;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	currentTime = (tv.tv_sec * 1000) + (tv.tv_usec/1000);

	if ((currentTime - mReqStartTime) > KEEP_ALIVE_TIMEOUT)
	{
		//send a request to keep link alive
		(void)sendKeepAlive();
	}
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::assignAddress(unsigned char address)
{
	//Set the current request
	setReq(Req_T::XID_ADDRESS);
	mAddress = address;

	mReqData.clear();

	//Add XID header
	mReqData.push_back(BROADCAST_ADDRESS);
	mReqData.push_back(XID_COMMAND);
	mReqData.push_back(XID_FORMAT_IDENTIFIER);
	mReqData.push_back(XID_GROUP_IDENTIFIER);
	mReqData.push_back(0x00);

	//Add UID
	if (mUid.size() > 0)
	{
		mReqData.push_back(XID_PI_UID);
		mReqData.push_back(static_cast<unsigned char>(mUid.size()));
		for (std::string::iterator it = mUid.begin(); it != mUid.end(); ++it)
		{
			mReqData.push_back(*it);
		}
	}

	//Add address
	mReqData.push_back(XID_PI_ADDRESS);
	mReqData.push_back(XID_PL_ADDRESS);
	mReqData.push_back(address);

	//Add device type
	mReqData.push_back(XID_PI_DEVICE_TYPE);
	mReqData.push_back(XID_PL_DEVICE_TYPE);
	mReqData.push_back(static_cast<unsigned char>(mType));

	//Add vendor code
	mReqData.push_back(XID_PI_VENDOR_CODE);
	mReqData.push_back(XID_PL_VENDOR_CODE);
	mReqData.push_back(mVendorCode[0]);
	mReqData.push_back(mVendorCode[1]);

	//Update request data length
	mReqData[XID_GROUP_LEN_POS] = (static_cast<unsigned char>(mReqData.size())) - 5;

	//Record start time
	recordStartTime();

	return sendRequest();
}


//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::connect(void)
{
	//Set the current request
	setReq(Req_T::CMD_CONNECT);

	mReqData.clear();

	//Add address and command
	mReqData.push_back(mAddress);
	mReqData.push_back(getCommndId(mReq));

	//Record start time
	recordStartTime();

	//Populate frame and send
	return sendRequest();
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::alarmsSubscribe(void)
{
	MotorStatus_T status = mStatus;

	//If a command is in progress or the device is not connected, then return error
	if (status == DEVICE_READY || status == DEVICE_FAIL)
	{
		//Set the current request
		setReq(IRetMotorComm::Req_T::ALARM_SUBSCRIBE);

		//Populate request data
		populateElementaryProc(getCommndId(mReq), NULL, 0);

		//Record start time
		recordStartTime();

		//Populate frame and send
		if (sendRequest())
		{
			setStatus(DEVICE_RUN);
		}
		else
		{
			setStatus(DEVICE_FAIL);
		}
	}
	return false;
}


//=============================================================================================================
// Private functions
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::populateElementaryProc(unsigned char command_id, unsigned char * data, unsigned length)
{
	unsigned char control = 0x00;

	control |= Iframe_MASK;
	control |= PF_MASK;
	control |= (mNs << 1);
	control |= (mNr << 5);

	//Populate address, control byte, command ID, data length, data bytes
	mReqData.clear();
	mReqData.push_back(mAddress);
	mReqData.push_back(control);
	mReqData.push_back(command_id);
	mReqData.push_back(length & 0xFF);
	mReqData.push_back((length & 0xFF00) >> 8);

	if (length > 0 && data != NULL)
	{
		for (unsigned i = 0; i < length; i++)
		{
			mReqData.push_back(data[i]);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::populateElementaryProc(unsigned char command_id, unsigned char antenna, unsigned char * data, unsigned length)
{
	unsigned char control = 0x00;

	control |= Iframe_MASK;
	control |= PF_MASK;
	control |= (mNs << 1);
	control |= (mNr << 5);

	//Populate address, control byte, command ID, data length, data bytes
	mReqData.clear();
	mReqData.push_back(mAddress);
	mReqData.push_back(control);
	mReqData.push_back(command_id);
	mReqData.push_back((length + 1) & 0xFF); //Increment length by 1 to include the subunit(antenna number) information
	mReqData.push_back(((length + 1) & 0xFF00) >> 8);
	mReqData.push_back(antenna);

	if (length > 0 && data != NULL)
	{
		for (unsigned i = 0; i < length; i++)
		{
			mReqData.push_back(data[i]);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::sendRequest(void)
{
	unsigned char result;				/* The send byte */
	short crc;					/* The crc value */
	unsigned char crc_l, crc_h;			/* The crc bytes */
	std::vector<unsigned char>::iterator it;  /*Declaring iterator to a vector*/

	//Start populating the frame to be sent
	mReqFrame.clear();
	//Add start flag
	mReqFrame.push_back(FLAG_START);

	//Add request data
	for (it = mReqData.begin(); it != mReqData.end(); ++it)
	{
		if (checkByte(result, *it))
		{
			mReqFrame.push_back(ESC_ASYNC);
			mReqFrame.push_back(result);
		}
		else
		{
			mReqFrame.push_back(result);
		}
	}

	//Calculate and append crc
	crc = fcs::fcs16(fcs::INITFCS16, &mReqData[0], mReqData.size());
	crc ^= 0xffff;

	crc_l = crc & 0xFF;
	crc_h = (crc >> 8) & 0xFF;

	// crc high, low
	if (checkByte(result, crc_l))
	{
		mReqFrame.push_back(ESC_ASYNC);
		mReqFrame.push_back(result);
	}
	else
	{
		mReqFrame.push_back(result);
	}

	if (checkByte(result, crc_h))
	{
		mReqFrame.push_back(ESC_ASYNC);
		mReqFrame.push_back(result);
	}
	else
	{
		mReqFrame.push_back(result);
	}

	//Add stop flag
	mReqFrame.push_back(FLAG_STOP);

	//Send the frame over serial
	if (mAisgDrv->write(mReqFrame.data(), mReqFrame.size()))
	{
		//Update sequence number
		if (getFrameType(mReqFrame[IRetMotorComm::TX_FRAME_CONTROL_POS]) == FRAME_TYPE_I)
		{
			mNs = mNs + 1;
			mNs = mNs % 8;
		}
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::checkByte(unsigned char & result, unsigned char input)
{
	bool flag_status;

	switch (input)
	{
	case FLAG_START:
	case ESC_ASYNC:
		/* Exlusive_or the 7D, 7E with 0x20   */
		result = input ^ (unsigned char)ESC_COMPL;
		/* Set the flag */
		flag_status = true;
		break;

	default:
		/* The normal byte */
		result = input;
		/* Set the flag */
		flag_status = false;
		break;
	}

	return flag_status;
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::i_frame_process(std::vector<unsigned char> response)
{
	unsigned char Vr, Vs;

	unsigned char control = response[IRetMotorComm::RX_FRAME_CONTROL_POS];
	Vs = (control >> 1) & 0x07;
	Vr = (control >> 5) & 0x07;

	//Transmit sequence number of master (mNs) should match the
	//expected receive sequence number of slave (Vr)
	if (mNs != Vr)
	{
		//sequence number mismatch
		//Slave has lost certain frames
	}

	//Transmit sequence number of slave (Vs) should match the
	//expected receive sequence number of master 9mNr)
	if (mNr != Vs)
	{
		//sequence number mismatch
		//master has lost certain frames
	}

	//Increment the next expected receive sequence number
	mNr = Vs;
	mNr = mNr + 1;
	mNr = mNr % 8;

	if (response.size() > IRetMotorComm::RX_FRAME_COMMAND_POS)
	{
		unsigned char command = response[IRetMotorComm::RX_FRAME_COMMAND_POS];
		Req_T req;

		//Check if response is received for the active request
		if (mStatus == DEVICE_RUN && command == getCommndId(mReq))
		{
			req = mReq;
		}
		//Check if response is an alarm indication
		else if (mStatus == DEVICE_READY &&
			(command == COMMAND_ID_ALARM_INDICATION || command == COMMAND_ID_ANTENNA_ALARM_INDICATION))
		{
			req = getRequestFromCommandId(command);
		}
		else
		{
			ILoggable::logEventInfo("I frame received - Response ignored\n");
			//Skip processing the response
			return;
		}

		AisgCommand::respCallback cb;

		//Call the response handler
		cb = getResponseCallback(req);
		if (cb != NULL)
		{
			cb(response);
		}
	}
	else
	{
		//Do not process frame as it is invalid
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::s_frame_process(std::vector<unsigned char> response)
{
	unsigned char control = 0x00;

	//For Set tilt and calibrate commands, send another S frame after a delay
	if (mReq == CMD_CALIBRATE || mReq == CMD_ANTENNA_CALIBRATE ||
		mReq == SET_TILT || mReq == SET_ANTENNA_TILT)
	{
		Task::msSleep(200);
	}

	control |= Sframe_MASK;
	control |= RR_MASK;
	control |= PF_MASK;
	control |= (mNr << 5);

	//Populate address, control byte
	mReqData.clear();
	mReqData.push_back(mAddress);
	mReqData.push_back(control);

	(void)sendRequest();
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::u_frame_process(std::vector<unsigned char> response)
{
	try
	{
		unsigned char type;

		//If U frame contains UID or vendor code or device type, then copy values in member variables
		switch (mReq)
		{
		case XID_ADDRESS:
			if ((response[1] == mAddress) &&
				(response[2] == IRetMotorComm::XID_RESPONSE) &&
				(response[3] == IRetMotorComm::XID_FORMAT_IDENTIFIER) &&
				(response[4] == IRetMotorComm::XID_GROUP_IDENTIFIER))
			{
				(void)IRetMotorComm::decode_xid_frame(response, mUid, mVendorCode, type);
				mType = static_cast<IRetMotorComm::RetType_T>(type);
				setInitEvent(EVT_ADDRESS_ASSIGNED);
			}
			break;

		case CMD_CONNECT:
			if (response[2] == IRetMotorComm::UA_RESPONSE)
			{
				setInitEvent(EVT_CONNECTED);
			}
			break;

		case CMD_DISCONNECT:
			if (response[2] == IRetMotorComm::UA_RESPONSE)
			{
				setEvent(EVT_RESPONSE_RECD);
			}
			break;

		default:
			break;
		}
	}
	catch (...)
	{
		//Do not process frame as it is invalid
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::recordStartTime(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	mReqStartTime = (tv.tv_sec * 1000) + (tv.tv_usec/1000);
}

//-------------------------------------------------------------------------------------------------------------
unsigned char RetMotorComm::getCommndId(Req_T command)
{
	if (mCommandMap.find(command) != mCommandMap.end())
	{
		return mCommandMap[command]->getCommndId();
	}
	else
	{
		return 0x00;
	}
}

//-------------------------------------------------------------------------------------------------------------
unsigned long RetMotorComm::getCommandTimeout(Req_T command)
{
	if (mCommandMap.find(command) != mCommandMap.end())
	{
		return mCommandMap[command]->getCommandTimeout();
	}
	else
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
AisgCommand::respCallback RetMotorComm::getResponseCallback(Req_T command)
{
	if (mCommandMap.find(command) != mCommandMap.end())
	{
		return mCommandMap[command]->getResponseCallback();
	}
	else
	{
		return NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------
IRetMotorComm::Req_T RetMotorComm::getRequestFromCommandId(unsigned char commandId)
{
	Req_T req = NO_CMD;
	for (std::map<Req_T, std::unique_ptr<AisgCommand>>::iterator it = mCommandMap.begin(); it != mCommandMap.end(); ++it)
	{
		if (it->second->getCommndId() == commandId)
		{
			req = it->first;
			break;
		}
	}

	return req;
}

//-------------------------------------------------------------------------------------------------------------
bool RetMotorComm::sendKeepAlive(void)
{
	if (mAccessMutex.try_lock())
	{
		bool ret = alarmsSubscribe();
		mAccessMutex.unlock();

		return ret;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_no_action(std::vector<unsigned char> response)
{
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_getInformation(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS] == 0)
		{
			unsigned fieldLen = response[IRetMotorComm::RX_FRAME_LEN_POS] |
				(response[IRetMotorComm::RX_FRAME_LEN_POS + 1] << 8);

			mProductNumber = "";
			mSerialNumber = "";
			mHardwareVer = "";
			mSoftwareVer = "";

			unsigned char param = 1;
			for (unsigned i = 0; i < fieldLen; )
			{
				unsigned char paramLen = response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS + i];

				for (unsigned char j = 0; j < paramLen; j++)
				{
					switch (param)
					{
					case 1: //Product number
						mProductNumber.push_back(response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS + 1 + i + j]);
						break;

					case 2: //Serial number
						mSerialNumber.push_back(response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS + 1 + i + j]);
						break;

					case 3: //Hardware version
						mHardwareVer.push_back(response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS + 1 + i + j]);
						break;

					case 4: //Software version
						mSoftwareVer.push_back(response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS + 1 + i + j]);
						break;
					};
				}

				i += paramLen + 1;
				param++;
			}
			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_getTilt(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS] == 0)
		{
			mResponseTilt[0] = (static_cast<short>(response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS]) |
				(static_cast<short>(response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS + 1]) << 8));

			mResponseTilt[0] = (mResponseTilt[0] / 10);

			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}

		return;
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}

	return;
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_getNumAntennae(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS] == 0)
		{
			mNumSubunits = response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS];
			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_getAlarmIndication(std::vector<unsigned char> response)
{
	try
	{
		unsigned fieldLen = response[IRetMotorComm::RX_FRAME_LEN_POS] |
			(response[IRetMotorComm::RX_FRAME_LEN_POS + 1] << 8);

		for (unsigned i = 0; i < fieldLen; )
		{
			unsigned char code;
			unsigned char state;

			//Get the alarm code and the alarm state
			code = response[IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS + i];
			state = response[IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS + i + 1];

			std::vector<unsigned char>::iterator it = std::find(mAlarmStatus[0].begin(), mAlarmStatus[0].end(), code);
			//Check if alarm code is present in the vector
			if (it != mAlarmStatus[0].end())
			{
				//If it is present and the alarm state is cleared, then remove it from the vector
				if (!state)
				{
					mAlarmStatus[0].erase(it);
				}
			}
			else
			{
				//If it is not present and the alarm state is raised, then add it to the vector
				if (state)
				{
					mAlarmStatus[0].push_back(code);
				}
			}

			i += 2;
		}
	}
	catch (...)
	{
		//Do not process response
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_getAlarmStatus(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS] == 0)
		{
			unsigned fieldLen = response[IRetMotorComm::RX_FRAME_LEN_POS] |
				(response[IRetMotorComm::RX_FRAME_LEN_POS + 1] << 8);

			mAlarmStatus[0].clear();
			for (unsigned i = 0; i < (fieldLen - 1); i++)
			{
				//Add alarm codes to the vector
				mAlarmStatus[0].push_back((response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS + i]));
			}

			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_generic(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS] == 0)
		{
			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_antennaGetTilt(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_MULTI_RET_RESP_CODE_POS] == 0)
		{
			unsigned char antenna = response[IRetMotorComm::RX_FRAME_MULTI_RET_ANTENNA_NUM_POS];
			mResponseTilt[antenna] =
				(static_cast<short>(response[IRetMotorComm::RX_FRAME_MULTI_RET_DATA_START_POS]) |
				(static_cast<short>(response[IRetMotorComm::RX_FRAME_MULTI_RET_DATA_START_POS + 1]) << 8));

			mResponseTilt[antenna] = mResponseTilt[antenna] / 10;

			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_antennaGetAlarmStatus(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_MULTI_RET_RESP_CODE_POS] == 0)
		{
			unsigned fieldLen = response[IRetMotorComm::RX_FRAME_LEN_POS] |
				(response[IRetMotorComm::RX_FRAME_LEN_POS + 1] << 8);

			unsigned char antenna = response[IRetMotorComm::RX_FRAME_MULTI_RET_ANTENNA_NUM_POS];
			mAlarmStatus[antenna].clear();
			for (unsigned i = 0; i < (fieldLen - 2); i++)
			{
				//Add alarm codes to the vector
				mAlarmStatus[antenna].push_back((response[IRetMotorComm::RX_FRAME_MULTI_RET_DATA_START_POS + i]));
			}

			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_antennaGeneric(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_MULTI_RET_RESP_CODE_POS] == 0)
		{
			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_antennaGetAlarmIndication(std::vector<unsigned char> response)
{
	try
	{
		unsigned fieldLen = response[IRetMotorComm::RX_FRAME_LEN_POS] |
			(response[IRetMotorComm::RX_FRAME_LEN_POS + 1] << 8);

		unsigned char antenna = response[IRetMotorComm::RX_FRAME_MULTI_RET_ANTENNA_NUM_POS];

		for (unsigned i = 0; i < (fieldLen - 1); )
		{
			unsigned char code;
			unsigned char state;

			//Get the alarm code and the alarm state
			code = response[IRetMotorComm::RX_FRAME_MULTI_RET_RESP_CODE_POS + i];
			state = response[IRetMotorComm::RX_FRAME_MULTI_RET_RESP_CODE_POS + i + 1];

			std::vector<unsigned char>::iterator it = std::find(mAlarmStatus[antenna].begin(), mAlarmStatus[antenna].end(), code);
			//Check if alarm code is present in the vector
			if (it != mAlarmStatus[antenna].end())
			{
				//If it is present and the alarm state is cleared, then remove it from the vector
				if (!state)
				{
					mAlarmStatus[antenna].erase(it);
				}
			}
			else
			{
				//If it is not present and the alarm state is raised, then add it to the vector
				if (state)
				{
					mAlarmStatus[antenna].push_back(code);
				}
			}

			i += 2;
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_antennaGetDeviceData(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_MULTI_RET_RESP_CODE_POS] == 0)
		{
			unsigned char antenna = response[IRetMotorComm::RX_FRAME_MULTI_RET_ANTENNA_NUM_POS];
			double tilt = (static_cast<short>(response[IRetMotorComm::RX_FRAME_MULTI_RET_DATA_START_POS]) |
				(static_cast<short>(response[IRetMotorComm::RX_FRAME_MULTI_RET_DATA_START_POS + 1]) << 8));

			tilt = (tilt / 10);

			if (mReq == GET_ANTENNA_MIN_TILT)
			{
				mMinTilt[antenna] = tilt;
			}
			else if (mReq == GET_ANTENNA_MAX_TILT)
			{
				mMaxTilt[antenna] = tilt;
			}

			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}

//-------------------------------------------------------------------------------------------------------------
void RetMotorComm::cb_getDeviceData(std::vector<unsigned char> response)
{
	try
	{
		if (response[IRetMotorComm::RX_FRAME_SINGLE_RET_RESP_CODE_POS] == 0)
		{
			double tilt = (static_cast<short>(response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS]) |
				(static_cast<short>(response[IRetMotorComm::RX_FRAME_SINGLE_RET_DATA_START_POS + 1]) << 8));

			tilt = (tilt / 10);

			if (mReq == GET_MIN_TILT)
			{
				mMinTilt[0] = tilt;
			}
			else if (mReq == GET_MAX_TILT)
			{
				mMaxTilt[0] = tilt;
			}

			setEvent(EVT_RESPONSE_RECD);
		}
		else
		{
			setEvent(EVT_RESPONSE_FAIL);
		}
	}
	catch (...)
	{
		//Do not process response
		setEvent(EVT_RESPONSE_FAIL);
	}
}
