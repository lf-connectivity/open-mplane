/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fbzcu27MplaneOranrrhSystemConfigTestHandler.cpp
 * \brief     Test methods for Fbzcu27-MPLANE-ORANRRH
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
#include "Fbzcu27MplaneOranrrhSystemConfigTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Fbzcu27MplaneOranrrhSystemConfigTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/system/.config", "System configuration", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new Fbzcu27MplaneOranrrhSystemConfigTestHandler("/system/.config/save",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Save the current configuration to non-volatile storage",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Fbzcu27MplaneOranrrhSystemConfigTestHandler("/system/.config/set",
			"STRING setting,STRING value",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set the value of a configuration setting",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Fbzcu27MplaneOranrrhSystemConfigTestHandler("/system/.config/show",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show current configuration",
			msgParser, settings))
	);





}




//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
Fbzcu27MplaneOranrrhSystemConfigTestHandler::Fbzcu27MplaneOranrrhSystemConfigTestHandler() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS),
	mHelper(SystemConfigTestHelper::getInstance())
{
	// NOTE: This is a dummy object creator only provided so build features can get access
	// to the registerEntry() method
}

//-------------------------------------------------------------------------------------------------------------
Fbzcu27MplaneOranrrhSystemConfigTestHandler::Fbzcu27MplaneOranrrhSystemConfigTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(SystemConfigTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
Fbzcu27MplaneOranrrhSystemConfigTestHandler::~Fbzcu27MplaneOranrrhSystemConfigTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool Fbzcu27MplaneOranrrhSystemConfigTestHandler::registerEntry(ITif* tif)
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
std::string Fbzcu27MplaneOranrrhSystemConfigTestHandler::operator()(const std::string& functionName)
{

    if( functionName == "save")
    {
        save( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "set")
    {
        set( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "show")
    {
        show( callVarList, returnVarList  );
        return "" ;
    }



    return "";
}


//-------------------------------------------------------------------------------------------------------------
void Fbzcu27MplaneOranrrhSystemConfigTestHandler::save(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->save( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Fbzcu27MplaneOranrrhSystemConfigTestHandler::set(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * STRING setting
	// * STRING value
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->set( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Fbzcu27MplaneOranrrhSystemConfigTestHandler::show(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->show( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}










// Add any statics, private methods etc here %%-->

// <--%%
