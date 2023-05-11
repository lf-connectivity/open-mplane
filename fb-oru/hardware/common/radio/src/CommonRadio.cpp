/*
 * CommonRadio.cpp
 *
 *  Created on: 15 Jun 2013
 *      Author: gdurban
 */

#include "IRadio.h"
#include "ICalData.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "IDevices.h"
#include "IModules.h"
#include "IRadioInfo.h"
#include "IFibre.h"
#include "ICarrierServer.h"
#include "ICpri.h"

#include "CommonRadioInfo.h"
#include "CommonRadio.h"

using namespace Mplane;

bool Mplane::CommonRadio::shutdown(void)
{
    return true;
}

Mplane::CommonRadio::CommonRadio() :
        mRadioInfo(IRadioInfoFactory::create()),
        m_MaxTxPorts(0), m_MaxRxPorts(0), m_MaxSRxPorts(0), m_MaxAldPorts(0),
        mDevices(IDevicesFactory::create()),
        // the initial values set above should now get changed by the factory implementations.
        // NOTE: The following factory calls SET the max number of ports (rather than use the current value)
        m_TxPorts(ITxPortFactory::createPorts(m_MaxTxPorts)),
        m_RxPorts(IRxPortFactory::createPorts(m_MaxRxPorts)),
        m_SRxPorts( ISRxPortFactory::createPorts(m_MaxSRxPorts)),
		m_AldPorts( IAldPortFactory::createPorts(m_MaxAldPorts)),
        mModules( IModulesFactory::create()),
        mCarrierServer(),
        mCalMode(false),
		mPreviousCalMode(false),
		mRxAgcMode(IRxAgc::RxAgcMode::RX_AGC_MODE_NOT_SET)
{
}

ReturnType::State Mplane::CommonRadio::initialise()
{
    // initialise everything
    ReturnType::State state = this->_initialise();

    if (state != ReturnType::RT_OK)
        return state;

    // Create CarrierServer now everything is initialised
    mCarrierServer = ICarrierServer::getInstance();

    return state;
}


ReturnType::State Mplane::CommonRadio::systemDeviceInitialise()
{
    return ReturnType::RT_OK;
}


/*
 * This is the doInit method that is called due to the inheritance from
 * Initialise.
 * It is called from the base method Initialise::initialise() to do
 * the actual initialisation for this class.
 *
 * Here we initialise the objects for the devices created by the factories.
 *
 */
ReturnType::State Mplane::CommonRadio::doInit()
{
    ReturnType::State result;
    std::string resultString = "COMMONRADIO INITIALISE RESULT: ";

    result = mDevices->initialise();
    if (result == ReturnType::RT_OK)
    {

//        // Initialise peripheral bus here, including I2C bus as it is likely to be used by system
//        // level devices initialisation that follows.
//        if (result == ReturnType::RT_OK)
//        {
//            std::shared_ptr<IPeripheralBus> periphBus(IPeripheralBus::getInstance()) ;
//            periphBus->initialise() ;
//        }

        result = systemDeviceInitialise();
        if (result == ReturnType::RT_OK)
        {
            // now that the hardware devices are initialised load the
            // calibration data as it may be used in the higher level initialisation
            result = getCalData().load();

            if (result == ReturnType::RT_OK)
            {

// The concept of Modules is not current supported.
//                result = mModules->initialise();
//                if (result == ReturnType::RT_OK)
//                {

                    // Init the Tx Ports
                    for (int ii = 0;
                            ii < m_MaxTxPorts && result == ReturnType::RT_OK; ii++)
                    {
                        result = this->getTxPort(ii).initialise();
                    }
                    if (result == ReturnType::RT_OK)
                    {

                        // Init the Rx Ports
                        for (int ii = 0;
                                ii < m_MaxRxPorts && result == ReturnType::RT_OK;
                                ii++)
                        {
                            result = this->getRxPort(ii).initialise();
                        }
                        if (result == ReturnType::RT_OK)
                        {

                            // Init the Rx Ports
                            for (int ii = 0;
                                    ii < m_MaxSRxPorts
                                    && result == ReturnType::RT_OK; ii++)
                            {
                                result = this->getSRxPort(ii).initialise();
                            }

                            if (result == ReturnType::RT_OK)
                            {
                                // Init the Fibre
                                // Create an interface to the radio CPRI cores, so that it is initialised, it
                                // will be used later by the fibre service.
                                result = IFibre::getInterface()->initialise();
                            }
                        }
//                  }
                }
            }
        }
    }

    /*
     * \todo Implement the error case when initialise fails in CommonRadio doInit().
     * At least log it and return.
     */

    // if common radio initialisatio is OK, do application specific initialisation
    if (result == ReturnType::RT_OK)
    {
        //
        // Call the higher level radio hardware implementations application specific
        // initialisation code. As this is is a pure virtual method in the common radio
        // it must be implemented by the final implementation.
        //
        result = appSpecificInitialise();
    }

    // Append the result to the result string and store it for longevity
    resultString += ReturnType::getState(result);
    setInitResultString(resultString);

    return result;
}

