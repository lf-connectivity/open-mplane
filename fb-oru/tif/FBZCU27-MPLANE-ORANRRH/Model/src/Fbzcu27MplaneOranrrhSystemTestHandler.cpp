/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fbzcu27MplaneOranrrhSystemTestHandler.cpp
 * \brief     Test methods for FBZCU27-MPLANE-ORANRRH
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
#include "Fbzcu27MplaneOranrrhSystemTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Fbzcu27MplaneOranrrhSystemTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/system", "System information", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new Fbzcu27MplaneOranrrhSystemTestHandler("/system/setClockIn",
			"ENUM(INTERNAL:External_10MHz:FIBRE:10G_SYNCE:25G_SYNCE) clkin",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Select the clock source to the system clock",
			msgParser, settings))
	);




	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/system/ClockIn", "STRING",
			"Current clock source to the system clock",
			ClockInGet,
			msgParser, settings))
	);



}




//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
Fbzcu27MplaneOranrrhSystemTestHandler::Fbzcu27MplaneOranrrhSystemTestHandler() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS),
	mHelper(SystemTestHelper::getInstance())
{
	// NOTE: This is a dummy object creator only provided so build features can get access
	// to the registerEntry() method
}

//-------------------------------------------------------------------------------------------------------------
Fbzcu27MplaneOranrrhSystemTestHandler::Fbzcu27MplaneOranrrhSystemTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(SystemTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
Fbzcu27MplaneOranrrhSystemTestHandler::~Fbzcu27MplaneOranrrhSystemTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool Fbzcu27MplaneOranrrhSystemTestHandler::registerEntry(ITif* tif)
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
std::string Fbzcu27MplaneOranrrhSystemTestHandler::operator()(const std::string& functionName)
{

    if( functionName == "setClockIn")
    {
        setClockIn( callVarList, returnVarList  );
        return "" ;
    }



    return "";
}


//-------------------------------------------------------------------------------------------------------------
void Fbzcu27MplaneOranrrhSystemTestHandler::setClockIn(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * ENUM(INTERNAL:External_10MHz:FIBRE:10G_SYNCE:25G_SYNCE) clkin
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->setClockIn( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}




//-------------------------------------------------------------------------------------------------------------
void Fbzcu27MplaneOranrrhSystemTestHandler::ClockInGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/system/ClockIn"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemTestHelper> helper(SystemTestHelper::getInstance()) ;
	helper->ClockInGet( pathname, returnList ) ;
}








// Add any statics, private methods etc here %%-->

// <--%%
