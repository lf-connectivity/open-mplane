/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsHelper.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Task.h"
#include "stringfunc.hpp"

#include "TcpPortHelper.h"
#include "RtiKeyword.h"
#include "FpgaCommsHelper.h"

using namespace Mplane;

//=============================================================================================================
// CLASSES
//=============================================================================================================

class CommsLog {
public:
	CommsLog(IRtiMsgParser& msgParser, std::shared_ptr<IFpgaComms> fpgaComms,
			unsigned port, IFpgaPdu::PduDataType type) :
		mMsgParser(msgParser),
		mFpgaComms(fpgaComms),
		mPort(port),
		mType(type),
		mRegistered(false),
		mFailReason(""),
		mTypeStr(std::string("[") + IFpgaPdu::typeToStr(type) + "] ")
	{
		mRegistered = mFpgaComms->registerMsgHandler(mType, this,
			[this](std::shared_ptr<IFpgaMsg> msg) {handleMsg(msg);},
			[](const IFpgaPdu& pdu)->std::shared_ptr<IFpgaMsg> {return IFpgaMsg::factory(pdu);},
			mFailReason) ;
	}

	~CommsLog()
	{
		if (mRegistered)
		{
			mFpgaComms->unRegisterMsgHandler(mType, this) ;
		}
	}

	void handleMsg(std::shared_ptr<IFpgaMsg> msg)
	{
//		std::string msgStr(mTypeStr + msg->toString()) ;
		std::string msgStr(msg->toString()) ;
		mMsgParser.tcpPortSend(mPort, msgStr) ;
	}

private:
	IRtiMsgParser& mMsgParser ;
	std::shared_ptr<IFpgaComms> mFpgaComms ;
	unsigned mPort ;
	IFpgaPdu::PduDataType mType ;
	bool mRegistered ;
	std::string mFailReason ;
	std::string mTypeStr ;
};

// Map indexed by port/PduDataType
using LogPortEntry = std::map<IFpgaPdu::PduDataType, std::shared_ptr<CommsLog> > ;
using LogPortMap = std::map<unsigned, LogPortEntry > ;
static LogPortMap mLogPorts ;

//=============================================================================================================
// PROTECTED STATIC
//=============================================================================================================
Mutex FpgaCommsHelper::mMutex ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// normal response timeout
const unsigned RESPONSE_TIMEOUT_MS = 2000 ;

// wait for PIM state timeout
const unsigned STATE_TIMEOUT_S	= 180 ;

// wait for PIM state - poll time
const unsigned STATE_POLL_MS		= 1000 ;


const std::vector<IFpgaPdu::PduDataType> dataTypes{
	IFpgaPdu::PduDataType::PDU_TYPE_CMD,
	IFpgaPdu::PduDataType::PDU_TYPE_REPLY,
	IFpgaPdu::PduDataType::PDU_TYPE_EVENT,
	IFpgaPdu::PduDataType::PDU_TYPE_LOG,
	IFpgaPdu::PduDataType::PDU_TYPE_MATLAB,
	IFpgaPdu::PduDataType::PDU_TYPE_TEXT,
} ;

