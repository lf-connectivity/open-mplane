/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwareSlotMgr.h
 * \brief     Manages "slots" of software packages
 *
 *
 * \details   Each "slot" is a complete package of files that make up a software installation
 *
 */


#ifndef INC_SOFTWARESLOTMGR_H_
#define INC_SOFTWARESLOTMGR_H_

#include <map>
#include <list>
#include <mutex>

#include "ISoftwareSlotMgr.h"
#include "TaskEvent.h"

namespace Mplane {

class SoftwarePackage ;
class SoftwareSlot ;

/*!
 * \class  SoftwareSlotMgr
 * \brief
 * \details
 *
 */
class SoftwareSlotMgr : public virtual ISoftwareSlotMgr, public TaskEvent {
public:
	/**
	 * Specify the various top-level paths (mainly for gtest)
	 * @param maxSlots	Total number of slots
	 * @param mgmtPath	Top-level management directory under which various sub-directories are created for slot info
	 * @param appsPath	Directory containing application tarballs
	 * @param osPath	Directory containing OS image links
	 */
	SoftwareSlotMgr(unsigned maxSlots, const std::string& mgmtPath, const std::string& appsPath, const std::string& osPath) ;
	SoftwareSlotMgr(unsigned maxSlots) ;
	SoftwareSlotMgr() ;
	virtual ~SoftwareSlotMgr() ;

	/**
	 * Get the list of slots
	 */
	virtual std::vector<std::shared_ptr<ISoftwareSlot>> slots() const override ;

	/**
	 * Install software into the named slot
	 */
	virtual bool install(const std::string& slotName, const std::vector<std::string>& files,
			ISoftwareSlotMgr::InstallCallback func, std::string& error) override ;

	/**
	 * Activate a slot
	 */
	virtual bool activate(const std::string& slotName, unsigned& requiredTimeoutSecs,
			ISoftwareSlotMgr::ActivateCallback func, std::string& error) override ;

	/*
	 * Debug - output the current slot information
	 */
	virtual void show(std::ostream& os = std::cout) override ;

	/**
	 * Clean out any unused files or broken links
	 */
	virtual bool clean(std::string& error) override ;

	/**
	 * Change read-only status of a slot's package
	 */
	virtual bool setReadonly(const std::string& slotName, bool readOnly, std::string& error) override ;



protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

protected:
	class SwJob ;
	class SwInstallJob ;
	class SwActivateJob ;
	void handleInstall(std::shared_ptr<SwInstallJob> job) ;
	void handleActivate(std::shared_ptr<SwActivateJob> job) ;
	void cleanDir(const std::string& dir) ;

private:
	void createDirectories() ;
	void createPackages() ;
	void createSlots() ;

private:
	unsigned mNumSlots ;
	std::string mMgrPath ;
	std::string mAppsPath ;
	std::string mOsPath ;
	std::vector<std::shared_ptr<ISoftwarePackage>> mPackages ;
	std::map<std::string, std::shared_ptr<ISoftwareSlot>> mSlots ;

	std::mutex mMutex ;
	std::list<std::shared_ptr<SwJob>> mJobs ;
} ;

}

#endif /* INC_SOFTWARESLOTMGR_H_ */
