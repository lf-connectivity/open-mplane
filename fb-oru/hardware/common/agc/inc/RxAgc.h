/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgc.h
 * \brief     RX agc object
 *
 *
 * \details   Sets up the hardware to ensure RX input levels are managed
 *
 */


#ifndef _HW_COMMON_AGC_RXAGC_H_
#define _HW_COMMON_AGC_RXAGC_H_

#include "Temperature.h"
#include "Frequency.h"
#include "Observer.hpp"
#include "TaskEvent.h"

#include "ICarrierBundleFreq.h"
#include "ITemperatureChange.h"
#include "IFrequencyChange.h"
#include "IRxAgcModeChange.h"
#include "IRxPort.h"
#include "IAttenuator.h"
#include "IRxAgc.h"

#include "CommonPort.h"

namespace Mplane {

class RxAgc : public virtual IRxAgc,
	public CommonPort,
	public TaskEvent,
	public Observer<IFrequencyChange>,
	public Observer<ITemperatureChange>,
	public Observer<IRxAgcModeChange, IRxAgc::RxAgcMode>
{
public:

	static const unsigned MAX_CG_STEPS;

	RxAgc(unsigned index, const std::string& name,
	      std::shared_ptr<IRxPort> rxPort,
	      std::shared_ptr<IAttenuator> rfAtten,
	      const unsigned int numLevels = MAX_CG_STEPS,
	      const double attenuationStep = 6.0,
	      unsigned numAdcBits=14, const Power& dBbelowFS=-1.0,
	      const Power& thresholdHysteresis = 3.0,
	      const Temperature& temperatureHysteresis = 2.0
	      ) ;
	virtual ~RxAgc() ;

	// IRxAgc interface

	/**
	 * Set the number of air frames that an attenuation state will remain active after the
	 * signal level drops below the programmed hysteresis threshold
	 * @param numFrames
	 */
	virtual void setAttenFrames(unsigned numFrames) override ;

	/**
	 * Change the digital gain value
	 * @param digitalGain
	 */
	virtual void setDigitalGain(Power digitalGain) override ;

	/**
	 * Change both the digital gain and the rx point adjust
	 * @param digitalGain
	 * @param rxPointAdjust
	 */
	virtual void setDigitalGain(Power digitalGain, Power rxPointAdjust) override ;

	/**
	 * Change rx point adjust
	 * @param rxPointAdjust
	 */
	virtual void setRxPointAdjust(Power rxPointAdjust) override ;

	/**
	 * Dump out internal data into a stream
	 */
	virtual void show(std::ostream& os) const override ;

	/**
	 * Dump out detailed internal data into a stream
	 */
	virtual void showDetail(std::ostream& os) const override ;

	/**
	 * Given an FE level (CG step) returns the difference between this level and level 0
	 * @param feLevel
	 * @return adjustment value to be applied based on the current FE level (CG step)
	 */
	virtual Power getFeAdjustment(unsigned feLevel) const override ;

	/**
	 * Given an FE level (CG step) returns the RF attenuator setting
	 * @param feLevel
	 * @return RF atten at this level
	 */
	virtual Power getFeAtten(unsigned feLevel) const override ;


	// Observer interface

	/**
	 * The callback method called whenever the frequency changes
	 *
	 * @param subject
	 */
	virtual void update(IFrequencyChange& subject) override;

	/**
	 * The callback method called whenever the temperature changes
	 *
	 * @param subject
	 */
	virtual void update(ITemperatureChange& subject) override;

	/**
	 * The callback method called whenever the AGC mode changes
	 *
	 * @param subject
	 */
	virtual void update(IRxAgcModeChange& subject, IRxAgc::RxAgcMode mode) override;

	/**
	 * A method used to get the name of the observer
	 */
	virtual const char* name() const override;


protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 * Re-calculate the fpga table data. Expected to be called after a change in parameters
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;


protected:

	/**
	 * Given the number of bits used in the ADC and the dBs below FS required we can calculate the ADC value required
	 * for the threshold
	 * @param numAdcBits
	 * @param dBbelowFS
	 */
	static unsigned calcThreshold(unsigned numAdcBits, const Power& dBbelowFS) ;

	/**
	 * Get the total digital gain value
	 */
	virtual Power getDigitalGain() const ;

	/**
	 * Calculate table
	 * Protected hook to be implemented by derived class
	 */
	virtual void calculateTable( void )  = 0;

	/**
	 * Program table
	 * Protected hook to be implemented by derived class
	 */
	virtual void writeTable( void )  = 0;

	/**
	 * Update the IF attenuation for current frequency from the table
	 * Protected hook to be implemented by derived class
	 */
	virtual void updateIfAtten() = 0;

	/**
	 * Read the desired RF attenuation for the FE level from the table
	 * Protected hook to be implemented by derived class
	 */
	virtual Power getDesiredAtten(unsigned feLevel) const = 0;

protected:

	std::shared_ptr<IRxPort>        mRxPort;
	std::shared_ptr<IAttenuator>    mRfAtten;
	Temperature                     mTemperatureHysteresis;
	Power                           mThresholdHysteresis;
	Power                           mDigitalGain;
	Power                           mRxPointAdjust;
	Frequency                       mFrequency;
	Temperature                     mTemperature;
	Power                           mdBbelowFS;
	Power                           mIfDsa;
	double                          mAttenuationStep;
	unsigned int                    mNumLevels;
	unsigned int                    mNumFrames;

	// List of desired attenuations for each level (CG steps)
	std::vector<Power>              mDesiredAttens;
	unsigned                        mNumAdcBits;
	IRxAgc::RxAgcMode               mMode;

private:
	// Protect the table data
	mutable Mutex mMutex ;

};

}

#endif /* _HW_COMMON_AGC_RXAGC_H_ */
