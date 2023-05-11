/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AnsiEsc_unittest.cpp
 * \brief     Google Test of AnsiEsc
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the AnsiEsc class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <memory>
#include <vector>


#include "AnsiEsc.h"

using namespace Mplane;

namespace {
	std::string ansiToText(const std::string& ansi)
	{
		std::string text ;
		for (auto cc : ansi)
		{
			if (cc == '\033')
				text += "ESC" ;
			else
				text += cc ;
		}
		return text ;
	}
}

//-------------------------------------------------------------------------------------------------------------
TEST(AnsiEsc, Foreground)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::vector<AnsiEsc::Colour> colours{
		AnsiEsc::Colour::BLACK,
		AnsiEsc::Colour::DARK_GREY,
		AnsiEsc::Colour::DARK_RED,
		AnsiEsc::Colour::RED,
		AnsiEsc::Colour::DARK_GREEN,
		AnsiEsc::Colour::GREEN,
		AnsiEsc::Colour::DARK_YELLOW,
		AnsiEsc::Colour::YELLOW,
		AnsiEsc::Colour::DARK_BLUE,
		AnsiEsc::Colour::BLUE,
		AnsiEsc::Colour::DARK_MAGENTA,
		AnsiEsc::Colour::MAGENTA,
		AnsiEsc::Colour::DARK_CYAN,
		AnsiEsc::Colour::CYAN,
		AnsiEsc::Colour::LIGHT_GREY,
		AnsiEsc::Colour::WHITE,
	} ;

	for (auto foreground : colours)
	{
		std::cerr << AnsiEsc::setColour(foreground) <<
			"Fore ground: " << AnsiEsc::colourName(foreground) <<
			" Code:'" << ansiToText(AnsiEsc::setColour(foreground)) << "' " <<
			AnsiEsc::resetColour() <<
			std::endl ;
	}

}

//-------------------------------------------------------------------------------------------------------------
TEST(AnsiEsc, Background)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::vector<AnsiEsc::Colour> colours{
		AnsiEsc::Colour::BLACK,
		AnsiEsc::Colour::DARK_GREY,
		AnsiEsc::Colour::DARK_RED,
		AnsiEsc::Colour::RED,
		AnsiEsc::Colour::DARK_GREEN,
		AnsiEsc::Colour::GREEN,
		AnsiEsc::Colour::DARK_YELLOW,
		AnsiEsc::Colour::YELLOW,
		AnsiEsc::Colour::DARK_BLUE,
		AnsiEsc::Colour::BLUE,
		AnsiEsc::Colour::DARK_MAGENTA,
		AnsiEsc::Colour::MAGENTA,
		AnsiEsc::Colour::DARK_CYAN,
		AnsiEsc::Colour::CYAN,
		AnsiEsc::Colour::LIGHT_GREY,
		AnsiEsc::Colour::WHITE,
	} ;

	AnsiEsc::Colour foreground{AnsiEsc::Colour::LIGHT_GREY} ;
	for (auto background : colours)
	{
		std::cerr << AnsiEsc::setColour(foreground, background) <<
			"Back ground: " << AnsiEsc::colourName(background) <<
			" Code:'" << ansiToText(AnsiEsc::setColour(foreground, background)) << "' " <<
			AnsiEsc::resetColour() <<
			std::endl ;
	}

}

//-------------------------------------------------------------------------------------------------------------
TEST(AnsiEsc, ColourNames)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::vector<std::string> colours{
		"bLack",
		"dark grey",
		"Dark Red",
		"Red",
		"DARK GREEN",
		"GREEN",
		"darkYellow",
		"Yellow",
		"DARK blue",
		"BLUE",
		"dark MAGENTA",
		"magenta",
		"DaRk CyAn",
		"cYaN",
		"light grey",
		"white"
	} ;

	for (auto foreground : colours)
	{
		std::cerr << AnsiEsc::setColour(foreground) <<
			"Fore ground: " << foreground <<
			" Code:'" << ansiToText(AnsiEsc::setColour(foreground)) << "' " <<
			AnsiEsc::resetColour() <<
			std::endl ;
	}


//	std::vector<std::string> invalidColours{
//		"xbLack",
//		"dark grey",
//		"Dark Red",
//		"Red",
//		"DARK GREEN",
//		"GREEN",
//		"darkYellow",
//		"Yellow",
//		"DARK blue",
//		"BLUE",
//		"dark MAGENTA",
//		"magenta",
//		"DaRk CyAn",
//		"cYaN",
//		"light grey",
//		"white"
//	} ;

}