#define DEBUG_FPGACOM
#ifdef DEBUG_FPGACOM
#define LOG_DEBUG_FPGACOM(fmt, args...) logDebugVerbose(fmt, ## args)
#else
#define LOG_DEBUG_FPGACOM(fmt, args...)
#endif



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsHelper::FpgaCommsHelper(const std::string& name, std::shared_ptr<IFpgaComms> fpgaComms, const std::string& stateVar) :
	Loggable(name, "TIF"),
	mFpgaComms(fpgaComms),
	mStateVar(stateVar)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsHelper::~FpgaCommsHelper()
{
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::shutdown()
{
	// Destroy all PIM log forwarders
	Mutex::Lock lock(FpgaCommsHelper::mMutex) ;
	mLogPorts.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::logClose(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	std::string typeStr( callList->find("type")->toString() ) ;
	IFpgaPdu::PduDataType type(IFpgaPdu::strToType(typeStr)) ;
	mFpgaComms->setLogging(type, false) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::logOpen(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	std::string typeStr( callList->find("type")->toString() ) ;
	IFpgaPdu::PduDataType type(IFpgaPdu::strToType(typeStr)) ;
	mFpgaComms->setLogging(type, true) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::logShow(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(FpgaCommsHelper::mMutex) ;

	std::stringstream ss ;
	ss << std::endl ;

	for (auto type : dataTypes)
	{
		ss << padLeft(IFpgaPdu::typeToStr(type), 7) ;
	}
	ss << std::endl ;

	for (auto type : dataTypes)
	{
		if (mFpgaComms->getLogging(type))
			ss << padLeft(" Y ", 7) ;
		else
			ss << padLeft("---", 7) ;
	}
	ss << std::endl ;
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::portOpen(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	/*
	 *   ENUM(REPLY:EVENT:LOG) type
	 *   INT port
	 */
	if (!TcpPortHelper::portValid(msgParser, "port", callList, returnList))
		return ;

	unsigned port( static_cast<unsigned>(callList->find("port")->toInt()) ) ;

	std::string typeStr( callList->find("type")->toString() ) ;
	IFpgaPdu::PduDataType type(IFpgaPdu::strToType(typeStr)) ;

	Mutex::Lock lock(FpgaCommsHelper::mMutex) ;

	// See if port exists in map
	auto logMap(mLogPorts.find(port)) ;
	if (logMap == mLogPorts.end())
	{
		auto ret( mLogPorts.insert( std::pair<unsigned, LogPortEntry>(port, LogPortEntry{}) ) ) ;
		logMap = ret.first ;
	}


	// see if this type entry exists
	auto logEntry(logMap->second.find(type)) ;
	if (logEntry != logMap->second.end())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Port logging already set up for this type") ;
		return ;
	}

	// Create a new entry
	logMap->second.insert(
		std::pair<IFpgaPdu::PduDataType, std::shared_ptr<CommsLog>>(
			type, std::shared_ptr<CommsLog>(new CommsLog(msgParser, mFpgaComms, port, type))
		)
	) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::portClose(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	/*
	 *   ENUM(REPLY:EVENT:LOG) type
	 *   INT port
	 */
	unsigned port( static_cast<unsigned>(callList->find("port")->toInt()) ) ;
	if ( (port < 1024) || (port > 65535) )
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Port number must be between 1024..65535") ;
		return ;
	}

	std::string typeStr( callList->find("type")->toString() ) ;
	IFpgaPdu::PduDataType type(IFpgaPdu::strToType(typeStr)) ;


	Mutex::Lock lock(FpgaCommsHelper::mMutex) ;

	// See if port exists in map
	auto logMap(mLogPorts.find(port)) ;
	if (logMap == mLogPorts.end())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("No entry for this port") ;
		return ;
	}


	// see if this type entry exists
	auto logEntry(logMap->second.find(type)) ;
	if (logEntry == logMap->second.end())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Port already closed for this type") ;
		return ;
	}

	// Remove this entry
	logMap->second.erase( logEntry ) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::portShow(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(FpgaCommsHelper::mMutex) ;

	std::stringstream ss ;
	ss << std::endl ;

	ss << padLeft("Port", 7) ;
	for (auto type : dataTypes)
	{
		ss << padLeft(IFpgaPdu::typeToStr(type), 7) ;
	}
	ss << std::endl ;

	for (auto logMapEntry : mLogPorts)
	{
		ss << padLeft(std::to_string(logMapEntry.first), 7) ;
		for (auto type : dataTypes)
		{
			if (logMapEntry.second.find(type) == logMapEntry.second.end())
				ss << padLeft("---", 7) ;
			else
				ss << padLeft(" Y ", 7) ;
		}
		ss << std::endl ;
	}
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
}

//=============================================================================================================
// Common Commands
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::apiVersion(IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status
	// * [STRING Info]
	// * [STRING Message]
	//

	// Send command to get API
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory("apiVersion") ) ;

	std::shared_ptr<IFpgaMsg> response ;
	if (! commandGetResponse(msg, returnList, response) )
		return ;

	if (!response.get())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Unable to get API version") ;
		return ;
	}

	std::map<std::string, DataVariant> attributes( response->getAttributes() ) ;
	if (attributes.find("apiVersion") == attributes.end() )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("reply did not include api version") ;
		return ;
	}

	// Show versions
	std::stringstream ss ;
	ss << std::endl ;
	ss << "Reply version       : " << std::hex << "0x" << attributes.at("apiVersion").toInt() << std::endl ;
	ss << "Application version : " << std::hex << "0x" << mFpgaComms->getApiVersion() << std::endl ;

	// finish up
	returnList->find(RtiKeyword::MESSAGE_VAR)->set(ss.str()) ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::checkApi(IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status
	// * [STRING Info]
	// * [STRING Message]
	//


	// Send command to get API
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory("apiVersion") ) ;

	std::shared_ptr<IFpgaMsg> response ;
	if (! commandGetResponse(msg, returnList, response) )
		return ;

	if (!response.get())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Unable to get API version") ;
		return ;
	}


	// Show versions
	std::map<std::string, DataVariant> attributes( response->getAttributes() ) ;
	if (attributes.find("apiVersion") == attributes.end() )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("reply did not include api version") ;
		return ;
	}

	unsigned embeddedVer = static_cast<unsigned>(attributes.at("apiVersion").toInt()) ;
	unsigned appVer = mFpgaComms->getApiVersion() ;

	// Compare versions
	if (embeddedVer != appVer)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("API versions do not match") ;
		return ;
	}

	// finish up
	returnList->find(RtiKeyword::MESSAGE_VAR)->set("API version match") ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::debugStatus(IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status
	// * [STRING Info]
	// * [STRING Message]
	//

	std::vector< std::pair<std::string, UINT16> > statusValues( mFpgaComms->statusValues() ) ;

	std::stringstream ss ;

	ss << std::endl ;
	for (auto entry : statusValues)
	{
		ss << padLeft(entry.first, 20) << " : 0x" << std::hex << entry.second << std::dec << std::endl ;
	}
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::frd(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory("frd", callList->getList() )) ;

	// Use FpgaComms to send command and process reply
	std::shared_ptr<IFpgaMsg> response ;
	if (! commandGetResponse(msg, returnList, response) )
		return ;

	if (!response.get())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Unable to get run FRD") ;
		return ;
	}

	std::map<std::string, DataVariant> attributes( response->getAttributes() ) ;
