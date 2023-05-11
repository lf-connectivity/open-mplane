#ifndef _hardware_COMMONCPRICORE_H_
#define _hardware_COMMONCPRICORE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpriCore.h
 * \brief     A file to define the CPRI Core that is common to a radio.
 *
 *
 * \details   A file to define the CPRI Core that is common to a radio.
 *
 */

// Includes go here, before the namespace
#include "Loggable.h"
#include "ICpri.h"
#include "ICpriCore.h"
#include "ISfpData.h"
#include "SfpData.h"
#include "IFpgaMgr.h"

namespace Mplane
{

enum CriticalErrorNumbers
{
    CRITICAL_ERROR_INVALID_CPRI_CORE_ID = 1,
    CRITICAL_ERROR_UNSUPPORTED_CPRI_CORE_STATE,
    CRITICAL_ERROR_UNKNOWN_CPRI_LINE_RATE,
    CRITICAL_ERROR_MAX
};

// forward class definitions
enum CpriCoreId
{
    CPRI_SLAVE_CORE,
    CPRI_MASTER_CORE,
    CPRI_NUM_CORES,
    CPRI_INACTIVE_CORE
};

/*! \brief  The Common CPRI Core Interface class
 *
 * This class provides a common implementation of the ICpriCore interface.
 * It extends the hardware interface ICpriCore to allow for any common radio-specific
 * processing to be added.
 * This class can and should be extended and modified where necessary to if the CPRI core is
 * replaced with a different core.
 */
class CommonCpriCore: public virtual ICpriCore, public Loggable
{
    friend class CommonCpriTestCase;


public:
    /**
     * Common CPRI core class constructor.
     *
     * \param cpriPortNumber CPRI port number in range starting from zero
     * \param cpriPortType CPRI port type, Slave or Master
     */
    CommonCpriCore( int cpriPortNumber, ICpri::CpriPortType cpriPortType );


    // public constants

    virtual ~CommonCpriCore() { };

    /*! @brief  The show function required by Loggable
     */
    virtual void show();

    /**
     * Method to get the port/fibre number.
     *
     * \return the port number, zero-based
     */
    virtual unsigned getPort() const override ;


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
     * Method to test if the line rate is supported.
     *
     * \param lineRate the line rate
     *
     * \return true if supported, false otherwise
     */
    virtual bool isLineRateSupported(ICpriCore::LineRate lineRate) override ;

    /*! @brief  Take the core out of reset
     *
     *  Method used to take the core out of reset to start normal
     *  operation .
     */
    virtual void takeCoreOutOfReset();

    /*! @brief  Place the core in reset
     *
     *  Places the core and holds it in reset.
     */
    virtual void putCoreIntoReset();

    /*! @brief  Determine if the core is in reset
     *
     *  Tests whether the core is currently held in reset.
     *
     * @return true if in reset
     */
    virtual bool isCoreOutOfReset();

    /*! @brief  reset the core
     *
     *  Resets the core by putting the core into reset and then taking
     *  it out of reset.
     */
    virtual void resetCore();

    /*! @brief  Get the core status
     *
     *  Method returns the CPRI core status as an enumerated value of type StatusCode;
     *
     *  @see StatusCode
     *
     *  @return a type defined enumerator for the current state
     */
    virtual ICpriCore::StatusCode_t getStatusCode();

    /*! @brief  Set the preferred CPRI protocol version of the core
     *
     *  Method used to set the preferred CPRI protocol version of the core.
     *
     *  @param  prefProtValue    the requested value
     */
    virtual void setPreferredProtocolVersion(UINT16 prefProtValue);

    /*! @brief  Get the preferred CPRI protocol version of the core
     *
     *  Method used to get the preferred CPRI protocol version of the core.
     *
     *  @return the preferred protocol version value.
     */
    virtual UINT16 getPreferredProtocolVersion();

    /*! @brief  Get the current CPRI protocol version of the core
     *
     *  Method used to get the current CPRI protocol version of the core.
     *
     *  @return the current protocol version value.
     */
    virtual UINT16 getCurrentProtocolVersion();

    /*! @brief  Determine if an alarm is active
     *
     *  Tests whether there is an alarm active. This is a current snapshot
     *  as the alarm status may be continually changing.
     *
     *  @return true if an alarm is active
     */
    virtual bool isAlarmCurrentlyActive();

    /*! @brief  Read remote alarms
     *
     *  Retrieves the current status of the remote alarms. These
     *  are an un-latched snapshot.
     *
     *  @return the remote alarms status
     */
    virtual ICpriCore::RemoteAlarms readRemoteAlarms();

    /*! @brief  Determine if SFP_LOS is active
     *
     *  Method returns true if the SFP loss of signal alarm is present. This is a current
     *  snapshot and indicates if a fibre is connected.
     *
     * @return true when SFP_LOS present, otherwise false
     */
    virtual bool haveSFPLOS();

