/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhFaults.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */



#include "IFaultsList.h"

#include "RrhFaults.h"
#include "IRadio.h"

#include "SynthClockFault.h"

#include "Cpri0LossOfFrameFaultMajor.h"
#include "Cpri0LossOfSignalFaultMajor.h"
#include "Cpri0RemoteAlarmIndFaultMajor.h"
#include "Cpri0SapDefectIndFaultMajor.h"

#include "Cpri1LossOfFrameFaultMajor.h"
#include "Cpri1LossOfSignalFaultMajor.h"
#include "Cpri1RemoteAlarmIndFaultMajor.h"
#include "Cpri1SapDefectIndFaultMajor.h"

#include "DpdPllLockFaultMajor.h"
#include "TxPllLockFaultMajor.h"
#include "RxPllLockFaultMajor.h"
#include "RefPllLockFaultMajor.h"

#include "TxOverPowerFaultMajor.h"
#include "TxOverPowerFaultMinor.h"
#include "TxUnderPowerFaultMinor.h"

#include "DpdTxFaultMajor.h"
#include "DpdTxFaultMinor.h"
#include "PclTxConvergenceFaultMajor.h"
#include "PclTxOverPowerFaultMajor.h"
#include "PopTripTxFaultMajor.h"
#include "SrlTxFaultMajor.h"
#include "HeartBeatFaultMajor.h"
#include "VswrTxFaultMajor.h"
#include "TxPowerMeasurementFaultMajor.h"

#include "BoardTxOverTemperatureFaultMajor.h"
#include "PaOverTemperatureFaultMajor.h"
#include "BoardTxOverTemperatureFaultMinor.h"
#include "PaOverTemperatureFaultMinor.h"
#include "BoardTxUnderTemperatureFaultMajor.h"
#include "PaUnderTemperatureFaultMajor.h"

/***********************************************************************************
 *
 * FOR THE MOMENT WE WILL ADD THE EXISTING FAULT OWNERS BUT THE EXISTING ARCHITECTURE
 * NEEDS TO CHANGE. ANY OBJECT SHOULD BE ABLE TO BE ASSIGNED AS A FAULT OWNER AND
 * THE FAULTS SHOULD BE UPDATED IN THEIR CONTEXT AND NOT FORCED THROUGH A FAULT SERVICE.
 *
 * FOR EXAMPLE THE CPRI FAULTS SHOULD BE OWNED AND RAISED BY THE  CPRI CONTROL SERVICE.
 *
 ***********************************************************************************/

#include "DpdPllLockMajorFaultOwner.h"
#include "RxPllLockMajorFaultOwner.h"
#include "TxPllLockMajorFaultOwner.h"
#include "RefPllLockMajorFaultOwner.h"

#include "TxOverPowerMajorFaultOwner.h"
#include "TxOverPowerMinorFaultOwner.h"
#include "TxUnderPowerMinorFaultOwner.h"

#include "PclTxMajorFaultOwner.h"
#include "PopTripMajorFaultOwner.h"
#include "SrlMajorFaultOwner.h"

