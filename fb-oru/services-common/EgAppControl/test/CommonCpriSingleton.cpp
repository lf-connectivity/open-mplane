/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpriSingleton.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CommonCpri.h"


using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
/**
 * The following provides the common CPRI interface class.
 */
std::shared_ptr<ICpri> Mplane::ICpri::getInterface()
{
    static std::shared_ptr<ICpri> _pInstance(new CommonCpri());

    return _pInstance;
}
