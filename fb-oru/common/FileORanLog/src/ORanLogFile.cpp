/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ORanLogFile.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Path.h"

#include "ORanLogFile.h"

using namespace Mplane;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IORanLogFile> IORanLogFile::factory(const std::string & filename)
{
	std::shared_ptr<IORanLogFile> instance(std::make_shared<ORanLogFile>(filename));
	return instance;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ORanLogFile::ORanLogFile(const std::string & filename)
	: mFilename(filename)
	, mDir(".")
	, mCompress(false)
	, mGatherDataFunc()
	, mEmpty(true)
	, mError("")
{
}

//-------------------------------------------------------------------------------------------------------------
ORanLogFile::~ORanLogFile()
{
}

//-------------------------------------------------------------------------------------------------------------
void ORanLogFile::setDir(const std::string & dir)
{
	mDir = dir;
	Path::mkpath(mDir);
}

//-------------------------------------------------------------------------------------------------------------
void ORanLogFile::setCompress(bool enable)
{
	mCompress = enable;

	// TODO: implement file compression
}

//-------------------------------------------------------------------------------------------------------------
std::string ORanLogFile::path() const
{
	return mDir + "/" + mFilename;
}

//-------------------------------------------------------------------------------------------------------------
bool ORanLogFile::empty() const
{
	return mEmpty;
}

//-------------------------------------------------------------------------------------------------------------
bool ORanLogFile::generateLog()
{
	mEmpty = true;
	std::string data(dataGather());

	if (data.empty())
		return true;

	// ensure directory exists
	if (!Path::exists(mDir))
	{
		return setError("Unable to create storage directory " + mDir);
	}

	// Save the data
	std::string path(mDir + "/" + mFilename);
	std::ofstream file(path);
	if (!file.is_open())
		return setError("Unable to create file " + path);

	file << data;
	file.close();

	mEmpty = false;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void ORanLogFile::registerDataGatherer(IORanLogFile::GatherDataFunc func)
{
	mGatherDataFunc = func;
}

//-------------------------------------------------------------------------------------------------------------
std::string ORanLogFile::error()
{
	std::string err;
	swap(err, mError);
	return err;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string ORanLogFile::dataGather()
{
	if (mGatherDataFunc)
		return mGatherDataFunc();

	return "";
}

//-------------------------------------------------------------------------------------------------------------
bool ORanLogFile::setError(const std::string & error)
{
	if (!mError.empty())
		mError += "\n";
	mError += error;
	return false;
}
