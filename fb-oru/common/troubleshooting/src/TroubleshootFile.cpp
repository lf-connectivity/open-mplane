/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootFile.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>

#include "TroubleshootFile.h"

using namespace Mplane;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TroubleshootFile::TroubleshootFile(const std::string & filename)
	: ORanLogFile(filename)
{
}

//-------------------------------------------------------------------------------------------------------------
TroubleshootFile::~TroubleshootFile()
{
}
