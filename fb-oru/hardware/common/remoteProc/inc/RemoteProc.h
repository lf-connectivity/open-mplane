/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteProc.h
 * \brief     Remote processor management
 *
 *
 * \details   Handles remote processor (i.e. on ARM this is the R5 cores) firmware loading and processor start/stop
 *
 */


#ifndef _REMOTEPROC_H_
#define _REMOTEPROC_H_

#include <string>

namespace Mplane {

/*!
 * \class  RemoteProc
 * \brief
 * \details
 *
 */
class RemoteProc {
public:
	RemoteProc(unsigned index) ;
	virtual ~RemoteProc() ;

	enum ProcState {
		// normal states
		PROC_OFFLINE,
		PROC_RUNNING,

		// unexpected states
		PROC_SUSPENDED,
		PROC_CRASHED,
		PROC_DELETED,
		PROC_INVALID,
	};

	static std::string state2str(ProcState state) ;
	static ProcState str2state(const std::string& str) ;

	/**
	 * Set the file path for the firmware to be loaded by this processor. File existence will be checked
	 * \return true if file exists and can be set as this processor's firmware; false otherwise
	 */
	bool setFirmware(const std::string& path) ;

	/**
	 * Either start or stop the processor
	 */
	bool setState(bool start) ;

	/**
	 * start the processor
	 */
	bool start() ;

	/**
	 * stop the processor
	 */
	bool stop() ;

	/**
	 * Convenience function that stops the processor (if it's running), sets the firmware, and starts the processor
	 */
	bool loadFirmware(const std::string& path) ;

	/**
	 * Get any error string
	 */
	std::string error() ;

	/**
	 * get the current processor state
	 */
	ProcState state() ;

	/**
	 * Write to a system file (e.g. /sys/class/remoteproc/remoteproc0/firmware)
	 */
	static bool writeSysFile(const std::string& path, const std::string& data) ;

	/**
	 * Read from a system file (e.g. /sys/class/remoteproc/remoteproc0/state)
	 */
	static bool readSysFile(const std::string& path, std::string& data) ;


protected:
	void setError(const std::string& error) ;

private:
	bool writeClass(const std::string& name, const std::string& data) ;
	bool readClass(const std::string& name, std::string& data) ;

private:
	unsigned mIndex ;
	std::string mFirmwarePath ;
	std::string mInstanceFirmware ;
	std::string mClassPath ;
	std::string mError ;
} ;

}

#endif /* _REMOTEPROC_H_ */
