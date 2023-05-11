/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdInfo.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "data/DpdInfo.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::DpdInfo::getTriggerVariable()
{
	return "Q" ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdInfo::DpdInfo() :
	mFailCount(0),
	mSuccessCount(0),
	mIteration(0),
	mB(0),
	mN(0),
	mQ(0),
	mG(0.0),
	mGexp(0.0),
	mEff(0.0),
	mEvm(0.0),
	mTxPort(0)
{
}

//-------------------------------------------------------------------------------------------------------------
DpdInfo::DpdInfo(const IDpdInfo& rhs) :
	mFailCount(rhs.getFailCount()),
	mSuccessCount(rhs.getSuccessCount()),
	mIteration(rhs.getIteration()),
	mB(rhs.getB()),
	mN(rhs.getN()),
	mQ(rhs.getQ()),
	mG(rhs.getG()),
	mGexp(rhs.getGexp()),
	mEff(rhs.getEff()),
	mEvm(rhs.getEvm()),
	mTxPort(rhs.getTxPort())
{
}

//-------------------------------------------------------------------------------------------------------------
DpdInfo::~DpdInfo() {
}

//-------------------------------------------------------------------------------------------------------------
void DpdInfo::clear()
{
	mFailCount = 0 ;
	mSuccessCount = 0 ;
	mIteration = 0 ;
	mB = 0 ;
	mN = 0 ;
	mQ = 0 ;

	mG = 0.0 ;
	mGexp = 0.0 ;
	mEff = 0.0 ;
	mEvm = 0.0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdInfo::predicate(const std::map<std::string, DataVariant>& attributes)
{
	if (!checkVariables(std::vector<std::string>{
		"B",
		"G",
		"Gexp",
		"N",
		"Q",
		"eff",
		"err",
		"evm",
		"fail",
		"i",
		"success",
		"tx",
	}, attributes))
		return false ;

	std::string err(attributes.at("err").toString()) ;
	return err == "OK" ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdInfo::setData(const std::map<std::string, DataVariant>& attributes)
{
	mFailCount = static_cast<unsigned>(attributes.at("fail").toInt()) ;
	mSuccessCount = static_cast<unsigned>(attributes.at("success").toInt()) ;
	mIteration = static_cast<unsigned>(attributes.at("i").toInt()) ;
	mB = static_cast<unsigned>(attributes.at("B").toInt()) ;
	mN = static_cast<unsigned>(attributes.at("N").toInt()) ;
	mQ = static_cast<unsigned>(attributes.at("Q").toInt()) ;

	mG = attributes.at("G").toFloat() ;
	mGexp = attributes.at("Gexp").toFloat() ;
	mEff = attributes.at("eff").toFloat() ;
	mEvm = attributes.at("evm").toFloat() ;

	mTxPort    = static_cast<unsigned>(attributes.at("tx").toInt()) ;

	return true ;
}
