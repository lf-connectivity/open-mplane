#ifndef _VRH_ICPRI_H_
#define _VRH_ICPRI_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICpri.h
 * \brief     Pure virtual interface that defines methods needed to access the CPRI links.
 *
 *
 * \details   Pure virtual interface that defines methods needed to access the CPRI links.
 *
 */

#include <iostream>
#include <memory>

#include "GlobalTypeDefs.h"

namespace Mplane
{

// forward declarations go here
class ICpriCore;


/*! \brief Provides a standard interface to the CPRI links.
 *
 * This class collects together the various interfaces used to control and monitor
 * one or more CPRI cores.
 *
 * It must be implemented as a singleton pattern such that only one ICpri
 * can exist.
 *
 * As part of its creation it will instantiate the appropriate number of CpriCore
 * interfaces and store them locally.
 * Accessor methods are used to retrieve a particular instance of the core.
 * Each CpriCore instance is defined by a zero based index, and the interface supports up to MAX_PORTS cores.
 */
class ICpri
{
public:

    /*! \brief  CPRI port type identities
     *
     * Identities for each CPRI port
     */
    enum CpriPortType
    {
        CpriPortSlave    = 0,
        CpriPortMaster   = 1,
        CpriPortInactive = 2
    };

    /*! \brief  CPRI carrier type
     *
     * For CDMA and UMTS the carrier type does not affect the CPRI container
     * mapping.
     * For LTE the container mapping is determined purely on LTE bandwidth.
     */
    enum cpriCarrierType
    {
        cpriNONE = 0,           //!< No container mapping
        cpriLTE_5MHZ,           //!< LTE 5MHZ bandwidth carrier type
        cpriLTE_10MHZ,          //!< LTE 10MHZ bandwidth carrier type
        cpriLTE_15MHZ,          //!< LTE 15MHZ bandwidth carrier type
        cpriLTE_20MHZ,          //!< LTE 20MHZ bandwidth carrier type
    };

    /*! \brief  Get the singleton instance
     *
     * Method defines a static method used to get the single instance of
     * the generic CPRI interface.
     *
     * \note Since this is a static method, it cannot be pure virtual and as such
     * it must have an implementation in the corresponding hardware-specific library.
     *
     * \return reference to the single instance of ICpri interface
     */
    static std::shared_ptr<ICpri> getInterface();


    /*! \brief  Port changed
     *
     * This method is used by the CPRI service to signal to the hardware that a port change has been
     * detected in the service. The ICpri object can then notify any Observers registered with the
     * appropriate ICpriCore
     *
     * \param  cpriPort  the zero-based port being queried
     */
    virtual void signalPortChange(unsigned cpriPort) const =0 ;


    /*! \brief  Get a CPRI core for the specified port
     *
     * Method used to return a specific instance of a CPRI core interface.
     *
     * \param  cpriPort  the zero-based port being queried
     *
     * \return a reference to a CPRI core interface or zero if the index is invalid.
     */
    virtual std::shared_ptr<ICpriCore> getPortCore(UINT32 cpriPort) = 0;

    /*! \brief  Get a CPRI core for the primary slave port
     *
     * Method used to return the instance of the CPRI core interface for the primary slave port
     *
     * \return a reference to a CPRI core interface for the primary slave port.
     */
    virtual std::shared_ptr<ICpriCore> getPrimaryPortCore() = 0;

    /*! \brief  Get the number of CPRI ports supported by the hardware
     *
     * Method used to return the number of CPRI ports supported by the hardware.
     *
     * \return the number of CPRI ports supported by the hardware.
     */
    virtual UINT32 getNumCpriPorts() const = 0;

    /*! \brief  Get the primary slave port number
     *
     * Method used to return the port number of the primary slave port, zero-based.
     *
     * \return the port number of the primary slave port, zero-based.
     */
    virtual UINT32 getPrimaryCpriPort() const = 0;

    /*! \brief  Get the CPRI interface version number
     *
     * Retrieves the running FPGA version number that contains the CPRI core. If not running, the invalid zero
     * version number is returned.
     *
     * \return version number or zero if invalid
     */
    virtual unsigned int getVersion() const = 0;

    /*! \brief  Verify the FPGA version
     *
     * Checks that the FPGA running the CPRI core matches the version expected.
     * This is mainly used as a check in the event of a PROCESSOR reset, where the
     * CPRI FPGA is left untouched (i.e. not reset). We need to verify that the FPGA version
     * running matches that expected by the application.
     *
     * \return true = CPRI FPGA verified OK, false = version mismatch - error
     */
    virtual const bool verifyFpgaVersion() = 0;

    /*! \brief  Enable CPRI loopback
     *
     * Enable CPRI loopback, used for factory tests.
     */
    virtual void enableCpriLoopback() = 0;

    /*! \brief  Disable CPRI loopback
     *
     * Disable CPRI loopback, used for factory tests.
     */
    virtual void disableCpriLoopback() = 0;

    /*! \brief  FPGA Soft Reset
     *
     * Performs a soft reset on the CPRI Interface's host FPGA. This
     * procedure does not reset the uP interface and timebase block.
     */
    virtual void fpgaSoftReset() = 0;

    /*! \brief  Determine if the C&M rate is stable
     *
     * Tests whether the C&M channel rate is stable.
     *
     * \return true if stable, false otherwise
     */
    virtual bool isCMRateStable() = 0;

    /*! \brief  Determine if all clocks are locked
     *
     * Tests whether all CPRI clock/synthesisers are locked.
     *
     * \param  cpriPort  the zero-based port being queried
     *
     * \return true if all clocks are locked, false otherwise
     */
    virtual bool areClocksLocked(UINT32 cpriPort) = 0;


    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~ICpri() { }

    /**
     * Method used for debug only and accessed by test interface.
     * @param os
     */
    virtual void showCpri( std::ostream& os = std::cout ) = 0;

    /**
     * This method is used ot indicate if the CPRI ports are configured with
     * the main port (zero) configured as be a master port, in which case the
     * CPRI controller can modify it's behaviour between client and server
     * modes of operation.
     *
     * @return true if the main port is configured as a master, ie a server mode.
     */
    virtual bool isMainMaster() = 0;

protected:

    /*! \brief  Default constructor
     *
     * Ensure we can only be constructed via an implementing class.
     */
    ICpri(void) { }

};


}  // end namespace Mplane

#endif /* _VRH_ICPRI_H_ */
