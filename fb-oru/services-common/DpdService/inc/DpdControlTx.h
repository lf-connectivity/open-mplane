/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdControlTx.h
 * \brief     Controls DPD for a single TX path
 *
 *
 * \details
 *
 */


#ifndef DPDCONTROLTX_H_
#define DPDCONTROLTX_H_

#include <memory>
#include <string>
#include <map>

#include "IFpgaMsg.h"

#include "Mutex.h"
#include "Conditional.h"
#include "Power.h"
#include "DataVariant.h"

#include "DpdControlBase.h"

namespace Mplane {

class FpgaCommsMsgMonitor ;

class DpdControlTx : public DpdControlBase {
public:
	/**
	 * Constructor
	 * @param txPort 0-based port number
	 */
	explicit DpdControlTx(unsigned txPort) ;
	virtual ~DpdControlTx() ;

    /**
     * Set PAPR target for this TX path
     */
    virtual bool setPapr(const Power& papr) ;

    /**
     * Set SRx attenuation for this TX path
     */
    virtual bool setSRxAtten(const Power& atten);

    /**
     * This method will reset the DPD on the specified channel to
     * unity gain
     */
    virtual bool resetDpd() ;

    /**
     * This method will enable adaption of the DPD on the specified
     * channel
     */
    virtual bool startDpd() ;

    /**
     * This method will enable adaption of the DPD on the specified
     * channel but also waits for 1 successful iteration (or time out)
     */
    virtual bool startDpd(unsigned timeoutMs) ;

    /**
     * This method will stop the DPD on the specified channel
     */
    virtual bool stopDpd() ;


    enum class QmcMode {
    	ON,
    	OFF,
    	FREEZE,
    	DCONLY
    };

    /**
     * Set QMC mode for this TX
     */
    virtual bool setQmc(QmcMode mode) ;

    /**
     * Returns the current count of successful iterations
     */
    virtual unsigned getSuccessCount() const ;

private:
	/**
	 * Forward the EVENT message on to the message monitor
	 * @param msg
	 */
	void msgDispatcher(std::shared_ptr<IFpgaMsg> msg) ;

	/**
	 * Process data from the message monitor
	 * @param attributes
	 */
	void handleEvent(const std::map<std::string, DataVariant>& attributes) ;

private:
	std::shared_ptr<FpgaCommsMsgMonitor> mMonitor ;
	unsigned mTxPort ;

	mutable Mutex mMutex ;
	Conditional mCond ;
	unsigned mSuccessCount ;
} ;

}

#endif /* DPDCONTROLTX_H_ */
