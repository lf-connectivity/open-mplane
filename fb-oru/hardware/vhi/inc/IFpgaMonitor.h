/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaMonitor.h
 * \brief     Interface to fpga register monitor
 *
 *
 * \details   Monitors one or more fpga registers looking for changes. When a register value changes, calls the
 * 			callback function (which typically will connect to a TIF output)
 *
 */


#ifndef IFPGAMONITOR_H_
#define IFPGAMONITOR_H_

#include <ostream>
#include <functional>
#include <memory>

namespace Mplane {

class IFpgaMonitor
{
public:
	IFpgaMonitor() {}
	virtual ~IFpgaMonitor() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IFpgaMonitor> getInstance() ;

	// Callback called on register change
	using RegisterCallback = std::function<void(unsigned address, UINT16 newValue, UINT16 oldValue, UINT16 mask)> ;

	// Callback used for displaying the monitor information. Allows clients to add their own information
	using ShowCallback = std::function<void(std::ostream& os)> ;


	/**
	 * Add a register to be monitored
	 * @param address	FPGA register address to monitor
	 * @param callback	Callback function to call when register value changes
	 * @param mask		Optional mask used to mask out bits that can be ignored (ignored if mask bit = 0)
	 */
	virtual void addRegister(unsigned address, UINT16 mask, RegisterCallback callback, ShowCallback showCallback = ShowCallback()) =0 ;

	/**
	 * Remove a register monitor
	 * @param address
	 * @param mask
	 */
	virtual void delRegister(unsigned address, UINT16 mask) =0 ;

	/**
	 * Display fpga monitors
	 * @param os	Output stream
	 * @param clientTitle	Optional client title appended to the monitor title
	 */
	virtual void show(std::ostream& os, const std::string& clientTitle = std::string("")) =0 ;

} ;

}

#endif /* IFPGAMONITOR_H_ */
