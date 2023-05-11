#ifndef _RADIOSVCS_ICPRIOAM_H_
#define _RADIOSVCS_ICPRIOAM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICpriOAM.h
 * \brief     The class definition for the interface to the CPRI OAM class
 *
 *
 * \details   The class definition for the interface to the CPRI OAM class
 *
 */

// Includes go here, before the namespace
#include "ICpriCore.h"


namespace Mplane
{

// forward declare classes here

/**
 * This class defines the interface that must be provided to satisfy
 * the requirements of OAM interface to the CPRI controller. The OAM doesn't
 * care who implements the interface.
 */
class ICpriOAM
{
public:

    /**
     * Method used to return a reference to the implementation of this CPRI
     * OAM interface.
     *
     * \return a pointer to an implementation of the CPRI OAM interface
     */
    static std::shared_ptr<ICpriOAM> getInterface();

    /**
     * Method to request a CPRI layer 2 reset on its Master port.
     *
     * \param resetEnabled is reset enabled or disabled
     */
    virtual void masterLinkResetRequest(bool resetEnabled) = 0;

    /**
     * Method to get master CPRI link status
     *
     * \param portStatus the reference to contain the returned state of the master port (returned by reference param)
     *
     * \return true if successful, false otherwise
     */
    virtual bool getMasterLinkStatus(ICpriCore::CpriPortStatus& portStatus) = 0;

    /**
     * Method to get slave CPRI link status, for port cpriPort.
     *
     * \param cpriPort the CPRI slave port, zero-based and relates to the number of CPRI ports
     * \param portStatus the reference to contain the returned state of the slave port (returned by reference param)
     *
     * \return true if successful, false otherwise
     */
    virtual bool getSlaveLinkStatus(UINT32 cpriPort, ICpriCore::CpriPortStatus& portStatus) = 0;

    virtual ~ICpriOAM();


protected:

};


} /* namespace Mplane */

#endif /* _RADIOSVCS_ICPRIOAM_H_ */