#include "OverTempMajorFaultOwner.h"
#include "OverTempMinorFaultOwner.h"
#include "UnderTempMajorFaultOwner.h"
#include "HeartBeatMajorFaultOwner.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
Mplane::RrhFaults::RrhFaults():
        mFaultsList(IFaultsList::getInstance())
{

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                                 //
    // FAULT IDS ARE ASSIGNED IN THE ORDER OF FAULTS CREATION. IF NEW FAULTS ARE REQUIRED THEY SHOULD  //
    // BE ADDED TO THE END OF THIS LIST.                                                               //
    //                                                                                                 //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

                                                                                                        // Fault ID
    mSynthClockFault = make_fault<SynthClockFault>();                                                   //1

    // The Cpri faults are owned and updated by the Cpri Port Handler
    mCpri0LossOfSignalFaultMajor = make_fault<Cpri0LossOfSignalFaultMajor>();                           //2
    mCpri0LossOfFrameFaultMajor = make_fault<Cpri0LossOfFrameFaultMajor>();                             //3
    mCpri0RemoteAlarmIndicationFaultMajor = make_fault<Cpri0RemoteAlarmIndicationFaultMajor>();         //4
    mCpri0SapDefectIndFaultMajor = make_fault<Cpri0SapDefectIndFaultMajor>();							//5

    // The Cpri faults are owned and updated by the Cpri Port Handler
    mCpri1LossOfSignalFaultMajor = make_fault<Cpri1LossOfSignalFaultMajor>();                           //6
    mCpri1LossOfFrameFaultMajor = make_fault<Cpri1LossOfFrameFaultMajor>();                             //7
    mCpri1RemoteAlarmIndicationFaultMajor = make_fault<Cpri1RemoteAlarmIndicationFaultMajor>();         //8
    mCpri1SapDefectIndFaultMajor = make_fault<Cpri1SapDefectIndFaultMajor>();

    // cppcheck-suppress useInitializationList
    mBoardTxUnderTemperatureFaultMajor.push_back( make_fault<BoardTx1UnderTemperatureFaultMajor>());             //9
    // cppcheck-suppress useInitializationList
    mBoardTxUnderTemperatureFaultMajor.push_back( make_fault<BoardTx2UnderTemperatureFaultMajor>());             //10
    // cppcheck-suppress useInitializationList
    mBoardTxUnderTemperatureFaultMajor.push_back( make_fault<BoardTx3UnderTemperatureFaultMajor>());             //11
    // cppcheck-suppress useInitializationList
    mBoardTxUnderTemperatureFaultMajor.push_back( make_fault<BoardTx4UnderTemperatureFaultMajor>());             //12
    // cppcheck-suppress useInitializationList
    mPaUnderTemperatureFaultMajor.push_back( make_fault<Pa1UnderTemperatureFaultMajor>());                       //13
    // cppcheck-suppress useInitializationList
    mPaUnderTemperatureFaultMajor.push_back( make_fault<Pa2UnderTemperatureFaultMajor>());                       //14
    // cppcheck-suppress useInitializationList
    mPaUnderTemperatureFaultMajor.push_back( make_fault<Pa3UnderTemperatureFaultMajor>());                       //15
    // cppcheck-suppress useInitializationList
    mPaUnderTemperatureFaultMajor.push_back( make_fault<Pa4UnderTemperatureFaultMajor>());                       //16

    std::shared_ptr<IFaultOwner> underTempMajorFaultOwner(make_faultOwner<UnderTempMajorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mBoardTxOverTemperatureFaultMinor.push_back( make_fault<BoardTx1OverTemperatureFaultMinor>());               //17
    // cppcheck-suppress useInitializationList
    mBoardTxOverTemperatureFaultMinor.push_back( make_fault<BoardTx2OverTemperatureFaultMinor>());               //18
    // cppcheck-suppress useInitializationList
    mBoardTxOverTemperatureFaultMinor.push_back( make_fault<BoardTx3OverTemperatureFaultMinor>());               //19
    // cppcheck-suppress useInitializationList
    mBoardTxOverTemperatureFaultMinor.push_back( make_fault<BoardTx4OverTemperatureFaultMinor>());               //20
    // cppcheck-suppress useInitializationList
    mPaOverTemperatureFaultMinor.push_back( make_fault<Pa1OverTemperatureFaultMinor>());                         //21
    // cppcheck-suppress useInitializationList
    mPaOverTemperatureFaultMinor.push_back( make_fault<Pa2OverTemperatureFaultMinor>());                         //22
    // cppcheck-suppress useInitializationList
    mPaOverTemperatureFaultMinor.push_back( make_fault<Pa3OverTemperatureFaultMinor>());                         //23
    // cppcheck-suppress useInitializationList
    mPaOverTemperatureFaultMinor.push_back( make_fault<Pa4OverTemperatureFaultMinor>());                         //24

    std::shared_ptr<IFaultOwner> overTempMinorFaultOwner(make_faultOwner<OverTempMinorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mBoardTxOverTemperatureFaultMajor.push_back( make_fault<BoardTx1OverTemperatureFaultMajor>());               //25
    // cppcheck-suppress useInitializationList
    mBoardTxOverTemperatureFaultMajor.push_back( make_fault<BoardTx2OverTemperatureFaultMajor>());               //26
    // cppcheck-suppress useInitializationList
    mBoardTxOverTemperatureFaultMajor.push_back( make_fault<BoardTx3OverTemperatureFaultMajor>());               //27
    // cppcheck-suppress useInitializationList
    mBoardTxOverTemperatureFaultMajor.push_back( make_fault<BoardTx4OverTemperatureFaultMajor>());               //28
    // cppcheck-suppress useInitializationList
    mPaOverTemperatureFaultMajor.push_back( make_fault<Pa1OverTemperatureFaultMajor>());                         //29
    // cppcheck-suppress useInitializationList
    mPaOverTemperatureFaultMajor.push_back( make_fault<Pa2OverTemperatureFaultMajor>());                         //30
    // cppcheck-suppress useInitializationList
    mPaOverTemperatureFaultMajor.push_back( make_fault<Pa3OverTemperatureFaultMajor>());                         //31
    // cppcheck-suppress useInitializationList
    mPaOverTemperatureFaultMajor.push_back( make_fault<Pa4OverTemperatureFaultMajor>());                         //32

    std::shared_ptr<IFaultOwner> overTempMajorFaultOwner(make_faultOwner<OverTempMajorFaultOwner>()) ;


    // cppcheck-suppress useInitializationList
    mRxPllLockFaultMajor = make_fault<RxPllLockFaultMajor>();                                           //33

    std::shared_ptr<IFaultOwner> rxPllLockMajorFaultOwner(make_faultOwner<RxPllLockMajorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mTxPllLockFaultMajor = make_fault<TxPllLockFaultMajor>();                                           //34

    std::shared_ptr<IFaultOwner> txPllLockMajorFaultOwner(make_faultOwner<TxPllLockMajorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mDpdPllLockFaultMajor = make_fault<DpdPllLockFaultMajor>();                                         //35

    std::shared_ptr<IFaultOwner> dpdPllLockMajorFaultOwner(make_faultOwner<DpdPllLockMajorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mRefPllLockFaultMajor = make_fault<RefPllLockFaultMajor>();                                         //36

    std::shared_ptr<IFaultOwner> refPllLockMajorFaultOwner(make_faultOwner<RefPllLockMajorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mTxUnderPowerFaultMinor.push_back( make_fault<Tx1UnderPowerFaultMinor>());                                   //37
    // cppcheck-suppress useInitializationList
    mTxUnderPowerFaultMinor.push_back( make_fault<Tx2UnderPowerFaultMinor>());                                   //38
    // cppcheck-suppress useInitializationList
    mTxUnderPowerFaultMinor.push_back( make_fault<Tx3UnderPowerFaultMinor>());                                   //39
    // cppcheck-suppress useInitializationList
    mTxUnderPowerFaultMinor.push_back( make_fault<Tx4UnderPowerFaultMinor>());                                   //40

    std::shared_ptr<IFaultOwner> txUnderPowerMinorFaultOwner(make_faultOwner<TxUnderPowerMinorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mTxOverPowerFaultMinor.push_back( make_fault<Tx1OverPowerFaultMinor>());                                     //41
    // cppcheck-suppress useInitializationList
    mTxOverPowerFaultMinor.push_back( make_fault<Tx2OverPowerFaultMinor>());                                     //42
    // cppcheck-suppress useInitializationList
    mTxOverPowerFaultMinor.push_back( make_fault<Tx3OverPowerFaultMinor>());                                     //43
    // cppcheck-suppress useInitializationList
    mTxOverPowerFaultMinor.push_back( make_fault<Tx4OverPowerFaultMinor>());                                     //44

    std::shared_ptr<IFaultOwner> txOverPowerMinorFaultOwner(make_faultOwner<TxOverPowerMinorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mTxOverPowerFaultMajor.push_back( make_fault<Tx1OverPowerFaultMajor>());                                     //45
    // cppcheck-suppress useInitializationList
    mTxOverPowerFaultMajor.push_back( make_fault<Tx2OverPowerFaultMajor>());                                     //46
    // cppcheck-suppress useInitializationList
    mTxOverPowerFaultMajor.push_back( make_fault<Tx3OverPowerFaultMajor>());                                     //47
    // cppcheck-suppress useInitializationList
    mTxOverPowerFaultMajor.push_back( make_fault<Tx4OverPowerFaultMajor>());                                     //48

    std::shared_ptr<IFaultOwner> txOverPowerMajorFaultOwner(make_faultOwner<TxOverPowerMajorFaultOwner>()) ;


    // The PCL faults are owned and updated by the TxService PCL state machine objects.
    // cppcheck-suppress useInitializationList
    mPclTxConvergenceFaultMajor.push_back( make_fault<PclTx1ConvergenceFaultMajor>());                           //49
    // cppcheck-suppress useInitializationList
    mPclTxConvergenceFaultMajor.push_back( make_fault<PclTx2ConvergenceFaultMajor>());                           //50
    // cppcheck-suppress useInitializationList
    mPclTxConvergenceFaultMajor.push_back( make_fault<PclTx3ConvergenceFaultMajor>());                           //51
    // cppcheck-suppress useInitializationList
    mPclTxConvergenceFaultMajor.push_back( make_fault<PclTx4ConvergenceFaultMajor>());                           //52
    // cppcheck-suppress useInitializationList
    mPclTxOverPowerFaultMajor.push_back( make_fault<PclTx1OverPowerFaultMajor>());                               //53
    // cppcheck-suppress useInitializationList
    mPclTxOverPowerFaultMajor.push_back( make_fault<PclTx2OverPowerFaultMajor>());                               //54
    // cppcheck-suppress useInitializationList
    mPclTxOverPowerFaultMajor.push_back( make_fault<PclTx3OverPowerFaultMajor>());                               //55
    // cppcheck-suppress useInitializationList
    mPclTxOverPowerFaultMajor.push_back( make_fault<PclTx4OverPowerFaultMajor>());                               //56

    // cppcheck-suppress useInitializationList
    mPopTripTxFaultMajor.push_back( make_fault<PopTripTx1FaultMajor>());                                         //57
    // cppcheck-suppress useInitializationList
    mPopTripTxFaultMajor.push_back( make_fault<PopTripTx2FaultMajor>());                                         //58
    // cppcheck-suppress useInitializationList
    mPopTripTxFaultMajor.push_back( make_fault<PopTripTx3FaultMajor>());                                         //59
    // cppcheck-suppress useInitializationList
    mPopTripTxFaultMajor.push_back( make_fault<PopTripTx4FaultMajor>());                                         //60

    std::shared_ptr<IFaultOwner> popTripMajorFaultOwner(make_faultOwner<PopTripMajorFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mSrlTxFaultMajor.push_back(make_fault<SrlTx1FaultMajor>());                                                 //61
    // cppcheck-suppress useInitializationList
    mSrlTxFaultMajor.push_back(make_fault<SrlTx2FaultMajor>());                                                 //62
    // cppcheck-suppress useInitializationList
    mSrlTxFaultMajor.push_back(make_fault<SrlTx3FaultMajor>());                                                 //63
    // cppcheck-suppress useInitializationList
    mSrlTxFaultMajor.push_back(make_fault<SrlTx4FaultMajor>());                                                 //64

    std::shared_ptr<IFaultOwner> srlMajorFaultOwner(make_faultOwner<SrlMajorFaultOwner>()) ;

    // The Vswr faults are owned and updated by the Vswr Monitor
    // cppcheck-suppress useInitializationList
    mVswrTxFaultMajor.push_back(make_fault<VswrTx1FaultMajor>());                                               //65
    // cppcheck-suppress useInitializationList
    mVswrTxFaultMajor.push_back(make_fault<VswrTx2FaultMajor>());                                               //66
    // cppcheck-suppress useInitializationList
    mVswrTxFaultMajor.push_back(make_fault<VswrTx3FaultMajor>());                                               //67
    // cppcheck-suppress useInitializationList
    mVswrTxFaultMajor.push_back(make_fault<VswrTx4FaultMajor>());                                               //68

    // The DPD faults are owned and updated by the specific DPD Service Alarm Client
    // cppcheck-suppress useInitializationList
    mDpdTxFaultMajor.push_back(make_fault<DpdTx1FaultMajor>());                                                 //69
    // cppcheck-suppress useInitializationList
    mDpdTxFaultMajor.push_back(make_fault<DpdTx2FaultMajor>());                                                 //70
    // cppcheck-suppress useInitializationList
    mDpdTxFaultMajor.push_back(make_fault<DpdTx3FaultMajor>());                                                 //71
    // cppcheck-suppress useInitializationList
    mDpdTxFaultMajor.push_back(make_fault<DpdTx4FaultMajor>());                                                 //72
    // cppcheck-suppress useInitializationList
    mDpdTxFaultMinor.push_back(make_fault<DpdTx1FaultMinor>());                                                 //73
    // cppcheck-suppress useInitializationList
    mDpdTxFaultMinor.push_back(make_fault<DpdTx2FaultMinor>());                                                 //74
    // cppcheck-suppress useInitializationList
    mDpdTxFaultMinor.push_back(make_fault<DpdTx3FaultMinor>());                                                 //75
    // cppcheck-suppress useInitializationList
    mDpdTxFaultMinor.push_back(make_fault<DpdTx4FaultMinor>());                                                 //76

    // cppcheck-suppress useInitializationList
    mHeartBeatFaultMajor = make_fault<HeartBeatFaultMajor>();                                           //77

    std::shared_ptr<IFaultOwner> heartBeatMajorFaultOwner(make_faultOwner<HeartBeatFaultOwner>()) ;

    // cppcheck-suppress useInitializationList
    mTxPowerMeasurementFaultMajor.push_back(make_fault<Tx1PowerMeasurementFaultMajor>());                       //78
    // cppcheck-suppress useInitializationList
    mTxPowerMeasurementFaultMajor.push_back(make_fault<Tx2PowerMeasurementFaultMajor>());                       //79
    // cppcheck-suppress useInitializationList
    mTxPowerMeasurementFaultMajor.push_back(make_fault<Tx3PowerMeasurementFaultMajor>());                       //80
    // cppcheck-suppress useInitializationList
    mTxPowerMeasurementFaultMajor.push_back(make_fault<Tx4PowerMeasurementFaultMajor>());                       //81

}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getSystemSynthFault( void )
{
	return mSynthClockFault;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getCpriLossOfSignalFaultMajor(int index)
{
    if( index < 0 || index > 1 )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
        if( index == 0 )
            return mCpri0LossOfSignalFaultMajor;
        else
            return mCpri1LossOfSignalFaultMajor;
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getCpriLossOfFrameFaultMajor(int index)
{
    if( index < 0 || index > 1 )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
        if( index == 0 )
            return mCpri0LossOfFrameFaultMajor;
        else
            return mCpri1LossOfFrameFaultMajor;
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getCpriRemoteAlarmIndicationFaultMajor(int index)
{
    if( index < 0 || index > 1 )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
        if( index == 0 )
            return mCpri0RemoteAlarmIndicationFaultMajor;
        else
            return mCpri1RemoteAlarmIndicationFaultMajor;
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getCpriSapDefectIndFaultMajor(int index)
{
    if( index < 0 || index > 1 )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
        if( index == 0 )
            return mCpri0SapDefectIndFaultMajor;
        else
            return mCpri1SapDefectIndFaultMajor;
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getVswrMajor(int index)
{
	int numPorts = IRadioFactory::getInterface()->getNumberOfTxPorts();
    if( index < 0 || index >= numPorts )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
    	return mVswrTxFaultMajor[index];
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getDpdTxFaultMajor(int index)
{
	int numPorts = IRadioFactory::getInterface()->getNumberOfTxPorts();
    if( index < 0 || index >= numPorts )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
    	return mDpdTxFaultMajor[index];
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getDpdTxFaultMinor(int index)
{
	int numPorts = IRadioFactory::getInterface()->getNumberOfTxPorts();
    if( index < 0 || index >= numPorts )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
    	return mDpdTxFaultMinor[index];
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getPclConvergenceMajor( int index )
{
	int numPorts = IRadioFactory::getInterface()->getNumberOfTxPorts();
    if( index < 0 || index >= numPorts )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
    	return mPclTxConvergenceFaultMajor[index];
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getPclOverPowerMajor( int index )
{
	int numPorts = IRadioFactory::getInterface()->getNumberOfTxPorts();
    if( index < 0 || index >= numPorts )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
    	return mPclTxOverPowerFaultMajor[index];
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFault> Mplane::RrhFaults::getPclPowerMeasurementMajor( int index )
{
	int numPorts = IRadioFactory::getInterface()->getNumberOfTxPorts();
    if( index < 0 || index >= numPorts )
    {
        std::invalid_argument e("Index out of range");
        throw e;
    }
    else
    {
    	return mTxPowerMeasurementFaultMajor[index];
    }
}
