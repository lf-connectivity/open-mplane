/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IResamplerConfig.h
 * \brief     This interface class provides access to the FPGA resampler configuration data
 *
 *
 * \details   This interface class provides access to the FPGA resampler configuration data
 *
 */

#ifndef _VRH_IRESAMPLERCONFIG_H_
#define _VRH_IRESAMPLERCONFIG_H_

// Includes go here, before the namespace
#include <vector>
#include <utility>
#include <string>
#include <memory>

#include "GlobalTypeDefs.h"
#include "Frequency.h"

// forward declarations go here, before the namespace

namespace Mplane
{

/*! \brief  Generic FPGA resampler configuration data interface
 *
 */
class IResamplerConfig
{
public:

    /**
     * Method that creates Resampler config instance for the Rx lineups
     * @return a reference to this radios Rx Resampler configuration data.
     */
    static std::shared_ptr<IResamplerConfig> getRxSingleton();

    /**
     * Method that creates Resampler config instance for the Tx lineups
     * @return a reference to this radios Tx Resampler configuration data.
     */
    static std::shared_ptr<IResamplerConfig> getTxSingleton();

    virtual ~IResamplerConfig() {};

    /*! \brief  Get the number of clocks per sample
     *
     *  \param Resampler Multiply and Divide factors, Instantaneous bandwidth
     */
    virtual unsigned getClockPerSample(std::pair<unsigned, unsigned> resamplerMD, Frequency ibw) =0;

    /*! \brief  Get the resampler coefficients
     *
     *  \param Resampler Multiply and Divide factors, Instantaneous bandwidth
     */
    virtual std::vector<float> getResamplingCoefficients(std::pair<unsigned, unsigned> resamplerMD, Frequency ibw) =0;
};

} /* namespace Mplane */


#endif /* _VRH_IRESAMPLERCONFIG_H_ */