    /*! @brief  Determine if LOS is active
     *
     *  Method returns true if the loss of signal alarm is present. This is a current
     *  snapshot as the alarm status may be continually changing.
     *
     * @return true when LOS present, otherwise false
     */
    virtual bool haveLOS();

    /*! @brief  Determine if LOF is active
     *
     *  Method returns true if the loss of frame alarm is present. This is a current
     *  snapshot as the alarm status may be continually changing.
     *
     *  @return true when LOF present, otherwise false
     */
    virtual bool haveLOF();

    /*! @brief  Determine if the core is a slave
     *
     *  Method returns true if core is configured as a slave.
     *
     *  @return true if core is slave, otherwise false.
     */
    virtual bool isSlave();

    /*! @brief  Determine if the core is a master
     *
     *  Method returns true if core is configured as a master
     *
     *  @return true if core is master, otherwise false.
     */
    virtual bool isMaster();

    /*! @brief  Determine if the core is inactive
     *
     *  Method returns true if core is not configured, i.e. is inactive, and is neither a slave or master
     *
     *  @return true if core is inactive, otherwise false.
     */
    virtual bool isInactive();

    /*! @brief  Read word Z.0.0
     *
     *  Method used to return the received sub-channel 2 control word 0.\n
     *  CPRI specification control word Z.0.0.
     *
     *  @return RSC2 word 0.
     */
    virtual UINT16 readRxSubChannel2Word0();

    /*! @brief  Read word Z.66.0
     *
     *  Method used to return the received sub-channel 2 control word 1.\n
     *  CPRI specification control word Z.66.0.
     *
     *  @return RSC2 word 1.
     */
    virtual UINT16 readRxSubChannel2Word1();

    /*! @brief  Read word Z.130.0
     *
     *  Method used to return the received sub-channel 2 control word 2.\n
     *  CPRI specification control word Z.130.0.
     *
     *  @return RSC2 word 2.
     */
    virtual UINT16 readRxSubChannel2Word2();

    /*! @brief read word Z.194.0
     *
     *  Method used to return the received sub-channel 2 control word 3.\n
     *  CPRI specification control word Z.194.0.\n
     *  This register contains the remote alarm indications that are latched and may be accessed
     *  using the getLatchedAlarms() method.
     *
     *  @return RSC2 word 3.
     */
    virtual UINT16 readRxSubChannel2Word3();

    /*! @brief  Reset the Ethernet interface for both the Tx and Rx directions.
     *
     *  Method used to reset the TX and RX CPRI Ethernet interfaces, for use when individual Tx and Rx resets
     *  are not supported.
     */
    virtual void cpriResetEthernet();

    /*! @brief  Reset the transmit Ethernet interface
     *
     *  Method used to reset the TX CPRI Ethernet interfaces.
     *
     *  Note: The common FPGA does not support an ethernet reset per direction.
     *
     */
    virtual void cpriResetEthernetTx();

    /*! @brief  Reset the receive Ethernet interface
     *
     *  Method used to reset the RX CPRI Ethernet interfaces.
     *
     *  Note: The common FPGA does not support an ethernet reset per direction.
     */
    virtual void cpriResetEthernetRx();

    /*! @brief  Get the GTP position
     *
     *  Method used to get the GTP transceiver barrel shift position.
     *
     *  @return the transceiver barrel shift position.
     */
    virtual UINT16 getGTPBarrelShiftPos();

    /*! @brief  Set the GTP position
     *
     *  Method used to set the GTP transceiver barrel shift position.
     *
     *  @param  shiftValue  the transceiver barrel shift position.
     */
    virtual void setGTPBarrelShiftPos(UINT16 shiftValue);

    /*! @brief  Set the preferred Ethernet pointer
     *
     *  Method used to set the preferred Ethernet pointer value. The value must
     *  be between 20 and 63, 20 being the highest bandwidth.
     *
     *  @param  prefEthPtrValue    the requested value
     */
    virtual void setPreferredEthernetPointer(UINT16 prefEthPtrValue);

    /*! @brief  Get the preferred Ethernet pointer
     *
     *  Method used to get the preferred Ethernet pointer value.
     *
     *  @return the preferred Ethernet pointer value.
     */
    virtual UINT16 getPreferredEthernetPointer();

    /*! @brief  Get the current Ethernet pointer
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
    virtual UINT16 getCurrentEthernetPointer();

    /*! @brief  Set the preferred HDLC rate
     *
     *  Method used to set the preferred HDLC rate value.
     *
     *  @param  prefHdlcRateValue    the requested value
     */
    virtual void setPreferredHdlcRate(UINT16 prefHdlcRateValue);

