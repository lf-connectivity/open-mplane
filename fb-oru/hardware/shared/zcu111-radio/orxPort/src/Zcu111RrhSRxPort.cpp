/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111RrhSRxPort.cpp
 * \brief     Zcu111 RRH radio SRxPort definition
 *
 *
 * \details   Zcu111 RRH radio SRxPort definition
 *
 */

#include "Zcu111RrhSRxPort.h"
#include "Frequency.h"
#include "Temperature.h"


using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
Mplane::Zcu111RrhSRxPort::Zcu111RrhSRxPort(int index, int txPortOffset, const char* name):
	Zcu111SRxPort( index, txPortOffset, name ),
	mNumAssociatedTxPorts(ISRxPortFactory::getNumAssociatedTxPorts()),
	mPathData(ISRxPortFactory::getNumAssociatedTxPorts() * 2),
	mCalData(),
	mSrxCal(),
	mSrxol(ISRxPortFactory::getNumAssociatedTxPorts(), std::shared_ptr<ISRxOpenLoop>()),
    mSwrol(ISRxPortFactory::getNumAssociatedTxPorts(), std::shared_ptr<ISwrOpenLoop>()),
	mFwdPowerUpdated(false),
	mRevPowerUpdated(false),
	mOptimaldBfs( -16.0 )
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Zcu111RrhSRxPort::~Zcu111RrhSRxPort()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::Zcu111RrhSRxPort::setPath(int index)
{
	if (index < 0 || index >= (int)mNumAssociatedTxPorts)
	{
		return ReturnType::RT_OUT_OF_RANGE;
	}

    return CommonSRxPort::setPath(index);
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Power Mplane::Zcu111RrhSRxPort::getPower(void)
{
	// Get the raw ADC RMS power
    Power power = getRawAdcRms();

    // Get the correction factor
    power += getCorrection();

	return power;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Power Mplane::Zcu111RrhSRxPort::getCorrection(void)
{
    int path = getPath();
    ISRxPort::Direction dir = getDirection();

    // Get the calibration data before proceeding.
    getCalData();

    Power correction = 0.0;
    if (dir == ISRxPort::Direction::SRX_DIR_FORWARD)
    {
		if (mSrxol[path] )
		{
			float temperature = getTemperature();
			Frequency frequency = getFrequency();
			correction = mSrxol[path]->dBfsTodBm(frequency,  getAttenuation() , temperature);
		}
    }
    else
    {
		if (mSwrol[path] )
		{
			float temperature = getTemperature();
			Frequency frequency = getFrequency();
			correction = mSwrol[path]->dBfsTodBm(frequency,  getAttenuation() , temperature);
		}
    }

	return correction;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::Zcu111RrhSRxPort::getFwdPower(int path, Power& rf, Power& digital)
{
	ReturnType::State returnState = ReturnType::RT_OK;

	if (path < 0 || path >= (int)mNumAssociatedTxPorts)
	{
		return ReturnType::RT_OUT_OF_RANGE;
	}

    if( ReturnType::RT_OK == updatePower( Direction::FORWARD ) )
    {
		Mutex::Lock lock(mMutex) ;      // don't mess with this until we've finished
		path &= 0x01;                   // forward path 0 - 1
		rf= mPathData[path].power;
		digital = mPathData[path].tssi;
		returnState = ReturnType::RT_OK;
    }
    else
    {
    	returnState = ReturnType::RT_ERROR;
    }

    return returnState;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::Zcu111RrhSRxPort::getRevPower(int path, Power& rf,  Power& digital)
{
	ReturnType::State returnState = ReturnType::RT_OK;

	if (path < 0 || path >= (int)mNumAssociatedTxPorts)
	{
		return ReturnType::RT_OUT_OF_RANGE;
	}

    if( ReturnType::RT_OK ==  updatePower( Direction::REVERSE ) )
    {
		Mutex::Lock lock(mMutex) ;
		path |= 0x02;                   // reverse path 2 - 3
		rf= mPathData[path].power;
		digital = mPathData[path].tssi;
		returnState = ReturnType::RT_OK;
    }
    else
    {
    	returnState = ReturnType::RT_ERROR;
    }

    return returnState;
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::Zcu111RrhSRxPort::setTargetPower(int path,  Mplane::Power target)
{
    if( path >= 0 && path < (int)(mNumAssociatedTxPorts))
    {
        // Get the calibration data before proceeding.
        getCalData();

        mPathData[ path ].target = target - mOptimaldBfs;
        int number = path & 0x01;
        if (mSrxol[number] )
        {
            Power atten = mSrxol[number]->findNearestAttenuation( getFrequency(), mPathData[ path ].target );
            if( atten.get() >= 0.0 )
            {
                mPathData[ path ].attenuation = atten;
                mPathData[ path | 0x02 ].attenuation = atten;

                return ReturnType::RT_OK;
            }
        }
        return ReturnType::RT_NOT_FOUND;            // we have no cal data, or can't find target in cal
    }
    return ReturnType::RT_OUT_OF_RANGE;             // invalid path
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::Zcu111RrhSRxPort::initialise()
{
    CommonSRxPort::initialise();

    // Set the SRX VCO control FPGA bit to a 1 to allow compatibility with the DPD.
    mSystemFpga->write_srxVcoControl(0x01);

    mCalData = std::dynamic_pointer_cast
            < ISRxCalDataContainer > (ICalDataFactory::getInterface());

    mSwrCalData = std::dynamic_pointer_cast
            < ISwrCalDataContainer > (ICalDataFactory::getInterface());

    // Get the calibration data
    getCalData();

    return ReturnType::RT_OK;
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::Zcu111RrhSRxPort::updatePower(Direction direction)
{
    Mutex::Lock lock(mMutex) ;      // prevent access to data whilst being updated.

    UINT16 done = 0;

    unsigned short atten;

    // setup the attenuation values
    if( direction == Direction::FORWARD )    // must be reverse measurement TX1_REV or TX2_REV
    {
        mAntennaFpga->write_srxFwdRevSelect(getIndex(), 0);      // forward measure
        atten = mAtten->calcControl( mPathData[ 0 ].attenuation );
        mAntennaFpga->write_srxPowerAtten( (unsigned) 0 + mTxPortOffset, atten );
        atten = mAtten->calcControl( mPathData[ 1 ].attenuation );
        mAntennaFpga->write_srxPowerAtten( 1 + mTxPortOffset, atten );
    }
    else
    {
    	mAntennaFpga->write_srxFwdRevSelect(getIndex(), 1);      // reverse measure
        atten = mAtten->calcControl( mPathData[ 2 ].attenuation );   // TX1 -reverse
        mAntennaFpga->write_srxPowerAtten( (unsigned) 0 + mTxPortOffset, atten );
        atten = mAtten->calcControl( mPathData[ 3 ].attenuation );                  // TX2 - reverse
        mAntennaFpga->write_srxPowerAtten( 1 + mTxPortOffset, atten );
    }


    // Start the conversion. should take takes just over 10ms
    mSystemFpga->write_measurementStart(1);

    for( int loop = 0; ((loop < 5) && (done == 0)); loop ++)
    {
        /* Sleep for 100ms at a time. */
        Task::msSleep(100);

        // Check for measurement "done"
        done = mSystemFpga->read_measurementDone();
    }

    /* We have come out of the conversion loop for what ever reason,
     * so stop the conversion. Actually it just sets bit 2 to the
     * correct state for next time.
     */
    mSystemFpga->write_measurementStart(0);

    // Check to see if the conversion actually completed or it timed out */
    if (done != 0)
    {
        // for each TX port, do get results and convert them.
        for( unsigned  input = (unsigned)0; input < mNumAssociatedTxPorts ; ++input )
        {
            UINT32 rf = 0;
            UINT32 tssi = 0;
            int channel = input;        // channel is the 0 based indexed into the fwd/rev path data
            if( direction == Direction::FORWARD )    // must be forward measurement TX1_FWD or TX2_FWD
            {
                rf = mAntennaFpga->read_srxPowerRssiFwd( input + mTxPortOffset);
                tssi = mAntennaFpga->read_srxPowerTssiFwd(input + mTxPortOffset);
                mFwdPowerUpdated = true;
            }
            else
            {
                channel |= 0x02;    // add reverse path indicator bit to path (ie 2 and 3)
                rf = mAntennaFpga->read_srxPowerRssiRev( input + mTxPortOffset);
                tssi = mAntennaFpga->read_srxPowerTssiRev(input + mTxPortOffset);
                mRevPowerUpdated = false;
            }
            if( rf == 0 )      // prevent -inf results
            {
                rf = 1;        // return noise floor of ~-78dB
            }
            if( tssi == 0 )
            {
                tssi = 1;      // force measurement to noise floor ~-42.14 dB
                mPathData[channel].tssi.set( -50.0 );
            }
            else
            {
                mPathData[channel].tssi.set( 10 * log10( ((float)tssi / SRX_TSSI_SCALE_FACTOR) ) );
            }

            /* Now we need to convert it to dBFS*/
            mPathData[channel].power.set(10 * log10((float)rf/SRX_RSSI_SCALE_FACTOR));

            float temperature = getTemperature();
            Frequency frequency = getFrequency();
            Power correction(0.0f);

            // Get the calibration data before proceeding.
            getCalData();

            // input is always 0 or 1 to match sampling on TX path 0 or 1
            if( direction == Direction::FORWARD )    // must be forward measurement so use chaneel 0,1 and the srx calibration data
            {
                if (mSrxol[input] )
                {
                    correction = (mSrxol[input]->dBfsTodBm(frequency, mPathData[ channel ].attenuation , temperature));
                    mPathData[channel].power += correction;
                }
            }
            else        // must be reverse power so use the channel 3,4 and the swr calibration data
            {
                if (mSwrol[input] )
                {
                    correction = (mSwrol[input]->dBfsTodBm(frequency, mPathData[ channel ].attenuation , temperature));
                    mPathData[channel].power += correction;
                }
            }
        }
    }
    else
    {
        // Conversion never completed!
        ILoggable::logEventError("Srx port read power failed, measurement done complete bit not set");
        return ReturnType::RT_ERROR;
    }


    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::Zcu111RrhSRxPort::getPathAtten(int path,
        Power& attenuation)
{
    if( path >= 0 && path < (int)(mNumAssociatedTxPorts * 2))
    {
        attenuation = mPathData[ path ].attenuation;

        return ReturnType::RT_OK;
    }
    return ReturnType::RT_OUT_OF_RANGE;             // invalid path
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::Zcu111RrhSRxPort::getCalData(void)
{
    ReturnType::State returnState = ReturnType::RT_OK;

    mSrxCal = mCalData->getSRxCal();
    mSwrCal = mSwrCalData->getSwrCal();

    if (mSrxCal->isLoaded())
    {
        for( int index = 0; index < (int)mNumAssociatedTxPorts ; ++index )
        {
            // use the path number to get cal data, not the zero based index
        	// Add the Tx port offset to get the correct path
            std::shared_ptr<ISRxOpenLoop> srx = mSrxCal->getSRxOpenLoop( index + 1 + mTxPortOffset );
            mSrxol[index] = srx;
        }
    }
    else
    {
        ILoggable::logEventError("Zcu111RrhSRxPort::getCalData() - SRx Cal not loaded");
        returnState = ReturnType::RT_ERROR;
    }

    if (mSwrCal->isLoaded())
    {
        for( int index = 0; index < (int)mNumAssociatedTxPorts ; ++index )
        {
            // use the path number to get cal data, not the zero based index
            std::shared_ptr<ISwrOpenLoop> swr = mSwrCal->getSwrOpenLoop( index + 1 + mTxPortOffset );
            mSwrol[index] = swr;
        }
    }
    else
    {
        ILoggable::logEventError("Zcu111RrhSRxPort::getCalData() - SWR Cal not loaded");
        returnState = ReturnType::RT_ERROR;
    }

    return returnState;
}
