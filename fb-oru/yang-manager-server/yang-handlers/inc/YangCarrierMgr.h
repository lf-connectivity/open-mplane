/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangCarrierMgr.h
 * \brief     Manager object for YANG carrier model
 *
 *
 * \details   Manager object for YANG carrier model
 *
 */


#ifndef YANG_HANDLERS_INC_YANGCARRIERMGR_H_
#define YANG_HANDLERS_INC_YANGCARRIERMGR_H_

#include "ICarrierScheduler.h"
#include "IYangCarrierMgr.h"

namespace Mplane {

/*!
 * \class  YangCarrierMgr
 * \brief
 * \details
 *
 */
class YangCarrierMgr : public virtual IYangCarrierMgr {
public:
	YangCarrierMgr() ;
	virtual ~YangCarrierMgr() ;

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

	/**
	 * Create an endpoint name from the prefix, antenna, carrier
	 *
	 */
	virtual std::string endpointName(const std::string& prefix, unsigned antenna, unsigned carrier) override ;

private:
	std::shared_ptr<ILeafContainer> mLeafContainer ;
} ;

}

#endif /* YANG_HANDLERS_INC_YANGCARRIERMGR_H_ */
