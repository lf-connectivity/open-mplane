/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Hdlc.h
 * \brief     Class to communicate using HDLC data link layer
 *
 *
 * \details   Class to communicate using HDLC data link layer
 *
 */


#ifndef COMMON_HDLC_INC_HDLC_H_
#define COMMON_HDLC_INC_HDLC_H_

#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <queue>
#include <chrono>
#include <functional>

#include "GlobalTypeDefs.h"
#include "IBus.h"
#include "TaskEvent.h"
#include "fcs.h"

namespace Mplane {

/*!
 * \class  Hdlc
 * \brief
 * \details
 *
 */
class Hdlc : public TaskEvent{
public:
	Hdlc(std::shared_ptr<IBus> phy);
	virtual ~Hdlc();

	static const unsigned char FLAG_START;		/* Starts each frame */
	static const unsigned char FLAG_STOP; 		/* Ends each frame */
	static const unsigned char ESC_ASYNC; 		/* Escapes special chars (0x7d, 0x7e, 0x7f) */
	static const unsigned char ESC_COMPL; 		/* XORed with special chars in data */
	static const unsigned char NO_START_FLAG_MASK = (1 << 0);
	static const unsigned char NO_STOP_FLAG_MASK = (1 << 1);
	static const unsigned char INCORRECT_FCS_MASK = (1 << 2);
	static const unsigned char RESP_TIMEOUT_MASK = (1 << 3);
	static const unsigned char COMM_TX_ERROR_MASK = (1 << 4);
	static const unsigned char COMM_RX_ERROR_MASK = (1 << 5);

	/**
	 * Callback function for when a vlan is found
	 */
	using RespCallbackFunc = std::function<void(unsigned char, unsigned int, std::vector<unsigned char>)> ;

    /**
     * This method forms an HDLC frame by adding flags and checksum to the provided raw data
     * and sends it to the physical layer.
     *
     * @return Success/Failure.
     */
    void sendFrame(const std::vector<unsigned char>& data, RespCallbackFunc cb, unsigned timeoutMs) ;

    /**
     * This method returns the running counter that stores the number of frames received
     * with incorrect CRC
     *
     */
    uint32_t getNumFramesWrongCrc(void);

    /**
     * This method returns the running counter that stores the number of frames received
     * without stop flag
     *
     */
    uint32_t getNumFramesNoStopFlag(void);

    /**
     * This method returns the running counter that stores the number of octets received
     *
     */
    uint32_t getNumOctetsReceived(void);

protected:

	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	bool runEvent() ;

private:

	std::shared_ptr<IBus> mPhy;            //!> Pointer to physical layer bus object

	struct ReqInfo                         //!> Structure for Request data to be sent as HDLC
	{
		ReqInfo():
			data(std::vector<unsigned char>(0)),
			cb(nullptr),
			timeoutMs(0)
		{

		}

		ReqInfo(const std::vector<unsigned char> txData, RespCallbackFunc respCb, unsigned timeoutVal):
			data(txData),
			cb(respCb),
			timeoutMs(timeoutVal)
		{

		}

		std::vector<unsigned char> data;
		RespCallbackFunc cb;
		unsigned timeoutMs;
	};

	std::queue<ReqInfo> mReqInfo;          //!> Request data to be sent as HDLC
	std::mutex mMutex;                     //!> Mutex required to protect shared data
	std::chrono::system_clock::time_point mRespStartTime;         //!> Time at request is sent or last data is received

	uint32_t mWrongCrcCounter;            //!> Running counter for frames received with incorrect CRC
	uint32_t mNoStopFlagCounter;          //!> Running counter for frames received without stop flag
	uint32_t mNumOctetsReceived;          //!> Running counter for number of octets received

	void formatHdlcFrame(std::vector<unsigned char>& data);

	bool transmitFrame(std::vector<unsigned char>& data);

	bool checkByte(unsigned char & result, unsigned char input);

	bool receiveData(std::vector<unsigned char>& data, unsigned int timeoutMs = 100);

	bool formatRxData(std::vector<unsigned char>& data, std::vector<unsigned char>& formattedRx);

} ;

}

#endif /* COMMON_HDLC_INC_HDLC_H_ */
