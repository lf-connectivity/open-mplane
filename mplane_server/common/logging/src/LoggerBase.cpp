/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoggerBase.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>

#include "LoggerBase.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LoggerBase::LoggerBase(
    ILoggable* parent,
    const std::string& instanceName,
    const std::string& groupName)
    : mParent(parent), mInstanceName(instanceName), mGroupName(groupName) {
  if (!parent)
    throw std::invalid_argument("Logger created with null parent");
}

//-------------------------------------------------------------------------------------------------------------
LoggerBase::~LoggerBase() {}
