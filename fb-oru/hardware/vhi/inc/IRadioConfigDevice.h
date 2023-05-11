/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRadioConfigDevice.h
 * \brief     An IDevice used for creating/starting the IRadioConfig
 *
 *
 * \details   An IDevice that will be added to the device initialisation list to set up IRadioConfig at the appropriate time
 * 			(i.e. after the FPGA has been created if the FPGA is needed)
 *
 */


#ifndef VHI_INC_IRADIOCONFIGDEVICE_H_
#define VHI_INC_IRADIOCONFIGDEVICE_H_

#include <memory>

#include "GlobalTypeDefs.h"
#include "IDevice.h"


namespace Mplane {

/*!
 * \class  IRadioConfigDevice
 * \brief
 * \details
 *
 */
class IRadioConfigDevice : public virtual IDevice {
public:
	IRadioConfigDevice() {}
	virtual ~IRadioConfigDevice() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IRadioConfigDevice> singleton() ;

    /** \brief Do the device initialisation
     *
     * Method called as part of the base class initialisation to perform the actual
     * initialisation function.
     * @return
     */
    virtual ReturnType::State doInit() =0 ;


     /**
      * Display the device details.
      */
     virtual void show() =0 ;


} ;

}

#endif /* VHI_INC_IRADIOCONFIGDEVICE_H_ */
