/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IEti.h
 * \brief     Virtual interface to elapsed time counter
 *
 *
 * \details   Implements a persistent timer that times the total application up time (ish!)
 *
 */


#ifndef IETI_H_
#define IETI_H_

#include <memory>

namespace Mplane {

class IEti {
public:
	IEti() {}
	virtual ~IEti() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IEti> getInstance() ;

	/**
	 * Set the rate of updates (in seconds)
	 * @param rate
	 * @return
	 */
	virtual bool setUpdateRate(unsigned rate) =0 ;

	/**
	 * Reset the ETI
	 */
	virtual void reset() =0 ;

	/**
	 * Get the update rate (seconds)
	 */
	virtual unsigned getUpdateRate() const =0 ;

	/**
	 * Get the current (live) ETI float value
	 */
	virtual float getElapsedTime() const =0 ;

	/**
	 * Get the last stored ETI float value
	 */
	virtual float getStoredElapsedTime() const =0 ;

	/**
	 * Get the path of the data file used to store the ETI
	 */
	virtual std::string getEtiFilepath() const =0 ;

	/**
	 * Get the path of the backup file used to store the ETI backup data
	 */
	virtual std::string getEtiBackupFilepath() const =0 ;

	/**
	 * Is backup data being used for the ETI - if so then the ETI is not accurate
	 */
	virtual bool isBackupUsed() const =0 ;

	/**
	 * Force an immediate save of the current ETI
	 */
	virtual void saveEti() =0 ;
} ;

}

#endif /* IETI_H_ */
