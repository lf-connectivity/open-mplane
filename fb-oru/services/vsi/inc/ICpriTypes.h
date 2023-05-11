/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICpriTypes.h
 * \brief     Type definitions used in CPRI virtual classes
 *
 *
 * \details
 *
 */


#ifndef ICPRITYPES_H_
#define ICPRITYPES_H_

#include "GlobalTypeDefs.h"

namespace Mplane {

class ICpriTypes {
public:

    /**
     * Line rate capability mask values. Each bit is equal to one rate.
     * To auto-negotiate set the mask to multiple rates.
     */
    enum cpriRateCapabilityMask
    {
        cpriRateMask614  =  1,
        cpriRateMask1228 =  cpriRateMask614  << 1,
        cpriRateMask2457 =  cpriRateMask1228 << 1,
        cpriRateMask3072 =  cpriRateMask2457 << 1,
        cpriRateMask4915 =  cpriRateMask3072 << 1,
        cpriRateMask6144 =  cpriRateMask4915 << 1,
        cpriRateMask9830 =  cpriRateMask6144 << 1,
        cpriRateMask10137=  cpriRateMask9830 << 1
    };

    /**
     * structure to carry CPRI L2 info data
     */
    struct cpriL2Info
    {
        UINT32 linkId;
        UINT32 pmre;
        UINT32 remoteEquipmentId;
    };

} ;

}

#endif /* ICPRITYPES_H_ */
