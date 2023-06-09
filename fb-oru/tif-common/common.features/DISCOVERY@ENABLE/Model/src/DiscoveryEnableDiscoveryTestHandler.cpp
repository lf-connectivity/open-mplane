/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DiscoveryEnableDiscoveryTestHandler.cpp
 * \brief     Test methods for DISCOVERY@ENABLE
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
#include "DiscoveryEnableDiscoveryTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void DiscoveryEnableDiscoveryTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/discovery", "Network discovery statistics", msgParser, settings) ) ;




	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/discovery/cacheAge", "INT",
			"Maximum time between notifications",
			cacheAgeGet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/discovery/ip", "STRING",
			"IP Address",
			ipGet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/discovery/notifyCount", "INT",
			"Number of notifications sent since connection",
			notifyCountGet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/discovery/searchCount", "INT",
			"Number of search requests since connection",
			searchCountGet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/discovery/uuid", "STRING",
			"SSDP uuid",
			uuidGet,
			msgParser, settings))
	);



}




//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
DiscoveryEnableDiscoveryTestHandler::DiscoveryEnableDiscoveryTestHandler() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS),
	mHelper(DiscoveryTestHelper::getInstance())
{
	// NOTE: This is a dummy object creator only provided so build features can get access
	// to the registerEntry() method
}

//-------------------------------------------------------------------------------------------------------------
DiscoveryEnableDiscoveryTestHandler::DiscoveryEnableDiscoveryTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(DiscoveryTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
DiscoveryEnableDiscoveryTestHandler::~DiscoveryEnableDiscoveryTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool DiscoveryEnableDiscoveryTestHandler::registerEntry(ITif* tif)
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
std::string DiscoveryEnableDiscoveryTestHandler::operator()(const std::string& functionName)
{


    return "";
}




//-------------------------------------------------------------------------------------------------------------
void DiscoveryEnableDiscoveryTestHandler::cacheAgeGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/discovery/cacheAge"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<DiscoveryTestHelper> helper(DiscoveryTestHelper::getInstance()) ;
	helper->cacheAgeGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
void DiscoveryEnableDiscoveryTestHandler::ipGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/discovery/ip"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<DiscoveryTestHelper> helper(DiscoveryTestHelper::getInstance()) ;
	helper->ipGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
void DiscoveryEnableDiscoveryTestHandler::notifyCountGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/discovery/notifyCount"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<DiscoveryTestHelper> helper(DiscoveryTestHelper::getInstance()) ;
	helper->notifyCountGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
void DiscoveryEnableDiscoveryTestHandler::searchCountGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/discovery/searchCount"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<DiscoveryTestHelper> helper(DiscoveryTestHelper::getInstance()) ;
	helper->searchCountGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
void DiscoveryEnableDiscoveryTestHandler::uuidGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/discovery/uuid"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<DiscoveryTestHelper> helper(DiscoveryTestHelper::getInstance()) ;
	helper->uuidGet( pathname, returnList ) ;
}








// Add any statics, private methods etc here %%-->

// <--%%
