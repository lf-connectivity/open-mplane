/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestEti.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTETI_H_
#define TESTETI_H_

#include "IEti.h"

namespace Mplane {

class TestEti : public virtual IEti {
public:
	TestEti() {}
	virtual ~TestEti() {}

	/**
	 * Set the rate of updates (in seconds)
	 * @param rate
	 * @return
	 */
	virtual bool setUpdateRate(unsigned rate) override {return true;}

	/**
	 * Reset the ETI
	 */
	virtual void reset() override {}

	/**
	 * Get the update rate (seconds)
	 */
	virtual unsigned getUpdateRate() const override {return 600;}

	/**
	 * Get ETI float value
	 */
	virtual float getElapsedTime() const override {return 0.0;}

	/**
	 * Get the last stored ETI float value
	 */
	virtual float getStoredElapsedTime() const override {return 0.0;}

	/**
	 * Get the path of the data file used to store the ETI
	 */
	virtual std::string getEtiFilepath() const override {return "";}

	/**
	 * Get the path of the backup file used to store the ETI backup data
	 */
	virtual std::string getEtiBackupFilepath() const override {return "";}

	/**
	 * Is backup data being used for the ETI - if so then the ETI is not accurate
	 */
	virtual bool isBackupUsed() const override {return false;}

	/**
	 * Force an immediate save of the current ETI
	 */
	virtual void saveEti() override {}

} ;

}

#endif /* TESTETI_H_ */
