/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HelperImagesTestHandler.cpp
 * \brief     Test methods for Helper
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run)
 *
 * Add any file header comments here %%-->
 *
 * <--%%
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
#include "HelperImagesTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void HelperImagesTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/image", "Image Management settings", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new HelperImagesTestHandler("/image/clean",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Clean flash of old images in order to free-up space",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new HelperImagesTestHandler("/image/install",
			"STRING version,STRING build",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Get and install package",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new HelperImagesTestHandler("/image/installFile",
			"STRING filename",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Get and install package from a file",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new HelperImagesTestHandler("/image/show",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show image management information",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new HelperImagesTestHandler("/image/showDetail",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show detailed image management information",
			msgParser, settings))
	);



	msgParser.add( static_cast<RtiDirEntry *>(new TestVar("/image/uboot", "BOOL(no:yes)",
			"Install new u-boot when OS installed?",
			ubootGet, ubootSet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestVar("/image/url", "STRING",
			"Server URL to download from",
			urlGet, urlSet,
			msgParser, settings))
	);



	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/image/bank", "ENUM(BANK1:BANK2)",
			"Currently active OS memory bank",
			bankGet,
			msgParser, settings))
	);



}




//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HelperImagesTestHandler::HelperImagesTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(ImagesTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
HelperImagesTestHandler::~HelperImagesTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
std::string HelperImagesTestHandler::operator()(const std::string& functionName)
{

    if( functionName == "clean")
    {
        clean( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "install")
    {
        install( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "installFile")
    {
        installFile( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "show")
    {
        show( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "showDetail")
    {
        showDetail( callVarList, returnVarList  );
        return "" ;
    }



    return "";
}


//-------------------------------------------------------------------------------------------------------------
void HelperImagesTestHandler::clean(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->clean( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void HelperImagesTestHandler::install(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * STRING version
	// * STRING build
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->install( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void HelperImagesTestHandler::installFile(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * STRING filename
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->installFile( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void HelperImagesTestHandler::show(  DataVariantList *callList, DataVariantList *returnList )
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
void HelperImagesTestHandler::showDetail(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->showDetail( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}



//-------------------------------------------------------------------------------------------------------------
bool HelperImagesTestHandler::ubootSet(  const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/image/uboot"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<ImagesTestHelper> helper(ImagesTestHelper::getInstance()) ;
	return helper->ubootSet( pathname, value, returnList ) ;
}

//-------------------------------------------------------------------------------------------------------------
void HelperImagesTestHandler::ubootGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/image/uboot"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<ImagesTestHelper> helper(ImagesTestHelper::getInstance()) ;
	helper->ubootGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
bool HelperImagesTestHandler::urlSet(  const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/image/url"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<ImagesTestHelper> helper(ImagesTestHelper::getInstance()) ;
	return helper->urlSet( pathname, value, returnList ) ;
}

//-------------------------------------------------------------------------------------------------------------
void HelperImagesTestHandler::urlGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/image/url"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<ImagesTestHelper> helper(ImagesTestHelper::getInstance()) ;
	helper->urlGet( pathname, returnList ) ;
}



//-------------------------------------------------------------------------------------------------------------
void HelperImagesTestHandler::bankGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/image/bank"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<ImagesTestHelper> helper(ImagesTestHelper::getInstance()) ;
	helper->bankGet( pathname, returnList ) ;
}








// Add any statics, private methods etc here %%-->

// <--%%
