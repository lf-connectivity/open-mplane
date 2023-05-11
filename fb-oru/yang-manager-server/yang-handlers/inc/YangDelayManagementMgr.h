/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangDelayManagementMgr.h
 * \brief     Manager object for YANG Delay Management model
 *
 *
 * \details   Manager object for YANG Delay Management model
 *
 */


#ifndef YANG_HANDLERS_INC_YANGDELAYMANAGEMENTMGR_H_
#define YANG_HANDLERS_INC_YANGDELAYMANAGEMENTMGR_H_

#include "ICarrierScheduler.h"
#include "IYangDelayManagementMgr.h"

namespace Mplane {

/*!
 * \class  YangDelayManagementMgr
 * \brief
 * \details
 *
 */
class YangDelayManagementMgr : public virtual IYangDelayManagementMgr {
public:
	YangDelayManagementMgr() ;
	virtual ~YangDelayManagementMgr() ;

	/**
	 * Initialise the object
	 */
	virtual bool initialise() override ;

	/**
	 * Assign the leaf container
	 */
	virtual void setLeafContainer(std::shared_ptr<ILeafContainer> leafContainer) override ;

	/**
	 * Get the leaf container
	 */
	virtual std::shared_ptr<ILeafContainer> leafContainer() override ;

private:
	std::shared_ptr<ILeafContainer> mLeafContainer ;
} ;

}

#endif /* YANG_HANDLERS_INC_YANGDELAYMANAGEMENTMGR_H_ */
