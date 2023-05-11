#ifndef _RADIOSVCS_CPRIPORTHANDLING_H_
#define _RADIOSVCS_CPRIPORTHANDLING_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriPortHandling.h
 * \brief     The class definition to control and monitor the CPRI link
 *
 *
 * \details   The class definition to control and monitor the CPRI link
 *
 */

// Includes go here, before the namespace
#include <vector>
#include <memory>


#include "ICpriPortHandler.h"
#include "ICpri.h"
#include "ICpriCore.h"
#include "ICommonRadioFaults.h"

#include "Loggable.h"
#include "Observer.hpp"
#include "FaultOwner.h"

#include "fpga/IFpgaSystemRegs.h"

//#include "CpriController.h"


// Uncomment to add extra verbose debugging useful while developing the state machines
//#define DEBUG_CPRI_CONTROL

namespace Mplane
{

// forward declare classes here
class CpriSfpControlLogic;

/**
 * This class provides a facility to control and monitor the CPRI link.
 *
 * There is one instance of this class for each CPRI port.
 *
 * This class provides a Subject for observers to attach to if they want to be informed when
 * CPRI port changes state.
 */
class CpriPortHandler: public ICpriPortHandler,
                       public Loggable
{
public:

    // allow off target test access
    friend class FibreControlServiceTestCases;
    friend class FibreControlServiceTestCase;

    class LossOfSignalOwner: public FaultOwner
    {
    public:
    	explicit LossOfSignalOwner( UINT32 path );

        std::shared_ptr<IFault> getFault();

        void set();

        void clear();

    protected:
        std::shared_ptr<IFault> mFault;
    };

    class LossOfFrameOwner: public FaultOwner
    {
    public:
    	explicit LossOfFrameOwner( UINT32 path );

        std::shared_ptr<IFault> getFault();

        void set();

        void clear();

    protected:
        std::shared_ptr<IFault> mFault;
    };

    class ServiceAccessPointDefectIndOwner: public FaultOwner
    {
    public:
    	explicit ServiceAccessPointDefectIndOwner( UINT32 path );

        std::shared_ptr<IFault> getFault();

        void set();

        void clear();

    protected:
        std::shared_ptr<IFault> mFault;
    };

    class RemoteAlarmIndicationOwner: public FaultOwner
    {
    public:
    	explicit RemoteAlarmIndicationOwner( UINT32 path );

        std::shared_ptr<IFault> getFault();

        void set();

        void clear();

    protected:
        std::shared_ptr<IFault> mFault;
    };

protected:
    /** the constructor is supplied with the port instance number and the SFP control logic reference.
     *
     * \param instance is the port number instance, zero-based
     * \param sfpLogic is a reference to the class that contains specifics about the SFP control logic
     */
    CpriPortHandler(UINT32 instance, std::shared_ptr<ICpriSfpControlLogic> sfpLogic);

public:
    virtual ~CpriPortHandler();

    static const int MASTER_CM_RETRY_COUNT = 64; //! a 250 msec update rate this is 16 seconds

    /**
     * structure to contain the state of the CPRI slave port for OAM reporting
     */
    struct cpriOAMPortStatus
    {
        /**
         * Indicates the current CPRI link overall port status.
         * This is the status reported to the OAM.
         *
         * true = link up, false = link down
         */
        bool cpriLinkState;

        /**
         * Indicates the last CPRI port status reported to the OAM.
         *
         * true = link up, false = link down
         */
        bool lastOAMReportedCpriLinkState;
    };

    /**
     * Factory for creating instances of this CpriPortHandler for a particular port
     * @param port
     * @return shared pointer to new instance
     */
    static std::shared_ptr<ICpriPortHandler> factory(unsigned port, std::shared_ptr<ICpriSfpControlLogic> sfpLogic) ;


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
    virtual CpriPortHandler::CpriSMStates getSmState() override ;

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

    /**
     * Clears the fixed line rate setting, restoring normal operation
     * @return true if ok
     */
    virtual bool clearFixedLineRate() override ;


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
    virtual void forceFixedLineRate(ICpriCore::LineRate lineRate) override ;


protected:

    /**
     * the preferred protocol version of the core on link negotiation.
     */
    static const UINT16 PREFERRED_PROTOCOL_VALUE = 2;

    /**
     * The preferred value used by the core on link negotiation, for a common rate with its peer.
     * The value must be between 20 and 63, 20 is the highest bandwidth.
     */
    static const UINT16 PREFERRED_ETHERNET_POINTER_VALUE = 20;

    /**
     * The preferred HDLC rate for the link. This sets the initial value the core uses in negotiating a common
     * rate with its peer. It should be set before link initialisation.
     */
    static const UINT16 PREFERRED_HDLC_RATE_VALUE = 7;

    /**
     * Method to display the port status.
     *
     * \param portStatus the port status structure to display
     * \param os the stream to output to
     */
    virtual void showPortStatus(ICpriCore::CpriPortStatus& portStatus, std::ostream& os);

    /**
     * Method to display the port control info.
     *
     * \param portControl the port control structure to display
     * \param os the stream to output to
     */
    virtual void showPortControl(ICpriCore::CpriPortControl& portControl, std::ostream& os);

    /**
     * Method to deal with changes to port status.
     *
     * \param newStatus the new state of the CPRI port
     */
    virtual void portStatusChanged(ICpriCore::CpriPortStatus newStatus);

    /**
     * Performs the CPRI slave state machine logic.
     * Called periodically, usually once per second, to monitor the CPRI slave port status.
     * The port can be in one of the following states:\n
     * - STATE_INITIAL: \n
     * - STATE_BAD: \n
     * - STATE_TRANSITION: \n
     * - STATE_GOOD: \n
     *
     * \return true if there is a change in the port status, false otherwise
     */
    virtual bool slaveStateMachine();

    /**
     * Performs the CPRI master state machine logic.
     * Called periodically, usually once per second, to monitor the CPRI master port status.
     * The port can be in one of the following states:\n
     * - STATE_INITIAL: \n
     * - STATE_BAD: \n
     * - STATE_TRANSITION: \n
     * - STATE_GOOD: \n
     *
     * \return true if there is a change in the port status, false otherwise
     */
    virtual bool masterStateMachine();

    /**
     * Method to handle what happens when the Slave port status changes to up
     */
    virtual void setSlavePortLinkUp();

    /**
     * Method to handle what happens when the Master port status changes to up
     */
    virtual void setMasterPortLinkUp();

    /**
     * Method to handle what happens when the Slave port status changes to down
     */
    virtual void setSlavePortLinkDown();

    /**
     * Method to handle what happens when the Master port status changes to down
     */
    virtual void setMasterPortLinkDown();

    /**
     * Initialises the ICpriCore::CpriPortControl with common defaults used by both master and slave ports.
     */
    virtual void setupDefaults();

    /**
     * Checks to see if auto-negotiation needs to be set up. Will trigger a new setup if the allowable
     * line rates change AND there is at least one valid line rate to set.
     *
     * This is called repeatedly in the state machine while powering up
     */
    virtual void checkAutoNeg();

    /**
     * Method to do default slave port setup for Auto Negotiating. This is the preferred method of setting
     * the line rate.\n
     * It will be called as part of the default core setup and if re-enabling the slave port if it has been disabled.
     */
    virtual void setupAutoNeg();

    /**
     * Get the current setting for the allowable line rates
     */
    virtual ICpriCore::LineRateCapability getAllowableRates() ;

    /**
     * Method to update the topology data for the CPRI port, is only set for slave ports.
     */
    virtual void updateTopologyData();

    /**
     * Method to get the current CPRI port status.
     * Reads the core status.
     *
     * \return CpriPortStatus the port status structure
     */
    virtual ICpriCore::CpriPortStatus getCpriPortStatus();

    /**
     * Method to test if the line rate is supported.
     *
     * \param lineRate the line rate
     *
     * \return true if supported, false otherwise
     */
    virtual bool isLineRateSupported(ICpriCore::LineRate lineRate);

    virtual const char* getCoreModeString(std::shared_ptr<ICpriCore> rCore);

    /**
     * Method to get the preferred protocol value for the core.
     *
     * Used once when the fibre is connected and before the core is taken out of reset.
     *
     * \return the preferred protocol value for the core.
     */
    virtual UINT16 getPreferredProtocolValue();

    /**
     * Method to get the preferred ethernet pointer value for the core.
     *
     * Used once when the fibre is connected and before the core is taken out of reset.
     *
     * \return the preferred ethernet pointer value for the core.
     */
    virtual UINT16 getPreferredEthPointerValue();

    /**
     * Method to get the preferred HDLC rate value for the core.
     *
     * Used once when the fibre is connected and before the core is taken out of reset.
     *
     * \return the preferred HDLC rate value for the core.
     */
    virtual UINT16 getPreferredHdlcRateValue();

    /**
     * Method to return the fibre-connected status
     *
     * \param portStatus the port status
     *
     * \return true when fibre connected, false otherwise
     */
    virtual bool isFibreConnected(ICpriCore::CpriPortStatus portStatus);

    /**
     * Method to return the status of the PLLs
     *
     * \param portStatus the port status
     *
     * \return true when clocks are locked, false otherwise
     */
    virtual bool areClocksLocked(ICpriCore::CpriPortStatus portStatus);

    /**
     * Method to test if the port status has changed
     *
     * \param portStatus the port status
     *
     * \return true if the port status has changed, false otherwise
     */
    virtual bool hasPortStatusChanged(ICpriCore::CpriPortStatus portStatus);

    /**
     * Method that returns the SM state as a string.
     *
     * \return the SM state as a string
     */
    virtual const char* getStateString(ICpriPortHandler::CpriSMStates smState) const;

    virtual void updateCpriFaults( void );
	virtual void updateLossOfSignalMajorFault( void ); //!> CPRI 0 Loss of signal Major fault update method
	virtual void updateLossOfFrameMajorFault( void );  //!> CPRI 0 Loss of frame Major fault update method
	virtual void updateServiceAccessPointDefectIndMajorFault( void ); //!> CPRI 0 SAP defect indication Major fault update method
	virtual void updateRemoteAlarmIndicationMajorFault( void );       //!> CPRI 0 RAI fault update method

	virtual ICpriCore::LineRateCapability rateToCapability(ICpriCore::LineRate lineRate) const ;

protected:

    UINT32 mPort;

    /**
     * Contains SFP logic as specified by the customer.
     * Controls for example the logic at link bringup whether to enable or disable the SFP transmit before sync
     * is achieved.
     *
     * Defaults to true.
     */
    std::shared_ptr<ICpriSfpControlLogic> mSfpLogic;

    std::shared_ptr<ICpriCore> mCore;

    std::shared_ptr<ICpri> mCpri;

    /**
     * Indicates if port is logically enabled. Only applies to master port.
     *
     * Defaults to false.
     */
    bool mPortLogicallyEnabled;

    /**
     * Holds the CPRI slave port status that is reported to OAM, by the CpriController.
     * OAM uses this information as part of its DHCP state machine logic.
     */
    cpriOAMPortStatus mCpriOAMSlavePortStatus;

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

    ICpriPortHandler::CpriSMStates mCurrentState;
    ICpriPortHandler::CpriSMStates mNextState;

    /**
     * Indicates if there was a state change during the last execution of the state machine.
     *
     * true if the last state-machine cycle changed state, false otherwise
     *
     * defaults to false
     */
    bool mLastSmStateChanged;

    int mMasterCMretryCount;

    ///  move these to CpriController ???
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

    /**
     * Reference to the command fpag implementation
     */
    std::shared_ptr<IFpgaSystemRegs> mFpga;

    /**
     * Current status of fault reporting gate. We should only report problems if we are in a good state.
     */
    bool mCpriFaultDetectOn;

    /**
     * If set to anything other than UNKOWN then forces port to use this line rate
     */
    ICpriCore::LineRate mFixedLineRate ;

protected:
    std::shared_ptr<ICommonRadioFaults> mFaults;
    std::shared_ptr<LossOfSignalOwner> mLossOfSignalOwner;
    std::shared_ptr<LossOfFrameOwner> mLossOfFrameOwner;
    std::shared_ptr<ServiceAccessPointDefectIndOwner> mServiceAccessPointDefectIndOwner;
    std::shared_ptr<RemoteAlarmIndicationOwner> mRemoteAlarmIndicationOwner;
};

} /* namespace Mplane */

#endif /* _RADIOSVCS_CPRIPORTHANDLING_H_ */
