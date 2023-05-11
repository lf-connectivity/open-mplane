/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestInjected.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Nodes/RtiDirEntry.h"
#include "Nodes/TestVar.h"
#include "Nodes/TestReadVar.h"
#include "Nodes/TestWriteVar.h"
#include "Nodes/DirClass.h"
#include "RtiKeyword.h"

#include "TestInjected.h"

using namespace Mplane ;

//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TestInjected::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/dpd", "DPD functions", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new TestInjected("/dpd/abort",
			"[INT tx]",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"requests an immediate termination of any iteration that is in progress",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestInjected("/dpd/apiVersion",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"get the current api version",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestInjected("/dpd/capture",
			"[INT tx],[ENUM(X:Z:RAW) src],[ENUM(OFF:ON) decimation],[INT level],[INT i]",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"capture a set of data and write to the MatLab output channel (use src=X|Z level=trigger i=#samples) ",
			msgParser, settings))
	);


}




//=============================================================================================================
// PUBLIC
//=============================================================================================================

TestInjected::TestInjected() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS)
{
}

//-------------------------------------------------------------------------------------------------------------
TestInjected::TestInjected(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings)
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
TestInjected::~TestInjected()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool TestInjected::registerEntry(ITif* tif)
{
	// Convert ITif object into it's expected subclasses
	IRtiMsgParser* msgParser(dynamic_cast<IRtiMsgParser*>(tif)) ;
	IRtiSettings* settings(dynamic_cast<IRtiSettings*>(tif)) ;
	if (!msgParser)
		return false ;
	if (!settings)
		return false ;

	// now call this object's registerMethods() method to do the actual work
	registerMethods(*msgParser, *settings) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string TestInjected::operator()(const std::string& functionName)
{

    if( functionName == "abort")
    {
        abort( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "apiVersion")
    {
        apiVersion( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "capture")
    {
        capture( callVarList, returnVarList  );
        return "" ;
    }


    return "";
}


//-------------------------------------------------------------------------------------------------------------
void TestInjected::abort(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * [INT tx]
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	returnList->find(RtiKeyword::INFO_VAR)->set("abort command") ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void TestInjected::apiVersion(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	returnList->find(RtiKeyword::INFO_VAR)->set("apiVersion command") ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void TestInjected::capture(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * [INT tx]
	// * [ENUM(X:Z:RAW) src]
	// * [ENUM(OFF:ON) decimation]
	// * [INT level]
	// * [INT i]
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	returnList->find(RtiKeyword::INFO_VAR)->set("capture command") ;

	// Insert your code here : %%-->

	// <--%%
}
