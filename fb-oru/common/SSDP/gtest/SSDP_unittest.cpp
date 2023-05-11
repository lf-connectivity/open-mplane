/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SSDP_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <string>

#include "MulticastSocket.h"
#include "TaskPeriodicEvent.h"
#include "Task.h"

#include "IAppOptions.h"
#include "IAppSettings.h"
#include "IAppSettingsFactory.h"

#include "NetStatus.h"

#include "Ssdp.h"

using namespace Mplane ;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const std::string SSDP_ADDRESS{"239.255.255.250"} ;
static const unsigned SSDP_PORT{41900} ;
static const unsigned MX{3} ;

const std::string MSEARCH(
    "M-SEARCH * HTTP/1.1\r\n"
    "HOST: " + SSDP_ADDRESS + ":" + std::to_string(SSDP_PORT) + "\r\n"
    "MAN: \"ssdp:discover\"\r\n"
    "MX: " + std::to_string(MX) + "\r\n"
    "ST: ssdp:all\r\n"
    "\r\n"
) ;


//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetStatus> INetStatus::getInstance()
{
	return NetStatus::getInstance() ;
}



//=============================================================================================================

namespace Mplane {


class SsdpDisplay : public TaskPeriodicEvent {
public:
	SsdpDisplay(bool debug) :
		TaskPeriodicEvent(2000, Task::PRIORITY_LOW, Task::SMALL_STACK, "SsdpRx", "SSDP"),
		mDebug(debug),
		mMutex(),
		mDevices()
	{
	}

	~SsdpDisplay() {}

	void addDevice(const std::string& uuid, const std::string& info)
	{
		Mutex::Lock lock(mMutex) ;
		mDevices[uuid] = info ;
	}

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override
	{
		Mutex::Lock lock(mMutex) ;

		// cls
		if (!mDebug)
			std::cout << "\033[2J\033[0;0H" ;

		// show current devices
		for (auto device : mDevices)
		{
			std::cout << device.first << " " << device.second << std::endl ;
		}
		return true ;
	}

private:
	bool mDebug ;
    Mutex mMutex ;
    std::map<std::string, std::string> mDevices ;
};

class SsdpRx : public Task {
public:
	SsdpRx(std::shared_ptr<SsdpDisplay> display, bool debug) :
		Task(Task::PRIORITY_LOW, Task::SMALL_STACK, "SsdpRx", "SSDP"),
		mDebug(debug),
		mDisplay(display),
		mSock( std::make_shared<MulticastSocket>() )
	{
		if (!mSock->create())
			return ;

		if (!mSock->setMulticast(SSDP_ADDRESS, SSDP_PORT))
			return ;

		if (!mSock->bind(SSDP_PORT))
			return ;
	}

	~SsdpRx() {}

protected:
    virtual int run() override
    {
    	// listen for client notifications
    	std::string buff ;
    	while(1)
    	{

    		if (mDebug)
    			std::cerr << "Listening for messages.." << std::endl ;

    		int numBytes(mSock->recv(buff)) ;
    		if (numBytes <= 0)
    		{
    			std::cerr << "ERROR: Unable to receive message" << std::endl ;
    			return 1 ;
    		}

    		if (mDebug)
    			std::cerr << buff << std::endl ;

    		processMsg(buff) ;
    	}

    	return 0 ;
    }

    void processMsg(const std::string& msg)
    {
    	// Skip anything without AXIS
    	if (msg.find("AXIS") == std::string::npos)
    		return ;

    	// only look at NOTIFY or OK
    	if (msg.find("NOTIFY * HTTP/1.1") == std::string::npos && msg.find("HTTP/1.1 200 OK") == std::string::npos)
    		return ;

    	// Grab some useful info
    	std::string unit( getField(msg, "AXIS-UNIT") ) ;
    	std::string host( getField(msg, "AXIS-HOST") );
    	std::string ip( getField(msg, "AXIS-IP") );
    	std::string server( getField(msg, "SERVER") );
    	std::string uuid( getField(msg, "USN") );

    	std::string info(unit + " " + host + " " + ip + " " + server) ;
    	mDisplay->addDevice(uuid, info) ;

    	if (mDebug)
    		std::cerr << uuid << " " << info << std::endl ;
    }

