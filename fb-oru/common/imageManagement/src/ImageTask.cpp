/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageTask.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ImageTask.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Set the priority of the task to high - when we start image transfer we want
// it to happen as fast as possible
static constexpr int IMAGE_MANAGER_PRIORITY = Task::PRIORITY_HIGH ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::ImageTask::ImageTask() :
	Task(IMAGE_MANAGER_PRIORITY, Task::MEDIUM_STACK, "Image Manager","IMG")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::ImageTask::~ImageTask()
{
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::ImageTask::keepAlive()
{
	kickSoftwareWatchdog() ;
}
