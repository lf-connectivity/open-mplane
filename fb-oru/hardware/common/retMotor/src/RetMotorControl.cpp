/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ret MotorControl.cpp
 * \brief     Motor control implementation
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string>
#include <sys/time.h>

#include "fcs.h"
#include "RetMotorControl.h"
#include "RetMotorComm.h"
#include "SerialData.h"
#include "ILoggable.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned int Mplane::RetMotorControl::MAX_RX_BUFF_SIZE(1024);
const std::string Mplane::RetMotorControl::AISG_DEV_PATH("/dev/ttyS1");

//=============================================================================================================
// Constructor and Destructor
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
Mplane::RetMotorControl::RetMotorControl():
		Loggable("RetMotorControl", "RetMotor")
{
	mConnected = false;
	mStatus = MASTER_INIT;
	mResponseState = WAITING_FOR_START_FLAG;
	mResponseFrame.clear();
	mFormattedResponseFrame.clear();
	mScanStartTime = 0;

	mAisgDrv = AisgSerialDriver::getInstance(AISG_DEV_PATH, 9600);

	// Attach to Aisg instance
	std::dynamic_pointer_cast<Subject<ISerialDataReceived>>(mAisgDrv)->attach(*this);
}

//-------------------------------------------------------------------------------------------------------------
Mplane::RetMotorControl::~RetMotorControl()
{
	//Disconnect and clear devices
	disconnect();
}

//=============================================================================================================
// Static functions
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
const char * Mplane::IRetMotorControl::statusToStr(MasterStatus_T status)
{
	switch (status)
	{
	case MASTER_INIT:
		return "INIT";

	case MASTER_CONN:
		return "CONNECTED";

	case MASTER_SCAN:
		return "SCANNING";

	case MASTER_READY:
		return "READY";

	case MASTER_ERROR:
		return "ERROR";
	}

	return "UNKNOWN";
}

