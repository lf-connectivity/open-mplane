#ifndef _hardware_COMMONCPRI_H_
#define _hardware_COMMONCPRI_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpri.h
 * \brief     A file to define the CPRI that is common to a radio.
 *
 *
 * \details   A file to define the CPRI that is common to a radio.
 *
 */

// Includes go here, before the namespace
#include <vector>
#include "Loggable.h"
#include "IFibre.h"
#include "ICpri.h"
#include "IFpgaMgr.h"

namespace Mplane
{

// forward class definitions
class CommonCpriCore;


/*! \brief  The Common CPRI Interface class
 *
 * This class provides a common implementation of the ICpri and IFibre interfaces.
 *
 * It extends the hardware interfaces for ICpri and IFibre to allow for any common radio-specific
 * processing to be added.
 * This class can and should be extended and modified where necessary to if the CPRI is
 * replaced with a different core.
 *
 * This common class collects together the various interfaces used to initialise a CPRI Fibre interface
 * and to control and monitor one or more CPRI cores.
 *
 * It must be implemented as a singleton pattern such that only one ICpri can exist.
 *
 * As part of its creation it will instantiate the appropriate number of CpriCore
 * interfaces and store them locally.
 * Accessor methods are used to retrieve a particular instance of the core.
 * Each CpriCore instance is defined by a zero based index, and the interface supports up to MAX_PORTS cores.
 *
 * The singleton class should be instantiated/retrieved by calling the
 * IFibre::getInterface() method. Since static methods cannot be virtual or extended
 * in a sub-class, it is implemented in this class's .cpp source file.
 */
class CommonCpri: public ICpri, public IFibre, public Loggable
{
    friend class CommonCpriTestCase;

    /**
     * This class should be instantiated by calling IFibre::getInterface() or ICpri::getInterface(). See
     * IFibre and ICpri in the VRH repository for further details.\n
     * IFibre and ICpri are declared as a friend of this class so that it can instantiate the otherwise protected
     * constructor.
     */
    friend class ICpri;
    friend class IFibre;

public:

    // public constants

    /**
     * Pass this variable to the Mplane::CommonCpri constructor to configure
     * the main CPRI port (zero) as a master CPRI core.
     */
    static const bool MAKE_MAIN_MASTER;

    virtual ~CommonCpri();

    /*! \brief  Port changed
     *
     * This method is used by the CPRI service to signal to the hardware that a port change has been
     * detected in the service. The ICpri object can then notify any Observers registered with the
     * appropriate ICpriCore
     *
     * \param  cpriPort  the zero-based port being queried
     */
    virtual void signalPortChange(unsigned cpriPort) const override ;


    /*! @brief  The show function required by Loggable
     */
    virtual void show();

    /*! \brief  The initialise method, required by IFibre
     *
     * Method called during system startup, post FPGA image load, to fully
     * initialise the Fibre interface(s).
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise(void);

    /*! \brief  Returns the fibre type for this implementation, required by IFibre
     *
     *  Method returns the fibre type as an enumerated value of type FibreType_t.
     *  The implementation (returned value) will be application specific.
     *
     *  \return a type defined enumerator for the fibre type
     */
    virtual IFibre::FibreType_t getFibreType() const;

    /*! \brief  Get the fibre clock sync source for this implementation, required by IFibre
     *
     *  Method returns the current clock sync source.
     *  The implementation (returned value) will be application specific.
     *
     *  \return the current clock sync source, zero-based integer
     */
    virtual int getFibreClockSyncSource();

    /*! \brief  Get the number of fibre ports supported by the hardware, required by IFibre
     *
     * Method used to return the number of fibre ports supported by the hardware.
     *
     * \return the number of fibre ports supported by the hardware.
     */
    virtual UINT32 getNumPorts() const;

    /*! \brief  Returns the fibre type string, required by IFibre
     *
     *  \return the type as a string
     */
    virtual const char* fibreTypeString() const;

    /*! \brief  Determine if all clocks are locked, required by IFibre
     *
     * Tests whether all Fibre clock/synthesisers are locked.
     *
     * \param  cpriPort  the zero-based port being queried
     *
     * \return true if all clocks are locked, false otherwise
     */
    virtual bool areClocksLocked(UINT32 cpriPort);

    /*! \brief  Get a CPRI core for the specified port, required by ICpri
     *
     * Method used to return a specific instance of a CPRI core interface.
     *
     * \param  cpriPort  the zero-based port being queried
     *
     * \return a reference to a CPRI core interface or zero if the index is invalid.
     */
    virtual std::shared_ptr<ICpriCore> getPortCore(UINT32 cpriPort);

    /*! \brief  Get a CPRI core for the primary slave port
     *
     * Method used to return the instance of the CPRI core interface for the primary slave port
     *
     * \return a reference to a CPRI core interface for the primary slave port.
     */
    virtual std::shared_ptr<ICpriCore> getPrimaryPortCore();

