/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mcp23S17RegModel.cpp
 * \brief     Model of a register set in Mcp23S17
 *
 *
 * \details   Models the register set in Mcp23S17
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Mcp23S17RegModel.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mcp23S17RegModel::Mcp23S17RegModel(const std::string& name, unsigned numAddressBits, unsigned numDataBits, unsigned addressLSB) :
	RegModel(name, numAddressBits, numDataBits, addressLSB)
{
}

//-------------------------------------------------------------------------------------------------------------
Mcp23S17RegModel::~Mcp23S17RegModel()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mcp23S17RegModel::updateModel(uint32_t offset, uint32_t data)
{
	/// Remove the opcode
	offset = offset >> 8;

	/// Check if the address is in range
	if (offset >= numRegs())
	{
		return ;
	}

	/// Add the register data to register cache
	mRegs[offset] = data & dataMask() ;
}
