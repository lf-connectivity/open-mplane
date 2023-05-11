#ifndef _VRH_ICPRICORE_H_
#define _VRH_ICPRICORE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICpriCore.h
 * \brief     Pure virtual interface that defines methods needed to access the CPRI Core.
 *
 *
 * \details   Pure virtual interface that defines methods needed to access the CPRI Core.
 *
 */

#include <iostream>

#include "Observer.hpp"
#include "GlobalTypeDefs.h"
#include "ICpri.h"


namespace Mplane
{

/*! \brief Provides a standard interface to the Xilinx CPRI core.
 *
 *  This interface class encompasses everything required to setup and monitor a Xilinx
 *  CPRI interface core.
 *
 *  It can be used with multiple instances, each associated with a particular implementation
 *  of the core within a single FPGA device.
 */
class ICpriCore : public Subject<ICpriCore>
{
public:

    /*! @brief  Core status
     *
     *  Enumerator used to identify the current core status.
     */
    typedef enum StatusCode
    {
        RESET,
        ATTEMPTING_L1_SYNCH,
        PROTOCOL_VERSION_SETUP,
        CM_PARAM_SETUP,
        PASSIVE_MODE,
        OPERATIONAL
    } StatusCode_t;

    static std::string statusToString(StatusCode status) ;

    /*! @brief  CPRI line rate
     *
     *  Used to specify the selected CPRI data rate
     */
    typedef enum LineRate
    {
        RateUnknown	= 0,
        Rate614_4	= 1,    // line rate 1 (614.4 Mbit/s)
        Rate1228_8	= 2,   // line rate 2 (2 x 614.4 Mbit/s)
        Rate2457_6	= 3,   // line rate 3 (4 x 614.4 Mbit/s)
        Rate3072_0	= 4,   // line rate 4 (5 x 614.4 Mbit/s)
        Rate4915_2	= 5,   // line rate 5 (8 x 614.4 Mbit/s)
        Rate6144_0	= 6,   // line rate 6 (10 x 614.4 Mbit/s)
        Rate9830_4	= 7,   // line rate 7 (16 x 614.4 Mbit/s)
        Rate10137_6	= 8,   // line rate 8 (16.5 x 614.4 Mbit/s)

        RateMax = Rate10137_6
    } LineRate_t;

    /**
     * Convert rate to string
     */
    static std::string lineRateToString(LineRate rate) ;

    /**
     * Convert string containing line rate code 1-8 or "auto" into a  line rate
     */
    static LineRate stringToLineRate(const std::string& str) ;

    /**
     * Convert string containing line rate in Mbps or "auto" into a line rate
     * @param str
     * @return
     */
    static LineRate stringMbpsToLineRate(const std::string& str) ;


    /*! @brief  CPRI management channel minimum and maximum rates in Kbps
     *
     *  Used to specify the minimum and maximum selected management channel rates for the current
     *  line rate.
     */
    typedef enum CMRateValue
    {
        CMRateUnknown = 0,
        CMRate240  =  240,
        CMRate480  =  480,
        CMRate960  =  960,
        CMRate1920 = 1920,
        CMRate2400 = 2400,
        CMRate3840 = 3840,
        CMRate4800 = 4800,
        CMRate7680 = 7680,
        CMRate21120 = 21120,
        CMRate42240 = 42240,
        CMRate84480 = 84480,
        CMRate105600 = 105600,
        CMRate168960 = 168960,
        CMRate211200 = 211200,
        CMRate337920 = 337920,
        CMRateDisabled = 0x7fff
    } CMRateValue_t;

    /**
     * Convert CM rate into string
     */
    static std::string cmRateToString(CMRateValue cmrRate) ;

    /*! @brief  Transmit format
     *
     *  Specify the transmit data format of the link, for BBU compatibility
     */
    enum TxFormat
    {
        TxFormat_16  = 16,
        TxFormat_9e2 = 92,
    };

    /*! @brief  CPRI Core Revision
     *
     *  Stores the CPRI Core revision, Major.Minor.
     */
    class Revision
    {
    public:
        Revision() :
            revMajor(0),
            revMinor(0) {};
        UINT16 revMajor;
        UINT16 revMinor;
    };

    /*! @brief  CPRI remote alarms
     *
     *  Stores remote alarms latched on this interface.
     */
    class RemoteAlarms
    {
    public:
        RemoteAlarms() :
            remoteRST(false),
            remoteRAI(false),
            remoteSDI(false),
            remoteLOS(false),
            remoteLOF(false) {};
        bool remoteRST;
        bool remoteRAI;
        bool remoteSDI;
        bool remoteLOS;
        bool remoteLOF;
    };


