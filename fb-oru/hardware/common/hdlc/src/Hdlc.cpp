/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Hdlc.cpp
 * \brief     Class to communicate using HDLC data link layer
 *
 *
 * \details   Class to communicate using HDLC data link layer
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Hdlc.h"
#include <string.h>
#include <sstream>
#include <iomanip>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned char Hdlc::FLAG_START(0x7E);		/* Starts each frame */
const unsigned char Hdlc::FLAG_STOP(0x7E); 		/* Ends each frame */
const unsigned char Hdlc::ESC_ASYNC(0x7D); 		/* Escapes special chars (0x7d, 0x7e, 0x7f) */
const unsigned char Hdlc::ESC_COMPL(0x20); 		/* XORed with special chars in data */

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Hdlc::Hdlc(std::shared_ptr<IBus> phy):
		TaskEvent(Task::PRIORITY_HIGH, Task::MEDIUM_STACK,
		 "HDLC", "HDLC_Task"),
		 mPhy(phy),
		 mReqInfo(),
		 mMutex(),
		 mRespStartTime(),
		 mWrongCrcCounter(0),
		 mNoStopFlagCounter(0),
		 mNumOctetsReceived(0)
{
}

//-------------------------------------------------------------------------------------------------------------
Hdlc::~Hdlc()
{
}

//-------------------------------------------------------------------------------------------------------------
void Hdlc::sendFrame(const std::vector<unsigned char>& data, RespCallbackFunc cb, unsigned timeoutMs)
{
	std::lock_guard<std::mutex> guard(mMutex);

	ReqInfo req(data, cb, timeoutMs);

	// Push the request on the queue
	mReqInfo.push(req);

	event();
}

