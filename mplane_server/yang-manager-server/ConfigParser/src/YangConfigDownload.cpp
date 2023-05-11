/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file    YangConfigDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "YangConfigDownload.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::YangConfigDownload::YangConfigDownload()
    : ConfigDownload("YangConfigDownload") {}

//-------------------------------------------------------------------------------------------------------------
Mplane::YangConfigDownload::~YangConfigDownload() {}

//-------------------------------------------------------------------------------------------------------------
bool
Mplane::YangConfigDownload::initialise(std::string& failReason) {
  if (!setInstallFileName("YangConfig.xml", failReason)) {
    return false;
  }

  return this->super::initialise(failReason);
}
