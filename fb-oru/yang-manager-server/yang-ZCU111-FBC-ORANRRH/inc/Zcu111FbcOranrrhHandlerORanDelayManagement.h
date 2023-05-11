/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanDelayManagement.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANDELAYMANAGEMENT_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANDELAYMANAGEMENT_H_

#include "Frequency.h"

#include "IFpgaMgr.h"
#include "IOranDelays.h"

#include "Zcu111Delay.h"

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanDelayManagement
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanDelayManagement : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanDelayManagement(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanDelayManagement();

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

private:

	bool createBandwidthScsDelayStateList(void);

	std::shared_ptr<SysrepoGetitemsCallback> mCallback;
	std::shared_ptr<IOranDelays> mOranDelays;

};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANDELAYMANAGEMENT_H_ */
