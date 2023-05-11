/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortMgr.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cstdio>
#include <cstdarg>
#include <sstream>

#include "TcpPortIo.h"
#include "TcpPortMgr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TcpPortMgr> TcpPortMgr::getInstance()
{
	static std::shared_ptr<TcpPortMgr> instance(new TcpPortMgr) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TcpPortMgr::TcpPortMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
TcpPortMgr::~TcpPortMgr()
{
	for (auto& entry : mTcpPorts)
	{
		entry.second->stop() ;
	}

	mTcpPorts.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortMgr::portOpen(ITcpPortIoTypes::TcpPortType type,
		unsigned port, unsigned maxConnections, std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry != mTcpPorts.end())
	{
		failReason = "TCP Port already opened" ;
		return false ;
	}

	std::shared_ptr<TcpPortIo> tcpPort(std::shared_ptr<TcpPortIo>(new TcpPortIo(type, port, maxConnections))) ;


	// now start the process
	try
	{
		tcpPort->start() ;
	}
	catch (SocketException& e)
	{
		failReason = e.description() ;
		return false ;
	}
	catch (...)
	{
		failReason = "Unable to open TCP port" ;
		return false ;
	}

	mTcpPorts[port] = tcpPort ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortMgr::portClose(unsigned port, std::string& failReason)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry == mTcpPorts.end())
		return true ;

	mTcpPorts.erase(entry) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortMgr::show(std::ostream& os)
{
	Mutex::Lock lock(mMutex) ;

	TcpPortIo::showFormat(os, "Port", "Type", "Inst", "Connection") ;
	for (auto& entry : mTcpPorts)
	{
		entry.second->show(os) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortMgr::portShow(unsigned port, std::ostream& os)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry == mTcpPorts.end())
		return ;

	entry->second->show(os) ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortMgr::portSend(unsigned port, const std::string& msg)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry == mTcpPorts.end())
		return ;

	entry->second->send(msg) ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortMgr::portSend(unsigned port, const std::vector<uint8_t>& msg)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry == mTcpPorts.end())
		return ;

	entry->second->send(msg) ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortMgr::portSend(unsigned port, char const* fmt, ... )
{
	va_list args;
	va_start (args, fmt);

	char buffer[1024];
	vsnprintf (buffer, sizeof(buffer), fmt, args);
	va_end (args);

	portSend( port, std::string(buffer) ) ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortMgr::portReceive(unsigned port, std::vector<uint8_t>& data, unsigned expectedSize, unsigned timeoutSecs)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry == mTcpPorts.end())
		return false ;

	return entry->second->receive(data, expectedSize, timeoutSecs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortMgr::portReceive(unsigned port, ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize, unsigned timeoutSecs)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry == mTcpPorts.end())
		return false ;

	return entry->second->receive(callback, expectedSize, timeoutSecs) ;
}


//-------------------------------------------------------------------------------------------------------------
bool TcpPortMgr::isPortOpen(unsigned port)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry == mTcpPorts.end())
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortMgr::setBinary(unsigned port, bool binary)
{
	Mutex::Lock lock(mMutex) ;

	auto entry(mTcpPorts.find(port)) ;
	if (entry == mTcpPorts.end())
		return ;

	entry->second->setBinary(binary) ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortMgr::closePorts()
{
	Mutex::Lock lock(mMutex) ;

	mTcpPorts.clear() ;
}
