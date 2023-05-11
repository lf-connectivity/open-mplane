/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwareSlotConstants.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SoftwareSlotConstants.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned DEFAULT_SLOTS(4) ;
#ifdef OFF_TARGET
const std::string TOP_DIR("/tmp/slots") ;
#else
const std::string TOP_DIR("/nandflash") ;
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned SoftwareSlotConstants::DefaultNumSlots(DEFAULT_SLOTS) ;
std::string SoftwareSlotConstants::MgmtDir(TOP_DIR + "/sw-mgmt") ;
std::string SoftwareSlotConstants::ManifestsSubdir("manifests") ;
std::string SoftwareSlotConstants::SlotsSubdir("slots") ;
std::string SoftwareSlotConstants::InvalidSubdir("invalid") ;
std::string SoftwareSlotConstants::ReadonlySubdir("read-only") ;
