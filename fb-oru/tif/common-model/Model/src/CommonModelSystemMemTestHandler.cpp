/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonModelSystemMemTestHandler.cpp
 * \brief     Test methods for common-model
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run)
 *
 * Add any file header comments here %%-->
 *
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
#include "CommonModelSystemMemTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/system/mem", "System memory monitoring", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new CommonModelSystemMemTestHandler("/system/mem/get",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],UINT rate (sec),BOOL(OFF:ON) logging,ENUM(PERIODIC:ONCHANGE) logRate,UINT threshold (kB)",
			"Get the memory monitor settings",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new CommonModelSystemMemTestHandler("/system/mem/set",
			"[UINT rate (sec)],[BOOL(OFF:ON) logging],[ENUM(PERIODIC:ONCHANGE) logRate],[UINT threshold (kB)]",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set the memory monitor settings",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new CommonModelSystemMemTestHandler("/system/mem/show",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show memory information",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new CommonModelSystemMemTestHandler("/system/mem/tcpClose",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Stop logging to tcp port",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new CommonModelSystemMemTestHandler("/system/mem/tcpOpen",
			"[UINT{1024..65535} tcp]",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Log to TCP port when logging is enabled",
			msgParser, settings))
	);



	msgParser.add( static_cast<RtiDirEntry *>(new TestVar("/system/mem/LogRate", "ENUM(PERIODIC:ONCHANGE)",
			"Logging rate",
			LogRateGet, LogRateSet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestVar("/system/mem/Logging", "BOOL(OFF:ON)",
			"Log memory usage changes",
			LoggingGet, LoggingSet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestVar("/system/mem/Threshold", "UINT",
			"Memory threshold",
			ThresholdGet, ThresholdSet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestVar("/system/mem/UpdateRate", "UINT",
			"Update rate",
			UpdateRateGet, UpdateRateSet,
			msgParser, settings))
	);



	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/system/mem/Usage", "UINT",
			"Current memory usage",
			UsageGet,
			msgParser, settings))
	);



}




//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
CommonModelSystemMemTestHandler::CommonModelSystemMemTestHandler() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS),
	mHelper(SystemMemTestHelper::getInstance())
{
	// NOTE: This is a dummy object creator only provided so build features can get access
	// to the registerEntry() method
}

//-------------------------------------------------------------------------------------------------------------
CommonModelSystemMemTestHandler::CommonModelSystemMemTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(SystemMemTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
CommonModelSystemMemTestHandler::~CommonModelSystemMemTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool CommonModelSystemMemTestHandler::registerEntry(ITif* tif)
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
std::string CommonModelSystemMemTestHandler::operator()(const std::string& functionName)
{

    if( functionName == "get")
    {
        get( callVarList, returnVarList  );
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


    if( functionName == "tcpClose")
    {
        tcpClose( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "tcpOpen")
    {
        tcpOpen( callVarList, returnVarList  );
        return "" ;
    }



    return "";
}


//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::get(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * UINT rate (sec)
	// * BOOL(OFF:ON) logging
	// * ENUM(PERIODIC:ONCHANGE) logRate
	// * UINT threshold (kB)
	//
	mHelper->get( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::set(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * [UINT rate (sec)]
	// * [BOOL(OFF:ON) logging]
	// * [ENUM(PERIODIC:ONCHANGE) logRate]
	// * [UINT threshold (kB)]
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
void CommonModelSystemMemTestHandler::show(  DataVariantList *callList, DataVariantList *returnList )
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


//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::tcpClose(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->tcpClose( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::tcpOpen(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * [UINT{1024..65535} tcp]
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->tcpOpen( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}



//-------------------------------------------------------------------------------------------------------------
bool CommonModelSystemMemTestHandler::LogRateSet(  const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/system/mem/LogRate"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	return helper->LogRateSet( pathname, value, returnList ) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::LogRateGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/system/mem/LogRate"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	helper->LogRateGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonModelSystemMemTestHandler::LoggingSet(  const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/system/mem/Logging"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	return helper->LoggingSet( pathname, value, returnList ) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::LoggingGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/system/mem/Logging"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	helper->LoggingGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonModelSystemMemTestHandler::ThresholdSet(  const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/system/mem/Threshold"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	return helper->ThresholdSet( pathname, value, returnList ) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::ThresholdGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/system/mem/Threshold"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	helper->ThresholdGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
bool CommonModelSystemMemTestHandler::UpdateRateSet(  const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/system/mem/UpdateRate"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	return helper->UpdateRateSet( pathname, value, returnList ) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::UpdateRateGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/system/mem/UpdateRate"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	helper->UpdateRateGet( pathname, returnList ) ;
}



//-------------------------------------------------------------------------------------------------------------
void CommonModelSystemMemTestHandler::UsageGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/system/mem/Usage"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<SystemMemTestHelper> helper(SystemMemTestHelper::getInstance()) ;
	helper->UsageGet( pathname, returnList ) ;
}








// Add any statics, private methods etc here %%-->

// <--%%
