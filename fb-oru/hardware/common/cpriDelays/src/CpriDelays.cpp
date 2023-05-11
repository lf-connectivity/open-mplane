/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriDelays.h
 * \brief     CPRI delay reporting
 *
 *
 */

#include <memory>

#include "ICpri.h"
#include "ICpriCore.h"
#include "IHardwareSettings.h"

#include "Delay.h"
#include "IFpgaMgr.h"

#include "CpriDelays.h"

namespace Mplane
{

static const float LineRateMHz[] = {
	0.0,
	614.4,
	1228.8,
	2457.6,
	3072.0,
	4915.2,
	6144.0,
	9830.4,
	10137.6
};

CpriDelays::CpriDelays() : mT2aFixedDelay(0), mTa3FixedDelay(0), mLineRateMHz(0)
{
}

const Delay CpriDelays::getCpriDlDelay(unsigned int fibre)
{
    Delay cpriDlDelay;

    CoreDelays coreDelays = getCoreDelays(fibre);

    auto fpga(IFpgaMgr::getIFpgaFibreRegs()) ;
    unsigned int DlBufferDelayReg = IFpgaMgr::getIFpgaIqRegs()->read_dlDelay(fibre);
    Delay DlBufferDelay(DlBufferDelayReg/0.24576, Delay::NS);

    unsigned int CdcFifoDelayReg = fpga->read_cdcfifoDelay(fibre);
    float CdcFifoDelay = (CdcFifoDelayReg*0.3125); // 40/128
    Delay cdcFifo(CdcFifoDelay, Delay::UI, mLineRateMHz);

        // Work out what Tgtprx is with out Tbarrel for reporting
    Delay TgtprxLessTbarrel(coreDelays.Tgtprx - coreDelays.Tbarrel);

    cpriDlDelay = coreDelays.Tcorerx + coreDelays.Tgtprx + mT2aFixedDelay + cdcFifo + DlBufferDelay;

    std::cout << "getCpriDlDelay : Fibre " << fibre << std::endl;
    std::cout << "cpriDlDelay        = " << cpriDlDelay.get(Delay::NS) << " ns" << std::endl;
    std::cout << "coreDelays.Tcorerx = " << coreDelays.Tcorerx << " = " << coreDelays.Tcorerx.get(Delay::NS) << " ns" << std::endl;
    std::cout << "coreDelays.Tgtprx  = " << TgtprxLessTbarrel << " = " << TgtprxLessTbarrel.get(Delay::NS) << " ns"<< std::endl;
    std::cout << "T2aFixedDelay      = " << mT2aFixedDelay << " = " << mT2aFixedDelay.get(Delay::NS) << " ns"<< std::endl;
    std::cout << "coreDelays.Tbarrel = " << coreDelays.Tbarrel << " = " << coreDelays.Tbarrel.get(Delay::NS) << " ns"<< std::endl;

    // Only add the barrel shift value if its rate 8. All other rates already include this and we don't want to double report it.
    std::shared_ptr<const IHardwareSettings> etnaHardwareSettings( IHardwareSettings::getInstance() );
	if (etnaHardwareSettings->getCpriRateCapablity() == IHardwareSettings::RATE8_CAPABLE)
	{
		cpriDlDelay += coreDelays.Tbarrel;

	}

    std::cout << "cdcFifo             = " << cdcFifo << " = " << cdcFifo.get(Delay::NS) << " ns; raw = " << CdcFifoDelayReg << std::endl;
    std::cout << "DlBufferDelay       = " << DlBufferDelay << "; raw value = " << DlBufferDelayReg << std::endl;
    std::cout << std::endl;

    return cpriDlDelay;;
}

const Delay CpriDelays::getCpriUlDelay(unsigned int fibre)
{
    Delay cpriUlDelay;

    CoreDelays coreDelays = getCoreDelays(fibre);

	auto fpga(IFpgaMgr::getIFpgaIqRegs()) ;
    unsigned int UlBufferDelayReg = fpga->read_ulDelayActual(fibre);
    Delay UlBufferDelay(UlBufferDelayReg/0.24576, Delay::NS);

    cpriUlDelay = coreDelays.Tcoretx + coreDelays.Tgtptx + mTa3FixedDelay + UlBufferDelay;

    std::cout << "getCpriUlDelay : Fibre " << fibre << std::endl;
    std::cout << "cpriUlDelay        = " << cpriUlDelay.get(Delay::NS) << " ns" << std::endl;
    std::cout << "coreDelays.Tcoretx = " << coreDelays.Tcoretx << " = " << coreDelays.Tcoretx.get(Delay::NS) << " ns"<< std::endl;
    std::cout << "coreDelays.Tgtptx  = " << coreDelays.Tgtptx << " = " << coreDelays.Tgtptx.get(Delay::NS) << " ns"<< std::endl;
    std::cout << "Ta3FixedDelay      = " << mTa3FixedDelay << " = " << mTa3FixedDelay.get(Delay::NS) << " ns"<< std::endl;
    std::cout << "UlBufferDelay      = " << UlBufferDelay << "; raw value = " << UlBufferDelayReg << std::endl;
    std::cout << std::endl;

    return cpriUlDelay;
}

const Delay CpriDelays::getCpriFrameRxDelay(unsigned int fibre)
{
    Delay cpriFrameRxDelay;

    CoreDelays coreDelays = getCoreDelays(fibre);

	auto fpga(IFpgaMgr::getIFpgaFibreRegs()) ;
    unsigned int CdcFifoDelayReg = fpga->read_cdcfifoDelay(fibre);
    float CdcFifoDelay = (CdcFifoDelayReg*0.3125); // 40/128
    Delay cdcFifo(CdcFifoDelay, Delay::UI, mLineRateMHz);

    cpriFrameRxDelay = coreDelays.Tcorerx + coreDelays.Tgtprx + cdcFifo;

    // Work out what Tgtprx is with out Tbarrel for reporting
    Delay TgtprxLessTbarrel(coreDelays.Tgtprx - coreDelays.Tbarrel);

    std::cout << "getCpriFrameRxDelay : Fibre " << fibre << std::endl;
    std::cout << "CpriFrameRxDelay   = " << cpriFrameRxDelay.get(Delay::NS) << " ns" << std::endl;
	std::cout << "coreDelays.Tcorerx = " << coreDelays.Tcorerx << " = " << coreDelays.Tcorerx.get(Delay::NS) << " ns" << std::endl;
	std::cout << "coreDelays.Tgtprx  = " << TgtprxLessTbarrel << " = " << TgtprxLessTbarrel.get(Delay::NS) << " ns"<< std::endl;
	std::cout << "coreDelays.Tbarrel = " << coreDelays.Tbarrel << " = " << coreDelays.Tbarrel.get(Delay::NS) << " ns"<< std::endl;

	std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() );
	if (hardwareSettings->getCpriRateCapablity() == IHardwareSettings::RATE8_CAPABLE)
	{
		cpriFrameRxDelay += coreDelays.Tbarrel;
	}

