/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanAld.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>

#include "stringfunc.hpp"

#include "YangMgrServer.h"
#include "YangParamUtils.h"
#include "XpathUtils.h"

#include "Zcu111FbcOranrrhHandlerORanAld.h"
#include "RadioDatastoreSysrepo.h"
#include "IRadio.h"
#include "Hdlc.h"


using namespace Mplane;

const unsigned int Zcu111FbcOranrrhHandlerORanAld::AldRespTimeout(500);
const unsigned int Zcu111FbcOranrrhHandlerORanAld::HdlcRespTimeout(3000);


//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanAld::Zcu111FbcOranrrhHandlerORanAld(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-ald", moduleMgr, "Zcu111FbcOranrrhHandlerORanAld")
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanAld::~Zcu111FbcOranrrhHandlerORanAld()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanAld::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

	REGISTER_RPC("ald-communication", Zcu111FbcOranrrhHandlerORanAld::rpcAldCommunication) ;

	return true;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanAld::rpcAldCommunication(std::shared_ptr<sysrepo::Session> session, const std::string& rpcXpath,
			std::shared_ptr<YangParams> callList, std::shared_ptr<YangParams> retList)
{
	int numPorts = IRadioFactory::getInterface()->getNumberOfAldPorts();
	const std::string rpc("ald-communication") ;

	uint8_t portId = 0xFF;
	std::vector<uint8_t> reqData(0);
	for (unsigned num=0; num < callList->getNumParams(); ++num)
	{
		std::shared_ptr<YangParam> param(callList->getParam(num)) ;
		std::string leaf(XpathUtils::leafName(param->name())) ;
		if (leaf == "port-id")
		{
			portId = param->getUInt8();
		}
		else if (leaf == "ald-req-msg")
		{
			reqData = param->getBinaryDecoded();
		}
	}

	// Check if port-id is valid
	if (portId >= 0 && portId < numPorts)
	{
		// Get the ald port
		std::vector< std::shared_ptr<IAldPort> > ports = IAldPortFactory::getPorts();

		// Get the Hdlc object
		std::shared_ptr<Hdlc> hdlc = ports[portId]->getHdlc();

		if (reqData.size() > 0)
		{
			auto responseCallback = [this, portId](unsigned char flag, unsigned int fullRespLen, std::vector<unsigned char> formattedRx){
				mHdlcErrorFlag = flag;
				mAldResp = formattedRx;
				mRespRecd = true;
			};

			mRespRecd = false;
			mHdlcErrorFlag = 0;
			mAldResp.clear();
			// Send request to ald port
			hdlc->sendFrame(reqData, responseCallback, AldRespTimeout);

			// Wait till the response is received or timeout happens
			std::chrono::system_clock::time_point respStart = std::chrono::system_clock::now();
			while (mRespRecd == false)
			{
				std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

				if (std::chrono::duration_cast<std::chrono::milliseconds>(now - respStart).count() >= HdlcRespTimeout)
				{
					break;
				}

				Task::msSleep(10);
			};

			// Populate the return list
			retList->addParam(portId, path(rpc + "/port-id")) ;

			if (mHdlcErrorFlag == 0)
			{
				retList->addParam("ACCEPTED", path(rpc + "/status")) ;
			}
			else
			{
				retList->addParam("REJECTED", path(rpc + "/status")) ;
				std::string errMsg("");
				if (mHdlcErrorFlag & Hdlc::RESP_TIMEOUT_MASK)
				{
					errMsg += "Response timed out";
				}
				if (mHdlcErrorFlag & Hdlc::COMM_TX_ERROR_MASK)
				{
					if (errMsg != "")
					{
						errMsg += ", ";
					}
					errMsg += "Transmission failed";
				}
				if (mHdlcErrorFlag & Hdlc::COMM_RX_ERROR_MASK)
				{
					if (errMsg != "")
					{
						errMsg += ", ";
					}
					errMsg += "Reception failed";
				}
				if (mHdlcErrorFlag & Hdlc::NO_START_FLAG_MASK)
				{
					if (errMsg != "")
					{
						errMsg += ", ";
					}
					errMsg += "Start flag not received";
				}
				if (mHdlcErrorFlag & Hdlc::NO_STOP_FLAG_MASK)
				{
					if (errMsg != "")
					{
						errMsg += ", ";
					}
					errMsg += "Stop flag not received";
				}
				if (mHdlcErrorFlag & Hdlc::INCORRECT_FCS_MASK)
				{
					if (errMsg != "")
					{
						errMsg += ", ";
					}
					errMsg += "Incorrect FCS in the response";
				}

				retList->addParam(errMsg, path(rpc + "/error-message")) ;
			}

			retList->addParam(mAldResp, path(rpc + "/ald-resp-msg"), false) ;
			retList->addParam(std::to_string(hdlc->getNumFramesWrongCrc()), path(rpc + "/frames-with-wrong-crc")) ;
			retList->addParam(std::to_string(hdlc->getNumFramesNoStopFlag()), path(rpc + "/frames-without-stop-flag")) ;
			retList->addParam(std::to_string(hdlc->getNumOctetsReceived()), path(rpc + "/number-of-received-octets")) ;
		}
		else
		{
			retList->addParam(portId, path(rpc + "/port-id")) ;
			retList->addParam("ACCEPTED", path(rpc + "/status")) ;
			retList->addParam(std::to_string(hdlc->getNumFramesWrongCrc()), path(rpc + "/frames-with-wrong-crc")) ;
			retList->addParam(std::to_string(hdlc->getNumFramesNoStopFlag()), path(rpc + "/frames-without-stop-flag")) ;
			retList->addParam(std::to_string(hdlc->getNumOctetsReceived()), path(rpc + "/number-of-received-octets")) ;
		}
	}
	else
	{
		retList->addParam(portId, path(rpc + "/port-id")) ;
		retList->addParam("REJECTED", path(rpc + "/status")) ;
		retList->addParam("Invalid ALD port identifier was used in RPC received from Netconf Client", path(rpc + "/error-message")) ;
	}

	return true;
}
