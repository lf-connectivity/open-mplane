#ifndef _AA_TCA6416A_H_
#define _AA_TCA6416A_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tca6416a.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "GlobalTypeDefs.h"

namespace Mplane
{


class TCA6416A
{
public:

	  // Command bytes
	  static const UINT8 INPUT_PORT0           = 0x00;
	  static const UINT8 INPUT_PORT1           = 0x01;
	  static const UINT8 OUTPUT_PORT0          = 0x02;
	  static const UINT8 OUTPUT_PORT1          = 0x03;
	  static const UINT8 POLARITY_INVERSION0   = 0x04;
	  static const UINT8 POLARITY_INVERSION1   = 0x05;
	  static const UINT8 CONFIGURATION0        = 0x06;
	  static const UINT8 CONFIGURATION1        = 0x07;

};


}



#endif /* _AA_TCA6416A_H_ */
