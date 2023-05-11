#ifndef _ISYSTEM_REGS_DEF_H_
#define _ISYSTEM_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaSystemRegs.h
 * \brief     FPGA System registers virtual interface
 *
 *
 * \details   This file defines the FPGA System registers.
 *
 *             ** Auto-generated file, do not edit **
 *
 *
 */
#include <memory>

#include <memory>
#include "GlobalTypeDefs.h"
#include "IFpgaKernel.h"
#include "IFpgaRegs.h"


namespace Mplane
{

class IFpgaSystemRegs : public virtual IFpgaRegs
{
public:
	IFpgaSystemRegs() {}
	virtual ~IFpgaSystemRegs(void) {} ;

    /** \brief  Does FPGA have a SYSTEM registers block
     *
     *  \return true if the FPGA instance does actually support a System registers block
     */
    virtual bool hasSystemRegisters(void) =0 ;

    /*! \brief  Get base address
     *
     *  Get the base address of the System registers (if supported)
     *
     *  \return base address of System registers; 0 if not supported
     */
    virtual UINT32 getSystemBlockAddr(void) =0 ;

    /*! \brief  Lock mutex
     *
     *  Lock the mutex protecting this region of fpga registers
     *
     */
    virtual void mutexLock(void) =0 ;

    /*! \brief  Unlock mutex
     *
     *  Unlock the mutex protecting this region of fpga registers
     *
     */
    virtual void mutexUnLock(void) =0 ;

    /*! \brief  Get fpga kernel
     *
     *  Get the fpga kernel driver
     *
     *  \return pointer to fpga kernel
     */
    virtual std::shared_ptr<IFpgaKernel> kernel() const =0 ;

    // == Accessors ==

    /**
     * Read field SYSTEM_CLOCK_RESET at 0x0 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_systemClockReset() const =0 ;

    /**
     * Write field SYSTEM_CLOCK_RESET at 0x0 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_systemClockReset(FpgaVal value) =0 ;

    /**
     * Read field SYSTEM_CLOCK_RESET at 0x0 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_systemClockReset() const =0 ;

    /**
     * Write field SYSTEM_CLOCK_RESET at 0x0 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_systemClockReset(FpgaVal value) =0 ;

    /**
     * Write field SYSTEM_CLOCK_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_systemClockReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BASEBAND_INTERFACE_RESET at 0x0 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_basebandInterfaceReset() const =0 ;

    /**
     * Write field BASEBAND_INTERFACE_RESET at 0x0 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_basebandInterfaceReset(FpgaVal value) =0 ;

    /**
     * Read field BASEBAND_INTERFACE_RESET at 0x0 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_basebandInterfaceReset() const =0 ;

    /**
     * Write field BASEBAND_INTERFACE_RESET at 0x0 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_basebandInterfaceReset(FpgaVal value) =0 ;

    /**
     * Write field BASEBAND_INTERFACE_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_basebandInterfaceReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RF_CHAIN_RESET at 0x0 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_rfChainReset() const =0 ;

    /**
     * Write field RF_CHAIN_RESET at 0x0 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rfChainReset(FpgaVal value) =0 ;

    /**
     * Read field RF_CHAIN_RESET at 0x0 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rfChainReset() const =0 ;

    /**
     * Write field RF_CHAIN_RESET at 0x0 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rfChainReset(FpgaVal value) =0 ;

    /**
     * Write field RF_CHAIN_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rfChainReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_ADC_INTFC_RESET at 0x0 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_rxAdcIntfcReset() const =0 ;

    /**
     * Write field RX_ADC_INTFC_RESET at 0x0 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxAdcIntfcReset(FpgaVal value) =0 ;

    /**
     * Read field RX_ADC_INTFC_RESET at 0x0 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxAdcIntfcReset() const =0 ;

    /**
     * Write field RX_ADC_INTFC_RESET at 0x0 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxAdcIntfcReset(FpgaVal value) =0 ;

    /**
     * Write field RX_ADC_INTFC_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxAdcIntfcReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FPGA_SOFT_RESET at 0x0 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_fpgaSoftReset() const =0 ;

    /**
     * Write field FPGA_SOFT_RESET at 0x0 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fpgaSoftReset(FpgaVal value) =0 ;

    /**
     * Read field FPGA_SOFT_RESET at 0x0 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaSoftReset() const =0 ;

    /**
     * Write field FPGA_SOFT_RESET at 0x0 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fpgaSoftReset(FpgaVal value) =0 ;

    /**
     * Write field FPGA_SOFT_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fpgaSoftReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field GTX_RESET at 0x0 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_gtxReset() const =0 ;

    /**
     * Write field GTX_RESET at 0x0 bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_gtxReset(FpgaVal value) =0 ;

    /**
     * Read field GTX_RESET at 0x0 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_gtxReset() const =0 ;

    /**
     * Write field GTX_RESET at 0x0 bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_gtxReset(FpgaVal value) =0 ;

    /**
     * Write field GTX_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_gtxReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FRAMER_RESET at 0x0 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_framerReset() const =0 ;

    /**
     * Write field FRAMER_RESET at 0x0 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_framerReset(FpgaVal value) =0 ;

    /**
     * Read field FRAMER_RESET at 0x0 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_framerReset() const =0 ;

    /**
     * Write field FRAMER_RESET at 0x0 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_framerReset(FpgaVal value) =0 ;

    /**
     * Write field FRAMER_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_framerReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MULTI_MAC_RESET at 0x0 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_multiMacReset() const =0 ;

    /**
     * Write field MULTI_MAC_RESET at 0x0 bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_multiMacReset(FpgaVal value) =0 ;

    /**
     * Read field MULTI_MAC_RESET at 0x0 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_multiMacReset() const =0 ;

    /**
     * Write field MULTI_MAC_RESET at 0x0 bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_multiMacReset(FpgaVal value) =0 ;

    /**
     * Write field MULTI_MAC_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_multiMacReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DCM_LOCK_ALARM_RESET at 0x0 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_dcmLockAlarmReset() const =0 ;

    /**
     * Write field DCM_LOCK_ALARM_RESET at 0x0 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dcmLockAlarmReset(FpgaVal value) =0 ;

    /**
     * Read field DCM_LOCK_ALARM_RESET at 0x0 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dcmLockAlarmReset() const =0 ;

    /**
     * Write field DCM_LOCK_ALARM_RESET at 0x0 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dcmLockAlarmReset(FpgaVal value) =0 ;

    /**
     * Write field DCM_LOCK_ALARM_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dcmLockAlarmReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_UNLATCHED_SYNTH_STATUS at 0x2 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedSynthStatus() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_SYNTH_STATUS at 0x2 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmUnlatchedSynthStatus(FpgaVal value) =0 ;

    /**
     * Read field ALARM_UNLATCHED_SYNTH_STATUS at 0x2 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedSynthStatus() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_SYNTH_STATUS at 0x2 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmUnlatchedSynthStatus(FpgaVal value) =0 ;

    /**
     * Write field ALARM_UNLATCHED_SYNTH_STATUS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmUnlatchedSynthStatus(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_UNLATCHED_DYN_ADC_ALM at 0x2 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedDynAdcAlm() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_DYN_ADC_ALM at 0x2 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmUnlatchedDynAdcAlm(FpgaVal value) =0 ;

    /**
     * Read field ALARM_UNLATCHED_DYN_ADC_ALM at 0x2 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedDynAdcAlm() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_DYN_ADC_ALM at 0x2 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmUnlatchedDynAdcAlm(FpgaVal value) =0 ;

    /**
     * Write field ALARM_UNLATCHED_DYN_ADC_ALM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmUnlatchedDynAdcAlm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_UNLATCHED_FPGA_TEMP_ALM at 0x2 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedFpgaTempAlm() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_FPGA_TEMP_ALM at 0x2 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmUnlatchedFpgaTempAlm(FpgaVal value) =0 ;

    /**
     * Read field ALARM_UNLATCHED_FPGA_TEMP_ALM at 0x2 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedFpgaTempAlm() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_FPGA_TEMP_ALM at 0x2 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmUnlatchedFpgaTempAlm(FpgaVal value) =0 ;

    /**
     * Write field ALARM_UNLATCHED_FPGA_TEMP_ALM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmUnlatchedFpgaTempAlm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_UNLATCHED_FPGA_TEMP_ALERT at 0x2 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedFpgaTempAlert() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_FPGA_TEMP_ALERT at 0x2 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmUnlatchedFpgaTempAlert(FpgaVal value) =0 ;

    /**
     * Read field ALARM_UNLATCHED_FPGA_TEMP_ALERT at 0x2 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedFpgaTempAlert() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_FPGA_TEMP_ALERT at 0x2 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmUnlatchedFpgaTempAlert(FpgaVal value) =0 ;

    /**
     * Write field ALARM_UNLATCHED_FPGA_TEMP_ALERT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmUnlatchedFpgaTempAlert(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_UNLATCHED_PSU_ALM at 0x2 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedPsuAlm() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_PSU_ALM at 0x2 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmUnlatchedPsuAlm(FpgaVal value) =0 ;

    /**
     * Read field ALARM_UNLATCHED_PSU_ALM at 0x2 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedPsuAlm() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_PSU_ALM at 0x2 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmUnlatchedPsuAlm(FpgaVal value) =0 ;

    /**
     * Write field ALARM_UNLATCHED_PSU_ALM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmUnlatchedPsuAlm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_UNLATCHED_AURORA_CHANNEL_UP at 0x2 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedAuroraChannelUp() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_AURORA_CHANNEL_UP at 0x2 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmUnlatchedAuroraChannelUp(FpgaVal value) =0 ;

    /**
     * Read field ALARM_UNLATCHED_AURORA_CHANNEL_UP at 0x2 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedAuroraChannelUp() const =0 ;

    /**
     * Write field ALARM_UNLATCHED_AURORA_CHANNEL_UP at 0x2 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmUnlatchedAuroraChannelUp(FpgaVal value) =0 ;

    /**
     * Write field ALARM_UNLATCHED_AURORA_CHANNEL_UP in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmUnlatchedAuroraChannelUp(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_COMPLETE_ALARM at 0x2 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_spi0CompleteAlarm() const =0 ;


    /**
     * Read field SPI0_COMPLETE_ALARM at 0x2 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0CompleteAlarm() const =0 ;




    /**
     * Read field SPI1_COMPLETE_ALARM at 0x2 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_spi1CompleteAlarm() const =0 ;


    /**
     * Read field SPI1_COMPLETE_ALARM at 0x2 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1CompleteAlarm() const =0 ;




    /**
     * Read field SPI_GPIO_INTERRUPT at 0x2 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_spiGpioInterrupt() const =0 ;


    /**
     * Read field SPI_GPIO_INTERRUPT at 0x2 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spiGpioInterrupt() const =0 ;




    /**
     * Read field ALARM_STATUS_SYNTH_STATUS at 0x4 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_alarmStatusSynthStatus() const =0 ;

    /**
     * Write field ALARM_STATUS_SYNTH_STATUS at 0x4 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmStatusSynthStatus(FpgaVal value) =0 ;

    /**
     * Read field ALARM_STATUS_SYNTH_STATUS at 0x4 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmStatusSynthStatus() const =0 ;

    /**
     * Write field ALARM_STATUS_SYNTH_STATUS at 0x4 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmStatusSynthStatus(FpgaVal value) =0 ;

    /**
     * Write field ALARM_STATUS_SYNTH_STATUS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmStatusSynthStatus(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_STATUS_DYN_ADC_ALM at 0x4 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_alarmStatusDynAdcAlm() const =0 ;

    /**
     * Write field ALARM_STATUS_DYN_ADC_ALM at 0x4 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmStatusDynAdcAlm(FpgaVal value) =0 ;

    /**
     * Read field ALARM_STATUS_DYN_ADC_ALM at 0x4 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmStatusDynAdcAlm() const =0 ;

    /**
     * Write field ALARM_STATUS_DYN_ADC_ALM at 0x4 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmStatusDynAdcAlm(FpgaVal value) =0 ;

    /**
     * Write field ALARM_STATUS_DYN_ADC_ALM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmStatusDynAdcAlm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_STATUS_FPGA_TEMP_ALM at 0x4 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_alarmStatusFpgaTempAlm() const =0 ;

    /**
     * Write field ALARM_STATUS_FPGA_TEMP_ALM at 0x4 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmStatusFpgaTempAlm(FpgaVal value) =0 ;

    /**
     * Read field ALARM_STATUS_FPGA_TEMP_ALM at 0x4 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmStatusFpgaTempAlm() const =0 ;

    /**
     * Write field ALARM_STATUS_FPGA_TEMP_ALM at 0x4 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmStatusFpgaTempAlm(FpgaVal value) =0 ;

    /**
     * Write field ALARM_STATUS_FPGA_TEMP_ALM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmStatusFpgaTempAlm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_STATUS_FPGA_TEMP_ALERT at 0x4 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_alarmStatusFpgaTempAlert() const =0 ;

    /**
     * Write field ALARM_STATUS_FPGA_TEMP_ALERT at 0x4 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmStatusFpgaTempAlert(FpgaVal value) =0 ;

    /**
     * Read field ALARM_STATUS_FPGA_TEMP_ALERT at 0x4 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmStatusFpgaTempAlert() const =0 ;

    /**
     * Write field ALARM_STATUS_FPGA_TEMP_ALERT at 0x4 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmStatusFpgaTempAlert(FpgaVal value) =0 ;

    /**
     * Write field ALARM_STATUS_FPGA_TEMP_ALERT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmStatusFpgaTempAlert(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_STATUS_PSU_ALM at 0x4 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_alarmStatusPsuAlm() const =0 ;

    /**
     * Write field ALARM_STATUS_PSU_ALM at 0x4 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmStatusPsuAlm(FpgaVal value) =0 ;

    /**
     * Read field ALARM_STATUS_PSU_ALM at 0x4 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmStatusPsuAlm() const =0 ;

    /**
     * Write field ALARM_STATUS_PSU_ALM at 0x4 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmStatusPsuAlm(FpgaVal value) =0 ;

    /**
     * Write field ALARM_STATUS_PSU_ALM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmStatusPsuAlm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_STATUS_AURORA_CHANNEL_UP at 0x4 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_alarmStatusAuroraChannelUp() const =0 ;

    /**
     * Write field ALARM_STATUS_AURORA_CHANNEL_UP at 0x4 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmStatusAuroraChannelUp(FpgaVal value) =0 ;

    /**
     * Read field ALARM_STATUS_AURORA_CHANNEL_UP at 0x4 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmStatusAuroraChannelUp() const =0 ;

    /**
     * Write field ALARM_STATUS_AURORA_CHANNEL_UP at 0x4 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmStatusAuroraChannelUp(FpgaVal value) =0 ;

    /**
     * Write field ALARM_STATUS_AURORA_CHANNEL_UP in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmStatusAuroraChannelUp(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_STATUS_PSU_FAIL at 0x4 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_alarmStatusPsuFail() const =0 ;

    /**
     * Write field ALARM_STATUS_PSU_FAIL at 0x4 bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_alarmStatusPsuFail(FpgaVal value) =0 ;

    /**
     * Read field ALARM_STATUS_PSU_FAIL at 0x4 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmStatusPsuFail() const =0 ;

    /**
     * Write field ALARM_STATUS_PSU_FAIL at 0x4 bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_alarmStatusPsuFail(FpgaVal value) =0 ;

    /**
     * Write field ALARM_STATUS_PSU_FAIL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_alarmStatusPsuFail(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LATCHED_SPI_GPIO_INTERRUPT at 0x4 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_latchedSpiGpioInterrupt() const =0 ;

    /**
     * Write field LATCHED_SPI_GPIO_INTERRUPT at 0x4 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_latchedSpiGpioInterrupt(FpgaVal value) =0 ;

    /**
     * Read field LATCHED_SPI_GPIO_INTERRUPT at 0x4 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_latchedSpiGpioInterrupt() const =0 ;

    /**
     * Write field LATCHED_SPI_GPIO_INTERRUPT at 0x4 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_latchedSpiGpioInterrupt(FpgaVal value) =0 ;

    /**
     * Write field LATCHED_SPI_GPIO_INTERRUPT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_latchedSpiGpioInterrupt(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYS_RX_ENABLE at 0x6 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_sysRxEnable() const =0 ;

    /**
     * Write field SYS_RX_ENABLE at 0x6 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sysRxEnable(FpgaVal value) =0 ;

    /**
     * Read field SYS_RX_ENABLE at 0x6 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sysRxEnable() const =0 ;

    /**
     * Write field SYS_RX_ENABLE at 0x6 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sysRxEnable(FpgaVal value) =0 ;

    /**
     * Write field SYS_RX_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sysRxEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYS_TX1_ENABLE at 0x6 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_sysTx1Enable() const =0 ;

    /**
     * Write field SYS_TX1_ENABLE at 0x6 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sysTx1Enable(FpgaVal value) =0 ;

    /**
     * Read field SYS_TX1_ENABLE at 0x6 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sysTx1Enable() const =0 ;

    /**
     * Write field SYS_TX1_ENABLE at 0x6 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sysTx1Enable(FpgaVal value) =0 ;

    /**
     * Write field SYS_TX1_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sysTx1Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYS_TX2_ENABLE at 0x6 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_sysTx2Enable() const =0 ;

    /**
     * Write field SYS_TX2_ENABLE at 0x6 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sysTx2Enable(FpgaVal value) =0 ;

    /**
     * Read field SYS_TX2_ENABLE at 0x6 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sysTx2Enable() const =0 ;

    /**
     * Write field SYS_TX2_ENABLE at 0x6 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sysTx2Enable(FpgaVal value) =0 ;

    /**
     * Write field SYS_TX2_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sysTx2Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_PLL_ENABLE_LO at 0x6 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_rxPllEnableLo() const =0 ;

    /**
     * Write field RX_PLL_ENABLE_LO at 0x6 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxPllEnableLo(FpgaVal value) =0 ;

    /**
     * Read field RX_PLL_ENABLE_LO at 0x6 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxPllEnableLo() const =0 ;

    /**
     * Write field RX_PLL_ENABLE_LO at 0x6 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxPllEnableLo(FpgaVal value) =0 ;

    /**
     * Write field RX_PLL_ENABLE_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxPllEnableLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_PLL_ENABLE_HI at 0x6 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_rxPllEnableHi() const =0 ;

    /**
     * Write field RX_PLL_ENABLE_HI at 0x6 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxPllEnableHi(FpgaVal value) =0 ;

    /**
     * Read field RX_PLL_ENABLE_HI at 0x6 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxPllEnableHi() const =0 ;

    /**
     * Write field RX_PLL_ENABLE_HI at 0x6 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxPllEnableHi(FpgaVal value) =0 ;

    /**
     * Write field RX_PLL_ENABLE_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxPllEnableHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RF_PLL_ENABLE_LO at 0x6 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_rfPllEnableLo() const =0 ;

    /**
     * Write field RF_PLL_ENABLE_LO at 0x6 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rfPllEnableLo(FpgaVal value) =0 ;

    /**
     * Read field RF_PLL_ENABLE_LO at 0x6 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rfPllEnableLo() const =0 ;

    /**
     * Write field RF_PLL_ENABLE_LO at 0x6 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rfPllEnableLo(FpgaVal value) =0 ;

    /**
     * Write field RF_PLL_ENABLE_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rfPllEnableLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RF_PLL_ENABLE_HI at 0x6 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_rfPllEnableHi() const =0 ;

    /**
     * Write field RF_PLL_ENABLE_HI at 0x6 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rfPllEnableHi(FpgaVal value) =0 ;

    /**
     * Read field RF_PLL_ENABLE_HI at 0x6 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rfPllEnableHi() const =0 ;

    /**
     * Write field RF_PLL_ENABLE_HI at 0x6 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rfPllEnableHi(FpgaVal value) =0 ;

    /**
     * Write field RF_PLL_ENABLE_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rfPllEnableHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPD_PLL_ENABLE at 0x6 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_dpdPllEnable() const =0 ;

    /**
     * Write field DPD_PLL_ENABLE at 0x6 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdPllEnable(FpgaVal value) =0 ;

    /**
     * Read field DPD_PLL_ENABLE at 0x6 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdPllEnable() const =0 ;

    /**
     * Write field DPD_PLL_ENABLE at 0x6 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdPllEnable(FpgaVal value) =0 ;

    /**
     * Write field DPD_PLL_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdPllEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BF_ENABLE at 0x6 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_bfEnable() const =0 ;

    /**
     * Write field BF_ENABLE at 0x6 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bfEnable(FpgaVal value) =0 ;

    /**
     * Read field BF_ENABLE at 0x6 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bfEnable() const =0 ;

    /**
     * Write field BF_ENABLE at 0x6 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bfEnable(FpgaVal value) =0 ;

    /**
     * Write field BF_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bfEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_HW_RESET at 0xa bits [0]
     * \return field value
     */
    virtual const FpgaVal read_dacHwReset() const =0 ;

    /**
     * Write field DAC_HW_RESET at 0xa bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacHwReset(FpgaVal value) =0 ;

    /**
     * Read field DAC_HW_RESET at 0xa bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacHwReset() const =0 ;

    /**
     * Write field DAC_HW_RESET at 0xa bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacHwReset(FpgaVal value) =0 ;

    /**
     * Write field DAC_HW_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacHwReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_GPIO_RESET at 0xa bits [1]
     * \return field value
     */
    virtual const FpgaVal read_spiGpioReset() const =0 ;

    /**
     * Write field SPI_GPIO_RESET at 0xa bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spiGpioReset(FpgaVal value) =0 ;

    /**
     * Read field SPI_GPIO_RESET at 0xa bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spiGpioReset() const =0 ;

    /**
     * Write field SPI_GPIO_RESET at 0xa bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spiGpioReset(FpgaVal value) =0 ;

    /**
     * Write field SPI_GPIO_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spiGpioReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPD_ADC_HW_RESET at 0xa bits [5]
     * \return field value
     */
    virtual const FpgaVal read_dpdAdcHwReset() const =0 ;

    /**
     * Write field DPD_ADC_HW_RESET at 0xa bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdAdcHwReset(FpgaVal value) =0 ;

    /**
     * Read field DPD_ADC_HW_RESET at 0xa bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdAdcHwReset() const =0 ;

    /**
     * Write field DPD_ADC_HW_RESET at 0xa bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdAdcHwReset(FpgaVal value) =0 ;

    /**
     * Write field DPD_ADC_HW_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdAdcHwReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYSTEM_CLOCK_HW_RESET at 0xa bits [10]
     * \return field value
     */
    virtual const FpgaVal read_systemClockHwReset() const =0 ;

    /**
     * Write field SYSTEM_CLOCK_HW_RESET at 0xa bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_systemClockHwReset(FpgaVal value) =0 ;

    /**
     * Read field SYSTEM_CLOCK_HW_RESET at 0xa bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_systemClockHwReset() const =0 ;

    /**
     * Write field SYSTEM_CLOCK_HW_RESET at 0xa bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_systemClockHwReset(FpgaVal value) =0 ;

    /**
     * Write field SYSTEM_CLOCK_HW_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_systemClockHwReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BASEBAND_CLOCK_HW_RESET at 0xa bits [11]
     * \return field value
     */
    virtual const FpgaVal read_basebandClockHwReset() const =0 ;

    /**
     * Write field BASEBAND_CLOCK_HW_RESET at 0xa bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_basebandClockHwReset(FpgaVal value) =0 ;

    /**
     * Read field BASEBAND_CLOCK_HW_RESET at 0xa bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_basebandClockHwReset() const =0 ;

    /**
     * Write field BASEBAND_CLOCK_HW_RESET at 0xa bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_basebandClockHwReset(FpgaVal value) =0 ;

    /**
     * Write field BASEBAND_CLOCK_HW_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_basebandClockHwReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ETHERNET_PHY_HW_RESET at 0xa bits [12]
     * \return field value
     */
    virtual const FpgaVal read_ethernetPhyHwReset() const =0 ;

    /**
     * Write field ETHERNET_PHY_HW_RESET at 0xa bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ethernetPhyHwReset(FpgaVal value) =0 ;

    /**
     * Read field ETHERNET_PHY_HW_RESET at 0xa bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ethernetPhyHwReset() const =0 ;

    /**
     * Write field ETHERNET_PHY_HW_RESET at 0xa bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ethernetPhyHwReset(FpgaVal value) =0 ;

    /**
     * Write field ETHERNET_PHY_HW_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ethernetPhyHwReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_CLOCK_HW_RESET at 0xa bits [13]
     * \return field value
     */
    virtual const FpgaVal read_dacClockHwReset() const =0 ;

    /**
     * Write field DAC_CLOCK_HW_RESET at 0xa bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacClockHwReset(FpgaVal value) =0 ;

    /**
     * Read field DAC_CLOCK_HW_RESET at 0xa bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacClockHwReset() const =0 ;

    /**
     * Write field DAC_CLOCK_HW_RESET at 0xa bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacClockHwReset(FpgaVal value) =0 ;

    /**
     * Write field DAC_CLOCK_HW_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacClockHwReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field USBPHY_HW_RESET at 0xa bits [14]
     * \return field value
     */
    virtual const FpgaVal read_usbphyHwReset() const =0 ;

    /**
     * Write field USBPHY_HW_RESET at 0xa bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_usbphyHwReset(FpgaVal value) =0 ;

    /**
     * Read field USBPHY_HW_RESET at 0xa bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_usbphyHwReset() const =0 ;

    /**
     * Write field USBPHY_HW_RESET at 0xa bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_usbphyHwReset(FpgaVal value) =0 ;

    /**
     * Write field USBPHY_HW_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_usbphyHwReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LED1 at 0xc bits [0]
     * \return field value
     */
    virtual const FpgaVal read_led1() const =0 ;

    /**
     * Write field LED1 at 0xc bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_led1(FpgaVal value) =0 ;

    /**
     * Read field LED1 at 0xc bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_led1() const =0 ;

    /**
     * Write field LED1 at 0xc bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_led1(FpgaVal value) =0 ;

    /**
     * Write field LED1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_led1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LED2 at 0xc bits [1]
     * \return field value
     */
    virtual const FpgaVal read_led2() const =0 ;

    /**
     * Write field LED2 at 0xc bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_led2(FpgaVal value) =0 ;

    /**
     * Read field LED2 at 0xc bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_led2() const =0 ;

    /**
     * Write field LED2 at 0xc bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_led2(FpgaVal value) =0 ;

    /**
     * Write field LED2 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_led2(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CLI_TR_SW_CTRL at 0xc bits [2]
     * \return field value
     */
    virtual const FpgaVal read_cliTrSwCtrl() const =0 ;

    /**
     * Write field CLI_TR_SW_CTRL at 0xc bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cliTrSwCtrl(FpgaVal value) =0 ;

    /**
     * Read field CLI_TR_SW_CTRL at 0xc bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cliTrSwCtrl() const =0 ;

    /**
     * Write field CLI_TR_SW_CTRL at 0xc bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cliTrSwCtrl(FpgaVal value) =0 ;

    /**
     * Write field CLI_TR_SW_CTRL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cliTrSwCtrl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX2_PLL_LOCKED at 0xc bits [6]
     * \return field value
     */
    virtual const FpgaVal read_tx2PllLocked() const =0 ;

