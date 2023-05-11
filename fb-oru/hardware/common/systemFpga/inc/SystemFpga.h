/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemFpga.h
 * \brief     Device interface to system FPGA(s)
 *
 *
 * \details   Allows the FPGA(s) to be initialised in the device list
 *
 */


#ifndef COMMON_SYSTEMFPGA_INC_SYSTEMFPGA_H_
#define COMMON_SYSTEMFPGA_INC_SYSTEMFPGA_H_

#include <memory>

#include "ISystemFpga.h"

#include "GlobalTypeDefs.h"
#include "CommonFpgaDev.h"
#include "Loggable.h"

namespace Mplane {

/*!
 * \class  SystemFpga
 * \brief
 * \details
 *
 */
class SystemFpga: public virtual ISystemFpga, public CommonFpgaDev, public Loggable {
public:
	SystemFpga(unsigned deviceIndex, const std::string& name) ;
	virtual ~SystemFpga() ;

    /** \brief Do the device initialisation
     *
     * Method called as part of the base class initialisation to perform the actual
     * initialisation function.
     * @return
     */

    virtual ReturnType::State doInit() override;

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
     virtual void show() override;

protected:

     /**
      * Method called during system FPGA initialisation so that applications
      * that need to modify the default behaviour of the system FPGA for a specific
      * application can do so by inheriting from the base implementation and overriding
      * this method.
      * @return
      */
     virtual ReturnType::State appSpecificInit();

private:
    std::string mDevName;
} ;

}

#endif /* COMMON_SYSTEMFPGA_INC_SYSTEMFPGA_H_ */
