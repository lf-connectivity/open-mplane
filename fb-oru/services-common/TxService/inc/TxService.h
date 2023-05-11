/*
 * CommonFpga.h
 *
 *  Created on: 12 Jun 2013
 *      Author: gdurban
 */

#ifndef RADIOSVCS_POWER_CONTROL_H_
#define RADIOSVCS_POWER_CONTROL_H_

#include <vector>

#include "IRadio.h"
#include "Service.h"
#include "ITxPcl.h"
#include "IVswr.h"

namespace Mplane
{

using namespace Mplane;

class TxService: public Service
{
public:

	static const unsigned int TXSERVICE_TIMER_PERIOD_MSEC;  // timer period for TxService


	TxService();

	/**
     *
     */
    virtual ~TxService();

protected:
    /**
     * Method that MUST be implemented by the inheriting service. The work done
     * my the service, is implemented by this method.
     */
    virtual void show();

    /**
     * Method that MUST be implemented by the inheriting service. The work done
     * my the service, is implemented by this method.
     * @return
     */
    virtual int service();

    /**
     * Method called by the service start() method, to register this service with
     * any particular Observer/Notify interface implementation.
     *
     * @note This method must be implemented by the inheriting service in order
     * for it to register as an observer of other objects.
     *
     * @return true if registration successful.
     */
    virtual bool registerObservers();

    /**
     * Method called as a result of the radio control process calling reset
     * in the service. By default the base class implementation does nothing.
     */
    virtual void doReset();

    std::shared_ptr<IRadio> mRadio;

    /**
     * A vector of Power Control Loop state machines
     */
    std::vector<std::shared_ptr<ITxPcl>> mPcls;
    std::vector<std::shared_ptr<IVswr>> mVswrs;

    int updateCount;
    static const int ONE_SEC_UPDATE = 4;

private:

};


} /* namespace Mplane */

#endif /* RADIOSVCS_POWER_CONTROL_H_ */