IRadioInfo& Mplane::CommonRadio::getInfo(void) const
{
    return *mRadioInfo;
}

int Mplane::CommonRadio::getNumberOfTxPorts() const
{
    return m_MaxTxPorts;
}

ITxPort& Mplane::CommonRadio::getTxPort(int index)
        /* throw (std::invalid_argument) */
{
    if (index >= 0 && index < m_MaxTxPorts)
    {
        return *m_TxPorts[index];
    }
    throw(std::invalid_argument("invalid index"));
    return *m_TxPorts[0];
}

int Mplane::CommonRadio::getNumberOfRxPorts() const
{
    return m_MaxRxPorts;
}

IRxPort& Mplane::CommonRadio::getRxPort(int index)
        /* throw (std::invalid_argument) */
{
    if (index >= 0 && index < m_MaxRxPorts)
    {
        return *m_RxPorts[index];
    }
    throw(std::invalid_argument("invalid index"));
    return *m_RxPorts[0];
}

int Mplane::CommonRadio::getNumberOfAldPorts() const
{
    return m_MaxAldPorts;
}

IAldPort& Mplane::CommonRadio::getAldPort(int index)
{
    if (index >= 0 && index < m_MaxAldPorts)
    {
        return *m_AldPorts[index];
    }
    throw(std::invalid_argument("invalid index"));
    return *m_AldPorts[0];
}


Mplane::CommonRadio::~CommonRadio()
{
}

IDevices& Mplane::CommonRadio::getDevices()
{
    return *mDevices;
}

IModules& Mplane::CommonRadio::getModules()
{
    return *mModules;
}

ReturnType::State Mplane::CommonRadio::updateTemperatureData()
{
    return ReturnType::RT_OK;
}

ReturnType::State Mplane::CommonRadio::updatePowerSupplyData()
{
    return ReturnType::RT_OK;
}

ReturnType::State Mplane::CommonRadio::appSpecificInitialise()
{
    return ReturnType::RT_OK;
}

int Mplane::CommonRadio::getNumberOfSRxPorts() const
{
    return m_MaxSRxPorts;
}

ISRxPort& Mplane::CommonRadio::getSRxPort(int index)
        /* throw (std::invalid_argument) */
{
    if (index >= 0 && index < m_MaxSRxPorts)
    {
        return *m_SRxPorts[index];
    }
    throw(std::invalid_argument("invalid index"));
    return *m_SRxPorts[0];
}

std::shared_ptr<ICarrierServer> Mplane::CommonRadio::getCarrierServer(void)
{
    return mCarrierServer;
}

void Mplane::CommonRadio::setCalMode(bool mode)
{
	mPreviousCalMode = mCalMode;
    mCalMode = mode;

    if (mPreviousCalMode != mCalMode)
    {
    	static_cast< Subject<ICalModeChange>* >(this)->notify() ;
    }
}

bool Mplane::CommonRadio::getCalMode()
{
    return mCalMode;
}

float Mplane::CommonRadio::getSupplyVoltage()
{
    return mSupplyVoltage.get();
}

void Mplane::CommonRadio::setRxAttenMode( IRxAgc::RxAgcMode mode )
{
	if (mRxAgcMode != mode)
	{
		mRxAgcMode = mode;

		static_cast< Subject<IRxAgcModeChange, IRxAgc::RxAgcMode>* >(this)->notify(mode) ;
	}
}

IRxAgc::RxAgcMode Mplane::CommonRadio::getRxAttenMode( void )
{
	return mRxAgcMode;
}
