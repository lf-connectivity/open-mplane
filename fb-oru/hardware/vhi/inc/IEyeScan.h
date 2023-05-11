/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IEyeScan.h
 * \brief     Virtual interface to the eye scan manager
 *
 *
 * \details   Performs eye scan on a particular fibre
 *
 */


#ifndef IEYESCAN_H_
#define IEYESCAN_H_

#include <memory>
#include "IEyeScanData.h"

namespace Mplane {

class IEyeScan {
public:
	IEyeScan() {}
	virtual ~IEyeScan() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IEyeScan> getInstance() ;

	/**
	 * Callback function used to output a line of text in the scan
	 */
	using ScanOutput = IEyeScanData::ScanOutput ;

	/**
	 * Is scanning supported on this hardware
	 * @return true if hardware capable of doing eye scans
	 */
	virtual bool scanSupported() const =0 ;

	/**
	 * Set up the scanning settings and start scanning
	 * @param fibre		0-based fibre number
	 * @param horizStep
	 * @param vertStep
	 * @param maxPrescale
	 * @param output		Callback function to output a line of text
	 * @return true if started ok
	 */
	virtual bool startScan(unsigned fibre, unsigned horizStep, unsigned vertStep, unsigned maxPrescale, ScanOutput output) =0 ;

	/**
	 * Abort scanning
	 * @return false on error
	 */
	virtual bool stopScan() =0 ;

	/**
	 * Is there a scan currently in progress?
	 */
	virtual bool isScanning() const =0 ;

	/**
	 * Return any errors as a string. Empty string if no errors
	 */
	virtual std::string getError()  const =0 ;


} ;

}

#endif /* IEYESCAN_H_ */
