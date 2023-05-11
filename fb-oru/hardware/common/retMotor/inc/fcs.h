/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      fcs.h
 * \brief     Implements checksum for Aisg protocol
 *
 *
 * \details
 *
 */


#ifndef FCS_H_
#define FCS_H_

namespace Mplane {

class fcs
{
public:

	/*
	* u16 represents an unsigned 16-bit number
	*/
	typedef unsigned short u16;

	static const u16 INITFCS16;		/* Initial FCS value */
	static const u16 GOODFCS16;		/* Good final FCS value */

	/**
	* Method to calculate CRC given the data buffer and the length. If the crc is included in the buffer,
	* then the calculated CRC should be equal to a specific value to verify the frame CRC
	*/
	static u16 fcs16(u16 fcs, unsigned char *cp, int len);
};

}

#endif //FCS_H_
