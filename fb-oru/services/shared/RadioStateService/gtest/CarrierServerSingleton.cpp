/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierServerSingleton.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Zcu111RrhCarrierServer.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierServer> ICarrierServer::getInstance()
{
    static std::shared_ptr<ICarrierServer> carrierServer(std::make_shared<Zcu111RrhCarrierServer>());
    return carrierServer ;
}
