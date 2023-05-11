/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAldPort.h
 * \brief     Virtual interface to an ALD port
 *
 *
 * \details   Virtual interface to an ALD port
 *
 */


#ifndef VHI_IALDPORT_H_
#define VHI_IALDPORT_H_

#include <vector>
#include <string>

#include "GlobalTypeDefs.h"
#include "Hdlc.h"

namespace Mplane {

/*
 * Forward class declarations
 */
class Hdlc;

/*!
 * \class  IAldPort
 * \brief
 * \details
 */
class IAldPort {
public:
	IAldPort() {}
	virtual ~IAldPort() {}

    /**
     * This method returns the HDLC interface to communicate to the devices on ALD port
     *
     * @return Pointer to Hdlc class
     */
    virtual std::shared_ptr<Hdlc> getHdlc() =0 ;

    /**
     * This method indicates whether DC power can be turned ON/OFF on this port
     *
     * @return bool
     */
    virtual bool isDCPowerControlSupported(void) =0 ;

    /**
     * This method provides the DC power supply status
     *
     * @return DC power status
     */
    virtual bool isDCPowerOn(void) =0 ;

    /**
     * This method is to turn ON/OFF
     *
     * @return None
     */
    virtual void setDCPower(bool) =0 ;

    /**
     * This method indicates whether overcontrol detection is supported on this port
     *
     * @return bool
     */
    virtual bool isOvercurrentDetectionSupported(void) =0 ;

    using OverCurrentFuncCb = std::function<void(bool)>;

    /**
     * This method registers callbacks for overcurrent notifications
     *
     * @return bool
     */
    virtual void registerOvercurrentCb(OverCurrentFuncCb cb) = 0;


} ;

/**
 * The IAldPortFactory is a polymorphic Ald port interface factory that allows a
 * specific radio implementation to set the number of ALD ports supported by
 * that particular hardware implementation, create the actual ALD port, again
 * specific to the radio implementation and return them as a vector that is
 * stored in the common radio implementation.
 *
 * @note This factory must be implemented by each radio type where its physical
 * characteristics have nothing in common with any existing implementation.
 */
class IAldPortFactory
{
public:

    /**
     * This interface must be implemented by each radio implementation
     * type. The caller passes in a variable by reference that will be used to
     * return the number of ports created. The return value, is a vector of
     * pointers to the common IAldPort interface.
     *
     * Any radio specific implementation code that is aware of the actual ALD port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * @param maxPorts a reference to a variable that is used to return the number of ports
     * @return a vector containing maxPorts Ald ports interface pointers.
     */
    static std::vector< std::shared_ptr<IAldPort> > createPorts( int &maxPorts );


    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a previous created list of ports. The return value, is a vector of
     * pointers to the common IAldPort interface.
     *
     * Any radio specific implementation code that is aware of the actual ALD port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \return a vector containing maxPorts Ald ports interface pointers.
     */
    static std::vector< std::shared_ptr<IAldPort> > getPorts( );
};

}

#endif /* VHI_IALDPORT_H_ */
