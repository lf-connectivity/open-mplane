/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBist.h
 * \brief     Virtual interface to BIST service
 *
 *
 * \details
 *
 */


#ifndef IBIST_H_
#define IBIST_H_

#include <functional>
#include <memory>
#include <string>
#include <sstream>

namespace Mplane {

class IBist {
public:
	IBist() {}
	virtual ~IBist() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IBist> getInstance() ;

	/**
	 * Report callback used to send out report - returns true on successfully sending report
	 */
	using BitReportFunc = std::function<bool(const std::string& report)> ;

	/**
	 * Set reporting rate (in minutes)
	 */
	virtual void setRate(unsigned rateMinutes) =0 ;

	/**
	 * Get current reporting rate (in minutes)
	 */
	virtual unsigned getRate() const =0 ;

	/**
	 * Start reporting
	 */
	virtual void startReporting(BitReportFunc reportFunc) =0 ;

	/**
	 * Stop reporting
	 */
	virtual void stopReporting() =0 ;

	/**
	 * Get the report
	 * @param report
	 */
	virtual void getReport(std::stringstream& report) =0 ;



} ;

}

#endif /* IBIST_H_ */
