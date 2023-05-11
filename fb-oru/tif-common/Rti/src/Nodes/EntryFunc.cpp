/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EntryFunc.cpp
 * \brief     Implements a directory entry that can be executed like a function
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <sstream>
#include "RtiKeyword.h"
#include "Nodes/EntryFunc.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
EntryFunc::EntryFunc(const std::string& pathname, const std::string& comment,
		const std::string& callFields, const std::string& returnFields,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	RtiDirEntry(pathname, comment, DirNode::DN_FILE, msgParser, settings),
	callVarList(0),
	returnVarList(0)
{
	setType(RTIENTRY_FUNC) ;

	// update the args lists
	std::string callArgs = mMsgParser.setCallArgs(callFields) ;
	std::string returnArgs = mMsgParser.setReturnArgs(returnFields) ;

	// create the lists
	callVarList = new DataVariantList( callArgs.c_str() );
	returnVarList = new DataVariantList( returnArgs.c_str() );
}


//-------------------------------------------------------------------------------------------------------------
EntryFunc::~EntryFunc()
{
    delete callVarList;
    delete returnVarList;
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryFunc::processFunc(const std::string& args)
{
	// set the arg values
	if( !callVarList->set( args.c_str() ) )
	{
		return RtiDirEntry::createErrorStatus(
				"Function: " + getName() + " - " + callVarList->getError()
		);
	}

	// check all required args have been set
	if (!callVarList->allSet())
	{
		return RtiDirEntry::createErrorStatus(
				"Function: " + getName() + " - unset argument " + callVarList->getError()
		);
	}

	// Check all parameters are within limits
	if (!callVarList->checkLimits())
	{
		return RtiDirEntry::createErrorStatus(
				"Function: " + getName() + " - " + callVarList->getError()
		);
	}

	// Ensure any previous results are cleared
	returnVarList->clearValues() ;

	// Preset special return vars
	std::vector<std::string> reserved(RtiKeyword::getReservedList()) ;
	for (std::vector<std::string>::const_iterator iter(reserved.begin()); iter != reserved.end(); ++iter)
	{
		returnVarList->find(*iter)->set(RtiKeyword::getDefault(*iter)) ;
	}

	// Call the member function
	std::string reply = operator()(getName()) ;

	// Return results
	std::string returnVars ;
	if (mSettings.get("showColumn")->toBool())
	{
		// column view
		if (!mSettings.get("formatVarVal")->toBool())
		{
			// simple column view
			returnVars = returnVarList->toString("\n") ;
		}
		else
		{
			// formatted column view
			std::vector< std::pair<std::string, std::string> > varVals( returnVarList->toVarVals() );

			// get max width of all variable names
			std::size_t width(0) ;
			for (DataVariantList::VarValListConstIter iter(varVals.begin()); iter != varVals.end(); ++iter)
			{
				width = std::max(width, iter->first.length()) ;
			}
			width = std::max(width, (std::size_t)20) ;

			// format the output
			std::string fill( mSettings.get("varValChar")->toString() ) ;
			char fillChar('.') ;
			if (!fill.empty())
				fillChar = fill[0] ;
			for (DataVariantList::VarValListConstIter iter(varVals.begin()); iter != varVals.end(); ++iter)
			{
				std::stringstream ss ;
				ss.width(width) ;

				ss.fill(fillChar) ;
				ss << std::left ;
				ss << iter->first ;

				ss.fill(' ') ;
				ss << ": " ;
				ss << iter->second ;
				ss << std::endl ;

				returnVars += ss.str() ;
			}
		}
	}
	else
	{
		// normal view
		returnVars = returnVarList->toString() ;
	}


	if (!reply.empty() && !returnVars.empty())
	{
		reply += "\n" ;
	}
	reply += returnVars ;
    return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryFunc::help()
{
	std::string reply ;

	reply = helpFormat(getName(), getComment()) ;

	reply += helpFormatIndent(1) + "call variables:\n" ;
	if (callVarList->empty())
	{
		reply += helpFormatIndent(2) + "No calling args\n" ;
	}
	else
	{
		reply += helpFormatIndent(2) + callVarList->varlist() + "\n" ;
	}

	reply += helpFormatIndent(1) + "return variables:\n" ;
	if (returnVarList->empty())
	{
		reply += helpFormatIndent(2) + "No return args\n" ;
	}
	else
	{
		reply += helpFormatIndent(2) + returnVarList->varlist() + "\n" ;
	}

	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryFunc::ls()
{
	std::string label = getName() + "(" + callVarList->varlist() + ")" ;
	return lsFormat(label, getComment()) ;
}
