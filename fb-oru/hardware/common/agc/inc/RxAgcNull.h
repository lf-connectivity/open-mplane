/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgcNull.h
 * \brief     NULL version of RxAgc
 *
 *
 * \details   Dummy version of RxAgc that any application which doesn't use RX AGC can instantiate
 *
 */


#ifndef RXAGCNULL_H_
#define RXAGCNULL_H_

#include "IRxAgc.h"

namespace Mplane {

class RxAgcNull : public virtual IRxAgc {
public:
	RxAgcNull(unsigned index, const std::string& name,
			unsigned numAdcBits=14, const Power& dBbelowFS=-1.0,
			const Power& thresholdHysteresis = 3.0,
			const Temperature& temperatureHysteresis = 2.0) ;
	virtual ~RxAgcNull() ;

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
} ;

class RxAgcNullFactory
{
public:

    /**
     * This interface must be implemented by each radio implementation
     * type. The caller passes in a variable by reference that will be used to
     * return the number of agcs created. The return value, is a vector of
     * pointers to the common IRxAgc interface.
     *
     * Any radio specific implementation code that is aware of the actual Rx agc
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * @return a vector containing Rx agcs interface pointers.
     */
    static std::vector< std::shared_ptr<IRxAgc> > createAgcs();


    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a previous created list of agcs. The return value, is a vector of
     * pointers to the common IRxAgc interface.
     *
     * Any radio specific implementation code that is aware of the actual Rx agc
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \return a vector containing Rx agcs interface pointers.
     */
    static std::vector< std::shared_ptr<IRxAgc> > getAgcs( );


    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a previous created agc. The return value is a
     * pointer to the common IRxAgc interface.
     *
     * \param index	0-based RX path
     * \return an Rx agcs interface pointer.
     */
    static std::shared_ptr<IRxAgc> getAgc( unsigned index );


};


}

#endif /* RXAGCNULL_H_ */
