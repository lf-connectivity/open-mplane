#ifndef _VRS_TESTICPRIPORTHANDLING_H_
#define _VRS_TESTICPRIPORTHANDLING_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICpriPortHandling.h
 * \brief     The class definition to control and monitor the CPRI link
 *
 *
 * \details   Interface class defining a subject for CPRI port handling
 *
 */

#include <vector>
#include <memory>
#include "ICpriCore.h"
#include "Observer.hpp"
#include "ICpriPortHandler.h"


namespace Mplane
{

// forward declare classes here

/**
 * This class provides a facility to control and monitor the CPRI link.
 *
 * There is one instance of this class for each CPRI port.
 *
 * This class provides a Subject for observers to attach to if they want to be informed when
 * CPRI port changes state.
 */
class TestICpriPortHandler: public ICpriPortHandler
{
public:
    TestICpriPortHandler(UINT32 instance) ;

    virtual ~TestICpriPortHandler() ;

    // Test Interface

    void testInjectPortStatus(const ICpriCore::CpriPortStatus portStatus) ;
    void testInjectLinkState(const bool linkState) ;
    void testInjectPmre(const UINT32 pmre) ;
    void testInjectLinkId(const UINT32 linkId) ;
    void testInjectReId(const UINT32 reId) ;
    void testInjectSetStateChange(bool state) ;
    void testInjectSetMasterMode(bool master) ;

    // ICpriPortHandler Interface


    /*! \brief  The show function required by Loggable
     */
    virtual void show() override ;

    /*! \brief  The show function that outputs to a string stream
     * required by ICpriPortHandler
     *
     * \param os the stream to output to
     */
    virtual void show(std::ostream& os) override ;

    /*! @brief  Determine if the port is configured as a slave
     *
     *  Method returns true if core is configured as a slave
     *
     *  @return true if port is slave, otherwise false.
     */
    virtual bool isSlave() override ;

    /*! @brief  Determine if the port is configured as a master
     *
     *  Method returns true if core is configured as a master
     *
     *  @return true if port is master, otherwise false.
     */
    virtual bool isMaster() override ;

    /**
     * Method to initialise the port status, called during constructor initialisation only.
     * It sets the initial values for local data, it does not affect the CPRI core.
     */
    virtual void initialisePortStatus() override ;

    /**
     * Performs the CPRI state machine logic, for however the port is configured.
     * Calls the appropriate state-machine for slave or master logic.
     *
     * \return true if there is a change in the port status, false otherwise
     */
    virtual bool stateMachine() override ;

    /**
     * Method to display the current state-machine state.
     */
    virtual void showSmState() override ;

    /**
     * Method to get the current link status.
     *
     * \return CpriPortStatus the port status structure
     */
    virtual ICpriCore::CpriPortStatus getLinkStatus() override ;

    /**
     * Method to start the port handler.
     * Sets the port status from the core.
     */
    virtual void start() override ;

    /**
     * Method that tests if the link is up.
     *
     * \return true is the link is up, false otherwise
     */
    virtual bool isLinkUp() override ;

    /**
     * Method to reset port leaving its state unchanged. Could involve putting the core into and
     * then out of reset.
     */
    virtual void resetPort() override ;

    /**
     * Method to determine if the port link is active (enabled) and
     * error free (meaning no LOS or LOF).
     *
     * NOTE:
     *  For master ports, the SDI alarm is not considered a fault, the Master link is considered up
     *  if SDI bit is set on master.
     *  For slave ports, the SAP defect Indication (SDI) is not considered a fault that should
     *  take down the slave link. The fault handling system will handle the response to all detected faults
     *  and may decide to block the Tx as it is an indication that IQ data is potentially invalid.
     *
     * \param portStatus the port status
     *
     * \return true if link is active and error free
     */
    virtual bool isLinkOK(ICpriCore::CpriPortStatus portStatus) override ;

    /**
     * Forces a port line rate capability.\n
     * To force a specific line rate then set to a single-bit value for the mask.
     *
     * This is available for testing use only!
     *
     * \param rateMask the line rate mask, each bit represents a different line rate
     */
    virtual void setPortLineRateCapability(ICpriTypes::cpriRateCapabilityMask rateMask) override ;

    /**
     * Method to configure a CPRI slave port, providing the line rate and IQ tx format.
     *
     * \param lineRate the line rate
     * \param txFormat the tx IQ format
     */
    virtual void configSlavePort(ICpriCore::LineRate lineRate,
                                 ICpriCore::TxFormat txFormat) override ;

    /**
     * Method to get the current state-machine state.
     *
     * \return the current state-machine state
     */
    virtual ICpriPortHandler::CpriSMStates getSmState() override ;

