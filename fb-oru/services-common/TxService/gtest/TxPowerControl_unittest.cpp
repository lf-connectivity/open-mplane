/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFunctionalTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <typeinfo>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Task.h"

#include "ISRxPort.h"
#include "IPa.h"
#include "ITxPcl.h"
#include "TxPowerControl.h"

#include "IDpdControl.h"
#include "CommonTxPort.h"

#include "ICarrier.h"
#include "ICarrierServer.h"


#include "ICalDownloadManagement.h"
#include "CalData.h"
#include "TxCal.h"

#include "IRadio.h"

#include "IAppSettings.h"
#include "IAppSettingsFactory.h"
#include "IAppOptions.h"

#include "OffTargetFPGA.h"

using namespace std;
using namespace Mplane;

//========================================================================================================================
// TYPES
//========================================================================================================================


//------------------------------------------------------------------------------------------------------------------------
// TxPowerControl test class


enum class TestError
{
    NONE,
    BAD_INDEX,
    BAD_STATE,
    DPD_START_FAILED
};


class TestDpdControl : public IDpdControl
{
public:

    TestError testError;
    bool mStart;
    std::shared_ptr<ITxPcl> mAssociatedPCL;

    TestDpdControl():
        testError( TestError::NONE ),
        mStart(false),
        mAssociatedPCL(0)
    {}

    virtual ~TestDpdControl(){};

    /**
     * This method will reset the DPD on the specified channel to
     * unity gain
     * \param tx - tx path [0..MAX-1] to be reset
     * \return true if all ok; false on failure
     */
    virtual bool resetDpd(unsigned tx) override
    {

        return  true;
    }


    /**
     * Set the PCL associated with the current test
     * @param pcl
     */
    void setPcl(std::shared_ptr<ITxPcl> pcl )
    {
        mAssociatedPCL = pcl;
    }

    /**
     * This method will enable adaption of the DPD on the specified
     * channel
     * \param tx - tx path to enable
     * \param timeoutMs - timeout time in millisecs
     * \return true if all ok; false on failure
     */
    virtual bool startDpd(unsigned tx, unsigned timeoutMs) override
    {
        testError = TestError::NONE;
        if( mAssociatedPCL->getIndex() != (int)tx )
        {
            testError = TestError::BAD_INDEX;
        }
        if( !mStart )
        {
            testError = TestError::DPD_START_FAILED;
        }
        return  mStart;
    }

    virtual bool startDpd(unsigned tx) override
    {
        testError = TestError::NONE;
        if( mAssociatedPCL->getIndex() != (int)tx )
        {
            testError = TestError::BAD_INDEX;
        }
        if( !mStart )
        {
            testError = TestError::DPD_START_FAILED;
        }
        return  mStart;
    }

    /**
     * This method will stop the DPD on the specified channel
     * \param tx - tx path [0..MAX-1] to be restarted
     * \return true if all ok; false on failure
     */
    virtual bool stopDpd(unsigned tx) override
    {
        return true;
    }

    /**
     * This method will send the latest PAPR target to the DPD for this tx path
     * \param tx - tx path [0..MAX-1] to be restarted
     * \return true if all ok; false on failure
     */
    virtual bool setPapr(unsigned tx, const Power& papr) override
    {
        return true;
    }

