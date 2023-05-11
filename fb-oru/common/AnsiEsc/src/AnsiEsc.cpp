/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AnsiEsc.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>

#include "stringfunc.hpp"
#include "AnsiEsc.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string ESC("\033") ;
const std::string CSI(ESC + "[") ;
const std::string SGR_CODE("m") ;
const std::string FOREGROUND_OFFSET{"3"} ;
const std::string BACKGROUND_OFFSET{"4"} ;
const std::map<AnsiEsc::Colour, std::string> COLOUR_TABLE{
	{ AnsiEsc::Colour::NONE, 			"0" },
	{ AnsiEsc::Colour::BLACK, 			"0" },
	{ AnsiEsc::Colour::DARK_GREY, 		"0;1" },
	{ AnsiEsc::Colour::DARK_RED, 		"1" },
	{ AnsiEsc::Colour::RED, 			"1;1" },
	{ AnsiEsc::Colour::DARK_GREEN, 		"2" },
	{ AnsiEsc::Colour::GREEN, 			"2;1" },
	{ AnsiEsc::Colour::DARK_YELLOW, 	"3" },
	{ AnsiEsc::Colour::YELLOW, 			"3;1" },
	{ AnsiEsc::Colour::DARK_BLUE, 		"4" },
	{ AnsiEsc::Colour::BLUE, 			"4;1" },
	{ AnsiEsc::Colour::DARK_MAGENTA, 	"5" },
	{ AnsiEsc::Colour::MAGENTA, 		"5;1" },
	{ AnsiEsc::Colour::DARK_CYAN, 		"6" },
	{ AnsiEsc::Colour::CYAN, 			"6;1" },
	{ AnsiEsc::Colour::LIGHT_GREY, 		"7" },
	{ AnsiEsc::Colour::WHITE, 			"7;1" },
};

const std::map<AnsiEsc::Colour, std::string> COLOUR_NAME{
	{ AnsiEsc::Colour::NONE, 			"No Colour" },
	{ AnsiEsc::Colour::BLACK, 			"Black" },
	{ AnsiEsc::Colour::DARK_GREY, 		"Dark Grey" },
	{ AnsiEsc::Colour::DARK_RED, 		"Dark Red" },
	{ AnsiEsc::Colour::RED, 			"Red" },
	{ AnsiEsc::Colour::DARK_GREEN, 		"Dark Green" },
	{ AnsiEsc::Colour::GREEN, 			"Green" },
	{ AnsiEsc::Colour::DARK_YELLOW, 	"Dark Yellow" },
	{ AnsiEsc::Colour::YELLOW, 			"Yellow" },
	{ AnsiEsc::Colour::DARK_BLUE, 		"Dark Blue" },
	{ AnsiEsc::Colour::BLUE, 			"Blue" },
	{ AnsiEsc::Colour::DARK_MAGENTA, 	"Dark Magenta" },
	{ AnsiEsc::Colour::MAGENTA, 		"Magenta" },
	{ AnsiEsc::Colour::DARK_CYAN, 		"Dark Cyan" },
	{ AnsiEsc::Colour::CYAN, 			"Cyan" },
	{ AnsiEsc::Colour::LIGHT_GREY, 		"Light Grey" },
	{ AnsiEsc::Colour::WHITE, 			"White" },
};

const std::map<std::string, AnsiEsc::Colour> COLOUR_FROM_NAME{
	{ "black", AnsiEsc::Colour::BLACK },
	{ "darkgrey", AnsiEsc::Colour::DARK_GREY },
	{ "darkred", AnsiEsc::Colour::DARK_RED },
	{ "red", AnsiEsc::Colour::RED },
	{ "darkgreen", AnsiEsc::Colour::DARK_GREEN },
	{ "green", AnsiEsc::Colour::GREEN },
	{ "darkyellow", AnsiEsc::Colour::DARK_YELLOW },
	{ "yellow", AnsiEsc::Colour::YELLOW },
	{ "darkblue", AnsiEsc::Colour::DARK_BLUE },
	{ "blue", AnsiEsc::Colour::BLUE },
	{ "darkmagenta", AnsiEsc::Colour::DARK_MAGENTA },
	{ "magenta", AnsiEsc::Colour::MAGENTA },
	{ "darkcyan", AnsiEsc::Colour::DARK_CYAN },
	{ "cyan", AnsiEsc::Colour::CYAN },
	{ "lightgrey", AnsiEsc::Colour::LIGHT_GREY },
	{ "white", AnsiEsc::Colour::WHITE },
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AnsiEsc::Colour AnsiEsc::colour(const std::string& colourName)
{
	std::string lower(removeSpaces(toLower(colourName))) ;
	auto entry(COLOUR_FROM_NAME.find(lower)) ;
	if (entry == COLOUR_FROM_NAME.end())
		return AnsiEsc::Colour::NONE ;

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
std::string AnsiEsc::colourName(Colour colour)
{
	return COLOUR_NAME.at(colour) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string AnsiEsc::setColour(Colour foreground, Colour background)
{
	return CSI +
			FOREGROUND_OFFSET + COLOUR_TABLE.at(foreground) + ";" +
			BACKGROUND_OFFSET + COLOUR_TABLE.at(background) +
			SGR_CODE ;
}

//-------------------------------------------------------------------------------------------------------------
std::string AnsiEsc::setColour(Colour foreground)
{
	return CSI + FOREGROUND_OFFSET + COLOUR_TABLE.at(foreground) + SGR_CODE ;
}

//-------------------------------------------------------------------------------------------------------------
std::string AnsiEsc::resetColour()
{
	return CSI + "0" + SGR_CODE ;
}

//-------------------------------------------------------------------------------------------------------------
std::string AnsiEsc::setColour(const std::string& foregroundName)
{
	AnsiEsc::Colour fore(colour(foregroundName)) ;
	if (fore == AnsiEsc::Colour::NONE)
		return "" ;

	return setColour(fore) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string AnsiEsc::setColour(const std::string& foregroundName, const std::string& backgroundName)
{
	AnsiEsc::Colour fore(colour(foregroundName)) ;
	if (fore == AnsiEsc::Colour::NONE)
		return "" ;
	AnsiEsc::Colour back(colour(backgroundName)) ;
	if (back == AnsiEsc::Colour::NONE)
		return "" ;

	return setColour(fore, back) ;
}
