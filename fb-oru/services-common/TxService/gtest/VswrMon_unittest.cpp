/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      VswrMon_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "IVswr.h"

using namespace Mplane;


namespace Mplane
{


class TestEcbFelixSRxPort:  public EcbFelixSRxPort
{
public:



    /**
     * TestI sampling receiver port constructor, stores the port index
     * it port number and name through the base common port class.
     */
    TestEcbFelixSRxPort( int index, int number, char const* name) :
        EcbFelixSRxPort(index, number, name),
        mDirection( Direction::FORWARD)
    {}


    virtual ReturnType::State updatePower( Direction direction ) override
    {
        mDirection = direction;
        return ReturnType::RT_OK;
    }

    /**
     * Default constructor
     */
    virtual ~TestEcbFelixSRxPort(){}

    Direction mDirection;
};

}

static const unsigned MAX_SRX_PORTS = 1 ;

/**
 * Implement static SRxPort creation factory for the CommonSRxPort.
 */
std::vector< std::shared_ptr<ISRxPort> > ISRxPortFactory::createPorts( int &maxPorts )
{
    maxPorts = MAX_SRX_PORTS ;
    return ISRxPortFactory::getPorts() ;
}


std::vector< std::shared_ptr<ISRxPort> > ISRxPortFactory::getPorts( )
{
    static std::vector< std::shared_ptr<ISRxPort> > sRxPortList;

    // set the number of RX ports for the host radio test implementation
    if( sRxPortList.empty())
    {
        for( unsigned index = 0; index < MAX_SRX_PORTS; index++)
        {
            sRxPortList.push_back (  std::shared_ptr<ISRxPort>(new TestEcbFelixSRxPort( index, index+1, "UTTestSrx")) );
        }
    }
    return sRxPortList;
}




class VswrTestTxPort: public CommonPort, public ITxPort
{
public:

    VswrTestTxPort( int index, int number, const char* name):
        CommonPort(index, number, name),
        mRadioOutputPower(0.0),
        mRfPower(0.0),
        mTestRfPower(0.0),
        mTestDigPower(-15.5),
        mCalData(0),
        mTemperature(45.0),     // make it hot to check out the temperature compensation of VVA
        mFrequency(2345000.0, Frequency::KHz ),
        mTxState(false),
        mOutputMode( ITxPort::Mode::MODULATED)
    {
        mPa = std::shared_ptr<IPa>( new PclTestIPa(index, number, "PclTestIpa"));
    }

    virtual ~VswrTestTxPort()
    {
    }

    virtual ReturnType::State initialise()
    {
        mCalData = std::dynamic_pointer_cast< CalData>(ICalDataFactory::getInterface());

        return ReturnType::RT_OK;
    }

    ReturnType::State setFrequency(const Frequency& frequency)
    {
        mFrequency = frequency;
        return ReturnType::RT_OK;
    }

    const Frequency getFrequency()
    {
        return mFrequency;
    }

    virtual ReturnType::State resetFifo()
    {
        return ReturnType::RT_OK;
    }

    unsigned getFifoLevel()
    {
    	return 8 ;
    }

    virtual Power getRfPower()
    {
        return mRfPower;
    }

    virtual ReturnType::State setTxOffLowLevel(void)
    {
        return ReturnType::RT_OK;
    }

    virtual ReturnType::State setTxOnLowLevel(void)
    {
        return ReturnType::RT_OK;
    }

    ReturnType::State setTxOn(void)
    {
        mTxState = true;
        return ReturnType::RT_OK;
    }

    ReturnType::State setTxOff(void)
    {
        mTxState = false;
        return ReturnType::RT_OK;
    }

    bool isTxOn(void)
    {
        return mTxState;
    }


    ReturnType::State setTargetPower(Power targetPower)
    {
        mTargetPower = targetPower;
        return ReturnType::RT_OK;
    }


    virtual ReturnType::State setRadioOutputPower( Power &power )
    {
        mRadioOutputPower = power;

        if( mCalData )
        {
            std::shared_ptr<ITxCalData> txCal = mCalData->getTxCal();

            if (txCal && txCal->isLoaded())
            {
            	std::shared_ptr<ITxOpenLoop> txol = txCal->getTxOpenLoop(getNumber()); // use the path number to get cal data, not the zero based index

                // used to get the calibration information for this power
                Power rfAttn;
                Power ifAttn;
                Power baseBand;
                Power correction;
                float calTemp;
                // given the required power, frequency and temperature, return the IF and RF attenuation value and the
                // small correction error that is used to set the digital path scalar.
                if ( txol->getData(mFrequency, power, mTemperature.get(), baseBand, correction,rfAttn, ifAttn, calTemp) == true)
                {
                    // Because the VVA has a poor temperature coefficient, we need to use the call temperature
                    // and current temperature to work out a compensation value. We make up the difference in the IF attenuator
                    float powerAdj = (calTemp - mTemperature.get() ) * 0.133;
                    rfAttn += powerAdj;
                    ifAttn -= powerAdj;
                    setIFAttenuation(ifAttn);
                    setRFAttenuation(rfAttn);


                }
            }
        }


        return ReturnType::RT_OK;
    }

    virtual Power getAttenuation()
    {
        return mTargetAttenuation;
    }

    virtual ReturnType::State setAttenuation( Power power )
    {

        Power ifAtten = round( (power.get() - mRFAttenuation.get()) * 2.0) / 2.0;

        Power rfAttnError = power - ifAtten;

        // if the attenuation is more that 0.5db away from the current IF attenuator, then
        // set it, otherwise set the smaller (
        if( (ifAtten > mIFAttenuation) || (ifAtten < mIFAttenuation) )
        {
            setIFAttenuation( ifAtten );
        }
        else
        {
            setRFAttenuation( rfAttnError );
        }

        //   No need to do this here as it is done by the low level CommonPort::setIF/RF/Attenuation
        //   mTargetAttenuation = mIFAttenuation + mRFAttenuation;

        return ReturnType::RT_OK;
    }