    /**
     * Method to initialise the port.
     */
    virtual void initPort() override ;

    /**
     * Method to get the port number.
     *
     * \return the port number, zero-based
     */
    virtual UINT32 getPort() override ;

    /**
     * Method to get the PMRE value for the primary slave port.
     *
     * \return the PMRE value for the primary slave port
     */
    virtual UINT32 getPmre() override ;

    /**
     * Method to get the REID value for the primary slave port.
     *
     * \return the REID value for the primary slave port
     */
    virtual UINT32 getReId() override ;

    /**
     * Method to get the LINKID value for the primary slave port.
     *
     * \return the LINKID value for the primary slave port
     */
    virtual UINT32 getLinkId() override ;

    /**
     * Method to get the OAM CPRI status for this slave port.
     *
     * \return true = link up, false = link down
     */
    virtual bool getSlaveOamLinkState() override ;

    /**
     * Method to get the last reported OAM CPRI status for this slave port.
     *
     * \return true = link up, false = link down
     */
    virtual bool getSlaveLastOamLinkState() override ;

    /**
     * Method to set the last reported OAM CPRI status for this slave port.
     * Sets the status to the current status.
     */
    virtual void setSlaveLastOamLinkState() override ;


    /**
     * Method to enable master reset.\n
     * Initiates a master link reset. After short delay (eg. 20ms) the link should be disabled to stop downstream
     * RRH from continually resetting.
     */
    virtual void enableReset() override ;

    /**
     * Method to disable master reset.\n
     * The second half of a master link reset. The link must be disabled after doing the link reset to stop downstream
     * RRH from continually resetting.
     */
    virtual void disableReset() override ;

    /**
     * Method to get the result of the last state-machine cycle.
     *
     * \return true if the last state-machine cycle changed state, false otherwise
     */
    virtual bool hasStateChanged() override ;

    /**
     * Method to enable master port when it is in INIT state.
     * Enabling master port resets the core hardware.
     *
     * \param slaveCore the slave core from which the required data is obtained
     */
    virtual void enableMasterPort(std::shared_ptr<ICpriCore> slaveCore) override ;

    /**
     * Method to disable master port and place it in INACTIVE state
     */
    virtual void disableMasterPort() override ;

    /*! @brief  Method to change the mode for the port, to master or slave
     *
     *  Method used to change the mode for the port, master or slave
     *
     * \param cpriPortType CPRI port type, Slave or Master
     *
     * \return true if successful, false otherwise
     */
    virtual bool changePortMode(ICpri::CpriPortType cpriPortType) override ;

    /**
     * Set a single line rate. This is provided so that a user can select the preferred line rate to use for negotiating.
     * Setting this value to UNKNOWN will allow auto selection
     *
     * \param lineRate the line rate
     * \return false if line rate is not supported
     */
    virtual bool setFixedLineRate(ICpriCore::LineRate lineRate) override ;
    virtual void forceFixedLineRate(ICpriCore::LineRate lineRate) override {}

    virtual bool clearFixedLineRate() override {return true;}

private:
    bool hasPortStatusChanged(ICpriCore::CpriPortStatus portStatus) ;

private:
    UINT32 mPort;


    /**
     * Indicates if port is logically enabled. Only applies to master port.
     *
     * Defaults to false.
     */
    bool mPortLogicallyEnabled;


    /**
     * current port control structure
     */
    ICpriCore::CpriPortControl mPortControl;

    /**
     * holds current port status
     */
    ICpriCore::CpriPortStatus mCurrentPortStatus;

    /**
     * Indicates the current CPRI link overall port status.
     *
     * true = link up, false = link down
     */
    bool mCpriLinkState;


    /**
     * Indicates if there was a state change during the last execution of the state machine.
     *
     * true if the last state-machine cycle changed state, false otherwise
     *
     * defaults to false
     */
    bool mLastSmStateChanged;


    /**
     * Max number of master ports as read from H/W Topology, obtained from FPGA.
     *
     * Valid values are 0-1
     *
     * Defaults to 1.
     */
    UINT32 mCpriPmre;

    /**
     * Remote equipment ID as read from H/W Topology, obtained from FPGA.
     *
     * Valid values are 0-6
     *
     * Defaults to 0.
     */
    UINT32 mCpriReId;

    /**
     * link Id as read from H/W Topology, obtained from FPGA.
     *
     * Valid values are 0-31
     *
     * Defaults to 0.
     */
    UINT32 mCpriLinkId;

    bool mMasterMode ;

};

} /* namespace Mplane */

#endif /* _VRS_TESTICPRIPORTHANDLING_H_ */
