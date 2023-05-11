/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteMsg.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef INC_REMOTEMSG_H_
#define INC_REMOTEMSG_H_


#include <stdint.h>

#if defined __cplusplus
#include <mutex>
extern "C" {
#endif

/* File Operations System call definitions */
#define RMSG_NULL_SYSCALL_ID  0x0U
#define RMSG_OPEN_SYSCALL_ID  0x1U
#define RMSG_CLOSE_SYSCALL_ID 0x2U
#define RMSG_WRITE_SYSCALL_ID 0x3U
#define RMSG_READ_SYSCALL_ID  0x4U
#define RMSG_ACK_STATUS_ID    0x5U
#define RMSG_TERM_SYSCALL_ID  0x6U

#define RMSG_COMMAND_ID       0x8U		// Command from host
#define RMSG_COMMAND_FRAG_ID  0x9U		// Command from host (partial fragment)

// Use MS bit to signify response rather than command
#define RMSG_RESPONSE_ID	  0x80U

// Get id without response bit
#define idValue(id)		(((id) & ~RMSG_RESPONSE_ID) & 0xff)
#define isResponse(id)	( ((id) & RMSG_RESPONSE_ID) == RMSG_RESPONSE_ID )
#define isCommand(id)	( !isResponse(id) && (id == RMSG_COMMAND_ID) )

// Maximum packet length
#ifndef RPMSG_BUFFER_SIZE
#define RPMSG_BUFFER_SIZE	(512U)
#endif
#define RPMSG_HEADER_SIZE	(16U)

// our packet must fit into the RPMSG buffer, which also includes 16 bytes of RPMSG header
#define RMSG_MAX_LEN	(RPMSG_BUFFER_SIZE - RPMSG_HEADER_SIZE)

// constants
#define RMSG_SYNC_BYTES		0x5250
#define RMSG_VER			0x01

// Remote processor message arguments
struct SysCallArgs {
#if defined __cplusplus
	SysCallArgs() :
		int_field1(0),
		int_field2(0),
		data_len(0)
	{}
#endif
	int32_t int_field1;
	int32_t int_field2;
	uint32_t data_len;
	uint8_t data[0]; // a pointer to data_buff
};

// Remote processor message without data
struct RemoteMsgHeader {
#if defined __cplusplus
	RemoteMsgHeader(uint32_t _id) :
		sync(RMSG_SYNC_BYTES),
		ver(RMSG_VER),
		id(_id),
		msg_count(newMsgCount()),
		args()
	{}

	// Construct response from command
	RemoteMsgHeader(const RemoteMsgHeader& rhs) :
		sync(RMSG_SYNC_BYTES),
		ver(RMSG_VER),
		id(rhs.id | RMSG_RESPONSE_ID),
		msg_count(rhs.msg_count),
		args(rhs.args)
	{}

	static uint32_t newMsgCount() ;

	static std::mutex mCountMutex ;
	static uint32_t mCount ;

#endif
	uint16_t sync ; // synchronisation (magic) bytes
	uint8_t ver;	// api version
	uint8_t id;		// command id number
	uint32_t msg_count; // message counter
	struct SysCallArgs	args;
};

/* Remote message data structure */
struct RemoteMsg {
#if defined __cplusplus
	RemoteMsg(uint32_t _id) :
		header(_id),
		data_buff()
	{}
	RemoteMsg() : RemoteMsg(RMSG_NULL_SYSCALL_ID)
	{}
#endif

	struct RemoteMsgHeader header;
	uint8_t data_buff[RMSG_MAX_LEN] ; // NOTE: Not all of this space can be used, just allocate more than enough
};

// this is the max size of the payload data
#define RMSG_MAX_BUFF	(RMSG_MAX_LEN - (unsigned)sizeof(struct RemoteMsgHeader))

#if !defined __cplusplus
/**
 * C function to initialise the structure
 */
extern void init_RemoteMsg(struct RemoteMsg* rmsg, uint32_t id) ;
#endif


#if defined __cplusplus
}
#endif



#endif /* INC_REMOTEMSG_H_ */
