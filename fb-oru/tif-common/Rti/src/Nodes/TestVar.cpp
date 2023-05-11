/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestVar.cpp
 * \brief     "Directory" entry implementing a variable with set/get method calls for RTI
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
#include "Nodes/TestVar.h"

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
TestVar::TestVar(const std::string& pathname, const std::string& varType, const std::string& comment,
		Getter getMethod, Setter setMethod,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryVar(pathname, varType, comment, msgParser, settings),
	mPathname(pathname),
	mGetMethod(getMethod),
	mSetMethod(setMethod)
{
}

//-------------------------------------------------------------------------------------------------------------
TestVar::~TestVar()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string TestVar::ls()
{
	// update value
	getValue() ;

	// do ls
	return this->super::ls() ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string TestVar::operator()(const std::string& name)
{
	// If "value" is set then this is a "set" access; otherwise it's a "get" access
	if (callVarList->find( valueStr() )->isSet())
	{
		setValue() ;
	}

	// update value
	getValue() ;

	// Let base class do the rest
    return this->super::operator()(name) ;
}

//-------------------------------------------------------------------------------------------------------------
void TestVar::getValue()
{
	std::string retListStr(getTypeStr() + " " + mPathname) ;
	DataVariantList *retList(new DataVariantList( RtiKeyword::addKeywordArgs(retListStr).c_str() ) );

	// update value from parent
	mGetMethod(mPathname, retList) ;

	// copy value over
	setData(retList->find( mPathname )->toString()) ;

	delete retList ;
}

//-------------------------------------------------------------------------------------------------------------
void TestVar::setValue()
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

	// Now mirror the current parent value back to the "shadow" value
	getValue() ;
}
