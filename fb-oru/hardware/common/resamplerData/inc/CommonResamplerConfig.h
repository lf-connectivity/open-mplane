/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonResamplerConfig.h
 * \brief     This interface class provides access to the FPGA resampler configuration data
 *
 *
 * \details   This interface class provides access to the FPGA resampler configuration data
 *
 */

#ifndef _COMMON_RESAMPLERCONFIG_H_
#define _COMMON_RESAMPLERCONFIG_H_

// Includes go here, before the namespace
#include <vector>
#include <utility>
#include <string>
#include <tuple>
#include <functional>
#include <map>

#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "IResamplerConfig.h"

// forward declarations go here, before the namespace

namespace Mplane
{

/*! \brief  FPGA resampler configuration data interface
 *
 */
class CommonResamplerConfig : public virtual IResamplerConfig
{
public:
	CommonResamplerConfig();
    virtual ~CommonResamplerConfig() {};

    /*! \brief  Get the number of clocks per sample
     *
     *  \param Resampler Multiply and Divide factors, Instantaneous bandwidth
     */
    virtual unsigned getClockPerSample(std::pair<unsigned, unsigned> resamplerMD, Frequency ibw) override;

    /*! \brief  Get the resampler coefficients
     *
     *  \param Resampler Multiply and Divide factors, Instantaneous bandwidth
     */
    virtual std::vector<float> getResamplingCoefficients(std::pair<unsigned, unsigned> resamplerMD, Frequency ibw) override;

protected:

    /*! \brief  Class representing 1 resampler configuration
     *
     */
    class Resampler
	{
	public:
    	Resampler(std::pair<unsigned, unsigned> resamplerRatio):
					mResampler(resamplerRatio)
				{};
    	~Resampler() {};

    	void addIbwData(Frequency ibw, unsigned clocksPerSample, const std::vector<float>& coeff);
    	unsigned getClockPerSample(Frequency ibw);
    	std::vector<float> getResamplingCoefficients(Frequency ibw);

    	inline unsigned resamplerMultiply(void) {return mResampler.first;}
    	inline unsigned resamplerDivide(void) {return mResampler.second;}

	private:

    	std::pair<unsigned, unsigned> mResampler;                                       //!> Resampler multiply and divide factors
    	std::map<Frequency, std::tuple<unsigned, std::vector<float>>> mIbwData;         //!> Data for each supported IBW
	};

    std::vector<Resampler> mResamplers;              //!> Resamplers

    /*! Method to add a new Resampler configuration
     */
    void createResampler(std::pair<unsigned, unsigned> resamplerRatio);

    /*! Method to add data for each supported instantaneous bandwidth (IBW)
     */
    void addIbwData(std::pair<unsigned, unsigned> resamplerRatio, Frequency ibw,
    		unsigned clocksPerSample, const std::vector<float>& coeff);

private:

    /*! Find the resampler for the given ratio
     *
     */
    int findResamplerIndex(std::pair<unsigned, unsigned> resamplerRatio);
};

} /* namespace Mplane */


#endif /* _COMMON_RESAMPLERCONFIG_H_ */