    /*! @brief  CPRI line rate capability
     *
     *  Indicates the line rate capability of this interface.
     */
    class LineRateCapability
    {
    public:
        LineRateCapability() :
            capableOfRate614_4(false),
            capableOfRate1228_8(false),
            capableOfRate2457_6(false),
            capableOfRate3072_0(false),
            capableOfRate4915_2(false),
            capableOfRate6144_0(false),
            capableOfRate9830_4(false),
            capableOfRate10137_6(false)
    	{};

        bool operator==(const LineRateCapability& rhs) const
		{
        	if (capableOfRate614_4 != rhs.capableOfRate614_4)
        		return false ;
        	if (capableOfRate1228_8 != rhs.capableOfRate1228_8)
        		return false ;
        	if (capableOfRate2457_6 != rhs.capableOfRate2457_6)
        		return false ;
        	if (capableOfRate3072_0 != rhs.capableOfRate3072_0)
        		return false ;
        	if (capableOfRate4915_2 != rhs.capableOfRate4915_2)
        		return false ;
        	if (capableOfRate6144_0 != rhs.capableOfRate6144_0)
        		return false ;
        	if (capableOfRate9830_4 != rhs.capableOfRate9830_4)
        		return false ;
        	if (capableOfRate10137_6 != rhs.capableOfRate10137_6)
        		return false ;

        	return true ;
		}

        bool operator!=(const LineRateCapability& rhs) const
		{
        	return !operator==(rhs) ;
		}

        bool empty()
        {
        	if (capableOfRate614_4)
        		return false ;
        	if (capableOfRate1228_8)
        		return false ;
        	if (capableOfRate2457_6)
        		return false ;
        	if (capableOfRate3072_0)
        		return false ;
        	if (capableOfRate4915_2)
        		return false ;
        	if (capableOfRate6144_0)
        		return false ;
        	if (capableOfRate9830_4)
        		return false ;
        	if (capableOfRate10137_6)
        		return false ;

        	return true ;
        }

        void clear()
        {
        	capableOfRate614_4 = false ;
        	capableOfRate1228_8 = false ;
        	capableOfRate2457_6 = false ;
        	capableOfRate3072_0 = false ;
        	capableOfRate4915_2 = false ;
        	capableOfRate6144_0 = false ;
        	capableOfRate9830_4 = false ;
        	capableOfRate10137_6 = false ;
        }

        bool capableOfRate614_4;
        bool capableOfRate1228_8;
        bool capableOfRate2457_6;
        bool capableOfRate3072_0;
        bool capableOfRate4915_2;
        bool capableOfRate6144_0;
        bool capableOfRate9830_4;
        bool capableOfRate10137_6;
    };

    /*! @brief  CPRI port status
     *
     *  Structure to contain the state of the CPRI port
     */
    class CpriPortStatus
    {
    public:
        CpriPortStatus() :
            logicallyEnabled(false),
            active(false),
            lineRate(RateUnknown),
            ethernetMinCMBandwidth(CMRateUnknown),
            ethernetMaxCMBandwidth(CMRateUnknown),
            protocolVersion(0),
            remoteSapDefect(false),
            remoteLossOfFrame(false),
            remoteLossOfSync(false),
			remoteAlarmInd(false),
            localLossOfFrame(false),
            localLossOfSync(false),
            mgtPllLock(false),
            mgtTxClockLock(false),
            mgtRxClockLock(false),
            sfpLos(true),
            status( ICpriCore::RESET ){};

        /**
         * is port logically enabled (always true for slave)
         */
        bool logicallyEnabled;

        /**
         *  is port active
         */
        bool active;

        /**
         * current CPRI line rate
         */
        LineRate lineRate;

        /**
         * ethernet C&M link minimum bandwidth
         */
        CMRateValue ethernetMinCMBandwidth;

        /**
         * ethernet C&M link maximum bandwidth
         */
        CMRateValue ethernetMaxCMBandwidth;

        /**
         * the CPRI protocol version
         */
        UINT32 protocolVersion;

        /**
         * Remote SAP defect flag reported from L1 inband protocol
         */
        bool remoteSapDefect;

        /**
         * Remote Loss of Frame flag reported from L1 inband protocol
         */
        bool remoteLossOfFrame;

