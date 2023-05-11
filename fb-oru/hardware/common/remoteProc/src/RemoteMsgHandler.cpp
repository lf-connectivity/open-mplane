/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteMsgHandler.cpp
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
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#include "ByteTransfer.hpp"

#include "RemoteProc.h"
#include "RpmsgMgr.h"
#include "RemoteMsg.h"

#include "RemoteMsgHandler.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned READ_TIMEOUT_MS(500) ;

/* "Initialization message" - this is really just junk used to start up the comms. The remote end will just
 *  ignore it
 */
#define RMSG_INIT_MSG	"init_msg"

#define DEBUG_RMSG
#ifdef DEBUG_RMSG
#define RMSG_COUT	std::cerr
#else
#define RMSG_COUT	if (false) std::cerr
#endif

//=============================================================================================================
// LOCAL
//=============================================================================================================
#ifdef DEBUG_RMSG
//-------------------------------------------------------------------------------------------------------------
namespace {
	//-------------------------------------------------------------------------------------------------------------
	static void dumpRemoteMsgData(int i, struct RemoteMsg* rmsg)
	{
		printf("    ") ;
		int j ;
		for (j = i-15; j <= i; ++j)
		{
			if (isprint(rmsg->data_buff[j]))
				printf("%c", rmsg->data_buff[j]) ;
			else
				printf(".") ;
		}
		printf("\r\n") ;
	}


	//-------------------------------------------------------------------------------------------------------------
	void dumpRemoteMsg(struct RemoteMsg* rmsg)
	{
		printf("-- RemoteMsg --------------------------------\r\n");
		printf("sync..............: 0x%04x\r\n", rmsg->header.sync) ;
		printf("ver...............: 0x%02x\r\n", rmsg->header.ver) ;
		printf("id................: 0x%02x\r\n", rmsg->header.id) ;
		printf("msg count.........: %u\r\n", rmsg->header.msg_count) ;
		printf("args.int_field1...: %d\r\n", rmsg->header.args.int_field1) ;
		printf("args.int_field2...: %d\r\n", rmsg->header.args.int_field2) ;
		printf("args.data_len.....: %d\r\n", rmsg->header.args.data_len) ;
		printf("args.data:\r\n") ;

		int i ;
		for (i=0; i < (int)rmsg->header.args.data_len; ++i)
		{
			if (i % 16 == 0)
				printf("%03x: ", i) ;

			printf("%02x ", rmsg->data_buff[i]) ;

			if (i % 16 == 15)
			{
				dumpRemoteMsgData(i, rmsg) ;
			}
		}

		for (; i <= 15; ++i)
		{
			printf("   ") ;

			if (i % 16 == 15)
			{
				dumpRemoteMsgData(i, rmsg) ;
			}
		}
		printf("\r\n---------------------------------------------\r\n");
	}

}
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RemoteMsgHandler::RemoteMsgHandler(unsigned index, std::shared_ptr<IFpgaMsgTokens> tokens) :
	RemoteMsgHandlerBase(index, tokens),
	mRpmsgMgr( RpmsgMgr::singleton() ),
	mProc( std::make_shared<RemoteProc>(index) ),
	mFd(-1),
	mPipeWrFd(-1),
	mPipeRdFd(-1),
	mMsgMutex(),
	mRpc(),
	mRpcResponse(),
	mCmd(),
	mCmdReply(),
	mGotReply(false)
{
	RMSG_COUT << std::endl << "NEW RemoteMsgHandler @ " << this << std::endl ;

	// Block SIGPIPE signal so we can handle it via errno
	sigset_t blockSet, prevSet ;
	::sigemptyset(&blockSet) ;
	::sigaddset(&blockSet, SIGPIPE) ;
	::sigprocmask(SIG_BLOCK, &blockSet, &prevSet) ;

	// open a pipe
	int filedes[2] ;
	if (::pipe(filedes) != 0)
	{
		return ;
	}

	mPipeRdFd = filedes[0] ;
	mPipeWrFd = filedes[1] ;

}

