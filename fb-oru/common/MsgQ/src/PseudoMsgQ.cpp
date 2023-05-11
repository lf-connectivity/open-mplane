/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PseudoMsgQ.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <map>

#include "PseudoMsgQ.h"

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
// Message Queue Manager
//=============================================================================================================

struct PseudoMsg {
	PseudoMsg(unsigned _msgSize = 0, PseudoMsgQ* _creator = nullptr) :
		msgSize(_msgSize),
		creator(_creator),
		reader(nullptr),
		writer(nullptr)
	{}

	unsigned msgSize ;
	PseudoMsgQ* creator ;
	PseudoMsgQ* reader ;
	PseudoMsgQ* writer ;
};

//-------------------------------------------------------------------------------------------------------------
class PseudoMsgQ::PseudoMsgMgr {
public:

#ifdef DEBUG_MSQ
#define SHOW_QUEUES()	showQueues()
#else
#define SHOW_QUEUES()
#endif

	/**
	 * Singleton
	 */
	static std::shared_ptr<PseudoMsgQ::PseudoMsgMgr> getInstance() ;

	PseudoMsgMgr() :
		mMgrMutex(),
		mQueues()
	{
	}

	~PseudoMsgMgr() {}

	unsigned getMsgSize(const std::string& name) const
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return 0 ;

		return entry->second.msgSize ;
	}

	bool isCreated(const std::string& name) const
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;
		SHOW_QUEUES() ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return false ;

		return true ;
	}

	void create(const std::string& name, unsigned msgSize, PseudoMsgQ* creator)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry != mQueues.end())
			return ;

		mQueues[name] = PseudoMsg(msgSize, creator) ;

		SHOW_QUEUES() ;
	}

	void close(const std::string& name)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return ;

		mQueues.erase(entry) ;

		SHOW_QUEUES() ;
	}

	bool openWrite(const std::string& name, PseudoMsgQ* writer)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;
		SHOW_QUEUES() ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return false ;

		mQueues[name].writer = writer ;
		SHOW_QUEUES() ;
		return true ;
	}

	bool openRead(const std::string& name, PseudoMsgQ* reader)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;
		SHOW_QUEUES() ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return false ;

		mQueues[name].reader = reader ;
		SHOW_QUEUES() ;

		return true ;
	}

	bool closeWrite(const std::string& name)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;
		SHOW_QUEUES() ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return false ;

		mQueues[name].writer = nullptr ;
		SHOW_QUEUES() ;
		return true ;
	}

	bool closeRead(const std::string& name)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;
		SHOW_QUEUES() ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return false ;

		mQueues[name].reader = nullptr ;
		SHOW_QUEUES() ;
		return true ;
	}

	PseudoMsgQ* getWriter(const std::string& name)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;
		SHOW_QUEUES() ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return nullptr ;

		if (!mQueues[name].writer)
			return mQueues[name].creator ;
		return mQueues[name].writer ;
	}

	PseudoMsgQ* getReader(const std::string& name)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;
		SHOW_QUEUES() ;

		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return nullptr ;

		if (!mQueues[name].reader)
			return mQueues[name].creator ;
		return mQueues[name].reader ;
	}


	void sendData(PseudoMsgQ* sender, const std::string& name, const std::vector<unsigned char>& data)
	{
		DBPRINT << "PMsgMgr " << this << " " << __func__ << " " << name << std::endl ;
		SHOW_QUEUES() ;

		// Only send data if there is a reader attached
		Mutex::Lock lock(mMgrMutex) ;
		auto entry(mQueues.find(name)) ;
		if (entry == mQueues.end())
			return ;

		PseudoMsgQ* reader(mQueues[name].reader ? mQueues[name].reader : mQueues[name].creator) ;
		if (!reader || (reader == sender) )
			return ;


		// Got a reader so we can transfer the data directly
		DUMP_DATA(name+" TX:", data) ;
		reader->transferData(data) ;
	}



