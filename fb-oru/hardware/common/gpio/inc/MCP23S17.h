#ifndef _AA_MCP23S17_H_
#define _AA_MCP23S17_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MCP23S17.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "GlobalTypeDefs.h"

namespace Mplane
{


class MCP23S17
{
public:

	  // Constants
	  static const UINT8 WR_Opcode = 0x40;
	  static const UINT8 RD_Opcode = 0x41;

	  // Memory Map when IOCON.Bank = 0
	  static const UINT8 IODIRA    = 0x00;
	  static const UINT8 IODIRB    = 0x01;
	  static const UINT8 IPOLA     = 0x02;
	  static const UINT8 IPOLB     = 0x03;
	  static const UINT8 GPINTENA  = 0x04;
	  static const UINT8 GPINTENB  = 0x05;
	  static const UINT8 DEFVALA   = 0x06;
	  static const UINT8 DEFVALB   = 0x07;
	  static const UINT8 INTCONA   = 0x08;
	  static const UINT8 INTCONB   = 0x09;
	  static const UINT8 IOCON     = 0x0A;
	  static const UINT8 GPPUA     = 0x0C;
	  static const UINT8 GPPUB     = 0x0D;
	  static const UINT8 INTFA     = 0x0E;
	  static const UINT8 INTFB     = 0x0F;
	  static const UINT8 INTCAPA   = 0x10;
	  static const UINT8 INTCAPB   = 0x11;
	  static const UINT8 GPIOA     = 0x12;
	  static const UINT8 GPIOB     = 0x13;
	  static const UINT8 OLATA     = 0x14;
	  static const UINT8 OLATB     = 0x15;

	  // IOCON fields
	  static const UINT8 IOCON_BANK   = 0x80;
	  static const UINT8 IOCON_MIRROR = 0x40;
	  static const UINT8 IOCON_SEQOP  = 0x20;
	  static const UINT8 IOCON_DISSLW = 0x10;
	  static const UINT8 IOCON_HAEN   = 0x08;
	  static const UINT8 IOCON_ODR    = 0x04;
	  static const UINT8 IOCON_INTPOL = 0x02;

	  // Init values
	  static const UINT8 INIT_PORT_A  = 0x55;
};


}



#endif /* _AA_MCP23S17_H_ */
