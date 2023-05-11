/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandlerMgr.h
 * \brief     A manager that instantiates all YANG handlers, derived from the base class IYangHandlerMgr
 *
 *
 * \details   The manager is a singleton created for this YANG application
 */


#ifndef YANG_HANDLERS_INC_YANGHANDLERMGR_H_
#define YANG_HANDLERS_INC_YANGHANDLERMGR_H_

#include <vector>

#include "IYangHandlerMgr.h"
#include "IYangCarrierMgr.h"

namespace Mplane {

/*!
 * \class  YangHandlerMgr
 * \brief
 * \details
 *
 */
class YangHandlerMgr : public virtual IYangHandlerMgr {
public:
	YangHandlerMgr(std::shared_ptr<IYangModuleMgr> moduleMgr) ;
	virtual ~YangHandlerMgr() ;

	/**
	 * Run the initialisation of the handlers (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override ;

	/**
	 * Add a YANG handler to the list that this manager manages
	 */
	virtual bool registerHandler(std::shared_ptr<IYangHandler> handler) override ;

	/**
	 * Debug
	 */
	virtual bool testCallback(const std::string& xpath, std::shared_ptr<DataVariant> value) override ;


protected:
	std::shared_ptr<IYangModuleMgr> moduleMgr() const ;

private:
	std::shared_ptr<IYangModuleMgr> mModuleMgr ;
	std::vector<std::shared_ptr<IYangHandler>> mHandlers ;

	std::shared_ptr<IYangCarrierMgr> mCarrierMgr ;

};

}

#endif /* YANG_HANDLERS_INC_YANGHANDLERMGR_H_ */
