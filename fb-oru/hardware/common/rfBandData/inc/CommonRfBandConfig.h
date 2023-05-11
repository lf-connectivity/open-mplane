/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRfBandConfig.h
 * \brief     This interface class provides access to the radios RF band constants
 *
 *
 * \details   This interface class provides access to the radios RF band constants
 *
 */

#ifndef _COMMON_RFBANDCONSTANTS_H_
#define _COMMON_RFBANDCONSTANTS_H_

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "IRfBandConfig.h"
#include "GlobalTypeDefs.h"
#include "Frequency.h"

// forward declarations go here, before the namespace

namespace Mplane
{

/*! \brief  Common RF band configuration
 *
 */
class CommonRfBandConfig : public virtual IRfBandConfig
{
public:
	CommonRfBandConfig();
    virtual ~CommonRfBandConfig() {};

    /*! \brief  Get the RF band centre min frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandCenterMinFreq(Frequency freq) override;

    /*! \brief  Get the RF band centre max frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandCenterMaxFreq(Frequency freq) override;

    /*! \brief  Get the RF band edge min frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandEdgeMinFreq(Frequency freq) override;

    /*! \brief  Get the RF band edge max frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandEdgeMaxFreq(Frequency freq) override;

    /*! \brief  Get the RF band sampling frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandSamplingFreq(Frequency freq) override;

    /*! \brief  Get the RF band Nyquist zone
     *
     *  \param Frequency to set
     */
    virtual unsigned getRfBandNyquistZone(Frequency freq) override;

    /*! \brief  Get the RF band decimation factor
     *
     *  \param Frequency to set
     */
    virtual unsigned getRfBandDecimationFactor(Frequency freq) override;

    /*! \brief  Get the RF band interpolation factor
     *
     *  \param Frequency to set
     */
    virtual unsigned getRfBandInterpolationFactor(Frequency freq) override;

    /*! \brief  Get the RF band MMCM multiply and divide factors
     *
     *  \param Frequency to set
     */
    virtual std::pair<unsigned, unsigned> getRfBandMmcmRatio(Frequency freq) override;

    /*! \brief  Get the RF band resampler multiply and divide factors
     *
     *  \param Frequency to set
     */
    virtual std::pair<unsigned, unsigned> getRfBandResamplerRatio(Frequency freq) override;

protected:

    /*! \brief  Class representing 1 RF band configuration
     *
     */
    class RfBand
	{
	public:
    	RfBand(Frequency centerMin, Frequency centerMax, Frequency edgeMin, Frequency edgeMax,
    			Frequency sampling, unsigned nyquistZone, unsigned decimation, unsigned interpolation,
				std::pair<unsigned, unsigned> mmcmRatio, std::pair<unsigned, unsigned> resamplerRatio):
					mCenterMin(centerMin),
					mCenterMax(centerMax),
					mEdgeMin(edgeMin),
					mEdgeMax(edgeMax),
					mSampling(sampling),
					mNyquistZone(nyquistZone),
					mDecimation(decimation),
					mInterpolation(interpolation),
					mMmcm(mmcmRatio),
					mResampler(resamplerRatio)
				{};
    	~RfBand() {};

    	inline Frequency centerMin(void) {return mCenterMin;}
    	inline Frequency centerMax(void) {return mCenterMax;}
    	inline Frequency edgeMin(void) {return mEdgeMin;}
    	inline Frequency edgeMax(void) {return mEdgeMax;}
    	inline Frequency sampling(void) {return mSampling;}
    	inline unsigned nyquistZone(void) {return mNyquistZone;}
    	inline unsigned decimation(void) {return mDecimation;}
    	inline unsigned interpolation(void) {return mInterpolation;}
    	inline unsigned mmcmMultiply(void) {return mMmcm.first;}
    	inline unsigned mmcmDivide(void) {return mMmcm.second;}
    	inline unsigned resamplerMultiply(void) {return mResampler.first;}
    	inline unsigned resamplerDivide(void) {return mResampler.second;}

	private:

    	Frequency mCenterMin;                     //!> Min center frequency of the RF band
    	Frequency mCenterMax;                     //!> Max center frequency of the RF band
    	Frequency mEdgeMin;                       //!> Min edge frequency of the RF band
    	Frequency mEdgeMax;                       //!> Max edge frequency of the RF band
    	Frequency mSampling;                      //!> Sampling frequency of the RF band
    	unsigned mNyquistZone;                    //!> Nyqust zone based on the sampling frequency
    	unsigned mDecimation;                     //!> Decimation factor used in the Rx path
    	unsigned mInterpolation;                  //!> Interpolation factor used in the Tx path
    	std::pair<unsigned, unsigned> mMmcm;      //!> MMCM multiple and divide factors
    	std::pair<unsigned, unsigned> mResampler; //!> Resampler multiple and divide factors
	};

    std::vector<RfBand> mRfBands;              //!> RF Bands

    /*! Method to add a new RF band
     */
    void addRfBand(Frequency centerMin, Frequency centerMax, Frequency edgeMin, Frequency edgeMax,
    			   Frequency sampling, unsigned nyquistZone, unsigned decimation, unsigned interpolation,
				   std::pair<unsigned, unsigned> mmcmRatio, std::pair<unsigned, unsigned> resamplerRatio);

private:

    /*! Find the RF band for the operating frequency
     *
     */
    int findRfBandIndex(Frequency freq);
};

} /* namespace Mplane */


#endif /* _COMMON_RFBANDCONSTANTS_H_ */