	std::cout << "cdcFifo             = " << cdcFifo << " = " << cdcFifo.get(Delay::NS) << " ns; raw = " << CdcFifoDelayReg << std::endl;
	std::cout << std::endl;

	return cpriFrameRxDelay;

}
const Delay CpriDelays::getCpriFrameTxDelay(unsigned int fibre)
{
    auto fpga(IFpgaMgr::getIFpgaFibreRegs()) ;
	unsigned int nodeBfnTxFrameDlyReg = fpga->read_nodeBfnTxFrameDly(fibre);

	float interimCalc = (((float)(nodeBfnTxFrameDlyReg * 1000))/245.76); // Convert from core clocks

	Delay cpriFrameTxDelay(interimCalc, Delay::NS);

	std::cout << "getCpriFrameTxDelay : Fibre " << fibre << std::endl;
	std::cout << "interimCalc =" << interimCalc << std::endl;
	std::cout << "cpriFrameTxDelay   = " << cpriFrameTxDelay.get(Delay::NS) << " ns; rawvalue = " << nodeBfnTxFrameDlyReg << std::endl;
	std::cout << std::endl;

	return cpriFrameTxDelay;
}

void CpriDelays::setCpriFrameTxDelay(unsigned int fibre, const Delay delay)
{
    auto fpga(IFpgaMgr::getIFpgaFibreRegs()) ;

	unsigned int NodeBfnTxFrameDly = std::ceil(((delay.get(Delay::NS) * 24576 ) / 100000)); // Convert into core clocks

	fpga->write_nodeBfnTxFrameDly(fibre, NodeBfnTxFrameDly);

	std::cout << "setCpriFrameTxDelay : Fibre " << fibre << std::endl;
	std::cout << "cpriFrameTxDelay   = " << delay.get(Delay::NS) << " ns; rawvalue = " << NodeBfnTxFrameDly << std::endl;
	std::cout << std::endl;
}