#ifdef DEBUG_MSQ
private:
	void showQueues(void) const
	{
		std::cerr << "-- Queues ---" << std::endl ;
		for (auto q : mQueues)
		{
			std::cerr << q.first << " :" <<
				" creator=" << q.second.creator <<
				" writer=" << q.second.writer <<
				" reader=" << q.second.reader <<
				std::endl ;
		}
		std::cerr << "-------------" << std::endl << std::endl ;
	}
#endif

private:
	mutable Mutex mMgrMutex ;
	std::map<std::string, PseudoMsg> mQueues ;
};

std::shared_ptr<PseudoMsgQ::PseudoMsgMgr> PseudoMsgQ::PseudoMsgMgr::getInstance()
{
	static std::shared_ptr<PseudoMsgQ::PseudoMsgMgr> instance(
		std::make_shared<PseudoMsgQ::PseudoMsgMgr>()
	) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PseudoMsgQ::PseudoMsgQ(const std::string& name) :
	mName(name),
	mMutex(),
	mCond(),
	mCreator(false),
	mConnected(false),
	mWriter(false),
	mBlocking(true),
	mBuffer(),
	mMsgMgr(PseudoMsgMgr::getInstance())
{
}

//-------------------------------------------------------------------------------------------------------------
PseudoMsgQ::~PseudoMsgQ()
{
	close() ;
}

//-------------------------------------------------------------------------------------------------------------
bool PseudoMsgQ::create(unsigned msgSize, unsigned maxMsgs)
{
DBPRINT << "PMsgQ " << mName << " " << this << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	mMsgMgr->create(mName, msgSize, this) ;

	mCreator = true ;
	mConnected = true ;

DBPRINT << "PMsgQ " << mName << " " << this << " CREAT" << std::endl ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool PseudoMsgQ::connectRead(bool blocking)
{
DBPRINT << "PMsgQ " << mName << " " << this  << " " << __func__ << std::endl ;

	{
	DBPRINT << "PMsgQ " << mName << " " << this  << " connectRead() mutex LOCK @ " << (void*)&mMutex << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (!mMsgMgr->isCreated(mName))
		return false ;

	mBlocking = blocking ;

DBPRINT << "PMsgQ " << mName << " " << this << " open RDONLY" << std::endl ;

	mConnected = true ;
	mWriter = false ;
	DBPRINT << "PMsgQ " << mName << " " << this  << " connectRead() mutex UNLOCK @ " << (void*)&mMutex << std::endl ;
	}

	mMsgMgr->openRead(mName, this) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool PseudoMsgQ::connectWrite(bool blocking)
{
DBPRINT << "PMsgQ " << mName << " " << this  << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (!mMsgMgr->isCreated(mName))
		return false ;

	mBlocking = blocking ;

DBPRINT << "PMsgQ " << mName << " " << this << " open WRONLY" << std::endl ;

	mConnected = true ;
	mWriter = true ;

	mMsgMgr->openWrite(mName, this) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool PseudoMsgQ::close()
{
DBPRINT << "PMsgQ " << mName << " " << this << " close" << std::endl ;

	if (mConnected)
	{
		if (mWriter)
			mMsgMgr->closeWrite(mName) ;
		else
			mMsgMgr->closeRead(mName) ;
	}
	mConnected = false ;

	if (mCreator)
	{
		// Creator responsible for closing "queue" down
		mMsgMgr->close(mName) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool PseudoMsgQ::isDataReady()
{
//DBPRINT << "PMsgQ " << mName << " " << this  << " " << __func__ << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (!mConnected)
		return false ;
	if (mWriter)
		return false ;

	if (mBlocking)
		return true ;

	// non-blocking receive
//	return !mBuffer.empty() ;
	if (mBuffer.empty())
		return false ;

	DBPRINT << "PMsgQ " << mName << " " << this  << " " << __func__ << " Data READY"<< std::endl ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool PseudoMsgQ::getData(std::vector<unsigned char>& data)
{

DBPRINT << "PMsgQ " << mName << " " << this  << " " << __func__ << std::endl ;

	bool blocking(false) ;
	{
DBPRINT << "PMsgQ " << mName << " " << this  << " getData() mutex LOCK @ " << (void*)&mMutex << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (!mConnected)
		return false ;
	if (mWriter)
		return false ;

	blocking = mBlocking ;
	}
DBPRINT << "PMsgQ " << mName << " " << this  << " getData() mutex UNLOCK @ " << (void*)&mMutex << std::endl ;

	if (blocking)
	{
		while( mBuffer.empty() )
		{
			DBPRINT	<< "PMsgQ " << mName << " " << this  << " wait for data " << " buffer size= " << mBuffer.size() << std::endl ;
			mCond.wait();
		}
	}

	DBPRINT << "PMsgQ " << mName << " " << this  << " getData() mutex LOCK @ " << (void*)&mMutex << std::endl ;
	Mutex::Lock lock(mMutex) ;

	// Non-blocking
	if (mBuffer.empty())
		return false ;

	data = mBuffer.front() ;
	mBuffer.pop() ;
	DBPRINT	<< "PMsgQ " << mName << " " << this  << " Got data " << data.size() << " bytes, buffer size= " << mBuffer.size() << std::endl ;
	DUMP_DATA(mName+" RX:", data) ;

	DBPRINT << "PMsgQ " << mName << " " << this  << " getData() mutex UNLOCK @ " << (void*)&mMutex << std::endl ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool PseudoMsgQ::sendData(const std::vector<unsigned char>& data, unsigned priority)
{
DBPRINT << "PMsgQ " << mName << " " << this  << " " << __func__ << std::endl ;
DBPRINT << "PMsgQ " << mName << " " << this  << " sendData() mutex LOCK @ " << (void*)&mMutex << std::endl ;
	Mutex::Lock lock(mMutex) ;

	if (!mConnected)
	{
		DBPRINT << "PMsgQ " << mName << " " << this  << " sendData() mutex UNLOCK @ " << (void*)&mMutex << std::endl ;
		return false ;
	}
	if (!mWriter && !mCreator)
	{
		DBPRINT << "PMsgQ " << mName << " " << this  << " sendData() mutex UNLOCK @ " << (void*)&mMutex << std::endl ;
		return false ;
	}

	// transfer the data
	mMsgMgr->sendData(this, mName, data) ;

DBPRINT << "PMsgQ " << mName << " " << this  << " sendData() mutex UNLOCK @ " << (void*)&mMutex << std::endl ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned PseudoMsgQ::getMaxMsgSize() const
{
	unsigned msgSize(mMsgMgr->getMsgSize(mName)) ;
DBPRINT << "PMsgQ " << mName << " " << this  << " msg size=" << msgSize << std::endl ;
	return msgSize ;
}

//-------------------------------------------------------------------------------------------------------------
std::string PseudoMsgQ::getName() const
{
	return mName ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool PseudoMsgQ::transferData(const std::vector<unsigned char>& data)
{
	DBPRINT << "PMsgQ " << mName << " " << this  << " transferData() size=" << data.size() << " buffer size=" << mBuffer.size() << std::endl ;

	// This is the reader being sent data from a writer
	bool blocking(false) ;
	{
DBPRINT << "PMsgQ " << mName << " " << this  << " transferData() mutex LOCK @ " << (void*)&mMutex << std::endl ;
	Mutex::Lock mlock(mMutex) ;
	mBuffer.push(data) ;
	blocking = mBlocking ;
DBPRINT << "PMsgQ " << mName << " " << this  << " transferData() mutex UNLOCK @ " << (void*)&mMutex << std::endl ;
	}
DBPRINT << "PMsgQ " << mName << " " << this  << " transferData() blocking=" << blocking << std::endl ;

	if (blocking)
	{
	DBPRINT << "PMsgQ " << mName << " " << this  << " transferData() cond LOCK @ " << (void*)&mCond << std::endl ;
	Conditional::Lock lock( mCond );
	mCond.signal();
	DBPRINT << "PMsgQ " << mName << " " << this  << " transferData() cond UNLOCK @ " << (void*)&mCond << std::endl ;
	}

	DBPRINT << "PMsgQ " << mName << " " << this  << " transferData() - END" << " buffer size=" << mBuffer.size()  << std::endl ;
	return true ;
}