    /**
     * Write field TX2_PLL_LOCKED at 0xc bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tx2PllLocked(FpgaVal value) =0 ;

    /**
     * Read field TX2_PLL_LOCKED at 0xc bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tx2PllLocked() const =0 ;

    /**
     * Write field TX2_PLL_LOCKED at 0xc bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tx2PllLocked(FpgaVal value) =0 ;

    /**
     * Write field TX2_PLL_LOCKED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tx2PllLocked(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX2_PLL_LOCKED at 0xc bits [7]
     * \return field value
     */
    virtual const FpgaVal read_rx2PllLocked() const =0 ;

    /**
     * Write field RX2_PLL_LOCKED at 0xc bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rx2PllLocked(FpgaVal value) =0 ;

    /**
     * Read field RX2_PLL_LOCKED at 0xc bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rx2PllLocked() const =0 ;

    /**
     * Write field RX2_PLL_LOCKED at 0xc bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rx2PllLocked(FpgaVal value) =0 ;

    /**
     * Write field RX2_PLL_LOCKED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rx2PllLocked(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TR_SW_CTRL at 0xc bits [9..8]
     * \return field value
     */
    virtual const FpgaVal read_trSwCtrl() const =0 ;

    /**
     * Write field TR_SW_CTRL at 0xc bits [9..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_trSwCtrl(FpgaVal value) =0 ;

    /**
     * Read field TR_SW_CTRL at 0xc bits [9..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_trSwCtrl() const =0 ;

    /**
     * Write field TR_SW_CTRL at 0xc bits [9..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_trSwCtrl(FpgaVal value) =0 ;

    /**
     * Write field TR_SW_CTRL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_trSwCtrl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SFP0_PLL_LOCKED at 0xc bits [10]
     * \return field value
     */
    virtual const FpgaVal read_sfp0PllLocked() const =0 ;

    /**
     * Write field SFP0_PLL_LOCKED at 0xc bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sfp0PllLocked(FpgaVal value) =0 ;

    /**
     * Read field SFP0_PLL_LOCKED at 0xc bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfp0PllLocked() const =0 ;

    /**
     * Write field SFP0_PLL_LOCKED at 0xc bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sfp0PllLocked(FpgaVal value) =0 ;

    /**
     * Write field SFP0_PLL_LOCKED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sfp0PllLocked(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SFP1_PLL_LOCKED at 0xc bits [11]
     * \return field value
     */
    virtual const FpgaVal read_sfp1PllLocked() const =0 ;

    /**
     * Write field SFP1_PLL_LOCKED at 0xc bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sfp1PllLocked(FpgaVal value) =0 ;

    /**
     * Read field SFP1_PLL_LOCKED at 0xc bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfp1PllLocked() const =0 ;

    /**
     * Write field SFP1_PLL_LOCKED at 0xc bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sfp1PllLocked(FpgaVal value) =0 ;

    /**
     * Write field SFP1_PLL_LOCKED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sfp1PllLocked(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_PLL_LOCKED at 0xc bits [13]
     * \return field value
     */
    virtual const FpgaVal read_txPllLocked() const =0 ;

    /**
     * Write field TX_PLL_LOCKED at 0xc bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txPllLocked(FpgaVal value) =0 ;

    /**
     * Read field TX_PLL_LOCKED at 0xc bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txPllLocked() const =0 ;

    /**
     * Write field TX_PLL_LOCKED at 0xc bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txPllLocked(FpgaVal value) =0 ;

    /**
     * Write field TX_PLL_LOCKED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txPllLocked(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_PLL_LOCKED at 0xc bits [14]
     * \return field value
     */
    virtual const FpgaVal read_rxPllLocked() const =0 ;

    /**
     * Write field RX_PLL_LOCKED at 0xc bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxPllLocked(FpgaVal value) =0 ;

    /**
     * Read field RX_PLL_LOCKED at 0xc bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxPllLocked() const =0 ;

    /**
     * Write field RX_PLL_LOCKED at 0xc bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxPllLocked(FpgaVal value) =0 ;

    /**
     * Write field RX_PLL_LOCKED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxPllLocked(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPD_PLL_LOCKED at 0xc bits [15]
     * \return field value
     */
    virtual const FpgaVal read_dpdPllLocked() const =0 ;

    /**
     * Write field DPD_PLL_LOCKED at 0xc bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdPllLocked(FpgaVal value) =0 ;

    /**
     * Read field DPD_PLL_LOCKED at 0xc bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdPllLocked() const =0 ;

    /**
     * Write field DPD_PLL_LOCKED at 0xc bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdPllLocked(FpgaVal value) =0 ;

    /**
     * Write field DPD_PLL_LOCKED in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdPllLocked(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field POWER_DETECTOR_SAMPLE at 0x10 bits [11..0]
     * \return field value
     */
    virtual const FpgaVal read_powerDetectorSample() const =0 ;


    /**
     * Read field POWER_DETECTOR_SAMPLE at 0x10 bits [11..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_powerDetectorSample() const =0 ;




    /**
     * Read field POWER_DETECTOR_VALID at 0x10 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_powerDetectorValid() const =0 ;


    /**
     * Read field POWER_DETECTOR_VALID at 0x10 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_powerDetectorValid() const =0 ;




    /**
     * Read field CLR_POWER_DETECTOR_VALID at 0x10 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_clrPowerDetectorValid() const =0 ;

    /**
     * Write field CLR_POWER_DETECTOR_VALID at 0x10 bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_clrPowerDetectorValid(FpgaVal value) =0 ;

    /**
     * Read field CLR_POWER_DETECTOR_VALID at 0x10 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_clrPowerDetectorValid() const =0 ;

    /**
     * Write field CLR_POWER_DETECTOR_VALID at 0x10 bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_clrPowerDetectorValid(FpgaVal value) =0 ;

    /**
     * Write field CLR_POWER_DETECTOR_VALID in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_clrPowerDetectorValid(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field POWER_DETECTOR_MANUAL_TRIG at 0x10 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_powerDetectorManualTrig() const =0 ;

    /**
     * Write field POWER_DETECTOR_MANUAL_TRIG at 0x10 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_powerDetectorManualTrig(FpgaVal value) =0 ;

    /**
     * Read field POWER_DETECTOR_MANUAL_TRIG at 0x10 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_powerDetectorManualTrig() const =0 ;

    /**
     * Write field POWER_DETECTOR_MANUAL_TRIG at 0x10 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_powerDetectorManualTrig(FpgaVal value) =0 ;

    /**
     * Write field POWER_DETECTOR_MANUAL_TRIG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_powerDetectorManualTrig(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PPC_PA_TRIP_CTRL at 0x12 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_ppcPaTripCtrl() const =0 ;

    /**
     * Write field PPC_PA_TRIP_CTRL at 0x12 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ppcPaTripCtrl(FpgaVal value) =0 ;

    /**
     * Read field PPC_PA_TRIP_CTRL at 0x12 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ppcPaTripCtrl() const =0 ;

    /**
     * Write field PPC_PA_TRIP_CTRL at 0x12 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ppcPaTripCtrl(FpgaVal value) =0 ;

    /**
     * Write field PPC_PA_TRIP_CTRL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ppcPaTripCtrl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX2_PLL_LOCK_ALARM at 0x24 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_tx2PllLockAlarm() const =0 ;

    /**
     * Write field TX2_PLL_LOCK_ALARM at 0x24 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tx2PllLockAlarm(FpgaVal value) =0 ;

    /**
     * Read field TX2_PLL_LOCK_ALARM at 0x24 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tx2PllLockAlarm() const =0 ;

    /**
     * Write field TX2_PLL_LOCK_ALARM at 0x24 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tx2PllLockAlarm(FpgaVal value) =0 ;

    /**
     * Write field TX2_PLL_LOCK_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tx2PllLockAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX2_PLL_LOCK_ALARM at 0x24 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_rx2PllLockAlarm() const =0 ;

    /**
     * Write field RX2_PLL_LOCK_ALARM at 0x24 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rx2PllLockAlarm(FpgaVal value) =0 ;

    /**
     * Read field RX2_PLL_LOCK_ALARM at 0x24 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rx2PllLockAlarm() const =0 ;

    /**
     * Write field RX2_PLL_LOCK_ALARM at 0x24 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rx2PllLockAlarm(FpgaVal value) =0 ;

    /**
     * Write field RX2_PLL_LOCK_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rx2PllLockAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SFP0_PLL_LOCK_ALARM at 0x24 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_sfp0PllLockAlarm() const =0 ;

    /**
     * Write field SFP0_PLL_LOCK_ALARM at 0x24 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sfp0PllLockAlarm(FpgaVal value) =0 ;

    /**
     * Read field SFP0_PLL_LOCK_ALARM at 0x24 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfp0PllLockAlarm() const =0 ;

    /**
     * Write field SFP0_PLL_LOCK_ALARM at 0x24 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sfp0PllLockAlarm(FpgaVal value) =0 ;

    /**
     * Write field SFP0_PLL_LOCK_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sfp0PllLockAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SFP1_PLL_LOCK_ALARM at 0x24 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_sfp1PllLockAlarm() const =0 ;

    /**
     * Write field SFP1_PLL_LOCK_ALARM at 0x24 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_sfp1PllLockAlarm(FpgaVal value) =0 ;

    /**
     * Read field SFP1_PLL_LOCK_ALARM at 0x24 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_sfp1PllLockAlarm() const =0 ;

    /**
     * Write field SFP1_PLL_LOCK_ALARM at 0x24 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_sfp1PllLockAlarm(FpgaVal value) =0 ;

    /**
     * Write field SFP1_PLL_LOCK_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_sfp1PllLockAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_PLL_LOCK_ALARM at 0x24 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_txPllLockAlarm() const =0 ;

    /**
     * Write field TX_PLL_LOCK_ALARM at 0x24 bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txPllLockAlarm(FpgaVal value) =0 ;

    /**
     * Read field TX_PLL_LOCK_ALARM at 0x24 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txPllLockAlarm() const =0 ;

    /**
     * Write field TX_PLL_LOCK_ALARM at 0x24 bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txPllLockAlarm(FpgaVal value) =0 ;

    /**
     * Write field TX_PLL_LOCK_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txPllLockAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_PLL_LOCK_ALARM at 0x24 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_rxPllLockAlarm() const =0 ;

    /**
     * Write field RX_PLL_LOCK_ALARM at 0x24 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxPllLockAlarm(FpgaVal value) =0 ;

    /**
     * Read field RX_PLL_LOCK_ALARM at 0x24 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxPllLockAlarm() const =0 ;

    /**
     * Write field RX_PLL_LOCK_ALARM at 0x24 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxPllLockAlarm(FpgaVal value) =0 ;

    /**
     * Write field RX_PLL_LOCK_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxPllLockAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPD_PLL_LOCK_ALARM at 0x24 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_dpdPllLockAlarm() const =0 ;

    /**
     * Write field DPD_PLL_LOCK_ALARM at 0x24 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdPllLockAlarm(FpgaVal value) =0 ;

    /**
     * Read field DPD_PLL_LOCK_ALARM at 0x24 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdPllLockAlarm() const =0 ;

    /**
     * Write field DPD_PLL_LOCK_ALARM at 0x24 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdPllLockAlarm(FpgaVal value) =0 ;

    /**
     * Write field DPD_PLL_LOCK_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdPllLockAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ALARM_UNLATCHED_EXT_FULL_GAIN at 0x26 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedExtFullGain() const =0 ;


    /**
     * Read field ALARM_UNLATCHED_EXT_FULL_GAIN at 0x26 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedExtFullGain() const =0 ;




    /**
     * Read field ALARM_UNLATCHED_VDD_VALID at 0x26 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedVddValid() const =0 ;


    /**
     * Read field ALARM_UNLATCHED_VDD_VALID at 0x26 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedVddValid() const =0 ;




    /**
     * Read field ALARM_UNLATCHED_OVER_POWER_ALARM at 0x26 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_alarmUnlatchedOverPowerAlarm() const =0 ;


    /**
     * Read field ALARM_UNLATCHED_OVER_POWER_ALARM at 0x26 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_alarmUnlatchedOverPowerAlarm() const =0 ;




    /**
     * Read field EXT_FULL_GAIN_ALARM at 0x28 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_extFullGainAlarm() const =0 ;

    /**
     * Write field EXT_FULL_GAIN_ALARM at 0x28 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_extFullGainAlarm(FpgaVal value) =0 ;

    /**
     * Read field EXT_FULL_GAIN_ALARM at 0x28 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_extFullGainAlarm() const =0 ;

    /**
     * Write field EXT_FULL_GAIN_ALARM at 0x28 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_extFullGainAlarm(FpgaVal value) =0 ;

    /**
     * Write field EXT_FULL_GAIN_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_extFullGainAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VDD_ALARM at 0x28 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_vddAlarm() const =0 ;

    /**
     * Write field VDD_ALARM at 0x28 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vddAlarm(FpgaVal value) =0 ;

    /**
     * Read field VDD_ALARM at 0x28 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vddAlarm() const =0 ;

    /**
     * Write field VDD_ALARM at 0x28 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vddAlarm(FpgaVal value) =0 ;

    /**
     * Write field VDD_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vddAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field OVER_POWER_ALARM at 0x28 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_overPowerAlarm() const =0 ;


    /**
     * Read field OVER_POWER_ALARM at 0x28 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_overPowerAlarm() const =0 ;




    /**
     * Read field MASTER_IRQ_LEVEL at 0x30 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_masterIrqLevel() const =0 ;

    /**
     * Write field MASTER_IRQ_LEVEL at 0x30 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterIrqLevel(FpgaVal value) =0 ;

    /**
     * Read field MASTER_IRQ_LEVEL at 0x30 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterIrqLevel() const =0 ;

    /**
     * Write field MASTER_IRQ_LEVEL at 0x30 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterIrqLevel(FpgaVal value) =0 ;

    /**
     * Write field MASTER_IRQ_LEVEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_masterIrqLevel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MASTER_IRQ_OVERRIDE at 0x30 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_masterIrqOverride() const =0 ;

    /**
     * Write field MASTER_IRQ_OVERRIDE at 0x30 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterIrqOverride(FpgaVal value) =0 ;

    /**
     * Read field MASTER_IRQ_OVERRIDE at 0x30 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterIrqOverride() const =0 ;

    /**
     * Write field MASTER_IRQ_OVERRIDE at 0x30 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterIrqOverride(FpgaVal value) =0 ;

    /**
     * Write field MASTER_IRQ_OVERRIDE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_masterIrqOverride(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MASTER_IRQ_ENABLE at 0x30 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_masterIrqEnable() const =0 ;

    /**
     * Write field MASTER_IRQ_ENABLE at 0x30 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterIrqEnable(FpgaVal value) =0 ;

    /**
     * Read field MASTER_IRQ_ENABLE at 0x30 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterIrqEnable() const =0 ;

    /**
     * Write field MASTER_IRQ_ENABLE at 0x30 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterIrqEnable(FpgaVal value) =0 ;

    /**
     * Write field MASTER_IRQ_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_masterIrqEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field EXT_FULL_GAIN_MASK at 0x32 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_extFullGainMask() const =0 ;

    /**
     * Write field EXT_FULL_GAIN_MASK at 0x32 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_extFullGainMask(FpgaVal value) =0 ;

    /**
     * Read field EXT_FULL_GAIN_MASK at 0x32 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_extFullGainMask() const =0 ;

    /**
     * Write field EXT_FULL_GAIN_MASK at 0x32 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_extFullGainMask(FpgaVal value) =0 ;

    /**
     * Write field EXT_FULL_GAIN_MASK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_extFullGainMask(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VDD_MASK at 0x32 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_vddMask() const =0 ;

    /**
     * Write field VDD_MASK at 0x32 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vddMask(FpgaVal value) =0 ;

    /**
     * Read field VDD_MASK at 0x32 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vddMask() const =0 ;

    /**
     * Write field VDD_MASK at 0x32 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vddMask(FpgaVal value) =0 ;

    /**
     * Write field VDD_MASK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vddMask(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CAPTURE_DONE_MASK at 0x32 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_captureDoneMask() const =0 ;

    /**
     * Write field CAPTURE_DONE_MASK at 0x32 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_captureDoneMask(FpgaVal value) =0 ;

    /**
     * Read field CAPTURE_DONE_MASK at 0x32 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_captureDoneMask() const =0 ;

    /**
     * Write field CAPTURE_DONE_MASK at 0x32 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_captureDoneMask(FpgaVal value) =0 ;

    /**
     * Write field CAPTURE_DONE_MASK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_captureDoneMask(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field EXT_FULL_GAIN_IRQ_STATUS at 0x34 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_extFullGainIrqStatus() const =0 ;

    /**
     * Write field EXT_FULL_GAIN_IRQ_STATUS at 0x34 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_extFullGainIrqStatus(FpgaVal value) =0 ;

    /**
     * Read field EXT_FULL_GAIN_IRQ_STATUS at 0x34 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_extFullGainIrqStatus() const =0 ;

    /**
     * Write field EXT_FULL_GAIN_IRQ_STATUS at 0x34 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_extFullGainIrqStatus(FpgaVal value) =0 ;

    /**
     * Write field EXT_FULL_GAIN_IRQ_STATUS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_extFullGainIrqStatus(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field VDD_IRQ_STATUS at 0x34 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_vddIrqStatus() const =0 ;

    /**
     * Write field VDD_IRQ_STATUS at 0x34 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_vddIrqStatus(FpgaVal value) =0 ;

    /**
     * Read field VDD_IRQ_STATUS at 0x34 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_vddIrqStatus() const =0 ;

    /**
     * Write field VDD_IRQ_STATUS at 0x34 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_vddIrqStatus(FpgaVal value) =0 ;

    /**
     * Write field VDD_IRQ_STATUS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_vddIrqStatus(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CAPTURE_DONE_IRQ_STATUS at 0x34 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_captureDoneIrqStatus() const =0 ;

    /**
     * Write field CAPTURE_DONE_IRQ_STATUS at 0x34 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_captureDoneIrqStatus(FpgaVal value) =0 ;

    /**
     * Read field CAPTURE_DONE_IRQ_STATUS at 0x34 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_captureDoneIrqStatus() const =0 ;

    /**
     * Write field CAPTURE_DONE_IRQ_STATUS at 0x34 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_captureDoneIrqStatus(FpgaVal value) =0 ;

    /**
     * Write field CAPTURE_DONE_IRQ_STATUS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_captureDoneIrqStatus(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WDOG_REFRESH at 0x40 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_wdogRefresh() const =0 ;

    /**
     * Write field WDOG_REFRESH at 0x40 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wdogRefresh(FpgaVal value) =0 ;

    /**
     * Read field WDOG_REFRESH at 0x40 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wdogRefresh() const =0 ;

    /**
     * Write field WDOG_REFRESH at 0x40 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wdogRefresh(FpgaVal value) =0 ;

    /**
     * Write field WDOG_REFRESH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wdogRefresh(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FIBRE_RESET_EVENT at 0x40 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_fibreResetEvent() const =0 ;


    /**
     * Read field FIBRE_RESET_EVENT at 0x40 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fibreResetEvent() const =0 ;




    /**
     * Read field WDOG_TIMEOUT_EVENT at 0x40 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_wdogTimeoutEvent() const =0 ;


    /**
     * Read field WDOG_TIMEOUT_EVENT at 0x40 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wdogTimeoutEvent() const =0 ;




    /**
     * Read field WDOG_RESET_EVENT at 0x40 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_wdogResetEvent() const =0 ;


    /**
     * Read field WDOG_RESET_EVENT at 0x40 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wdogResetEvent() const =0 ;




    /**
     * Read field WDOG_ENABLE at 0x40 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_wdogEnable() const =0 ;

    /**
     * Write field WDOG_ENABLE at 0x40 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wdogEnable(FpgaVal value) =0 ;

    /**
     * Read field WDOG_ENABLE at 0x40 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wdogEnable() const =0 ;

    /**
     * Write field WDOG_ENABLE at 0x40 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wdogEnable(FpgaVal value) =0 ;

    /**
     * Write field WDOG_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wdogEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WDOG_RESET at 0x40 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_wdogReset() const =0 ;

    /**
     * Write field WDOG_RESET at 0x40 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wdogReset(FpgaVal value) =0 ;

    /**
     * Read field WDOG_RESET at 0x40 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wdogReset() const =0 ;

    /**
     * Write field WDOG_RESET at 0x40 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wdogReset(FpgaVal value) =0 ;

    /**
     * Write field WDOG_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wdogReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_VCO_CONTROL at 0x46 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_rxVcoControl() const =0 ;

    /**
     * Write field RX_VCO_CONTROL at 0x46 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxVcoControl(FpgaVal value) =0 ;

    /**
     * Read field RX_VCO_CONTROL at 0x46 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxVcoControl() const =0 ;

    /**
     * Write field RX_VCO_CONTROL at 0x46 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxVcoControl(FpgaVal value) =0 ;

    /**
     * Write field RX_VCO_CONTROL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxVcoControl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRX_VCO_CONTROL at 0x46 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_srxVcoControl() const =0 ;

    /**
     * Write field SRX_VCO_CONTROL at 0x46 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srxVcoControl(FpgaVal value) =0 ;

    /**
     * Read field SRX_VCO_CONTROL at 0x46 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srxVcoControl() const =0 ;

    /**
     * Write field SRX_VCO_CONTROL at 0x46 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srxVcoControl(FpgaVal value) =0 ;

    /**
     * Write field SRX_VCO_CONTROL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srxVcoControl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SAMPLE_POINT_LO at 0x8e bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_samplePointLo() const =0 ;

    /**
     * Write field SAMPLE_POINT_LO at 0x8e bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_samplePointLo(FpgaVal value) =0 ;

    /**
     * Read field SAMPLE_POINT_LO at 0x8e bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_samplePointLo() const =0 ;

    /**
     * Write field SAMPLE_POINT_LO at 0x8e bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_samplePointLo(FpgaVal value) =0 ;

    /**
     * Write field SAMPLE_POINT_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_samplePointLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SAMPLE_POINT_HI at 0xa2 bits [14..12]
     * \return field value
     */
    virtual const FpgaVal read_samplePointHi() const =0 ;

    /**
     * Write field SAMPLE_POINT_HI at 0xa2 bits [14..12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_samplePointHi(FpgaVal value) =0 ;

    /**
     * Read field SAMPLE_POINT_HI at 0xa2 bits [14..12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_samplePointHi() const =0 ;

    /**
     * Write field SAMPLE_POINT_HI at 0xa2 bits [14..12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_samplePointHi(FpgaVal value) =0 ;

    /**
     * Write field SAMPLE_POINT_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_samplePointHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UART_FIFO_WRITE at 0xb2 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_UartFifoWrite() const =0 ;

    /**
     * Write field UART_FIFO_WRITE at 0xb2 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_UartFifoWrite(FpgaVal value) =0 ;

    /**
     * Read field UART_FIFO_WRITE at 0xb2 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartFifoWrite() const =0 ;

    /**
     * Write field UART_FIFO_WRITE at 0xb2 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_UartFifoWrite(FpgaVal value) =0 ;

    /**
     * Write field UART_FIFO_WRITE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_UartFifoWrite(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UART_FIFO_READ at 0xb4 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_UartFifoRead() const =0 ;


    /**
     * Read field UART_FIFO_READ at 0xb4 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartFifoRead() const =0 ;




    /**
     * Read field UART_RX_FRAME_ERROR at 0xb8 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_UartRxFrameError() const =0 ;


    /**
     * Read field UART_RX_FRAME_ERROR at 0xb8 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartRxFrameError() const =0 ;




    /**
     * Read field UART_RX_OVERRUN_ERROR at 0xb8 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_UartRxOverrunError() const =0 ;


    /**
     * Read field UART_RX_OVERRUN_ERROR at 0xb8 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartRxOverrunError() const =0 ;




    /**
     * Read field UART_TX_BUFFER_FULL at 0xb8 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_UartTxBufferFull() const =0 ;


    /**
     * Read field UART_TX_BUFFER_FULL at 0xb8 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartTxBufferFull() const =0 ;




    /**
     * Read field UART_TX_BUFFER_EMPTY at 0xb8 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_UartTxBufferEmpty() const =0 ;


    /**
     * Read field UART_TX_BUFFER_EMPTY at 0xb8 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartTxBufferEmpty() const =0 ;




    /**
     * Read field UART_RX_BUFFER_FULL at 0xb8 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_UartRxBufferFull() const =0 ;


    /**
     * Read field UART_RX_BUFFER_FULL at 0xb8 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartRxBufferFull() const =0 ;




    /**
     * Read field UART_RX_DATA_PRESENT at 0xb8 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_UartRxDataPresent() const =0 ;


    /**
     * Read field UART_RX_DATA_PRESENT at 0xb8 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartRxDataPresent() const =0 ;




    /**
     * Read field UART_RX_FIFO_RESET at 0xbc bits [0]
     * \return field value
     */
    virtual const FpgaVal read_UartRxFifoReset() const =0 ;

    /**
     * Write field UART_RX_FIFO_RESET at 0xbc bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_UartRxFifoReset(FpgaVal value) =0 ;

    /**
     * Read field UART_RX_FIFO_RESET at 0xbc bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartRxFifoReset() const =0 ;

    /**
     * Write field UART_RX_FIFO_RESET at 0xbc bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_UartRxFifoReset(FpgaVal value) =0 ;

    /**
     * Write field UART_RX_FIFO_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_UartRxFifoReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UART_TX_FIFO_RESET at 0xbc bits [1]
     * \return field value
     */
    virtual const FpgaVal read_UartTxFifoReset() const =0 ;

    /**
     * Write field UART_TX_FIFO_RESET at 0xbc bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_UartTxFifoReset(FpgaVal value) =0 ;

    /**
     * Read field UART_TX_FIFO_RESET at 0xbc bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartTxFifoReset() const =0 ;

    /**
     * Write field UART_TX_FIFO_RESET at 0xbc bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_UartTxFifoReset(FpgaVal value) =0 ;

    /**
     * Write field UART_TX_FIFO_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_UartTxFifoReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UART_FIFO_TRIGGER at 0xbc bits [2]
     * \return field value
     */
    virtual const FpgaVal read_UartFifoTrigger() const =0 ;

    /**
     * Write field UART_FIFO_TRIGGER at 0xbc bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_UartFifoTrigger(FpgaVal value) =0 ;

    /**
     * Read field UART_FIFO_TRIGGER at 0xbc bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartFifoTrigger() const =0 ;

    /**
     * Write field UART_FIFO_TRIGGER at 0xbc bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_UartFifoTrigger(FpgaVal value) =0 ;

    /**
     * Write field UART_FIFO_TRIGGER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_UartFifoTrigger(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UART_RX_ENABLE_CONTROL at 0xbe bits [0]
     * \return field value
     */
    virtual const FpgaVal read_UartRxEnableControl() const =0 ;

    /**
     * Write field UART_RX_ENABLE_CONTROL at 0xbe bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_UartRxEnableControl(FpgaVal value) =0 ;

    /**
     * Read field UART_RX_ENABLE_CONTROL at 0xbe bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartRxEnableControl() const =0 ;

    /**
     * Write field UART_RX_ENABLE_CONTROL at 0xbe bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_UartRxEnableControl(FpgaVal value) =0 ;

    /**
     * Write field UART_RX_ENABLE_CONTROL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_UartRxEnableControl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UART_TX_ENABLE_CONTROL at 0xbe bits [1]
     * \return field value
     */
    virtual const FpgaVal read_UartTxEnableControl() const =0 ;

