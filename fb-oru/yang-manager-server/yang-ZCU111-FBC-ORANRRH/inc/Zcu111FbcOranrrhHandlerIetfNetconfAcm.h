/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerIetfNetconfAcm.h
 * \brief     IETF NETCONF Access Control Model module handler
 *
 *
 * \details   IETF NETCONF Access Control Model module handler
 *
 */

#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFNETCONFACM_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFNETCONFACM_H_

#include <string>
#include <memory>

#include "YangMgrServer.h"
#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerIetfNetconfAcm
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerIetfNetconfAcm : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerIetfNetconfAcm(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerIetfNetconfAcm();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:
	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath, std::shared_ptr<YangParam> oldValue, std::shared_ptr<YangParam> newValue) override ;

	/*!
	 \brief Module change hook - called by module_change() method to have this class validate the proposed values changes
	 \param params A YangParams pointer containing all of the changed values
	 \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any other sysrepo error
	 status as necessary.
	 */
	virtual int validate(std::shared_ptr<YangParams> params, std::shared_ptr<YangParams> deletedParams) override ;


private:
	bool addSudoRules() ;
	bool addFmpmRules() ;
	bool addNmsRules() ;
	bool addSwmRules() ;
	bool addRootRules() ;

private:
	/*
	 * Callbacks
	 */
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFNETCONFACM_H_ */