        /**
         * Remote Loss of Sync flag reported from L1 inband protocol
         */
        bool remoteLossOfSync;

        /**
         * Remote Alarm Indication flag reported from L1 inband protocol
         */
        bool remoteAlarmInd;

        /**
         * Local Loss of Frame flag reported from L1 inband protocol
         */
        bool localLossOfFrame;

        /**
         * Local Loss of Sync flag reported from L1 inband protocol
         */
        bool localLossOfSync;

        /**
         * MGT_PLL_Lock flag indicates if the MGT PLL is locked.
         * true = PLL locked
         */
        bool mgtPllLock;

        /**
         * MGT_Tx_Clock_Lock flag indicates if the MGT Tx Clock generation is locked.
         * true = PLL locked
         */
        bool mgtTxClockLock;

        /**
         * MGT_Tx_Clock_Lock flag indicates if the MGT Rx Clock generation is locked.
         * true = PLL locked
         */
        bool mgtRxClockLock;

        /**
         * SFP Loss of Sync flag indicates if the fibre is connected.
         * true = fibre not connected
         */
        bool sfpLos;

        /**
         * Returns the CPRI Core operational status.
         */
        ICpriCore::StatusCode_t status;
    };

    /*! @brief  CPRI port control
     *
     *  Structure to contain control information for CPRI port
     */
    class CpriPortControl
    {
    public:
        CpriPortControl() :
            txFormat(ICpriCore::TxFormat_9e2),
            ethernetBandwidth(ICpriCore::CMRate960) {};

        /**
         * specify TX format for BBU compatibility
         */
        TxFormat txFormat ;

        /**
         * specify allowable CPRI rates
         */
        LineRateCapability allowableRates;

        /**
         * Specify Ethernet bandwidth rates.
         * This maps directly to CM-Rate, and the ethernet pointer.
         */
        CMRateValue_t ethernetBandwidth;

    } ;

    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

    /**
     * Method to get the port/fibre number.
     *
     * \return the port number, zero-based
     */
    virtual unsigned getPort() const =0;

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
     * Method to test if the line rate is supported.
     *
     * \param lineRate the line rate
     *
     * \return true if supported, false otherwise
     */
    virtual bool isLineRateSupported(ICpriCore::LineRate lineRate) =0 ;


    /*! @brief  Take the core out of reset
     *
     *  Method used to take the core out of reset to start normal
     *  operation .
     */
    virtual void takeCoreOutOfReset() = 0;

    /*! @brief  Place the core in reset
     *
     *  Places the core and holds it in reset.
     */
    virtual void putCoreIntoReset() = 0;

    /*! @brief  Determine if the core is in reset
     *
     *  Tests whether the core is currently held in reset.
     *
     * @return true if in reset
     */
    virtual bool isCoreOutOfReset() = 0;

    /*! @brief  reset the core
     *
     *  Resets the core by putting the core into reset and then taking
     *  it out of reset.
     */
    virtual void resetCore() = 0;

    /*! @brief  Get the core status
     *
     *  Method returns the CPRI core status as an enumerated value of type StatusCode;
     *
     *  @see StatusCode
     *
     *  @return a type defined enumerator for the current state
     */
    virtual ICpriCore::StatusCode_t getStatusCode() = 0;

    /*! @brief  Set the preferred CPRI protocol version of the core
     *
     *  Method used to set the preferred CPRI protocol version of the core.
     *
     *  @param  prefProtValue    the requested value
     */
    virtual void setPreferredProtocolVersion(UINT16 prefProtValue) = 0;

    /*! @brief  Get the preferred CPRI protocol version of the core
     *
     *  Method used to get the preferred CPRI protocol version of the core.
     *
     *  @return the preferred protocol version value.
     */
    virtual UINT16 getPreferredProtocolVersion() = 0;

    /*! @brief  Get the current CPRI protocol version of the core
     *
     *  Method used to get the current CPRI protocol version of the core.
     *
     *  @return the current protocol version value.
     */
    virtual UINT16 getCurrentProtocolVersion() = 0;

    /*! @brief  Determine if an alarm is active
     *
     *  Tests whether there is an alarm active. This is a current snapshot
     *  as the alarm status may be continually changing.
     *
     *  @return true if an alarm is active
     */
    virtual bool isAlarmCurrentlyActive() = 0;

    /*! @brief  Read remote alarms
     *
     *  Retrieves the current status of the remote alarms. These
     *  are an un-latched snapshot.
     *
     *  @return the remote alarms status
     */
    virtual RemoteAlarms readRemoteAlarms() = 0;

