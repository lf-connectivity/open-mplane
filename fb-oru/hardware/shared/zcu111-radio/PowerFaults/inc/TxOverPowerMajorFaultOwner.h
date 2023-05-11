/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxOverpowerMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TX_OVERPOWER_MAJOR_FAULTOWNER_H_
#define TX_OVERPOWER_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"

#include "Observer.hpp"
#include "ICarrierServer.h"

namespace Mplane {

class TxOverPowerMajorFaultOwner : public FaultOwner,
								   public Observer<ITxOn, const ITxEventData&>,
								   public Observer<ITxOff, const ITxEventData&>
{
public:
	TxOverPowerMajorFaultOwner() ;
	virtual ~TxOverPowerMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

    /**
     * Handle carrier manager Tx ON update events
     * @param subject ITxOn
     * @param txOnOff associated data
     */
    virtual void update(ITxOn& subject, const ITxEventData& txOnOff);

    /**
     * Handle carrier manager Tx OFF update events
     * @param subject ITxOff
     * @param txOnOff associated data
     */
    virtual void update(ITxOff& subject, const ITxEventData& txOnOff);

    /**
     * Required by Observer template
     * @return
     */
    virtual const char* name() const
    {
        return "TX_OVERPOWER_MAJOR_FAULT_OWNER";
    }

private:

    bool mIsTx1On; //!> Local store of current state of Tx1 Carrier
    bool mIsTx2On; //!> Local store of current state of Tx2 Carrier
    bool mIsTx3On; //!> Local store of current state of Tx3 Carrier
    bool mIsTx4On; //!> Local store of current state of Tx4 Carrier

    std::shared_ptr<ICarrierServer> mCarrierMgr;
} ;

}

#endif /* TX_OVERPOWER_MAJOR_FAULTOWNER_H_ */
