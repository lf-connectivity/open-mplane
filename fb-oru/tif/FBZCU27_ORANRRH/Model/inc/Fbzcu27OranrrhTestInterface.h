/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fbzcu27OranrrhTestInterface.h
 * \brief     Test interface for Fbzcu27_ORANRRH
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
#include "Fbzcu27TestInterface.h"

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class Fbzcu27OranrrhTestInterface: public Fbzcu27TestInterface
{
public:
    Fbzcu27OranrrhTestInterface();
    ~Fbzcu27OranrrhTestInterface();
};

} // MPLANE

#endif /* __ZCU11_ORANRRH_TEST_INTERFACE__H_*/