//-------------------------------------------------------------------------------------------------------------
RemoteMsgHandler::~RemoteMsgHandler()
{
	RMSG_COUT << std::endl << "DEL RemoteMsgHandler @ " << this << std::endl ;
	disconnect() ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::connect(const std::string &firmware)
{
	RMSG_COUT  << std::endl << "RemoteMsgHandler::connect(" << firmware << ")" << std::endl ;

	if (mFd > 0)
		return setError("Already connected") ;

	// notify the rpmsg manager that the device is going to be started
	RMSG_COUT  << std::endl << "RemoteMsgHandler::connect() add device..." << std::endl ;
	mRpmsgMgr->addingDevice(index()) ;

	// load the firmware and start the processor
	RMSG_COUT << std::endl << "RemoteMsgHandler::connect() load firmware..." << std::endl ;
	if (!mProc->loadFirmware(firmware))
	{
		RMSG_COUT << std::endl << "RemoteMsgHandler::connect() failed to load firmware" << std::endl ;
		return setError("Failed to load firmware") ;
	}

	// ensure the rpmsg device is started
	RMSG_COUT  << std::endl << "RemoteMsgHandler::connect() add device..." << std::endl ;
	mRpmsgMgr->addDevice(index()) ;

	// Open proxy rpmsg device
	std::string rpmsgDev(mRpmsgMgr->getDevice(index())) ;
	for (unsigned retry=1; retry <= 2; ++retry)
	{
		RMSG_COUT  << std::endl << "RemoteMsgHandler::connect() open device '" << rpmsgDev << "'... " << retry << std::endl ;
		mFd = open(rpmsgDev.c_str(), O_RDWR) ;
		if (mFd > 0)
			break ;

		sleep(1) ;
	}

	RMSG_COUT << std::endl << "RemoteMsgHandler::connect() open device fd=" << mFd << std::endl ;
	if (mFd < 0)
	{
		RMSG_COUT << "RemoteMsgHandler: Error unable to open rpmsg device" << std::endl ;
		return setError("Unable to open rpmsg device") ;
	}

	// start - effectively sends gibberish that is ignored at the remote end. Just ensures that the link is up
	RMSG_COUT << std::endl << "RemoteMsgHandler::connect() send init..." << std::endl ;
	int ret = ::write(mFd, RMSG_INIT_MSG, sizeof(RMSG_INIT_MSG));
	if (ret < 0)
	{
		RMSG_COUT << "RemoteMsgHandler: Failed to send init message" << std::endl ;
		disconnect() ;
		return setError("Failed to send init message") ;
	}

	RMSG_COUT << std::endl << "RemoteMsgHandler::connect() - DONE" << std::endl ;

	setActive(true) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::disconnect()
{
RMSG_COUT  << std::endl << "RemoteMsgHandler::disconnect() - START" << std::endl ;
	setActive(false) ;

	// send junk down pipe to exit read/select
	if (mPipeWrFd > 0)
	{
		char buff[8] = {0,0,0,0,0,0,0,0} ;
		::write(mPipeWrFd, buff, 1) ;

		close(mPipeWrFd) ;
		mPipeWrFd = -1 ;
	}
	if (mPipeRdFd > 0)
	{
		close(mPipeRdFd) ;
		mPipeRdFd = -1 ;
	}


	// disconnect from the device driver so that we can unload it
	if (mFd > 0)
		close(mFd) ;

	// stop the processor
	mProc->stop() ;
//	sleep(1) ;

	// unload the device if we've finished with it
RMSG_COUT  << std::endl << "RemoteMsgHandler::disconnect() - unload device.." << std::endl ;
	mRpmsgMgr->delDevice(index()) ;

	mFd = -1 ;

RMSG_COUT  << std::endl << "RemoteMsgHandler::disconnect() - DONE" << std::endl ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::sendCommand(const std::string &cmd,
		const std::vector<DataVariant> &attributes,
		const std::set<std::string> &varNames,
		std::vector<DataVariant> &replyAttributes,
		unsigned timeoutMs)
{
	if (!isActive() || !isEventLoop())
		return setError("Event loop inactive") ;

	// TODO: split long command into multiple fragments

	replyAttributes.clear() ;
	std::vector<uint8_t> pduBytes( cmdBytes(cmd, attributes, varNames) ) ;
	unsigned len(pduBytes.size()) ;
	if (len >= RMSG_MAX_BUFF)
		len = RMSG_MAX_BUFF ;

	/* Construct remote command */
	{
	std::unique_lock<std::mutex> lock(mMsgMutex) ;
	mCmd = RemoteMsg(RMSG_COMMAND_ID) ;
	mCmdReply = RemoteMsg(RMSG_NULL_SYSCALL_ID) ;
	memcpy(mCmd.data_buff, &pduBytes[0], len) ;
	mCmd.header.args.data_len = len ;
	pduBytes.clear() ;
	mGotReply = false ;
	}

	size_t payload_size = sizeof(RemoteMsgHeader) + len ;

RMSG_COUT << std::endl << "RemoteMsgHandler::sendCommand() * cmd bytes=" << len << " header=" << sizeof(RemoteMsgHeader) << " payload_size=" << payload_size <<	std::endl ;

	/* Transmit rpc response */
	ssize_t bytes_written = ::write(mFd, (void*)&mCmd, payload_size);

RMSG_COUT << std::endl << "RemoteMsgHandler::sendCommand() * DONE write=" << bytes_written << " payload_size=" << payload_size << std::endl ;
	if (bytes_written != (ssize_t)payload_size)
		return setError("Failed to send payload") ;

	// Get response until timeout or got a response
//	while ( !mGotReply )
//	{
//		// timing out here counts as failure
//		bool timedOut(true) ;
//		bool rc = this->read(timeoutMs, timedOut) ;
//		if (timedOut)
//			return false ;
//		return rc ;
//	}

	while (!mGotReply)
	{
		std::unique_lock<std::mutex> lock(mMsgMutex) ;
		if (mReplyCv.wait_for(lock, std::chrono::milliseconds(timeoutMs)) == std::cv_status::timeout)
		{
std::cerr << "Timed out " << timeoutMs << " ms" << std::endl ;
			return setError("Timed out waiting for reply") ;
		}
	}

	// convert command reply
	{
	std::unique_lock<std::mutex> lock(mMsgMutex) ;
	reply(mCmdReply.data_buff, mCmdReply.header.args.data_len, replyAttributes) ;
	mGotReply = false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::procSetState(bool start)
{
	if ( mProc->setState(start) )
		return true ;

	return setError(mProc->error()) ;
}

//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandler::procState()
{
	return static_cast<int>( mProc->state() ) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::processRpc()
{
	errno = 0 ;
	RMSG_COUT << std::endl << "RemoteMsgHandler::processRpc() id=" << (int)mRpc.header.id << std::endl ;

	bool ok(false) ;

	if (isResponse(mRpc.header.id))
	{
		std::unique_lock<std::mutex> lock(mMsgMutex) ;
		RMSG_COUT << std::endl << "RemoteMsgHandler::processRpc() * response id " << mRpc.header.id << std::endl ;
		mCmdReply = RemoteMsg(mRpc) ;
		mGotReply = true ;
		mReplyCv.notify_all() ;
		return true ;
	}

	/* Handle RPC */
	switch ((int)(mRpc.header.id))
	{
		case RMSG_OPEN_SYSCALL_ID:
		{
			ok = handleOpen();
			break;
		}
		case RMSG_CLOSE_SYSCALL_ID:
		{
			ok = handleClose();
			break;
		}
		case RMSG_READ_SYSCALL_ID:
		{
			ok = handleRead();
			break;
		}
		case RMSG_WRITE_SYSCALL_ID:
		{
			ok = handleWrite();
			break;
		}
		case RMSG_TERM_SYSCALL_ID:
		{
			setActive(false) ;
			ok = true;
			break;
		}

		case RMSG_NULL_SYSCALL_ID:
		default:
		{
			std::cerr << "RemoteMsgHandler: Error invalid RPC sys call ID: " << mRpc.header.id << std::endl ;
			ok = false;
			break;
		}
	}

	RMSG_COUT << std::endl << "RemoteMsgHandler::processRpc() - DONE ok=" << ok << std::endl ;
	return ok;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::handleOpen()
{
	errno = 0 ;
	RMSG_COUT << std::endl << "RemoteMsgHandler::handleOpen() '" << mRpc.header.args.data << "' arg1=" << mRpc.header.args.int_field1 << " arg2=" << mRpc.header.args.int_field2 << std::endl ;

	/* Open host fd */
	std::shared_ptr<IHostFileMgr> mgr(fileMgr()) ;
	int fd = mgr->open((char *)mRpc.header.args.data, mRpc.header.args.int_field1,
			mRpc.header.args.int_field2);

	RMSG_COUT << "RemoteMsgHandler::handleOpen() * fd=" << fd << " errno=" << errno << std::endl ;

	/* Construct rpc response */
	mRpcResponse = RemoteMsg(mRpc) ;
	mRpcResponse.header.args.int_field1 = fd;
	mRpcResponse.header.args.int_field2 = 0; /*not used*/
	mRpcResponse.header.args.data_len = 0; /*not used*/

	/* Transmit rpc response */
	ssize_t bytes_written = ::write(mFd, (void*)&mRpcResponse, sizeof(RemoteMsgHeader));

	RMSG_COUT << std::endl << "RemoteMsgHandler::handleOpen() * DONE write=" << bytes_written << " header=" << sizeof(RemoteMsgHeader) << std::endl ;
	return (bytes_written == sizeof(RemoteMsgHeader));
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::handleClose()
{
	errno = 0 ;
	RMSG_COUT << std::endl << "RemoteMsgHandler::handleClose()" << " arg1=" << mRpc.header.args.int_field1 << std::endl ;

	/* Close host fd */
	std::shared_ptr<IHostFileMgr> mgr(fileMgr()) ;
	int retval = mgr->close(mRpc.header.args.int_field1);

	RMSG_COUT << std::endl << "RemoteMsgHandler::handleClose() * ret=" << retval << " errno=" << errno << std::endl ;

	/* Construct rpc response */
	mRpcResponse = RemoteMsg(mRpc) ;
	mRpcResponse.header.args.int_field1 = retval;
	mRpcResponse.header.args.int_field2 = 0; /*not used*/
	mRpcResponse.header.args.data_len = 0; /*not used*/

	/* Transmit rpc response */
	ssize_t bytes_written = ::write(mFd, (void*)&mRpcResponse, sizeof(RemoteMsgHeader));

	RMSG_COUT << std::endl << "RemoteMsgHandler::handleClose() * DONE write=" << bytes_written << " header=" << sizeof(RemoteMsgHeader) << " errno=" << errno << std::endl ;

	return (bytes_written == sizeof(RemoteMsgHeader)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::handleWrite()
{
	errno = 0 ;
	RMSG_COUT << std::endl << "RemoteMsgHandler::handleWrite()" << " arg1=" << mRpc.header.args.int_field1 << " arg2=" << mRpc.header.args.int_field2 << std::endl ;


	/* Write to host fd */
	std::shared_ptr<IHostFileMgr> mgr(fileMgr()) ;
	ssize_t bytes_written = mgr->write(mRpc.header.args.int_field1,
				(const uint8_t*)mRpc.header.args.data,
				mRpc.header.args.int_field2);

	RMSG_COUT << std::endl << "RemoteMsgHandler::handleWrite() * ret=" << bytes_written << " errno=" << errno << std::endl ;


	/* Construct rpc response */
	mRpcResponse = RemoteMsg(mRpc) ;
	mRpcResponse.header.args.int_field1 = bytes_written;
	mRpcResponse.header.args.int_field2 = 0; /*not used*/
	mRpcResponse.header.args.data_len = 0; /*not used*/

	/* Transmit rpc response */
	bytes_written = ::write(mFd, (void*)&mRpcResponse, sizeof(RemoteMsgHeader));

	RMSG_COUT << std::endl << "RemoteMsgHandler::handleWrite() * DONE write=" << bytes_written << " header=" << sizeof(RemoteMsgHeader) << " errno=" << errno << std::endl ;

	return (bytes_written == sizeof(RemoteMsgHeader));
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::handleRead()
{
	errno = 0 ;
	RMSG_COUT << std::endl << "RemoteMsgHandler::handleRead()" << " arg1=" << mRpc.header.args.int_field1 << " arg2=" << mRpc.header.args.int_field2 << std::endl ;

	ssize_t bytes_read ;
	mRpcResponse = RemoteMsg(mRpc) ;

	std::shared_ptr<IHostFileMgr> mgr(fileMgr()) ;

	if (mRpc.header.args.int_field1 == STDIN_FILENO)
	{
		/* Perform read from fd for large size since this is a
		STD/I request */
		bytes_read = mgr->read(mRpc.header.args.int_field1, (uint8_t *)mRpcResponse.data_buff, RMSG_MAX_BUFF);
	}
	else
	{
		/* Perform read from fd */
		int bytes_to_read = mRpc.header.args.int_field2 ;
		if (bytes_to_read > (int)RMSG_MAX_BUFF)
			bytes_to_read = RMSG_MAX_BUFF ;
		bytes_read = mgr->read(mRpc.header.args.int_field1, (uint8_t *)mRpcResponse.data_buff, bytes_to_read);
	}

	/* Construct rpc response */
	mRpcResponse.header.args.int_field1 = bytes_read;
	mRpcResponse.header.args.int_field2 = 0; /* not used */
	mRpcResponse.header.args.data_len = bytes_read;

#ifdef DEBUG_RMSG
	dumpRemoteMsg(&mRpcResponse) ;
#endif

	size_t payload_size = sizeof(RemoteMsgHeader) + ((bytes_read > 0) ? bytes_read : 0);

	RMSG_COUT << std::endl << "RemoteMsgHandler::handleRead() * bytes read=" << bytes_read << " header=" << sizeof(RemoteMsgHeader) << " payload_size=" << payload_size << " errno=" << errno << std::endl ;

	/* Transmit rpc response */
	ssize_t bytes_written = ::write(mFd, (void*)&mRpcResponse, payload_size);

	RMSG_COUT << std::endl << "RemoteMsgHandler::handleRead() * DONE write=" << bytes_written << " payload_size=" << payload_size << std::endl ;
	return (bytes_written == (ssize_t)payload_size) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandler::read(unsigned timeoutMs, bool& timedOut)
{
	timedOut = false ;

//	RMSG_COUT << std::endl << "== RemoteMsgHandler: read... =========" << std::endl ;

	struct timeval tval ;
	struct timeval* tvalp(nullptr) ;
	if (timeoutMs > 0)
	{
		unsigned secs(timeoutMs / 1000) ;
		unsigned msecs(timeoutMs - (secs*1000)) ;
		unsigned usecs(msecs * 1000) ;
		tval.tv_sec = secs ;
		tval.tv_usec = usecs ;
		tvalp = &tval ;
	}

	int nfds = 0 ;
	fd_set fds ;
	FD_ZERO(&fds) ;

	FD_SET(mFd, &fds) ;
	if (mFd >= nfds)
		nfds = mFd + 1 ;
	FD_SET(mPipeRdFd, &fds) ;
	if (mPipeRdFd >= nfds)
		nfds = mPipeRdFd + 1 ;

//		std::cerr << "select... @ " << this << " : DevFd=" << mDevFd << " mReadFd=" << mReadFd << std::endl ;
	int rc = ::select(nfds, &fds, NULL, NULL, tvalp) ;
	if (rc < 0)
	{
//			std::cerr << "select error errno=" << errno << std::endl ;
		return 1 ;
	}

	// timeout
	if (rc == 0)
	{
		timedOut = true ;
		return true ;
	}

	// check to see if we're still active before continuing
	if (!isActive())
		return false ;

	// did we exit because of timeout or pipe write
	if (!FD_ISSET(mFd, &fds))
		return false ;

	// ok to get the data
	int bytes_rcvd = ::read(mFd, (void*)&mRpc, sizeof(mRpc));

#ifdef DEBUG_RMSG
	{
	std::cerr << std::endl << "RemoteMsgHandler: read got " << bytes_rcvd << " bytes" << std::endl ;
	const char *cp = (char *)&mRpc ;
	std::string str(bytes_rcvd, ' ') ;
	for (int i=0; i < bytes_rcvd; ++i) str[i] = *cp++ ;
	ByteTransfer::dump(str) ;
	}
#endif

	if ( (bytes_rcvd < 0) && (bytes_rcvd != -EAGAIN) )
		return true;

	/* Handle rpc */
	if (processRpc())
		return true ;

	// error
	std::cerr << "RemoteMsgHandler: Error handling remote procedure call" << std::endl ;
	std::cerr << "  RPC id " << mRpc.header.id << std::endl ;
	std::cerr << "  arg1 " << mRpc.header.args.int_field1 << std::endl ;
	std::cerr << "  arg2 " << mRpc.header.args.int_field2 << std::endl ;

	return false ;
}
//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandler::fd()
{
	return mFd ;
}

//=============================================================================================================
// PROTECTED THREAD
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandler::eventLoopFunc()
{
//std::cerr << "RemoteMsgHandler::eventLoopFunc() - START" << std::endl ;

	bool timedOut(true) ;
	while ( isEventLoop() && isActive() && timedOut )
	{
		// keep trying to read while we time out
		bool rc = this->read(READ_TIMEOUT_MS, timedOut) ;
		if (timedOut)
			continue ;

		// not timeout, so return state
		//std::cerr << "RemoteMsgHandler::eventLoopFunc() - EXIT rc=" << rc << std::endl ;
		return rc ? -1 : 0 ;
	}

//std::cerr << "RemoteMsgHandler::eventLoopFunc() - END isEventLoop=" << isEventLoop() << " isActive=" << isActive() << " timedOut=" << timedOut << std::endl ;
	return 0 ;
}
