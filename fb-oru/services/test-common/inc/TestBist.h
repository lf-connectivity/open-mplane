/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestBist.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTBIST_H_
#define TESTBIST_H_

#include "IBist.h"

namespace Mplane {

class TestBist : public virtual IBist {
public:
	TestBist() {}
	virtual ~TestBist() {}

	/**
	 * Set reporting rate (in minutes)
	 */
	virtual void setRate(unsigned rateMinutes) override {}

	/**
	 * Get current reporting rate (in minutes)
	 */
	virtual unsigned getRate() const override {return 10;}

	/**
	 * Start reporting
	 */
	virtual void startReporting(IBist::BitReportFunc reportFunc) override {}

	/**
	 * Stop reporting
	 */
	virtual void stopReporting() override {}

	/**
	 * Get the report
	 * @param report
	 */
	virtual void getReport(std::stringstream& report) override {}

} ;

}

#endif /* TESTBIST_H_ */