    /*! @brief  Get the preferred HDLC rate
     *
     *  Method used to get the preferred HDLC rate value.
     *
     *  @return the current HDLC rate value.
     */
    virtual UINT16 getPreferredHdlcRate();

    /*! @brief  Get the CPRI line rate
     *
     *  Method used to read the current CPRI line rate.
     *
     *  @return the line rate register.
     */
    virtual ICpriCore::LineRate_t getCurrentLineRate();

    /*! @brief  Get the line rate capabilities
     *
     *  Method used to return all the line rates the core is capable of.
     *
     *  @return the line rate capabilities.
     */
    virtual ICpriCore::LineRateCapability getLineRateCapability();

    /*! @brief  Set the line rate capabilities to Null, i.e. no line rate
     *
     *  Method used to set the line rate capabilities to Null, thereby inhibiting any attempt to sync by the core.
     */
    virtual void setNoLineRateCapability();

    /*! @brief  Set the line rate capabilities
     *
     *  Method used to set the line rate capabilities.
     *
     *  @param  rateCapability  the line rate capabilities.
     */
    virtual void setLineRateCapability(LineRateCapability rateCapability);

    /*! @brief  Enable link reset request
     *
     *  Transmits the link reset request. Currently only applies to the master core and is ignored
     *  on the slave.
     */
    virtual void enableTransmitResetRequest();

    /*! @brief  Disable link reset request
     *
     *  Stops transmitting the link reset request. Currently only applies to the master core and
     *  is ignored on the slave.
     */
    virtual void disableTransmitResetRequest();

    /*! @brief  Determine if link reset ack is active
     *
     *  Tests whether the transmit reset acknowledgement is active.
     *
     *  @return true if active
     */
    virtual bool isTransmitResetAckActive();

    /*! @brief  Set the transmit alarm SDI to on
     */
    virtual void setTxAlarmSdi();

    /*! @brief  Set the transmit alarm SDI to off
     */
    virtual void clearTxAlarmSdi();

    /*! @brief  Determine if the transmit SAP defect is active
     *
     *  Tests whether the transmit SAP is active.
     *
     *  @return true if active
     */
    virtual bool isTransmitSapDefectActive();

    /*! @brief  Enable the slave transmit
     *
     *  Enables the transmit on the slave, turns the optical laser on.
     */
    virtual void slaveTransmitEnable();

    /*! @brief  Disable the slave transmit
     *
     *  Disables the transmit on the slave, turns the optical laser off.
     */
    virtual void slaveTransmitDisable();

    /*! @brief  Determine if the slave transmit is enabled
     *
     *  Tests whether the slave transmit is enabled.
     *
     *  @return true if enabled, false otherwise
     */
    virtual bool isSlaveTransmitEnabled();

    /*! @brief  Get the R21 coarse timer
     *
     *  Method used to read the R21 coarse timer value.\n
     *
     *  This is the T14 delay for the master port, and the Toffset delay for the slave port.
     *
     *  @return R21 coarse time value.
     */
    virtual UINT32 getR21CoarseTimer();

    /*! @brief  Get the R21 FIFO transit time
     *
     *  Method used to return the FIFO transit time value for the R21 coarse time.
     *
     *  @return the 14 bit FIFO transit timer value.
     */
    virtual UINT16 getR21FIFOTransitTime();

    /*! @brief  Get the PMRE value
     *
     *  Method used on slave cores to retrieve the PMRE value, which indicates the
     *  maximum number of master ports available within the network. For master cores
     *  0 is returned.
     *
     *  @return PMRE maximum masters in network.
     */
    virtual UINT16 getTopologyPMRE();

    /*! @brief  Get the Link ID
     *
     *  Method used on slave cores to return a number that identifies which link of
     *  Radio Equipment Controller the CPRI link is connected to. This is a value between
     *  1 and the maximum supported by the REC. For master cores 0 is returned.
     *
     *  @return the REC link ID.
     */
    virtual UINT16 getTopologyLinkId();

    /*! @brief  Get the RE ID
     *
     *  Method used on slave cores to return the remote equipment ID, used to identify
     *  the position of the core in the network chain emanating from the
     *  Radio Equipment Controller. For master cores it is used to read back the REID
     *  that has been set.
     *
     *  @return the remote equipment ID
     */
    virtual UINT16 getTopologyREID();

    /*! @brief  Set the RE ID
     *
     *  Method used on master CPRI cores to set the outgoing remote equipment ID to be
     *  on the next link in the CPRI chain. This method has no effect on slave cores.
     *
     *  @param  reid    to be sent to the next link in CPRI chain.
     */
    virtual void setTopologyREID(UINT16 reid);

