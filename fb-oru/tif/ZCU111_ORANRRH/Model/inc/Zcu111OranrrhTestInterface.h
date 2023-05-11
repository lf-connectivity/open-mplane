/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111OranrrhTestInterface.h
 * \brief     Test interface for ZCU111_ORANRRH
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
#include "Zcu111TestInterface.h"

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class Zcu111OranrrhTestInterface: public Zcu111TestInterface
{
public:
    Zcu111OranrrhTestInterface();
    ~Zcu111OranrrhTestInterface();
};

} // Mplane

#endif /* __ZCU11_ORANRRH_TEST_INTERFACE__H_*/