const Delay Mplane::CpriDelays::getAntUpDelay(unsigned int fibre)
{
    Delay antUpDelay;

    CoreDelays coreDelays = getCoreDelays(fibre);

	auto fpga(IFpgaMgr::getIFpgaIqRegs()) ;
    unsigned int UlBufferDelayReg = fpga->read_ulDelayActual(fibre);
    Delay UlBufferDelay(UlBufferDelayReg/0.24576, Delay::NS);

    antUpDelay = coreDelays.Tcoretx + coreDelays.Tgtptx + mTa3FixedDelay + UlBufferDelay;

    std::cout << "getCpriUlDelay : Fibre " << fibre << std::endl;
    std::cout << "cpriUlDelay        = " << antUpDelay.get(Delay::NS) << " ns" << std::endl;
    std::cout << "coreDelays.Tcoretx = " << coreDelays.Tcoretx << " = " << coreDelays.Tcoretx.get(Delay::NS) << " ns"<< std::endl;
    std::cout << "coreDelays.Tgtptx  = " << coreDelays.Tgtptx << " = " << coreDelays.Tgtptx.get(Delay::NS) << " ns"<< std::endl;
    std::cout << "Ta3FixedDelay      = " << mTa3FixedDelay << " = " << mTa3FixedDelay.get(Delay::NS) << " ns"<< std::endl;
    std::cout << "UlBufferDelay      = " << UlBufferDelay << "; raw value = " << UlBufferDelayReg << std::endl;
    std::cout << std::endl;

    return antUpDelay;
}

const Delay Mplane::CpriDelays::getAntDownDelay(unsigned int fibre)
{
	return 0;
}

