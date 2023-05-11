/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRxAgc.h
 * \brief     Virtual interface to RX agc
 *
 *
 * \details   The RX agc object sets up the hardware such that it keeps the RX input level within a usable range of
 * values. If the input level gets too high then extra input attenuation is added; similarly attenuation is removed if
 * the input level gets too low. The actual attenuation value used is reported by this object so that system gain can
 * be calculated.
 *
 * There will be a single agc entity per RX port, hence the use of the singleton pattern and ports factory
 *
 */


#ifndef IRXAGC_H_
#define IRXAGC_H_

#include <memory>
#include <vector>

#include "GlobalTypeDefs.h"
#include "Temperature.h"
#include "Power.h"

namespace Mplane {

class IRxAgc {
public:

	enum class RxAgcMode
	{
		RX_AGC_MODE_MANUAL,
		RX_AGC_MODE_AUTO,
		RX_AGC_MODE_NOT_SET
	};

	IRxAgc() {}
	virtual ~IRxAgc() {}

	/**
	 * Set the number of air frames that an attenuation state will remain active after the
	 * signal level drops below the programmed hysteresis threshold
	 * @param numFrames
	 */
	virtual void setAttenFrames(unsigned numFrames) =0 ;

	/**
	 * Change the digital gain value
	 * @param digitalGain
	 */
	virtual void setDigitalGain(Power digitalGain) =0 ;

	/**
	 * Change both the digital gain and the rx point adjust
	 * @param digitalGain
	 * @param rxPointAdjust
	 */
	virtual void setDigitalGain(Power digitalGain, Power rxPointAdjust) =0 ;

	/**
	 * Change rx point adjust
	 * @param rxPointAdjust
	 */
	virtual void setRxPointAdjust(Power rxPointAdjust) =0 ;

	/**
	 * Dump out internal data into a stream
	 */
	virtual void show(std::ostream& os) const =0 ;

	/**
	 * Dump out detailed internal data into a stream
	 */
	virtual void showDetail(std::ostream& os) const =0 ;

	/**
	 * Given an FE level (CG step) returns the difference between this level and level 0
	 * @param feLevel
	 * @return adjustment value to be applied based on the current FE level (CG step)
	 */
	virtual Power getFeAdjustment(unsigned feLevel) const =0 ;

	/**
	 * Given an FE level (CG step) returns the RF attenuator setting
	 * @param feLevel
	 * @return RF atten at this level
	 */
	virtual Power getFeAtten(unsigned feLevel) const =0 ;
} ;


class IRxAgcFactory
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

#endif /* IRXAGC_H_ */