    /*! @brief  Get the MGT PLL locked status
     *
     *  Method used to return the MGT_PLL_Lock flag status, to indicate if the MGT PLL is locked.
     *
     *  @return true if PLL locked, false otherwise
     */
    bool getMgtPllLock();

    /*! @brief  Get the MGT Tx Clock generation locked status
     *
     *  Method used to return the MGT Tx Clock flag status, to indicate if the MGT Tx Clock is locked.
     *
     *  @return true if PLL locked, false otherwise
     */
    bool getMgtTxClockLock();

    /*! @brief  Get the MGT Rx Clock generation locked status
     *
     *  Method used to return the MGT Rx Clock flag status, to indicate if the MGT Rx Clock is locked.
     *
     *  @return true if PLL locked, false otherwise
     */
    bool getMgtRxClockLock();

    /*! @brief  Set up the CPRI port
     *
     *  Sets up a CPRI port.
     *
     *  @param  portControl reference to the port control parameters
     */
    virtual void setPortParameters(CpriPortControl &portControl);

    /*! @brief  Get the CPRI port status
     *
     *  Method to get CPRI port status
     *
     *  @return cpri port status structure
     */
    virtual ICpriCore::CpriPortStatus getPortStatus();

    /*! @brief  Get the CPRI Core revision number
     *
     * Retrieves the CPRI Core revision number,
     * bits 0-7:  Minor
     * bits 8-15: Major
     *
     *  @return CPRI Core revision
     */
    virtual UINT16 getRevision();

    /*! @brief  Method to change the mode for the port, to master or slave
     *
     *  Method used to change the mode for the port, master or slave
     *
     * \param cpriPortType CPRI port type, Slave or Master
     *
     * \return true if successful, false otherwise
     */
    virtual bool changeMode(ICpri::CpriPortType cpriPortType);

    /*! \brief Get the number of times the Topology REID value is zero
     *
     * Method to get the number of times the Topology REID value is zero.
     *
     * \return the number of times the Topology REID value is zero
     */
    virtual int getCpriReIdIsZeroCount();

    /*! \brief Resets the number of times the Topology REID value is zero
     *
     * Method to reset the number of times the Topology REID value is zero.
     */
    virtual void resetCpriReIdIsZeroCount();

    const char* getStatusCodeString(StatusCode statusCode);
    char* getLineRateCapabilityString(ICpriCore::LineRateCapability rateCap);
    const char* getCurrentEthernetRateString(CMRateValue ethRate);
    const char* getTxFormatString(TxFormat txFormat);

    /**
     * Sets the number of unused samples in between valid ones, set to 0 for consecutive samples
     */
    virtual void setWaitSamples(unsigned waitSamples) override ;

    /**
     * Get the current setting of wait samples
     */
    virtual unsigned getWaitSamples() const override ;



    /**
     * Method used for debug only and accessed by test interface.
     * @param os
     */
    virtual void showPort( std::ostream& os = std::cout );

 private:

    /*! @brief  Method to set the mode for the port, master or slave
     *
     *  Method used to set the mode for the port, master or slave, according to the core Id
     */
    void setMode();

    /*! @brief  Method to set the default core initialisation
     *
     *  Method used to set the core registers to their initial default settings
     */
    void defaultCoreInitialisation();

    /*! @brief  Method used to get the minimum CMRateValue for the current line rate.
     *
     *  Method used to get the minimum CMRateValue for the current line rate.
     *
     *  @return the minimum CMRateValue for the current line rate.
     */
    ICpriCore::CMRateValue_t getCurrentMinEthernetRate();

    /*! @brief  Method used to get the maximum CMRateValue for the current line rate.
     *
     *  Method used to get the maximum CMRateValue for the current line rate.
     *
     *  @return the maximum CMRateValue for the current line rate.
     */
    ICpriCore::CMRateValue_t getCurrentMaxEthernetRate();

    /*! @brief  Method used to convert the Ethernet pointer value to a CMRateValue.
     *
     *  Method used to convert the Ethernet pointer value to a CMRateValue.
     *
     *  @return the current CMRateValue.
     */
    UINT32 getCurrentEthernetBitRate(UINT32 currentEthernetPointer);

    void showPortStatus(std::ostream& os = std::cout);

private:
    /**
     * Uses the CommonFpga to set the FPGA regs
     */
    std::shared_ptr<IFpgaCpri> mFpga;
    std::shared_ptr<IFpgaFibreRegs> mFibreFpga;

    /**
     * SFP module access
     */
    std::shared_ptr<ISfpData> mSfpData ;

    UINT16 mCoreId;

    UINT32 mFibre;

    unsigned mWaitSamples ;

    /**
     * Count the number of times the Topology REID value is zero
     */
    int mCpriReIdIsZeroCount;

};  // end of class CommonCpriCore


} /* namespace Mplane */


#endif /* _hardware_COMMONCPRICORE_H_ */
