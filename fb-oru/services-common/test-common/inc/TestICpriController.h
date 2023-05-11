#ifndef _VRS_TESTICPRICONTROLLER_H_
#define _VRS_TESTICPRICONTROLLER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICpriController.h
 * \brief     Interface to class that controls and monitors the CPRI link
 *
 *
 * \details   The class definition to control and monitor the CPRI link
 *
 */

#include "ICpriPortHandler.h"
#include "ICpriController.h"


namespace Mplane
{


/**
 * This class provides a facility to control and monitor the CPRI link.
 *
 */
class TestICpriController : public ICpriController
{
public:

	TestICpriController() ;


	// Test interface

	/**
	 * Call to update any ICpriPortHandlers that have changed
	 */
	void testNotifyCpriPortObservers() ;

	/**
	 * Get the CpriPortHandler for this port
	 * @param port
	 * @return
	 */
	std::shared_ptr<ICpriPortHandler> testGetPortHandler(unsigned port) ;




	// ICpriController interface

    /**
     * Used to get the single instance allowed of this class
     *
     * \return reference to the class instance
     */
    static ICpriController& getInterface() ;

    /*! \brief  The show function
     */
    virtual void show(std::ostream& os = std::cout);

    /**
     * Implements the ICpriOAM method to do a Master link reset.\n
     * This is a CPRI layer 2 reset.
     *
     * \param resetEnabled is reset enabled or disabled
     */
    virtual void masterLinkResetRequest(bool resetEnabled) ;

    /**
     * Implements the ICpriOAM method to get CPRI link status of the master port
     *
     * \param CpriPortStatus the reference to contain the returned state of the master port (returned by reference)
     *
     * \return true if successful, false otherwise
     */
    virtual bool getMasterLinkStatus(ICpriCore::CpriPortStatus& portStatus) ;

    /**
     * Implements the ICpriOAM method to get CPRI link status of the slave port
     *
     * \param cpriPort the CPRI slave port, zero-based and relates to the number of CPRI ports
     * \param CpriPortStatus the reference to contain the returned state of the slave port (returned by reference)
     *
     * \return true if successful, false otherwise
     */
    virtual bool getSlaveLinkStatus(UINT32 cpriPort, ICpriCore::CpriPortStatus& portStatus) ;

    /**
     * Returns the number of CPRI port handlers. There is one handler for each CPRI port.
     *
     * \return the number of CPRI port handlers.
     */
    virtual UINT32 getNumPortHandlers() ;

    /**
     * Method that allows observers of CPRI ports to attach to specific port handlers.
     *
     * \param cpriPort the CPRI port, zero-based and relates to the number of CPRI port handlers.
     * \param observer the reference to the Observer who wishes to be attached to the port handler.
     *
     * \return true if successful, false otherwise
     */
    virtual bool attachToPortHandler(UINT32 cpriPort, Observer<ICpriPortHandler>& observer) ;

    /**
     * Method that allows observers of CPRI ports to detach from specific port handlers.
     *
     * \param cpriPort the CPRI port, zero-based and relates to the number of CPRI port handlers.
     * \param observer the reference to the Observer who wishes to be detached from the port handler.
     *
     * \return true if successful, false otherwise
     */
    virtual bool detachPortHandler(UINT32 cpriPort, Observer<ICpriPortHandler>& observer) ;

    /**
     * Implements the mandatory IFibreControl method to show the fibre control status.
     */
    virtual void showFibreControl() ;

    /**
     * Implements the mandatory IFibreControl method to start the fibre control.
     * This is invoked from the controlling Service implementation, and is part of the generic start()
     * method. When it is called we know that all software objects have been created and their constructors
     * executed.
     * It is at this point that Observers will register themselves with Subjects, by attaching themselves
     * to them.
     */
    virtual void startFibreControl() ;

    /**
     * Implements the mandatory IFibreControl method to service the fibre control.
     * Is called periodically, eg. 1 second, to perform fibre controlling functions.
     * This will typically be called by a Service implementation.
     */
    virtual void serviceFibreControl() ;

    /**
     * Implements the mandatory IFibreControl method to reset the fibre control
     */
    virtual void resetFibreControl() ;

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
    virtual bool setPortLineRateCapability(UINT32 cpriPort, ICpriController::cpriRateCapabilityMask rateMask) ;

    /**
     * Method to request a CPRI loopback.
     *
     * \param state true to enable loopback, false to disable
     * \param carrier - carrier to perform the loopback on
     * \param txc - tx container to loopback
     * \param rx1c - rx1 container to loopback on
     * \param rx2c - rx2 container to loopback on
     */
    virtual void loopbackRequest(bool state, UINT32 carrier, int txc, int rx1c, int rx2c) ;

    /**
     * Method to get the layer 2 data for a specific CPRI port. The layer 2 data contains:\n
     * LINKID, PMRE, REID
     *
     * \param cpriPort the port to get the L2 info from, zero-based
     * \param cpriL2Info the CPRI L2 info structure (returned by reference)
     *
     * \return true if successful, false otherwise
     */
    virtual bool getLayer2Information(UINT32 cpriPort, ICpriController::cpriL2Info& cpriL2Info) ;

    /**
     * Method to check if there is a free carrier available for loopback testing.
     *
     * \returns true - a carrier is available, false - all carriers configured
     */
    virtual bool isLoopbackCarrierAvailable() ;

    /**
     * Method to set the Protocol Id, see the ARD-0546 spec for valid values.
     *
     * This method will be called directly from the Application's CPRI attributes handler
     *
     * \param pidValue the PID value to set
     */
    virtual void setProtocolId(UINT32 pidValue) ;

    /**
     * Sets the local variable used to trigger the controller tick handler.
     * This will only be used by a user/tester at runtime to control the amount of CPRI debug info.
     *
     * Defaults to false.
     *
     * \param state is set to true to trigger a dump of CPRI info on each controller service tick
     */
    virtual void setTickShowState(bool state) ;

    /**
     * mandatory destructor. Should never be called except by unit test code
     */
    virtual ~TestICpriController();

    /**
     * Gets the current port handler for this port
     * @param port
     * @return pointer to port handler (or null pointer for invalid port)
     */
    virtual std::shared_ptr<ICpriPortHandler> getPortHandler(unsigned port) const override ;

private:
    /**
     * holds port handlers pointers
     */
    std::vector< std::shared_ptr<ICpriPortHandler> > mPortHandlers;


};

} /* namespace Mplane */

#endif /* _VRS_TESTICPRICONTROLLER_H_ */