    ReturnType::State setIFAttenuation(Power attn)
    {
        mIFAttenuation = attn;
        mTargetAttenuation = mRFAttenuation + mIFAttenuation;
        return ReturnType::RT_OK;
    }

    ReturnType::State setRFAttenuation(Power attn)
    {
        mRFAttenuation = attn;
        mTargetAttenuation = mRFAttenuation + mIFAttenuation;
        return ReturnType::RT_OK;
    }

    Power getIFAttenuation()
    {
        return mIFAttenuation;
    }

    Power getRFAttenuation()
    {
        return mRFAttenuation;
    }

    ReturnType::State setMode(Mode mode)
    {
        mOutputMode = mode;
        return ReturnType::RT_OK;
    }

    ITxPort::Mode getMode()
    {
        return mOutputMode;
    }

    ReturnType::State setDigitalPowerScaler(float power)
    {
        mDigitalPowerScaler = power;
        return ReturnType::RT_OK;
    }

    const Power getDigitalPowerScaler()
    {
        return mDigitalPowerScaler;
    }

    const Temperature getTemperature()
    {
        return mTemperature;
    }

    ReturnType::State setCWPower(Power power)
    {
        mCWPower = power;
        return ReturnType::RT_OK;
    }

    Power getCWPower()
    {
        return mCWPower;
    }


    virtual ReturnType::State getFwdPower(  Power& forward, Power& digital)
    {
        forward = mTestRfPower;
        digital = mTestDigPower;
        return ReturnType::RT_OK;
    }

    ReturnType::State setDacDCOffset(int IOffset,  int QOffset)
    {
        return ReturnType::RT_OK;
    }


    ReturnType::State setDacPhaseOffset(int IOffset,  int QOffset)
    {
        return ReturnType::RT_OK;
    }

    ReturnType::State setDacMagOffset(int IOffset,  int QOffset)
    {
        return ReturnType::RT_OK;
    }

    ReturnType::State getDacDCOffset(int& IOffset,  int& QOffset)
    {
        return ReturnType::RT_OK;
    }


    ReturnType::State getDacPhaseOffset(int& IOffset,  int& QOffset)
    {
        return ReturnType::RT_OK;
    }

    ReturnType::State getDacMagOffset(int& IOffset,  int& QOffset)
    {
        return ReturnType::RT_OK;
    }


    ReturnType::State updatePowerData(Power &rfPower, int &rawAdcValue)
    {
        return ReturnType::RT_NOT_SUPPORTED;
    }

    ReturnType::State updateFwdPowerData()
    {
        return ReturnType::RT_NOT_SUPPORTED;
    }

    Power getTargetPower()
    {
        return mTargetPower;
    }

    Power getMaxPower(void)
    {
        return mMaxPower;
    }

    ReturnType::State setTxDelay(UINT32 delay)
    {
        // set the Tx delay adjustment - TBD

        return ReturnType::RT_OK;
    }

    const Frequency getCalFrequency(void) const
    {
        return Frequency(0u);
    }

    /**
     * Method returns true if this TX path supports an external output PA.
     *
     * @return true if external PA available, otherwise false.
     */
    virtual const bool hasPA()
    {
        return true;
    }

    /**
     * If TX path has an external PA fitted this method return a shared pointer to an
     * appropriate implementation of the IPa interface.
     *
     * @return
     */
    virtual std::shared_ptr<IPa> getPA()
    {
        return mPa;
    }

    ReturnType::State setOpAttenPad( AttenPadState state )
    {
        return ReturnType::RT_OK;
    }

    ITxPort::AttenPadState getOpAttenPad()
    {
        return AttenPadState::PAD_OFF;
    }

    ReturnType::State setLowPassFilter( LowPassFilterState state )
    {
        return ReturnType::RT_OK;
    }

    ITxPort::LowPassFilterState getLowPassFilter()
    {
        return LowPassFilterState::FILTER_OFF;
    }


    std::shared_ptr<IPa> mPa;
    Power mRadioOutputPower;
    Power mRfPower;
    Power mTestRfPower;
    Power mTestDigPower;
    std::shared_ptr<CalData> mCalData;
    Temperature mTemperature;
    Frequency mFrequency;

    Power       mTargetPower;               //!> This holds the target output power for this port in dB
    Power       mTargetAttenuation;         //!> This holds the target path attenuation provided by hardware specific implementations
    Power       mRFAttenuation;             //!> This holds the current RF attenuation value in dB
    Power       mIFAttenuation;             //!> This holds the current IF attenuation value in dB
    Power       mMaxPower;
    Power    mDigitalPowerScaler;
    Power mCWPower;
    bool mTxState;
    Mode mOutputMode;

};

static const unsigned MAX_PORTS = 2 ;

std::vector< std::shared_ptr<ITxPort> > ITxPortFactory::createPorts( int &maxPorts )
{
    maxPorts = MAX_PORTS ;
    return ITxPortFactory::getPorts() ;
}


std::vector< std::shared_ptr<ITxPort> > ITxPortFactory::getPorts( )
{
    static std::vector< std::shared_ptr<ITxPort> > txPortList;

    // set the number of RX ports for the host radio test implementation
    if( txPortList.empty())
    {
        for( unsigned index = 0; index < MAX_PORTS; index++)
        {
            txPortList.push_back (  std::shared_ptr<ITxPort>(new VswrTestTxPort( index, index+1, "VSWR_TEST_TX")) );
        }
    }
    return txPortList;
}




TEST(VswrMonTest, unittest)
{


}