void Mplane::CpriDelays::setSyncOffset(unsigned int fibre,	syncOffsetMasterSlave_T masterOrSlave)
{
	// Base class implementation does nothing.
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//##-------------------------------------------------------------------------------------------------------------------------------------
//#	See http://twiki.axisnt.co.uk/cgi-bin/twiki/view/Engineering/SwIfCommonBbIfCpri#Delay_Measurement_and_Compensati
//#
//#

//-------------------------------------------------------------------------------------------------
// Gets the various Xilinx core delays
//
CpriDelays::CoreDelays CpriDelays::getCoreDelays(unsigned fibre)
{
	//Update the line rate just in case it has changed.
	updateLineRate(fibre);

	auto fpga(IFpgaMgr::getIFpgaFibreRegs() ) ;

	unsigned barrelShiftReg = fpga->read_barrelShift(fibre) ;
	unsigned cdcDelayReg = fpga->read_cdcfifoDelay(fibre) ;
	unsigned txCdcDelayReg = fpga->read_txCdcFifoDelay(fibre) ;

	//##-----------------------------------------------------------------------------
	//#	The Tfifo, Toffset coarse and Tbarrel delays are provided by the FPGA as:
	//#
	//#		Tfifo	= CDC_FIFO_Delay * (rate8: 33/128; 10G: 40/128; 20/128)
	//#		Toffset coarse	= R21Hi:R21Lo * (rate8: 33/128; 10G: 40/128; 20/128)
	//#		Tbarrel	= Barrel_Shift
	//#
	// (see http://twiki.axisnt.co.uk/cgi-bin/twiki/view/Engineering/SwIfCommonBbIfCpri)
	//
	//#	GTP and CPRI Core Delay Values:
	//#	Delay Parameter 	Rate8			10Gbps Capable Core 	<10Gbps Capable Core
	//#	TGTPRX 				408.5UI			408.5UI + TBARREL 		210.5UI + TBARREL
	//#	TCORERX 			129UI			160UI 					80 UI
	//#	TGTPTX 				221.5UI			221.5UI 				113.75UI
	//#	TCORETX 			164UI			80UI 					40UI
	//#
	//# Tsum = Tgtprx + Tfifo + Tcorerx + Tcoretx + Tgtptx
	//#
    std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() );
    float ui = cdcDelayReg * static_cast<float>(hardwareSettings->getClockToUi()) ;
    Delay cdcDelay(DelayUnitUI::UNIT.to_ns(ui, mLineRateMHz));

    ui = txCdcDelayReg * static_cast<float>(hardwareSettings->getClockToUi()) ;
    Delay txCdcDelay(DelayUnitUI::UNIT.to_ns(ui, mLineRateMHz));

    Delay barrelShift(barrelShiftReg, Delay::UI, mLineRateMHz) ;

    CoreDelays coreDelays ;

	if (hardwareSettings->getCpriRateCapablity() == IHardwareSettings::RATE8_CAPABLE)
	{
		// Rate8 capable
		coreDelays.Tfifo = Delay(cdcDelay, Delay::UI) ;
		coreDelays.Ttxfifo = Delay(txCdcDelay, Delay::UI) ;
		coreDelays.Tbarrel = Delay(0.0) ;
		coreDelays.Tgtprx = Delay(408.50, Delay::UI, mLineRateMHz) ;
		coreDelays.Tcorerx = Delay(129.00, Delay::UI, mLineRateMHz) ;
		coreDelays.Tgtptx = Delay(221.50, Delay::UI, mLineRateMHz) ;
		coreDelays.Tcoretx = Delay(164.00, Delay::UI, mLineRateMHz) ;

		mT2aFixedDelay = Delay(231.00, Delay::UI, mLineRateMHz) + BASIC_FRAME ;
		mTa3FixedDelay = Delay(264.00, Delay::UI, mLineRateMHz) ;
	}
	else if (hardwareSettings->getCpriRateCapablity() == IHardwareSettings::RATE7_CAPABLE)
	{
		// 10Gb/s capable
		coreDelays.Tfifo = Delay(cdcDelay, Delay::UI) ;
		coreDelays.Ttxfifo = Delay(0.0) ;
		coreDelays.Tbarrel = barrelShift ;
		coreDelays.Tgtprx = Delay(408.50, Delay::UI, mLineRateMHz) + barrelShift ;
		coreDelays.Tcorerx = Delay(160.00, Delay::UI, mLineRateMHz) ;
		coreDelays.Tgtptx = Delay(221.50, Delay::UI, mLineRateMHz) ;
		coreDelays.Tcoretx = Delay(80.00, Delay::UI, mLineRateMHz) ;

		mT2aFixedDelay = Delay(280.00, Delay::UI, mLineRateMHz) + BASIC_FRAME ;
		mTa3FixedDelay = Delay(320.00, Delay::UI, mLineRateMHz) ;
	}
	else
	{
		coreDelays.Tfifo = Delay(cdcDelay, Delay::UI) ;
		coreDelays.Ttxfifo = Delay(0.0) ;
		coreDelays.Tbarrel = barrelShift ;
		coreDelays.Tgtprx = Delay(210.50, Delay::UI, mLineRateMHz) + barrelShift ;
		coreDelays.Tcorerx = Delay(80.00, Delay::UI, mLineRateMHz) ;
		coreDelays.Tgtptx = Delay(113.75, Delay::UI, mLineRateMHz) ;
		coreDelays.Tcoretx = Delay(40.00, Delay::UI, mLineRateMHz) ;

		mT2aFixedDelay = Delay(140.00, Delay::UI, mLineRateMHz) + BASIC_FRAME ;
		mTa3FixedDelay = Delay(160.00, Delay::UI, mLineRateMHz) ;
	}

	bool debug(true);

	if (debug)
	{
		std::cout << "Core Delays Fibre" << fibre << " @ " << mLineRateMHz <<
			" : Tfifo " << coreDelays.Tfifo <<
			" : Ttxfifo " << coreDelays.Ttxfifo <<
			" : Tbarrel " << coreDelays.Tbarrel <<
			" : Tgtprx " << coreDelays.Tgtprx <<
			" : Tcorerx " << coreDelays.Tcorerx <<
			" : Tgtptx " << coreDelays.Tgtptx <<
			" : Tcoretx " << coreDelays.Tcoretx <<
			" : T2aFixed " << mT2aFixedDelay <<
			" : Ta3Fixed " << mTa3FixedDelay <<
			std::endl ;
	}

	return coreDelays ;
}

void Mplane::CpriDelays::updateLineRate(unsigned int fibre)
{
	// Get the line rate
	std::shared_ptr<ICpri> cpri( ICpri::getInterface() ) ;
	std::shared_ptr<ICpriCore> cpriCore(cpri->getPortCore(fibre)) ;
	ICpriCore::LineRate_t lineRate(cpriCore->getCurrentLineRate()) ;

	mLineRateMHz = LineRateMHz[lineRate];
}

}