    /*! @brief  Determine if SFP_LOS is active
     *
     *  Method returns true if the SFP loss of signal alarm is present. This is a current
     *  snapshot and indicates if a fibre is connected.
     *
     * @return true when SFP_LOS present, otherwise false
     */
    virtual bool haveSFPLOS() = 0;

    /*! @brief  Determine if LOS is active
     *
     *  Method returns true if the loss of signal alarm is present. This is a current
     *  snapshot as the alarm status may be continually changing.
     *
     * @return true when LOS present, otherwise false
     */
    virtual bool haveLOS() = 0;

    /*! @brief  Determine if LOF is active
     *
     *  Method returns true if the loss of frame alarm is present. This is a current
     *  snapshot as the alarm status may be continually changing.
     *
     *  @return true when LOF present, otherwise false
     */
    virtual bool haveLOF() = 0;

    /*! @brief  Determine if the core is a slave
     *
     *  Method returns true if core is configured as a slave.
     *
     *  @return true if core is slave, otherwise false.
     */
    virtual bool isSlave() = 0;

    /*! @brief  Determine if the core is a master
     *
     *  Method returns true if core is configured as a master
     *
     *  @return true if core is master, otherwise false.
     */
    virtual bool isMaster() = 0;

    /*! @brief  Determine if the core is inactive
     *
     *  Method returns true if core is not configured, i.e. is inactive, and is neither a slave or master
     *
     *  @return true if core is inactive, otherwise false.
     */
    virtual bool isInactive() = 0;

    /*! @brief  Get the Ethernet pointer
     *
     *  Method returns the current Ethernet pointer value, a value between
     *  20 and 63, where 20 is the highest bandwidth. A value of 0 indicates
     *  the Ethernet pointer has not been set.
     *
     *  The range 20-63 is defined by the CPRI specification.
     *
     *  This value along with the line rate value is used to determine the ethernetCMBandwidth.
     *
     *  @return current Ethernet pointer
     */
    virtual UINT16 getCurrentEthernetPointer() = 0;

    /*! @brief  Read word Z.0.0
     *
     *  Method used to return the received sub-channel 2 control word 0.\n
     *  CPRI specification control word Z.0.0.
     *
     *  @return RSC2 word 0.
     */
    virtual UINT16 readRxSubChannel2Word0() = 0;

    /*! @brief  Read word Z.66.0
     *
     *  Method used to return the received sub-channel 2 control word 1.\n
     *  CPRI specification control word Z.66.0.
     *
     *  @return RSC2 word 1.
     */
    virtual UINT16 readRxSubChannel2Word1() = 0;

    /*! @brief  Read word Z.130.0
     *
     *  Method used to return the received sub-channel 2 control word 2.\n
     *  CPRI specification control word Z.130.0.
     *
     *  @return RSC2 word 2.
     */
    virtual UINT16 readRxSubChannel2Word2() = 0;

    /*! @brief read word Z.194.0
     *
     *  Method used to return the received sub-channel 2 control word 3.\n
     *  CPRI specification control word Z.194.0.\n
     *  This register contains the remote alarm indications that are latched and may be accessed
     *  using the getLatchedAlarms() method.
     *
     *  @return RSC2 word 3.
     */
    virtual UINT16 readRxSubChannel2Word3() = 0;

    /*! @brief  Reset the Ethernet interface for both the Tx and Rx directions.
     *
     *  Method used to reset the TX and RX CPRI Ethernet interfaces, for use when individual Tx and Rx resets
     *  are not supported.
     */
    virtual void cpriResetEthernet() = 0;

    /*! @brief  Reset the transmit Ethernet interface
     *
     *  Method used to reset the TX CPRI Ethernet interfaces.
     */
    virtual void cpriResetEthernetTx() = 0;

    /*! @brief  Reset the receive Ethernet interface
     *
     *  Method used to reset the RX CPRI Ethernet interfaces.
     */
    virtual void cpriResetEthernetRx() = 0;

    /*! @brief  Get the GTP position
     *
     *  Method used to get the GTP transceiver barrel shift position.
     *
     *  @return the transceiver barrel shift position.
     */
    virtual UINT16 getGTPBarrelShiftPos() = 0;

    /*! @brief  Set the GTP position
     *
     *  Method used to set the GTP transceiver barrel shift position.
     *
     *  @param  shiftValue  the transceiver barrel shift position.
     */
    virtual void setGTPBarrelShiftPos(UINT16 shiftValue) = 0;

