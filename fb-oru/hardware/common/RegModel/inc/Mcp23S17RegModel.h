/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mcp23S17RegModel.h
 * \brief     Model of a register set in Mcp23S17
 *
 *
 * \details   Models the register set in Mcp23S17
 *
 */


#ifndef INC_MCP23S17_REGMODEL_H_
#define INC_MCP23S17_REGMODEL_H_

#include "RegModel.h"

namespace Mplane {

/*!
 * \class  RegModel
 * \brief
 * \details   Model can be can be updated as an IBus monitor
 *
 */
class Mcp23S17RegModel : public RegModel {
public:
	/**
	 * Create the model with a fixed number of address bits (i.e. fixed known number of registers) and each register
	 * having a fixed data width
	 */
	Mcp23S17RegModel(const std::string& name, unsigned numAddressBits, unsigned numDataBits, unsigned addressLSB) ;
	virtual ~Mcp23S17RegModel() ;

protected:

	virtual void updateModel(uint32_t offset, uint32_t data) override;
} ;

}

#endif /* INC_MCP23S17_REGMODEL_H_ */
