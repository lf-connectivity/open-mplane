/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgc.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cmath>

#include "Maths.h"

#include "IRxPort.h"
#include "ICalData.h"
#include "IRxCalData.h"
#include "IRxAgcCalData.h"
#include "IRxCal.h"
#include "IRadio.h"
#include "IDevices.h"
#include "IRfConst.h"

#include "RxAgc.h"

using namespace Mplane;

//=============================================================================================================
// TYPES
//=============================================================================================================


//=============================================================================================================
// STATIC
//=============================================================================================================

// FPGA is limited to at most 6 CG steps
const unsigned RxAgc::MAX_CG_STEPS(6) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
static const std::string indexedName(const std::string& name, unsigned index)
{
	const std::string iname(name + std::to_string(index)) ;
	return iname ;
}

//-------------------------------------------------------------------------------------------------------------
RxAgc::RxAgc(unsigned index, const std::string& name,
		std::shared_ptr<IRxPort> rxPort,
		std::shared_ptr<IAttenuator> rfAtten,
		const unsigned int numLevels,
		const double attenuationStep,
		unsigned numAdcBits, const Power& dBbelowFS,
		const Power& thresholdHysteresis,
		const Temperature& temperatureHysteresis) :
	CommonPort(static_cast<int>(index), indexedName(name, index).c_str()),
	TaskEvent(Task::PRIORITY_MEDIUM, Task::SMALL_STACK, CommonPort::getName(), "RX"),

	mRxPort(rxPort),
	mRfAtten(rfAtten),
	mTemperatureHysteresis(temperatureHysteresis),
	mThresholdHysteresis(thresholdHysteresis),
	mDigitalGain(0.0),
	mRxPointAdjust(0.0),
	mFrequency(0.0),
	mTemperature(0.0),
	mdBbelowFS(dBbelowFS),
	mIfDsa(0.0),
	mAttenuationStep(attenuationStep),
	mNumLevels(numLevels),
	mNumFrames(0),
	mNumAdcBits(numAdcBits),
	mMode(IRxAgc::RxAgcMode::RX_AGC_MODE_NOT_SET),

	mMutex()
{
	// get agc cal and read CG steps
	std::shared_ptr<IRxAgcCalDataContainer> calData(
		std::dynamic_pointer_cast<IRxAgcCalDataContainer>(ICalDataFactory::getInterface())
	);
	std::shared_ptr<IRxAgcCalData> agcData(calData->getRxAgcCal());
	mDesiredAttens = agcData->getCgSteps((mRxPort->getIndex()) + 1) ;

	// limit size of table if necessary
	if (mDesiredAttens.size() > mNumLevels)
	{
		mDesiredAttens.resize(mNumLevels) ;
	}

	// Register for frequency updates on this RX port
	std::dynamic_pointer_cast<Subject<IFrequencyChange>>(mRxPort)->attach(*this);

	// Register for temperature updates
	std::dynamic_pointer_cast<Subject<ITemperatureChange>>(mRxPort)->attach( *this );

	// Register for AGC mode change
	std::dynamic_pointer_cast<Subject<IRxAgcModeChange, IRxAgc::RxAgcMode>>(IRadioFactory::getInterface())->attach( *this );
}

//-------------------------------------------------------------------------------------------------------------
RxAgc::~RxAgc()
{
	// Remove observers
	std::dynamic_pointer_cast<Subject<IFrequencyChange>>(mRxPort)->detach(*this);
	std::dynamic_pointer_cast<Subject<ITemperatureChange>>(mRxPort)->detach( *this );
}

