/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfigDevice.h
 * \brief     IDevice for radio config
 *
 *
 * \details   IDevice for radio config
 *
 */


#ifndef COMMON_RADIOCONFIG_INC_RADIOCONFIGDEVICE_H_
#define COMMON_RADIOCONFIG_INC_RADIOCONFIGDEVICE_H_

#include "IRadioConfigDevice.h"
#include "Device.h"

namespace Mplane {

/*!
 * \class  RadioConfigDevice
 * \brief
 * \details
 *
 */
class RadioConfigDevice : public virtual IRadioConfigDevice, public Device {
public:
	RadioConfigDevice() ;
	virtual ~RadioConfigDevice() ;

    /** \brief Do the device initialisation
     *
     * Method called as part of the base class initialisation to perform the actual
     * initialisation function.
     * @return
     */
    virtual ReturnType::State doInit() override ;


     /**
      * Display the device details.
      */
     virtual void show() override ;

} ;

}

#endif /* COMMON_RADIOCONFIG_INC_RADIOCONFIGDEVICE_H_ */
