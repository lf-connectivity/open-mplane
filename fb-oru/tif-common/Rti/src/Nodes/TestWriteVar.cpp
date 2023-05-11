/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestWriteVar.cpp
 * \brief     "Directory" entry implementing a write-only variable with set method calls for RTI
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
#include "Nodes/TestWriteVar.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANT
//=============================================================================================================

//=============================================================================================================
// PROTOTYPES
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestWriteVar::TestWriteVar(const std::string& pathname, const std::string& varType, const std::string& comment,
		Setter setMethod,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryVar(pathname, varType, comment, msgParser, settings),
	mPathname(pathname),
	mSetMethod(setMethod)
{
}

//-------------------------------------------------------------------------------------------------------------
TestWriteVar::~TestWriteVar()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TestWriteVar::operator()(const std::string& name)
{
	// If "value" is set then this is a "set" access; otherwise it's a "get" access
	if (callVarList->find( valueStr() )->isSet())
	{
		setValue() ;
	}

	// Let base class do the rest
    return this->super::operator()(name) ;
}

//-------------------------------------------------------------------------------------------------------------
void TestWriteVar::setValue()
{
	std::string retListStr(getTypeStr() + " " + mPathname) ;
	DataVariantList *retList(new DataVariantList( RtiKeyword::addKeywordArgs(retListStr).c_str() ) );

	DataVariant dv(mPathname, getTypeStr()) ;
	dv.set(callVarList->find( valueStr() )->toString()) ;

	// update value in parent
	bool ok = mSetMethod(mPathname, &dv, retList) ;

	std::string msg( retList->find(RtiKeyword::MESSAGE_VAR)->toString() ) ;
	delete retList ;

	if (!ok)
	{
		returnVarList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		if (msg.empty())
			returnVarList->find(RtiKeyword::MESSAGE_VAR)->set("Error setting variable") ;
		else
			returnVarList->find(RtiKeyword::MESSAGE_VAR)->set(msg) ;
		return ;
	}
}
