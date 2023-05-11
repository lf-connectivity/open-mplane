/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ORanLogFileMgr.cpp
 * \brief     Manager of ORAN log files
 *
 *
 * \details   Collects ORAN log files in an application and for generating those files
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ORanLogFileMgr.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ORanLogFileMgr::ORanLogFileMgr()
	: mDir(".")
	, mCompress(false)
	, mFiles()
	, mError("")
	, mIndex(0)
{
}

//-------------------------------------------------------------------------------------------------------------
ORanLogFileMgr::~ORanLogFileMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
void ORanLogFileMgr::addFile(std::shared_ptr<IORanLogFile> file)
{
	file->setDir(mDir);
	file->setCompress(mCompress);
	mFiles.push_back(file);
}

//-------------------------------------------------------------------------------------------------------------
void ORanLogFileMgr::setFileCompression(bool enable)
{
	mCompress = enable;
	for (auto file : mFiles)
		file->setCompress(mCompress);
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> ORanLogFileMgr::generateLogs()
{
	if (!startLog())
		return std::vector<std::string>();

	while (!doneLog())
	{
		if (!nextLog())
			return std::vector<std::string>();
	}

	return paths();
}

//-------------------------------------------------------------------------------------------------------------
void ORanLogFileMgr::setDir(const std::string & dir)
{
	mDir = dir;
	for (auto file : mFiles)
		file->setDir(mDir);
}

//-------------------------------------------------------------------------------------------------------------
std::string ORanLogFileMgr::error()
{
	std::string err;
	swap(err, mError);
	return err;
}

//-------------------------------------------------------------------------------------------------------------
void ORanLogFileMgr::clear()
{
	mFiles.clear();
	mError.clear();
	mDir = ".";
	mCompress = false;
}

//-------------------------------------------------------------------------------------------------------------
bool ORanLogFileMgr::startLog()
{
	mIndex = 0;
	return nextLog();
}

//-------------------------------------------------------------------------------------------------------------
bool ORanLogFileMgr::doneLog()
{
	if (mIndex >= mFiles.size())
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool ORanLogFileMgr::nextLog()
{
	// Process the current file then increment index if ok
	if (mIndex >= mFiles.size())
		return false;

	if (!mFiles[mIndex]->generateLog())
	{
		return setError("Failed to gather data for " + mFiles[mIndex]->path() + " : " + mFiles[mIndex]->error());
	}

	++mIndex;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> ORanLogFileMgr::paths()
{
	std::vector<std::string> list;

	for (auto file : mFiles)
	{
		if (!file->empty())
			list.push_back(file->path());
	}

	return list;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool ORanLogFileMgr::setError(const std::string & error)
{
	if (!mError.empty())
		mError += "\n";
	mError += error;
	return false;
}