    /**
     * This method will send the latest SRx attenuation value to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setSRxAtten(unsigned tx, const Power& atten) override
	{
    	return true ;
	}

    bool setParams(unsigned tx, const std::vector<DataVariant> &params)
    {
    	return true;
    }


    //-------------------------------------------------------------------------------------------------------------
    void addEventMonitor(const std::string &name, unsigned tx,
    		const std::string &event, MonitorFunc func,
    		const std::vector<DataVariant>& attributeValues)
    {
    	mFunc[name] = func;
    }

    //-------------------------------------------------------------------------------------------------------------
    void addEventMonitor(const std::string &name, MonitorFunc func,
    		const std::vector<DataVariant>& attributeValues)
    {

    }

    //-------------------------------------------------------------------------------------------------------------
    void delEventMonitor(const std::string &name)
    {

    }

    //-------------------------------------------------------------------------------------------------------------
    void addAlarmMonitor(const std::string &name, IDpdControl::MonitorFunc func,
    		const std::vector<DataVariant> &attributeValues)
    {

    }

    //-------------------------------------------------------------------------------------------------------------
    void delAlarmMonitor(const std::string &name)
    {

    }

	void sendDpdEvent(const std::map<std::string, DataVariant>& attributeValues)
	{
		for (auto & cb : mFunc)
		{
			cb.second(attributeValues);
		}
	}

private:
	std::map<std::string, MonitorFunc> mFunc;

};

//namespace Mplane
//{

std::shared_ptr<IDpdControl> IDpdControl::getInterface()
{
    static std::shared_ptr<IDpdControl> interface(std::make_shared<TestDpdControl>());
    return interface ;
}

//-------------------------------------------------------------------------------------------------------------
bool IDpdControl::pushInt(std::vector<DataVariant>& list, const std::string& name, int value)
{
	DataVariant dv(name, std::string("INT")) ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool IDpdControl::pushFloat(std::vector<DataVariant>& list, const std::string& name, float value)
{
    DataVariant dv(name, std::string("FLOAT")) ;
    dv.set(value) ;
    list.push_back(dv) ;
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool IDpdControl::pushBool(std::vector<DataVariant>& list, const std::string& name, bool value,
		const std::map<bool, std::string>& enumValues)
{
	DataVariant dv(name, std::string("ENUM(") + enumValues.at(false) + ":" + enumValues.at(true) + ")") ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool IDpdControl::pushEnum(std::vector<DataVariant>& list,
		const std::string& name, const std::string& value,
		const std::string& enumValues)
{
	DataVariant dv(name, std::string("ENUM(") + enumValues + ")") ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}



class PclTestIPa: public IPa
{

public:

    /*!
     *
     * \brief Method to get the ID eeprom associated with the PA
     *
     * \param  None
     * \return The IdEeprom object if any, else NULL
     */
    virtual std::shared_ptr<IIdEeprom> getIdEeprom( void )
    {
    	std::shared_ptr<IIdEeprom> idEeprom(0);
    	return idEeprom;
    }

    /*!
      *
      * \brief Pure virtual method to get the temperature value
      *
      * \param  Temperature sensor to read, each PA has two.
      * \return The temperature reading of the selected sensor.
      */
     virtual float getTemperature( paTempSensor_T temperatureSensorToRead )
     {
         if( IPa::PA_TEMP_1 == temperatureSensorToRead )
         {
             return 55.5;
         }
         else if( IPa::PA_TEMP_2 == temperatureSensorToRead )
         {
             return 66.6;
         }
         else
         {
             return 77.7;
         }
     }

     /*!
      *
      * \brief Virtual method to get PA idea
      *
      * \param  None
      * \return The integer value of the PA id that has been read.
      */
     virtual UINT16 getID( void )
     {
         return 0x55aa;
     }

     /*!
      *
      * \brief Virtual method to retrieve if a PA is connected.
      *
      * \param  None
      * \return Is a PA connected true/false
      */
     virtual bool isConnected( void )
     {
    	 return true;
     }

     /*!
      *
      * \brief Virtual method to retrieve the number of sensors per PA.
      *
      * \param  None
      * \return Number of sensors per PA
      */
     virtual UINT16 numberTempSensorsPerPa( void )
     {
    	 return 2;
     }

     PclTestIPa( int index, const char* name):
        mIndex(index), mName(name),
        mDesignGain( 53.0 ),
        mMaxDesignGain( 61.0 )
     {

     }

     virtual ~PclTestIPa(){}

     virtual const Power getDesignGain()
     {
         return mDesignGain;
     }

     /**
      * Method used to return the possible operational band for the PA, ie the maximum
      * power - the minimum power, taking into account all thermal and aging effects.
      * @return
      */
     virtual const Power getMaxDesignGain()
     {
         return mMaxDesignGain;
     }

	 /*!
	   *
	   * \brief Virtual method to update the average temperature value
	   *
	   */
	 virtual void updateAvgTemp( void )
	 {
	 }


     /**
      * Method used to enable a PA connected to the radio
      *
      * @return Return state of the operation
      */
     virtual const ReturnType::State setPaEnable( void ) {return ReturnType::RT_OK;}

     /**
      * Method used to disable a PA connected to the radio
      *
      * @return Return state of the operation
      */
     virtual const ReturnType::State setPaDisable( void ) {return ReturnType::RT_OK;}

     /**
      * Method used to query the enable/disable of a PA connected to the radio
      *
      * @param Reference to the PA current state
      * @return Return state of the operation
      */
     virtual const ReturnType::State getPaState( paState_T &paState ) {
    	 paState = IPa::paState_T::PA_DISABLED;
    	 return ReturnType::RT_OK;
     }

     /**
      * Method used to return the status for the PA Gain Manual Control.
      *
      * @param UINT16 ctrlRawValue the raw value of the PA Gain Manual control register
      *
      * @return true if successful, false otherwise
      */
     virtual bool getPaGainManualCtrl(UINT16& ctrlRawValue)
     {
    	 ctrlRawValue = 0;
    	 return true;
     }

