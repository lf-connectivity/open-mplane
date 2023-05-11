/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdControlBase.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IFpgaComms.h"

#include "DpdControlBase.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdControlBase::DpdControlBase(const std::string& name) :
	Loggable(name, "DpdControl"),
	mFpgaComms(IFpgaComms::getInterface())
{
}

//-------------------------------------------------------------------------------------------------------------
DpdControlBase::~DpdControlBase()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool DpdControlBase::dpdCmd(const std::string& cmd, const std::vector<DataVariant>& args)
{
	// Create message
	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory(cmd, args) ) ;

	// send command
	std::shared_ptr<IFpgaMsg> response ;
	std::string failReason ;
	return commandGetResponse(msg, response, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdControlBase::dpdSet(const std::vector<DataVariant>& args)
{
	if (args.empty())
		return true ;

	return dpdCmd("set", args) ;
}

////-------------------------------------------------------------------------------------------------------------
//bool DpdControlBase::dpdGet(const std::vector<DataVariant>& args, const std::set<std::string>& names,
//		std::map<std::string, DataVariant>& values)
//{
//	if (names.empty())
//		return true ;
//
//	// Create message
//	std::shared_ptr<IFpgaMsg> msg( IFpgaMsg::factory("get", args, names) ) ;
//
//	// send command, get response
//	std::shared_ptr<IFpgaMsg> response ;
//	std::string failReason ;
//	if (!commandGetResponse(msg, response, failReason))
//		return false ;
//
//	// Return values
//// @TODO
//
//	return true ;
//}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool DpdControlBase::commandGetResponse(std::shared_ptr<IFpgaMsg> msg,
		std::shared_ptr<IFpgaMsg>& response, std::string& failReason)
{
	if (!mFpgaComms->commandWaitResponse(msg, response, failReason))
		return false ;

	return true ;
}

//=============================================================================================================
// PROTECTED STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool DpdControlBase::pushInt(std::vector<DataVariant>& list,
		const std::string& name, int value)
{
	DataVariant dv(name, std::string("INT")) ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdControlBase::pushFloat(std::vector<DataVariant>& list,
		const std::string& name, float value)
{
	DataVariant dv(name, std::string("FLOAT")) ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdControlBase::pushEnum(std::vector<DataVariant>& list,
		const std::string& name, const std::string& enums,
		const std::string& value)
{
	DataVariant dv(name, std::string("ENUM(") + enums + ")") ;
	dv.set(value) ;
	list.push_back(dv) ;
	return true ;
}
