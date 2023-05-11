/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxRfBandConfig.h
 * \brief     This interface class provides access to the radios Rx RF band constants
 *
 *
 * \details   This interface class provides access to the radios Rx RF band constants
 *
 */

#ifndef _COMMON_RXRFBANDCONSTANTS_H_
#define _COMMON_RXRFBANDCONSTANTS_H_

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "CommonRfBandConfig.h"
#include "GlobalTypeDefs.h"
#include "Frequency.h"

// forward declarations go here, before the namespace

namespace Mplane
{

/*! \brief  Common RF band configuration
 *
 */
class CommonRxRfBandConfig : public CommonRfBandConfig
{
public:
	CommonRxRfBandConfig();
    virtual ~CommonRxRfBandConfig() {};

protected:

    /*! Method to add a new RF band
     */
    void addRxRfBand(Frequency centerMin, Frequency centerMax, Frequency edgeMin, Frequency edgeMax,
    			   Frequency sampling, unsigned nyquistZone, unsigned decimation,
				   std::pair<unsigned, unsigned> mmcmRatio, std::pair<unsigned, unsigned> resamplerRatio);
};

} /* namespace Mplane */


#endif /* _COMMON_RXRFBANDCONSTANTS_H_ */
