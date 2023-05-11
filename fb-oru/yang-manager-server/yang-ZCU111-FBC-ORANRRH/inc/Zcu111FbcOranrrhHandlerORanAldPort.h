/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanAldPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANALDPORT_H_
#define ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANALDPORT_H_

#include "YangHandlerSysrepo.h"
#include "SysrepoGetitemsCallback.h"
#include "IAldPort.h"

namespace Mplane {

/*!
 * \class  Zcu111FbcOranrrhHandlerORanAldPort
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanAldPort : public YangHandlerSysrepo {
public:
	Zcu111FbcOranrrhHandlerORanAldPort(std::shared_ptr<IYangModuleMgr> moduleMgr) ;
	virtual ~Zcu111FbcOranrrhHandlerORanAldPort() ;

	/**
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override ;

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

private:

	std::shared_ptr<SysrepoGetitemsCallback> mCallback;

	std::map<std::string, bool> mAldPortDcStatus;

	void createReadOnlyData(int index);

	void createReadWriteData(int index);

	void registerOverCurrent(int index);

	void initDcStatus(int index);

	int getAldPortIndexFromName(std::string name);

	void monitorDcStatus(void);

} ;

}

#endif /* ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANALDPORT_H_ */