//=============================================================================================================
// Public functions
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::reset(void)
{
	//Only execute request if connected
	if (mConnected == true &&
		(mStatus == MASTER_CONN || mStatus == MASTER_READY || mStatus == MASTER_ERROR))
	{
		//Reset all the devices on the bus by broadcasting the request
		if (IRetMotorComm::resetAll(mAisgDrv))
		{
			//Reset the device list and the response vectors
			execute(RESET_REQ);
			setStatus(MASTER_CONN);
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::reset(unsigned char address)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		//Reset the individual motor
		if (mMotorDevices[address - 1]->reset())
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::connect(void)
{
	if (mAisgDrv->isOpen())
	{
		//Set status to connected
		mConnected = true;
		setStatus(MASTER_CONN);
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::isConnected(void)
{
	return (mConnected);
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::disconnect(void)
{
	//Set status back to Init
	executeDisconnect();
	setStatus(MASTER_INIT);
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::getMasterInfo(std::string& serialNum, std::string& softwareVersion)
{
	double ver = 1.1;//SOFTWARE_VERSION;

	softwareVersion = std::to_string(ver).c_str();
	serialNum = "";

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::scan(void)
{
	//Start the scan only if in connected state
	if (mConnected == true)
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		mScanStartTime = (tv.tv_sec * 1000) + (tv.tv_usec/1000);
		setStatus(MASTER_SCAN);
		if (IRetMotorComm::scan(mAisgDrv))
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------------------
int Mplane::RetMotorControl::getNumDevices(void)
{
	return mMotorDevices.size();
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::getDeviceInfo(unsigned char address, std::string& uid, std::string & productNum, std::string & serialNum,
	std::string & hardwareVersion, std::string & softwareVersion, std::string & vendorCode, std::string & deviceType)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		if (mMotorDevices[address - 1]->getDeviceInfo(uid, productNum, serialNum, hardwareVersion, softwareVersion, vendorCode, deviceType))
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::getNumSubunits(unsigned char address, unsigned & numSubUnits)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		if (mMotorDevices[address - 1]->getNumSubunits(numSubUnits))
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::getMinTilt(unsigned char address, double & minTilt, int antenna)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		if (mMotorDevices[address - 1]->getMinTilt(minTilt, antenna))
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::getMaxTilt(unsigned char address, double & maxTilt, int antenna)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		if (mMotorDevices[address - 1]->getMaxTilt(maxTilt, antenna))
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::calibrate(unsigned char address, int antenna)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		if (mMotorDevices[address - 1]->calibrate(antenna))
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::getTilt(unsigned char address, double & tilt, int antenna)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		if (mMotorDevices[address - 1]->getTilt(tilt, antenna))
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::setTilt(unsigned char address, double tilt, int antenna)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		if (mMotorDevices[address - 1]->setTilt(tilt, antenna))
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::RetMotorControl::status(void)
{
	return IRetMotorControl::statusToStr(mStatus);
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::RetMotorControl::status(unsigned char address)
{
	std::string statusStr = "UNKNOWN";
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		//Get the motor status
		unsigned status = mMotorDevices[address - 1]->status();
		//Convert status to string
		statusStr = IRetMotorComm::statusToStr(static_cast<IRetMotorComm::MotorStatus_T>(status));
	}

	return statusStr;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::getAlarmStatus(unsigned char address, std::string & alarmStatus, int antenna)
{
	unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

	//Check if connected and address is valid
	if (mConnected == true && mStatus == MASTER_READY &&
		numDevices != 0 && address != 0 && (address - 1) <= numDevices)
	{
		return (mMotorDevices[address - 1]->getAlarmStatus(alarmStatus, antenna));
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::timerUpdate(void)
{
	execute(TIMER_UPDATE);
}

//=============================================================================================================
// Protected functions
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::update(ISerialDataReceived& subject)
{
	execute(RX_DATA);
}

//-------------------------------------------------------------------------------------------------------------
const char* Mplane::RetMotorControl::name() const
{
	return "RetMotorControl";
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::execute(ExecuteEvents_T evt)
{
	//Lock with mutex so that it prevents parallel execution
	Mutex::Lock lock(mExeMutex);
	switch (evt)
	{
	case TIMER_UPDATE:
		//Check for timeouts and execute individual motor state machine
		performRoutineTask();
		break;

	case RESET_REQ:
		//Clear the motor devices
		removeDevices();
		//Clear Response buffer and flag
		mResponseState = WAITING_FOR_START_FLAG;
		mResponseFrame.clear();
		mFormattedResponseFrame.clear();
		break;

	case RX_DATA:
		//Process incoming data on periodic calls
		receiveData();
		break;
	}
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::performRoutineTask(void)
{
	if (mConnected)
	{
		//Check if scan has timed out
		if (mStatus == MASTER_SCAN)
		{
			checkScanTimeout();
		}

		//Run each motor state machine
		for (std::vector<IRetMotorComm*>::iterator it = mMotorDevices.begin(); it != mMotorDevices.end(); ++it)
		{
			if (*it != nullptr)
			{
				unsigned char address = static_cast<unsigned char>(it - mMotorDevices.begin() + 1);
				(*it)->stateMachineMotor(address);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::receiveData(void)
{
	if (mConnected)
	{
		std::vector<unsigned char> buffer;

		//Get the serial data
		SerialData data = mAisgDrv->getSerialData();

		buffer = data.getData();

		//Process the received data
		processRxData((char*)buffer.data(), buffer.size());
	}
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::setStatus(MasterStatus_T status)
{
	Mutex::Lock lock(mMutex);
	mStatus = status;
}

//=============================================================================================================
// Private functions
//=============================================================================================================
//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::processRxData(char* data, unsigned long length)
{
	for (unsigned long index = 0; index < length; index++)
	{
		switch (mResponseState)
		{
		//Discard any data till the start flag is received
		case WAITING_FOR_START_FLAG:
			if (data[index] == IRetMotorComm::FLAG_START)
			{
				mResponseFrame.clear();
				mFormattedResponseFrame.clear();
				mResponseFrame.push_back(data[index]);
				mResponseState = RECEIVING_DATA;
			}
			break;

		case RECEIVING_DATA:
			//when stop flag is received, process the received frame
			if (data[index] == IRetMotorComm::FLAG_STOP)
			{
				//If we receive stop flag immediately after start flag, then ignore the stop flag and keep collecting data
				//This situation may arise if the code is out of sync and considers the stop flag of one of the frame as the start flag
				//In this case, when it receives the start flag for the next frame, it will be ignored and the frame data will be collected
				if (mResponseFrame.size() > 1)
				{
					mResponseFrame.push_back(data[index]);

					//If formatted response has correct CRC, then proceed
					if (formatRxData())
					{
						//Check if response contains atleast the address and the contol byte
						if (mFormattedResponseFrame.size() > IRetMotorComm::RX_FRAME_CONTROL_POS)
						{
							unsigned char address = mFormattedResponseFrame[IRetMotorComm::RX_FRAME_ADDRESS_POS];

							//If master is scanning and U frame is received, then check if it is the scan response
							if (mStatus == MASTER_SCAN &&
								IRetMotorComm::getFrameType(mFormattedResponseFrame[IRetMotorComm::RX_FRAME_CONTROL_POS]) ==
										IRetMotorComm::FRAME_TYPE_U &&
								address == 0x00)
							{
								(void)checkScanResponse();
							}
							//Else check if it is a response from one of the existing devices
							else
							{
								unsigned char numDevices = static_cast<unsigned char>(mMotorDevices.size());

								//If motor is found in the device list, then process the response, else discard it
								if (numDevices != 0 && address != 0 && (address - 1) <= numDevices)
								{
									mMotorDevices[address - 1]->processResponse(mFormattedResponseFrame);
								}
							}
						}
					}

					mResponseState = WAITING_FOR_START_FLAG;
					mResponseFrame.clear();
					mFormattedResponseFrame.clear();
				}
			}
			else
			{
				mResponseFrame.push_back(data[index]);
			}
			break;

		default:
			mResponseState = WAITING_FOR_START_FLAG;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::formatRxData(void)
{
	//unsigned short crc;				/* The crc values. */
	bool fcs_status = false;
	std::vector<unsigned char>::iterator it;

	//Check for escape sequence
	for (it = mResponseFrame.begin(); it != mResponseFrame.end(); ++it)
	{
		if (*it == IRetMotorComm::ESC_ASYNC)
		{
			++it;
			if (it == mResponseFrame.end())
			{
				break;
			}
			mFormattedResponseFrame.push_back(*it ^ IRetMotorComm::ESC_COMPL);
		}
		else
		{
			mFormattedResponseFrame.push_back(*it);
		}
	}

	if (mFormattedResponseFrame.size() > 2)
	{
		//Calculate and verify CRC in the received frame
		unsigned short crc = fcs::fcs16(fcs::INITFCS16, &mFormattedResponseFrame[1], mFormattedResponseFrame.size() - 2);
		if (crc == fcs::GOODFCS16)
		{
			fcs_status = true;
		}
		else
		{
			ILoggable::logEventWarning("RetMotorControl - Frame received with invalid CRC");
		}
	}

	return fcs_status;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RetMotorControl::checkScanResponse(void)
{
	std::string uid = "";
	std::string vendorCode = "";

	bool ret = false;

	if ((mFormattedResponseFrame.size() > 4) &&
		(mFormattedResponseFrame[2] == IRetMotorComm::XID_RESPONSE) &&
		(mFormattedResponseFrame[3] == IRetMotorComm::XID_FORMAT_IDENTIFIER) &&
		(mFormattedResponseFrame[4] == IRetMotorComm::XID_GROUP_IDENTIFIER))
	{
		unsigned char type = 0xff;

		(void)IRetMotorComm::decode_xid_frame(mFormattedResponseFrame, uid, vendorCode, type);

		if (uid != "" && vendorCode != "" && type != 0xFF)
		{
			ret = true;

			//Check if a device exists with the received UID, vendor code and device type
			std::vector<IRetMotorComm*>::iterator it;

			for (it = mMotorDevices.begin(); it != mMotorDevices.end(); ++it)
			{
				if ((*it)->isThisMotor(uid, vendorCode, type))
				{
					break;
				}
			}

			//If it does not exist, then create a new device
			if (it == mMotorDevices.end())
			{
				std::string motorType = IRetMotorComm::deviceTypeToStr((IRetMotorComm::RetType_T)type);
				logDebugNormal("Motor found %s %s %s", uid.c_str(), vendorCode.c_str(),motorType.c_str());
				mMotorDevices.push_back(new RetMotorComm(uid, vendorCode, type, mAisgDrv));
			}
			else
			{
				//set the device state to init, so that it gets assigned an address again
				(*it)->reInitialize();
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::checkScanTimeout(void)
{
	//If master is scanning
	if (mStatus == MASTER_SCAN)
	{
		unsigned long currentTime;
		struct timeval tv;
		gettimeofday(&tv, NULL);
		currentTime = (tv.tv_sec * 1000) + (tv.tv_usec/1000);

		//If scan times out, then check for number of devices detected
		if ((currentTime - mScanStartTime) > IRetMotorComm::TIME_SCAN)
		{
			//If atleast 1 device is detected, then master is ready
			if (mMotorDevices.size() > 0)
			{
				setStatus(MASTER_READY);
			}
			//If no devices on the bus, then set master status to error
			else
			{
				setStatus(MASTER_ERROR);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::removeDevices(void)
{
	for (std::vector<IRetMotorComm*>::iterator it = mMotorDevices.begin(); it != mMotorDevices.end(); ++it)
	{
		delete *it;
	}
	mMotorDevices.clear();
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::disconnectWithErr(void)
{
	executeDisconnect();
	setStatus(MASTER_ERROR);
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RetMotorControl::executeDisconnect(void)
{
	if (mConnected)
	{
		execute(RESET_REQ);
		mConnected = false;
	}
}
