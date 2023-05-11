/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICwGen.h
 * \brief     CW tone generator virtual interface
 *
 *
 */


#ifndef ICWGEN_H_
#define ICWGEN_H_

#include <memory>

namespace Mplane {

/*!
 * \class  ICwGen
 * \brief
 * \details
 *
 */
class ICwGen {
public:
	ICwGen() {}
	virtual ~ICwGen() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<ICwGen> getInstance() ;

	/**
	 * Set the frequency in kHz (may be -ve)
	 * @return true if set ok; false otherwise
	 */
	virtual bool setFrequency(unsigned cwIndex, double freqKHz) =0 ;

    /**
     * Set the frequency to match the specified IM product
     * @param[in] cwIndex the index of the CW block to be configured
     * @param[in] cwIndex1 the index of the LOWER frequency of the two CW sources
     * @param[in] cwIndex2 the index of the UPPER frequency of the two CW sources
     * @param[in] imOrder the order of the IM product that is to be cancelled
     * @return true if set ok; false otherwise
     */
    virtual bool setImFrequency(unsigned cwIndex, unsigned cw1Index, unsigned cw2Index, int imOrder) =0 ;

	/**
	 * Set the amplitude of the particular CW generator in dBFS
	 * @return true if set ok; false otherwise
	 */
	virtual bool setAmplitude(unsigned cwIndex, float dBFS) =0 ;

	/**
	 * Set the phase of the particular CW generator in rads
	 * @return true if set ok; false otherwise
	 */
	virtual bool setPhase(unsigned cwIndex, float rads) =0 ;

	/**
	 * Set the frequency in kHz (may be -ve)
	 * @return true if set ok; false otherwise
	 */
	virtual double getFrequency(unsigned cwIndex) const =0 ;

	/**
	 * Set the amplitude of the particular CW generator in dBm
	 * @return true if set ok; false otherwise
	 */
	virtual float getAmplitude(unsigned cwIndex) const =0 ;

	/**
	 * Set the phase of the particular CW generator in rads
	 * @return true if set ok; false otherwise
	 */
	virtual float getPhase(unsigned cwIndex) const =0 ;

    /**
     * Enable/disable the particular CW generator output
     * @return true if set ok; false otherwise
     */
    virtual bool setOutput(unsigned cwIndex, bool onoff) =0 ;

} ;

}

#endif /* ICWGEN_H_ */
