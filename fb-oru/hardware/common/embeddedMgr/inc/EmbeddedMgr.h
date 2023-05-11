/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EmbeddedMgr.h
 * \brief     Base class that implements shared methods for IEmbeddedMgr
 *
 *
 * \details   Base class that implements shared methods for IEmbeddedMgr
 *
 */


#ifndef COMMON_EMBEDDEDMGR_INC_EMBEDDEDMGR_H_
#define COMMON_EMBEDDEDMGR_INC_EMBEDDEDMGR_H_

#include <map>
#include <utility>

#include "IEmbeddedMgr.h"

namespace Mplane {

/*!
 * \class  EmbeddedMgr
 * \brief
 * \details
 *
 */
class EmbeddedMgr : public virtual IEmbeddedMgr {
public:
	/**
	 * Constructor accepts vector of std::pairs. Each std::pair consists of the processor name, and a wildcard name of the
	 * firmware for that processor. The vector index is used as the processor number.
	 */
	EmbeddedMgr(const std::vector<std::pair<std::string, std::string>>& firmwareList,
			const std::string& firmwarePath = "") ;
	virtual ~EmbeddedMgr() ;

	/**
	 * Get the list of names of the processors. The vector index corresponds to the processor index that can be used with the
	 * other methods
	 */
	virtual std::vector<std::string> names() const override ;

	/**
	 * Get processor current status. Use processor index.
	 */
	virtual IEmbeddedMgr::ProcState status(unsigned index) override ;

	/**
	 * Get processor current status. Use processor name.
	 */
	virtual IEmbeddedMgr::ProcState status(const std::string& name) override ;

	/**
	 * Get any errors. Clears error string.
	 */
	virtual std::string error() override ;

	/**
	 * Convert name into processor index. Returns -1 for invalid name
	 */
	virtual int procIndex(const std::string& name) const override ;

	/**
	 * Convert index to processor name. Returns empty string for invalid index
	 */
	virtual std::string name(unsigned index) const override ;

	/**
	 * Get the full path to the actual firmware for this processor
	 * \return path for this processor's firmware; empry string otherwise
	 */
	virtual std::string firmware(unsigned index) const override ;

	/**
	 * Get the full path to the actual firmware for this processor
	 * \return path for this processor's firmware; empry string otherwise
	 */
	virtual std::string firmware(const std::string& name) const override ;

	/**
	 * Change the file path for the firmware to be loaded by this processor. File existence will be checked
	 * \return true if file exists and can be set as this processor's firmware; false otherwise
	 */
	virtual bool setFirmware(unsigned index, const std::string& path) override ;

	/**
	 * Change the file path for the firmware to be loaded by this processor. File existence will be checked
	 * \return true if file exists and can be set as this processor's firmware; false otherwise
	 */
	virtual bool setFirmware(const std::string& name, const std::string& path) override ;

	/**
	 * Either start or stop the processor
	 */
	virtual bool setState(unsigned index, bool start) override ;

	/**
	 * Either start or stop the processor
	 */
	virtual bool setState(const std::string& name, bool start) override ;

	/**
	 * start the processor
	 */
	virtual bool start(unsigned index) override ;

	/**
	 * start the processor
	 */
	virtual bool start(const std::string& name) override ;

	/**
	 * stop the processor
	 */
	virtual bool stop(unsigned index) override ;

	/**
	 * stop the processor
	 */
	virtual bool stop(const std::string& name) override ;

	/**
	 * Convenience function that stops the processor (if it's running), sets the firmware, and starts the processor
	 */
	virtual bool loadFirmware(unsigned index) override ;

	/**
	 * Convenience function that stops the processor (if it's running), sets the firmware, and starts the processor
	 */
	virtual bool loadFirmware(const std::string& name) override ;

	/**
	 * Get the remote message handler associated with this processor
	 */
	virtual std::shared_ptr<IRemoteMsgHandler> msgHandler(unsigned index) override ;

	/**
	 * Start/stop the event loop for this processor. This will use the appropriate IRemoteMsgHandler
	 * to start/stop handling messages from the processor
	 */
	virtual bool eventLoop(unsigned index, bool start) override ;


protected:
	// Shared utilities

	/**
	 * Set the error string and return FALSE so that method can be called in a return statement
	 */
	bool setError(const std::string& error) ;

	/**
	 * Get path under which all the firmware is stored
	 */
	std::string firmarePath() const ;

	/**
	 * Set the name of the firmware for this processor. Wildcard names will be resolved to the first match in the firmware
	 * directory.
	 * \return true if file exists; false otherwise
	 */
	bool firmwareMap(unsigned index, const std::string& firmwareName) ;

protected:
	// HOOKS to be overridden by derived objects

	/**
	 * Start/stop the processor
	 */
	virtual bool doSetState(unsigned index, bool start) ;

	/**
	 * Cause the processor to load it's firmware
	 */
	virtual bool doSetFirmware(unsigned index) ;

	/**
	 * Get the current processor status
	 */
	virtual IEmbeddedMgr::ProcState doStatus(unsigned index) ;

private:
	std::string mFirmwarePath ;
	std::map<std::string, unsigned> mNameIndexMap ;
	std::vector<std::string> mNames ;
	std::vector<std::string> mFirmware ;
	std::vector<std::shared_ptr<IRemoteMsgHandler>> mMsgHandler ;
	std::string mError ;
} ;

}

#endif /* COMMON_EMBEDDEDMGR_INC_EMBEDDEDMGR_H_ */
