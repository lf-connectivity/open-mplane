/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanEcpriDelay.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANECPRIDELAY_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANECPRIDELAY_H_

#include "YangHandlerSysrepo.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanEcpriDelay
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanEcpriDelay : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanEcpriDelay(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanEcpriDelay();

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
	 \param xpath Contains full path of the element for which paramDelete callback is called. Eg /o-ran-compression-factors:sync/compression-details/iq-bandwidth
	 \param oldValue The original value of the element
	 */
	virtual void paramDelete(const std::string& xpath, std::shared_ptr<YangParam> oldValue) ;


private:
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANECPRIDELAY_H_ */