    /**
     * Write field UART_TX_ENABLE_CONTROL at 0xbe bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_UartTxEnableControl(FpgaVal value) =0 ;

    /**
     * Read field UART_TX_ENABLE_CONTROL at 0xbe bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartTxEnableControl() const =0 ;

    /**
     * Write field UART_TX_ENABLE_CONTROL at 0xbe bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_UartTxEnableControl(FpgaVal value) =0 ;

    /**
     * Write field UART_TX_ENABLE_CONTROL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_UartTxEnableControl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UART_AUTO_RX_MODE at 0xbe bits [2]
     * \return field value
     */
    virtual const FpgaVal read_UartAutoRxMode() const =0 ;

    /**
     * Write field UART_AUTO_RX_MODE at 0xbe bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_UartAutoRxMode(FpgaVal value) =0 ;

    /**
     * Read field UART_AUTO_RX_MODE at 0xbe bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_UartAutoRxMode() const =0 ;

    /**
     * Write field UART_AUTO_RX_MODE at 0xbe bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_UartAutoRxMode(FpgaVal value) =0 ;

    /**
     * Write field UART_AUTO_RX_MODE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_UartAutoRxMode(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FPGA_MAJOR_VER at 0x100 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_fpgaMajorVer() const =0 ;


    /**
     * Read field FPGA_MAJOR_VER at 0x100 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaMajorVer() const =0 ;




    /**
     * Read field FPGA_MINOR_VER at 0x100 bits [15..8]
     * \return field value
     */
    virtual const FpgaVal read_fpgaMinorVer() const =0 ;


    /**
     * Read field FPGA_MINOR_VER at 0x100 bits [15..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaMinorVer() const =0 ;




    /**
     * Read field BOARD_ID at 0x102 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_boardId() const =0 ;


    /**
     * Read field BOARD_ID at 0x102 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_boardId() const =0 ;




    /**
     * Read field BOARD_VER at 0x102 bits [15..8]
     * \return field value
     */
    virtual const FpgaVal read_boardVer() const =0 ;


    /**
     * Read field BOARD_VER at 0x102 bits [15..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_boardVer() const =0 ;




    /**
     * Read field FPGA_BUILD_NUM at 0x104 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_fpgaBuildNum() const =0 ;


    /**
     * Read field FPGA_BUILD_NUM at 0x104 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaBuildNum() const =0 ;




    /**
     * Read field CUSTOMER_ID at 0x108 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_customerId() const =0 ;


    /**
     * Read field CUSTOMER_ID at 0x108 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_customerId() const =0 ;




    /**
     * Read field FPGA_FIBRES at 0x120 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_fpgaFibres() const =0 ;


    /**
     * Read field FPGA_FIBRES at 0x120 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaFibres() const =0 ;




    /**
     * Read field FPGA_TX_ANTENNAS at 0x122 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_fpgaTxAntennas() const =0 ;


    /**
     * Read field FPGA_TX_ANTENNAS at 0x122 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaTxAntennas() const =0 ;




    /**
     * Read field FPGA_RX_ANTENNAS at 0x124 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_fpgaRxAntennas() const =0 ;


    /**
     * Read field FPGA_RX_ANTENNAS at 0x124 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaRxAntennas() const =0 ;




    /**
     * Read field FPGA_DL_CARRIERS at 0x126 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_fpgaDlCarriers() const =0 ;


    /**
     * Read field FPGA_DL_CARRIERS at 0x126 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaDlCarriers() const =0 ;




    /**
     * Read field FPGA_UL_CARRIERS at 0x128 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_fpgaUlCarriers() const =0 ;


    /**
     * Read field FPGA_UL_CARRIERS at 0x128 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaUlCarriers() const =0 ;




    /**
     * Read field NUM_DL_RF_CHAINS at 0x12a bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_numDlRfChains() const =0 ;


    /**
     * Read field NUM_DL_RF_CHAINS at 0x12a bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_numDlRfChains() const =0 ;




    /**
     * Read field NUM_UL_RF_CHAINS at 0x12c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_numUlRfChains() const =0 ;


    /**
     * Read field NUM_UL_RF_CHAINS at 0x12c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_numUlRfChains() const =0 ;




    /**
     * Read field DL_TUNER_CLOCKS_PER_SAMPLE at 0x12e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_dlTunerClocksPerSample() const =0 ;


    /**
     * Read field DL_TUNER_CLOCKS_PER_SAMPLE at 0x12e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlTunerClocksPerSample() const =0 ;




    /**
     * Read field UL_TUNER_CLOCKS_PER_SAMPLE at 0x12e bits [11..8]
     * \return field value
     */
    virtual const FpgaVal read_ulTunerClocksPerSample() const =0 ;


    /**
     * Read field UL_TUNER_CLOCKS_PER_SAMPLE at 0x12e bits [11..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulTunerClocksPerSample() const =0 ;




    /**
     * Read field NUM_WAVEFORM_MODULES at 0x130 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_numWaveformModules() const =0 ;


    /**
     * Read field NUM_WAVEFORM_MODULES at 0x130 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_numWaveformModules() const =0 ;




    /**
     * Read field NUM_PIM_MODULES at 0x132 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_numPimModules() const =0 ;


    /**
     * Read field NUM_PIM_MODULES at 0x132 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_numPimModules() const =0 ;




    /**
     * Read field NUM_COMMON_SYNC_MODULES at 0x134 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_numCommonSyncModules() const =0 ;


    /**
     * Read field NUM_COMMON_SYNC_MODULES at 0x134 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_numCommonSyncModules() const =0 ;




    /**
     * Read field DL_TUNER_NCO_BITS at 0x136 bits [5..0]
     * \return field value
     */
    virtual const FpgaVal read_dlTunerNcoBits() const =0 ;


    /**
     * Read field DL_TUNER_NCO_BITS at 0x136 bits [5..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlTunerNcoBits() const =0 ;




    /**
     * Read field UL_TUNER_NCO_BITS at 0x136 bits [13..8]
     * \return field value
     */
    virtual const FpgaVal read_ulTunerNcoBits() const =0 ;


    /**
     * Read field UL_TUNER_NCO_BITS at 0x136 bits [13..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulTunerNcoBits() const =0 ;




    /**
     * Read field FEATURE_NUM_BITS at 0x140 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_featureNumBits() const =0 ;


    /**
     * Read field FEATURE_NUM_BITS at 0x140 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureNumBits() const =0 ;




    /**
     * Read field FEATURE_RSSI_V2 at 0x142 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_featureRssiV2() const =0 ;


    /**
     * Read field FEATURE_RSSI_V2 at 0x142 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureRssiV2() const =0 ;




    /**
     * Read field FEATURE_DPD_V2_BIGMEM at 0x142 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_featureDpdV2Bigmem() const =0 ;


    /**
     * Read field FEATURE_DPD_V2_BIGMEM at 0x142 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureDpdV2Bigmem() const =0 ;




    /**
     * Read field FEATURE_RAW_CPRI_IQ_MAPPING at 0x142 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_featureRawCpriIqMapping() const =0 ;


    /**
     * Read field FEATURE_RAW_CPRI_IQ_MAPPING at 0x142 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureRawCpriIqMapping() const =0 ;




    /**
     * Read field FEATURE_DPD_ADC_ALARM at 0x142 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_featureDpdAdcAlarm() const =0 ;


    /**
     * Read field FEATURE_DPD_ADC_ALARM at 0x142 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureDpdAdcAlarm() const =0 ;




    /**
     * Read field FEATURE_DUAL_BAND_RX_VCO at 0x142 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_featureDualBandRxVco() const =0 ;


    /**
     * Read field FEATURE_DUAL_BAND_RX_VCO at 0x142 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureDualBandRxVco() const =0 ;




    /**
     * Read field FEATURE_DDC_OUT_IQ_INVERT_EARLY at 0x142 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_featureDdcOutIqInvertEarly() const =0 ;


    /**
     * Read field FEATURE_DDC_OUT_IQ_INVERT_EARLY at 0x142 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureDdcOutIqInvertEarly() const =0 ;




    /**
     * Read field FEATURE_DDC_OUT_IQ_INVERT_LATE at 0x142 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_featureDdcOutIqInvertLate() const =0 ;


    /**
     * Read field FEATURE_DDC_OUT_IQ_INVERT_LATE at 0x142 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureDdcOutIqInvertLate() const =0 ;




    /**
     * Read field FEATURE_POWER_MEASUREMENT_V2 at 0x142 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_featurePowerMeasurementV2() const =0 ;


    /**
     * Read field FEATURE_POWER_MEASUREMENT_V2 at 0x142 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featurePowerMeasurementV2() const =0 ;




    /**
     * Read field FEATURE_CHBW3_BIT at 0x142 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_featureChbw3Bit() const =0 ;


    /**
     * Read field FEATURE_CHBW3_BIT at 0x142 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureChbw3Bit() const =0 ;




    /**
     * Read field FEATURE_BB_PWR_PROG_ALPHA at 0x142 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_featureBbPwrProgAlpha() const =0 ;


    /**
     * Read field FEATURE_BB_PWR_PROG_ALPHA at 0x142 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureBbPwrProgAlpha() const =0 ;




    /**
     * Read field FEATURE_VLAN_TAGGING at 0x142 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_featureVlanTagging() const =0 ;


    /**
     * Read field FEATURE_VLAN_TAGGING at 0x142 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureVlanTagging() const =0 ;




    /**
     * Read field FEATURE_STATIC_DAISY_CHAIN at 0x142 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_featureStaticDaisyChain() const =0 ;


    /**
     * Read field FEATURE_STATIC_DAISY_CHAIN at 0x142 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureStaticDaisyChain() const =0 ;




    /**
     * Read field FEATURE_PROGRAMMABLE_CFR_FINAL_CLIP at 0x142 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_featureProgrammableCfrFinalClip() const =0 ;


    /**
     * Read field FEATURE_PROGRAMMABLE_CFR_FINAL_CLIP at 0x142 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureProgrammableCfrFinalClip() const =0 ;




    /**
     * Read field FEATURE_CDC_DELAY_BARREL_SHIFT at 0x142 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_featureCdcDelayBarrelShift() const =0 ;


    /**
     * Read field FEATURE_CDC_DELAY_BARREL_SHIFT at 0x142 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureCdcDelayBarrelShift() const =0 ;




    /**
     * Read field FEATURE_CORDIC_BASED_RSSI at 0x142 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_featureCordicBasedRssi() const =0 ;


    /**
     * Read field FEATURE_CORDIC_BASED_RSSI at 0x142 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureCordicBasedRssi() const =0 ;




    /**
     * Read field FEATURE_BB_FILTERS_AMPLITUDE at 0x142 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_featureBbFiltersAmplitude() const =0 ;


    /**
     * Read field FEATURE_BB_FILTERS_AMPLITUDE at 0x142 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureBbFiltersAmplitude() const =0 ;




    /**
     * Read field FEATURE_CFR_XILINX at 0x144 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_featureCfrXilinx() const =0 ;


    /**
     * Read field FEATURE_CFR_XILINX at 0x144 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureCfrXilinx() const =0 ;




    /**
     * Read field FEATURE_CPRI10_GBPS_CAPABLE at 0x144 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_featureCpri10GbpsCapable() const =0 ;


    /**
     * Read field FEATURE_CPRI10_GBPS_CAPABLE at 0x144 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureCpri10GbpsCapable() const =0 ;




    /**
     * Read field PWM14_BIT_FEATURE at 0x144 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_pwm14BitFeature() const =0 ;


    /**
     * Read field PWM14_BIT_FEATURE at 0x144 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_pwm14BitFeature() const =0 ;




    /**
     * Read field FEATURE_BB_FILTER2_STAGE_SQRT at 0x144 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_featureBbFilter2StageSqrt() const =0 ;


    /**
     * Read field FEATURE_BB_FILTER2_STAGE_SQRT at 0x144 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureBbFilter2StageSqrt() const =0 ;




    /**
     * Read field FEATURE_CLOSER_CHANNEL_SPACING at 0x144 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_featureCloserChannelSpacing() const =0 ;


    /**
     * Read field FEATURE_CLOSER_CHANNEL_SPACING at 0x144 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureCloserChannelSpacing() const =0 ;




    /**
     * Read field FEATURE_SRX_POWER_MEAS at 0x144 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_featureSrxPowerMeas() const =0 ;


    /**
     * Read field FEATURE_SRX_POWER_MEAS at 0x144 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureSrxPowerMeas() const =0 ;




    /**
     * Read field FEATURE_EYE_SCAN at 0x144 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_featureEyeScan() const =0 ;


    /**
     * Read field FEATURE_EYE_SCAN at 0x144 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_featureEyeScan() const =0 ;




    /**
     * Read field XPS_BYPASS at 0x144 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_XpsBypass() const =0 ;


    /**
     * Read field XPS_BYPASS at 0x144 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_XpsBypass() const =0 ;




    /**
     * Read field SPI0_RD_OPP_EDGE at 0x200 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_spi0RdOppEdge() const =0 ;

    /**
     * Write field SPI0_RD_OPP_EDGE at 0x200 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0RdOppEdge(FpgaVal value) =0 ;

    /**
     * Read field SPI0_RD_OPP_EDGE at 0x200 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0RdOppEdge() const =0 ;

    /**
     * Write field SPI0_RD_OPP_EDGE at 0x200 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0RdOppEdge(FpgaVal value) =0 ;

    /**
     * Write field SPI0_RD_OPP_EDGE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0RdOppEdge(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_CLK_INVERT at 0x200 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_spi0ClkInvert() const =0 ;

    /**
     * Write field SPI0_CLK_INVERT at 0x200 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0ClkInvert(FpgaVal value) =0 ;

    /**
     * Read field SPI0_CLK_INVERT at 0x200 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0ClkInvert() const =0 ;

    /**
     * Write field SPI0_CLK_INVERT at 0x200 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0ClkInvert(FpgaVal value) =0 ;

    /**
     * Write field SPI0_CLK_INVERT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0ClkInvert(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_WDATA_LEN at 0x200 bits [10..6]
     * \return field value
     */
    virtual const FpgaVal read_spi0WdataLen() const =0 ;

    /**
     * Write field SPI0_WDATA_LEN at 0x200 bits [10..6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0WdataLen(FpgaVal value) =0 ;

    /**
     * Read field SPI0_WDATA_LEN at 0x200 bits [10..6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0WdataLen() const =0 ;

    /**
     * Write field SPI0_WDATA_LEN at 0x200 bits [10..6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0WdataLen(FpgaVal value) =0 ;

    /**
     * Write field SPI0_WDATA_LEN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0WdataLen(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_RDATA_LEN at 0x200 bits [15..11]
     * \return field value
     */
    virtual const FpgaVal read_spi0RdataLen() const =0 ;

    /**
     * Write field SPI0_RDATA_LEN at 0x200 bits [15..11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0RdataLen(FpgaVal value) =0 ;

    /**
     * Read field SPI0_RDATA_LEN at 0x200 bits [15..11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0RdataLen() const =0 ;

    /**
     * Write field SPI0_RDATA_LEN at 0x200 bits [15..11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0RdataLen(FpgaVal value) =0 ;

    /**
     * Write field SPI0_RDATA_LEN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0RdataLen(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_SELECT at 0x202 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0Select() const =0 ;

    /**
     * Write field SPI0_SELECT at 0x202 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0Select(FpgaVal value) =0 ;

    /**
     * Read field SPI0_SELECT at 0x202 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0Select() const =0 ;

    /**
     * Write field SPI0_SELECT at 0x202 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0Select(FpgaVal value) =0 ;

    /**
     * Write field SPI0_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0Select(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_WRITE_DATA_LO at 0x204 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0WriteDataLo() const =0 ;

    /**
     * Write field SPI0_WRITE_DATA_LO at 0x204 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0WriteDataLo(FpgaVal value) =0 ;

    /**
     * Read field SPI0_WRITE_DATA_LO at 0x204 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0WriteDataLo() const =0 ;

    /**
     * Write field SPI0_WRITE_DATA_LO at 0x204 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0WriteDataLo(FpgaVal value) =0 ;

    /**
     * Write field SPI0_WRITE_DATA_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0WriteDataLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_WRITE_DATA_HI at 0x206 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0WriteDataHi() const =0 ;

    /**
     * Write field SPI0_WRITE_DATA_HI at 0x206 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0WriteDataHi(FpgaVal value) =0 ;

    /**
     * Read field SPI0_WRITE_DATA_HI at 0x206 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0WriteDataHi() const =0 ;

    /**
     * Write field SPI0_WRITE_DATA_HI at 0x206 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0WriteDataHi(FpgaVal value) =0 ;

    /**
     * Write field SPI0_WRITE_DATA_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0WriteDataHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_READ_DATA_LO at 0x208 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0ReadDataLo() const =0 ;


    /**
     * Read field SPI0_READ_DATA_LO at 0x208 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0ReadDataLo() const =0 ;




    /**
     * Read field SPI0_READ_DATA_HI at 0x20a bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0ReadDataHi() const =0 ;


    /**
     * Read field SPI0_READ_DATA_HI at 0x20a bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0ReadDataHi() const =0 ;




    /**
     * Read field PRBS_TX_EN at 0x20c bits [2..0]
     * \return field value
     */
    virtual const FpgaVal read_prbsTxEn() const =0 ;

    /**
     * Write field PRBS_TX_EN at 0x20c bits [2..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_prbsTxEn(FpgaVal value) =0 ;

    /**
     * Read field PRBS_TX_EN at 0x20c bits [2..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_prbsTxEn() const =0 ;

    /**
     * Write field PRBS_TX_EN at 0x20c bits [2..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_prbsTxEn(FpgaVal value) =0 ;

    /**
     * Write field PRBS_TX_EN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_prbsTxEn(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PRBS_TX_FORCE_ERR at 0x20c bits [3]
     * \return field value
     */
    virtual const FpgaVal read_prbsTxForceErr() const =0 ;

    /**
     * Write field PRBS_TX_FORCE_ERR at 0x20c bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_prbsTxForceErr(FpgaVal value) =0 ;

    /**
     * Read field PRBS_TX_FORCE_ERR at 0x20c bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_prbsTxForceErr() const =0 ;

    /**
     * Write field PRBS_TX_FORCE_ERR at 0x20c bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_prbsTxForceErr(FpgaVal value) =0 ;

    /**
     * Write field PRBS_TX_FORCE_ERR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_prbsTxForceErr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PRBS_CNTR_RESET at 0x20c bits [4]
     * \return field value
     */
    virtual const FpgaVal read_prbsCntrReset() const =0 ;

    /**
     * Write field PRBS_CNTR_RESET at 0x20c bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_prbsCntrReset(FpgaVal value) =0 ;

    /**
     * Read field PRBS_CNTR_RESET at 0x20c bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_prbsCntrReset() const =0 ;

    /**
     * Write field PRBS_CNTR_RESET at 0x20c bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_prbsCntrReset(FpgaVal value) =0 ;

    /**
     * Write field PRBS_CNTR_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_prbsCntrReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PRBS_RX_EN at 0x20c bits [7..5]
     * \return field value
     */
    virtual const FpgaVal read_prbsRxEn() const =0 ;

    /**
     * Write field PRBS_RX_EN at 0x20c bits [7..5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_prbsRxEn(FpgaVal value) =0 ;

    /**
     * Read field PRBS_RX_EN at 0x20c bits [7..5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_prbsRxEn() const =0 ;

    /**
     * Write field PRBS_RX_EN at 0x20c bits [7..5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_prbsRxEn(FpgaVal value) =0 ;

    /**
     * Write field PRBS_RX_EN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_prbsRxEn(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PRBS_RX_ERR at 0x20c bits [8]
     * \return field value
     */
    virtual const FpgaVal read_prbsRxErr() const =0 ;

