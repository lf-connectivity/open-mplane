/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NullFileStatus.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "NullFileStatus.h"

using namespace Mplane;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileStatus>
NullFileStatus::nullObject() {
  return (std::make_shared<NullFileStatus>());
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileStatus>
IFileStatus::nullObject() {
  return NullFileStatus::nullObject();
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------

Mplane::NullFileStatus::NullFileStatus() {}

Mplane::NullFileStatus::~NullFileStatus() {}

void
Mplane::NullFileStatus::setOutputFunction(
    IFileStatus::StatusOutputFunc func) {}

void
Mplane::NullFileStatus::clearOutputFunction() {}

void
Mplane::NullFileStatus::restart(unsigned num) {}

void
Mplane::NullFileStatus::operation(const std::string& op) {}

void
Mplane::NullFileStatus::start(const std::string& filename) {}

void
Mplane::NullFileStatus::progress(unsigned progressPercent) {}

void
Mplane::NullFileStatus::end() {}

void
Mplane::NullFileStatus::fail(const std::string& error) {}

void
Mplane::NullFileStatus::success() {}

bool
Mplane::NullFileStatus::isComplete() const {
  return true;
}

std::string
Mplane::NullFileStatus::getError() const {
  return "";
}

std::string
Mplane::NullFileStatus::getFilename() const {
  return "";
}

std::string
Mplane::NullFileStatus::getOperation() const {
  return "";
}

unsigned
Mplane::NullFileStatus::getProgress() const {
  return 100;
}

unsigned
Mplane::NullFileStatus::getTotalProgress() const {
  return 100;
}

unsigned
Mplane::NullFileStatus::getNumFiles() const {
  return 1;
}

void
Mplane::NullFileStatus::start(
    const std::string& op, const std::string& filename) {}

void
Mplane::NullFileStatus::skip() {}

void
Mplane::NullFileStatus::skip(unsigned numFiles) {}

void
Mplane::NullFileStatus::copy(std::shared_ptr<IFileStatus>) {}