    /*! @brief  Set the preferred Ethernet pointer
     *
     *  Method used to set the preferred Ethernet pointer value. The value must
     *  be between 20 and 63, 20 being the highest bandwidth.
     *
     *  @param  prefEthPtrValue    the requested value
     */
    virtual void setPreferredEthernetPointer(UINT16 prefEthPtrValue) = 0;

    /*! @brief  Get the preferred Ethernet pointer
     *
     *  Method used to get the preferred Ethernet pointer value.
     *
     *  @return the preferred Ethernet pointer value.
     */
    virtual UINT16 getPreferredEthernetPointer() = 0;

    /*! @brief  Set the preferred HDLC rate
     *
     *  Method used to set the preferred HDLC rate value.
     *
     *  @param  prefHdlcRateValue    the requested value
     */
    virtual void setPreferredHdlcRate(UINT16 prefHdlcRateValue) = 0;

    /*! @brief  Get the preferred HDLC rate
     *
     *  Method used to get the preferred HDLC rate value.
     *
     *  @return the preferred HDLC rate value.
     */
    virtual UINT16 getPreferredHdlcRate() = 0;

    /*! @brief  Get the CPRI line rate
     *
     *  Method used to read the current CPRI line rate.
     *
     *  @return the line rate register.
     */
    virtual ICpriCore::LineRate_t getCurrentLineRate() = 0;

    /*! @brief  Get the line rate capabilities
     *
     *  Method used to return all the line rates the core is capable of.
     *
     *  @return the line rate capabilities.
     */
    virtual LineRateCapability getLineRateCapability() = 0;

    /*! @brief  Set the line rate capabilities to Null, i.e. no line rate
     *
     *  Method used to set the line rate capabilities to Null, thereby inhibiting any attempt to sync by the core.
     */
    virtual void setNoLineRateCapability() = 0;

    /*! @brief  Set the line rate capabilities
     *
     *  Method used to set the line rate capabilities.
     *
     *  @param  rateCapability  the line rate capabilities.
     */
    virtual void setLineRateCapability(LineRateCapability rateCapability) = 0;

    /*! @brief  Enable link reset request
     *
     *  Transmits the link reset request. Currently only applies to the master core and is ignored
     *  on the slave.
     */
    virtual void enableTransmitResetRequest() = 0;

    /*! @brief  Disable link reset request
     *
     *  Stops transmitting the link reset request. Currently only applies to the master core and
     *  is ignored on the slave.
     */
    virtual void disableTransmitResetRequest() = 0;

    /*! @brief  Determine if link reset ack is active
     *
     *  Tests whether the transmit reset acknowledgement is active.
     *
     *  @return true if active
     */
    virtual bool isTransmitResetAckActive() = 0;

    /*! @brief  Set the transmit alarm SDI to on
     */
    virtual void setTxAlarmSdi() = 0;

    /*! @brief  Set the transmit alarm SDI to off
     */
    virtual void clearTxAlarmSdi() = 0;

    /*! @brief  Determine if the transmit SAP defect is active
     *
     *  Tests whether the transmit SAP is active.
     *
     *  @return true if active
     */
    virtual bool isTransmitSapDefectActive() = 0;

    /*! @brief  Enable the slave transmit
     *
     *  Enables the transmit on the slave, turns the optical laser on.
     */
    virtual void slaveTransmitEnable() = 0;

    /*! @brief  Disable the slave transmit
     *
     *  Disables the transmit on the slave, turns the optical laser off.
     */
    virtual void slaveTransmitDisable() = 0;

    /*! @brief  Determine if the slave transmit is enabled
     *
     *  Tests whether the slave transmit is enabled.
     *
     *  @return true if enabled, false otherwise
     */
    virtual bool isSlaveTransmitEnabled() = 0;

    /*! @brief  Get the R21 coarse timer
     *
     *  Method used to read the R21 coarse timer value.\n
     *
     *  This is the T14 delay for the master port, and the Toffset delay for the slave port.
     *
     *  @return R21 coarse time value.
     */
    virtual UINT32 getR21CoarseTimer() = 0;

    /*! @brief  Get the R21 FIFO transit time
     *
     *  Method used to return the FIFO transit time value for the R21 coarse time.
     *
     *  @return the 14 bit FIFO transit timer value.
     */
    virtual UINT16 getR21FIFOTransitTime() = 0;