    /**
     * Write field PRBS_RX_ERR at 0x20c bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_prbsRxErr(FpgaVal value) =0 ;

    /**
     * Read field PRBS_RX_ERR at 0x20c bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_prbsRxErr() const =0 ;

    /**
     * Write field PRBS_RX_ERR at 0x20c bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_prbsRxErr(FpgaVal value) =0 ;

    /**
     * Write field PRBS_RX_ERR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_prbsRxErr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_ARB_LOST at 0x214 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_i2cIsrArbLost() const =0 ;

    /**
     * Write field I2C_ISR_ARB_LOST at 0x214 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cIsrArbLost(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_ARB_LOST at 0x214 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cIsrArbLost() const =0 ;

    /**
     * Write field I2C_ISR_ARB_LOST at 0x214 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cIsrArbLost(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_ARB_LOST in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cIsrArbLost(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_TX_ERROR at 0x214 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_i2cIsrTxError() const =0 ;

    /**
     * Write field I2C_ISR_TX_ERROR at 0x214 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cIsrTxError(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_TX_ERROR at 0x214 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cIsrTxError() const =0 ;

    /**
     * Write field I2C_ISR_TX_ERROR at 0x214 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cIsrTxError(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_TX_ERROR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cIsrTxError(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_SLAVE_TX_COMPLETE at 0x214 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_I2cIsrSlaveTxComplete() const =0 ;

    /**
     * Write field I2C_ISR_SLAVE_TX_COMPLETE at 0x214 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_I2cIsrSlaveTxComplete(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_SLAVE_TX_COMPLETE at 0x214 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_I2cIsrSlaveTxComplete() const =0 ;

    /**
     * Write field I2C_ISR_SLAVE_TX_COMPLETE at 0x214 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_I2cIsrSlaveTxComplete(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_SLAVE_TX_COMPLETE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_I2cIsrSlaveTxComplete(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_TX_FIFO_EMPTY at 0x214 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_i2cIsrTxFifoEmpty() const =0 ;

    /**
     * Write field I2C_ISR_TX_FIFO_EMPTY at 0x214 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cIsrTxFifoEmpty(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_TX_FIFO_EMPTY at 0x214 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cIsrTxFifoEmpty() const =0 ;

    /**
     * Write field I2C_ISR_TX_FIFO_EMPTY at 0x214 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cIsrTxFifoEmpty(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_TX_FIFO_EMPTY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cIsrTxFifoEmpty(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_RX_FIFO_FULL at 0x214 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_i2cIsrRxFifoFull() const =0 ;

    /**
     * Write field I2C_ISR_RX_FIFO_FULL at 0x214 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cIsrRxFifoFull(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_RX_FIFO_FULL at 0x214 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cIsrRxFifoFull() const =0 ;

    /**
     * Write field I2C_ISR_RX_FIFO_FULL at 0x214 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cIsrRxFifoFull(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_RX_FIFO_FULL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cIsrRxFifoFull(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_I2C_NOT_BUSY at 0x214 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_i2cIsrI2cNotBusy() const =0 ;

    /**
     * Write field I2C_ISR_I2C_NOT_BUSY at 0x214 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cIsrI2cNotBusy(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_I2C_NOT_BUSY at 0x214 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cIsrI2cNotBusy() const =0 ;

    /**
     * Write field I2C_ISR_I2C_NOT_BUSY at 0x214 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cIsrI2cNotBusy(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_I2C_NOT_BUSY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cIsrI2cNotBusy(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_ADDRESSED_AS_SLAVE at 0x214 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_i2cIsrAddressedAsSlave() const =0 ;

    /**
     * Write field I2C_ISR_ADDRESSED_AS_SLAVE at 0x214 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cIsrAddressedAsSlave(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_ADDRESSED_AS_SLAVE at 0x214 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cIsrAddressedAsSlave() const =0 ;

    /**
     * Write field I2C_ISR_ADDRESSED_AS_SLAVE at 0x214 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cIsrAddressedAsSlave(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_ADDRESSED_AS_SLAVE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cIsrAddressedAsSlave(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_NOT_ADDRESSED_AS_SLAVE at 0x214 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_i2cIsrNotAddressedAsSlave() const =0 ;

    /**
     * Write field I2C_ISR_NOT_ADDRESSED_AS_SLAVE at 0x214 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cIsrNotAddressedAsSlave(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_NOT_ADDRESSED_AS_SLAVE at 0x214 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cIsrNotAddressedAsSlave() const =0 ;

    /**
     * Write field I2C_ISR_NOT_ADDRESSED_AS_SLAVE at 0x214 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cIsrNotAddressedAsSlave(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_NOT_ADDRESSED_AS_SLAVE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cIsrNotAddressedAsSlave(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ISR_TX_FIFO_HALF_EMPTY at 0x214 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_i2cIsrTxFifoHalfEmpty() const =0 ;

    /**
     * Write field I2C_ISR_TX_FIFO_HALF_EMPTY at 0x214 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cIsrTxFifoHalfEmpty(FpgaVal value) =0 ;

    /**
     * Read field I2C_ISR_TX_FIFO_HALF_EMPTY at 0x214 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cIsrTxFifoHalfEmpty() const =0 ;

    /**
     * Write field I2C_ISR_TX_FIFO_HALF_EMPTY at 0x214 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cIsrTxFifoHalfEmpty(FpgaVal value) =0 ;

    /**
     * Write field I2C_ISR_TX_FIFO_HALF_EMPTY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cIsrTxFifoHalfEmpty(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_ENABLE at 0x216 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrEnable() const =0 ;

    /**
     * Write field I2C_CSR_ENABLE at 0x216 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrEnable(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_ENABLE at 0x216 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrEnable() const =0 ;

    /**
     * Write field I2C_CSR_ENABLE at 0x216 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrEnable(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_TX_FIFO_RESET at 0x216 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrTxFifoReset() const =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_RESET at 0x216 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrTxFifoReset(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_TX_FIFO_RESET at 0x216 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrTxFifoReset() const =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_RESET at 0x216 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrTxFifoReset(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrTxFifoReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_MSMS_MASTER at 0x216 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrMsmsMaster() const =0 ;

    /**
     * Write field I2C_CSR_MSMS_MASTER at 0x216 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrMsmsMaster(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_MSMS_MASTER at 0x216 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrMsmsMaster() const =0 ;

    /**
     * Write field I2C_CSR_MSMS_MASTER at 0x216 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrMsmsMaster(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_MSMS_MASTER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrMsmsMaster(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_TX at 0x216 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrTx() const =0 ;

    /**
     * Write field I2C_CSR_TX at 0x216 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrTx(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_TX at 0x216 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrTx() const =0 ;

    /**
     * Write field I2C_CSR_TX at 0x216 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrTx(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_TX in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrTx(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_TX_ACK_ENABLE at 0x216 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrTxAckEnable() const =0 ;

    /**
     * Write field I2C_CSR_TX_ACK_ENABLE at 0x216 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrTxAckEnable(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_TX_ACK_ENABLE at 0x216 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrTxAckEnable() const =0 ;

    /**
     * Write field I2C_CSR_TX_ACK_ENABLE at 0x216 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrTxAckEnable(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_TX_ACK_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrTxAckEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_REPEAT_START at 0x216 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrRepeatStart() const =0 ;

    /**
     * Write field I2C_CSR_REPEAT_START at 0x216 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrRepeatStart(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_REPEAT_START at 0x216 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrRepeatStart() const =0 ;

    /**
     * Write field I2C_CSR_REPEAT_START at 0x216 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrRepeatStart(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_REPEAT_START in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrRepeatStart(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_GENERAL_CALL_ENABLE at 0x216 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrGeneralCallEnable() const =0 ;

    /**
     * Write field I2C_CSR_GENERAL_CALL_ENABLE at 0x216 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrGeneralCallEnable(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_GENERAL_CALL_ENABLE at 0x216 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrGeneralCallEnable() const =0 ;

    /**
     * Write field I2C_CSR_GENERAL_CALL_ENABLE at 0x216 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrGeneralCallEnable(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_GENERAL_CALL_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrGeneralCallEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_RESET_N at 0x216 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrResetN() const =0 ;

    /**
     * Write field I2C_CSR_RESET_N at 0x216 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrResetN(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_RESET_N at 0x216 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrResetN() const =0 ;

    /**
     * Write field I2C_CSR_RESET_N at 0x216 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrResetN(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_RESET_N in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrResetN(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_ADDRESSED_BY_GENERAL_CALL at 0x216 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrAddressedByGeneralCall() const =0 ;

    /**
     * Write field I2C_CSR_ADDRESSED_BY_GENERAL_CALL at 0x216 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrAddressedByGeneralCall(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_ADDRESSED_BY_GENERAL_CALL at 0x216 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrAddressedByGeneralCall() const =0 ;

    /**
     * Write field I2C_CSR_ADDRESSED_BY_GENERAL_CALL at 0x216 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrAddressedByGeneralCall(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_ADDRESSED_BY_GENERAL_CALL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrAddressedByGeneralCall(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_ADDRESSED_AS_SLAVE at 0x216 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrAddressedAsSlave() const =0 ;

    /**
     * Write field I2C_CSR_ADDRESSED_AS_SLAVE at 0x216 bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrAddressedAsSlave(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_ADDRESSED_AS_SLAVE at 0x216 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrAddressedAsSlave() const =0 ;

    /**
     * Write field I2C_CSR_ADDRESSED_AS_SLAVE at 0x216 bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrAddressedAsSlave(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_ADDRESSED_AS_SLAVE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrAddressedAsSlave(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_BUS_BUSY at 0x216 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrBusBusy() const =0 ;

    /**
     * Write field I2C_CSR_BUS_BUSY at 0x216 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrBusBusy(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_BUS_BUSY at 0x216 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrBusBusy() const =0 ;

    /**
     * Write field I2C_CSR_BUS_BUSY at 0x216 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrBusBusy(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_BUS_BUSY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrBusBusy(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_SRW_READ at 0x216 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrSrwRead() const =0 ;

    /**
     * Write field I2C_CSR_SRW_READ at 0x216 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrSrwRead(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_SRW_READ at 0x216 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrSrwRead() const =0 ;

    /**
     * Write field I2C_CSR_SRW_READ at 0x216 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrSrwRead(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_SRW_READ in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrSrwRead(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_TX_FIFO_FULL at 0x216 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrTxFifoFull() const =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_FULL at 0x216 bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrTxFifoFull(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_TX_FIFO_FULL at 0x216 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrTxFifoFull() const =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_FULL at 0x216 bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrTxFifoFull(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_FULL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrTxFifoFull(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_RX_FIFO_FULL at 0x216 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrRxFifoFull() const =0 ;

    /**
     * Write field I2C_CSR_RX_FIFO_FULL at 0x216 bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrRxFifoFull(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_RX_FIFO_FULL at 0x216 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrRxFifoFull() const =0 ;

    /**
     * Write field I2C_CSR_RX_FIFO_FULL at 0x216 bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrRxFifoFull(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_RX_FIFO_FULL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrRxFifoFull(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_RX_FIFO_EMPTY at 0x216 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrRxFifoEmpty() const =0 ;

    /**
     * Write field I2C_CSR_RX_FIFO_EMPTY at 0x216 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrRxFifoEmpty(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_RX_FIFO_EMPTY at 0x216 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrRxFifoEmpty() const =0 ;

    /**
     * Write field I2C_CSR_RX_FIFO_EMPTY at 0x216 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrRxFifoEmpty(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_RX_FIFO_EMPTY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrRxFifoEmpty(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_CSR_TX_FIFO_EMPTY at 0x216 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrTxFifoEmpty() const =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_EMPTY at 0x216 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrTxFifoEmpty(FpgaVal value) =0 ;

    /**
     * Read field I2C_CSR_TX_FIFO_EMPTY at 0x216 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrTxFifoEmpty() const =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_EMPTY at 0x216 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrTxFifoEmpty(FpgaVal value) =0 ;

    /**
     * Write field I2C_CSR_TX_FIFO_EMPTY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cCsrTxFifoEmpty(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_TX_FIFO_WRITE at 0x218 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_i2cTxFifoWrite() const =0 ;

    /**
     * Write field I2C_TX_FIFO_WRITE at 0x218 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cTxFifoWrite(FpgaVal value) =0 ;

    /**
     * Read field I2C_TX_FIFO_WRITE at 0x218 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cTxFifoWrite() const =0 ;

    /**
     * Write field I2C_TX_FIFO_WRITE at 0x218 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cTxFifoWrite(FpgaVal value) =0 ;

    /**
     * Write field I2C_TX_FIFO_WRITE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cTxFifoWrite(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_TX_FIFO_READ at 0x218 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_i2cTxFifoRead() const =0 ;

    /**
     * Write field I2C_TX_FIFO_READ at 0x218 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cTxFifoRead(FpgaVal value) =0 ;

    /**
     * Read field I2C_TX_FIFO_READ at 0x218 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cTxFifoRead() const =0 ;

    /**
     * Write field I2C_TX_FIFO_READ at 0x218 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cTxFifoRead(FpgaVal value) =0 ;

    /**
     * Write field I2C_TX_FIFO_READ in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cTxFifoRead(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_RX_FIFO_READ at 0x21a bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_i2cRxFifoRead() const =0 ;

    /**
     * Write field I2C_RX_FIFO_READ at 0x21a bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cRxFifoRead(FpgaVal value) =0 ;

    /**
     * Read field I2C_RX_FIFO_READ at 0x21a bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cRxFifoRead() const =0 ;

    /**
     * Write field I2C_RX_FIFO_READ at 0x21a bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cRxFifoRead(FpgaVal value) =0 ;

    /**
     * Write field I2C_RX_FIFO_READ in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cRxFifoRead(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_ADR at 0x21c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_i2cAdr() const =0 ;

    /**
     * Write field I2C_ADR at 0x21c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cAdr(FpgaVal value) =0 ;

    /**
     * Read field I2C_ADR at 0x21c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cAdr() const =0 ;

    /**
     * Write field I2C_ADR at 0x21c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cAdr(FpgaVal value) =0 ;

    /**
     * Write field I2C_ADR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cAdr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_FIFO_CSR_WRITE at 0x21e bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_i2cFifoCsrWrite() const =0 ;

    /**
     * Write field I2C_FIFO_CSR_WRITE at 0x21e bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cFifoCsrWrite(FpgaVal value) =0 ;

    /**
     * Read field I2C_FIFO_CSR_WRITE at 0x21e bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cFifoCsrWrite() const =0 ;

    /**
     * Write field I2C_FIFO_CSR_WRITE at 0x21e bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cFifoCsrWrite(FpgaVal value) =0 ;

    /**
     * Write field I2C_FIFO_CSR_WRITE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cFifoCsrWrite(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field I2C_RI_RESET at 0x220 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_i2cRiReset() const =0 ;

    /**
     * Write field I2C_RI_RESET at 0x220 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cRiReset(FpgaVal value) =0 ;

    /**
     * Read field I2C_RI_RESET at 0x220 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cRiReset() const =0 ;

    /**
     * Write field I2C_RI_RESET at 0x220 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cRiReset(FpgaVal value) =0 ;

    /**
     * Write field I2C_RI_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_i2cRiReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_SRX_ENABLE at 0x230 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_spiSrxEnable() const =0 ;

    /**
     * Write field SPI_SRX_ENABLE at 0x230 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spiSrxEnable(FpgaVal value) =0 ;

    /**
     * Read field SPI_SRX_ENABLE at 0x230 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spiSrxEnable() const =0 ;

    /**
     * Write field SPI_SRX_ENABLE at 0x230 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spiSrxEnable(FpgaVal value) =0 ;

    /**
     * Write field SPI_SRX_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spiSrxEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_SRX_DONE at 0x230 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_spiSrxDone() const =0 ;


    /**
     * Read field SPI_SRX_DONE at 0x230 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spiSrxDone() const =0 ;




    /**
     * Read field SPI_SRX_ADC_READ_LOC at 0x232 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_spiSrxAdcReadLoc() const =0 ;

    /**
     * Write field SPI_SRX_ADC_READ_LOC at 0x232 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spiSrxAdcReadLoc(FpgaVal value) =0 ;

    /**
     * Read field SPI_SRX_ADC_READ_LOC at 0x232 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spiSrxAdcReadLoc() const =0 ;

    /**
     * Write field SPI_SRX_ADC_READ_LOC at 0x232 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spiSrxAdcReadLoc(FpgaVal value) =0 ;

    /**
     * Write field SPI_SRX_ADC_READ_LOC in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spiSrxAdcReadLoc(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_SRX_ADC_READ_REQ at 0x232 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_spiSrxAdcReadReq() const =0 ;

    /**
     * Write field SPI_SRX_ADC_READ_REQ at 0x232 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spiSrxAdcReadReq(FpgaVal value) =0 ;

    /**
     * Read field SPI_SRX_ADC_READ_REQ at 0x232 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spiSrxAdcReadReq() const =0 ;

    /**
     * Write field SPI_SRX_ADC_READ_REQ at 0x232 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spiSrxAdcReadReq(FpgaVal value) =0 ;

    /**
     * Write field SPI_SRX_ADC_READ_REQ in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spiSrxAdcReadReq(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_SRX_ADC_READ_DONE at 0x232 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_spiSrxAdcReadDone() const =0 ;


    /**
     * Read field SPI_SRX_ADC_READ_DONE at 0x232 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spiSrxAdcReadDone() const =0 ;




    /**
     * Read field SPI_SRX_ADC_READ_DATA at 0x234 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_spiSrxAdcReadData() const =0 ;


    /**
     * Read field SPI_SRX_ADC_READ_DATA at 0x234 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spiSrxAdcReadData() const =0 ;




    /**
     * Read field SPI_PSU_ENABLE at 0x236 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_SPI_PSU_Enable() const =0 ;

    /**
     * Write field SPI_PSU_ENABLE at 0x236 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_SPI_PSU_Enable(FpgaVal value) =0 ;

    /**
     * Read field SPI_PSU_ENABLE at 0x236 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_SPI_PSU_Enable() const =0 ;

    /**
     * Write field SPI_PSU_ENABLE at 0x236 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_SPI_PSU_Enable(FpgaVal value) =0 ;

    /**
     * Write field SPI_PSU_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_SPI_PSU_Enable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_PSU_DONE at 0x236 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_SPI_PSU_Done() const =0 ;


    /**
     * Read field SPI_PSU_DONE at 0x236 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_SPI_PSU_Done() const =0 ;




    /**
     * Read field SPI_PSU_VOLTAGE at 0x236 bits [15..8]
     * \return field value
     */
    virtual const FpgaVal read_SPI_PSU_Voltage() const =0 ;

    /**
     * Write field SPI_PSU_VOLTAGE at 0x236 bits [15..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_SPI_PSU_Voltage(FpgaVal value) =0 ;

    /**
     * Read field SPI_PSU_VOLTAGE at 0x236 bits [15..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_SPI_PSU_Voltage() const =0 ;

    /**
     * Write field SPI_PSU_VOLTAGE at 0x236 bits [15..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_SPI_PSU_Voltage(FpgaVal value) =0 ;

    /**
     * Write field SPI_PSU_VOLTAGE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_SPI_PSU_Voltage(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI_PSU_CRC at 0x238 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_SPI_PSU_CRC() const =0 ;

    /**
     * Write field SPI_PSU_CRC at 0x238 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_SPI_PSU_CRC(FpgaVal value) =0 ;

    /**
     * Read field SPI_PSU_CRC at 0x238 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_SPI_PSU_CRC() const =0 ;

    /**
     * Write field SPI_PSU_CRC at 0x238 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_SPI_PSU_CRC(FpgaVal value) =0 ;

    /**
     * Write field SPI_PSU_CRC in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_SPI_PSU_CRC(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_CLK_INVERT at 0x300 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_spi1ClkInvert() const =0 ;

    /**
     * Write field SPI1_CLK_INVERT at 0x300 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1ClkInvert(FpgaVal value) =0 ;

    /**
     * Read field SPI1_CLK_INVERT at 0x300 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1ClkInvert() const =0 ;

    /**
     * Write field SPI1_CLK_INVERT at 0x300 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1ClkInvert(FpgaVal value) =0 ;

    /**
     * Write field SPI1_CLK_INVERT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1ClkInvert(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_WDATA_LEN at 0x300 bits [10..6]
     * \return field value
     */
    virtual const FpgaVal read_spi1WdataLen() const =0 ;

    /**
     * Write field SPI1_WDATA_LEN at 0x300 bits [10..6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1WdataLen(FpgaVal value) =0 ;

    /**
     * Read field SPI1_WDATA_LEN at 0x300 bits [10..6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1WdataLen() const =0 ;

    /**
     * Write field SPI1_WDATA_LEN at 0x300 bits [10..6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1WdataLen(FpgaVal value) =0 ;

    /**
     * Write field SPI1_WDATA_LEN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1WdataLen(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_RDATA_LEN at 0x300 bits [15..11]
     * \return field value
     */
    virtual const FpgaVal read_spi1RdataLen() const =0 ;

    /**
     * Write field SPI1_RDATA_LEN at 0x300 bits [15..11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1RdataLen(FpgaVal value) =0 ;

    /**
     * Read field SPI1_RDATA_LEN at 0x300 bits [15..11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1RdataLen() const =0 ;

    /**
     * Write field SPI1_RDATA_LEN at 0x300 bits [15..11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1RdataLen(FpgaVal value) =0 ;

    /**
     * Write field SPI1_RDATA_LEN in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1RdataLen(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_SELECT at 0x302 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1Select() const =0 ;

    /**
     * Write field SPI1_SELECT at 0x302 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1Select(FpgaVal value) =0 ;

    /**
     * Read field SPI1_SELECT at 0x302 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1Select() const =0 ;

    /**
     * Write field SPI1_SELECT at 0x302 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1Select(FpgaVal value) =0 ;

    /**
     * Write field SPI1_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1Select(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_WRITE_DATA_LO at 0x304 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1WriteDataLo() const =0 ;

    /**
     * Write field SPI1_WRITE_DATA_LO at 0x304 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1WriteDataLo(FpgaVal value) =0 ;

    /**
     * Read field SPI1_WRITE_DATA_LO at 0x304 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1WriteDataLo() const =0 ;

    /**
     * Write field SPI1_WRITE_DATA_LO at 0x304 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1WriteDataLo(FpgaVal value) =0 ;

    /**
     * Write field SPI1_WRITE_DATA_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1WriteDataLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_WRITE_DATA_HI at 0x306 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1WriteDataHi() const =0 ;

    /**
     * Write field SPI1_WRITE_DATA_HI at 0x306 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1WriteDataHi(FpgaVal value) =0 ;

    /**
     * Read field SPI1_WRITE_DATA_HI at 0x306 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1WriteDataHi() const =0 ;

    /**
     * Write field SPI1_WRITE_DATA_HI at 0x306 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1WriteDataHi(FpgaVal value) =0 ;

    /**
     * Write field SPI1_WRITE_DATA_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1WriteDataHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_READ_DATA_LO at 0x308 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1ReadDataLo() const =0 ;


    /**
     * Read field SPI1_READ_DATA_LO at 0x308 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1ReadDataLo() const =0 ;




    /**
     * Read field SPI1_READ_DATA_HI at 0x30a bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1ReadDataHi() const =0 ;


    /**
     * Read field SPI1_READ_DATA_HI at 0x30a bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1ReadDataHi() const =0 ;




    /**
     * Read field SPI1_CLK_DIV at 0x30c bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1ClkDiv() const =0 ;

    /**
     * Write field SPI1_CLK_DIV at 0x30c bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1ClkDiv(FpgaVal value) =0 ;

    /**
     * Read field SPI1_CLK_DIV at 0x30c bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1ClkDiv() const =0 ;

    /**
     * Write field SPI1_CLK_DIV at 0x30c bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1ClkDiv(FpgaVal value) =0 ;

    /**
     * Write field SPI1_CLK_DIV in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1ClkDiv(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_CLK_PHASE1 at 0x30c bits [14]
     * \return field value
     */
    virtual const FpgaVal read_spi1ClkPhase1() const =0 ;

    /**
     * Write field SPI1_CLK_PHASE1 at 0x30c bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1ClkPhase1(FpgaVal value) =0 ;

    /**
     * Read field SPI1_CLK_PHASE1 at 0x30c bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1ClkPhase1() const =0 ;

    /**
     * Write field SPI1_CLK_PHASE1 at 0x30c bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1ClkPhase1(FpgaVal value) =0 ;

    /**
     * Write field SPI1_CLK_PHASE1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1ClkPhase1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI1_KEEP_ENABLE at 0x30c bits [15]
     * \return field value
     */
    virtual const FpgaVal read_spi1KeepEnable() const =0 ;

    /**
     * Write field SPI1_KEEP_ENABLE at 0x30c bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1KeepEnable(FpgaVal value) =0 ;

    /**
     * Read field SPI1_KEEP_ENABLE at 0x30c bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1KeepEnable() const =0 ;

    /**
     * Write field SPI1_KEEP_ENABLE at 0x30c bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1KeepEnable(FpgaVal value) =0 ;

    /**
     * Write field SPI1_KEEP_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi1KeepEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_CLK_DIV at 0x30e bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0ClkDiv() const =0 ;

    /**
     * Write field SPI0_CLK_DIV at 0x30e bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0ClkDiv(FpgaVal value) =0 ;

    /**
     * Read field SPI0_CLK_DIV at 0x30e bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0ClkDiv() const =0 ;

    /**
     * Write field SPI0_CLK_DIV at 0x30e bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0ClkDiv(FpgaVal value) =0 ;

    /**
     * Write field SPI0_CLK_DIV in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0ClkDiv(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_REQUEST at 0x30e bits [8]
     * \return field value
     */
    virtual const FpgaVal read_spi0Request() const =0 ;

    /**
     * Write field SPI0_REQUEST at 0x30e bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0Request(FpgaVal value) =0 ;

    /**
     * Read field SPI0_REQUEST at 0x30e bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0Request() const =0 ;

    /**
     * Write field SPI0_REQUEST at 0x30e bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0Request(FpgaVal value) =0 ;

    /**
     * Write field SPI0_REQUEST in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0Request(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_CLK_PHASE1 at 0x30e bits [14]
     * \return field value
     */
    virtual const FpgaVal read_spi0ClkPhase1() const =0 ;

    /**
     * Write field SPI0_CLK_PHASE1 at 0x30e bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0ClkPhase1(FpgaVal value) =0 ;

    /**
     * Read field SPI0_CLK_PHASE1 at 0x30e bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0ClkPhase1() const =0 ;

    /**
     * Write field SPI0_CLK_PHASE1 at 0x30e bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0ClkPhase1(FpgaVal value) =0 ;

    /**
     * Write field SPI0_CLK_PHASE1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0ClkPhase1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SPI0_KEEP_ENABLE at 0x30e bits [15]
     * \return field value
     */
    virtual const FpgaVal read_spi0KeepEnable() const =0 ;

    /**
     * Write field SPI0_KEEP_ENABLE at 0x30e bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0KeepEnable(FpgaVal value) =0 ;

    /**
     * Read field SPI0_KEEP_ENABLE at 0x30e bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0KeepEnable() const =0 ;

    /**
     * Write field SPI0_KEEP_ENABLE at 0x30e bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0KeepEnable(FpgaVal value) =0 ;

    /**
     * Write field SPI0_KEEP_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_spi0KeepEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DUC_CFR_ENABLE at 0x400 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_ducCfrEnable() const =0 ;

    /**
     * Write field DUC_CFR_ENABLE at 0x400 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ducCfrEnable(FpgaVal value) =0 ;

    /**
     * Read field DUC_CFR_ENABLE at 0x400 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ducCfrEnable() const =0 ;

    /**
     * Write field DUC_CFR_ENABLE at 0x400 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ducCfrEnable(FpgaVal value) =0 ;

    /**
     * Write field DUC_CFR_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ducCfrEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_OUTPUT_ENABLE at 0x400 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_dacOutputEnable() const =0 ;

    /**
     * Write field DAC_OUTPUT_ENABLE at 0x400 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacOutputEnable(FpgaVal value) =0 ;

    /**
     * Read field DAC_OUTPUT_ENABLE at 0x400 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacOutputEnable() const =0 ;

    /**
     * Write field DAC_OUTPUT_ENABLE at 0x400 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacOutputEnable(FpgaVal value) =0 ;

    /**
     * Write field DAC_OUTPUT_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacOutputEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_INPUT_SEL at 0x400 bits [6..5]
     * \return field value
     */
    virtual const FpgaVal read_dacInputSel() const =0 ;

    /**
     * Write field DAC_INPUT_SEL at 0x400 bits [6..5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacInputSel(FpgaVal value) =0 ;

    /**
     * Read field DAC_INPUT_SEL at 0x400 bits [6..5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacInputSel() const =0 ;

    /**
     * Write field DAC_INPUT_SEL at 0x400 bits [6..5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacInputSel(FpgaVal value) =0 ;

    /**
     * Write field DAC_INPUT_SEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacInputSel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_INPUT_USE_ANT at 0x400 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_dacInputUseAnt() const =0 ;

    /**
     * Write field DAC_INPUT_USE_ANT at 0x400 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacInputUseAnt(FpgaVal value) =0 ;

    /**
     * Read field DAC_INPUT_USE_ANT at 0x400 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacInputUseAnt() const =0 ;

    /**
     * Write field DAC_INPUT_USE_ANT at 0x400 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacInputUseAnt(FpgaVal value) =0 ;

    /**
     * Write field DAC_INPUT_USE_ANT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacInputUseAnt(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BB_BYPASS_OVERLOAD_PROT at 0x400 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_bbBypassOverloadProt() const =0 ;

    /**
     * Write field BB_BYPASS_OVERLOAD_PROT at 0x400 bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bbBypassOverloadProt(FpgaVal value) =0 ;

    /**
     * Read field BB_BYPASS_OVERLOAD_PROT at 0x400 bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bbBypassOverloadProt() const =0 ;

    /**
     * Write field BB_BYPASS_OVERLOAD_PROT at 0x400 bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bbBypassOverloadProt(FpgaVal value) =0 ;

    /**
     * Write field BB_BYPASS_OVERLOAD_PROT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bbBypassOverloadProt(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DPD_BYPASS at 0x400 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_dpdBypass() const =0 ;

    /**
     * Write field DPD_BYPASS at 0x400 bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dpdBypass(FpgaVal value) =0 ;

    /**
     * Read field DPD_BYPASS at 0x400 bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dpdBypass() const =0 ;

    /**
     * Write field DPD_BYPASS at 0x400 bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dpdBypass(FpgaVal value) =0 ;

    /**
     * Write field DPD_BYPASS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dpdBypass(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DUC_FINAL_CFR_BYPASS at 0x400 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_ducFinalCfrBypass() const =0 ;

    /**
     * Write field DUC_FINAL_CFR_BYPASS at 0x400 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ducFinalCfrBypass(FpgaVal value) =0 ;

    /**
     * Read field DUC_FINAL_CFR_BYPASS at 0x400 bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ducFinalCfrBypass() const =0 ;

    /**
     * Write field DUC_FINAL_CFR_BYPASS at 0x400 bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ducFinalCfrBypass(FpgaVal value) =0 ;

    /**
     * Write field DUC_FINAL_CFR_BYPASS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ducFinalCfrBypass(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MEASUREMENT_FWD_REV_SELECT at 0x402 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_measurementFwdRevSelect() const =0 ;

    /**
     * Write field MEASUREMENT_FWD_REV_SELECT at 0x402 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_measurementFwdRevSelect(FpgaVal value) =0 ;

    /**
     * Read field MEASUREMENT_FWD_REV_SELECT at 0x402 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_measurementFwdRevSelect() const =0 ;

    /**
     * Write field MEASUREMENT_FWD_REV_SELECT at 0x402 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_measurementFwdRevSelect(FpgaVal value) =0 ;

    /**
     * Write field MEASUREMENT_FWD_REV_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_measurementFwdRevSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MEASUREMENT_CHANNEL_SELECT at 0x402 bits [2..1]
     * \return field value
     */
    virtual const FpgaVal read_measurementChannelSelect() const =0 ;

    /**
     * Write field MEASUREMENT_CHANNEL_SELECT at 0x402 bits [2..1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_measurementChannelSelect(FpgaVal value) =0 ;

    /**
     * Read field MEASUREMENT_CHANNEL_SELECT at 0x402 bits [2..1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_measurementChannelSelect() const =0 ;

    /**
     * Write field MEASUREMENT_CHANNEL_SELECT at 0x402 bits [2..1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_measurementChannelSelect(FpgaVal value) =0 ;

    /**
     * Write field MEASUREMENT_CHANNEL_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_measurementChannelSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MEASUREMENT_START at 0x402 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_measurementStart() const =0 ;

    /**
     * Write field MEASUREMENT_START at 0x402 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_measurementStart(FpgaVal value) =0 ;

    /**
     * Read field MEASUREMENT_START at 0x402 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_measurementStart() const =0 ;

    /**
     * Write field MEASUREMENT_START at 0x402 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_measurementStart(FpgaVal value) =0 ;

    /**
     * Write field MEASUREMENT_START in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_measurementStart(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MEASUREMENT_DONE at 0x402 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_measurementDone() const =0 ;


    /**
     * Read field MEASUREMENT_DONE at 0x402 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_measurementDone() const =0 ;




    /**
     * Read field MIMO_PRIMMARY_CHAN_SEL at 0x402 bits [9..8]
     * \return field value
     */
    virtual const FpgaVal read_mimoPrimmaryChanSel() const =0 ;

    /**
     * Write field MIMO_PRIMMARY_CHAN_SEL at 0x402 bits [9..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_mimoPrimmaryChanSel(FpgaVal value) =0 ;

    /**
     * Read field MIMO_PRIMMARY_CHAN_SEL at 0x402 bits [9..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mimoPrimmaryChanSel() const =0 ;

    /**
     * Write field MIMO_PRIMMARY_CHAN_SEL at 0x402 bits [9..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_mimoPrimmaryChanSel(FpgaVal value) =0 ;

    /**
     * Write field MIMO_PRIMMARY_CHAN_SEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_mimoPrimmaryChanSel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DOWNLINK_POWER_CHANNEL1 at 0x404 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_downlinkPowerChannel1() const =0 ;


    /**
     * Read field DOWNLINK_POWER_CHANNEL1 at 0x404 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_downlinkPowerChannel1() const =0 ;




    /**
     * Read field RSSI_IQ_STREAM_SELECT at 0x408 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiIqStreamSelect() const =0 ;

    /**
     * Write field RSSI_IQ_STREAM_SELECT at 0x408 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rssiIqStreamSelect(FpgaVal value) =0 ;

    /**
     * Read field RSSI_IQ_STREAM_SELECT at 0x408 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiIqStreamSelect() const =0 ;

    /**
     * Write field RSSI_IQ_STREAM_SELECT at 0x408 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rssiIqStreamSelect(FpgaVal value) =0 ;

    /**
     * Write field RSSI_IQ_STREAM_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rssiIqStreamSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RSSI_CHANNEL_SELECT at 0x40a bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiChannelSelect() const =0 ;

    /**
     * Write field RSSI_CHANNEL_SELECT at 0x40a bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rssiChannelSelect(FpgaVal value) =0 ;

    /**
     * Read field RSSI_CHANNEL_SELECT at 0x40a bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiChannelSelect() const =0 ;

    /**
     * Write field RSSI_CHANNEL_SELECT at 0x40a bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rssiChannelSelect(FpgaVal value) =0 ;

    /**
     * Write field RSSI_CHANNEL_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rssiChannelSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RSSI_START at 0x40a bits [2]
     * \return field value
     */
    virtual const FpgaVal read_rssiStart() const =0 ;

