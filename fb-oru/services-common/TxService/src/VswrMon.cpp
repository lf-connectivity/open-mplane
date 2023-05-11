/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      VswrMon.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "VswrMon.h"
#include "FaultOwner.h"
#include "ICommonRadioFaults.h"
#include "IRadio.h"
#include "ITxPort.h"



using namespace Mplane;


const int   Mplane::VswrMon::DEFAULT_PERIOD = 6;
const float Mplane::VswrMon::DEFAULT_THRESHOLD = 6.0f;
const int   Mplane::VswrMon::PERIOD_OFF = 0;
const float Mplane::VswrMon::THRESHOLD_OFF = 0.0f;
const float Mplane::VswrMon::MIN_DIGITAL_POWER = -45.0;
const float Mplane::VswrMon::MAX_DIGITAL_POWER_DIFF = 2.0;
const float Mplane::VswrMon::LOWER_DIGITAL_THRESHOLD = -49.0;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================
IVswr::vswrShutdownMode_T VswrMon::mShutdownMode(IVswr::vswrShutdownMode_T::automatic);

Mplane::VswrMon::VswrMon(int path):
             Loggable("Vswr", "TX"),
             mPath(path),
             mThreshold(DEFAULT_THRESHOLD),
             mPeriod(DEFAULT_PERIOD),
             mFaults(ICommonRadioFaults::getInstance()), // get interface to all supported radio fault
             mPeriodCount(0),
             mActive(false),
             mForward(0.0),
             mReverse(0.0),
             mFwdDigital(0.0),
             mRevDigital(0.0)
{
    mReturnLoss.setSize( mPeriod );
    std::vector<std::shared_ptr<ITxPort>> txPorts = ITxPortFactory::getPorts();
    mTxPort = txPorts[mPath];

    mVswrFaultOwner = std::shared_ptr<VswrFaultOwner>(new VswrFaultOwner( mPath )) ;
    mVswrFaultOwner->getFault()->addOwner( mVswrFaultOwner );       // don't do this inside cos of shared_ptr<this> problems

    mVswrFaultOwner->clear();

    mPcl = ITxPcl::getInstance( mPath );
}

Mplane::VswrMon::~VswrMon()
{
}

bool Mplane::VswrMon::setThreshold(Power threshold)
{
    mThreshold = threshold;
    return true;
}

bool Mplane::VswrMon::setPeriod(int seconds)
{
    mPeriod   = seconds;
    mReturnLoss.setSize( mPeriod );
    return true;
}

Power Mplane::VswrMon::getThreshold()
{
    return mThreshold;
}

int Mplane::VswrMon::getPeriod()
{
    return mPeriod;
}

Power Mplane::VswrMon::getReturnLoss()
{
    return mReturnLoss.get();
}

bool Mplane::VswrMon::isActive()
{
    return mActive;
}

bool Mplane::VswrMon::faultState()
{
    return  mVswrFaultOwner->getFault()->isFaultPresent();
}

void Mplane::VswrMon::processMeasurements()
{

    // going to TX on and we are not yet active clear the alarm if it's present.
    if( mTxPort->isTxOn() && mActive == false )
    {
        if( mVswrFaultOwner->getFault()->isFaultPresent() )
        {
            mVswrFaultOwner->clear();
        }
        mActive = true;
    }


    // only do VSWR monitoring when the TX is on, we've reached target Tx gain and it is
    // enabled through non-zero threshold and period.
    if( mTxPort->isTxOn() && mActive &&
            ( (mPcl->getState() ==  TxPclState::TRACK) || (mPcl->getState() ==  TxPclState::CONVERGE) ) &&
            mThreshold > THRESHOLD_OFF && mPeriod > PERIOD_OFF)
    {

        ReturnType::State fwdPowerOK = mTxPort->getFwdPower( mForward, mFwdDigital );
        ReturnType::State revPowerOK = mTxPort->getRevPower( mReverse, mRevDigital );

        if( (ReturnType::RT_OK == fwdPowerOK ) &&
            (ReturnType::RT_OK == revPowerOK ) )
        {
            if( ((mRevDigital - mFwdDigital) <= MAX_DIGITAL_POWER_DIFF) &&
                 (mRevDigital >= LOWER_DIGITAL_THRESHOLD)               &&
                 (mFwdDigital >= LOWER_DIGITAL_THRESHOLD) )

            {
                // Now includes that external filter loss compensation.
                Power returnLoss = ( (mForward - mReverse) + (mFwdDigital - mRevDigital) - ((Power)2 * (mTxPort->getExtFilterLoss())) );

                mReturnLoss.add(returnLoss);

                eventInfo( "VSWR PORT %d: RF FWD: %f, REV: %f - DIG FWD: %f, REV: %f - RET LOSS: %f, AVG RET LOSS %f, THRESH: %f - ALM %s",
                        mPath, mForward.get(), mReverse.get(), mFwdDigital.get(), mRevDigital.get(),
                        returnLoss.get(), mReturnLoss.get().get(), mThreshold.get(), mVswrFaultOwner->getFault()->getFaultPresentString().c_str() );

            }
            else
            {
                eventInfo( "VSWR PORT %d: DIG FWD: %f, REV: %f - Diff > 2.0dB or values < -49.0dB . Measurements ignored",
                        mPath, mFwdDigital.get(), mRevDigital.get() );
            }
        }
        else
        {
            eventInfo( "VSWR PORT %d: FWD or REV SRx bad measurement. Values ignored this time.", mPath );
        }

        // Have we reached the check period?
        if( ++mPeriodCount >= mPeriod )
        {
            mPeriodCount = 0;
            if( mReturnLoss.get() < mThreshold )  // is the return loss less than the threshold?
            {
                eventInfo( "VSWR PORT %d: FAULT RAISED after CHECK AVG RET LOSS %f, against THRESH: %f",
                        mPath, mReturnLoss.get().get(), mThreshold.get() );
                mVswrFaultOwner->set();
            }
            else
            {
                eventInfo( "VSWR PORT %d: FAULT CLEARED after CHECK AVG RET LOSS %f, against THRESH: %f",
                        mPath, mReturnLoss.get().get(), mThreshold.get() );
                mVswrFaultOwner->clear();
            }
        }

    }

    // if TX is off and we've been active then tidy things up for a restart
    if( mTxPort->isTxOn() == false && mActive == true )
    {
        mActive = false;
        mPeriodCount = 0;
    }
}

Mplane::VswrMon::VswrFaultOwner::VswrFaultOwner(int path):
        FaultOwner("Vswr"),
        mFault(ICommonRadioFaults::getInstance()->getVswrMajor(path))
{
}

std::shared_ptr<IFault> Mplane::VswrMon::VswrFaultOwner::getFault()
{
    return mFault;
}

void Mplane::VswrMon::VswrFaultOwner::set()
{
    mFault->setStatus( true );
}

void Mplane::VswrMon::VswrFaultOwner::clear()
{
    mFault->setStatus( false );
}

void Mplane::VswrMon::setShutdownMode(IVswr::vswrShutdownMode_T shutdownMode)
{
	VswrMon::setMode(shutdownMode);
}

IVswr::vswrShutdownMode_T Mplane::VswrMon::getShutdownMode()
{
	return VswrMon::getMode();
}

void Mplane::VswrMon::setMode(IVswr::vswrShutdownMode_T mode)
{
	//VswrMon::
	mShutdownMode = mode;
}

IVswr::vswrShutdownMode_T Mplane::VswrMon::getMode()
{
	return mShutdownMode;
}
