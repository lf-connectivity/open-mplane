/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanModuleCap.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANMODULECAP_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANMODULECAP_H_

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanModuleCap
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanModuleCap : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanModuleCap(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanModuleCap();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:
	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

	/*!
	 \brief Module change hook - called by module_change() method to have this class validate the proposed values changes
	 \param params A YangParams pointer containing all of the changed values
	 \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any other sysrepo error
	 status as necessary.
	 */
	virtual int validate(std::shared_ptr<YangParams> params, std::shared_ptr<YangParams> deletedParams) ;

private:

	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

	/**
	 * Create the sync-status in the sysrepo
	 */
	bool createRuCapabilities(void) ;

	/**
	 * Create the sync-capability in the sysrepo
	 */
	bool createBandCapabilities(void) ;

	/**
	 * Populate the band container with ul/dl info
	 */
	bool populateBanduldl(std::shared_ptr<ILeafContainer> band, uint64_t minFreq, uint64_t maxFreq, bool isUl);

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANMODULECAP_H_ */