    /**
     * Write field RSSI_START at 0x40a bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rssiStart(FpgaVal value) =0 ;

    /**
     * Read field RSSI_START at 0x40a bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiStart() const =0 ;

    /**
     * Write field RSSI_START at 0x40a bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rssiStart(FpgaVal value) =0 ;

    /**
     * Write field RSSI_START in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rssiStart(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RSSI_DONE at 0x40a bits [3]
     * \return field value
     */
    virtual const FpgaVal read_rssiDone() const =0 ;


    /**
     * Read field RSSI_DONE at 0x40a bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiDone() const =0 ;




    /**
     * Read field RSSI_RX_FE_ATTEN at 0x40a bits [6..4]
     * \return field value
     */
    virtual const FpgaVal read_rssiRxFeAtten() const =0 ;


    /**
     * Read field RSSI_RX_FE_ATTEN at 0x40a bits [6..4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiRxFeAtten() const =0 ;




    /**
     * Read field RSSI_BEAMFORMER_MEASUREMENT_ENABLE at 0x40a bits [12]
     * \return field value
     */
    virtual const FpgaVal read_rssiBeamformerMeasurementEnable() const =0 ;

    /**
     * Write field RSSI_BEAMFORMER_MEASUREMENT_ENABLE at 0x40a bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rssiBeamformerMeasurementEnable(FpgaVal value) =0 ;

    /**
     * Read field RSSI_BEAMFORMER_MEASUREMENT_ENABLE at 0x40a bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiBeamformerMeasurementEnable() const =0 ;

    /**
     * Write field RSSI_BEAMFORMER_MEASUREMENT_ENABLE at 0x40a bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rssiBeamformerMeasurementEnable(FpgaVal value) =0 ;

    /**
     * Write field RSSI_BEAMFORMER_MEASUREMENT_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rssiBeamformerMeasurementEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RSSI_NARROW at 0x40a bits [13]
     * \return field value
     */
    virtual const FpgaVal read_rssiNarrow() const =0 ;

    /**
     * Write field RSSI_NARROW at 0x40a bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rssiNarrow(FpgaVal value) =0 ;

    /**
     * Read field RSSI_NARROW at 0x40a bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiNarrow() const =0 ;

    /**
     * Write field RSSI_NARROW at 0x40a bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rssiNarrow(FpgaVal value) =0 ;

    /**
     * Write field RSSI_NARROW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rssiNarrow(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RSSI_CAL_ADC_MEASUREMENT_ENABLE at 0x40a bits [15]
     * \return field value
     */
    virtual const FpgaVal read_rssiCalAdcMeasurementEnable() const =0 ;

    /**
     * Write field RSSI_CAL_ADC_MEASUREMENT_ENABLE at 0x40a bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rssiCalAdcMeasurementEnable(FpgaVal value) =0 ;

    /**
     * Read field RSSI_CAL_ADC_MEASUREMENT_ENABLE at 0x40a bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiCalAdcMeasurementEnable() const =0 ;

    /**
     * Write field RSSI_CAL_ADC_MEASUREMENT_ENABLE at 0x40a bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rssiCalAdcMeasurementEnable(FpgaVal value) =0 ;

    /**
     * Write field RSSI_CAL_ADC_MEASUREMENT_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rssiCalAdcMeasurementEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RSSI_ADC_RESULT_LO at 0x40c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiAdcResultLo() const =0 ;


    /**
     * Read field RSSI_ADC_RESULT_LO at 0x40c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiAdcResultLo() const =0 ;




    /**
     * Read field RX_FE_NUM_LEVELS at 0x410 bits [2..0]
     * \return field value
     */
    virtual const FpgaVal read_rxFeNumLevels() const =0 ;


    /**
     * Read field RX_FE_NUM_LEVELS at 0x410 bits [2..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeNumLevels() const =0 ;




    /**
     * Read field RSSI_VERSION at 0x412 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiVersion() const =0 ;


    /**
     * Read field RSSI_VERSION at 0x412 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiVersion() const =0 ;




    /**
     * Read field RX_FE_ATTEN_FRAMES at 0x414 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_rxFeAttenFrames() const =0 ;

    /**
     * Write field RX_FE_ATTEN_FRAMES at 0x414 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxFeAttenFrames(FpgaVal value) =0 ;

    /**
     * Read field RX_FE_ATTEN_FRAMES at 0x414 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeAttenFrames() const =0 ;

    /**
     * Write field RX_FE_ATTEN_FRAMES at 0x414 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxFeAttenFrames(FpgaVal value) =0 ;

    /**
     * Write field RX_FE_ATTEN_FRAMES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxFeAttenFrames(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RSSI_ADC_RESULT_HI at 0x416 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiAdcResultHi() const =0 ;


    /**
     * Read field RSSI_ADC_RESULT_HI at 0x416 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiAdcResultHi() const =0 ;




    /**
     * Read field RSSI_ADC_PEAK at 0x418 bits [11..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiAdcPeak() const =0 ;


    /**
     * Read field RSSI_ADC_PEAK at 0x418 bits [11..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiAdcPeak() const =0 ;




    /**
     * Read field RSSI_DUTY_CYCLE_COUNT_LO at 0x41c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiDutyCycleCountLo() const =0 ;


    /**
     * Read field RSSI_DUTY_CYCLE_COUNT_LO at 0x41c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiDutyCycleCountLo() const =0 ;




    /**
     * Read field RSSI_DUTY_CYCLE_COUNT_HI at 0x41e bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiDutyCycleCountHi() const =0 ;


    /**
     * Read field RSSI_DUTY_CYCLE_COUNT_HI at 0x41e bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiDutyCycleCountHi() const =0 ;




    /**
     * Read field PLAYBACK_TONE_ENABLE at 0x420 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_playbackToneEnable() const =0 ;

    /**
     * Write field PLAYBACK_TONE_ENABLE at 0x420 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_playbackToneEnable(FpgaVal value) =0 ;

    /**
     * Read field PLAYBACK_TONE_ENABLE at 0x420 bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_playbackToneEnable() const =0 ;

    /**
     * Write field PLAYBACK_TONE_ENABLE at 0x420 bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_playbackToneEnable(FpgaVal value) =0 ;

    /**
     * Write field PLAYBACK_TONE_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_playbackToneEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PLAYBACK_TONE_SWEEP_ENABLE at 0x420 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_playbackToneSweepEnable() const =0 ;

    /**
     * Write field PLAYBACK_TONE_SWEEP_ENABLE at 0x420 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_playbackToneSweepEnable(FpgaVal value) =0 ;

    /**
     * Read field PLAYBACK_TONE_SWEEP_ENABLE at 0x420 bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_playbackToneSweepEnable() const =0 ;

    /**
     * Write field PLAYBACK_TONE_SWEEP_ENABLE at 0x420 bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_playbackToneSweepEnable(FpgaVal value) =0 ;

    /**
     * Write field PLAYBACK_TONE_SWEEP_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_playbackToneSweepEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DOWNLINK_POWER_CHANNEL2 at 0x44a bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_downlinkPowerChannel2() const =0 ;


    /**
     * Read field DOWNLINK_POWER_CHANNEL2 at 0x44a bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_downlinkPowerChannel2() const =0 ;




    /**
     * Read field BB_PD_TC at 0x44c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_bbPdTc() const =0 ;

    /**
     * Write field BB_PD_TC at 0x44c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bbPdTc(FpgaVal value) =0 ;

    /**
     * Read field BB_PD_TC at 0x44c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bbPdTc() const =0 ;

    /**
     * Write field BB_PD_TC at 0x44c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bbPdTc(FpgaVal value) =0 ;

    /**
     * Write field BB_PD_TC in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bbPdTc(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BB_PD_TC_DECAY at 0x44e bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_bbPdTcDecay() const =0 ;

    /**
     * Write field BB_PD_TC_DECAY at 0x44e bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bbPdTcDecay(FpgaVal value) =0 ;

    /**
     * Read field BB_PD_TC_DECAY at 0x44e bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bbPdTcDecay() const =0 ;

    /**
     * Write field BB_PD_TC_DECAY at 0x44e bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bbPdTcDecay(FpgaVal value) =0 ;

    /**
     * Write field BB_PD_TC_DECAY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bbPdTcDecay(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DOWNLINK_POWER_CHANNEL3 at 0x450 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_downlinkPowerChannel3() const =0 ;


    /**
     * Read field DOWNLINK_POWER_CHANNEL3 at 0x450 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_downlinkPowerChannel3() const =0 ;




    /**
     * Read field DOWNLINK_POWER_CHANNEL4 at 0x452 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_downlinkPowerChannel4() const =0 ;


    /**
     * Read field DOWNLINK_POWER_CHANNEL4 at 0x452 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_downlinkPowerChannel4() const =0 ;




    /**
     * Read field BB_PD_BETA_ATTACK at 0x454 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_bbPdBetaAttack() const =0 ;

    /**
     * Write field BB_PD_BETA_ATTACK at 0x454 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bbPdBetaAttack(FpgaVal value) =0 ;

    /**
     * Read field BB_PD_BETA_ATTACK at 0x454 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bbPdBetaAttack() const =0 ;

    /**
     * Write field BB_PD_BETA_ATTACK at 0x454 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bbPdBetaAttack(FpgaVal value) =0 ;

    /**
     * Write field BB_PD_BETA_ATTACK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bbPdBetaAttack(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field OLP_NOM_THRES at 0x460 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_olpNomThres() const =0 ;

    /**
     * Write field OLP_NOM_THRES at 0x460 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_olpNomThres(FpgaVal value) =0 ;

    /**
     * Read field OLP_NOM_THRES at 0x460 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_olpNomThres() const =0 ;

    /**
     * Write field OLP_NOM_THRES at 0x460 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_olpNomThres(FpgaVal value) =0 ;

    /**
     * Write field OLP_NOM_THRES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_olpNomThres(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field OL_FAST_THRES at 0x462 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_olFastThres() const =0 ;

    /**
     * Write field OL_FAST_THRES at 0x462 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_olFastThres(FpgaVal value) =0 ;

    /**
     * Read field OL_FAST_THRES at 0x462 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_olFastThres() const =0 ;

    /**
     * Write field OL_FAST_THRES at 0x462 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_olFastThres(FpgaVal value) =0 ;

    /**
     * Write field OL_FAST_THRES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_olFastThres(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field OL_SLOW_THRES at 0x464 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_olSlowThres() const =0 ;

    /**
     * Write field OL_SLOW_THRES at 0x464 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_olSlowThres(FpgaVal value) =0 ;

    /**
     * Read field OL_SLOW_THRES at 0x464 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_olSlowThres() const =0 ;

    /**
     * Write field OL_SLOW_THRES at 0x464 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_olSlowThres(FpgaVal value) =0 ;

    /**
     * Write field OL_SLOW_THRES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_olSlowThres(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LOW_PWR_ALARM_THRES at 0x466 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_lowPwrAlarmThres() const =0 ;

    /**
     * Write field LOW_PWR_ALARM_THRES at 0x466 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_lowPwrAlarmThres(FpgaVal value) =0 ;

    /**
     * Read field LOW_PWR_ALARM_THRES at 0x466 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_lowPwrAlarmThres() const =0 ;

    /**
     * Write field LOW_PWR_ALARM_THRES at 0x466 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_lowPwrAlarmThres(FpgaVal value) =0 ;

    /**
     * Write field LOW_PWR_ALARM_THRES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_lowPwrAlarmThres(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field OVER_PWR_ALARM_THRES at 0x468 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_overPwrAlarmThres() const =0 ;

    /**
     * Write field OVER_PWR_ALARM_THRES at 0x468 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_overPwrAlarmThres(FpgaVal value) =0 ;

    /**
     * Read field OVER_PWR_ALARM_THRES at 0x468 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_overPwrAlarmThres() const =0 ;

    /**
     * Write field OVER_PWR_ALARM_THRES at 0x468 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_overPwrAlarmThres(FpgaVal value) =0 ;

    /**
     * Write field OVER_PWR_ALARM_THRES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_overPwrAlarmThres(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ADC1_OVR_ALARM at 0x470 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_adc1OvrAlarm() const =0 ;

    /**
     * Write field ADC1_OVR_ALARM at 0x470 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_adc1OvrAlarm(FpgaVal value) =0 ;

    /**
     * Read field ADC1_OVR_ALARM at 0x470 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_adc1OvrAlarm() const =0 ;

    /**
     * Write field ADC1_OVR_ALARM at 0x470 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_adc1OvrAlarm(FpgaVal value) =0 ;

    /**
     * Write field ADC1_OVR_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_adc1OvrAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ADC2_OVR_ALARM at 0x470 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_adc2OvrAlarm() const =0 ;

    /**
     * Write field ADC2_OVR_ALARM at 0x470 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_adc2OvrAlarm(FpgaVal value) =0 ;

    /**
     * Read field ADC2_OVR_ALARM at 0x470 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_adc2OvrAlarm() const =0 ;

    /**
     * Write field ADC2_OVR_ALARM at 0x470 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_adc2OvrAlarm(FpgaVal value) =0 ;

    /**
     * Write field ADC2_OVR_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_adc2OvrAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ADC3_OVR_ALARM at 0x470 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_adc3OvrAlarm() const =0 ;

    /**
     * Write field ADC3_OVR_ALARM at 0x470 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_adc3OvrAlarm(FpgaVal value) =0 ;

    /**
     * Read field ADC3_OVR_ALARM at 0x470 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_adc3OvrAlarm() const =0 ;

    /**
     * Write field ADC3_OVR_ALARM at 0x470 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_adc3OvrAlarm(FpgaVal value) =0 ;

    /**
     * Write field ADC3_OVR_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_adc3OvrAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ADC4_OVR_ALARM at 0x470 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_adc4OvrAlarm() const =0 ;

    /**
     * Write field ADC4_OVR_ALARM at 0x470 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_adc4OvrAlarm(FpgaVal value) =0 ;

    /**
     * Read field ADC4_OVR_ALARM at 0x470 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_adc4OvrAlarm() const =0 ;

    /**
     * Write field ADC4_OVR_ALARM at 0x470 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_adc4OvrAlarm(FpgaVal value) =0 ;

    /**
     * Write field ADC4_OVR_ALARM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_adc4OvrAlarm(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_TEST_MODE at 0x480 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_dacTestMode() const =0 ;

    /**
     * Write field DAC_TEST_MODE at 0x480 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacTestMode(FpgaVal value) =0 ;

    /**
     * Read field DAC_TEST_MODE at 0x480 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacTestMode() const =0 ;

    /**
     * Write field DAC_TEST_MODE at 0x480 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacTestMode(FpgaVal value) =0 ;

    /**
     * Write field DAC_TEST_MODE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacTestMode(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_ANT_TEST_MODE at 0x480 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_dacAntTestMode() const =0 ;

    /**
     * Write field DAC_ANT_TEST_MODE at 0x480 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacAntTestMode(FpgaVal value) =0 ;

    /**
     * Read field DAC_ANT_TEST_MODE at 0x480 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacAntTestMode() const =0 ;

    /**
     * Write field DAC_ANT_TEST_MODE at 0x480 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacAntTestMode(FpgaVal value) =0 ;

    /**
     * Write field DAC_ANT_TEST_MODE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacAntTestMode(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_CLKS_PER_SAMPLE at 0x480 bits [11..8]
     * \return field value
     */
    virtual const FpgaVal read_dacClksPerSample() const =0 ;

    /**
     * Write field DAC_CLKS_PER_SAMPLE at 0x480 bits [11..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacClksPerSample(FpgaVal value) =0 ;

    /**
     * Read field DAC_CLKS_PER_SAMPLE at 0x480 bits [11..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacClksPerSample() const =0 ;

    /**
     * Write field DAC_CLKS_PER_SAMPLE at 0x480 bits [11..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacClksPerSample(FpgaVal value) =0 ;

    /**
     * Write field DAC_CLKS_PER_SAMPLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacClksPerSample(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_SED_I0 at 0x482 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dacSedI0() const =0 ;

    /**
     * Write field DAC_SED_I0 at 0x482 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacSedI0(FpgaVal value) =0 ;

    /**
     * Read field DAC_SED_I0 at 0x482 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacSedI0() const =0 ;

    /**
     * Write field DAC_SED_I0 at 0x482 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacSedI0(FpgaVal value) =0 ;

    /**
     * Write field DAC_SED_I0 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacSedI0(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_SED_Q0 at 0x484 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dacSedQ0() const =0 ;

    /**
     * Write field DAC_SED_Q0 at 0x484 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacSedQ0(FpgaVal value) =0 ;

    /**
     * Read field DAC_SED_Q0 at 0x484 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacSedQ0() const =0 ;

    /**
     * Write field DAC_SED_Q0 at 0x484 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacSedQ0(FpgaVal value) =0 ;

    /**
     * Write field DAC_SED_Q0 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacSedQ0(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_SED_I1 at 0x486 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dacSedI1() const =0 ;

    /**
     * Write field DAC_SED_I1 at 0x486 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacSedI1(FpgaVal value) =0 ;

    /**
     * Read field DAC_SED_I1 at 0x486 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacSedI1() const =0 ;

    /**
     * Write field DAC_SED_I1 at 0x486 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacSedI1(FpgaVal value) =0 ;

    /**
     * Write field DAC_SED_I1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacSedI1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_SED_Q1 at 0x488 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dacSedQ1() const =0 ;

    /**
     * Write field DAC_SED_Q1 at 0x488 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacSedQ1(FpgaVal value) =0 ;

    /**
     * Read field DAC_SED_Q1 at 0x488 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacSedQ1() const =0 ;

    /**
     * Write field DAC_SED_Q1 at 0x488 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacSedQ1(FpgaVal value) =0 ;

    /**
     * Write field DAC_SED_Q1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacSedQ1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAC_IQ_SWAP at 0x48a bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_dacIqSwap() const =0 ;

    /**
     * Write field DAC_IQ_SWAP at 0x48a bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dacIqSwap(FpgaVal value) =0 ;

    /**
     * Read field DAC_IQ_SWAP at 0x48a bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dacIqSwap() const =0 ;

    /**
     * Write field DAC_IQ_SWAP at 0x48a bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dacIqSwap(FpgaVal value) =0 ;

    /**
     * Write field DAC_IQ_SWAP in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dacIqSwap(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_ATTEN_UPDATE at 0x490 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_txAttenUpdate() const =0 ;

    /**
     * Write field TX_ATTEN_UPDATE at 0x490 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txAttenUpdate(FpgaVal value) =0 ;

    /**
     * Read field TX_ATTEN_UPDATE at 0x490 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txAttenUpdate() const =0 ;

    /**
     * Write field TX_ATTEN_UPDATE at 0x490 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txAttenUpdate(FpgaVal value) =0 ;

    /**
     * Write field TX_ATTEN_UPDATE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txAttenUpdate(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_ATTEN_MODE at 0x490 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_txAttenMode() const =0 ;

    /**
     * Write field TX_ATTEN_MODE at 0x490 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txAttenMode(FpgaVal value) =0 ;

    /**
     * Read field TX_ATTEN_MODE at 0x490 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txAttenMode() const =0 ;

    /**
     * Write field TX_ATTEN_MODE at 0x490 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txAttenMode(FpgaVal value) =0 ;

    /**
     * Write field TX_ATTEN_MODE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txAttenMode(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_ATTEN_DONE at 0x490 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_txAttenDone() const =0 ;


    /**
     * Read field TX_ATTEN_DONE at 0x490 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txAttenDone() const =0 ;




    /**
     * Read field RX_ATTEN_UPDATE at 0x490 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_rxAttenUpdate() const =0 ;

    /**
     * Write field RX_ATTEN_UPDATE at 0x490 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxAttenUpdate(FpgaVal value) =0 ;

    /**
     * Read field RX_ATTEN_UPDATE at 0x490 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxAttenUpdate() const =0 ;

    /**
     * Write field RX_ATTEN_UPDATE at 0x490 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxAttenUpdate(FpgaVal value) =0 ;

    /**
     * Write field RX_ATTEN_UPDATE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxAttenUpdate(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_ATTEN_MODE at 0x490 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_rxAttenMode() const =0 ;

    /**
     * Write field RX_ATTEN_MODE at 0x490 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxAttenMode(FpgaVal value) =0 ;

    /**
     * Read field RX_ATTEN_MODE at 0x490 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxAttenMode() const =0 ;

    /**
     * Write field RX_ATTEN_MODE at 0x490 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxAttenMode(FpgaVal value) =0 ;

    /**
     * Write field RX_ATTEN_MODE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxAttenMode(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_ATTEN_DONE at 0x490 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_rxAttenDone() const =0 ;


    /**
     * Read field RX_ATTEN_DONE at 0x490 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxAttenDone() const =0 ;




    /**
     * Read field RX_FE_ATTEN_UPDATE at 0x490 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_rxFeAttenUpdate() const =0 ;

    /**
     * Write field RX_FE_ATTEN_UPDATE at 0x490 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxFeAttenUpdate(FpgaVal value) =0 ;

    /**
     * Read field RX_FE_ATTEN_UPDATE at 0x490 bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeAttenUpdate() const =0 ;

    /**
     * Write field RX_FE_ATTEN_UPDATE at 0x490 bits [7]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxFeAttenUpdate(FpgaVal value) =0 ;

    /**
     * Write field RX_FE_ATTEN_UPDATE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxFeAttenUpdate(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_FE_THRESHOLD_DET_CLR at 0x490 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_rxFeThresholdDetClr() const =0 ;

    /**
     * Write field RX_FE_THRESHOLD_DET_CLR at 0x490 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxFeThresholdDetClr(FpgaVal value) =0 ;

    /**
     * Read field RX_FE_THRESHOLD_DET_CLR at 0x490 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeThresholdDetClr() const =0 ;

    /**
     * Write field RX_FE_THRESHOLD_DET_CLR at 0x490 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxFeThresholdDetClr(FpgaVal value) =0 ;

    /**
     * Write field RX_FE_THRESHOLD_DET_CLR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxFeThresholdDetClr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CAL_RX_ATTENUATION at 0x4a4 bits [5..0]
     * \return field value
     */
    virtual const FpgaVal read_calRxAttenuation() const =0 ;

    /**
     * Write field CAL_RX_ATTENUATION at 0x4a4 bits [5..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_calRxAttenuation(FpgaVal value) =0 ;

    /**
     * Read field CAL_RX_ATTENUATION at 0x4a4 bits [5..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calRxAttenuation() const =0 ;

    /**
     * Write field CAL_RX_ATTENUATION at 0x4a4 bits [5..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_calRxAttenuation(FpgaVal value) =0 ;

    /**
     * Write field CAL_RX_ATTENUATION in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_calRxAttenuation(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FORCE_DPD_OVERRIDE at 0x4a4 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_forceDpdOverride() const =0 ;

    /**
     * Write field FORCE_DPD_OVERRIDE at 0x4a4 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_forceDpdOverride(FpgaVal value) =0 ;

    /**
     * Read field FORCE_DPD_OVERRIDE at 0x4a4 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_forceDpdOverride() const =0 ;

    /**
     * Write field FORCE_DPD_OVERRIDE at 0x4a4 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_forceDpdOverride(FpgaVal value) =0 ;

    /**
     * Write field FORCE_DPD_OVERRIDE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_forceDpdOverride(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_FE_ATTEN_ELEM at 0x4aa bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_rxFeAttenElem() const =0 ;

    /**
     * Write field RX_FE_ATTEN_ELEM at 0x4aa bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxFeAttenElem(FpgaVal value) =0 ;

    /**
     * Read field RX_FE_ATTEN_ELEM at 0x4aa bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeAttenElem() const =0 ;

    /**
     * Write field RX_FE_ATTEN_ELEM at 0x4aa bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxFeAttenElem(FpgaVal value) =0 ;

    /**
     * Write field RX_FE_ATTEN_ELEM in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxFeAttenElem(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_FE_ATTEN_LEVEL at 0x4aa bits [4..2]
     * \return field value
     */
    virtual const FpgaVal read_rxFeAttenLevel() const =0 ;

    /**
     * Write field RX_FE_ATTEN_LEVEL at 0x4aa bits [4..2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxFeAttenLevel(FpgaVal value) =0 ;

    /**
     * Read field RX_FE_ATTEN_LEVEL at 0x4aa bits [4..2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeAttenLevel() const =0 ;

    /**
     * Write field RX_FE_ATTEN_LEVEL at 0x4aa bits [4..2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxFeAttenLevel(FpgaVal value) =0 ;

    /**
     * Write field RX_FE_ATTEN_LEVEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxFeAttenLevel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_FE_ATTEN_PORT at 0x4aa bits [8..5]
     * \return field value
     */
    virtual const FpgaVal read_rxFeAttenPort() const =0 ;

    /**
     * Write field RX_FE_ATTEN_PORT at 0x4aa bits [8..5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxFeAttenPort(FpgaVal value) =0 ;

    /**
     * Read field RX_FE_ATTEN_PORT at 0x4aa bits [8..5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeAttenPort() const =0 ;

    /**
     * Write field RX_FE_ATTEN_PORT at 0x4aa bits [8..5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxFeAttenPort(FpgaVal value) =0 ;

    /**
     * Write field RX_FE_ATTEN_PORT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxFeAttenPort(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_FE_ATTEN_DATA at 0x4ac bits [12..0]
     * \return field value
     */
    virtual const FpgaVal read_rxFeAttenData() const =0 ;

    /**
     * Write field RX_FE_ATTEN_DATA at 0x4ac bits [12..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxFeAttenData(FpgaVal value) =0 ;

    /**
     * Read field RX_FE_ATTEN_DATA at 0x4ac bits [12..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeAttenData() const =0 ;

    /**
     * Write field RX_FE_ATTEN_DATA at 0x4ac bits [12..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxFeAttenData(FpgaVal value) =0 ;

    /**
     * Write field RX_FE_ATTEN_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxFeAttenData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PA_CAL_CNTL at 0x4ae bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_paCalCntl() const =0 ;

    /**
     * Write field PA_CAL_CNTL at 0x4ae bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_paCalCntl(FpgaVal value) =0 ;

    /**
     * Read field PA_CAL_CNTL at 0x4ae bits [1..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_paCalCntl() const =0 ;

    /**
     * Write field PA_CAL_CNTL at 0x4ae bits [1..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_paCalCntl(FpgaVal value) =0 ;

    /**
     * Write field PA_CAL_CNTL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_paCalCntl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field COUPLER_CAL_CNTL at 0x4ae bits [3..2]
     * \return field value
     */
    virtual const FpgaVal read_couplerCalCntl() const =0 ;

    /**
     * Write field COUPLER_CAL_CNTL at 0x4ae bits [3..2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_couplerCalCntl(FpgaVal value) =0 ;

    /**
     * Read field COUPLER_CAL_CNTL at 0x4ae bits [3..2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_couplerCalCntl() const =0 ;

    /**
     * Write field COUPLER_CAL_CNTL at 0x4ae bits [3..2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_couplerCalCntl(FpgaVal value) =0 ;

    /**
     * Write field COUPLER_CAL_CNTL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_couplerCalCntl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LOOP_SEL at 0x4ae bits [4]
     * \return field value
     */
    virtual const FpgaVal read_loopSel() const =0 ;

    /**
     * Write field LOOP_SEL at 0x4ae bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_loopSel(FpgaVal value) =0 ;

    /**
     * Read field LOOP_SEL at 0x4ae bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_loopSel() const =0 ;

    /**
     * Write field LOOP_SEL at 0x4ae bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_loopSel(FpgaVal value) =0 ;

    /**
     * Write field LOOP_SEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_loopSel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TX_SEL at 0x4ae bits [5]
     * \return field value
     */
    virtual const FpgaVal read_txSel() const =0 ;

