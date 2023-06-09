/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImagesTestHelper.cpp
 * \brief     Test helper for common
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run)
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "RtiKeyword.h"
#include "ImagesTestHelper.h"

// Add any specific includes here %%-->
#include <sstream>
#include "IImageManagement.h"
#include "Path.h"

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->


// <--%%



//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ImagesTestHelper> ImagesTestHelper::getInstance()
{
	static std::shared_ptr<ImagesTestHelper> instance(std::make_shared<ImagesTestHelper>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ImagesTestHelper::ImagesTestHelper()
// Insert additional inheritance constructors here : %%-->
: 	mMutex(),
 	mFileStatus(IFileStatus::simpleTracker()),
 	mLatestStatus(mFileStatus),
	mZipPort(),
	mZipFileWriter(),
	mInstallingZip(false),
	mInstalledZip(false)

// <--%%
{
	// Insert your code here : %%-->


	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
ImagesTestHelper::~ImagesTestHelper()
{
	// Insert your code here : %%-->


	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::clean( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	std::string failReason ;
	if ( !imageMgr->cleanImages(failReason) )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return ;
	}

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::install( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * STRING version
	// * STRING build
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::string version(callList->find("version")->toString()) ;
	std::string build(callList->find("build")->toString()) ;

	// Download
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	std::string failReason ;
	bool ok = imageMgr->getAndInstall(IImageTypes::IMAGE_PACKAGE, version, build,
			IFileStatus::simpleOutput([&msgParser](const std::string& status){ msgParser.sendOutput(status); }), // \satisfy{@req_8403{200}}
			failReason) ; // \satisfy{@req_8403{198}}


	if (!ok)    // \satisfy{@req_8403{201}}
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return ;
	}


	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::installFile( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * STRING filename
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::string filename(callList->find("filename")->toString()) ;

	IImageTypes::Type type(IImageTypes::IMAGE_PACKAGE) ;
	if ( Path::extension(filename) == ".zip")
		type = IImageTypes::IMAGE_ZIP ;

	// Download
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	std::string failReason ;
	bool ok = imageMgr->getAndInstall(type, filename,
			IFileStatus::simpleOutput([&msgParser](const std::string& status){ msgParser.sendOutput(status); }), // \satisfy{@req_8403{199}}
			failReason) ;   // \satisfy{@req_8403{198}}

	if (!ok)    // \satisfy{@req_8403{201}}
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return ;
	}


	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::installStatus( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * BOOL done
	// * BOOL fail
	// * INT totalProgress (%)
	// * STRING file
	// * STRING op
	// * INT fileProgress (%)
	// * STRING error
	//

	// Insert your code here : %%-->
	if (!mInstallingZip && !mInstalledZip)
	{
		returnList->find("done")->set(false) ;
		returnList->find("totalProgress")->set(0) ;
		returnList->find("fileProgress")->set(0) ;
		returnList->find("fail")->set(true) ;

		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("No zip file has been installed") ;
		return ;
	}

	returnList->find("done")->set(mLatestStatus->isComplete()) ;
	returnList->find("totalProgress")->set( static_cast<int>(mLatestStatus->getTotalProgress()) ) ;
	returnList->find("file")->set(mLatestStatus->getFilename()) ;
	returnList->find("op")->set(mLatestStatus->getOperation()) ;
	returnList->find("fileProgress")->set( static_cast<int>(mLatestStatus->getProgress()) ) ;

	std::string error(mLatestStatus->getError()) ;
	bool fail(!error.empty()) ;
	returnList->find("error")->set(error) ;
	returnList->find("fail")->set(fail) ;
	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::installTcp( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT tcp
	// * INT size
	// * [INT timeout=60]
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	if (!TcpPortHelper::portValid(msgParser, "tcp", callList, returnList))
		return ;

	Mutex::Lock lock(mMutex) ;

	mZipPort = std::make_shared<TcpPortHelper>(msgParser, "tcp", callList) ;

	unsigned expectedSize( static_cast<unsigned>(callList->find("size")->toInt()) ) ;
	unsigned timeoutSecs( static_cast<unsigned>(callList->find("timeout")->toInt()) ) ;

	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	std::string failReason ;
	mZipFileWriter = imageMgr->getZipFileWriter(mFileStatus, expectedSize, failReason) ;
	if (!mZipFileWriter)
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return ;
	}

	// Initiate the transfer (in a background thread)
	mInstallingZip = true ;
	mLatestStatus = mFileStatus ;
	bool ok = imageMgr->zipInstall(

		mFileStatus,

		// Receive function
		[this, expectedSize, timeoutSecs]()->bool {
			bool ok = mZipPort->receive([this](const std::vector<uint8_t>& data)->bool {
//				std::cerr << "ImagesTestHelper::installTcp [tfr callback] write size=" << data.size() << std::endl ;
					return mZipFileWriter->addData(data) ;
				},
				expectedSize,
				timeoutSecs
			) ;

//			std::cerr << "ImagesTestHelper::installTcp tfr callback done - ok=" << ok << std::endl ;

			return ok ;
		},

		// Cleanup function
		[this](){ zipInstallComplete(); },

		failReason
	) ;

	if (!ok)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return ;
	}

	returnList->find(RtiKeyword::INFO_VAR)->set("Transfer running in background. Use 'installStatus' command to check progress.") ;
	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::show( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	std::stringstream ss ;
	ss << std::endl ;
	imageMgr->show(ss) ;
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::showDetail( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	std::stringstream ss ;
	ss << std::endl ;
	imageMgr->showDetail(ss) ;
	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;

	// <--%%
}



//-------------------------------------------------------------------------------------------------------------
bool ImagesTestHelper::autoCleanThresholdSet( const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/image/autoCleanThreshold"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	std::string failReason ;
	if ( !imageMgr->setAutocleanThreshold(value->toUint(), failReason) )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return false ;
	}

	// Check that we aren't lower than the minimum
	unsigned actual = imageMgr->getAutocleanThreshold() ;
	if (actual != value->toUint())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Cannot set threshold below "+std::to_string(actual)) ;
		return false ;
	}
	return true ;

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::autoCleanThresholdGet( const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/image/autoCleanThreshold"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	returnList->find(pathname)->set( (int)imageMgr->getAutocleanThreshold() ) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
bool ImagesTestHelper::ubootSet( const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/image/uboot"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	std::string failReason ;
	if ( !imageMgr->setUbootInstall(value->toBool(), failReason) )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return false ;
	}
	return true ;

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::ubootGet( const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/image/uboot"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	returnList->find(pathname)->set( imageMgr->getUbootInstall() ) ;

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
bool ImagesTestHelper::urlSet( const std::string& pathname, DataVariant *value, DataVariantList *returnList )
{
	// Setter for "/image/url"
	//
	// Use the value passed in as something like:
	//
	//    int newValue = value->toInt() ;
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	std::string failReason ;
	if ( !imageMgr->setRemoteUrl(value->toString(), failReason) )
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(failReason) ;
		return false ;
	}
	return true ;

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::urlGet( const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/image/url"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//

	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	returnList->find(pathname)->set( imageMgr->getRemoteUrl() ) ;

	// <--%%
}



//-------------------------------------------------------------------------------------------------------------
void ImagesTestHelper::bankGet( const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/image/bank"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	returnList->find(pathname)->set( (imageMgr->getOsBank() == IImageTypes::OS_BANK1 ? "BANK1" : "BANK2") ) ;

	// <--%%
}








// Add any statics, private methods etc here %%-->

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::ImagesTestHelper::zipInstallComplete()
{
	Mutex::Lock lock(mMutex) ;

	// create a copy of the last install status
	mLatestStatus = IFileStatus::simpleTracker() ;
	mLatestStatus->copy(mFileStatus) ;

	// reset
	mFileStatus->restart(1) ;
	mInstallingZip = false ;
	mInstalledZip = true ;
	mZipPort.reset() ;
	mZipFileWriter.reset() ;

//std::cerr << "ImagesTestHelper::zipInstallComplete()" << std::endl ;
}

// <--%%
