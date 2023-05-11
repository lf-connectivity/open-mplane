/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdService.h
 * \brief     Service DPD messages
 *
 *
 * \details   Creates a framework for the DPD services
 *
 */


#ifndef DPDSERVICE_H_
#define DPDSERVICE_H_

#include <queue>
#include <memory>
#include <vector>
#include <map>
#include <string>

#include "Observer.hpp"
#include "DataVariant.h"
#include "TaskEvent.h"

#include "IDpdControl.h"

#include "data/IDpdData.h"

namespace Mplane {

class IFpgaMsg ;
class IFpgaComms ;
class FpgaCommsMsgMonitor ;
class DpdControlTx ;

class DpdService : public TaskEvent, public virtual IDpdControl
{
public:
	DpdService() ;
	virtual ~DpdService() ;

    // IDpdControl interface

    /**
     * This method will reset the DPD on the specified channel to
     * unity gain
     * \param tx - tx path [0..MAX-1] to be reset
     * \return true if all ok; false on failure
     */
    virtual bool resetDpd(unsigned tx) override;

    /**
     * This method will enable adaption of the DPD on the specified
     * channel (does not wait for successful iteration).
     * \param tx - tx path to enable
     * \return true if all ok; false on failure
     */
    virtual bool startDpd(unsigned tx) override;

    /**
     * This method will enable adaption of the DPD on the specified
     * channel
     * \param tx - tx path to enable
     * \param timeoutMs - timeout time in millisecs
     * \return true if all ok; false on failure
     */
    virtual bool startDpd(unsigned tx, unsigned timeoutMs) override;

    /**
     * This method will stop the DPD on the specified channel
     * \param tx - tx path [0..MAX-1] to be stopped
     * \return true if all ok; false on failure
     */
    virtual bool stopDpd(unsigned tx) override;

    /**
     * This method will send the latest PAPR target to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setPapr(unsigned tx, const Power& papr) override;

    /**
     * This method will send the latest SRx attenuation value to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setSRxAtten(unsigned tx, const Power& atten) override;

    /**
     * This method will send a new set of parameters to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setParams(unsigned tx, const std::vector<DataVariant>& params) override ;

protected:
	// Add a new monitor
	bool addMonitor(std::shared_ptr<FpgaCommsMsgMonitor> monitor) ;

	// Message handlers for each of the types of information that clients can register for.
	template<class ConcreteDataType, class VirtualDataType, class VirtualClientType>
	void handleEvent(std::map<std::string, DataVariant> attributes)
	{
		// Create a concrete data object
		std::shared_ptr<ConcreteDataType> data(std::make_shared<ConcreteDataType>()) ;

		// check that data is ok to use
		std::shared_ptr<IDpdData> dp(std::dynamic_pointer_cast<IDpdData>(data)) ;
		if (!dp->predicate(attributes))
			return ;

		// fill up data class with data
		data->setData(attributes) ;

		// Send data class to clients
		dynamic_cast< Subject<VirtualClientType, const VirtualDataType&>* >(this)->notify(*data) ;
	}


protected:
	// TaskEvent run task
	virtual bool runEvent() ;

	// forward the message to all monitors
	void msgDispatcher(std::shared_ptr<IFpgaMsg> msg) ;

	// get the appropriate DPD controller. Tx port is 0-based
	std::shared_ptr<DpdControlTx> getDpdControl(unsigned txPort) ;



private:
	std::shared_ptr<IFpgaComms> mFpgaComms ;

	Mutex				mMutex ;
	std::queue< std::shared_ptr<IFpgaMsg> >	mMessages ;

	std::vector< std::shared_ptr<FpgaCommsMsgMonitor> > mMonitors ;

    std::vector< std::shared_ptr<DpdControlTx> > mDpdControl ;
} ;

}

#endif /* DPDSERVICE_H_ */
