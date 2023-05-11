
#ifndef _RADIO_HARDWARE_COMMON_RXEQUALISER_H_
#define _RADIO_HARDWARE_COMMON_RXEQUALISER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxEqualiser.h
 * \brief     A file to define the interface to a common rx equaliser
 *
 *
 * \details   A file to define the interface to a common rx equaliser
 *
 */

#include "CommonEqualiser.h"
#include "IRxPort.h"

namespace Mplane
{

class CommonRxEqualiser : public CommonEqualiser
{
public:
	CommonRxEqualiser(int index, const char* name, FrequencyOffset minFreq,
			FrequencyOffset maxFreq, unsigned int numPoints);

    /*!
     * \brief CommonEqualiser destructor
     */
    virtual ~CommonRxEqualiser();

    static const unsigned MAX_NUM_TAPS;

protected:

    virtual void attachToFreqChange(void) override;
};

}

#endif /* _RADIO_HARDWARE_COMMON_RXEQUALISER_H_ */
