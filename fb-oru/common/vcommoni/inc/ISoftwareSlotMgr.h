/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISoftwareSlotMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VCOMMONI_INC_ISOFTWARESLOTMGR_H_
#define VCOMMONI_INC_ISOFTWARESLOTMGR_H_

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

#include "ISoftwareSlot.h"

namespace Mplane {

/*!
 * \class  ISoftwareSlotMgr
 * \brief
 * \details
 *
 */
class ISoftwareSlotMgr {
public:
	ISoftwareSlotMgr() {}
	virtual ~ISoftwareSlotMgr() {}

	/**
	 * Get the singleton
	 */
	static std::shared_ptr<ISoftwareSlotMgr> singleton() ;


	/**
	 * Get the list of slots
	 */
	virtual std::vector<std::shared_ptr<ISoftwareSlot>> slots() const =0 ;

	/**
	 * Install status
	 */
	enum InstallStatus {
        INSTALL_COMPLETED,
		INSTALL_FILE_ERROR,
		INSTALL_INTEGRITY_ERROR,
		INSTALL_APPLICATION_ERROR,
	};

	/**
	 * Static method to convert enum to string
	 */
	static std::string installStatusString(InstallStatus status) ;

	/**
	 * Callback function called at end of install
	 */
	using InstallCallback = std::function<void(const std::string& slotName, InstallStatus status, const std::string& error)> ;

	/**
	 * Install software into the named slot
	 */
	virtual bool install(const std::string& slotName, const std::vector<std::string>& files,
			InstallCallback func, std::string& error) =0 ;

	/**
	 * Install status
	 */
	enum ActivateStatus {
        ACTIVATE_COMPLETED,
		ACTIVATE_APPLICATION_ERROR,
	};

	/**
	 * Static method to convert enum to string
	 */
	static std::string activateStatusString(ActivateStatus status) ;


	/**
	 * Callback function called at end of install
	 * NOTE: returnCode is unused
	 */
	using ActivateCallback = std::function<void(const std::string& slotName, ActivateStatus status, unsigned returnCode,
			const std::string& error)> ;

	/**
	 * Activate a slot
	 * @param slotName				Name of slot to active
	 * @param requiredTimeoutSecs	Returns the max time this activation will take before timing out
	 * @param func					Callback function called on error or completion
	 * @param error					Returns error string on error
	 * @return TRUE if started activation ok; false with error string otherwise
	 */
	virtual bool activate(const std::string& slotName, unsigned& requiredTimeoutSecs,
			ActivateCallback func, std::string& error) =0 ;

	/*
	 * Debug - output the current slot information
	 */
	virtual void show(std::ostream& os = std::cout) =0 ;

	/**
	 * Clean out any unused files or broken links
	 */
	virtual bool clean(std::string& error) =0 ;

	/**
	 * Change read-only status of a slot's package
	 */
	virtual bool setReadonly(const std::string& slotName, bool readOnly, std::string& error) =0 ;

} ;

}

#endif /* VCOMMONI_INC_ISOFTWARESLOTMGR_H_ */
