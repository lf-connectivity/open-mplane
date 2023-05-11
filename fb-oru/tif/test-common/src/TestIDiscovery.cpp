/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIDiscovery.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
static unsigned count{0} ;

#include "TestIDiscovery.h"

using namespace Mplane;

Mplane::TestIDiscovery::TestIDiscovery() {
}

Mplane::TestIDiscovery::~TestIDiscovery() {
}

std::string Mplane::TestIDiscovery::getIp() const {
	return "123.456.789.001" ;
}

std::string Mplane::TestIDiscovery::getUuid() const {
	return "00000000-0000-0000-000000000000" ;
}

unsigned Mplane::TestIDiscovery::getCacheAge() const {
	return 2100 ;
}

unsigned Mplane::TestIDiscovery::getSearchCount() const {
	return count++ ;
}

unsigned Mplane::TestIDiscovery::getNotifyCount() const {
	return count++ ;
}
//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
