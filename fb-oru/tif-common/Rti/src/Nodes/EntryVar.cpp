/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EntryVar.cpp
 * \brief     Implements a directory entry that can be executed like a function
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include "Nodes/EntryVar.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANT
//=============================================================================================================
static const std::string ValueStr = "Value" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
EntryVar::EntryVar(const std::string& pathname, const std::string& varType, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, setCallFields(varType), setReturnFields(varType), msgParser, settings),
	mData(new DataVariant( ValueStr, varType ))
{
	setType(RTIENTRY_VAR) ;
}

//-------------------------------------------------------------------------------------------------------------
EntryVar::EntryVar(const std::string& pathname, std::shared_ptr<DataVariant> data, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, setCallFields(data->getTypeStr()), setReturnFields(data->getTypeStr()),
			msgParser, settings),
	mData(data)
{
	setType(RTIENTRY_VAR) ;
}


//-------------------------------------------------------------------------------------------------------------
EntryVar::~EntryVar()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryVar::ls()
{
	std::string label ;
	std::string name( getName() ) ;
	std::string value( mData->getValue() ) ;

	if (!mSettings.get("formatVarVal")->toBool())
	{
		// simple column view
		label = name + "=" + value ;
	}
	else
	{
		unsigned labelWidth(lsLabelWidth()) ;

		// use 32% for name
		unsigned nameWidth( labelWidth * 32 / 100) ;

		// format the output
		std::string fill( mSettings.get("varValChar")->toString() ) ;
		char fillChar('.') ;
		if (!fill.empty())
			fillChar = fill[0] ;

		std::stringstream ss ;
		ss.width(nameWidth) ;

		ss.fill(fillChar) ;
		ss << std::left ;
		ss << name ;

		ss.fill(' ') ;
		ss << ": " ;
		ss << value ;

		label = ss.str() ;
	}
	return lsFormat(label, getComment()) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string EntryVar::operator()(const std::string& name)
{
	// If "value" is set then this is a "set" access; otherwise it's a "get" access
	if (callVarList->find(ValueStr)->isSet())
	{
		mData->set(callVarList->find(ValueStr)->toString()) ;
	}

	// Now get the current value
	returnVarList->find(ValueStr)->set(mData->toString());

	// Just use the return vars to pass the information back
    return "" ;
}

//-------------------------------------------------------------------------------------------------------------
void EntryVar::setData(const std::string& value)
{
	mData->set(value) ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string EntryVar::getTypeStr()
{
	return mData->getTypeStr() ;
}

//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string EntryVar::setCallFields(const std::string& varType)
{
	// make input optional
	std::string args = "[" + varType + " " + ValueStr + "]" ;

	return args ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryVar::setReturnFields(const std::string& varType)
{
	std::string fields = varType + " " + ValueStr ;

	return fields ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string& EntryVar::valueStr()
{
	return ValueStr ;
}
