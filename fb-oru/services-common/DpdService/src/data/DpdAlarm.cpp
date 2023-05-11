/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdAlarm.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "data/DpdAlarm.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::DpdAlarm::getTriggerVariable()
{
	return "fail" ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdAlarm::DpdAlarm() :
	mFailCount(0),
	mAlarmType(DpdAlarmType::OK),
	mTxPort(0)
{
}

//-------------------------------------------------------------------------------------------------------------
DpdAlarm::DpdAlarm(const IDpdAlarm& rhs) :
	mFailCount(rhs.getFailCount()),
	mAlarmType(rhs.getAlarmType()),
	mTxPort(rhs.getTxPort())
{
}

//-------------------------------------------------------------------------------------------------------------
DpdAlarm::~DpdAlarm() {
}

//-------------------------------------------------------------------------------------------------------------
bool DpdAlarm::predicate(const std::map<std::string, DataVariant>& attributes)
{
	// Require the following variable to be present:
	//   fail
	//   err
	//   tx
	//
	if (!checkVariables(std::vector<std::string>{
		"fail",
		"err",
		"tx"
	}, attributes))
		return false ;

//	int failCount(attributes.at("fail").toInt()) ;
//	return failCount > 0 ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdAlarm::setData(const std::map<std::string, DataVariant>& attributes)
{
	mFailCount = static_cast<unsigned>(attributes.at("fail").toInt()) ;
	mAlarmType = static_cast<DpdAlarmType>(attributes.at("err").toInt()) ;
	mTxPort    = static_cast<unsigned>(attributes.at("tx").toInt()) ;

	return true ;
}
