/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDpdVswr.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ITxPort.h"
#include "data/TestDpdVswr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::TestDpdVswr::TestDpdVswr() :
	mNumTxPorts( ITxPortFactory::getPorts().size() ),
	mPowers(mNumTxPorts, Power(0.0))
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TestDpdVswr::~TestDpdVswr() {
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::TestDpdVswr::getMeasurement(unsigned port) const
{
	if (port >= mNumTxPorts)
		return Power(0.0) ;

	return mPowers.at(port) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TestDpdVswr::setData(const std::map<std::string, DataVariant>& attributes)
{
	// @TODO
	return true ;
}
