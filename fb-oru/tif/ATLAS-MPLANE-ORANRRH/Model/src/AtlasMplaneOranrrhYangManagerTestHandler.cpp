/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AtlasMplaneOranrrhYangManagerTestHandler.cpp
 * \brief     Test methods for Atlas-MPLANE-ORANRRH
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run)
 *
 * Add any file header comments here %%-->

 * <--%%
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
#include "AtlasMplaneOranrrhYangManagerTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void AtlasMplaneOranrrhYangManagerTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/oran/yang-mgr", "YANG manager test methods", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new AtlasMplaneOranrrhYangManagerTestHandler("/oran/yang-mgr/getInstalledModuleList",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],STRING Modules",
			"Get the list of modules installed",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new AtlasMplaneOranrrhYangManagerTestHandler("/oran/yang-mgr/getModuleFeatures",
			"STRING module",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],STRING Features",
			"Get the list of module features",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new AtlasMplaneOranrrhYangManagerTestHandler("/oran/yang-mgr/getStatus",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],ENUM(Initialised:Uninitialised:Failed) mgrStatus",
			"Get the status of the YANG manager",
			msgParser, settings))
	);





}




//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
AtlasMplaneOranrrhYangManagerTestHandler::AtlasMplaneOranrrhYangManagerTestHandler() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS),
	mHelper(YangManagerTestHelper::getInstance())
{
	// NOTE: This is a dummy object creator only provided so build features can get access
	// to the registerEntry() method
}

//-------------------------------------------------------------------------------------------------------------
AtlasMplaneOranrrhYangManagerTestHandler::AtlasMplaneOranrrhYangManagerTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(YangManagerTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
AtlasMplaneOranrrhYangManagerTestHandler::~AtlasMplaneOranrrhYangManagerTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool AtlasMplaneOranrrhYangManagerTestHandler::registerEntry(ITif* tif)
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
std::string AtlasMplaneOranrrhYangManagerTestHandler::operator()(const std::string& functionName)
{

    if( functionName == "getInstalledModuleList")
    {
        getInstalledModuleList( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getModuleFeatures")
    {
        getModuleFeatures( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getStatus")
    {
        getStatus( callVarList, returnVarList  );
        return "" ;
    }



    return "";
}


//-------------------------------------------------------------------------------------------------------------
void AtlasMplaneOranrrhYangManagerTestHandler::getInstalledModuleList(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * STRING Modules
	//
	mHelper->getInstalledModuleList( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void AtlasMplaneOranrrhYangManagerTestHandler::getModuleFeatures(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * STRING module
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * STRING Features
	//
	mHelper->getModuleFeatures( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void AtlasMplaneOranrrhYangManagerTestHandler::getStatus(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * ENUM(Initialised:Uninitialised:Failed) mgrStatus
	//
	mHelper->getStatus( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}










// Add any statics, private methods etc here %%-->

// <--%%
