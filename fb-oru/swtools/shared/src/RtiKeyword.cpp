/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiKeyword.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "stringfunc.hpp"
#include "RtiKeyword.h"
#include "DataVariant.h"

using namespace Mplane ;

//=============================================================================================================
// TYPES
//=============================================================================================================
struct KeywordInfo {
	std::string name ;
	std::string type ;
	std::string defaultVal ;
	bool optional ;
};

//=============================================================================================================
// STATIC
//=============================================================================================================
const std::string RtiKeyword::StatusOK("OK") ;
const std::string RtiKeyword::StatusERROR("ERROR") ;

static const unsigned STATUS_IDX = 0 ;
static const unsigned INFO_IDX = 1 ;
static const unsigned MESSAGE_IDX = 2 ;
static const KeywordInfo info[] = {
	{"Status", 	"ENUM(OK:ERROR)", 	RtiKeyword::StatusOK,	false },
	{"Info", 	"STRING", 			"", 					true },
	{"Message", "STRING", 			"", 					true }
};
static const unsigned INFO_SIZE = sizeof(info) / sizeof(KeywordInfo) ;

const std::string RtiKeyword::STATUS_VAR(info[STATUS_IDX].name) ;
const std::string RtiKeyword::INFO_VAR(info[INFO_IDX].name) ;
const std::string RtiKeyword::MESSAGE_VAR(info[MESSAGE_IDX].name) ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string RtiKeyword::getType(const std::string& var)
{
	std::string lower( toLower(var) ) ;
	for (unsigned idx=0; idx < INFO_SIZE; ++idx)
	{
		if (toLower(info[idx].name) == lower)
			return info[idx].type ;
	}

	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiKeyword::isOptional(const std::string& var)
{
	std::string lower( toLower(var) ) ;
	for (unsigned idx=0; idx < INFO_SIZE; ++idx)
	{
		if (toLower(info[idx].name) == lower)
			return info[idx].optional ;
	}

	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::RtiKeyword::getDefault(const std::string& var)
{
	std::string lower( toLower(var) ) ;
	for (unsigned idx=0; idx < INFO_SIZE; ++idx)
	{
		if (toLower(info[idx].name) == lower)
			return info[idx].defaultVal ;
	}

	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiKeyword::isReserved(const std::string& var)
{
	std::string lower( toLower(var) ) ;
	for (unsigned idx=0; idx < INFO_SIZE; ++idx)
	{
		if (toLower(info[idx].name) == lower)
			return true ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> Mplane::RtiKeyword::getReservedList()
{
	std::vector<std::string> names ;
	for (unsigned idx=0; idx < INFO_SIZE; ++idx)
	{
		names.push_back(info[idx].name) ;
	}
	return names ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiKeyword::addKeywordArgs(const std::string& args)
{
	// Need to add special return variables to all returns:
	//	"ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info]"

	DataVariantList dvList ;
	std::vector<std::string> reserved(RtiKeyword::getReservedList()) ;
	for (std::vector<std::string>::const_iterator iter(reserved.begin()); iter != reserved.end(); ++iter)
	{
		DataVariant* dv = new DataVariant(*iter, RtiKeyword::getType(*iter)) ;
		dv->setOptional(RtiKeyword::isOptional(*iter)) ;
		if (!RtiKeyword::getDefault(*iter).empty())
			dv->set(RtiKeyword::getDefault(*iter)) ;
		dvList.add(dv) ;
	}
	std::string fullReturnFields = dvList.varlist(",", true) ;

	if (!args.empty())
	{
		if (!fullReturnFields.empty())
			fullReturnFields += "," ;
		fullReturnFields += args ;
	}

	return fullReturnFields ;
}
