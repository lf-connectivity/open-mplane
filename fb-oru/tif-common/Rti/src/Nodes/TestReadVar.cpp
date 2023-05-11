/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestReadVar.cpp
 * \brief     "Directory" entry implementing a variable with get method calls for RTI
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include "RtiKeyword.h"
#include "Nodes/TestReadVar.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANT
//=============================================================================================================

//=============================================================================================================
// PROTOTYPES
//=============================================================================================================
static bool setMethod(const std::string& pathname, DataVariant *value, DataVariantList *returnList);

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestReadVar::TestReadVar(const std::string& pathname, const std::string& varType, const std::string& comment,
		Getter getMethod,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	TestVar(pathname, varType, comment, getMethod, setMethod, msgParser, settings)
{
}

//-------------------------------------------------------------------------------------------------------------
TestReadVar::~TestReadVar()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TestReadVar::operator()(const std::string& name)
{
	// If "value" is set then this is a "set" access; otherwise it's a "get" access
	if (callVarList->find( valueStr() )->isSet())
	{
		returnVarList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

		std::stringstream ss ;
		ss << "Cannot set read-only variable " << name ;
		returnVarList->find(RtiKeyword::MESSAGE_VAR)->set( ss.str() );
		return "" ;
	}

	// Let base class do the rest
    return this->super::operator()(name) ;
}


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static bool setMethod(const std::string& pathname, DataVariant *value, DataVariantList *returnList)
{
	returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

	std::stringstream ss ;
	ss << "Cannot set read-only variable " << pathname ;
	returnList->find(RtiKeyword::MESSAGE_VAR)->set( ss.str() );
	return false ;
}
