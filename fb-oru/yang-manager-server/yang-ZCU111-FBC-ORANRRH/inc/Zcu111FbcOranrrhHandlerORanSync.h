/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanSync.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSYNC_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSYNC_H_

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"
#include "ILinuxPtpService.h"
#include "Zcu111FbcOranrrhHandlerORanSyncNotif.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanSync
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanSync : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanSync(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanSync();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:
	/*!
	 \brief Module change hook - called by module_change() method to have this class validate the proposed values changes
	 \param params A YangParams pointer containing all of the changed values
	 \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any other sysrepo error
	 status as necessary.
	 */
	virtual int validate(std::shared_ptr<YangParams> params, std::shared_ptr<YangParams> deletedParams) ;

	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

	/*!
	 \brief Module change hook - called by module_change() method with filtered events
	 \param xpath Contains full path of the element for which paramDelete callback is called. Eg /o-ran-sync:sync/ptp-config/ptp-profile.
	 \param oldValue The original value of the element
	 */
	virtual void paramDelete(const std::string& xpath, std::shared_ptr<YangParam> oldValue) ;


private:

	/**
	 * Create the sync-status in the sysrepo
	 */
	bool createSyncStatus() ;

	/**
	 * Create the sync-capability in the sysrepo
	 */
	bool createSyncCapability() ;

	/**
	 * Create the ptp-status in the sysrepo
	 */
	bool createPtpStatus() ;

	/**
	 * Create the synce-status in the sysrepo
	 */
	bool createSyncEStatus() ;

	/**
	 * Get the interfaces from ietf-interfaces module
	 */
	std::map<std::string, std::map<std::string, std::string> > getInterfaces(void);

	/**
	 * Get the port reference for a given interface name
	 */
	std::map<std::string, std::shared_ptr<YangParam> > getPortReference(std::string interface);

	/**
	 * Method to populate sync sources from the yang model
	 */
	void populateSyncSources(void);

    /**
     * Handle IAlarmMonitor update events
     * @param alarm associated data
     */
    //void update(const IAlarm& alarm);

	std::shared_ptr<SysrepoGetitemsCallback> mCallback;
	std::map<std::string, uint8_t> mSyncSources;
	std::shared_ptr<ILinuxPtp> mLinuxPtp;
	std::shared_ptr<Zcu111FbcOranrrhHandlerORanSyncNotif> mNotif;
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSYNC_H_ */
