/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhEqualiserTestHandler.cpp
 * \brief     Test methods for ZCU111-FBC-ORANRRH
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
#include "Zcu111FbcOranrrhEqualiserTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhEqualiserTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/equaliser", "Equaliser settings", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111FbcOranrrhEqualiserTestHandler("/equaliser/getPassthrough",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],BOOL(OFF:ON) passthrough",
			"Get the passthrough mode state",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111FbcOranrrhEqualiserTestHandler("/equaliser/setPassthrough",
			"BOOL(OFF:ON) passthrough",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Turn ON/OFF the passthrough mode",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111FbcOranrrhEqualiserTestHandler("/equaliser/showAll",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show debug details of all Tx and Rx equaliser",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111FbcOranrrhEqualiserTestHandler("/equaliser/showRx",
			"INT Index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show debug details of a Rx equaliser",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111FbcOranrrhEqualiserTestHandler("/equaliser/showTx",
			"INT Index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show debug details of a Tx equaliser",
			msgParser, settings))
	);





}




//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhEqualiserTestHandler::Zcu111FbcOranrrhEqualiserTestHandler() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS),
	mHelper(EqualiserTestHelper::getInstance())
{
	// NOTE: This is a dummy object creator only provided so build features can get access
	// to the registerEntry() method
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhEqualiserTestHandler::Zcu111FbcOranrrhEqualiserTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(EqualiserTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhEqualiserTestHandler::~Zcu111FbcOranrrhEqualiserTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhEqualiserTestHandler::registerEntry(ITif* tif)
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
std::string Zcu111FbcOranrrhEqualiserTestHandler::operator()(const std::string& functionName)
{

    if( functionName == "getPassthrough")
    {
        getPassthrough( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "setPassthrough")
    {
        setPassthrough( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "showAll")
    {
        showAll( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "showRx")
    {
        showRx( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "showTx")
    {
        showTx( callVarList, returnVarList  );
        return "" ;
    }



    return "";
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhEqualiserTestHandler::getPassthrough(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * BOOL(OFF:ON) passthrough
	//
	mHelper->getPassthrough( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhEqualiserTestHandler::setPassthrough(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * BOOL(OFF:ON) passthrough
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->setPassthrough( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhEqualiserTestHandler::showAll(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->showAll( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhEqualiserTestHandler::showRx(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT Index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->showRx( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhEqualiserTestHandler::showTx(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT Index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->showTx( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}










// Add any statics, private methods etc here %%-->

// <--%%