    /**
     * Write field TX_SEL at 0x4ae bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_txSel(FpgaVal value) =0 ;

    /**
     * Read field TX_SEL at 0x4ae bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_txSel() const =0 ;

    /**
     * Write field TX_SEL at 0x4ae bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_txSel(FpgaVal value) =0 ;

    /**
     * Write field TX_SEL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_txSel(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LOOPBACK_SELECT at 0x4ae bits [7..6]
     * \return field value
     */
    virtual const FpgaVal read_loopbackSelect() const =0 ;

    /**
     * Write field LOOPBACK_SELECT at 0x4ae bits [7..6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_loopbackSelect(FpgaVal value) =0 ;

    /**
     * Read field LOOPBACK_SELECT at 0x4ae bits [7..6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_loopbackSelect() const =0 ;

    /**
     * Write field LOOPBACK_SELECT at 0x4ae bits [7..6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_loopbackSelect(FpgaVal value) =0 ;

    /**
     * Write field LOOPBACK_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_loopbackSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CAL_FWD_REV_SEL_CH1 at 0x4ae bits [8]
     * \return field value
     */
    virtual const FpgaVal read_calFwdRevSelCh1() const =0 ;

    /**
     * Write field CAL_FWD_REV_SEL_CH1 at 0x4ae bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_calFwdRevSelCh1(FpgaVal value) =0 ;

    /**
     * Read field CAL_FWD_REV_SEL_CH1 at 0x4ae bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calFwdRevSelCh1() const =0 ;

    /**
     * Write field CAL_FWD_REV_SEL_CH1 at 0x4ae bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_calFwdRevSelCh1(FpgaVal value) =0 ;

    /**
     * Write field CAL_FWD_REV_SEL_CH1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_calFwdRevSelCh1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CAL_FWD_REV_SEL_CH2 at 0x4ae bits [9]
     * \return field value
     */
    virtual const FpgaVal read_calFwdRevSelCh2() const =0 ;

    /**
     * Write field CAL_FWD_REV_SEL_CH2 at 0x4ae bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_calFwdRevSelCh2(FpgaVal value) =0 ;

    /**
     * Read field CAL_FWD_REV_SEL_CH2 at 0x4ae bits [9]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calFwdRevSelCh2() const =0 ;

    /**
     * Write field CAL_FWD_REV_SEL_CH2 at 0x4ae bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_calFwdRevSelCh2(FpgaVal value) =0 ;

    /**
     * Write field CAL_FWD_REV_SEL_CH2 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_calFwdRevSelCh2(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CAL_ADC_IACC_LO at 0x4b0 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcIaccLo() const =0 ;


    /**
     * Read field CAL_ADC_IACC_LO at 0x4b0 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcIaccLo() const =0 ;




    /**
     * Read field CAL_ADC_IACC_HI at 0x4b2 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcIaccHi() const =0 ;


    /**
     * Read field CAL_ADC_IACC_HI at 0x4b2 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcIaccHi() const =0 ;




    /**
     * Read field CAL_ADC_QACC_LO at 0x4b4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcQaccLo() const =0 ;


    /**
     * Read field CAL_ADC_QACC_LO at 0x4b4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcQaccLo() const =0 ;




    /**
     * Read field CAL_ADC_QACC_HI at 0x4b6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcQaccHi() const =0 ;


    /**
     * Read field CAL_ADC_QACC_HI at 0x4b6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcQaccHi() const =0 ;




    /**
     * Read field CAL_ADC_SAMPLE_COUNT_LO at 0x4b8 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcSampleCountLo() const =0 ;


    /**
     * Read field CAL_ADC_SAMPLE_COUNT_LO at 0x4b8 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcSampleCountLo() const =0 ;




    /**
     * Read field CAL_ADC_SAMPLE_COUNT_HI at 0x4ba bits [5..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcSampleCountHi() const =0 ;


    /**
     * Read field CAL_ADC_SAMPLE_COUNT_HI at 0x4ba bits [5..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcSampleCountHi() const =0 ;




    /**
     * Read field CAL_ADC_RSSI_HP_LO at 0x4bc bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcRssiHpLo() const =0 ;


    /**
     * Read field CAL_ADC_RSSI_HP_LO at 0x4bc bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcRssiHpLo() const =0 ;




    /**
     * Read field CAL_ADC_RSSI_HP_HI at 0x4be bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcRssiHpHi() const =0 ;


    /**
     * Read field CAL_ADC_RSSI_HP_HI at 0x4be bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcRssiHpHi() const =0 ;




    /**
     * Read field DOWNLINK_POWER_SEQUENCE_NUMBER at 0x4c0 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_downlinkPowerSequenceNumber() const =0 ;


    /**
     * Read field DOWNLINK_POWER_SEQUENCE_NUMBER at 0x4c0 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_downlinkPowerSequenceNumber() const =0 ;




    /**
     * Read field DOWNLINK_POWER_SEQUENCE_NUMBER_RESET at 0x4c0 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_downlinkPowerSequenceNumberReset() const =0 ;

    /**
     * Write field DOWNLINK_POWER_SEQUENCE_NUMBER_RESET at 0x4c0 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_downlinkPowerSequenceNumberReset(FpgaVal value) =0 ;

    /**
     * Read field DOWNLINK_POWER_SEQUENCE_NUMBER_RESET at 0x4c0 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_downlinkPowerSequenceNumberReset() const =0 ;

    /**
     * Write field DOWNLINK_POWER_SEQUENCE_NUMBER_RESET at 0x4c0 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_downlinkPowerSequenceNumberReset(FpgaVal value) =0 ;

    /**
     * Write field DOWNLINK_POWER_SEQUENCE_NUMBER_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_downlinkPowerSequenceNumberReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DYN_ADC_DE_SKEW at 0x4d4 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_dynAdcDeSkew() const =0 ;

    /**
     * Write field DYN_ADC_DE_SKEW at 0x4d4 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dynAdcDeSkew(FpgaVal value) =0 ;

    /**
     * Read field DYN_ADC_DE_SKEW at 0x4d4 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dynAdcDeSkew() const =0 ;

    /**
     * Write field DYN_ADC_DE_SKEW at 0x4d4 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dynAdcDeSkew(FpgaVal value) =0 ;

    /**
     * Write field DYN_ADC_DE_SKEW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dynAdcDeSkew(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DYN_ADC_FORCE_DE_SKEW at 0x4d4 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_dynAdcForceDeSkew() const =0 ;

    /**
     * Write field DYN_ADC_FORCE_DE_SKEW at 0x4d4 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dynAdcForceDeSkew(FpgaVal value) =0 ;

    /**
     * Read field DYN_ADC_FORCE_DE_SKEW at 0x4d4 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dynAdcForceDeSkew() const =0 ;

    /**
     * Write field DYN_ADC_FORCE_DE_SKEW at 0x4d4 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dynAdcForceDeSkew(FpgaVal value) =0 ;

    /**
     * Write field DYN_ADC_FORCE_DE_SKEW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dynAdcForceDeSkew(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DYN_ADC_MASK at 0x4d6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_dynAdcMask() const =0 ;

    /**
     * Write field DYN_ADC_MASK at 0x4d6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_dynAdcMask(FpgaVal value) =0 ;

    /**
     * Read field DYN_ADC_MASK at 0x4d6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dynAdcMask() const =0 ;

    /**
     * Write field DYN_ADC_MASK at 0x4d6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_dynAdcMask(FpgaVal value) =0 ;

    /**
     * Write field DYN_ADC_MASK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_dynAdcMask(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_ENABLE at 0x5a2 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_xcorrEnable() const =0 ;

    /**
     * Write field XCORR_ENABLE at 0x5a2 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrEnable(FpgaVal value) =0 ;

    /**
     * Read field XCORR_ENABLE at 0x5a2 bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrEnable() const =0 ;

    /**
     * Write field XCORR_ENABLE at 0x5a2 bits [8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrEnable(FpgaVal value) =0 ;

    /**
     * Write field XCORR_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_REPLICA_ADDR_RESET at 0x5a2 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_xcorrReplicaAddrReset() const =0 ;

    /**
     * Write field XCORR_REPLICA_ADDR_RESET at 0x5a2 bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrReplicaAddrReset(FpgaVal value) =0 ;

    /**
     * Read field XCORR_REPLICA_ADDR_RESET at 0x5a2 bits [9]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrReplicaAddrReset() const =0 ;

    /**
     * Write field XCORR_REPLICA_ADDR_RESET at 0x5a2 bits [9]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrReplicaAddrReset(FpgaVal value) =0 ;

    /**
     * Write field XCORR_REPLICA_ADDR_RESET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrReplicaAddrReset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CAL_RX_TUNER_NCO_HI at 0x5ac bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calRxTunerNcoHi() const =0 ;

    /**
     * Write field CAL_RX_TUNER_NCO_HI at 0x5ac bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_calRxTunerNcoHi(FpgaVal value) =0 ;

    /**
     * Read field CAL_RX_TUNER_NCO_HI at 0x5ac bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calRxTunerNcoHi() const =0 ;

    /**
     * Write field CAL_RX_TUNER_NCO_HI at 0x5ac bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_calRxTunerNcoHi(FpgaVal value) =0 ;

    /**
     * Write field CAL_RX_TUNER_NCO_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_calRxTunerNcoHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CAL_RX_TUNER_NCO_LO at 0x5ae bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_calRxTunerNcoLo() const =0 ;

    /**
     * Write field CAL_RX_TUNER_NCO_LO at 0x5ae bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_calRxTunerNcoLo(FpgaVal value) =0 ;

    /**
     * Read field CAL_RX_TUNER_NCO_LO at 0x5ae bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calRxTunerNcoLo() const =0 ;

    /**
     * Write field CAL_RX_TUNER_NCO_LO at 0x5ae bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_calRxTunerNcoLo(FpgaVal value) =0 ;

    /**
     * Write field CAL_RX_TUNER_NCO_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_calRxTunerNcoLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DEST_MAC_UPPER_WORD at 0x5c2 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_destMacUpperWord() const =0 ;

    /**
     * Write field DEST_MAC_UPPER_WORD at 0x5c2 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_destMacUpperWord(FpgaVal value) =0 ;

    /**
     * Read field DEST_MAC_UPPER_WORD at 0x5c2 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_destMacUpperWord() const =0 ;

    /**
     * Write field DEST_MAC_UPPER_WORD at 0x5c2 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_destMacUpperWord(FpgaVal value) =0 ;

    /**
     * Write field DEST_MAC_UPPER_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_destMacUpperWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DEST_MAC_MIDDLE_WORD at 0x5c4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_destMacMiddleWord() const =0 ;

    /**
     * Write field DEST_MAC_MIDDLE_WORD at 0x5c4 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_destMacMiddleWord(FpgaVal value) =0 ;

    /**
     * Read field DEST_MAC_MIDDLE_WORD at 0x5c4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_destMacMiddleWord() const =0 ;

    /**
     * Write field DEST_MAC_MIDDLE_WORD at 0x5c4 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_destMacMiddleWord(FpgaVal value) =0 ;

    /**
     * Write field DEST_MAC_MIDDLE_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_destMacMiddleWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DEST_MAC_LOWER_WORD at 0x5c6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_destMacLowerWord() const =0 ;

    /**
     * Write field DEST_MAC_LOWER_WORD at 0x5c6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_destMacLowerWord(FpgaVal value) =0 ;

    /**
     * Read field DEST_MAC_LOWER_WORD at 0x5c6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_destMacLowerWord() const =0 ;

    /**
     * Write field DEST_MAC_LOWER_WORD at 0x5c6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_destMacLowerWord(FpgaVal value) =0 ;

    /**
     * Write field DEST_MAC_LOWER_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_destMacLowerWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRC_MAC_UPPER_WORD at 0x5c8 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_srcMacUpperWord() const =0 ;

    /**
     * Write field SRC_MAC_UPPER_WORD at 0x5c8 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srcMacUpperWord(FpgaVal value) =0 ;

    /**
     * Read field SRC_MAC_UPPER_WORD at 0x5c8 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srcMacUpperWord() const =0 ;

    /**
     * Write field SRC_MAC_UPPER_WORD at 0x5c8 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srcMacUpperWord(FpgaVal value) =0 ;

    /**
     * Write field SRC_MAC_UPPER_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srcMacUpperWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRC_MAC_MIDDLE_WORD at 0x5ca bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_srcMacMiddleWord() const =0 ;

    /**
     * Write field SRC_MAC_MIDDLE_WORD at 0x5ca bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srcMacMiddleWord(FpgaVal value) =0 ;

    /**
     * Read field SRC_MAC_MIDDLE_WORD at 0x5ca bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srcMacMiddleWord() const =0 ;

    /**
     * Write field SRC_MAC_MIDDLE_WORD at 0x5ca bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srcMacMiddleWord(FpgaVal value) =0 ;

    /**
     * Write field SRC_MAC_MIDDLE_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srcMacMiddleWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRC_MAC_LOWER_WORD at 0x5cc bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_srcMacLowerWord() const =0 ;

    /**
     * Write field SRC_MAC_LOWER_WORD at 0x5cc bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srcMacLowerWord(FpgaVal value) =0 ;

    /**
     * Read field SRC_MAC_LOWER_WORD at 0x5cc bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srcMacLowerWord() const =0 ;

    /**
     * Write field SRC_MAC_LOWER_WORD at 0x5cc bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srcMacLowerWord(FpgaVal value) =0 ;

    /**
     * Write field SRC_MAC_LOWER_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srcMacLowerWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DEST_IP_UPPER_WORD at 0x5ce bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_destIpUpperWord() const =0 ;

    /**
     * Write field DEST_IP_UPPER_WORD at 0x5ce bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_destIpUpperWord(FpgaVal value) =0 ;

    /**
     * Read field DEST_IP_UPPER_WORD at 0x5ce bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_destIpUpperWord() const =0 ;

    /**
     * Write field DEST_IP_UPPER_WORD at 0x5ce bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_destIpUpperWord(FpgaVal value) =0 ;

    /**
     * Write field DEST_IP_UPPER_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_destIpUpperWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DEST_IP_LOWER_WORD at 0x5d0 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_destIpLowerWord() const =0 ;

    /**
     * Write field DEST_IP_LOWER_WORD at 0x5d0 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_destIpLowerWord(FpgaVal value) =0 ;

    /**
     * Read field DEST_IP_LOWER_WORD at 0x5d0 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_destIpLowerWord() const =0 ;

    /**
     * Write field DEST_IP_LOWER_WORD at 0x5d0 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_destIpLowerWord(FpgaVal value) =0 ;

    /**
     * Write field DEST_IP_LOWER_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_destIpLowerWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRC_IP_UPPER_WORD at 0x5d2 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_srcIpUpperWord() const =0 ;

    /**
     * Write field SRC_IP_UPPER_WORD at 0x5d2 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srcIpUpperWord(FpgaVal value) =0 ;

    /**
     * Read field SRC_IP_UPPER_WORD at 0x5d2 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srcIpUpperWord() const =0 ;

    /**
     * Write field SRC_IP_UPPER_WORD at 0x5d2 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srcIpUpperWord(FpgaVal value) =0 ;

    /**
     * Write field SRC_IP_UPPER_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srcIpUpperWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRC_IP_LOWER_WORD at 0x5d4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_srcIpLowerWord() const =0 ;

    /**
     * Write field SRC_IP_LOWER_WORD at 0x5d4 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srcIpLowerWord(FpgaVal value) =0 ;

    /**
     * Read field SRC_IP_LOWER_WORD at 0x5d4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srcIpLowerWord() const =0 ;

    /**
     * Write field SRC_IP_LOWER_WORD at 0x5d4 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srcIpLowerWord(FpgaVal value) =0 ;

    /**
     * Write field SRC_IP_LOWER_WORD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srcIpLowerWord(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DEST_PORT at 0x5d6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_destPort() const =0 ;

    /**
     * Write field DEST_PORT at 0x5d6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_destPort(FpgaVal value) =0 ;

    /**
     * Read field DEST_PORT at 0x5d6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_destPort() const =0 ;

    /**
     * Write field DEST_PORT at 0x5d6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_destPort(FpgaVal value) =0 ;

    /**
     * Write field DEST_PORT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_destPort(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SRC_PORT at 0x5d8 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_srcPort() const =0 ;

    /**
     * Write field SRC_PORT at 0x5d8 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_srcPort(FpgaVal value) =0 ;

    /**
     * Read field SRC_PORT at 0x5d8 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_srcPort() const =0 ;

    /**
     * Write field SRC_PORT at 0x5d8 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_srcPort(FpgaVal value) =0 ;

    /**
     * Write field SRC_PORT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_srcPort(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_THRESHOLD_LO at 0x5dc bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrThresholdLo() const =0 ;

    /**
     * Write field XCORR_THRESHOLD_LO at 0x5dc bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrThresholdLo(FpgaVal value) =0 ;

    /**
     * Read field XCORR_THRESHOLD_LO at 0x5dc bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrThresholdLo() const =0 ;

    /**
     * Write field XCORR_THRESHOLD_LO at 0x5dc bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrThresholdLo(FpgaVal value) =0 ;

    /**
     * Write field XCORR_THRESHOLD_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrThresholdLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_THRESHOLD_HI at 0x5de bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrThresholdHi() const =0 ;

    /**
     * Write field XCORR_THRESHOLD_HI at 0x5de bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrThresholdHi(FpgaVal value) =0 ;

    /**
     * Read field XCORR_THRESHOLD_HI at 0x5de bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrThresholdHi() const =0 ;

    /**
     * Write field XCORR_THRESHOLD_HI at 0x5de bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrThresholdHi(FpgaVal value) =0 ;

    /**
     * Write field XCORR_THRESHOLD_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrThresholdHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_REPLICA_I0 at 0x5e0 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrReplicaI0() const =0 ;

    /**
     * Write field XCORR_REPLICA_I0 at 0x5e0 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrReplicaI0(FpgaVal value) =0 ;

    /**
     * Read field XCORR_REPLICA_I0 at 0x5e0 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrReplicaI0() const =0 ;

    /**
     * Write field XCORR_REPLICA_I0 at 0x5e0 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrReplicaI0(FpgaVal value) =0 ;

    /**
     * Write field XCORR_REPLICA_I0 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrReplicaI0(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_REPLICA_I1 at 0x5e2 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrReplicaI1() const =0 ;

    /**
     * Write field XCORR_REPLICA_I1 at 0x5e2 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrReplicaI1(FpgaVal value) =0 ;

    /**
     * Read field XCORR_REPLICA_I1 at 0x5e2 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrReplicaI1() const =0 ;

    /**
     * Write field XCORR_REPLICA_I1 at 0x5e2 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrReplicaI1(FpgaVal value) =0 ;

    /**
     * Write field XCORR_REPLICA_I1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrReplicaI1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_REPLICA_Q0 at 0x5e4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrReplicaQ0() const =0 ;

    /**
     * Write field XCORR_REPLICA_Q0 at 0x5e4 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrReplicaQ0(FpgaVal value) =0 ;

    /**
     * Read field XCORR_REPLICA_Q0 at 0x5e4 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrReplicaQ0() const =0 ;

    /**
     * Write field XCORR_REPLICA_Q0 at 0x5e4 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrReplicaQ0(FpgaVal value) =0 ;

    /**
     * Write field XCORR_REPLICA_Q0 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrReplicaQ0(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_REPLICA_Q1 at 0x5e6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrReplicaQ1() const =0 ;

    /**
     * Write field XCORR_REPLICA_Q1 at 0x5e6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrReplicaQ1(FpgaVal value) =0 ;

    /**
     * Read field XCORR_REPLICA_Q1 at 0x5e6 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrReplicaQ1() const =0 ;

    /**
     * Write field XCORR_REPLICA_Q1 at 0x5e6 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrReplicaQ1(FpgaVal value) =0 ;

    /**
     * Write field XCORR_REPLICA_Q1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrReplicaQ1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_PEAK_LO at 0x5e8 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrPeakLo() const =0 ;

    /**
     * Write field XCORR_PEAK_LO at 0x5e8 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrPeakLo(FpgaVal value) =0 ;

    /**
     * Read field XCORR_PEAK_LO at 0x5e8 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrPeakLo() const =0 ;

    /**
     * Write field XCORR_PEAK_LO at 0x5e8 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrPeakLo(FpgaVal value) =0 ;

    /**
     * Write field XCORR_PEAK_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrPeakLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field XCORR_PEAK_HI at 0x5ea bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrPeakHi() const =0 ;

    /**
     * Write field XCORR_PEAK_HI at 0x5ea bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrPeakHi(FpgaVal value) =0 ;

    /**
     * Read field XCORR_PEAK_HI at 0x5ea bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrPeakHi() const =0 ;

    /**
     * Write field XCORR_PEAK_HI at 0x5ea bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrPeakHi(FpgaVal value) =0 ;

    /**
     * Write field XCORR_PEAK_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_xcorrPeakHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MASTER_MODEM_NUM_DL_SAMPLES_LO at 0x610 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_masterModemNumDlSamplesLo() const =0 ;

    /**
     * Write field MASTER_MODEM_NUM_DL_SAMPLES_LO at 0x610 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterModemNumDlSamplesLo(FpgaVal value) =0 ;

    /**
     * Read field MASTER_MODEM_NUM_DL_SAMPLES_LO at 0x610 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterModemNumDlSamplesLo() const =0 ;

    /**
     * Write field MASTER_MODEM_NUM_DL_SAMPLES_LO at 0x610 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterModemNumDlSamplesLo(FpgaVal value) =0 ;

    /**
     * Write field MASTER_MODEM_NUM_DL_SAMPLES_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_masterModemNumDlSamplesLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MASTER_MODEM_NUM_DL_SAMPLES_HI at 0x612 bits [4..0]
     * \return field value
     */
    virtual const FpgaVal read_masterModemNumDlSamplesHi() const =0 ;

    /**
     * Write field MASTER_MODEM_NUM_DL_SAMPLES_HI at 0x612 bits [4..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterModemNumDlSamplesHi(FpgaVal value) =0 ;

    /**
     * Read field MASTER_MODEM_NUM_DL_SAMPLES_HI at 0x612 bits [4..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterModemNumDlSamplesHi() const =0 ;

    /**
     * Write field MASTER_MODEM_NUM_DL_SAMPLES_HI at 0x612 bits [4..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterModemNumDlSamplesHi(FpgaVal value) =0 ;

    /**
     * Write field MASTER_MODEM_NUM_DL_SAMPLES_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_masterModemNumDlSamplesHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BOARD_IS_MASTER at 0x620 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_boardIsMaster() const =0 ;

    /**
     * Write field BOARD_IS_MASTER at 0x620 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_boardIsMaster(FpgaVal value) =0 ;

    /**
     * Read field BOARD_IS_MASTER at 0x620 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_boardIsMaster() const =0 ;

    /**
     * Write field BOARD_IS_MASTER at 0x620 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_boardIsMaster(FpgaVal value) =0 ;

    /**
     * Write field BOARD_IS_MASTER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_boardIsMaster(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field USE_LOCAL_BUSES at 0x620 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_useLocalBuses() const =0 ;

    /**
     * Write field USE_LOCAL_BUSES at 0x620 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_useLocalBuses(FpgaVal value) =0 ;

    /**
     * Read field USE_LOCAL_BUSES at 0x620 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_useLocalBuses() const =0 ;

    /**
     * Write field USE_LOCAL_BUSES at 0x620 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_useLocalBuses(FpgaVal value) =0 ;

    /**
     * Write field USE_LOCAL_BUSES in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_useLocalBuses(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RX_TX_LOOP_ON_OFF at 0x620 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_rxTxLoopOnOff() const =0 ;

    /**
     * Write field RX_TX_LOOP_ON_OFF at 0x620 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxTxLoopOnOff(FpgaVal value) =0 ;

    /**
     * Read field RX_TX_LOOP_ON_OFF at 0x620 bits [15]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxTxLoopOnOff() const =0 ;

    /**
     * Write field RX_TX_LOOP_ON_OFF at 0x620 bits [15]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxTxLoopOnOff(FpgaVal value) =0 ;

    /**
     * Write field RX_TX_LOOP_ON_OFF in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rxTxLoopOnOff(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC1_INPUT_OUTPUT_SELECT at 0x62c bits [0]
     * \return field value
     */
    virtual const FpgaVal read_bnc1InputOutputSelect() const =0 ;

    /**
     * Write field BNC1_INPUT_OUTPUT_SELECT at 0x62c bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc1InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Read field BNC1_INPUT_OUTPUT_SELECT at 0x62c bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc1InputOutputSelect() const =0 ;

    /**
     * Write field BNC1_INPUT_OUTPUT_SELECT at 0x62c bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc1InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Write field BNC1_INPUT_OUTPUT_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc1InputOutputSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC2_INPUT_OUTPUT_SELECT at 0x62c bits [1]
     * \return field value
     */
    virtual const FpgaVal read_bnc2InputOutputSelect() const =0 ;

    /**
     * Write field BNC2_INPUT_OUTPUT_SELECT at 0x62c bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc2InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Read field BNC2_INPUT_OUTPUT_SELECT at 0x62c bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc2InputOutputSelect() const =0 ;

    /**
     * Write field BNC2_INPUT_OUTPUT_SELECT at 0x62c bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc2InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Write field BNC2_INPUT_OUTPUT_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc2InputOutputSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC3_INPUT_OUTPUT_SELECT at 0x62c bits [2]
     * \return field value
     */
    virtual const FpgaVal read_bnc3InputOutputSelect() const =0 ;

    /**
     * Write field BNC3_INPUT_OUTPUT_SELECT at 0x62c bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc3InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Read field BNC3_INPUT_OUTPUT_SELECT at 0x62c bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc3InputOutputSelect() const =0 ;

    /**
     * Write field BNC3_INPUT_OUTPUT_SELECT at 0x62c bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc3InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Write field BNC3_INPUT_OUTPUT_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc3InputOutputSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC4_INPUT_OUTPUT_SELECT at 0x62c bits [3]
     * \return field value
     */
    virtual const FpgaVal read_bnc4InputOutputSelect() const =0 ;

    /**
     * Write field BNC4_INPUT_OUTPUT_SELECT at 0x62c bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc4InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Read field BNC4_INPUT_OUTPUT_SELECT at 0x62c bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc4InputOutputSelect() const =0 ;

    /**
     * Write field BNC4_INPUT_OUTPUT_SELECT at 0x62c bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc4InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Write field BNC4_INPUT_OUTPUT_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc4InputOutputSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC5_INPUT_OUTPUT_SELECT at 0x62c bits [4]
     * \return field value
     */
    virtual const FpgaVal read_bnc5InputOutputSelect() const =0 ;

    /**
     * Write field BNC5_INPUT_OUTPUT_SELECT at 0x62c bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc5InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Read field BNC5_INPUT_OUTPUT_SELECT at 0x62c bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc5InputOutputSelect() const =0 ;

    /**
     * Write field BNC5_INPUT_OUTPUT_SELECT at 0x62c bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc5InputOutputSelect(FpgaVal value) =0 ;

    /**
     * Write field BNC5_INPUT_OUTPUT_SELECT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc5InputOutputSelect(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC1_INPUT_VALUE at 0x62c bits [5]
     * \return field value
     */
    virtual const FpgaVal read_bnc1InputValue() const =0 ;


