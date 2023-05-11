#ifndef _VRS_ICPRIPORTHANDLING_H_
#define _VRS_ICPRIPORTHANDLING_H_

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

#include "ICpri.h"
#include "ICpriCore.h"
#include "ICpriTypes.h"

#include "Observer.hpp"


namespace Mplane
{

/*! \brief Provides a virtual interface to SFP logic
 *
 */
class ICpriSfpControlLogic
{
public:

    ICpriSfpControlLogic() {}
    virtual ~ICpriSfpControlLogic() {}

    /**
     * Control flag used to decide whether to sync with a server SFP with the core in reset.\n
     *
     * When the RRH is connected to a BBU then the BBU may decide to hold off its SFP transmit until it detects
     * that a RRH is connected and transmitting (optical laser light on). In this case the RRH must transmit even
     * though sync has not been achieved with the BBU.\n
     *
     * This applies to Slave ports only.\n
     *
     * Set this to true to enable the SFP transmit and take the core out of reset while sync is being achieved.
     * Set this to false to disable the SFP transmit and keep the core in reset until sync is achieved.
     *
     * Defaults to false.
     */
    virtual bool sfpSlaveTransmitBeforeSync() const =0 ;

};


/**
 * This class provides a facility to control and monitor the CPRI link.
 *
 * There is one instance of this class for each CPRI port.
 *
 * This class provides a Subject for observers to attach to if they want to be informed when
 * CPRI port changes state.
 */
class ICpriPortHandler: public Subject<ICpriPortHandler>
{
public:
    ICpriPortHandler() {} ;

    virtual ~ICpriPortHandler() {} ;

    // CPRI state machine states
    enum CpriSMStates
    {
        STATE_INACTIVE = 0,
        STATE_INITIAL  = 1,
        STATE_BAD,
        STATE_TRANSITION,
        STATE_GOOD,
    } ;


    /**
     * Factory for creating instances of ICpriPortHandler for a particular port
     * @param port
     * @return shared pointer to new instance
     */
    static std::shared_ptr<ICpriPortHandler> factory(unsigned port, std::shared_ptr<ICpriSfpControlLogic> sfpLogic) ;


    /*! \brief  The show function required by Loggable
     */
    virtual void show() =0 ;

    /*! \brief  The show function that outputs to a string stream
     * required by ICpriPortHandler
     *
     * \param os the stream to output to
     */
    virtual void show(std::ostream& os) =0 ;

    /*! @brief  Determine if the port is configured as a slave
     *
     *  Method returns true if core is configured as a slave
     *
     *  @return true if port is slave, otherwise false.
     */
    virtual bool isSlave() =0 ;

    /*! @brief  Determine if the port is configured as a master
     *
     *  Method returns true if core is configured as a master
     *
     *  @return true if port is master, otherwise false.
     */
    virtual bool isMaster() =0 ;

    /**
     * Method to initialise the port status, called during constructor initialisation only.
     * It sets the initial values for local data, it does not affect the CPRI core.
     */
    virtual void initialisePortStatus() =0 ;

    /**
     * Performs the CPRI state machine logic, for however the port is configured.
     * Calls the appropriate state-machine for slave or master logic.
     *
     * \return true if there is a change in the port status, false otherwise
     */
    virtual bool stateMachine() =0 ;

    /**
     * Method to display the current state-machine state.
     */
    virtual void showSmState() =0 ;

    /**
     * Method to get the current link status.
     *
     * \return CpriPortStatus the port status structure
     */
    virtual ICpriCore::CpriPortStatus getLinkStatus() =0 ;

    /**
     * Method to start the port handler.
     * Sets the port status from the core.
     */
    virtual void start() =0 ;

    /**
     * Method that tests if the link is up.
     *
     * \return true is the link is up, false otherwise
     */
    virtual bool isLinkUp() =0 ;

    /**
     * Method to reset port leaving its state unchanged. Could involve putting the core into and
     * then out of reset.
     */
    virtual void resetPort() =0 ;

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
    virtual bool isLinkOK(ICpriCore::CpriPortStatus portStatus) =0 ;

    /**
     * Forces a port line rate capability.\n
     * To force a specific line rate then set to a single-bit value for the mask.
     *
     * This is available for testing use only!
     *
     * \param rateMask the line rate mask, each bit represents a different line rate
     */
    virtual void setPortLineRateCapability(ICpriTypes::cpriRateCapabilityMask rateMask) =0 ;

