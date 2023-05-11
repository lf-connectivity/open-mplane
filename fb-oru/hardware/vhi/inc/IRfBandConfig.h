/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRfBandConfig.h
 * \brief     This interface class provides access to the radios RF band constants
 *
 *
 * \details   This interface class provides access to the radios RF band constants
 *
 */

#ifndef _VRH_IRFBANDCONSTANTS_H_
#define _VRH_IRFBANDCONSTANTS_H_

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

/*! \brief  Generic RF band constants interface
 *
 */
class IRfBandConfig
{
public:

    /**
     * Method that creates RF Band config instance for the Rx lineups
     * @return a reference to this radios Rx RF band config data.
     */
    static std::shared_ptr<IRfBandConfig> getRxSingleton();

    /**
     * Method that creates RF Band config instance for the Tx lineups
     * @return a reference to this radios Tx RF band config data.
     */
    static std::shared_ptr<IRfBandConfig> getTxSingleton();

    virtual ~IRfBandConfig() {};

    /*! \brief  Get the RF band centre min frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandCenterMinFreq(Frequency freq) =0;

    /*! \brief  Get the RF band centre max frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandCenterMaxFreq(Frequency freq) =0;

    /*! \brief  Get the RF band edge min frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandEdgeMinFreq(Frequency freq) =0;

    /*! \brief  Get the RF band edge max frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandEdgeMaxFreq(Frequency freq) =0;

    /*! \brief  Get the RF band sampling frequency
     *
     *  \param Frequency to set
     */
    virtual Frequency getRfBandSamplingFreq(Frequency freq) =0;

    /*! \brief  Get the RF band Nyquist zone
     *
     *  \param Frequency to set
     */
    virtual unsigned getRfBandNyquistZone(Frequency freq) =0;

    /*! \brief  Get the RF band decimation factor
     *
     *  \param Frequency to set
     */
    virtual unsigned getRfBandDecimationFactor(Frequency freq) =0;

    /*! \brief  Get the RF band interpolation factor
     *
     *  \param Frequency to set
     */
    virtual unsigned getRfBandInterpolationFactor(Frequency freq) =0;

    /*! \brief  Get the RF band MMCM multiply and divide factors
     *
     *  \param Frequency to set
     */
    virtual std::pair<unsigned, unsigned> getRfBandMmcmRatio(Frequency freq) =0;

    /*! \brief  Get the RF band resampler multiply and divide factors
     *
     *  \param Frequency to set
     */
    virtual std::pair<unsigned, unsigned> getRfBandResamplerRatio(Frequency freq) =0;
};

} /* namespace Mplane */


#endif /* _VRH_IRFBANDCONSTANTS_H_ */
