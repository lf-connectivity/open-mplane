#ifndef _COMMONSERVICES_H_
#define _COMMONSERVICES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonServices.h
 * \brief     Class extends the IServices interface to provide control of common services.
 *
 *
 * \details   Class extends the IServices interface to provide control of common services.
 *
 */

#include "IServicesCtl.h"

namespace Mplane
{

class TxService;
class RxService;
//class FaultService;
class DigitalPowerService;
class FibreControlService;
//class DpdService;

class CommonServices: public IServicesCtl
{
    friend class CommonServicesTestCase;
public:

    /**
     *
     */
    CommonServices();

    /**
     * Method called by the controlling radio process to start all services
     *
     */
    virtual void start();

    /**
     * Method called by the controlling radio process to reset all services.
     *
     * @return
     */
    virtual void reset();

    /**
     * Method called by the controlling radio process to temporarily suspend
     * all services.
     *
     */
    virtual void suspend();

    /**
     * Method called by the controlling radio process to resume a currently
     * suspended services.
     */
    virtual void resume();

    /**
     * Method used to shutdown all services after which the service may be deleted
     * or restarted using the start() method.
     */
    virtual void shutdown();


    virtual ~CommonServices();

protected:


    std::shared_ptr<TxService> mTxService;
    std::shared_ptr<RxService> mRxService;
//    std::shared_ptr<FaultService> mFaultService;
    std::shared_ptr<DigitalPowerService> mPowerService;
    std::shared_ptr<FibreControlService> mFibreControlService;
//    std::shared_ptr<DpdService> mDpdService;

};

}




#endif /* _COMMONSERVICES_H_ */