//-------------------------------------------------------------------------------------------------------------
uint32_t Hdlc::getNumFramesWrongCrc(void)
{
	return mWrongCrcCounter;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t Hdlc::getNumFramesNoStopFlag(void)
{
	return mNoStopFlagCounter;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t Hdlc::getNumOctetsReceived(void)
{
	return mNumOctetsReceived;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Hdlc::runEvent(void)
{
	std::unique_lock<std::mutex> guard(mMutex);

	// Loop till queue has items
	while (mReqInfo.empty() == false)
	{
		// Get the front item
		ReqInfo req = mReqInfo.front();

		guard.unlock();

		// Create the Hdlc frame
		formatHdlcFrame(req.data);

		std::vector<unsigned char> formattedRx;
		formattedRx.clear();

		// Transmit the HDLC frame
		if (transmitFrame(req.data) == true)
		{
			if (req.cb)
			{
				unsigned char flag = 0;
				std::vector<unsigned char> resp;

				// Receive response
				if (receiveData(resp, req.timeoutMs) == true)
				{
					// If reception is successful, then analyse the received data

					// Check whether any response was received
					unsigned int len = resp.size();
					if (len == 0)
					{
						flag |= RESP_TIMEOUT_MASK;
					}
					else
					{
						// Record the number of octets received
						mNumOctetsReceived += resp.size();

						if (resp[0] != FLAG_START)
						{
							flag |= NO_START_FLAG_MASK;
						}

						if (resp[len - 1] != FLAG_STOP)
						{
							flag |= NO_STOP_FLAG_MASK;

							// Increment counter for frames without stop flag
							mNoStopFlagCounter++;
						}

						if (formatRxData(resp, formattedRx) == false)
						{
							flag |= INCORRECT_FCS_MASK;

							// Increment counter for frames with CRC error
							mWrongCrcCounter++;
						}
					}
				}
				else
				{
					flag |= COMM_RX_ERROR_MASK;
				}

				// Provide the reponse to the callback
				req.cb(flag, resp.size(), formattedRx);
			}
		}
		// If transmission fails, then call the callback with failure
		else
		{
			if (req.cb)
			{
				unsigned int flag = COMM_TX_ERROR_MASK;
				req.cb(flag, 0, formattedRx);
			}
		}

		guard.lock();

		// Pop the item from the queue
		mReqInfo.pop();

		guard.unlock();

		Task::msSleep(10);
	}

	return true;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Hdlc::formatHdlcFrame(std::vector<unsigned char>& data)
{
	unsigned char result;				/* The send byte */
	short crc;					/* The crc value */
	unsigned char crc_l, crc_h;			/* The crc bytes */
	std::vector<unsigned char> dataBackup;

	dataBackup = data;

	//Start populating the frame to be sent
	data.clear();
	//Add start flag
	data.push_back(FLAG_START);

	//Add request data
	for (auto & byte : dataBackup)
	{
		if (checkByte(result, byte))
		{
			data.push_back(ESC_ASYNC);
			data.push_back(result);
		}
		else
		{
			data.push_back(result);
		}
	}

	//Calculate and append crc
	crc = fcs::fcs16(fcs::INITFCS16, &dataBackup[0], dataBackup.size());
	crc ^= 0xffff;

	crc_l = crc & 0xFF;
	crc_h = (crc >> 8) & 0xFF;

	// crc high, low
	if (checkByte(result, crc_l))
	{
		data.push_back(ESC_ASYNC);
		data.push_back(result);
	}
	else
	{
		data.push_back(result);
	}

	if (checkByte(result, crc_h))
	{
		data.push_back(ESC_ASYNC);
		data.push_back(result);
	}
	else
	{
		data.push_back(result);
	}

	//Add stop flag
	data.push_back(FLAG_STOP);
}

//-------------------------------------------------------------------------------------------------------------
bool Hdlc::checkByte(unsigned char & result, unsigned char input)
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
bool Hdlc::transmitFrame(std::vector<unsigned char>& data)
{
	std::stringstream txData;

	for (unsigned int i = 0; i < data.size(); i++)
	{
		unsigned int val;
		val = static_cast<unsigned char>(data[i]);
		txData << "0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << val;
		txData << " ";
	}

	std::string infoStr = "Tx Data on bus " + mPhy->busName() + " : " + txData.str();
	eventInfo(infoStr);

	///  Send data
	if (mPhy->writeData(data))
	{
		return true ;
	}

	std::string errStr = "Tx Error on bus " + mPhy->busName() + " : " + mPhy->error();
	eventError(errStr);

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Hdlc::receiveData(std::vector<unsigned char>& data, unsigned int timeoutMs)
{
	std::vector<unsigned char> receivedData;

	data.clear();
	mRespStartTime = std::chrono::system_clock::now();

	while(true)
	{
		// Clear the received data vector to receive new data
		receivedData.clear();

		///  Read data
		if (mPhy->readData(receivedData))
		{
			std::stringstream rxData;

			for (unsigned int i = 0; i < receivedData.size(); i++)
			{
				unsigned int val;
				val = static_cast<unsigned char>(receivedData[i]);
				rxData << "0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << val;
				rxData << " ";
			}

			if (receivedData.size() != 0)
			{
				std::string infoStr = "Rx Data on bus " + mPhy->busName() + " : " + rxData.str();
				eventInfo(infoStr);

				// Append received data in the return data buffer
				for (auto & byte : receivedData)
				{
					data.push_back(byte);
				}

				// Restart response timer
				mRespStartTime = std::chrono::system_clock::now();
			}
			else
			{
				// If response has timed out, then stop reading
				std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

				if (std::chrono::duration_cast<std::chrono::milliseconds>(now - mRespStartTime).count() >= timeoutMs)
				{
					break;
				}
			}

			// Sleep for 10ms
			Task::msSleep(10);
		}
		// If the read command fails, then return error
		else
		{
			std::string errStr = "Rx Error on bus " + mPhy->busName() + " : " + mPhy->error();
			eventError(errStr);
			return false;
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Hdlc::formatRxData(std::vector<unsigned char>& data, std::vector<unsigned char>& formattedRx)
{
	//unsigned short crc;				/* The crc values. */
	bool fcs_status = false;
	std::vector<unsigned char>::iterator it;

	//Check for escape sequence
	for (it = data.begin(); it != data.end(); ++it)
	{
		if (*it == ESC_ASYNC)
		{
			++it;
			if (it == data.end())
			{
				break;
			}
			formattedRx.push_back(*it ^ ESC_COMPL);
		}
		else
		{
			formattedRx.push_back(*it);
		}
	}

	if (formattedRx.size() > 2)
	{
		//Calculate and verify CRC in the received frame
		unsigned short crc = fcs::fcs16(fcs::INITFCS16, &formattedRx[1], formattedRx.size() - 2);
		if (crc == fcs::GOODFCS16)
		{
			fcs_status = true;
		}
	}

	// Remove start flag
	if (formattedRx[0] == FLAG_START)
	{
		formattedRx.erase(formattedRx.begin());
	}

	// Remove stop flag and CRC
	if (formattedRx[formattedRx.size()-1] == FLAG_STOP)
	{
		formattedRx.erase(formattedRx.end() - 3, formattedRx.end());
	}
	else
	{
		formattedRx.erase(formattedRx.end() - 2, formattedRx.end());
	}

	return fcs_status;
}
