#ifndef _RADIO_HARDWARE_COMMONFPGADEV_H_
#define _RADIO_HARDWARE_COMMONFPGADEV_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFpgaDev.h
 * \brief     A file to contain the common implementation of a generic FPGA device.
 *
 *
 * \details   This file defines the common implementation of a generic FPGA device
 *            and expands on it if necessary.
 *
 */

#include <string>

#include "IFpgaDev.h"
#include "Device.h"

namespace Mplane
{

/*! \brief  Generic FPGA interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  FPGA device
 *  The interface contains configuration and control aspects.
 *
 *  This class represents a virtual interface used to setup the FPGA
 *  on a radio. It is designed to be implemented as a polymorphic base class
 *  for all FPGA device classes..
 *
 *  The actual implementation of this interface, will be aware of the type
 *  of FPGA in use and how to configure it.
 *
 *  This generic FPGA interface is used in the IFpgaDev interface, to provide
 *  a generic method of configuring the radio's FPGA devices (likely to be one
 *  per board but not necessarily)
 *
 */
class CommonFpgaDev:  public virtual IFpgaDev, public Device
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class CommonFpgaDevTestCase;


public:


    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  Means that this CommonFpgaDev class does not provide any FPGA-type specific
     *  initialisation. That is left to the inheritors who know what
     *  device they are.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "FPGA INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit() = 0;

    /*! \brief  Configure the FPGA
     *
     *  Method to configure the FPGA.
     *
     *  Pure virtual because configuring an FPGA is not a common
     *  procedure and is board and FPGA-type specific, but we know we need
     *  to program it, so this forces the implementation to provide
     *  the program procedure.
     *
     *  \return state of RT_OK if synthesiser is locked OK, RT_other if not.
     */

     /*! \brief  Dump the FPGA configuration status
     *
     *  Dump the state of the FPGA configuration to the console or log file
     */
    virtual void show(std::ostream& os);
    virtual void show(void);


    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    CommonFpgaDev( int index, const std::string& name);

    /*! \brief Destructor
     *
     *  Ensure we can only be destructed via an implementing class
     *
     */
    virtual ~CommonFpgaDev();


private:


};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONFPGADEV_H_ */