     /**
      * Method used to set the status for the PA Gain Manual Control.
      *
      * @param UINT16 ctrlStatus the raw value of the PA Gain Manual Control register to set
      *
      * @return true if successful, false otherwise
      */
     virtual bool setPaGainManualCtrl(UINT16 ctrlStatus)
     {
    	 return true;
     }

     /**
      * Method used to return the status for the PA Gain Override.
      *
      * @param UINT16 overrideRawValue the raw value of the PA Gain Override register
      *
      * @return true if successful, false otherwise
      */
     virtual bool getPaGainOverride(UINT16& overrideRawValue)
     {
    	 overrideRawValue = 0;
    	 return true;
     }

     /**
      * Method used to set the status for the PA Gain Override.
      *
      * @param UINT16 overrideStatus the raw value of the PA Gain Override register to set
      *
      * @return true if successful, false otherwise
      */
     virtual bool setPaGainOverride(UINT16 overrideStatus)
     {
    	 return true;
     }

     /**
      * Get the 0-based index
      */
     virtual int getIndex() const {return mIndex; }

     /**
      * Get the name
      */
     virtual std::string getName() const { return mName; }

     int mIndex;
     std::string mName;
     Power mDesignGain;
     Power mMaxDesignGain;

};


class PclTestTxPort: public CommonPort, public ITxPort
{
public:

    PclTestTxPort( int index, const char* name):
        CommonPort(index, name),
        mRadioOutputPower(0.0),
        mRfPower(0.0),
        mTestRfPower(0.0),
        mTestDigPower(-15.5),
        mCalData(0),
        mTemperature(45.0),     // make it hot to check out the temperature compensation of VVA
        mFrequency(2345000.0, Frequency::KHz ),
        mExtLoss(0.0f),
        mTxState(false),
        mOutputMode( ITxPort::Mode::MODULATED),
		mTxGain(0.0)
    {
        mPa = std::shared_ptr<IPa>( new PclTestIPa(index, "PclTestIpa"));
    }

    virtual ~PclTestTxPort()
    {
    }

    virtual ReturnType::State initialise()
    {
        mCalData = std::dynamic_pointer_cast< CalData>(ICalDataFactory::getInterface());

        return ReturnType::RT_OK;
    }

    ReturnType::State setSynth(const Frequency& frequency)
    {
        mFrequency = frequency;
        return ReturnType::RT_OK;
    }

    ReturnType::State setFrequency(const Frequency& frequency)
    {
        return setSynth(frequency);
    }

    const Frequency getFrequency()
    {
        return mFrequency;
    }

    const Frequency getSynthFrequency()
    {
        return mFrequency;
    }

