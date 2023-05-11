/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanProcessingElement.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANPROCESSINGELEMENT_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANPROCESSINGELEMENT_H_

#include <string>
#include <memory>

#include "ICUPlaneMonitor.h"

#include "YangMgrServer.h"
#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanProcessingElement
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanProcessingElement : public YangHandlerSysrepo
{
public:
	Zcu111FbcOranrrhHandlerORanProcessingElement(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanProcessingElement();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

	/*
	 * Add an ru-processing element
	 */
	virtual void addRuProcessingElement(const std::string & ruElement,
	                                    const std::string & vlanIf,
	                                    const std::string & duMac);

protected:
	/*
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

private:
	/*
	 * Get list of interfaces
	 */
	std::map<std::string, std::map<std::string, std::string>> getInterfaces(YangPath pathInterfaces);

	/*
	 * Get interface parameter
	 */
	std::string getInterfaceParameter(const std::string & interface, YangPath pathParam);

	/*
	 * Callbacks
	 */
	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

	/*
	 * C/U-Plane monitor
	 */
	std::shared_ptr<ICUPlaneMonitor> mCUPlaneMonitor;
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANPROCESSINGELEMENT_H_ */
