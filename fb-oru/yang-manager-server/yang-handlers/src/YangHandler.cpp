/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandler.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "XpathUtils.h"
#include "YangParamUtils.h"
#include "YangHandler.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangHandler::YangHandler(const std::string &name, std::shared_ptr<IYangModuleMgr> moduleMgr) :
	mName(name),
	mModuleMgr(moduleMgr),
	mPersist(IYangPersist::factory(mName))
{
	// ensure we get any saved values
	mPersist->read() ;
}

//-------------------------------------------------------------------------------------------------------------
YangHandler::~YangHandler()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string YangHandler::name() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
bool YangHandler::initialise()
{
	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangModuleMgr> YangHandler::moduleMgr() const
{
	return mModuleMgr ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangPersist> YangHandler::persistMgr() const
{
	return mPersist ;
}

//-------------------------------------------------------------------------------------------------------------
void YangHandler::makePersistent(const std::set<std::string> &paths)
{
	mPersist->setPersist(paths) ;
}

//-------------------------------------------------------------------------------------------------------------
void YangHandler::makePersistent(const std::string &xpath)
{
	mPersist->setPersist(xpath) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string YangHandler::leafName(const std::string &xpath) const
{
	return XpathUtils::leafName(xpath) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned YangHandler::getParamUint16(uint32_t moduleId, const std::string &xpath, bool &ok)
{
	ok=false ;

	std::shared_ptr<YangParam> param(getParam(moduleId, xpath)) ;
	if (!param)
		return 0 ;

	std::string error ;
	uint16_t val(YangParamUtils::toUint16(param, error)) ;
	if (!error.empty())
		return 0 ;

	ok = true ;
	return val ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<YangParam> YangHandler::getParam(uint32_t moduleId, const std::string &xpath)
{
	std::shared_ptr<YangParam> param ;
	YangResult_E result(mModuleMgr->getItem(moduleId, xpath, param)) ;

	if (result != YangResult_E::OK)
		return std::shared_ptr<YangParam>() ;

	return param ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier::FFTsizeType YangHandler::frameStructToFFTsize(uint8_t frameStruct)
{
	uint8_t numfft( (frameStruct & 0xf0) >> 4) ;

	switch (numfft)
	{
	case 12:	return ICarrier::FFT_4096 ;
	case 11:	return ICarrier::FFT_2048 ;
	case 10:	return ICarrier::FFT_1024 ;
	case  9:	return ICarrier::FFT_512 ;
	case  8:	return ICarrier::FFT_256 ;
	case  7:	return ICarrier::FFT_128 ;
	default:
		return ICarrier::FFT_NONE ;
	}

	return ICarrier::FFT_NONE ;
}


//-------------------------------------------------------------------------------------------------------------
ICarrier::ScsType YangHandler::frameStructToScsType(uint8_t frameStruct)
{
	uint8_t scs(frameStruct & 0xf) ;

	switch (scs)
	{
	case  0:	return ICarrier::SCS_15kHz ;
	case  1:	return ICarrier::SCS_30kHz ;
	case  2:	return ICarrier::SCS_60kHz ;
	case  3:	return ICarrier::SCS_120kHz ;
	case  4:	return ICarrier::SCS_240kHz ;
	case 12:	return ICarrier::SCS_1kHz25 ;
	case 13:	return ICarrier::SCS_3kHz75 ;
	case 14:	return ICarrier::SCS_5kHz ;
	case 15:	return ICarrier::SCS_7kHz5 ;
	default:
		return ICarrier::SCS_NONE ;
	}

	return ICarrier::SCS_NONE ;
}

//-------------------------------------------------------------------------------------------------------------
bool YangHandler::listIndex(const std::string &xpath, std::string& listName, std::string &key, std::string &value) const
{
	return XpathUtils::listIndex(xpath, listName, key, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool YangHandler::listIndex(const std::string &xpath, std::string& listName, std::string &key, int &value) const
{
	return XpathUtils::listIndex(xpath, listName, key, value) ;
}
