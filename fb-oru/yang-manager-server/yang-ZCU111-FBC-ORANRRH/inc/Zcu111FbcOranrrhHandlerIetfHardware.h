/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerIetfHardware.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFHARDWARE_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFHARDWARE_H_

#include "YangHandlerSysrepo.h"

namespace Mplane
{
class SysrepoGetitemsCallback;

/*!
 * \class  Zcu111FbcOranrrhHandlerIetfHardware
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerIetfHardware : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerIetfHardware(std::shared_ptr<IYangModuleMgr> moduleMgr);

	static const std::string mRadioCardHardwareName;

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	bool initialise() override;

protected:
	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	void valueChange(const std::string& xpath,
	                 std::shared_ptr<YangParam> oldValue,
	                 std::shared_ptr<YangParam> newValue) override;

private:
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERIETFHARDWARE_H_ */