//-------------------------------------------------------------------------------------------------------------
void RxAgc::update(IFrequencyChange& subject)
{
	// skip if no change
	Frequency newFreq(subject.getFrequency()) ;

	logDebugNormal("RxAgc [%d] update : Freq %llu KHz", mRxPort->getIndex(), newFreq.get());

	if (newFreq == mFrequency)
		return ;

	{
		// protect change
		Mutex::Lock lock(mMutex) ;
		mFrequency = newFreq ;
	}

	// changed so update the table
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void RxAgc::update(ITemperatureChange& subject)
{
	// skip if no change
	Temperature newTemperature(subject.getTemperature()) ;
	if ( abs(newTemperature.get() - mTemperature.get()) <= mTemperatureHysteresis.get())
		return ;

	{
		// protect change
		Mutex::Lock lock(mMutex) ;
		mTemperature = newTemperature ;
	}

	// changed so update the table
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void RxAgc::update(IRxAgcModeChange& subject, IRxAgc::RxAgcMode mode)
{
	// If mode has not changed, then return
	if (mMode == mode)
	{
		return;
	}

	{
		// protect change
		Mutex::Lock lock(mMutex) ;
		mMode = mode ;
	}

	// If mode is changed to auto, then set the RF attenuator to CG0 level
	// and reprogram the CG table.
	if (mode == IRxAgc::RxAgcMode::RX_AGC_MODE_AUTO)
	{
		// Set Rf attenuator to CG level 0 if mode is changed to Auto
		mRxPort->setRfAttenuation(getFeAtten(0));

		// changed so update the table
		event() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void RxAgc::setDigitalGain(Power digitalGain)
{
	// skip if no change
	if (digitalGain == mDigitalGain)
		return ;

	{
		// protect change
		Mutex::Lock lock(mMutex) ;
		mDigitalGain = digitalGain ;
	}

	// changed so update the table
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void RxAgc::setDigitalGain(Power digitalGain, Power rxPointAdjust)
{
	// skip if no change
	if ((digitalGain == mDigitalGain) && (rxPointAdjust == mRxPointAdjust))
		return ;

	{
		// protect change
		Mutex::Lock lock(mMutex) ;
		mDigitalGain = digitalGain ;
		mRxPointAdjust = rxPointAdjust ;
	}

	// changed so update the table
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void RxAgc::setRxPointAdjust(Power rxPointAdjust)
{
	// skip if no change
	if (rxPointAdjust == mRxPointAdjust)
		return ;

	{
		// protect change
		Mutex::Lock lock(mMutex) ;
		mRxPointAdjust = rxPointAdjust ;
	}

	// changed so update the table
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void RxAgc::setAttenFrames(unsigned numFrames)
{
	mNumFrames = numFrames ;
}


//-------------------------------------------------------------------------------------------------------------
const char* RxAgc::name() const
{
	return this->CommonPort::getName().data() ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxAgc::show(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxAgc::showDetail(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::RxAgc::getFeAdjustment(unsigned feLevel) const
{
	std::shared_ptr<IRxCalDataContainer> calData = std::dynamic_pointer_cast
			< IRxCalDataContainer > (ICalDataFactory::getInterface());

	std::shared_ptr<IRxCalData> rxCal = calData->getRxCal();
	std::shared_ptr<IRxOpenLoop> rxol ;
	if (rxCal->isLoaded())
	{
		rxol = rxCal->getRxOpenLoop((mRxPort->getIndex()) + 1);
	}

	if (!rxol)
	{
		return Power(0.0) ;
	}

	// if AGC is disabled then just use CG0
	if (IRadioFactory::getInterface()->getRxAttenMode() == IRxAgc::RxAgcMode::RX_AGC_MODE_MANUAL)
	{
		feLevel = 0 ;
	}


	Mutex::Lock lock(mMutex) ;

	if (feLevel >= mDesiredAttens.size())
	{
		return Power(0.0) ;
	}

	// get dBfsTodBm value from cal file for this CG step and return it as the offset to be applied
	Power dBfsTodBm = rxol->dBfsTodBm(mFrequency, getDesiredAtten(feLevel), mTemperature.get()) ;

	logDebugNormal("RSSI [%d] : Freq %llu KHz Temp %.1f C dBfsTodBm %.2f dBm",
		mRxPort->getIndex(),
		mFrequency.get(Frequency::KHz),
		mTemperature.get(),
		dBfsTodBm.get()	) ;

	return dBfsTodBm ;
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::RxAgc::getFeAtten(unsigned feLevel) const
{
	Mutex::Lock lock(mMutex) ;

	if (feLevel >= mDesiredAttens.size())
		return Power(0.0) ;

	return getDesiredAtten(feLevel);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RxAgc::runEvent()
{
	calculateTable();

	writeTable();

	updateIfAtten();

	return true;
}

//-------------------------------------------------------------------------------------------------------------
Power RxAgc::getDigitalGain() const
{
	std::shared_ptr<IRfConst> rfConst(IRfConstFactory::getInterface()) ;

	// Total digital gain = digital gain - carrier RSSI gain
	return mDigitalGain - rfConst->getCarrierRssiGain() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned RxAgc::calcThreshold(unsigned numAdcBits, const Power& dBbelowFS)
{
	// Fullscale for this ADC
	unsigned fs((1 << numAdcBits)-1) ;

	// Calculate the threshold as N dB below FS
	float threshold = (float)fs * pow(10.0, dBbelowFS.get() / 20.0) ;

	return static_cast<unsigned>(threshold) ;
}
