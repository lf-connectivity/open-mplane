/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIFaultChange.h
 * \brief     Test Interface for RadioState
 *
 *
 * \details   Defines the expected interface for the radio state
 *
 */

#include "TestIFaultChange.h"

using namespace Mplane;

/*! \brief  Stub of the IRadioState Interface
 *
 * This class provides an implementation of the IFaultChange interface, for use
 * by unit tests.
 * Users/coders of the unit tests that use an IFaultChange interface must ensure
 * that they code the TestIFaultChange implementation that meets their unit test
 * cases.
 */

//-------------------------------------------------------------------------------------------------------------
const std::string& TestIFaultChange::getFaultName( void )
{
	return mFaultName;
}

//-------------------------------------------------------------------------------------------------------------
void TestIFaultChange::setFaultName( const std::string& faultName )
{
	mFaultName = faultName;
}
