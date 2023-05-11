/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AtlasOranrrhTestInterface.h
 * \brief     Test interface for Atlas_ORANRRH
 *
 *
 * \details
 *
 */

#ifndef __ZCU11_ORANRRH_TEST_INTERFACE__H_
#define __ZCU11_ORANRRH_TEST_INTERFACE__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "AtlasTestInterface.h"

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class AtlasOranrrhTestInterface: public AtlasTestInterface
{
public:
    AtlasOranrrhTestInterface();
    ~AtlasOranrrhTestInterface();
};

} // MPLANE

#endif /* __ZCU11_ORANRRH_TEST_INTERFACE__H_*/
