#ifndef _RADIOSVCS_FIBRECONTROLSERVICE_H_
#define _RADIOSVCS_FIBRECONTROLSERVICE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FibreControlService.h
 * \brief     The class definition to perform the common radio Fibre control services
 *
 *
 * \details   The class definition to perform the common radio Fibre control services
 *
 */

// Includes go here, before the namespace
#include "Service.h"
#include "IFibre.h"
#include "IFibreControl.h"

namespace Mplane
{

// forward class definitions


class FibreControlService: public Service
{
public:
    friend class FibreControlServiceTestCases;
    friend class FibreControlServiceTestCase;

    static const unsigned int SERVICE_PERIOD = 500;  // 500 msec service period

    FibreControlService();


    /**
     *
     */
    virtual ~FibreControlService();

protected:
    /**
     * Method that MUST be implemented by the inheriting service. The work done
     * by the service, is implemented by this method.
     */
    virtual void show();

    /**
     * Method that MUST be implemented by the inheriting service. The work done
     * by the service, is implemented by this method.
     *
     * \note The service method will continue to be called for as long as is
     * returns zero, non-zero indicates and execution error in the service
     * that will result in it being shutdown and the error made available to the
     * Task exit value.
     *
     * \return 0 when running normally, any other value is a error condition
     */
    virtual int service();

    /**
     * Method called by the Service start() method, to register this service with
     * any particular Observer/Notify interface implementation.
     *
     * \note This method must be implemented by the inheriting service in order
     * for it to register as an observer of other objects.
     *
     * \return true if registration successful.
     */
    virtual bool registerObservers();

    /**
     * Method called as a result of the radio control process calling reset
     * in the service. By default the base class implementation does nothing.
     */
    virtual void doReset();

private:

    std::shared_ptr<IFibreControl> mFibreController;
};

} /* namespace Mplane */

#endif /* _RADIOSVCS_FIBRECONTROLSERVICE_H_ */