    std::string getField(const std::string& msg, const std::string& field)
    {
    	std::size_t pos(msg.find(field+":")) ;
    	if (pos == std::string::npos)
    		return "";

    	pos += field.size()+1 ;
    	std::size_t end(msg.find_first_of("\r\n", pos)) ;
    	if (end == std::string::npos)
    		end = msg.size() ;

    	return msg.substr(pos, end-pos) ;
    }

private:
    bool mDebug ;
    std::shared_ptr<SsdpDisplay> mDisplay ;
    std::shared_ptr<MulticastSocket> mSock ;
};

}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(SSDP, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// Change log file location for testing
	NetStatus::mTestIpLogPath = "./ip.log" ;
	NetStatus::mTestUpdateRateMs = 200 ;


	/////////////////////////////////////////////////////////////////
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;

	// Add the default options
	std::vector<std::shared_ptr<IAppOptionSpec> > options ;
	options.push_back(
		IAppOptionSpec::factory("ethbb",  DataVariantType::String, "Ethernet interface name (over baseband)", "eth_bb", "ETHBB")
	) ;
	options.push_back(
		IAppOptionSpec::factory("ethcdi", DataVariantType::String, "Ethernet interface name (control and debug)", "eth_cdi", "ETHCDI")
	) ;
	options.push_back(
		IAppOptionSpec::factory("port", DataVariantType::Int, "TIF port", "49500", "TIFPORT")
	) ;
	options.push_back(
		IAppOptionSpec::factory("ethssdp", DataVariantType::String, "Ethernet interface name (discovery)", "eth5", "ETHSSDP")
	) ;

	// Define expected options and process the command line
	int argc=0;
	const char* args = {"SSDP_unittest"} ;
	const char **argv=&args;
	auto mAppOpts = IAppOptions::createInstance(argc, argv, "SSDP Service Test", options) ;

	std::string ifname(mAppOpts->getOption("ethssdp").toString()) ;
	std::cerr << "Connecting to interface " << ifname << "..." << std::endl ;


	/////////////////////////////////////////////////////////////////

	// This is a test program - not a real test
	std::shared_ptr<Ssdp> ssdp(
		std::make_shared<Ssdp>(
			"TEST",
			"1.0",
			ifname,
			1800)
	) ;

	Loggable::setGroupLogDebugLevel(Loggable::LOG_DEBUG_VERBOSE, "SSDP") ;

//	sleep(120) ;

	///////////////////////////////////////////////////////////////////

	bool debug(true) ;

	// Receiver
	std::shared_ptr<SsdpDisplay> display( std::make_shared<SsdpDisplay>(debug) ) ;
	std::shared_ptr<SsdpRx> rx( std::make_shared<SsdpRx>(display, debug) ) ;
	rx->start() ;

	// Sender
	std::shared_ptr<MulticastSocket> msock( std::make_shared<MulticastSocket>() ) ;

	if (!msock->create())
	{
		std::cerr << "ERROR: Unable to create multicast socket" << std::endl ;
		return ;
	}

	if (!msock->setMulticast(SSDP_ADDRESS, SSDP_PORT))
	{
		std::cerr << "ERROR: Unable to bind to multicast port" << std::endl ;
		return ;
	}

	// User loop
	while(1)
	{
		std::cerr << "Send M-SEARCH ..." << std::endl ;

		// Chuck out a search
		if (!msock->send(MSEARCH))
		{
			std::cerr << "ERROR: Unable to send message" << std::endl ;
			return ;
		}
		sleep(2*MX) ;
	}


}
