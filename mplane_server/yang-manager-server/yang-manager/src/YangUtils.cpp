/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangUtils.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangUtils.h"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangUtils::YangUtils() {}

//-------------------------------------------------------------------------------------------------------------
YangUtils::~YangUtils() {}

//-------------------------------------------------------------------------------------------------------------
std::string
YangUtils::getDateTime(time_t timestamp) {
  return getDateTime(localtime(&timestamp));
}

//-------------------------------------------------------------------------------------------------------------
std::string
YangUtils::getDateTime(struct tm* timeInfo) {
  char buffTimeDate[35];
  std::string strTimeDate;

  // YYYY-yy-ddTHH:MM:SS(+|-)hh:mm
  // Example: 10 September 1972, 14:42:22 London (13:42:22 UTC)
  //          1972-09-10T14:42:22+01:00
  strftime(buffTimeDate, sizeof(buffTimeDate), "%Y-%m-%dT%H:%M:%S%z", timeInfo);
  strTimeDate = buffTimeDate;
  strTimeDate.insert((strTimeDate.size() - 2), ":");

  // std::cerr << strTimeDate << std::endl;

  return strTimeDate;
}