    virtual bool isBadIbsFreq( Frequency frequency )
    {
     	return false;
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

    virtual Power getExtFilterLoss()
    {
        return mExtLoss;
    }

    virtual ReturnType::State setExtFilterLoss(Power filterLoss)
    {
        if( filterLoss.get() >= 0.0f && filterLoss.get() <= 1.2f )
        {
            mExtLoss = filterLoss;
            return ReturnType::RT_OK;
        }
        return ReturnType::RT_OUT_OF_RANGE;
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
            	std::shared_ptr<ITxOpenLoop> txol = txCal->getTxOpenLoop(getIndex() + 1); // use the path number to get cal data, not the zero based index

                // used to get the calibration information for this power
                Power rfAttn;
                Power baseBand;
                Power correction;
                float calTemp;
                // given the required power, frequency and temperature, return the IF and RF attenuation value and the
                // small correction error that is used to set the digital path scalar.
                if ( txol->getData(mFrequency, power, mTemperature.get(), baseBand, correction,rfAttn, calTemp) == true)
                {
                    // Because the VVA has a poor temperature coefficient, we need to use the call temperature
                    // and current temperature to work out a compensation value. We make up the difference in the IF attenuator
                    float powerAdj = (calTemp - mTemperature.get() ) * 0.133;
                    rfAttn += powerAdj;
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
        setRFAttenuation( power );

        //   No need to do this here as it is done by the low level CommonPort::setIF/RF/Attenuation
        //   mTargetAttenuation = mIFAttenuation + mRFAttenuation;

        return ReturnType::RT_OK;
    }

    ReturnType::State setIFAttenuation(Power attn)
    {
        return ReturnType::RT_OK;
    }

    ReturnType::State setRFAttenuation(Power attn)
    {
        mRFAttenuation = attn;
        mTargetAttenuation = mRFAttenuation;
        return ReturnType::RT_OK;
    }

    ReturnType::State setRFAttenuation(Power attn, Temperature temperature)
    {
        mRFAttenuation = attn;
        mTargetAttenuation = mRFAttenuation;
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

    virtual ReturnType::State getRevPower(  Power& reverse, Power& digital)
    {
        reverse = mTestRevPower;
        digital = mTestRevDigPower;
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



    ReturnType::State setDacIfOffset( double  MHzOffset )
    {
        return ReturnType::RT_OK;
    }

    double getDacIfOffset()
    {
       return 0;
    }

    ReturnType::State updatePowerData(Power &rfPower, int &rawAdcValue)
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

    Power getMaxFreqDepPower(void)
    {
        return mMaxPower;
    }

    Power getMinFreqDepPower(void)
     {
         return mMinPower;
     }

    Power getMinPower(void)
    {
        return mMinPower;
    }

    Power getMaxPaPower(void)
    {
        return mMaxPaPower;
    }

    ReturnType::State setTxDelay(UINT32 delay)
    {
        // set the Tx delay adjustment - TBD

        return ReturnType::RT_OK;
    }

    const Frequency getCalFrequency(void) const
    {
        return Frequency(0ull);
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

    void setTxGain( float gain )
    {
    	mTxGain = gain;
    }

    float getTxGain()
    {
    	return mTxGain;
    }

    ReturnType::State setPath( int path )
    {
    	return ReturnType::RT_OK;
    }

    int getPath()
    {
    	return 0;
    }


    std::shared_ptr<IPa> mPa;
    Power mRadioOutputPower;
    Power mRfPower;
    Power mTestRfPower;
    Power mTestDigPower;
    Power mTestRevPower;
    Power mTestRevDigPower;
    std::shared_ptr<CalData> mCalData;
    Temperature mTemperature;
    Frequency mFrequency;

    Power       mTargetPower;               //!> This holds the target output power for this port in dB
    Power       mTargetAttenuation;         //!> This holds the target path attenuation provided by hardware specific implementations
    Power       mRFAttenuation;             //!> This holds the current RF attenuation value in dB
    Power       mIFAttenuation;             //!> This holds the current IF attenuation value in dB
    Power       mMaxPower{46.1f};
    Power       mMinPower{30.0f};
    Power       mMaxPaPower{49.2f};
    Power    mDigitalPowerScaler;
    Power mCWPower;
    Power mExtLoss;
    bool mTxState;
    Mode mOutputMode;
    float mTxGain;

};

static const unsigned MAX_PORTS = 4 ;

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
            txPortList.push_back (  std::shared_ptr<ITxPort>(new PclTestTxPort( index, "PCL_TEST_TX")) );
        }
    }
    return txPortList;
}



class TxPowerControlTest : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {
    }

};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TxPowerControlTest, Basic)
{
    // Ensure rssiDone bit is set to allow test to run
	std::shared_ptr<OffTargetFPGA> offTargetFpga = OffTargetFPGA::getInstance();
    offTargetFpga->writeField("rssiDone", 1);
    offTargetFpga->writeField("lowPowerAlarm[0]",0);
    offTargetFpga->writeField("highPowerAlarm[0]",0);
    offTargetFpga->writeField("lowPowerAlarm[1]",0);
    offTargetFpga->writeField("highPowerAlarm[1]",0);

    std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
    std::cerr << "Starting AxisArtProcess application for " << appSettings->getBoardString() << " hardware" << std::endl;

    int argc = 0;
    char noarg[] = "";
    const char** argv = (const char**)&noarg;

    // Define expected options and process the command line
    std::shared_ptr<IAppOptions> opts(IAppOptions::createInstance(argc, argv,
        "Advanced Radio Tester",
        std::vector<std::shared_ptr<IAppOptionSpec> >{
            IAppOptionSpec::factory("ethbb",  DataVariantType::String, "Ethernet interface name (over baseband)", "eth_bb", "ETHBB"),
            IAppOptionSpec::factory("ethcdi", DataVariantType::String, "Ethernet interface name (control and debug)", "eth_cdi", "ETHCDI"),
        }
    )) ;

    // create the cal data objects and their assciated CalDownload objects
    std::shared_ptr<ICalData> calData = ICalDataFactory::getInterface();

    // tell cal download manager to change the root install directory.
    std::string failReason ;
    std::shared_ptr<ICalDownloadManagement> calMgr(ICalDownloadManagement::getInstance()) ;
    calMgr->testInjectInstallDir("../../../TxService/gtest/caldata", failReason) ;


    std::shared_ptr<IRadio> radio = IRadioFactory::getInterface();      // this will load the cal data from the above

    radio->initialise();


    std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());

    std::shared_ptr<IDpdControl> iDpdCtl = IDpdControl::getInterface();

    std::shared_ptr<TestDpdControl> testDpd( std::dynamic_pointer_cast<TestDpdControl>(iDpdCtl)  );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );
    std::shared_ptr<ITxPort> txPort1 = txPorts[0];
    std::shared_ptr<ITxPort> txPort2 = txPorts[1];

    std::shared_ptr<PclTestTxPort> testTxPort1( std::dynamic_pointer_cast<PclTestTxPort>(txPort1) );
    std::shared_ptr<PclTestTxPort> testTxPort2( std::dynamic_pointer_cast<PclTestTxPort>(txPort2) );

    std::string prefix = "[----------] ";

    std::shared_ptr<ITxPcl> pcl1 = ITxPcl::getInstance(0);

    std::shared_ptr<ITxPcl> pcl2 = ITxPcl::getInstance(1);

    std::cout << prefix << "Check INIT state" << std::endl;
    ASSERT_TRUE( pcl1->getState() == TxPclState::INIT );
    ASSERT_TRUE( pcl2->getState() == TxPclState::INIT );

    std::cout << prefix << "Check PCL 1 moves to OFF state" << std::endl;
    pcl1->timerUpdate();
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
    ASSERT_TRUE( pcl2->getState() == TxPclState::INIT );

    std::cout << prefix << "Check PCL 2 moves to OFF state" << std::endl;
    pcl2->timerUpdate();
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );

    std::cout << prefix << "Check PCL 2 moves to MANUAL state" << std::endl;
    pcl2->setManual();
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
    ASSERT_TRUE( pcl2->getState() == TxPclState::MANUAL );

    std::cout << prefix << "For PCL 2 check only AUTO event can move MANUAL through INIT to OFF  state" << std::endl;
    pcl2->timerUpdate();
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
    ASSERT_TRUE( pcl2->getState() == TxPclState::MANUAL );
    pcl2->setTxOn();
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
    ASSERT_TRUE( pcl2->getState() == TxPclState::MANUAL );
    pcl2->setAuto();
    // the AUTO event will be processed by initialised which will go straight to off.
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );


    testDpd->setPcl( pcl1 );
    testDpd->mStart = false;    // DPD fail to start
    pcl1->timerUpdate();
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );

    std::cout << prefix << "For PCL 1 check setting carrier causes TX ON and sets initial open loop power" << std::endl;
    testDpd->testError = TestError::NONE;

    Frequency frequency(900000ULL, Frequency::KHz);

    txPort1->setFrequency( frequency );
    txPort2->setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 1
    ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );
    carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
    carrierSetter.setTxPower( 43.0 );
    carrierSetter.setTxFrequency(frequency);
    carrierSetter.setRxFrequency(frequency);
    carrierSetter.setGroupSizeUp( 4 );
    carrierSetter.setGroupSizeDown( 4 );
    carrierSetter.setTxScaling( -18.0 );
    carrierSetter.setTxContainer( 0, 1 );
    carrierSetter.setTxContainer( 1, 0 );
    carrierSetter.setTxContainer( 2, 0 );
    carrierSetter.setTxContainer( 3, 0 );
    carrierSetter.setTxFibre(0, 0) ;
    carrierSetter.setRxFibre(0, 0) ;
    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    EXPECT_FLOAT_EQ( pcl1->getTargetPower().get(), 0.0);

    testTxPort1->mTestRfPower.set( 30.0 );
    testTxPort1->mTestDigPower.set( -23.5 );


    ASSERT_TRUE( pcl1->getState() == TxPclState::OPENLOOP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );

    pcl1->timerUpdate();            // execute the open loop - set the open loop power, using target power

    EXPECT_FLOAT_EQ( pcl1->getTargetPower().get(), 43.0);


    EXPECT_FLOAT_EQ( testTxPort1->mRadioOutputPower.get(), -24.0 );

    EXPECT_FLOAT_EQ( testTxPort1->getAttenuation().get(), 18.1405001 );
    EXPECT_FLOAT_EQ( testTxPort1->getRFAttenuation().get(), 18.1405001 );

    pcl1->timerUpdate();            // execute the open loop - WAIT_DP wait digital power good

    pcl1->timerUpdate();            // execute the open loop - CHECK_RF check RF measured power is good

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );


    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );


    std::cout << prefix << "For PCL 1 open loop power OK, start RAMP mode" << std::endl;

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );


    std::cout << prefix << "Set PCL 2 carrier on and moves to RAMP state" << std::endl;
    testDpd->setPcl( pcl2 );

    // NOTE: Need to disable carrier before making changes
    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );


    carrierSetter = carrierServer->getCarrierSetter(0);
        carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
        carrierSetter.setTxPower( 43.0 );
        carrierSetter.setTxFrequency(frequency);
        carrierSetter.setRxFrequency(frequency);
        carrierSetter.setGroupSizeUp( 4 );
        carrierSetter.setGroupSizeDown( 4 );
        carrierSetter.setTxScaling( -18.0 );
        carrierSetter.setTxContainer( 0, 1 );
        carrierSetter.setTxContainer( 1, 5 );
        carrierSetter.setState(ICarrier::STATE_ENABLE);
     EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

     testTxPort2->mTestRfPower.set( 30.0 );
     testTxPort2->mTestDigPower.set( -23.5 );


    ASSERT_TRUE( pcl1->getState() == TxPclState::OPENLOOP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OPENLOOP );

    pcl1->timerUpdate();
    pcl2->timerUpdate();

    EXPECT_FLOAT_EQ( pcl2->getTargetPower().get(), 43.0);
    EXPECT_FLOAT_EQ( testTxPort2->mRadioOutputPower.get(), -24.0 );

    EXPECT_FLOAT_EQ( testTxPort2->getAttenuation().get(), 18.1405001 );
    EXPECT_FLOAT_EQ( testTxPort2->getRFAttenuation().get(), 18.1405001 );

    pcl1->timerUpdate();            // execute the open loop - WAIT_DP wait digital power good
    pcl2->timerUpdate();            // execute the open loop - WAIT_DP wait digital power good

    pcl1->timerUpdate();            // execute the open loop - CHECK_RF check RF measured power is good
    pcl2->timerUpdate();            // execute the open loop - CHECK_RF check RF measured power is good


    std::cout << prefix << "Check PCL 1 ramp mode doesn't change attenuation on low input power" << std::endl;
    testTxPort1->mTestRfPower.set( 34.0 );
    testTxPort1->mTestDigPower.set( -46.0 );
    testTxPort2->mTestRfPower.set( 34.0 );
    testTxPort2->mTestDigPower.set( -46.0 );

    pcl1->timerUpdate();
    pcl2->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );

    EXPECT_FLOAT_EQ( testTxPort1->getAttenuation().get(), 18.1405001 );
    EXPECT_FLOAT_EQ( testTxPort1->getRFAttenuation().get(), 18.1405001 );

    EXPECT_FLOAT_EQ( testTxPort2->getAttenuation().get(), 18.1405001 );
    EXPECT_FLOAT_EQ( testTxPort2->getRFAttenuation().get(), 18.1405001 );


    std::cout << prefix << "Check PCL 1 ramps to power and enters track mode" << std::endl;


    testTxPort1->mTestRfPower.set( 34.0 );
    testTxPort1->mTestDigPower.set( -21.5 );

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );

    EXPECT_FLOAT_EQ( pcl1->getGainError().get(), 5.2467842 );
    EXPECT_FLOAT_EQ( testTxPort1->getAttenuation().get(), 15.517107  );
    EXPECT_FLOAT_EQ( testTxPort1->getRFAttenuation().get(), 15.517107);

    // Change measured powers
    testTxPort1->mTestRfPower.set( 39.2 );
    testTxPort1->mTestDigPower.set( -21.7 );

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );
    EXPECT_FLOAT_EQ( pcl1->getGainError().get(), 2.8178635 );
    EXPECT_FLOAT_EQ( testTxPort1->getAttenuation().get(), 14.108175 );
    EXPECT_FLOAT_EQ( testTxPort1->getRFAttenuation().get(), 14.108175 );

    // Change measured powers
    testTxPort1->mTestRfPower.set( 41.1 );
    testTxPort1->mTestDigPower.set( -21.0 );

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );
    EXPECT_FLOAT_EQ( pcl1->getGainError().get(),0.72485352);
    EXPECT_FLOAT_EQ( testTxPort1->getAttenuation().get(), 13.745749 );
    EXPECT_FLOAT_EQ( testTxPort1->getRFAttenuation().get(), 13.745749 );

    // Change measured powers
    testTxPort1->mTestRfPower.set( 41.1 );
    testTxPort1->mTestDigPower.set( -21.0 );

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );
    EXPECT_FLOAT_EQ( pcl1->getGainError().get(), 0.40000153);
    EXPECT_FLOAT_EQ( testTxPort1->getAttenuation().get(), 13.545748 );
    EXPECT_FLOAT_EQ( testTxPort1->getRFAttenuation().get(), 13.545748 );


    testDpd->mStart = true;    // this time let DPD start OK

    testTxPort1->mTestRfPower.set( 41.4 );
    testTxPort1->mTestDigPower.set( -21.0 );

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::CONVERGE );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );
    EXPECT_FLOAT_EQ( pcl1->getGainError().get(), 0.19771576 );
    EXPECT_FLOAT_EQ( testTxPort1->getAttenuation().get(),  13.545748 );
    EXPECT_FLOAT_EQ( testTxPort1->getRFAttenuation().get(),13.545748);

    // Do not send the DPD event
    pcl1->timerUpdate();
    ASSERT_TRUE( pcl1->getState() == TxPclState::CONVERGE );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );

    // Send DPD event with onOff=ON
    DataVariant txDv(DataVariantType::Type::Uint, "tx","0");
    DataVariant onOffDv(DataVariantType::Type::String, "onoff","ON");

    std::map<std::string, DataVariant> evData;
    evData["tx"] = txDv;
    evData["onoff"] = onOffDv;

    testDpd->sendDpdEvent(evData);
    pcl1->timerUpdate();
    ASSERT_TRUE( pcl1->getState() == TxPclState::TRACK );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );

    std::cout << prefix << "Make PCL 2 fail to ramp, shutdown and go to TX OFF" << std::endl;

    testTxPort2->mTestRfPower.set( 40.0 );
    testTxPort2->mTestDigPower.set( -21.5 );

    pcl2->timerUpdate();
    pcl2->timerUpdate();
    pcl2->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::TRACK );
    ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );

    EXPECT_FLOAT_EQ( testTxPort2->getAttenuation().get(), 17.89356 );
    EXPECT_FLOAT_EQ( testTxPort2->getRFAttenuation().get(), 17.89356 );

    for( int count = 0; count < 27; count++ )
    {
        pcl2->timerUpdate();
        ASSERT_TRUE( pcl2->getState() == TxPclState::RAMP );
    }

    pcl2->timerUpdate();
    pcl2->timerUpdate();
    pcl2->timerUpdate();

    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );


    std::cout << prefix << "Check PCL 1 track mode tracks small gain changes" << std::endl;

    testTxPort1->mTestRfPower.set( 41.45 );
    testTxPort1->mTestDigPower.set( -21.0 );

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::TRACK );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );
    EXPECT_FLOAT_EQ( 0.049999237, pcl1->getGainError().get() );
    EXPECT_FLOAT_EQ( 13.540748, testTxPort1->getAttenuation().get() );
    EXPECT_FLOAT_EQ( 13.540748 , testTxPort1->getRFAttenuation().get() );

    testTxPort1->mTestRfPower.set( 41.455 );
    testTxPort1->mTestDigPower.set( -21.0 );

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::TRACK );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );
    EXPECT_FLOAT_EQ( 0.049999237, pcl1->getGainError().get() );
    EXPECT_FLOAT_EQ( 13.540748, testTxPort1->getAttenuation().get() );
    EXPECT_FLOAT_EQ( 13.540748 , testTxPort1->getRFAttenuation().get() );

    // Don't change power readings and check gain error remains the same, but attenuation creeps up.

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::TRACK );
    ASSERT_TRUE( pcl2->getState() == TxPclState::OFF );
    EXPECT_FLOAT_EQ( 0.049999237, pcl1->getGainError().get() );
    EXPECT_FLOAT_EQ( 13.540748, testTxPort1->getAttenuation().get() );
    EXPECT_FLOAT_EQ( 13.540748, testTxPort1->getRFAttenuation().get() );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );

    // Re-enable the carrier

    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    ASSERT_TRUE( pcl1->getState() == TxPclState::OPENLOOP );

    pcl1->timerUpdate();            // execute the open loop - WAIT_DP wait digital power good
    pcl1->timerUpdate();            // execute the open loop - CHECK_RF check RF measured power is good

    testTxPort1->mTestRfPower.set( 34.0 );
    testTxPort1->mTestDigPower.set( -46.0 );
    testTxPort2->mTestRfPower.set( 34.0 );
    testTxPort2->mTestDigPower.set( -46.0 );
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::RAMP );

    testTxPort1->mTestRfPower.set( 41.4 );
    testTxPort1->mTestDigPower.set( -21.0 );

    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    ASSERT_TRUE( pcl1->getState() == TxPclState::CONVERGE );

    // Ensure that it does not go to track based on the old EV_TRACK event
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    ASSERT_TRUE( pcl1->getState() == TxPclState::CONVERGE );

    testDpd->sendDpdEvent(evData);
    pcl1->timerUpdate();
    EXPECT_EQ( pcl1->getState(), TxPclState::TRACK );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TxPowerControlTest, WaitDP)
{
	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "TX") ;

    // Ensure rssiDone bit is set to allow test to run
	std::shared_ptr<OffTargetFPGA> offTargetFpga = OffTargetFPGA::getInstance();
    offTargetFpga->writeField("rssiDone", 1);
    offTargetFpga->writeField("lowPowerAlarm[0]",0);
    offTargetFpga->writeField("highPowerAlarm[0]",0);
    offTargetFpga->writeField("lowPowerAlarm[1]",0);
    offTargetFpga->writeField("highPowerAlarm[1]",0);

    std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
    std::cerr << "Starting AxisArtProcess application for " << appSettings->getBoardString() << " hardware" << std::endl;

    int argc = 0;
    char noarg[] = "";
    const char** argv = (const char**)&noarg;

    // Define expected options and process the command line
    std::shared_ptr<IAppOptions> opts(IAppOptions::createInstance(argc, argv,
        "Advanced Radio Tester",
        std::vector<std::shared_ptr<IAppOptionSpec> >{
            IAppOptionSpec::factory("ethbb",  DataVariantType::String, "Ethernet interface name (over baseband)", "eth_bb", "ETHBB"),
            IAppOptionSpec::factory("ethcdi", DataVariantType::String, "Ethernet interface name (control and debug)", "eth_cdi", "ETHCDI"),
        }
    )) ;

    // create the cal data objects and their assciated CalDownload objects
    std::shared_ptr<ICalData> calData = ICalDataFactory::getInterface();

    // tell cal download manager to change the root install directory.
    std::string failReason ;
    std::shared_ptr<ICalDownloadManagement> calMgr(ICalDownloadManagement::getInstance()) ;
    calMgr->testInjectInstallDir("../../../TxService/gtest/caldata", failReason) ;


    std::shared_ptr<IRadio> radio = IRadioFactory::getInterface();      // this will load the cal data from the above

    radio->initialise();


    std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance());

    std::shared_ptr<IDpdControl> iDpdCtl = IDpdControl::getInterface();

    std::shared_ptr<TestDpdControl> testDpd( std::dynamic_pointer_cast<TestDpdControl>(iDpdCtl)  );

    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( );
    std::shared_ptr<ITxPort> txPort1 = txPorts[0];
    std::shared_ptr<ITxPort> txPort2 = txPorts[1];

    std::shared_ptr<PclTestTxPort> testTxPort1( std::dynamic_pointer_cast<PclTestTxPort>(txPort1) );
    std::shared_ptr<PclTestTxPort> testTxPort2( std::dynamic_pointer_cast<PclTestTxPort>(txPort2) );

    std::string prefix = "[----------] ";

    std::shared_ptr<ITxPcl> pcl1 = ITxPcl::getInstance(0);

    std::cout << prefix << "Check PCL 1 moves to OFF state" << std::endl;
    pcl1->timerUpdate();
    EXPECT_EQ( TxPclState::OFF, pcl1->getState() );


    testDpd->setPcl( pcl1 );
    testDpd->mStart = false;    // DPD fail to start
    pcl1->timerUpdate();
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );

    std::cout << prefix << "For PCL 1 check setting carrier causes TX ON and sets initial open loop power" << std::endl;
    testDpd->testError = TestError::NONE;

    Frequency frequency(900000ULL, Frequency::KHz);

    txPort1->setFrequency( frequency );
    txPort2->setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 1
    ICarrierSetter& carrierSetter( carrierServer->getCarrierSetter(0) );
    carrierSetter.setType(ICarrier::CARRTYPE_LTE10);
    carrierSetter.setTxPower( 43.0 );
    carrierSetter.setTxFrequency(frequency);
    carrierSetter.setRxFrequency(frequency);
    carrierSetter.setGroupSizeUp( 4 );
    carrierSetter.setGroupSizeDown( 4 );
    carrierSetter.setTxScaling( -18.0 );
    carrierSetter.setTxContainer( 0, 1 );
    carrierSetter.setTxContainer( 1, 0 );
    carrierSetter.setState(ICarrier::STATE_ENABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));

    testTxPort1->mTestRfPower.set( 30.0 );

    // set dig power below min - should then fail WaitDP
    testTxPort1->mTestDigPower.set( -23.5 );


    ASSERT_TRUE( pcl1->getState() == TxPclState::OPENLOOP );

    pcl1->timerUpdate();            // execute the open loop - set the open loop power, using target power

    // set dig power below min - should then fail WaitDP
    testTxPort1->mTestDigPower.set( -50.0 );

    pcl1->timerUpdate();            // execute the open loop - WAIT_DP wait digital power good
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();
    pcl1->timerUpdate();

    // Will have timed out by now so will be off
    ASSERT_TRUE( pcl1->getState() == TxPclState::OFF );

    carrierSetter.setState(ICarrier::STATE_DISABLE);
    EXPECT_TRUE(carrierServer->setCarrier( carrierSetter ));
}
