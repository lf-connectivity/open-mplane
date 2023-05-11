
#ifndef _RADIO_HARDWARE_COMMON_TXEQUALISER_H_
#define _RADIO_HARDWARE_COMMON_TXEQUALISER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxEqualiser.h
 * \brief     A file to define the interface to a common tx equaliser
 *
 *
 * \details   A file to define the interface to a common tx equaliser
 *
 */

#include "CommonEqualiser.h"
#include "ITxPort.h"

namespace Mplane
{

class CommonTxEqualiser : public CommonEqualiser
{
public:
    CommonTxEqualiser(int index, const char* name, FrequencyOffset minFreq,
			FrequencyOffset maxFreq, unsigned int numPoints);

    /*!
     * \brief CommonTxEqualiser destructor
     */
    virtual ~CommonTxEqualiser();

    static const unsigned MAX_NUM_TAPS;

protected:

    virtual void attachToFreqChange(void) override;
};

}

#endif /* _RADIO_HARDWARE_COMMON_TXEQUALISER_H_ */
