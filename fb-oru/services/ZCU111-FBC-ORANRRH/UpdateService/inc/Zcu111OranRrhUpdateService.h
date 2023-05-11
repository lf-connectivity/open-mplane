/*
 * Zcu111OranRrhUpdateService.h
 *
 *  Created on: 28 May 2020
 *      Author: rcooper
 */

#ifndef _MPLANE_Zcu111_ORAN_RRH_UPDATE_SERVICE_H_
#define _MPLANE_Zcu111_ORAN_RRH_UPDATE_SERVICE_H_

#include "OranRrhUpdateService.h"

namespace Mplane
{

using namespace Mplane;

class Zcu111OranRrhUpdateService: public OranRrhUpdateService
{
public:
	Zcu111OranRrhUpdateService();

    /**
     *
     */
    virtual ~Zcu111OranRrhUpdateService();

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
     * Method called as a result of the radio control process calling reset
     * in the service. By default the base class implementation does nothing.
     */
    virtual void doReset();

private:
};


} /* namespace Mplane */

#endif