    /**
     * Read field BNC1_INPUT_VALUE at 0x62c bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc1InputValue() const =0 ;




    /**
     * Read field BNC2_INPUT_VALUE at 0x62c bits [6]
     * \return field value
     */
    virtual const FpgaVal read_bnc2InputValue() const =0 ;


    /**
     * Read field BNC2_INPUT_VALUE at 0x62c bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc2InputValue() const =0 ;




    /**
     * Read field BNC3_INPUT_VALUE at 0x62c bits [7]
     * \return field value
     */
    virtual const FpgaVal read_bnc3InputValue() const =0 ;


    /**
     * Read field BNC3_INPUT_VALUE at 0x62c bits [7]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc3InputValue() const =0 ;




    /**
     * Read field BNC4_INPUT_VALUE at 0x62c bits [8]
     * \return field value
     */
    virtual const FpgaVal read_bnc4InputValue() const =0 ;


    /**
     * Read field BNC4_INPUT_VALUE at 0x62c bits [8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc4InputValue() const =0 ;




    /**
     * Read field BNC5_INPUT_VALUE at 0x62c bits [9]
     * \return field value
     */
    virtual const FpgaVal read_bnc5InputValue() const =0 ;


    /**
     * Read field BNC5_INPUT_VALUE at 0x62c bits [9]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc5InputValue() const =0 ;




    /**
     * Read field BNC1_OUTPUT_VALUE at 0x62c bits [10]
     * \return field value
     */
    virtual const FpgaVal read_bnc1OutputValue() const =0 ;

    /**
     * Write field BNC1_OUTPUT_VALUE at 0x62c bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc1OutputValue(FpgaVal value) =0 ;

    /**
     * Read field BNC1_OUTPUT_VALUE at 0x62c bits [10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc1OutputValue() const =0 ;

    /**
     * Write field BNC1_OUTPUT_VALUE at 0x62c bits [10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc1OutputValue(FpgaVal value) =0 ;

    /**
     * Write field BNC1_OUTPUT_VALUE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc1OutputValue(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC2_OUTPUT_VALUE at 0x62c bits [11]
     * \return field value
     */
    virtual const FpgaVal read_bnc2OutputValue() const =0 ;

    /**
     * Write field BNC2_OUTPUT_VALUE at 0x62c bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc2OutputValue(FpgaVal value) =0 ;

    /**
     * Read field BNC2_OUTPUT_VALUE at 0x62c bits [11]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc2OutputValue() const =0 ;

    /**
     * Write field BNC2_OUTPUT_VALUE at 0x62c bits [11]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc2OutputValue(FpgaVal value) =0 ;

    /**
     * Write field BNC2_OUTPUT_VALUE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc2OutputValue(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC3_OUTPUT_VALUE at 0x62c bits [12]
     * \return field value
     */
    virtual const FpgaVal read_bnc3OutputValue() const =0 ;

    /**
     * Write field BNC3_OUTPUT_VALUE at 0x62c bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc3OutputValue(FpgaVal value) =0 ;

    /**
     * Read field BNC3_OUTPUT_VALUE at 0x62c bits [12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc3OutputValue() const =0 ;

    /**
     * Write field BNC3_OUTPUT_VALUE at 0x62c bits [12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc3OutputValue(FpgaVal value) =0 ;

    /**
     * Write field BNC3_OUTPUT_VALUE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc3OutputValue(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC4_OUTPUT_VALUE at 0x62c bits [13]
     * \return field value
     */
    virtual const FpgaVal read_bnc4OutputValue() const =0 ;

    /**
     * Write field BNC4_OUTPUT_VALUE at 0x62c bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc4OutputValue(FpgaVal value) =0 ;

    /**
     * Read field BNC4_OUTPUT_VALUE at 0x62c bits [13]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc4OutputValue() const =0 ;

    /**
     * Write field BNC4_OUTPUT_VALUE at 0x62c bits [13]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc4OutputValue(FpgaVal value) =0 ;

    /**
     * Write field BNC4_OUTPUT_VALUE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc4OutputValue(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BNC5_OUTPUT_VALUE at 0x62c bits [14]
     * \return field value
     */
    virtual const FpgaVal read_bnc5OutputValue() const =0 ;

    /**
     * Write field BNC5_OUTPUT_VALUE at 0x62c bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_bnc5OutputValue(FpgaVal value) =0 ;

    /**
     * Read field BNC5_OUTPUT_VALUE at 0x62c bits [14]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_bnc5OutputValue() const =0 ;

    /**
     * Write field BNC5_OUTPUT_VALUE at 0x62c bits [14]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_bnc5OutputValue(FpgaVal value) =0 ;

    /**
     * Write field BNC5_OUTPUT_VALUE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_bnc5OutputValue(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CALIBRATION_ENABLE at 0x630 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_calibrationEnable() const =0 ;

    /**
     * Write field CALIBRATION_ENABLE at 0x630 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_calibrationEnable(FpgaVal value) =0 ;

    /**
     * Read field CALIBRATION_ENABLE at 0x630 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calibrationEnable() const =0 ;

    /**
     * Write field CALIBRATION_ENABLE at 0x630 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_calibrationEnable(FpgaVal value) =0 ;

    /**
     * Write field CALIBRATION_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_calibrationEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CALIBRATION_DONE at 0x630 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_calibrationDone() const =0 ;


    /**
     * Read field CALIBRATION_DONE at 0x630 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calibrationDone() const =0 ;




    /**
     * Read field CFR_TABLE_CONTROL at 0x630 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_cfrTableControl() const =0 ;

    /**
     * Write field CFR_TABLE_CONTROL at 0x630 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrTableControl(FpgaVal value) =0 ;

    /**
     * Read field CFR_TABLE_CONTROL at 0x630 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrTableControl() const =0 ;

    /**
     * Write field CFR_TABLE_CONTROL at 0x630 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrTableControl(FpgaVal value) =0 ;

    /**
     * Write field CFR_TABLE_CONTROL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrTableControl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field BEAMFORMER_TABLE_CONTROL at 0x630 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_beamformerTableControl() const =0 ;

    /**
     * Write field BEAMFORMER_TABLE_CONTROL at 0x630 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_beamformerTableControl(FpgaVal value) =0 ;

    /**
     * Read field BEAMFORMER_TABLE_CONTROL at 0x630 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_beamformerTableControl() const =0 ;

    /**
     * Write field BEAMFORMER_TABLE_CONTROL at 0x630 bits [3]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_beamformerTableControl(FpgaVal value) =0 ;

    /**
     * Write field BEAMFORMER_TABLE_CONTROL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_beamformerTableControl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_ACTIVE_TABLE at 0x630 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_cfrActiveTable() const =0 ;


    /**
     * Read field CFR_ACTIVE_TABLE at 0x630 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrActiveTable() const =0 ;




    /**
     * Read field CFR_FORCE_TABLE_CHG at 0x630 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_cfrForceTableChg() const =0 ;

    /**
     * Write field CFR_FORCE_TABLE_CHG at 0x630 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrForceTableChg(FpgaVal value) =0 ;

    /**
     * Read field CFR_FORCE_TABLE_CHG at 0x630 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrForceTableChg() const =0 ;

    /**
     * Write field CFR_FORCE_TABLE_CHG at 0x630 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrForceTableChg(FpgaVal value) =0 ;

    /**
     * Write field CFR_FORCE_TABLE_CHG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrForceTableChg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_CLIP_TABLE_ADDRESS at 0x680 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_cfrClipTableAddress() const =0 ;

    /**
     * Write field CFR_CLIP_TABLE_ADDRESS at 0x680 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrClipTableAddress(FpgaVal value) =0 ;

    /**
     * Read field CFR_CLIP_TABLE_ADDRESS at 0x680 bits [9..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrClipTableAddress() const =0 ;

    /**
     * Write field CFR_CLIP_TABLE_ADDRESS at 0x680 bits [9..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrClipTableAddress(FpgaVal value) =0 ;

    /**
     * Write field CFR_CLIP_TABLE_ADDRESS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrClipTableAddress(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_CLIP_TABLE_DATA at 0x682 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_cfrClipTableData() const =0 ;

    /**
     * Write field CFR_CLIP_TABLE_DATA at 0x682 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrClipTableData(FpgaVal value) =0 ;

    /**
     * Read field CFR_CLIP_TABLE_DATA at 0x682 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrClipTableData() const =0 ;

    /**
     * Write field CFR_CLIP_TABLE_DATA at 0x682 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrClipTableData(FpgaVal value) =0 ;

    /**
     * Write field CFR_CLIP_TABLE_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrClipTableData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_ERROR_FILTER_COEFFICIENT_ADDRESS at 0x684 bits [10..0]
     * \return field value
     */
    virtual const FpgaVal read_cfrErrorFilterCoefficientAddress() const =0 ;

    /**
     * Write field CFR_ERROR_FILTER_COEFFICIENT_ADDRESS at 0x684 bits [10..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrErrorFilterCoefficientAddress(FpgaVal value) =0 ;

    /**
     * Read field CFR_ERROR_FILTER_COEFFICIENT_ADDRESS at 0x684 bits [10..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrErrorFilterCoefficientAddress() const =0 ;

    /**
     * Write field CFR_ERROR_FILTER_COEFFICIENT_ADDRESS at 0x684 bits [10..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrErrorFilterCoefficientAddress(FpgaVal value) =0 ;

    /**
     * Write field CFR_ERROR_FILTER_COEFFICIENT_ADDRESS in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrErrorFilterCoefficientAddress(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CFR_ERROR_FILTER_COEFFICIENT_DATA at 0x686 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_cfrErrorFilterCoefficientData() const =0 ;

    /**
     * Write field CFR_ERROR_FILTER_COEFFICIENT_DATA at 0x686 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrErrorFilterCoefficientData(FpgaVal value) =0 ;

    /**
     * Read field CFR_ERROR_FILTER_COEFFICIENT_DATA at 0x686 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrErrorFilterCoefficientData() const =0 ;

    /**
     * Write field CFR_ERROR_FILTER_COEFFICIENT_DATA at 0x686 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrErrorFilterCoefficientData(FpgaVal value) =0 ;

    /**
     * Write field CFR_ERROR_FILTER_COEFFICIENT_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cfrErrorFilterCoefficientData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ETH_PAUSE_LENGTH at 0x922 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_ethPauseLength() const =0 ;

    /**
     * Write field ETH_PAUSE_LENGTH at 0x922 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ethPauseLength(FpgaVal value) =0 ;

    /**
     * Read field ETH_PAUSE_LENGTH at 0x922 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ethPauseLength() const =0 ;

    /**
     * Write field ETH_PAUSE_LENGTH at 0x922 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ethPauseLength(FpgaVal value) =0 ;

    /**
     * Write field ETH_PAUSE_LENGTH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ethPauseLength(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ETH_MANUAL_PAUSE_TRIGGER at 0x924 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_ethManualPauseTrigger() const =0 ;

    /**
     * Write field ETH_MANUAL_PAUSE_TRIGGER at 0x924 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ethManualPauseTrigger(FpgaVal value) =0 ;

    /**
     * Read field ETH_MANUAL_PAUSE_TRIGGER at 0x924 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ethManualPauseTrigger() const =0 ;

    /**
     * Write field ETH_MANUAL_PAUSE_TRIGGER at 0x924 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ethManualPauseTrigger(FpgaVal value) =0 ;

    /**
     * Write field ETH_MANUAL_PAUSE_TRIGGER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ethManualPauseTrigger(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ETH_PAUSE_MASK at 0x926 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_ethPauseMask() const =0 ;

    /**
     * Write field ETH_PAUSE_MASK at 0x926 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ethPauseMask(FpgaVal value) =0 ;

    /**
     * Read field ETH_PAUSE_MASK at 0x926 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ethPauseMask() const =0 ;

    /**
     * Write field ETH_PAUSE_MASK at 0x926 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ethPauseMask(FpgaVal value) =0 ;

    /**
     * Write field ETH_PAUSE_MASK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ethPauseMask(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MB_READ_DATA at 0xc00 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_mbReadData() const =0 ;

    /**
     * Write field MB_READ_DATA at 0xc00 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_mbReadData(FpgaVal value) =0 ;

    /**
     * Read field MB_READ_DATA at 0xc00 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbReadData() const =0 ;

    /**
     * Write field MB_READ_DATA at 0xc00 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_mbReadData(FpgaVal value) =0 ;

    /**
     * Write field MB_READ_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_mbReadData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MB_WRITE_DATA at 0xc02 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_mbWriteData() const =0 ;

    /**
     * Write field MB_WRITE_DATA at 0xc02 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_mbWriteData(FpgaVal value) =0 ;

    /**
     * Read field MB_WRITE_DATA at 0xc02 bits [7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbWriteData() const =0 ;

    /**
     * Write field MB_WRITE_DATA at 0xc02 bits [7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_mbWriteData(FpgaVal value) =0 ;

    /**
     * Write field MB_WRITE_DATA in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_mbWriteData(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MB_READ_EMPTY_FLAG at 0xc04 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_mbReadEmptyFlag() const =0 ;


    /**
     * Read field MB_READ_EMPTY_FLAG at 0xc04 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbReadEmptyFlag() const =0 ;




    /**
     * Read field MB_READ_HALF_FULL_FLAG at 0xc04 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_mbReadHalfFullFlag() const =0 ;


    /**
     * Read field MB_READ_HALF_FULL_FLAG at 0xc04 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbReadHalfFullFlag() const =0 ;




    /**
     * Read field MB_READ_FULL_FLAG at 0xc04 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_mbReadFullFlag() const =0 ;


    /**
     * Read field MB_READ_FULL_FLAG at 0xc04 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbReadFullFlag() const =0 ;




    /**
     * Read field MB_WRITE_EMPTY_FLAG at 0xc04 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_mbWriteEmptyFlag() const =0 ;


    /**
     * Read field MB_WRITE_EMPTY_FLAG at 0xc04 bits [3]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbWriteEmptyFlag() const =0 ;




    /**
     * Read field MB_WRITE_HALF_FULL_FLAG at 0xc04 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_mbWriteHalfFullFlag() const =0 ;


    /**
     * Read field MB_WRITE_HALF_FULL_FLAG at 0xc04 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbWriteHalfFullFlag() const =0 ;




    /**
     * Read field MB_WRITE_FULL_FLAG at 0xc04 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_mbWriteFullFlag() const =0 ;


    /**
     * Read field MB_WRITE_FULL_FLAG at 0xc04 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbWriteFullFlag() const =0 ;




    /**
     * Read field MB_READ_FIFO_LEN at 0xc06 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_mbReadFifoLen() const =0 ;


    /**
     * Read field MB_READ_FIFO_LEN at 0xc06 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbReadFifoLen() const =0 ;




    /**
     * Read field MB_WRITE_FIFO_LEN at 0xc08 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_mbWriteFifoLen() const =0 ;


    /**
     * Read field MB_WRITE_FIFO_LEN at 0xc08 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mbWriteFifoLen() const =0 ;




    /**
     * Read field RP3AF_SYNC_CLR at 0xd00 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_rp3afSyncClr() const =0 ;

    /**
     * Write field RP3AF_SYNC_CLR at 0xd00 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rp3afSyncClr(FpgaVal value) =0 ;

    /**
     * Read field RP3AF_SYNC_CLR at 0xd00 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rp3afSyncClr() const =0 ;

    /**
     * Write field RP3AF_SYNC_CLR at 0xd00 bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rp3afSyncClr(FpgaVal value) =0 ;

    /**
     * Write field RP3AF_SYNC_CLR in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rp3afSyncClr(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYNC_USE_RX_MF_TICK at 0xd00 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_syncUseRxMfTick() const =0 ;

    /**
     * Write field SYNC_USE_RX_MF_TICK at 0xd00 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_syncUseRxMfTick(FpgaVal value) =0 ;

    /**
     * Read field SYNC_USE_RX_MF_TICK at 0xd00 bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_syncUseRxMfTick() const =0 ;

    /**
     * Write field SYNC_USE_RX_MF_TICK at 0xd00 bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_syncUseRxMfTick(FpgaVal value) =0 ;

    /**
     * Write field SYNC_USE_RX_MF_TICK in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_syncUseRxMfTick(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYNC_FRAME_ADV_VALID at 0xd00 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_syncFrameAdvValid() const =0 ;

    /**
     * Write field SYNC_FRAME_ADV_VALID at 0xd00 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_syncFrameAdvValid(FpgaVal value) =0 ;

    /**
     * Read field SYNC_FRAME_ADV_VALID at 0xd00 bits [2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_syncFrameAdvValid() const =0 ;

    /**
     * Write field SYNC_FRAME_ADV_VALID at 0xd00 bits [2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_syncFrameAdvValid(FpgaVal value) =0 ;

    /**
     * Write field SYNC_FRAME_ADV_VALID in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_syncFrameAdvValid(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FORCE_SYNC at 0xd00 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_forceSync() const =0 ;

    /**
     * Write field FORCE_SYNC at 0xd00 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_forceSync(FpgaVal value) =0 ;

    /**
     * Read field FORCE_SYNC at 0xd00 bits [4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_forceSync() const =0 ;

    /**
     * Write field FORCE_SYNC at 0xd00 bits [4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_forceSync(FpgaVal value) =0 ;

    /**
     * Write field FORCE_SYNC in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_forceSync(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYNC_GPS_TICK_ENA_BIT at 0xd00 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_Sync_GpsTickEna_Bit() const =0 ;

    /**
     * Write field SYNC_GPS_TICK_ENA_BIT at 0xd00 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_Sync_GpsTickEna_Bit(FpgaVal value) =0 ;

    /**
     * Read field SYNC_GPS_TICK_ENA_BIT at 0xd00 bits [5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_Sync_GpsTickEna_Bit() const =0 ;

    /**
     * Write field SYNC_GPS_TICK_ENA_BIT at 0xd00 bits [5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_Sync_GpsTickEna_Bit(FpgaVal value) =0 ;

    /**
     * Write field SYNC_GPS_TICK_ENA_BIT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_Sync_GpsTickEna_Bit(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYNC_GPS_TICK_LOCK_BIT at 0xd00 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_Sync_GpsTickLock_Bit() const =0 ;

    /**
     * Write field SYNC_GPS_TICK_LOCK_BIT at 0xd00 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_Sync_GpsTickLock_Bit(FpgaVal value) =0 ;

    /**
     * Read field SYNC_GPS_TICK_LOCK_BIT at 0xd00 bits [6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_Sync_GpsTickLock_Bit() const =0 ;

    /**
     * Write field SYNC_GPS_TICK_LOCK_BIT at 0xd00 bits [6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_Sync_GpsTickLock_Bit(FpgaVal value) =0 ;

    /**
     * Write field SYNC_GPS_TICK_LOCK_BIT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_Sync_GpsTickLock_Bit(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CLK_SEL_FIBRE at 0xd00 bits [9..8]
     * \return field value
     */
    virtual const FpgaVal read_clkSelFibre() const =0 ;

    /**
     * Write field CLK_SEL_FIBRE at 0xd00 bits [9..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_clkSelFibre(FpgaVal value) =0 ;

    /**
     * Read field CLK_SEL_FIBRE at 0xd00 bits [9..8]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_clkSelFibre() const =0 ;

    /**
     * Write field CLK_SEL_FIBRE at 0xd00 bits [9..8]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_clkSelFibre(FpgaVal value) =0 ;

    /**
     * Write field CLK_SEL_FIBRE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_clkSelFibre(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYNC_SEL_FIBRE at 0xd00 bits [11..10]
     * \return field value
     */
    virtual const FpgaVal read_syncSelFibre() const =0 ;

    /**
     * Write field SYNC_SEL_FIBRE at 0xd00 bits [11..10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_syncSelFibre(FpgaVal value) =0 ;

    /**
     * Read field SYNC_SEL_FIBRE at 0xd00 bits [11..10]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_syncSelFibre() const =0 ;

    /**
     * Write field SYNC_SEL_FIBRE at 0xd00 bits [11..10]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_syncSelFibre(FpgaVal value) =0 ;

    /**
     * Write field SYNC_SEL_FIBRE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_syncSelFibre(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FRAME_TYPE at 0xd00 bits [15..12]
     * \return field value
     */
    virtual const FpgaVal read_Frame_Type() const =0 ;

    /**
     * Write field FRAME_TYPE at 0xd00 bits [15..12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_Frame_Type(FpgaVal value) =0 ;

    /**
     * Read field FRAME_TYPE at 0xd00 bits [15..12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_Frame_Type() const =0 ;

    /**
     * Write field FRAME_TYPE at 0xd00 bits [15..12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_Frame_Type(FpgaVal value) =0 ;

    /**
     * Write field FRAME_TYPE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_Frame_Type(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SYNC_OFFSET at 0xd02 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_syncOffset() const =0 ;

    /**
     * Write field SYNC_OFFSET at 0xd02 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_syncOffset(FpgaVal value) =0 ;

    /**
     * Read field SYNC_OFFSET at 0xd02 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_syncOffset() const =0 ;

    /**
     * Write field SYNC_OFFSET at 0xd02 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_syncOffset(FpgaVal value) =0 ;

    /**
     * Write field SYNC_OFFSET in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_syncOffset(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RP3_IS_SYNC at 0xd04 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_rp3IsSync() const =0 ;


    /**
     * Read field RP3_IS_SYNC at 0xd04 bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rp3IsSync() const =0 ;




    /**
     * Read field DUC_PWR_ADVANCE at 0xd10 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_ducPwrAdvance() const =0 ;

    /**
     * Write field DUC_PWR_ADVANCE at 0xd10 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ducPwrAdvance(FpgaVal value) =0 ;

    /**
     * Read field DUC_PWR_ADVANCE at 0xd10 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ducPwrAdvance() const =0 ;

    /**
     * Write field DUC_PWR_ADVANCE at 0xd10 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ducPwrAdvance(FpgaVal value) =0 ;

    /**
     * Write field DUC_PWR_ADVANCE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ducPwrAdvance(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RF_PWR_ADC_DELAY at 0xd12 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_rfPwrAdcDelay() const =0 ;


    /**
     * Read field RF_PWR_ADC_DELAY at 0xd12 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rfPwrAdcDelay() const =0 ;




    /**
     * Read field MIMO_OFFSET_LO at 0xd18 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_mimoOffsetLo() const =0 ;

    /**
     * Write field MIMO_OFFSET_LO at 0xd18 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_mimoOffsetLo(FpgaVal value) =0 ;

    /**
     * Read field MIMO_OFFSET_LO at 0xd18 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mimoOffsetLo() const =0 ;

    /**
     * Write field MIMO_OFFSET_LO at 0xd18 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_mimoOffsetLo(FpgaVal value) =0 ;

    /**
     * Write field MIMO_OFFSET_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_mimoOffsetLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MIMO_OFFSET_HI at 0xd1a bits [15..12]
     * \return field value
     */
    virtual const FpgaVal read_mimoOffsetHi() const =0 ;

