/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileStatus.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "stringfunc.hpp"
#include "FileStatus.h"

using namespace Mplane;

#ifdef DEBUG_FILESTATUS
#define DEBUG_SHOW() debugShow()
#else
#define DEBUG_SHOW() {}
#endif

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileStatus> FileStatus::simpleTracker()
{
	return (std::make_shared<FileStatus>()) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileStatus> IFileStatus::simpleTracker()
{
	return FileStatus::simpleTracker() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileStatus> FileStatus::simpleOutput(StatusOutputFunc func)
{
	std::shared_ptr<IFileStatus> object(std::make_shared<FileStatus>()) ;
	object->setOutputFunction(func) ;
	return object ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileStatus> IFileStatus::simpleOutput(StatusOutputFunc func)
{
	return FileStatus::simpleOutput(func) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FileStatus::FileStatus() :
	mNumFiles(1),
	mCurrentFile(0),
	mOp(""),
	mFile(""),
	mFileProgress(0),
	mTotalProgress(0),
	mDone(false),
	mError(""),
	mOutputFunc(),
	mPrevProgress(-1)
{
}


//-------------------------------------------------------------------------------------------------------------
void FileStatus::copy(std::shared_ptr<IFileStatus> rhs)
{
	mNumFiles = rhs->getNumFiles() ;
	mCurrentFile = 0 ;
	mOp = rhs->getOperation() ;
	mFile = rhs->getFilename() ;
	mFileProgress = rhs->getProgress() ;
	mTotalProgress = rhs->getTotalProgress() ;
	mDone = rhs->isComplete() ;
	mError = rhs->getError() ;
	mOutputFunc = IFileStatus::StatusOutputFunc() ;
	mPrevProgress = -1 ;

	// If the specified object is a FileStatus object, then we can use it
	std::shared_ptr<FileStatus> fileStatus(std::dynamic_pointer_cast<FileStatus>(rhs)) ;
	if (!fileStatus)
		return ;

	mCurrentFile = fileStatus->mCurrentFile ;
	mOutputFunc = fileStatus->mOutputFunc ;
	mPrevProgress = fileStatus->mPrevProgress ;
}


//-------------------------------------------------------------------------------------------------------------
FileStatus::~FileStatus()
{
}


//-------------------------------------------------------------------------------------------------------------
void FileStatus::setOutputFunction(IFileStatus::StatusOutputFunc func)
{
	mOutputFunc = func ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::clearOutputFunction()
{
	mOutputFunc = IFileStatus::StatusOutputFunc() ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::restart(unsigned num)
{
	if (num > 0)
		mNumFiles = num ;

	mCurrentFile = 0 ;
	mOp.clear() ;
	mFile.clear() ;
	mFileProgress = 0 ;
	mTotalProgress = 0 ;
	mDone = false ;
	mError.clear() ;
	mPrevProgress = -1 ;

	DEBUG_SHOW() ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::operation(const std::string& op)
{
	mOp = op ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::start(const std::string& filename)
{
	++mCurrentFile ;
	mFile = filename ;
	mFileProgress = 0 ;

	if (mCurrentFile > mNumFiles)
		mNumFiles = mCurrentFile ;

	if (!mOutputFunc)
		return ;
	if (mOp.empty())
		return ;
	if (mFile.empty())
		return ;

	// Call the output function with a simple string
	mOutputFunc( outputStart(mOp, mFile) ) ;

	DEBUG_SHOW() ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::start(const std::string& op, const std::string& filename)
{
	operation(op) ;
	start(filename) ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::progress(unsigned progressPercent)
{
	if (mCurrentFile < 1)
		return ;

	// update progress then return immediately if no status change
	if (!updateProgress(progressPercent))
		return ;

	DEBUG_SHOW() ;

	if (!mOutputFunc)
		return ;

	// Call the output function with a simple string
	mOutputFunc( outputPercent(progressPercent) ) ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::end()
{
	updateProgress(100) ;

	DEBUG_SHOW() ;

	// skip if not outputting
	if (!mOutputFunc)
		return ;

	// skip if not output anything yet
	if (mFile.empty())
		return ;

	// Call the output function with a simple string
	mOutputFunc( outputPercent(100) ) ;
	mOutputFunc( outputEnd() ) ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::skip()
{
	start("") ;

	// effectively end()
	updateProgress(100) ;

	DEBUG_SHOW() ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::skip(unsigned numFiles)
{
	if (numFiles == 0)
		return ;

	for (unsigned i=0; i < numFiles; ++i)
		skip() ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::fail(const std::string& error)
{
	mError = error ;
	mDone = true ;

	DEBUG_SHOW() ;

	if (!mOutputFunc)
		return ;

	// Call the output function with a simple string
	mOutputFunc("\n") ;
}

//-------------------------------------------------------------------------------------------------------------
void FileStatus::success()
{
	// finish off any existing file if necessary
	if (mFileProgress < 100)
		end() ;

	mDone = true ;
	mCurrentFile = mNumFiles ;
	mFileProgress = 100 ;
	mTotalProgress = 100 ;

	DEBUG_SHOW() ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileStatus::isComplete() const
{
	return mDone ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileStatus::getError() const
{
	return mError ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::FileStatus::getNumFiles() const
{
	return mNumFiles ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileStatus::getFilename() const
{
	return mFile ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileStatus::getOperation() const
{
	return mOp ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned FileStatus::getProgress() const
{
	return mFileProgress ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned FileStatus::getTotalProgress() const
{
	return mTotalProgress ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string FileStatus::outputStart(const std::string& op, const std::string& filename) const
{
	return (op + ": " + filename + "   0%") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileStatus::outputPercent(unsigned progress) const
{
	// Call the output function with a simple string
	static const std::string del("\b\b\b\b    \b\b\b\b") ;

	std::string percent(std::to_string(progress)) ;
	return (del + padRight(percent, 3) + "%") ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileStatus::outputEnd() const
{
	return "\n" ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool FileStatus::updateProgress(unsigned progress)
{
	if (progress > 100)
		progress = 100 ;

	int currentProgress( static_cast<int>(mFileProgress) ) ;
	bool showUpdate(mPrevProgress != currentProgress) ;
	mPrevProgress = currentProgress ;

	mFileProgress = progress ;
	if (progress == 100)
		mTotalProgress = ( mCurrentFile * 100 ) / mNumFiles ;
	else
		mTotalProgress = ( ( (mCurrentFile-1) * 100) + progress ) / mNumFiles ;

	return showUpdate ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#ifdef DEBUG_FILESTATUS
void FileStatus::debugShow()
{
	std::cerr << "FileStatus: File " << mCurrentFile << "/" << mNumFiles <<
			" Op=" << mOp <<
			" Name=" << mFile <<
			" Progress=" << mFileProgress <<
			"% Total=" << mTotalProgress <<
			"% [Done?=" << mDone <<
			" Error=" << mError <<
			"]" << std::endl ;
}
#endif
