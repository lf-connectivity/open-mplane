#ifndef _RADIOSVCS_CPRICONTROLLER_H_
#define _RADIOSVCS_CPRICONTROLLER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriController.h
 * \brief     The class definition to control and monitor the CPRI link
 *
 *
 * \details   The class definition to control and monitor the CPRI link
 *
 */

// Includes go here, before the namespace
#include <vector>
#include <memory>
#include "Loggable.h"


#include "ICpriController.h"
#include "IFibreControl.h"
#include "ICpri.h"
#include "ICpriCore.h"
#include "ICpriPortHandler.h"
#include "ICpriOAM.h"

#include "Observer.hpp"


namespace Mplane
{

/**
 * This class provides a facility to control and monitor the CPRI link.
 *
 */
class CpriController: public ICpriController,
                      public IFibreControl,
                      public ICpriOAM,
                      public Loggable
{
public:

    // allow off target test access
    friend class FibreControlServiceTestCases;
    friend class FibreControlServiceTestCase;

    // alias types
    typedef ICpriController::cpriL2Info cpriL2Info ;
    typedef ICpriController::cpriRateCapabilityMask cpriRateCapabilityMask ;

    /**
     * Used to get the single instance allowed of this class
     *
     * \return reference to the class instance
     */
    static std::shared_ptr<ICpriController> getInterface();

    /*! \brief  The show function required by Loggable
     */
    virtual void show();

    /*! \brief  The show function that outputs to a string stream
     * required by ICpriController
     */
    virtual void show(std::ostream& os);
    virtual void showPort(std::ostream& os, UINT32 portIndex);

    /**
     * Implements the ICpriOAM method to do a Master link reset.\n
     * This is a CPRI layer 2 reset.
     *
     * \param resetEnabled is reset enabled or disabled
     */
    virtual void masterLinkResetRequest(bool resetEnabled);

    /**
     * Implements the ICpriOAM method to get CPRI link status of the master port
     *
     * \param portStatus the reference to contain the returned state of the master port (returned by reference)
     *
     * \return true if successful, false otherwise
     */
    virtual bool getMasterLinkStatus(ICpriCore::CpriPortStatus& portStatus);

    /**
     * Implements the ICpriOAM method to get CPRI link status of the slave port
     *
     * \param cpriPort the CPRI slave port, zero-based and relates to the number of CPRI ports
     * \param portStatus the reference to contain the returned state of the slave port (returned by reference)
     *
     * \return true if successful, false otherwise
     */
    virtual bool getSlaveLinkStatus(UINT32 cpriPort, ICpriCore::CpriPortStatus& portStatus);

    /**
     * Returns the number of CPRI port handlers. There is one handler for each CPRI port.
     *
     * \return the number of CPRI port handlers.
     */
    virtual UINT32 getNumPortHandlers();

    /**
     * Method that allows observers of CPRI ports to attach to specific port handlers.
     *
     * \param cpriPort the CPRI port, zero-based and relates to the number of CPRI port handlers.
     * \param observer the reference to the Observer who wishes to be attached to the port handler.
     *
     * \return true if successful, false otherwise
     */
    virtual bool attachToPortHandler(UINT32 cpriPort, Observer<ICpriPortHandler>& observer);

    /**
     * Method that allows observers of CPRI ports to detach from specific port handlers.
     *
     * \param cpriPort the CPRI port, zero-based and relates to the number of CPRI port handlers.
     * \param observer the reference to the Observer who wishes to be detached from the port handler.
     *
     * \return true if successful, false otherwise
     */
    virtual bool detachPortHandler(UINT32 cpriPort, Observer<ICpriPortHandler>& observer);

    /**
     * Implements the mandatory IFibreControl method to show the fibre control status.
     */
    virtual void showFibreControl();

    /**
     * Implements the mandatory IFibreControl method to start the fibre control.
     * This is invoked from the controlling Service implementation, and is part of the generic start()
     * method. When it is called we know that all software objects have been created and their constructors
     * executed.
     * It is at this point that Observers will register themselves with Subjects, by attaching themselves
     * to them.
     */
    virtual void startFibreControl();

    /**
     * Implements the mandatory IFibreControl method to service the fibre control.
     * Is called periodically, eg. 1 second, to perform fibre controlling functions.
     * This will typically be called by a Service implementation.
     */
    virtual void serviceFibreControl();

    /**
     * Implements the mandatory IFibreControl method to reset the fibre control
     */
    virtual void resetFibreControl();

    /**
     * Forces a CPRI slave port line rate capability.\n
     * To force a specific line rate then set to a single-bit value for the mask.
     *
     * \note This method is available for test purposes use only!
     *
     * \param cpriPort the slave port affected by this line rate capability, zero-based
     * \param rateMask the line rate mask, each bit represents a different line rate
     *
     * \return true if successful, false otherwise
     */
    virtual bool setPortLineRateCapability(UINT32 cpriPort, ICpriController::cpriRateCapabilityMask rateMask);

    /**
     * Method to request a CPRI loopback.
     *
     * \param state true to enable loopback, false to disable
     * \param carrier - carrier to perform the loopback on
     * \param txc - tx container to loopback
     * \param rx1c - rx1 container to loopback on
     * \param rx2c - rx2 container to loopback on
     */
    virtual void loopbackRequest(bool state, UINT32 carrier, int txc, int rx1c, int rx2c);

    /**
     * Method to get the layer 2 data for a specific CPRI port. The layer 2 data contains:\n
     * LINKID, PMRE, REID
     *
     * \param cpriPort the port to get the L2 info from, zero-based
     * \param cpriL2Info the CPRI L2 info structure (returned by reference)
     *
     * \return true if successful, false otherwise
     */
    virtual bool getLayer2Information(UINT32 cpriPort, ICpriController::cpriL2Info& cpriL2Info);

    /**
     * Method to check if there is a free carrier available for loopback testing.
     *
     * \returns true - a carrier is available, false - all carriers configured
     */
    virtual bool isLoopbackCarrierAvailable();

    /**
     * Method to set the Protocol Id, see the ARD-0546 spec for valid values.
     *
     * This method will be called directly from the Application's CPRI attributes handler
     *
     * \param pidValue the PID value to set
     */
    virtual void setProtocolId(UINT32 pidValue);

    /**
     * Sets the local variable used to trigger the controller tick handler.
     * This will only be used by a user/tester at runtime to control the amount of CPRI debug info.
     *
     * Defaults to false.
     *
     * \param state is set to true to trigger a dump of CPRI info on each controller service tick
     */
    virtual void setTickShowState(bool state);

    /**
     * mandatory destructor. Should never be called except by unit test code
     */
    virtual ~CpriController();

    /**
     * Gets the current port handler for this port
     * @param port
     * @return pointer to port handler (or null pointer for invalid port)
     */
    virtual std::shared_ptr<ICpriPortHandler> getPortHandler(unsigned port) const override ;


protected:
    /**
     *
     * \param sfpLogic a reference to the CpriSfpControlLogic class that contains customer-specific SFP control logic
     */
    explicit CpriController(std::shared_ptr<ICpriSfpControlLogic> sfpLogic);


private:

    /**
     * \todo how do we handle the ARD-0546 attributes in the General design.
     * How are the attributes handled, data validated and updated by the application.
     *
     * The CPRI controller needs to update:\n
     *  - CPRIDELAY
     *  - PROTOCOL
     *  - CPRIDESC
     *  - CPRISTAT
     *  - SFPDATA
     */

    /**
     *  The PID supported.
     *  IQ format: TDD LTE uses 15-bit DL/UL coding
     */
    static const UINT32 PID_SUPPORTED = 4;

    /**
     * Method to do the default setup for the CPRI core, and should be called as part of the start()
     * implementation, which is the part of the controlled system bringup sequence.
     */
    void defaultCoreSetup();

    /**
     * Method to enable slave loopback mode
     */
    void enableSlaveLoopback();

    /**
     * Method to disable slave loopback mode
     */
    void disableSlaveLoopback();

    /**
     * Method to enable master reset.\n
     * Initiates a master link reset. After short delay (eg. 20ms) the link should be disabled to stop downstream
     * RRH from continually resetting.
     *
     * \param port the Master port, zero-based
     */
    void enableMasterReset(UINT32 port);

    /**
     * Method to disable master reset.\n
     * The second half of a master link reset. The link must be disabled after doing the link reset to stop downstream
     * RRH from continually resetting.
     *
     * \param port the Master port, zero-based
     */
    void disableMasterReset(UINT32 port);

    /**
     * Method to reset all master ports.
     */
    void resetMasterPorts();

    /**
     * Method to reset master port leaving its state unchanged. Could involve putting the master core into and
     * then out of reset.
     *
     * \param port the Master port, zero-based
     */
    void resetMasterPort(UINT32 port);

    /**
     * Method to update the OAM Slave CPRI status. This method is called whenever there is a
     * change in a slave port status.
     * It reports changes in the CPRI port status [to OAM], by using the notify() interface to the OAM observer.
     * It is the OAM implementation that handles a CPRI link that toggles down then
     * up as part of its DHCP handling.
     */
    void updateOAMSlaveCpriState();

    /**
     * Method to populate the ARD-0546 attribute CPRIDESC.
     * \note this is included here until the design for ARD-0546 attribute handling is done. This should really go
     * into an ARD-0546 attribute interface class
     */
    void populateCpriDesc();

    /**
     * Method to populate the ARD-0546 attribute CPRISTAT
     * \note this is included here until the design for ARD-0546 attribute handling is done. This should really go
     * into an ARD-0546 attribute interface class
     */
    void populateCpriStat();

    /**
     * Method to populate the ARD-0546 attribute SFPDATA
     * \note this is included here until the design for ARD-0546 attribute handling is done. This should really go
     * into an ARD-0546 attribute interface class
     */
    void populateSfpData();

    /**
     * Performs the CPRI slave port handling, which includes the state machine logic.
     * Called periodically, usually once per second, to monitor the CPRI slave port status.
     */
    bool slavePortHandling();

    /**
     * Performs the CPRI master port handling, which includes the state machine logic.
     * Called periodically, usually once per second, to monitor the CPRI masterport status.
     */
    bool masterPortHandling();

    /**
     * Determine whether this RRH is at the end of a chain.
     * Depends on the status of the Master port(s).
     * All master ports must be disabled or link down for it to be set to 'end of chain'
     */
    void updateEndRE();

    /**
     * Notify CPRI port observers of a change in slave or master port status.
     */
    void notifyCpriPortObservers();

    /**
     * Display the state variables used in the controller tick handler, a debug and tester aid
     */
    void controllerTickShow();


private:
    /**
     * Indicates if this RE (RRH) is the last one in a daisy chain.
     *
     * Defaults to true.
     */
    bool mIsEndRE;

    /**
     * holds port handlers pointers
     */
    std::vector< std::shared_ptr<ICpriPortHandler> > mPortHandlers;

    /**
     * The available carrier on which to perform CPRI loopback
     *
     * Defaults to 1, the first carrier.
     */
    UINT32 mLoopbackCarrier;

    /**
     * Local flag to indicate if the controller has been started.
     * Will block any servicing while not started.
     *
     * Defaults to false.
     */
    bool mControllerStarted;

    /**
     * Local flag to indicate when the controller is executing a service event.
     * Will block another service request while one is in progress.
     *
     * Defaults to false.
     */
    bool mServiceInProgress;

    /**
     * Local flag to indicate if more controller debug is to be dumped out during each service tick handling.
     *
     * Set to true to enable more debug output.
     *
     * Defaults to false.
     */
    bool mControllerTickShowState;

    /**
     * Keep a reference to he hardware cpri controller interface
     */
    std::shared_ptr<ICpri> mCpri;


};

} /* namespace Mplane */

#endif /* _RADIOSVCS_CPRICONTROLLER_H_ */
