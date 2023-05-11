/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MsgQ.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <error.h>

#include <iostream>
#include <cstdlib>

#include "MsgQ.h"

//#define DEBUG_MSQ
#ifdef DEBUG_MSQ
#include "ByteTransfer.hpp"
#endif


using namespace Mplane;

#ifdef DEBUG_MSQ
#define DBPRINT std::cerr
#define DUMP_DATA(msg, vec) { std::cout << msg << std::endl; ByteTransfer::dump(vec); }
#else
#define DBPRINT	if (0) std::cout
#define DUMP_DATA(msg, vec)
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::MsgQ::MsgQ(const std::string& name) :
	mName(name),
	mMutex(),
	mCreated(false),
	mMqd(-1),
	mMsgSize(0),
	mBlocking(true)
{
DBPRINT << "MsgQ NEW : " << mName << " " << this << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::MsgQ::~MsgQ()
{
DBPRINT << "MsgQ DEL : " << mName << " " << this << std::endl ;
	close() ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::MsgQ::create(unsigned msgSize, unsigned maxMsgs)
{
DBPRINT << "MsgQ " << mName << " " << this << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	// fail if already open
	if (mMqd != (mqd_t)-1)
		return false ;

	// Delete any previous queue
	::mq_unlink(mName.c_str()) ;

    /* If 'attrp' is NULL, mq_open() uses default attributes. If an
       option specifying a message queue attribute is supplied on the
       command line, we save the attribute in 'attr' and set 'attrp'
       pointing to 'attr'. We assign some (arbitrary) default values
       to the fields of 'attr' in case the user specifies the value
       for one of the queue attributes, but not the other. */

    struct mq_attr attr;
    attr.mq_maxmsg = maxMsgs;
    attr.mq_msgsize = msgSize;
    mMsgSize = msgSize ;

DBPRINT << "MsgQ " << mName << " " << this << " CREAT" << std::endl ;
    mMqd = ::mq_open(mName.c_str(), (O_CREAT | O_RDWR | O_EXCL), (S_IRUSR | S_IWUSR), &attr);
//	if (mMqd == (mqd_t) -1)
//		std::cerr << "MsgQ " << mName << " " << this  << " " << "Error: MsgQ create - errno=" << errno << std::endl ;

    if (mMqd == (mqd_t) -1)
        return false ;

    // allocate buffer
    mBuffer.resize(mMsgSize) ;

    mCreated = true ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::MsgQ::connectWrite(bool blocking)
{
DBPRINT << "MsgQ " << mName << " " << this  << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (mMqd != -1)
		return false ;

	mBlocking = blocking ;
	int flags(O_WRONLY) ;
	if (!blocking)
		flags |= O_NONBLOCK ;

DBPRINT << "MsgQ " << mName << " " << this << " open WRONLY" << std::endl ;
	mMqd = ::mq_open(mName.c_str(), flags);
//	if (mMqd == (mqd_t) -1)
//		std::cerr << "MsgQ " << mName << " " << this  << " " << "Error: MsgQ connectWrite - open - errno=" << errno << std::endl ;

    if (mMqd == (mqd_t) -1)
    	return false ;

    /* We need to know the 'mq_msgsize' attribute of the queue in
       order to determine the size of the buffer for mq_receive() */
    struct mq_attr attr;
    if (::mq_getattr(mMqd, &attr) == -1)
        return false ;
    mMsgSize = attr.mq_msgsize ;

    // allocate buffer
    mBuffer.resize(mMsgSize) ;

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::MsgQ::connectRead(bool blocking)
{
DBPRINT << "MsgQ " << mName << " " << this  << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (mMqd != -1)
		return false ;

	mBlocking = blocking ;
	int flags(O_RDONLY) ;
	if (!blocking)
		flags |= O_NONBLOCK ;

DBPRINT << "MsgQ " << mName << " " << this << " open RDONLY" << std::endl ;
	mMqd = ::mq_open(mName.c_str(), flags);
//	if (mMqd == (mqd_t) -1)
//		std::cerr << "MsgQ " << mName << " " << this  << " " << "Error: MsgQ connectRead - open - errno=" << errno << std::endl ;

	if (mMqd == (mqd_t) -1)
    	return false ;

    /* We need to know the 'mq_msgsize' attribute of the queue in
       order to determine the size of the buffer for mq_receive() */
    struct mq_attr attr;
    if (::mq_getattr(mMqd, &attr) == -1)
        return false ;
    mMsgSize = attr.mq_msgsize ;

    // allocate buffer
    mBuffer.resize(mMsgSize) ;

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::MsgQ::close()
{
	if (mMqd == -1)
		return true ;

DBPRINT << "MsgQ " << mName << " " << this << " close" << std::endl ;
	if (::mq_close(mMqd) != 0)
		return false ;

	mMqd = -1 ;

	if (mCreated)
	{
DBPRINT << "MsgQ " << mName << " " << this << " unlink" << std::endl ;
	   if (::mq_unlink(mName.c_str()) != 0)
		   return false ;
	}

	mCreated = false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::MsgQ::isDataReady()
{
DBPRINT << "MsgQ " << mName << " " << this  << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (mMqd == (mqd_t)-1)
		return false ;

	if (mBlocking)
		return true ;

	// non-blocking receive
	unsigned priority ;
	int numRead = ::mq_receive(mMqd, (char*)&mBuffer[0], (size_t)mMsgSize, &priority);
	if (numRead > 0)
	{
		mBuffer.resize(numRead) ;
		return true ;
	}

	return false ;

}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::MsgQ::sendData(const std::vector<unsigned char>& data, unsigned priority)
{
DBPRINT << "MsgQ " << mName << " " << this  << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (mMqd == (mqd_t)-1)
		return false ;

DUMP_DATA("MsgQ::sendData", data);
	if (::mq_send(mMqd, (char*)&data[0], data.size(), priority) == -1)
        return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::MsgQ::getData(std::vector<unsigned char>& data)
{
DBPRINT << "MsgQ " << mName << " " << this  << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (mMqd == (mqd_t)-1)
		return false ;

	if (mBlocking)
	{
		unsigned priority ;
		int numRead = ::mq_receive(mMqd, (char*)&mBuffer[0], (size_t)mMsgSize, &priority);
//		if (numRead < 0)
//			std::cerr << "MsgQ " << mName << " " << this  << " " << "Error: MsgQ getData - errno=" << errno << std::endl ;
		if (numRead < 0)
			return false ;

DBPRINT	<< "MsgQ " << mName << " " << this  << " Got data " << numRead << " bytes " << std::endl ;
		mBuffer.resize(numRead) ;
	}

	// Non-blocking
	if (mBuffer.empty())
		return false ;

	data.clear() ;
	using std::swap ;
	std::swap(data, mBuffer) ;

    // allocate buffer for next message
    mBuffer.resize(mMsgSize) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::MsgQ::getMaxMsgSize() const
{
DBPRINT << "MsgQ " << mName << " " << this  << " msg size=" << mMsgSize << std::endl ;
	return mMsgSize ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::MsgQ::getName() const
{
	return mName ;
}