//std::cerr << "Attributes" << std::endl ;
//for (auto entry : attributes)
//{
//	std::cerr << entry.first << "=" << entry.second << std::endl ;
//}
	if (attributes.find("addr") == attributes.end() )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("reply did not include address") ;
		return ;
	}
	if (attributes.find("data") == attributes.end() )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("reply did not include data") ;
		return ;
	}

	std::stringstream ss ;
	ss << std::endl ;
	ss << std::hex << "0x" << attributes.at("addr").toInt() << ": 0x" << attributes.at("data").toInt() ;
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::fwr(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory("fwr", callList->getList() )) ;

	// Use FpgaComms to send command and process reply
	std::shared_ptr<IFpgaMsg> response ;
	if (! commandGetResponse(msg, returnList, response) )
		return ;

	if (!response.get())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Unable to get run FWR") ;
		return ;
	}

	std::map<std::string, DataVariant> attributes( response->getAttributes() ) ;
	if (attributes.find("addr") == attributes.end() )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("reply did not include address") ;
		return ;
	}
	if (attributes.find("data") == attributes.end() )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("reply did not include data") ;
		return ;
	}

	std::stringstream ss ;
	ss << std::endl ;
	ss << std::hex << "0x" << attributes.at("addr").toInt() << ": 0x" << attributes.at("data").toInt() ;
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::get( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// Called with:
	// * [STRING arg0]
	// * [STRING arg1]
	// ..
	// * [STRING arg59]
	// Returns:
	// * ENUM(OK:ERROR) Status
	// * [STRING Info]
	// * [STRING Message]
	//

	// Create a set of variable names to get, along with a list of any attributes provided
	std::vector<DataVariant> attributes ;
	std::set<std::string> varNames ;
	for (auto dv : callList->getList())
	{
		if (dv.isSet())
		{
			// name to get
			if (dv.getType() == DataVariantType::String)
			{
				// ensure name is valid
				if (!mFpgaComms->getTokens()->isStateToken(dv.toString()))
				{
					returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
					returnList->find(RtiKeyword::MESSAGE_VAR)->set("Invalid variable name " + dv.toString()) ;
					return ;
				}
				varNames.insert(dv.toString()) ;
				continue ;
			}

			// variable to set
			attributes.push_back(dv) ;
		}
	}

	// If no attributes set then abort
	if (varNames.empty())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Get command requires at least one variable name") ;
		return ;
	}

	// Create message
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory(
			"get",
			attributes,
			varNames
	) ) ;


	// Use FpgaComms to send command and process reply
	commandShowResponse(msg, returnList) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::set( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	std::vector<DataVariant> attributes( callList->getList() ) ;

	// If no attributes set then abort
	if (attributes.empty())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Set command requires at least one attribute to be set") ;
		return ;
	}

	// Create message
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory("set", attributes) ) ;

	// Use FpgaComms to send command and process reply
	commandWaitResponse(msg, returnList) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::dump(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	cmdWaitResponse("dump", callList, returnList) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::reset(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	cmdWaitResponse("reset", callList, returnList) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsHelper::restart(IRtiMsgParser& msgParser, DataVariantList* callList, DataVariantList* returnList)
{
	cmdWaitResponse("restart", callList, returnList) ;

	// need to wait for the microblaze to restart
	Task::msSleep(2000) ;

	// Now wait for pim state to "clear" - i.e. coming back with state != 9999 will be fine
	commandWaitNotState( 9999, returnList ) ;
}



//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::cmdWithSet( const std::string& command, DataVariantList *callList, DataVariantList *returnList )
{
	// Create message
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory(command, callList->getList()) ) ;

	// Use FpgaComms to send command and process reply
	return commandWaitResponse(msg, returnList) ;

}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::cmdShowResponse(const std::string& command, DataVariantList* returnList)
{
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory(command) ) ;
	return commandShowResponse(msg, returnList) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::cmdWaitResponse(const std::string& command, DataVariantList* returnList)
{
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory(command) ) ;
	return commandWaitResponse(msg, returnList) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::cmdGetResponse(const std::string& command,
		DataVariantList* returnList, std::shared_ptr<IFpgaMsg>& response)
{
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory(command) ) ;
	return commandGetResponse(msg, returnList, response) ;
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::cmdShowResponse(const std::string& command, DataVariantList *callList, DataVariantList* returnList)
{
	std::shared_ptr<IFpgaMsg> msg( msgFromCommand(command, callList) ) ;
	return commandShowResponse(msg, returnList) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::cmdWaitResponse(const std::string& command, DataVariantList *callList, DataVariantList* returnList)
{
	std::shared_ptr<IFpgaMsg> msg( msgFromCommand(command, callList) ) ;
	return commandWaitResponse(msg, returnList) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::cmdGetResponse(const std::string& command, DataVariantList *callList,
		DataVariantList* returnList, std::shared_ptr<IFpgaMsg>& response)
{
	std::shared_ptr<IFpgaMsg> msg( msgFromCommand(command, callList) ) ;
	return commandGetResponse(msg, returnList, response) ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsg> FpgaCommsHelper::msgFromCommand( const std::string& command, DataVariantList *callList )
{
	return IFpgaMsg::factory(command, callList->getList()) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::commandShowResponse( std::shared_ptr<IFpgaMsg> msg, DataVariantList *returnList )
{
	// - Display the response message -

	// Use FpgaComms to send command and process reply
	std::shared_ptr<IFpgaMsg> response ;
	std::string failReason ;
	if (!mFpgaComms->commandWaitResponse(msg, response, failReason))
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return false ;
	}

	// Report string
	returnList->find(RtiKeyword::MESSAGE_VAR)->set(response->toString()) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::commandWaitResponse( std::shared_ptr<IFpgaMsg> msg, DataVariantList *returnList )
{
	// - Wait for ACK : Do NOT show response message -
	std::shared_ptr<IFpgaMsg> response ;
	return commandGetResponse(msg, returnList, response) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::commandGetResponse( std::shared_ptr<IFpgaMsg> msg, DataVariantList *returnList, std::shared_ptr<IFpgaMsg>& response )
{
	// - Wait for ACK : Do NOT show response message -

	// Use FpgaComms to send command and process reply
	std::string failReason ;
	if (!mFpgaComms->commandWaitResponse(msg, response, failReason))
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsHelper::commandWaitNotState(unsigned state, DataVariantList* returnList)
{
	// Need to repeatedly send the 'get state' command until the state is NOT the one specified

//std::cerr << "FpgaCommsHelper::commandWaitState " << mStateVar << "==" << state << std::endl ;

	// repeated send of command
	unsigned loopCount(STATE_TIMEOUT_S * 1000 / STATE_POLL_MS) ;
	while (loopCount > 0)
	{
		// create the command
		std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory(
				"get",
				std::vector<DataVariant>{},
				std::set<std::string>{mStateVar}
		) ) ;

//		std::cerr << "FpgaCommsHelper::commandWaitState [" << loopCount << "] send cmd..." << msg->toString() << std::endl ;

		// Use FpgaComms to send command and process reply
		std::shared_ptr<IFpgaMsg> response ;
		if (!commandGetResponse(msg, returnList, response))
			return false ;

//		std::cerr << "FpgaCommsHelper::commandWaitState check response " << response->toString() << std::endl ;

		// process the response - should be in the form 'get state=2'
		std::map<std::string, DataVariant> attributes( response->getAttributes() ) ;
		if (attributes.find(mStateVar) != attributes.end() )
		{
//			std::cerr << "FpgaCommsHelper::commandWaitState state=" << attributes.at(mStateVar).toInt() << std::endl ;

			// see if we've finally got to a state we can move on from
			if (attributes.at(mStateVar).toInt() != static_cast<int>(state) )
				return true ;
		}

//		std::cerr << "FpgaCommsHelper::commandWaitState sleep..." << std::endl ;

		logDebugVerbose("Waiting for state %s to leave %u (count=%u)", mStateVar.c_str(), state, loopCount) ;

		// poll tick
		Task::msSleep(STATE_POLL_MS) ;

		--loopCount ;
	}

	// failed to get response
	returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
	returnList->find(RtiKeyword::MESSAGE_VAR)->set("State change timed out") ;
	return false ;
}
