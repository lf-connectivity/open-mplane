/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IEyeScanData.h
 * \brief     Virtual interface to data class
 *
 *
 * \details
 *
 */


#ifndef IEYESCANDATA_H_
#define IEYESCANDATA_H_

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include "GlobalTypeDefs.h"

namespace Mplane {

class IEyeScanData {
public:
	IEyeScanData() {}
	virtual ~IEyeScanData() {}

	/**
	 * Callback function used to output a line of text in the scan
	 */
	using ScanOutput = std::function<void(const std::string& line)> ;

	/**
	 * Set the function used by the data class to output itself
	 * @param output
	 */
	virtual void setOutputFunc(ScanOutput output) =0 ;

	/**
	 * Add the next data point
	 * @param data
	 * @return true if end of data
	 */
	virtual bool addData(UINT32 data) =0 ;

	/**
	 * Add data from a vector
	 * @param data
	 * @return true if end of data
	 */
	virtual bool addData(std::vector<UINT32> data) =0 ;

	/**
	 * Clear out all data
	 */
	virtual void clear() =0 ;

	/**
	 * Dump contents using the ScanOutput function
	 */
	virtual void output() =0 ;

	/**
	 * Get any errors as a string message
	 */
	virtual std::string getError() const =0 ;

	/**
	 * Information about the data
	 */
	struct ScanInfo {
		unsigned numSamples ;
		int vertStep ;
		int vertMin ;
		int vertMax ;
		int horizStep ;
		int horizMin ;
		int horizMax ;
		bool lpmMode ;
	};
	virtual ScanInfo getInfo() const =0 ;


} ;

}

#endif /* IEYESCANDATA_H_ */
