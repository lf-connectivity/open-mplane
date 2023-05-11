/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaCommsConstants.h
 * \brief     FPGA comms constants
 *
 *
 * \details   Header file used both by the uBlaze code and the C++ application
 *
 */

#ifndef IFPGACOMMSCONSTANTS_H_
#define IFPGACOMMSCONSTANTS_H_

#ifdef __cplusplus
extern "C"
{
#endif


/* bit fields */
#define SENDER_RTS_BIT 		0
#define SENDER_SD_BIT  		1
#define RECEIVER_RTR_BIT 	2
#define RECEIVER_RD_BIT  	3

// define the constants PDU header
#define HEADER_LEN   (4)

// Register offsets
#define SENDER_CTRL_OFFSET			0
#define RECEIVER_CTRL_OFFSET		2
#define DATA_OFFSET					4

// Channel 1 pointer control values
// Values used to resync
#define CTRL_RESET_REQ		((short)-2)
#define CTRL_RESET_ACK		((short)-1)
#define CTRL_ACK_TMO		((short)-4)
#define CTRL_RELEASE_TMO	((short)-5)

// Message types
#define TYPE_BYTE_COMMAND 	((unsigned char)'C')
#define TYPE_BYTE_RESPONSE 	((unsigned char)'R')
#define TYPE_BYTE_EVENT 	((unsigned char)'E')
#define TYPE_BYTE_LOG 		((unsigned char)'L')
#define TYPE_BYTE_MATLAB	((unsigned char)'M')
#define TYPE_BYTE_TEXT 		((unsigned char)'T')


#ifdef __cplusplus
}
#endif

#endif /* IFPGACOMMSCONSTANTS_H_ */
