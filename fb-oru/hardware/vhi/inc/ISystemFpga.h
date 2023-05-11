/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISystemFpga.h
 * \brief     Virtual interface for Device interface to system FPGA(s)
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VHI_INC_ISYSTEMFPGA_H_
#define VHI_INC_ISYSTEMFPGA_H_

#include <memory>

#include "GlobalTypeDefs.h"
#include "IDevice.h"

namespace Mplane {

/*!
 * \class  ISystemFpga
 * \brief
 * \details
 *
 */
class ISystemFpga : public virtual IDevice {
public:
	ISystemFpga()  {}
	virtual ~ISystemFpga() {}

	/**
	 * Create the instance
	 */
	static std::shared_ptr<ISystemFpga> makeInstance(unsigned deviceIndex, const std::string& name = "SystemFpga") ;

    /** \brief Do the device initialisation
     *
     * Method called as part of the base class initialisation to perform the actual
     * initialisation function.
     * @return
     */

    virtual ReturnType::State doInit() =0 ;

    /*! \brief  Configure the FPGA
      *
      *  Method to configure the FPGA.
      *
      *  Pure virtual because programming the FPGA is not a common
      *  procedure and is likely to be board specific specific. We know we need
      *  to program it, so this forces the implementation to provide the
      *  program procedure.
      *
      *  \return state of RT_OK if the FPGA configured OK, RT_other if not.
      */


     /**
      * Display the device details.
      */
     virtual void show() =0 ;


} ;

}

#endif /* VHI_INC_ISYSTEMFPGA_H_ */