    /**
     * Method to configure a CPRI slave port, providing the line rate and IQ tx format.
     *
     * \param lineRate the line rate
     * \param txFormat the tx IQ format
     */
    virtual void configSlavePort(ICpriCore::LineRate lineRate,
                                 ICpriCore::TxFormat txFormat) =0 ;

    /**
     * Method to get the current state-machine state.
     *
     * \return the current state-machine state
     */
    virtual CpriSMStates getSmState() =0 ;

    /**
     * Method to initialise the port.
     */
    virtual void initPort() =0 ;

    /**
     * Method to get the port number.
     *
     * \return the port number, zero-based
     */
    virtual UINT32 getPort() =0 ;

    /**
     * Method to get the PMRE value for the primary slave port.
     *
     * \return the PMRE value for the primary slave port
     */
    virtual UINT32 getPmre() =0 ;

    /**
     * Method to get the REID value for the primary slave port.
     *
     * \return the REID value for the primary slave port
     */
    virtual UINT32 getReId() =0 ;

    /**
     * Method to get the LINKID value for the primary slave port.
     *
     * \return the LINKID value for the primary slave port
     */
    virtual UINT32 getLinkId() =0 ;

    /**
     * Method to get the OAM CPRI status for this slave port.
     *
     * \return true = link up, false = link down
     */
    virtual bool getSlaveOamLinkState() =0 ;

    /**
     * Method to get the last reported OAM CPRI status for this slave port.
     *
     * \return true = link up, false = link down
     */
    virtual bool getSlaveLastOamLinkState() =0 ;

    /**
     * Method to set the last reported OAM CPRI status for this slave port.
     * Sets the status to the current status.
     */
    virtual void setSlaveLastOamLinkState() =0 ;


    /**
     * Method to enable master reset.\n
     * Initiates a master link reset. After short delay (eg. 20ms) the link should be disabled to stop downstream
     * RRH from continually resetting.
     */
    virtual void enableReset() =0 ;

    /**
     * Method to disable master reset.\n
     * The second half of a master link reset. The link must be disabled after doing the link reset to stop downstream
     * RRH from continually resetting.
     */
    virtual void disableReset() =0 ;

    /**
     * Method to get the result of the last state-machine cycle.
     *
     * \return true if the last state-machine cycle changed state, false otherwise
     */
    virtual bool hasStateChanged() =0 ;

    /**
     * Method to enable master port when it is in INIT state.
     * Enabling master port resets the core hardware.
     *
     * \param slaveCore the slave core from which the required data is obtained
     */
    virtual void enableMasterPort(std::shared_ptr<ICpriCore> slaveCore) =0 ;

    /**
     * Method to disable master port and place it in INACTIVE state
     */
    virtual void disableMasterPort() =0 ;

    /*! @brief  Method to change the mode for the port, to master or slave
     *
     *  Method used to change the mode for the port, master or slave
     *
     * \param cpriPortType CPRI port type, Slave or Master
     *
     * \return true if successful, false otherwise
     */
    virtual bool changePortMode(ICpri::CpriPortType cpriPortType) =0 ;

    /**
     * Set a single line rate. This is provided so that a user can select the preferred line rate to use for negotiating.
     * Setting this value to UNKNOWN will allow auto selection
     *
     * \param lineRate the line rate
     * \return false if line rate is not supported
     */
    virtual bool setFixedLineRate(ICpriCore::LineRate lineRate) =0 ;

    /**
     * Clears the fixed line rate setting, restoring normal operation
     * @return true if ok
     */
    virtual bool clearFixedLineRate() =0 ;


    /**
     * Set a single line rate. This is provided so that a user can select the preferred line rate to use for negotiating.
     * Setting this value to UNKNOWN will allow auto selection. This method is similar to setFixedLineRate() apart from the fact
     * that setFixedLineRate() checks that the line rate is valid, whereas this method just forces the line rate.
     *
     * NOTE: This method can be used in an ICpriPortHandler constructor method (where the actual allowed line rates are not yet known
     * so setFixedLineRate() will always fail).
     *
     * \param lineRate the line rate
     */
    virtual void forceFixedLineRate(ICpriCore::LineRate lineRate) =0 ;


};

} /* namespace Mplane */

#endif /* _VRS_ICPRIPORTHANDLING_H_ */
