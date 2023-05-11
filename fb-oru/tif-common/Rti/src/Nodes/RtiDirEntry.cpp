/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiDirEntry.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include "RtiKeyword.h"
#include "Nodes/RtiDirEntry.h"

using namespace Mplane ;


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
std::string RtiDirEntry::createErrorStatus(const std::string& message)
{
	std::string error(
		RtiKeyword::STATUS_VAR + "=" + RtiKeyword::StatusERROR + " " +
		RtiKeyword::MESSAGE_VAR + "=\"" + message + "\""
	) ;
	return error ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiDirEntry::createOkStatus()
{
	static const std::string OkStr(RtiKeyword::STATUS_VAR + "=" + RtiKeyword::StatusOK) ;
	return OkStr ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RtiDirEntry::RtiDirEntry(const std::string& pathname, const std::string& comment, DirNode::DirNodeType type,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	DirNode(pathname, type),
	mType(RTIENTRY_BASE),
	mComment(comment),
	mMsgParser(msgParser),
	mSettings(settings)
{

}


//-------------------------------------------------------------------------------------------------------------
RtiDirEntry::~RtiDirEntry()
{

}

//-------------------------------------------------------------------------------------------------------------
std::string RtiDirEntry::getComment() const
{
	return mComment ;
}

//-------------------------------------------------------------------------------------------------------------
RtiDirEntry::RtiDirEntryType RtiDirEntry::getType() const
{
	return mType ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void RtiDirEntry::setType(RtiDirEntryType type)
{
	mType = type ;
}


//-------------------------------------------------------------------------------------------------------------
std::string RtiDirEntry::lsFormat(const std::string& label, const std::string& comment)
{
	std::stringstream ss ;
	ss.width(lsLabelWidth()) ;

	std::vector<std::string> labelLines( wrapLabel(label) ) ;

	for (unsigned idx=0; idx < labelLines.size(); ++idx)
	{
		// indent wrapped lines
		if (idx > 0)
			ss << "  " ;
		ss << std::left << labelLines[idx] ;

		if ( (idx==0) && !comment.empty())
			ss << std::left << "# " << comment ;

		ss << std::endl ;
	}
	return ss.str() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned RtiDirEntry::lsLabelWidth()
{
	// @todo - scale depending on tty width?
	return 60 ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiDirEntry::helpTitleFormat(const std::string& title)
{
	std::string str = "\n" + title + ":\n" ;
	return str ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiDirEntry::helpFormat(const std::string& label, const std::string& comment)
{
	std::stringstream ss ;
	ss << helpFormatIndent(0) << label ;
	if (!comment.empty())
		ss << " - " << comment ;
	ss << std::endl ;

	return ss.str() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiDirEntry::helpFormatIndent(unsigned level)
{
	std::string indent( (level+1)*4, ' ') ;
	return indent ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> RtiDirEntry::wrapLabel(const std::string& label)
{
	std::vector<std::string> labelLines ;

	// is the string longer than will fit into the space?
	if (label.length() < lsLabelWidth())
	{
		// will fit, so return single line
		labelLines.push_back(label) ;
		return labelLines ;
	}

	// split on ',' first
	std::vector<std::string> commaLines(wrapLabel(label, ",")) ;
	for (std::vector<std::string>::const_iterator iter(commaLines.begin()); iter != commaLines.end() ; ++iter)
	{
		// split on space if necessary
		std::vector<std::string> spaceLines(wrapLabel(*iter, " ")) ;
		labelLines.insert(labelLines.end(), spaceLines.begin(), spaceLines.end()) ;
	}

	return labelLines ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> RtiDirEntry::wrapLabel(const std::string& label, const std::string& wrapStr)
{
	std::vector<std::string> labelLines ;

	// is the string longer than will fit into the space?
	if (label.length() < lsLabelWidth())
	{
		// will fit, so return single line
		labelLines.push_back(label) ;
		return labelLines ;
	}

	std::string line(label) ;
	std::size_t commaPos(line.find_first_of(wrapStr)) ;
	while(commaPos != std::string::npos)
	{
		std::string subLine(line.substr(0, commaPos+1)) ;
		line = line.substr(commaPos+1) ;

		labelLines.push_back(subLine) ;

		commaPos = line.find_first_of(wrapStr) ;
	}

	labelLines.push_back(line) ;

	return labelLines ;
}
