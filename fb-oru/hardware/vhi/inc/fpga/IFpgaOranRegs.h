#ifndef _IORAN_REGS_DEF_H_
#define _IORAN_REGS_DEF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaOranRegs.h
 * \brief     FPGA Oran registers virtual interface
 *
 *
 * \details   This file defines the FPGA Oran registers.
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

class IFpgaOranRegs : public virtual IFpgaRegs
{
public:
	IFpgaOranRegs() {}
	virtual ~IFpgaOranRegs(void) {} ;

    /** \brief  Does FPGA have a ORAN registers block
     *
     *  \return true if the FPGA instance does actually support a Oran registers block
     */
    virtual bool hasOranRegisters(void) =0 ;

    /*! \brief  Get base address
     *
     *  Get the base address of the Oran registers (if supported)
     *
     *  \return base address of Oran registers; 0 if not supported
     */
    virtual UINT32 getOranBlockAddr(void) =0 ;

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
     * Read field UDP_DL_DEST_PORT at 0x40060 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_udpDlDestPort(unsigned fibre) const =0 ;

    /**
     * Write field UDP_DL_DEST_PORT at 0x40060 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_udpDlDestPort(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field UDP_DL_DEST_PORT at 0x40060 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_udpDlDestPort(unsigned fibre) const =0 ;

    /**
     * Write field UDP_DL_DEST_PORT at 0x40060 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_udpDlDestPort(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field UDP_DL_DEST_PORT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_udpDlDestPort(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UDP_DEST_PORT_FILTER_ENABLE at 0x40062 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_udpDestPortFilterEnable(unsigned fibre) const =0 ;

    /**
     * Write field UDP_DEST_PORT_FILTER_ENABLE at 0x40062 bits [0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_udpDestPortFilterEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field UDP_DEST_PORT_FILTER_ENABLE at 0x40062 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_udpDestPortFilterEnable(unsigned fibre) const =0 ;

    /**
     * Write field UDP_DEST_PORT_FILTER_ENABLE at 0x40062 bits [0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_udpDestPortFilterEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field UDP_DEST_PORT_FILTER_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_udpDestPortFilterEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field DAISYCHAIN_ENABLE at 0x40200 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_daisychainEnable(unsigned fibre) const =0 ;

    /**
     * Write field DAISYCHAIN_ENABLE at 0x40200 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_daisychainEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field DAISYCHAIN_ENABLE at 0x40200 bits [8]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_daisychainEnable(unsigned fibre) const =0 ;

    /**
     * Write field DAISYCHAIN_ENABLE at 0x40200 bits [8]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_daisychainEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field DAISYCHAIN_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_daisychainEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CUPLANE_SRC_MAC_LO at 0x40800 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_cuplaneSrcMacLo(unsigned fibreiq) const =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_LO at 0x40800 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cuplaneSrcMacLo(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field CUPLANE_SRC_MAC_LO at 0x40800 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cuplaneSrcMacLo(unsigned fibreiq) const =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_LO at 0x40800 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cuplaneSrcMacLo(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cuplaneSrcMacLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CUPLANE_SRC_MAC_MID at 0x40802 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_cuplaneSrcMacMid(unsigned fibreiq) const =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_MID at 0x40802 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cuplaneSrcMacMid(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field CUPLANE_SRC_MAC_MID at 0x40802 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cuplaneSrcMacMid(unsigned fibreiq) const =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_MID at 0x40802 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cuplaneSrcMacMid(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_MID in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cuplaneSrcMacMid(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CUPLANE_SRC_MAC_HI at 0x40804 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_cuplaneSrcMacHi(unsigned fibreiq) const =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_HI at 0x40804 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cuplaneSrcMacHi(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field CUPLANE_SRC_MAC_HI at 0x40804 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cuplaneSrcMacHi(unsigned fibreiq) const =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_HI at 0x40804 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cuplaneSrcMacHi(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field CUPLANE_SRC_MAC_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cuplaneSrcMacHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RU_IP_ADDR_LO at 0x40808 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ruIpAddrLo(unsigned fibre) const =0 ;

    /**
     * Write field RU_IP_ADDR_LO at 0x40808 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ruIpAddrLo(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field RU_IP_ADDR_LO at 0x40808 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ruIpAddrLo(unsigned fibre) const =0 ;

    /**
     * Write field RU_IP_ADDR_LO at 0x40808 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ruIpAddrLo(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field RU_IP_ADDR_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ruIpAddrLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RU_IP_ADDR_HI at 0x4080a bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ruIpAddrHi(unsigned fibre) const =0 ;

    /**
     * Write field RU_IP_ADDR_HI at 0x4080a bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ruIpAddrHi(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field RU_IP_ADDR_HI at 0x4080a bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ruIpAddrHi(unsigned fibre) const =0 ;

    /**
     * Write field RU_IP_ADDR_HI at 0x4080a bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ruIpAddrHi(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field RU_IP_ADDR_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ruIpAddrHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PTP_DOMAIN_NUMBER at 0x40810 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpDomainNumber(unsigned fibre) const =0 ;

    /**
     * Write field PTP_DOMAIN_NUMBER at 0x40810 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ptpDomainNumber(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field PTP_DOMAIN_NUMBER at 0x40810 bits [7..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpDomainNumber(unsigned fibre) const =0 ;

    /**
     * Write field PTP_DOMAIN_NUMBER at 0x40810 bits [7..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ptpDomainNumber(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field PTP_DOMAIN_NUMBER in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ptpDomainNumber(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PTP_MASTER_PORT_ID0 at 0x40812 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpMasterPortID0(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID0 at 0x40812 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ptpMasterPortID0(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field PTP_MASTER_PORT_ID0 at 0x40812 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpMasterPortID0(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID0 at 0x40812 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ptpMasterPortID0(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID0 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ptpMasterPortID0(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PTP_MASTER_PORT_ID1 at 0x40814 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpMasterPortID1(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID1 at 0x40814 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ptpMasterPortID1(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field PTP_MASTER_PORT_ID1 at 0x40814 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpMasterPortID1(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID1 at 0x40814 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ptpMasterPortID1(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID1 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ptpMasterPortID1(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PTP_MASTER_PORT_ID2 at 0x40816 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpMasterPortID2(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID2 at 0x40816 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ptpMasterPortID2(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field PTP_MASTER_PORT_ID2 at 0x40816 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpMasterPortID2(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID2 at 0x40816 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ptpMasterPortID2(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID2 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ptpMasterPortID2(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PTP_MASTER_PORT_ID3 at 0x40818 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpMasterPortID3(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID3 at 0x40818 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ptpMasterPortID3(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field PTP_MASTER_PORT_ID3 at 0x40818 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpMasterPortID3(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID3 at 0x40818 bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ptpMasterPortID3(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID3 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ptpMasterPortID3(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PTP_MASTER_PORT_ID4 at 0x4081a bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpMasterPortID4(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID4 at 0x4081a bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ptpMasterPortID4(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field PTP_MASTER_PORT_ID4 at 0x4081a bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpMasterPortID4(unsigned fibre) const =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID4 at 0x4081a bits [15..0]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ptpMasterPortID4(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field PTP_MASTER_PORT_ID4 in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ptpMasterPortID4(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_READ_LO at 0x40820 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpRxTimestampFifoReadLo(unsigned fibre) const =0 ;


    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_READ_LO at 0x40820 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpRxTimestampFifoReadLo(unsigned fibre) const =0 ;




    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_READ_HI at 0x40822 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpRxTimestampFifoReadHi(unsigned fibre) const =0 ;


    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_READ_HI at 0x40822 bits [15..0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpRxTimestampFifoReadHi(unsigned fibre) const =0 ;




    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_EMPTY at 0x40824 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpRxTimestampFifoEmpty(unsigned fibre) const =0 ;


    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_EMPTY at 0x40824 bits [0]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpRxTimestampFifoEmpty(unsigned fibre) const =0 ;




    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_FULL at 0x40824 bits [1]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpRxTimestampFifoFull(unsigned fibre) const =0 ;


    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_FULL at 0x40824 bits [1]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpRxTimestampFifoFull(unsigned fibre) const =0 ;




    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_ENABLE at 0x40824 bits [15]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_ptpRxTimestampFifoEnable(unsigned fibre) const =0 ;

    /**
     * Write field PTP_RX_TIMESTAMP_FIFO_ENABLE at 0x40824 bits [15]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ptpRxTimestampFifoEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Read field PTP_RX_TIMESTAMP_FIFO_ENABLE at 0x40824 bits [15]
     * \param fibre
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpRxTimestampFifoEnable(unsigned fibre) const =0 ;

    /**
     * Write field PTP_RX_TIMESTAMP_FIFO_ENABLE at 0x40824 bits [15]
     * \param fibre
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ptpRxTimestampFifoEnable(unsigned fibre, FpgaVal value) =0 ;

    /**
     * Write field PTP_RX_TIMESTAMP_FIFO_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_ptpRxTimestampFifoEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CPLANE_VLAN_ENABLE at 0x70062 bits [4]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_cplaneVlanEnable(unsigned fibreiq) const =0 ;

    /**
     * Write field CPLANE_VLAN_ENABLE at 0x70062 bits [4]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cplaneVlanEnable(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field CPLANE_VLAN_ENABLE at 0x70062 bits [4]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cplaneVlanEnable(unsigned fibreiq) const =0 ;

    /**
     * Write field CPLANE_VLAN_ENABLE at 0x70062 bits [4]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cplaneVlanEnable(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field CPLANE_VLAN_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cplaneVlanEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UPLANE_VLAN_ENABLE at 0x70062 bits [5]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_uplaneVlanEnable(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_VLAN_ENABLE at 0x70062 bits [5]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_uplaneVlanEnable(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field UPLANE_VLAN_ENABLE at 0x70062 bits [5]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_uplaneVlanEnable(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_VLAN_ENABLE at 0x70062 bits [5]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_uplaneVlanEnable(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field UPLANE_VLAN_ENABLE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_uplaneVlanEnable(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field RTC_PC_ID at 0x70066 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_rtcPcId(unsigned fibreiq) const =0 ;

    /**
     * Write field RTC_PC_ID at 0x70066 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_rtcPcId(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field RTC_PC_ID at 0x70066 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_rtcPcId(unsigned fibreiq) const =0 ;

    /**
     * Write field RTC_PC_ID at 0x70066 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_rtcPcId(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field RTC_PC_ID in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_rtcPcId(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UPLANE_DEST_MAC_LO at 0x7006e bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_uplaneDestMacLo(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_DEST_MAC_LO at 0x7006e bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_uplaneDestMacLo(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field UPLANE_DEST_MAC_LO at 0x7006e bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_uplaneDestMacLo(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_DEST_MAC_LO at 0x7006e bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_uplaneDestMacLo(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field UPLANE_DEST_MAC_LO in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_uplaneDestMacLo(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UPLANE_DEST_MAC_MID at 0x70070 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_uplaneDestMacMid(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_DEST_MAC_MID at 0x70070 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_uplaneDestMacMid(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field UPLANE_DEST_MAC_MID at 0x70070 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_uplaneDestMacMid(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_DEST_MAC_MID at 0x70070 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_uplaneDestMacMid(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field UPLANE_DEST_MAC_MID in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_uplaneDestMacMid(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UPLANE_DEST_MAC_HI at 0x70072 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_uplaneDestMacHi(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_DEST_MAC_HI at 0x70072 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_uplaneDestMacHi(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field UPLANE_DEST_MAC_HI at 0x70072 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_uplaneDestMacHi(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_DEST_MAC_HI at 0x70072 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_uplaneDestMacHi(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field UPLANE_DEST_MAC_HI in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_uplaneDestMacHi(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CPLANE_VLAN_TAG at 0x7007c bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_cplaneVlanTag(unsigned fibreiq) const =0 ;

    /**
     * Write field CPLANE_VLAN_TAG at 0x7007c bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cplaneVlanTag(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field CPLANE_VLAN_TAG at 0x7007c bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cplaneVlanTag(unsigned fibreiq) const =0 ;

    /**
     * Write field CPLANE_VLAN_TAG at 0x7007c bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cplaneVlanTag(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field CPLANE_VLAN_TAG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cplaneVlanTag(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field UPLANE_VLAN_TAG at 0x7007e bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_uplaneVlanTag(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_VLAN_TAG at 0x7007e bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_uplaneVlanTag(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field UPLANE_VLAN_TAG at 0x7007e bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_uplaneVlanTag(unsigned fibreiq) const =0 ;

    /**
     * Write field UPLANE_VLAN_TAG at 0x7007e bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_uplaneVlanTag(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field UPLANE_VLAN_TAG in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_uplaneVlanTag(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field AIRFRAME_TS_LO at 0x70090 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_airframeTsLo(unsigned fibreiq) const =0 ;


    /**
     * Read field AIRFRAME_TS_LO at 0x70090 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_airframeTsLo(unsigned fibreiq) const =0 ;




    /**
     * Read field AIRFRAME_TS_HI at 0x70092 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_airframeTsHi(unsigned fibreiq) const =0 ;


    /**
     * Read field AIRFRAME_TS_HI at 0x70092 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_airframeTsHi(unsigned fibreiq) const =0 ;




    /**
     * Read field MAX_SLOT at 0x78070 bits [5..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_maxSlot(unsigned fibreiq) const =0 ;

    /**
     * Write field MAX_SLOT at 0x78070 bits [5..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_maxSlot(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field MAX_SLOT at 0x78070 bits [5..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_maxSlot(unsigned fibreiq) const =0 ;

    /**
     * Write field MAX_SLOT at 0x78070 bits [5..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_maxSlot(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field MAX_SLOT in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_maxSlot(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field MAX_SYMBOL at 0x78070 bits [13..8]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_maxSymbol(unsigned fibreiq) const =0 ;

    /**
     * Write field MAX_SYMBOL at 0x78070 bits [13..8]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_maxSymbol(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field MAX_SYMBOL at 0x78070 bits [13..8]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_maxSymbol(unsigned fibreiq) const =0 ;

    /**
     * Write field MAX_SYMBOL at 0x78070 bits [13..8]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_maxSymbol(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field MAX_SYMBOL in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_maxSymbol(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CP0_LENGTH at 0x78072 bits [10..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_cp0Length(unsigned fibreiq) const =0 ;

    /**
     * Write field CP0_LENGTH at 0x78072 bits [10..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cp0Length(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field CP0_LENGTH at 0x78072 bits [10..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cp0Length(unsigned fibreiq) const =0 ;

    /**
     * Write field CP0_LENGTH at 0x78072 bits [10..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cp0Length(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field CP0_LENGTH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cp0Length(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FFT_SIZE at 0x78072 bits [15..12]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_fftSize(unsigned fibreiq) const =0 ;

    /**
     * Write field FFT_SIZE at 0x78072 bits [15..12]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_fftSize(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field FFT_SIZE at 0x78072 bits [15..12]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_fftSize(unsigned fibreiq) const =0 ;

    /**
     * Write field FFT_SIZE at 0x78072 bits [15..12]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_fftSize(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field FFT_SIZE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_fftSize(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field CP1_LENGTH at 0x78074 bits [10..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_cp1Length(unsigned fibreiq) const =0 ;

    /**
     * Write field CP1_LENGTH at 0x78074 bits [10..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_cp1Length(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field CP1_LENGTH at 0x78074 bits [10..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_cp1Length(unsigned fibreiq) const =0 ;

    /**
     * Write field CP1_LENGTH at 0x78074 bits [10..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_cp1Length(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field CP1_LENGTH in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_cp1Length(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LTE_MODE at 0x78074 bits [12]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_lteMode(unsigned fibreiq) const =0 ;

    /**
     * Write field LTE_MODE at 0x78074 bits [12]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_lteMode(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field LTE_MODE at 0x78074 bits [12]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_lteMode(unsigned fibreiq) const =0 ;

    /**
     * Write field LTE_MODE at 0x78074 bits [12]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_lteMode(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field LTE_MODE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_lteMode(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field LAST_POSITIVE_TONE at 0x78076 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_lastPositiveTone(unsigned fibreiq) const =0 ;

    /**
     * Write field LAST_POSITIVE_TONE at 0x78076 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_lastPositiveTone(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field LAST_POSITIVE_TONE at 0x78076 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_lastPositiveTone(unsigned fibreiq) const =0 ;

    /**
     * Write field LAST_POSITIVE_TONE at 0x78076 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_lastPositiveTone(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field LAST_POSITIVE_TONE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_lastPositiveTone(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field FIRST_NEGATIVE_TONE at 0x78078 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_firstNegativeTone(unsigned fibreiq) const =0 ;

    /**
     * Write field FIRST_NEGATIVE_TONE at 0x78078 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_firstNegativeTone(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field FIRST_NEGATIVE_TONE at 0x78078 bits [15..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_firstNegativeTone(unsigned fibreiq) const =0 ;

    /**
     * Write field FIRST_NEGATIVE_TONE at 0x78078 bits [15..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_firstNegativeTone(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field FIRST_NEGATIVE_TONE in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_firstNegativeTone(FpgaVal* buff, FpgaVal value) =0 ;


    /**
     * Read field SUBCARRIER_SPACING at 0x7807a bits [3..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_subcarrierSpacing(unsigned fibreiq) const =0 ;

    /**
     * Write field SUBCARRIER_SPACING at 0x7807a bits [3..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_subcarrierSpacing(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Read field SUBCARRIER_SPACING at 0x7807a bits [3..0]
     * \param fibreiq
     * \return field value
     */
    virtual const FpgaVal read_nomutex_subcarrierSpacing(unsigned fibreiq) const =0 ;

