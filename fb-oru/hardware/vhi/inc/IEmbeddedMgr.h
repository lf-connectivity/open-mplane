/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IEmbeddedMgr.h
 * \brief     Embedded apps manager
 *
 *
 * \details   Manages farming the embedded applications off to the correct co-processor
 *
 */


#ifndef VHI_INC_IEMBEDDEDMGR_H_
#define VHI_INC_IEMBEDDEDMGR_H_

#include <memory>
#include <vector>
#include <string>

#include "IRemoteMsgHandler.h"

namespace Mplane {

/*!
 * \class  IEmbeddedMgr
 * \brief
 * \details
 *
 */
class IEmbeddedMgr {
public:
	/**
	 * All accesses through singleton
	 */
	static std::shared_ptr<IEmbeddedMgr> singleton() ;

	IEmbeddedMgr() {}
	virtual ~IEmbeddedMgr() {}

	/**
	 * Get the list of names of the processors. The vector index corresponds to the processor index that can be used with the
	 * other methods
	 */
	virtual std::vector<std::string> names() const =0 ;

	/**
	 * Processor states
	 */
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

	/**
	 * Convert processor state to string
	 */
	static std::string state2str(ProcState state) ;

	/**
	 * Convert processor state string to state
	 */
	static ProcState str2state(const std::string& str) ;


	/**
	 * Get processor current status. Use processor index.
	 */
	virtual ProcState status(unsigned index) =0 ;

	/**
	 * Get processor current status. Use processor name.
	 */
	virtual ProcState status(const std::string& name) =0 ;

	/**
	 * Get any errors. Clears error string.
	 */
	virtual std::string error() =0 ;

	/**
	 * Convert name into processor index. Returns -1 for invalid name
	 */
	virtual int procIndex(const std::string& name) const =0 ;

	/**
	 * Convert index to processor name. Returns empty string for invalid index
	 */
	virtual std::string name(unsigned index) const =0 ;

	/**
	 * Get the full path to the actual firmware for this processor
	 * \return path for this processor's firmware; empry string otherwise
	 */
	virtual std::string firmware(unsigned index) const =0 ;

	/**
	 * Get the full path to the actual firmware for this processor
	 * \return path for this processor's firmware; empry string otherwise
	 */
	virtual std::string firmware(const std::string& name) const =0 ;

	/**
	 * Change the file path for the firmware to be loaded by this processor. File existence will be checked
	 * \return true if file exists and can be set as this processor's firmware; false otherwise
	 */
	virtual bool setFirmware(unsigned index, const std::string& path) =0 ;

	/**
	 * Change the file path for the firmware to be loaded by this processor. File existence will be checked
	 * \return true if file exists and can be set as this processor's firmware; false otherwise
	 */
	virtual bool setFirmware(const std::string& name, const std::string& path) =0 ;

	/**
	 * Either start or stop the processor
	 */
	virtual bool setState(unsigned index, bool start) =0 ;

	/**
	 * Either start or stop the processor
	 */
	virtual bool setState(const std::string& name, bool start) =0 ;

	/**
	 * start the processor
	 */
	virtual bool start(unsigned index) =0 ;

	/**
	 * start the processor
	 */
	virtual bool start(const std::string& name) =0 ;

	/**
	 * stop the processor
	 */
	virtual bool stop(unsigned index) =0 ;

	/**
	 * stop the processor
	 */
	virtual bool stop(const std::string& name) =0 ;

	/**
	 * Convenience function that stops the processor (if it's running), sets the firmware, and starts the processor
	 */
	virtual bool loadFirmware(unsigned index) =0 ;

	/**
	 * Convenience function that stops the processor (if it's running), sets the firmware, and starts the processor
	 */
	virtual bool loadFirmware(const std::string& name) =0 ;

	/**
	 * Get the remote message handler associated with this processor
	 */
	virtual std::shared_ptr<IRemoteMsgHandler> msgHandler(unsigned index) =0 ;

	/**
	 * Start/stop the event loop for this processor. This will use the appropriate IRemoteMsgHandler
	 * to start/stop handling messages from the processor
	 */
	virtual bool eventLoop(unsigned index, bool start) =0 ;

} ;

}

#endif /* VHI_INC_IEMBEDDEDMGR_H_ */
