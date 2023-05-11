/*
 * CommonFpga.h
 *
 *  Created on: 12 Jun 2013
 *      Author: gdurban
 */

#ifndef RADIOSVCS_POWERSERVICES_H_
#define RADIOSVCS_POWERSERVICES_H_

#include "Service.h"
#include "IRadio.h"

namespace Mplane
{

using namespace Mplane;

class DigitalPowerService: public Service
{
public:
	DigitalPowerService();

    /**
     *
     */
    virtual ~DigitalPowerService();

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


private:
    std::shared_ptr<IRadio> radio;

};


} /* namespace Mplane */

#endif /* RADIOSVCS_POWERSERVICES_H_ */