    /**
     * Write field SUBCARRIER_SPACING at 0x7807a bits [3..0]
     * \param fibreiq
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_subcarrierSpacing(unsigned fibreiq, FpgaVal value) =0 ;

    /**
     * Write field SUBCARRIER_SPACING in 16-bit buffer
     * \param value field value
     * \return RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write_subcarrierSpacing(FpgaVal* buff, FpgaVal value) =0 ;



    /**
     * Read combined register RU_IP_ADDR at 0x4080a bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_ruIpAddr(unsigned fibre) const =0 ;






    /**
     * Write combined field RU_IP_ADDR at 0x4080a bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_ruIpAddr(unsigned fibre, FpgaVal value) =0 ;






    /**
     * Read combined register RU_IP_ADDR at 0x4080a bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ruIpAddr(unsigned fibre) const =0 ;






    /**
     * Write combined field RU_IP_ADDR at 0x4080a bits [31..0]
     * \param value field value
     * \return RT_OK if successful
     */
    virtual ReturnType::State write_nomutex_ruIpAddr(unsigned fibre, FpgaVal value) =0 ;


    /**
     * Read combined register PTP_RX_TIMESTAMP_FIFO_READ_DATA at 0x40822 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_ptpRxTimestampFifoReadData(unsigned fibre) const =0 ;







    /**
     * Read combined register PTP_RX_TIMESTAMP_FIFO_READ_DATA at 0x40822 bits [31..0]
     * \return field value
     */
    virtual const FpgaVal read_nomutex_ptpRxTimestampFifoReadData(unsigned fibre) const =0 ;




};


} /* namespace Mplane */

#endif /* _IORAN_REGS_DEF_H_ */