    /**
     * Write field MIMO_OFFSET_HI at 0xd1a bits [15..12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_mimoOffsetHi(FpgaVal value) =0 ;

    /**
     * Read field MIMO_OFFSET_HI at 0xd1a bits [15..12]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mimoOffsetHi() const =0 ;

    /**
     * Write field MIMO_OFFSET_HI at 0xd1a bits [15..12]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_mimoOffsetHi(FpgaVal value) =0 ;

    /**
     * Write field MIMO_OFFSET_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_mimoOffsetHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WCDMA_TCP_TSLOT at 0xd1c bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_wcdmaTcpTslot() const =0 ;

    /**
     * Write field WCDMA_TCP_TSLOT at 0xd1c bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wcdmaTcpTslot(FpgaVal value) =0 ;

    /**
     * Read field WCDMA_TCP_TSLOT at 0xd1c bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wcdmaTcpTslot() const =0 ;

    /**
     * Write field WCDMA_TCP_TSLOT at 0xd1c bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wcdmaTcpTslot(FpgaVal value) =0 ;

    /**
     * Write field WCDMA_TCP_TSLOT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wcdmaTcpTslot(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field WCDMA_RTWP_TSLOT at 0xd1e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_wcdmaRtwpTslot() const =0 ;

    /**
     * Write field WCDMA_RTWP_TSLOT at 0xd1e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_wcdmaRtwpTslot(FpgaVal value) =0 ;

    /**
     * Read field WCDMA_RTWP_TSLOT at 0xd1e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_wcdmaRtwpTslot() const =0 ;

    /**
     * Write field WCDMA_RTWP_TSLOT at 0xd1e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_wcdmaRtwpTslot(FpgaVal value) =0 ;

    /**
     * Write field WCDMA_RTWP_TSLOT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_wcdmaRtwpTslot(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_ON_REG at 0xd20 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxOnReg() const =0 ;

    /**
     * Write field TDD_TX_ON_REG at 0xd20 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxOnReg(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_ON_REG at 0xd20 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxOnReg() const =0 ;

    /**
     * Write field TDD_TX_ON_REG at 0xd20 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxOnReg(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_ON_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxOnReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_ON_REG_HI at 0xd22 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxOnRegHi() const =0 ;

    /**
     * Write field TDD_TX_ON_REG_HI at 0xd22 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxOnRegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_ON_REG_HI at 0xd22 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxOnRegHi() const =0 ;

    /**
     * Write field TDD_TX_ON_REG_HI at 0xd22 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxOnRegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_ON_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxOnRegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_OFF_REG at 0xd24 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxOffReg() const =0 ;

    /**
     * Write field TDD_TX_OFF_REG at 0xd24 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxOffReg(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_OFF_REG at 0xd24 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxOffReg() const =0 ;

    /**
     * Write field TDD_TX_OFF_REG at 0xd24 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxOffReg(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_OFF_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxOffReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_OFF_REG_HI at 0xd26 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxOffRegHi() const =0 ;

    /**
     * Write field TDD_TX_OFF_REG_HI at 0xd26 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxOffRegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_OFF_REG_HI at 0xd26 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxOffRegHi() const =0 ;

    /**
     * Write field TDD_TX_OFF_REG_HI at 0xd26 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxOffRegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_OFF_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxOffRegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_ON2_REG at 0xd28 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxOn2Reg() const =0 ;

    /**
     * Write field TDD_TX_ON2_REG at 0xd28 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxOn2Reg(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_ON2_REG at 0xd28 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxOn2Reg() const =0 ;

    /**
     * Write field TDD_TX_ON2_REG at 0xd28 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxOn2Reg(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_ON2_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxOn2Reg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_ON2_REG_HI at 0xd2a bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxOn2RegHi() const =0 ;

    /**
     * Write field TDD_TX_ON2_REG_HI at 0xd2a bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxOn2RegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_ON2_REG_HI at 0xd2a bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxOn2RegHi() const =0 ;

    /**
     * Write field TDD_TX_ON2_REG_HI at 0xd2a bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxOn2RegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_ON2_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxOn2RegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_OFF2_REG at 0xd2c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxOff2Reg() const =0 ;

    /**
     * Write field TDD_TX_OFF2_REG at 0xd2c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxOff2Reg(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_OFF2_REG at 0xd2c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxOff2Reg() const =0 ;

    /**
     * Write field TDD_TX_OFF2_REG at 0xd2c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxOff2Reg(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_OFF2_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxOff2Reg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_OFF2_REG_HI at 0xd2e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxOff2RegHi() const =0 ;

    /**
     * Write field TDD_TX_OFF2_REG_HI at 0xd2e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxOff2RegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_OFF2_REG_HI at 0xd2e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxOff2RegHi() const =0 ;

    /**
     * Write field TDD_TX_OFF2_REG_HI at 0xd2e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxOff2RegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_OFF2_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxOff2RegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_ON_REG at 0xd30 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxOnReg() const =0 ;

    /**
     * Write field TDD_RX_ON_REG at 0xd30 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxOnReg(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_ON_REG at 0xd30 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxOnReg() const =0 ;

    /**
     * Write field TDD_RX_ON_REG at 0xd30 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxOnReg(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_ON_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxOnReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_ON_REG_HI at 0xd32 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxOnRegHi() const =0 ;

    /**
     * Write field TDD_RX_ON_REG_HI at 0xd32 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxOnRegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_ON_REG_HI at 0xd32 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxOnRegHi() const =0 ;

    /**
     * Write field TDD_RX_ON_REG_HI at 0xd32 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxOnRegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_ON_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxOnRegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_OFF_REG at 0xd34 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxOffReg() const =0 ;

    /**
     * Write field TDD_RX_OFF_REG at 0xd34 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxOffReg(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_OFF_REG at 0xd34 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxOffReg() const =0 ;

    /**
     * Write field TDD_RX_OFF_REG at 0xd34 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxOffReg(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_OFF_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxOffReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_OFF_REG_HI at 0xd36 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxOffRegHi() const =0 ;

    /**
     * Write field TDD_RX_OFF_REG_HI at 0xd36 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxOffRegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_OFF_REG_HI at 0xd36 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxOffRegHi() const =0 ;

    /**
     * Write field TDD_RX_OFF_REG_HI at 0xd36 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxOffRegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_OFF_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxOffRegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_ON2_REG at 0xd38 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxOn2Reg() const =0 ;

    /**
     * Write field TDD_RX_ON2_REG at 0xd38 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxOn2Reg(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_ON2_REG at 0xd38 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxOn2Reg() const =0 ;

    /**
     * Write field TDD_RX_ON2_REG at 0xd38 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxOn2Reg(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_ON2_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxOn2Reg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_ON2_REG_HI at 0xd3a bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxOn2RegHi() const =0 ;

    /**
     * Write field TDD_RX_ON2_REG_HI at 0xd3a bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxOn2RegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_ON2_REG_HI at 0xd3a bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxOn2RegHi() const =0 ;

    /**
     * Write field TDD_RX_ON2_REG_HI at 0xd3a bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxOn2RegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_ON2_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxOn2RegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_OFF2_REG at 0xd3c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxOff2Reg() const =0 ;

    /**
     * Write field TDD_RX_OFF2_REG at 0xd3c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxOff2Reg(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_OFF2_REG at 0xd3c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxOff2Reg() const =0 ;

    /**
     * Write field TDD_RX_OFF2_REG at 0xd3c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxOff2Reg(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_OFF2_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxOff2Reg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_OFF2_REG_HI at 0xd3e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxOff2RegHi() const =0 ;

    /**
     * Write field TDD_RX_OFF2_REG_HI at 0xd3e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxOff2RegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_OFF2_REG_HI at 0xd3e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxOff2RegHi() const =0 ;

    /**
     * Write field TDD_RX_OFF2_REG_HI at 0xd3e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxOff2RegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_OFF2_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxOff2RegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_REG_ON_REG at 0xd40 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxRegOnReg() const =0 ;

    /**
     * Write field TDD_RX_REG_ON_REG at 0xd40 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxRegOnReg(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_REG_ON_REG at 0xd40 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxRegOnReg() const =0 ;

    /**
     * Write field TDD_RX_REG_ON_REG at 0xd40 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxRegOnReg(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_REG_ON_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxRegOnReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_REG_ON_REG_HI at 0xd42 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxRegOnRegHi() const =0 ;

    /**
     * Write field TDD_RX_REG_ON_REG_HI at 0xd42 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxRegOnRegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_REG_ON_REG_HI at 0xd42 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxRegOnRegHi() const =0 ;

    /**
     * Write field TDD_RX_REG_ON_REG_HI at 0xd42 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxRegOnRegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_REG_ON_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxRegOnRegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_REG_ON2_REG at 0xd44 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxRegOn2Reg() const =0 ;

    /**
     * Write field TDD_RX_REG_ON2_REG at 0xd44 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxRegOn2Reg(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_REG_ON2_REG at 0xd44 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxRegOn2Reg() const =0 ;

    /**
     * Write field TDD_RX_REG_ON2_REG at 0xd44 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxRegOn2Reg(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_REG_ON2_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxRegOn2Reg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_RX_REG_ON2_REG_HI at 0xd46 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddRxRegOn2RegHi() const =0 ;

    /**
     * Write field TDD_RX_REG_ON2_REG_HI at 0xd46 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddRxRegOn2RegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_RX_REG_ON2_REG_HI at 0xd46 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddRxRegOn2RegHi() const =0 ;

    /**
     * Write field TDD_RX_REG_ON2_REG_HI at 0xd46 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddRxRegOn2RegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_RX_REG_ON2_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddRxRegOn2RegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_LO_ON_REG at 0xd50 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxLoOnReg() const =0 ;

    /**
     * Write field TDD_TX_LO_ON_REG at 0xd50 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxLoOnReg(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_LO_ON_REG at 0xd50 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxLoOnReg() const =0 ;

    /**
     * Write field TDD_TX_LO_ON_REG at 0xd50 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxLoOnReg(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_LO_ON_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxLoOnReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_LO_ON_REG_HI at 0xd52 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxLoOnRegHi() const =0 ;

    /**
     * Write field TDD_TX_LO_ON_REG_HI at 0xd52 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxLoOnRegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_LO_ON_REG_HI at 0xd52 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxLoOnRegHi() const =0 ;

    /**
     * Write field TDD_TX_LO_ON_REG_HI at 0xd52 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxLoOnRegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_LO_ON_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxLoOnRegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_LO_OFF_REG at 0xd54 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxLoOffReg() const =0 ;

    /**
     * Write field TDD_TX_LO_OFF_REG at 0xd54 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxLoOffReg(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_LO_OFF_REG at 0xd54 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxLoOffReg() const =0 ;

    /**
     * Write field TDD_TX_LO_OFF_REG at 0xd54 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxLoOffReg(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_LO_OFF_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxLoOffReg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_LO_OFF_REG_HI at 0xd56 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxLoOffRegHi() const =0 ;

    /**
     * Write field TDD_TX_LO_OFF_REG_HI at 0xd56 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxLoOffRegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_LO_OFF_REG_HI at 0xd56 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxLoOffRegHi() const =0 ;

    /**
     * Write field TDD_TX_LO_OFF_REG_HI at 0xd56 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxLoOffRegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_LO_OFF_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxLoOffRegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_LO_ON2_REG at 0xd58 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxLoOn2Reg() const =0 ;

    /**
     * Write field TDD_TX_LO_ON2_REG at 0xd58 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxLoOn2Reg(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_LO_ON2_REG at 0xd58 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxLoOn2Reg() const =0 ;

    /**
     * Write field TDD_TX_LO_ON2_REG at 0xd58 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxLoOn2Reg(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_LO_ON2_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxLoOn2Reg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_LO_ON2_REG_HI at 0xd5a bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxLoOn2RegHi() const =0 ;

    /**
     * Write field TDD_TX_LO_ON2_REG_HI at 0xd5a bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxLoOn2RegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_LO_ON2_REG_HI at 0xd5a bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxLoOn2RegHi() const =0 ;

    /**
     * Write field TDD_TX_LO_ON2_REG_HI at 0xd5a bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxLoOn2RegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_LO_ON2_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxLoOn2RegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_LO_OFF2_REG at 0xd5c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxLoOff2Reg() const =0 ;

    /**
     * Write field TDD_TX_LO_OFF2_REG at 0xd5c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxLoOff2Reg(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_LO_OFF2_REG at 0xd5c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxLoOff2Reg() const =0 ;

    /**
     * Write field TDD_TX_LO_OFF2_REG at 0xd5c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxLoOff2Reg(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_LO_OFF2_REG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxLoOff2Reg(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_TX_LO_OFF2_REG_HI at 0xd5e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddTxLoOff2RegHi() const =0 ;

    /**
     * Write field TDD_TX_LO_OFF2_REG_HI at 0xd5e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddTxLoOff2RegHi(FpgaVal value) =0 ;

    /**
     * Read field TDD_TX_LO_OFF2_REG_HI at 0xd5e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddTxLoOff2RegHi() const =0 ;

    /**
     * Write field TDD_TX_LO_OFF2_REG_HI at 0xd5e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddTxLoOff2RegHi(FpgaVal value) =0 ;

    /**
     * Write field TDD_TX_LO_OFF2_REG_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddTxLoOff2RegHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_CTRL at 0xd7e bits [0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutCtrl() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_CTRL at 0xd7e bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutCtrl(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_CTRL at 0xd7e bits [0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutCtrl() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_CTRL at 0xd7e bits [0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutCtrl(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_CTRL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutCtrl(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_POLARITY at 0xd7e bits [1]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutPolarity() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_POLARITY at 0xd7e bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutPolarity(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_POLARITY at 0xd7e bits [1]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutPolarity() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_POLARITY at 0xd7e bits [1]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutPolarity(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_POLARITY in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutPolarity(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_ON1 at 0xd80 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutOn1() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON1 at 0xd80 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutOn1(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_ON1 at 0xd80 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutOn1() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON1 at 0xd80 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutOn1(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutOn1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_ON1_HI at 0xd82 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutOn1Hi() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON1_HI at 0xd82 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutOn1Hi(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_ON1_HI at 0xd82 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutOn1Hi() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON1_HI at 0xd82 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutOn1Hi(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON1_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutOn1Hi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_OFF1 at 0xd84 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutOff1() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF1 at 0xd84 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutOff1(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_OFF1 at 0xd84 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutOff1() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF1 at 0xd84 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutOff1(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutOff1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_OFF1_HI at 0xd86 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutOff1Hi() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF1_HI at 0xd86 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutOff1Hi(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_OFF1_HI at 0xd86 bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutOff1Hi() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF1_HI at 0xd86 bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutOff1Hi(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF1_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutOff1Hi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_ON2 at 0xd88 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutOn2() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON2 at 0xd88 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutOn2(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_ON2 at 0xd88 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutOn2() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON2 at 0xd88 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutOn2(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON2 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutOn2(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_ON2_HI at 0xd8a bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutOn2Hi() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON2_HI at 0xd8a bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutOn2Hi(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_ON2_HI at 0xd8a bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutOn2Hi() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON2_HI at 0xd8a bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutOn2Hi(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_ON2_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutOn2Hi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_OFF2 at 0xd8c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutOff2() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF2 at 0xd8c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutOff2(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_OFF2 at 0xd8c bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutOff2() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF2 at 0xd8c bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutOff2(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF2 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutOff2(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field TDD_SIGNAL_OUT_OFF2_HI at 0xd8e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_tddSignalOutOff2Hi() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF2_HI at 0xd8e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_tddSignalOutOff2Hi(FpgaVal value) =0 ;

    /**
     * Read field TDD_SIGNAL_OUT_OFF2_HI at 0xd8e bits [3..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_tddSignalOutOff2Hi() const =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF2_HI at 0xd8e bits [3..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_tddSignalOutOff2Hi(FpgaVal value) =0 ;

    /**
     * Write field TDD_SIGNAL_OUT_OFF2_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_tddSignalOutOff2Hi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DL_TYPE at 0x30000 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_dlType(unsigned chain) const =0 ;


    /**
     * Read field DL_TYPE at 0x30000 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlType(unsigned chain) const =0 ;




    /**
     * Read field DL_IQ_STREAMS at 0x30004 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_dlIqStreams(unsigned chain) const =0 ;


    /**
     * Read field DL_IQ_STREAMS at 0x30004 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_dlIqStreams(unsigned chain) const =0 ;




    /**
     * Read field RESULTING_DL_PROCESSING at 0x30008 bits [15..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_resultingDlProcessing(unsigned chain) const =0 ;


    /**
     * Read field RESULTING_DL_PROCESSING at 0x30008 bits [15..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_resultingDlProcessing(unsigned chain) const =0 ;




    /**
     * Read field UL_TYPE at 0x30010 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_ulType(unsigned chain) const =0 ;


    /**
     * Read field UL_TYPE at 0x30010 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulType(unsigned chain) const =0 ;




    /**
     * Read field UL_IQ_STREAMS at 0x30014 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_ulIqStreams(unsigned chain) const =0 ;


    /**
     * Read field UL_IQ_STREAMS at 0x30014 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ulIqStreams(unsigned chain) const =0 ;




    /**
     * Read field RESULTING_UL_PROCESSING at 0x30018 bits [15..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_resultingUlProcessing(unsigned chain) const =0 ;


    /**
     * Read field RESULTING_UL_PROCESSING at 0x30018 bits [15..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_resultingUlProcessing(unsigned chain) const =0 ;




    /**
     * Read field DESIRED_CH_BW at 0x30020 bits [4..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_desiredChBw(unsigned chain) const =0 ;

    /**
     * Write field DESIRED_CH_BW at 0x30020 bits [4..0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_desiredChBw(unsigned chain, FpgaVal value) =0 ;

    /**
     * Read field DESIRED_CH_BW at 0x30020 bits [4..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_desiredChBw(unsigned chain) const =0 ;

    /**
     * Write field DESIRED_CH_BW at 0x30020 bits [4..0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_desiredChBw(unsigned chain, FpgaVal value) =0 ;

    /**
     * Write field DESIRED_CH_BW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_desiredChBw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DESIRED_AIR_STD at 0x30022 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_desiredAirStd(unsigned chain) const =0 ;

    /**
     * Write field DESIRED_AIR_STD at 0x30022 bits [7..0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_desiredAirStd(unsigned chain, FpgaVal value) =0 ;

    /**
     * Read field DESIRED_AIR_STD at 0x30022 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_desiredAirStd(unsigned chain) const =0 ;

    /**
     * Write field DESIRED_AIR_STD at 0x30022 bits [7..0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_desiredAirStd(unsigned chain, FpgaVal value) =0 ;

    /**
     * Write field DESIRED_AIR_STD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_desiredAirStd(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ACTIVE_CH_BW at 0x30024 bits [4..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_activeChBw(unsigned chain) const =0 ;

    /**
     * Write field ACTIVE_CH_BW at 0x30024 bits [4..0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_activeChBw(unsigned chain, FpgaVal value) =0 ;

    /**
     * Read field ACTIVE_CH_BW at 0x30024 bits [4..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_activeChBw(unsigned chain) const =0 ;

    /**
     * Write field ACTIVE_CH_BW at 0x30024 bits [4..0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_activeChBw(unsigned chain, FpgaVal value) =0 ;

    /**
     * Write field ACTIVE_CH_BW in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_activeChBw(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field ACTIVE_AIR_STD at 0x30026 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_activeAirStd(unsigned chain) const =0 ;

    /**
     * Write field ACTIVE_AIR_STD at 0x30026 bits [7..0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_activeAirStd(unsigned chain, FpgaVal value) =0 ;

    /**
     * Read field ACTIVE_AIR_STD at 0x30026 bits [7..0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_activeAirStd(unsigned chain) const =0 ;

    /**
     * Write field ACTIVE_AIR_STD at 0x30026 bits [7..0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_activeAirStd(unsigned chain, FpgaVal value) =0 ;

    /**
     * Write field ACTIVE_AIR_STD in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_activeAirStd(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CHAIN_ACTIVE at 0x3002c bits [0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_ChainActive(unsigned chain) const =0 ;

    /**
     * Write field CHAIN_ACTIVE at 0x3002c bits [0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ChainActive(unsigned chain, FpgaVal value) =0 ;

    /**
     * Read field CHAIN_ACTIVE at 0x3002c bits [0]
     * \param chain
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ChainActive(unsigned chain) const =0 ;

    /**
     * Write field CHAIN_ACTIVE at 0x3002c bits [0]
     * \param chain
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ChainActive(unsigned chain, FpgaVal value) =0 ;

    /**
     * Write field CHAIN_ACTIVE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ChainActive(FpgaVal* buff, FpgaVal value) =0 ;



    /**
     * Read combined register PLL_LOCK at 0xc bits [15..1311..10,7..6]
     * \return field value
     */
    virtual const FpgaVal read_pllLock() const =0 ;






    /**
     * Write combined field PLL_LOCK at 0xc bits [15..1311..10,7..6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_pllLock(FpgaVal value) =0 ;






    /**
     * Read combined register PLL_LOCK at 0xc bits [15..1311..10,7..6]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_pllLock() const =0 ;






    /**
     * Write combined field PLL_LOCK at 0xc bits [15..1311..10,7..6]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_pllLock(FpgaVal value) =0 ;


    /**
     * Read combined register SAMPLE_POINT at 0x8e bits [18..0]
     * \return field value
     */
    virtual const FpgaVal read_samplePoint() const =0 ;






    /**
     * Write combined field SAMPLE_POINT at 0x8e bits [18..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_samplePoint(FpgaVal value) =0 ;






    /**
     * Read combined register SAMPLE_POINT at 0x8e bits [18..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_samplePoint() const =0 ;






    /**
     * Write combined field SAMPLE_POINT at 0x8e bits [18..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_samplePoint(FpgaVal value) =0 ;


    /**
     * Read combined register FPGA_VERSION at 0x100 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_fpgaVersion() const =0 ;







    /**
     * Read combined register FPGA_VERSION at 0x100 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fpgaVersion() const =0 ;



    /**
     * Read combined register SPI0_CONTROL1 at 0x200 bits [15..4]
     * \return field value
     */
    virtual const FpgaVal read_spi0Control1() const =0 ;






    /**
     * Write combined field SPI0_CONTROL1 at 0x200 bits [15..4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0Control1(FpgaVal value) =0 ;






    /**
     * Read combined register SPI0_CONTROL1 at 0x200 bits [15..4]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0Control1() const =0 ;






    /**
     * Write combined field SPI0_CONTROL1 at 0x200 bits [15..4]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0Control1(FpgaVal value) =0 ;


    /**
     * Read combined register SPI0_WRITE_DATA at 0x204 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0WriteData() const =0 ;






    /**
     * Write combined field SPI0_WRITE_DATA at 0x204 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0WriteData(FpgaVal value) =0 ;






    /**
     * Read combined register SPI0_WRITE_DATA at 0x204 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0WriteData() const =0 ;






    /**
     * Write combined field SPI0_WRITE_DATA at 0x204 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0WriteData(FpgaVal value) =0 ;


    /**
     * Read combined register SPI0_READ_DATA at 0x208 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0ReadData() const =0 ;







    /**
     * Read combined register SPI0_READ_DATA at 0x208 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0ReadData() const =0 ;



    /**
     * Read combined register I2C_CSR_REG at 0x216 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_i2cCsrReg() const =0 ;






    /**
     * Write combined field I2C_CSR_REG at 0x216 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_i2cCsrReg(FpgaVal value) =0 ;






    /**
     * Read combined register I2C_CSR_REG at 0x216 bits [15..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_i2cCsrReg() const =0 ;






    /**
     * Write combined field I2C_CSR_REG at 0x216 bits [15..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_i2cCsrReg(FpgaVal value) =0 ;


    /**
     * Read combined register SPI1_CONTROL1 at 0x300 bits [15..5]
     * \return field value
     */
    virtual const FpgaVal read_spi1Control1() const =0 ;






    /**
     * Write combined field SPI1_CONTROL1 at 0x300 bits [15..5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1Control1(FpgaVal value) =0 ;






    /**
     * Read combined register SPI1_CONTROL1 at 0x300 bits [15..5]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1Control1() const =0 ;






    /**
     * Write combined field SPI1_CONTROL1 at 0x300 bits [15..5]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1Control1(FpgaVal value) =0 ;


    /**
     * Read combined register SPI1_WRITE_DATA at 0x304 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1WriteData() const =0 ;






    /**
     * Write combined field SPI1_WRITE_DATA at 0x304 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1WriteData(FpgaVal value) =0 ;






    /**
     * Read combined register SPI1_WRITE_DATA at 0x304 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1WriteData() const =0 ;






    /**
     * Write combined field SPI1_WRITE_DATA at 0x304 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1WriteData(FpgaVal value) =0 ;


    /**
     * Read combined register SPI1_READ_DATA at 0x308 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1ReadData() const =0 ;







    /**
     * Read combined register SPI1_READ_DATA at 0x308 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1ReadData() const =0 ;



    /**
     * Read combined register SPI1_CONTROL2 at 0x30c bits [15..14,7..0]
     * \return field value
     */
    virtual const FpgaVal read_spi1Control2() const =0 ;






    /**
     * Write combined field SPI1_CONTROL2 at 0x30c bits [15..14,7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi1Control2(FpgaVal value) =0 ;






    /**
     * Read combined register SPI1_CONTROL2 at 0x30c bits [15..14,7..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi1Control2() const =0 ;






    /**
     * Write combined field SPI1_CONTROL2 at 0x30c bits [15..14,7..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi1Control2(FpgaVal value) =0 ;


    /**
     * Read combined register SPI0_CONTROL2 at 0x30e bits [15..14,8..0]
     * \return field value
     */
    virtual const FpgaVal read_spi0Control2() const =0 ;






    /**
     * Write combined field SPI0_CONTROL2 at 0x30e bits [15..14,8..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_spi0Control2(FpgaVal value) =0 ;






    /**
     * Read combined register SPI0_CONTROL2 at 0x30e bits [15..14,8..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_spi0Control2() const =0 ;






    /**
     * Write combined field SPI0_CONTROL2 at 0x30e bits [15..14,8..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_spi0Control2(FpgaVal value) =0 ;


    /**
     * Read combined register RSSI_ADC_RESULT at 0x40c bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiAdcResult() const =0 ;







    /**
     * Read combined register RSSI_ADC_RESULT at 0x40c bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiAdcResult() const =0 ;



    /**
     * Read combined register RSSI_DUTY_CYCLE_COUNT at 0x41c bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_rssiDutyCycleCount() const =0 ;







    /**
     * Read combined register RSSI_DUTY_CYCLE_COUNT at 0x41c bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rssiDutyCycleCount() const =0 ;



    /**
     * Read combined register RX_FE_ATTEN_REG at 0x4aa bits [8..0]
     * \return field value
     */
    virtual const FpgaVal read_rxFeAtten_reg() const =0 ;






    /**
     * Write combined field RX_FE_ATTEN_REG at 0x4aa bits [8..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rxFeAtten_reg(FpgaVal value) =0 ;






    /**
     * Read combined register RX_FE_ATTEN_REG at 0x4aa bits [8..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rxFeAtten_reg() const =0 ;






    /**
     * Write combined field RX_FE_ATTEN_REG at 0x4aa bits [8..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rxFeAtten_reg(FpgaVal value) =0 ;


    /**
     * Read combined register CAL_ADC_IACC at 0x4b0 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcIacc() const =0 ;







    /**
     * Read combined register CAL_ADC_IACC at 0x4b0 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcIacc() const =0 ;



    /**
     * Read combined register CAL_ADC_QACC at 0x4b4 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcQacc() const =0 ;







    /**
     * Read combined register CAL_ADC_QACC at 0x4b4 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcQacc() const =0 ;



    /**
     * Read combined register CAL_ADC_SAMPLE_COUNT at 0x4b8 bits [21..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcSampleCount() const =0 ;







    /**
     * Read combined register CAL_ADC_SAMPLE_COUNT at 0x4b8 bits [21..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcSampleCount() const =0 ;



    /**
     * Read combined register CAL_ADC_RSSI_HP at 0x4bc bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_calAdcRssiHp() const =0 ;







    /**
     * Read combined register CAL_ADC_RSSI_HP at 0x4bc bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_calAdcRssiHp() const =0 ;



    /**
     * Read combined register XCORR_THRESHOLD at 0x5dc bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrThreshold() const =0 ;






    /**
     * Write combined field XCORR_THRESHOLD at 0x5dc bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrThreshold(FpgaVal value) =0 ;






    /**
     * Read combined register XCORR_THRESHOLD at 0x5dc bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrThreshold() const =0 ;






    /**
     * Write combined field XCORR_THRESHOLD at 0x5dc bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrThreshold(FpgaVal value) =0 ;


    /**
     * Read combined register XCORR_REPLICA_I at 0x5e0 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrReplicaI() const =0 ;






    /**
     * Write combined field XCORR_REPLICA_I at 0x5e0 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrReplicaI(FpgaVal value) =0 ;






    /**
     * Read combined register XCORR_REPLICA_I at 0x5e0 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrReplicaI() const =0 ;






    /**
     * Write combined field XCORR_REPLICA_I at 0x5e0 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrReplicaI(FpgaVal value) =0 ;


    /**
     * Read combined register XCORR_REPLICA_Q at 0x5e4 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrReplicaQ() const =0 ;






    /**
     * Write combined field XCORR_REPLICA_Q at 0x5e4 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrReplicaQ(FpgaVal value) =0 ;






    /**
     * Read combined register XCORR_REPLICA_Q at 0x5e4 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrReplicaQ() const =0 ;






    /**
     * Write combined field XCORR_REPLICA_Q at 0x5e4 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrReplicaQ(FpgaVal value) =0 ;


    /**
     * Read combined register XCORR_PEAK at 0x5e8 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_xcorrPeak() const =0 ;






    /**
     * Write combined field XCORR_PEAK at 0x5e8 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_xcorrPeak(FpgaVal value) =0 ;






    /**
     * Read combined register XCORR_PEAK at 0x5e8 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_xcorrPeak() const =0 ;






    /**
     * Write combined field XCORR_PEAK at 0x5e8 bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_xcorrPeak(FpgaVal value) =0 ;


    /**
     * Read combined register MASTER_MODEM_NUM_DL_SAMPLES at 0x610 bits [20..0]
     * \return field value
     */
    virtual const FpgaVal read_masterModemNumDlSamples() const =0 ;






    /**
     * Write combined field MASTER_MODEM_NUM_DL_SAMPLES at 0x610 bits [20..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_masterModemNumDlSamples(FpgaVal value) =0 ;






    /**
     * Read combined register MASTER_MODEM_NUM_DL_SAMPLES at 0x610 bits [20..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_masterModemNumDlSamples() const =0 ;






    /**
     * Write combined field MASTER_MODEM_NUM_DL_SAMPLES at 0x610 bits [20..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_masterModemNumDlSamples(FpgaVal value) =0 ;


    /**
     * Read combined register CFR_TABLE_CONTROL_BITS at 0x630 bits [5,3..2]
     * \return field value
     */
    virtual const FpgaVal read_cfrTableControlBits() const =0 ;






    /**
     * Write combined field CFR_TABLE_CONTROL_BITS at 0x630 bits [5,3..2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cfrTableControlBits(FpgaVal value) =0 ;






    /**
     * Read combined register CFR_TABLE_CONTROL_BITS at 0x630 bits [5,3..2]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cfrTableControlBits() const =0 ;






    /**
     * Write combined field CFR_TABLE_CONTROL_BITS at 0x630 bits [5,3..2]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cfrTableControlBits(FpgaVal value) =0 ;


    /**
     * Read combined register MIMO_OFFSET at 0xd18 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_mimoOffset() const =0 ;






    /**
     * Write combined field MIMO_OFFSET at 0xd18 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_mimoOffset(FpgaVal value) =0 ;






    /**
     * Read combined register MIMO_OFFSET at 0xd18 bits [19..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_mimoOffset() const =0 ;






    /**
     * Write combined field MIMO_OFFSET at 0xd18 bits [19..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_mimoOffset(FpgaVal value) =0 ;



};


} /* namespace Mplane */

#endif /* _ISYSTEM_REGS_DEF_H_ */
