/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaTxVVABus.cpp
 * \brief     Bus interface to the Tx VVA via the FPGA
 *
 *
 * \details   Bus interface to the Tx VVA via the FPGA
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <iostream>
#include "FpgaTxVVABus.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaTxVVABus::FpgaTxVVABus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings, unsigned index) :
		Bus(busName, busDetails, busLock, busSettings),
		mFpga(IFpgaMgr::getIFpgaAntennaRegs()),
		mIndex( index )
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaTxVVABus::~FpgaTxVVABus()
{
}


//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool FpgaTxVVABus::doWriteShort(uint32_t offset, uint16_t val)
{
	/// Set the attenuation value
	mFpga->write_txVattenRaw(mIndex, val);

	return true;
}
