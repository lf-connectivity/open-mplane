/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBusMonitor.h
 * \brief     A virtual class for monitoring a bus
 *
 *
 * \details   Register this class with an IBus instance and the update methods get called whenever a register write, register read,
 * 				or bytes write/read operation takes place
 *
 */


#ifndef VHI_INC_IBUSMONITOR_H_
#define VHI_INC_IBUSMONITOR_H_

#include <cstdint>
#include <vector>

namespace Mplane {

/*!
 * \class  IBusMonitor
 * \brief
 * \details
 *
 */
class IBusMonitor {
public:
	IBusMonitor() {}
	virtual ~IBusMonitor() {}

	/**
	 * Called by IBus for any register write
	 */
	virtual void updateWrite(uint32_t offset, uint32_t data) =0 ;

	/**
	 * Called by IBus for any bytes write
	 */
	virtual void updateWrite(uint32_t offset, const std::vector<uint8_t>& data) =0 ;

	/**
	 * Called by IBus for any bytes write
	 */
	virtual void updateWrite(const std::vector<uint8_t>& data) =0 ;

	/**
	 * Called by IBus for any register read
	 */
	virtual void updateRead(uint32_t offset, uint32_t data) =0 ;

	/**
	 * Called by IBus for any bytes read
	 */
	virtual void updateRead(uint32_t offset, const std::vector<uint8_t>& data) =0 ;

	/**
	 * Called by IBus for any bytes read
	 */
	virtual void updateRead(const std::vector<uint8_t>& data) =0 ;

} ;

}

#endif /* VHI_INC_IBUSMONITOR_H_ */