    /*! \brief  Get the number of CPRI ports supported by the hardware, required by ICpri
     *
     * Method used to return the number of CPRI ports supported by the hardware.
     *
     * \return the number of CPRI ports supported by the hardware.
     */
    virtual UINT32 getNumCpriPorts() const;

    /*! \brief  Get the primary slave port number
     *
     * Method used to return the port number of the primary slave port, zero-based.
     *
     * \return the port number of the primary slave port, zero-based.
     */
    virtual UINT32 getPrimaryCpriPort() const;

    /*! \brief  Get the CPRI interface version number, required by ICpri
     *
     * Retrieves the running FPGA version number that contains the CPRI core. If not running, the invalid zero
     * version number is returned.
     *
     * \return version number or zero if invalid
     */
    virtual unsigned int getVersion() const;

    /*! \brief  Verify the FPGA version, required by ICpri, required by ICpri
     *
     * Checks that the FPGA running the CPRI core matches the version expected.
     * This is mainly used as a check in the event of a PROCESSOR reset, where the
     * CPRI FPGA is left untouched (i.e. not reset). We need to verify that the FPGA version
     * running matches that expected by the application.
     *
     * \return true = CPRI FPGA verified OK, false = version mismatch - error
     */
    virtual const bool verifyFpgaVersion();

    /*! \brief  Enable CPRI loopback, required by ICpri
     *
     * Enable CPRI loopback, used for factory tests.
     */
    virtual void enableCpriLoopback();

    /*! \brief  Disable CPRI loopback, required by ICpri
     *
     * Disable CPRI loopback, used for factory tests.
     */
    virtual void disableCpriLoopback();

    /*! \brief  FPGA Soft Reset, required by ICpri
     *
     * Performs a soft reset on the CPRI Interface's host FPGA. This
     * procedure does not reset the uP interface and timebase block.
     */
    virtual void fpgaSoftReset();

    /*! \brief  Determine if the C&M rate is stable, required by ICpri
     *
     * Tests whether the C&M channel rate is stable.
     * For the RRH this occurs  when the master's preferred Ethernet pointer, current pointer and
     * received pointer are the same.
     *
     * \return true if stable, false otherwise
     */
    virtual bool isCMRateStable();

    /**
     * Method used for debug only and accessed by test interface.
     * @param os
     */
    virtual void showCpri( std::ostream& os = std::cout );

    /**
     * This method is used ot indicate if the CPRI ports are configured with
     * the main port (zero) configured as be a master port, in which case the
     * CPRI controller can modify it's behaviour between client and server
     * modes of operation.
     *
     * @return true if the main port is configured as a master, ie a server mode.
     */
    virtual bool isMainMaster();

protected:

    /*! \brief  Default constructor
     *
     * Construct a base common CPRI class, that  supports a common CPRI configuration.
     *
     * A protected constructor is provided for the singleton pattern
     * to return just a single instance of the ICpri interface.
     *
     * @param mainIsMaster defaults to false, is set true then the main CPRI
     * port is configured as a master port.
     * @param numCpriPorts defaults to NUM_CPRI_PORTS which is currently 2.
     * This allows common cpri to configured with a number of ports and not a fixed
     * size, as not all products have the same number of ports.
     */
    explicit CommonCpri( bool mainIsMaster = false, UINT32 numCpriPorts = NUM_CPRI_PORTS);


    /**
     * Gets the initial port type (Slave or Master) for the given port. The
     * port type returned is based on the mMainIsMaster setting. If true then
     * port zero is configured as a master and others are configured as slaves,
     * if false then the main port is configured as a slave and the last
     * available port is a master.
     *
     * \param cpriPort the CPRI port number
     *
     * \return the port type, slave or master
     */
    virtual ICpri::CpriPortType getCpriPortInitialType(UINT32 cpriPort);

    /**
     * Used to clear the list of ICpriCore created in the constructor. Used by derived classes to
     * add new cores
     */
    virtual void clearCpriCores() ;

private:

    static const UINT32 CPRI_PRIMARY_PORT = 0; // the port which is the primary slave
    static const UINT32 NUM_CPRI_PORTS = 2;  // the number of CPRI ports populated on the hardware

    bool mMainIsMaster;   //!> Local member variable to hold the master/slave configuration.
    UINT32 mNumCpriPorts; //!> Local member variable to hold the configured number of CPRI ports

    /**
     * The initialised state
     */
    ReturnType::State mInitialised;


    /**
     * Uses the CommonFpga to set the FPGA regs
     */
    std::shared_ptr<IFpgaFibreRegs> mFpga;

    /**
     * The fibre clock sync source, a zero-based number of the port from which the clock is derived.
     */
    int mFibreClockSource;

protected:
    /**
     * Used internally to hold the instances of CpriCore supported by
     * this interface. Scope is protected to allow sub classes to create
     * the appropriate core types.
     */
    std::vector<std::shared_ptr<ICpriCore>> mCpriCores;

};  // end of class CommonCpri

typedef std::shared_ptr<CommonCpri> CommonCpriPtr;


} /* namespace Mplane */


#endif /* _hardware_COMMONCPRI_H_ */