    /*! @brief  Get the PMRE value
     *
     *  Method used on slave cores to retrieve the PMRE value, which indicates the
     *  maximum number of master ports available within the network. For master cores
     *  0 is returned.
     *
     *  @return PMRE maximum masters in network.
     */
    virtual UINT16 getTopologyPMRE() = 0;

    /*! @brief  Get the Link ID
     *
     *  Method used on slave cores to return a number that identifies which link of
     *  Radio Equipment Controller the CPRI link is connected to. This is a value between
     *  1 and the maximum supported by the REC. For master cores 0 is returned.
     *
     *  @return the REC link ID.
     */
    virtual UINT16 getTopologyLinkId() = 0;

    /*! @brief  Get the RE ID
     *
     *  Method used on slave cores to return the remote equipment ID, used to identify
     *  the position of the core in the network chain emanating from the
     *  Radio Equipment Controller. For master cores it is used to read back the REID
     *  that has been set.
     *
     *  @return the remote equipment ID
     */
    virtual UINT16 getTopologyREID() = 0;

    /*! @brief  Set the RE ID
     *
     *  Method used on master CPRI cores to set the outgoing remote equipment ID to be
     *  on the next link in the CPRI chain. This method has no effect on slave cores.
     *
     *  @param  reid    to be sent to the next link in CPRI chain.
     */
    virtual void setTopologyREID(UINT16 reid) = 0;

    /*! @brief  Get the MGT PLL locked status
     *
     *  Method used to return the MGT_PLL_Lock flag status, to indicate if the MGT PLL is locked.
     *
     *  @return true if PLL locked, false otherwise
     */
    virtual bool getMgtPllLock() = 0;

    /*! @brief  Get the MGT Tx Clock generation locked status
     *
     *  Method used to return the MGT Tx Clock flag status, to indicate if the MGT Tx Clock is locked.
     *
     *  @return true if PLL locked, false otherwise
     */
    virtual bool getMgtTxClockLock() = 0;

    /*! @brief  Get the MGT Rx Clock generation locked status
     *
     *  Method used to return the MGT Rx Clock flag status, to indicate if the MGT Rx Clock is locked.
     *
     *  @return true if PLL locked, false otherwise
     */
    virtual bool getMgtRxClockLock() = 0;

    /*! @brief  Set up the CPRI port
     *
     *  Sets up a CPRI port.
     *
     *  @param  portControl reference to the port control parameters
     */
    virtual void setPortParameters(CpriPortControl &portControl) = 0;

    /*! @brief  Get the CPRI port status
     *
     *  Method to get CPRI port status
     *
     *  @return cpri port status structure
     */
    virtual CpriPortStatus getPortStatus() = 0;

    /*! @brief  Get the CPRI Core revision number
     *
     * Retrieves the CPRI Core revision number,
     * bits 0-7:  Minor
     * bits 8-15: Major
     *
     *  @return CPRI Core revision
     */
    virtual UINT16 getRevision() = 0;

    /*! @brief  Method to change the mode for the port, to master or slave
     *
     *  Method used to change the mode for the port, master or slave
     *
     * \param cpriPortType CPRI port type, Slave or Master
     *
     * \return true if successful, false otherwise
     */
    virtual bool changeMode(ICpri::CpriPortType cpriPortType) = 0;

    virtual const char* getStatusCodeString(ICpriCore::StatusCode statusCode) = 0;
    static const char* getCurrentLineRateString(ICpriCore::LineRate rate);
    virtual char* getLineRateCapabilityString(ICpriCore::LineRateCapability rateCap) = 0;
    virtual const char* getCurrentEthernetRateString(ICpriCore::CMRateValue ethRate) = 0;
    virtual const char* getTxFormatString(ICpriCore::TxFormat txFormat) = 0;

    /**
     * Method used for debug only and accessed by test interface.
     * @param os
     */
    virtual void showPort( std::ostream& os = std::cout ) = 0;

    /**
     * Sets the number of unused samples in between valid ones, set to 0 for consecutive samples
     */
    virtual void setWaitSamples(unsigned waitSamples) =0 ;

    /**
     * Get the current setting of wait samples
     */
    virtual unsigned getWaitSamples() const =0 ;


    /*! @brief virtual destructor to prevent compiler warnings
     *
     */
    virtual ~ICpriCore() { };

protected:

    /*! @brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    ICpriCore();

};


}  // end namespace Mplane

#endif /* _VRH_ICPRICORE_H_ */
