/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IXcorrManager.h
 * \brief     Interface to cross correlation management
 *
 *
 * \details   Handles all of the hardware interfacing (writing to fpga registers) etc for cross correlation
 *
 */


#ifndef IXCORRMANAGER_H_
#define IXCORRMANAGER_H_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

#include "IFileMgr.h"

namespace Mplane {

class IXcorrManager {
public:
	/**
	 * Singleton factory
	 * @return pointer to the single instance of the Waveform Manager
	 */
	static std::shared_ptr<IXcorrManager> getInstance(void) ;

	// Destructor
	virtual ~IXcorrManager() {}

	/**
	 * initialisation. Can be overridden by derived objects to define their own waveforms
	 */
	virtual bool init() =0 ;

	virtual bool setFilename(const std::string& filename) = 0 ;
	virtual bool setEnable(bool enable) = 0 ;
	virtual bool setThreshold(float threshold) = 0 ;

	virtual std::string getFilename() = 0 ;
	virtual bool isEnabled() = 0 ;
	virtual float getThreshold() = 0 ;

	/**
	 * After correlation read out the detected peak value
	 */
	virtual unsigned getPeak() = 0 ;
	virtual float readPeak() = 0 ;

	/**
	 * read the replica file and determine the depth based on the file size. Assumes filename
	 * has been set.
	 *
	 */
	virtual unsigned getFileDepth() const =0 ;

	/**
	 * Get the FileMgr instance for playback files
	 */
	virtual std::shared_ptr<IFileMgr> getPlaybackFileMgr() =0 ;


	/**
	 * Get the reason for an error
	 * @return error string
	 */
	virtual std::string getErrorReason() = 0 ;

	/**
	 * Get directory path for where replica files are stored
	 * @return directory
	 */
	virtual std::string getReplicaDirectory() const =0 ;

	/**
	 * Load the replica waveform
	 * @return true if loaded
	 */
	virtual bool loadReplica() =0 ;
	virtual bool loadReplica(const std::string& filename) =0 ;


	// Debug
	virtual void show(std::ostream& os) =0 ;
	virtual void showReg(std::ostream& os) =0 ;

	/**
	 * Read out the currently loaded replica pattern from the fpga
	 * @param maxPoints	If set >0 then limits the number of IQ pairs displayed
	 */
	virtual std::vector< std::pair<UINT32, UINT32> > readReplica(unsigned maxPoints = 0) =0 ;

} ;

}

#endif /* IXCORRMANAGER_H_ */
