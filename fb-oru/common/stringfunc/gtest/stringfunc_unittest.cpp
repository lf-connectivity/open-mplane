/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      stringfunc_unittest.cpp
 * \brief     Google Test of stringfunc
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the stringfunc class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <regex>

#include <memory>
#include "stringfunc.hpp"

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, PadLeft)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = padLeft("ABCDE", 10, '.') ;
	EXPECT_EQ(std::string("ABCDE....."), result) ;

	result = padLeft("ABCDE", 5, '.') ;
	EXPECT_EQ(std::string("ABCDE"), result) ;

	result = padLeft("ABCDE", 2, '.') ;
	EXPECT_EQ(std::string("ABCDE"), result) ;

	result = padLeft("", 10, '-') ;
	EXPECT_EQ(std::string("----------"), result) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, PadRight)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = padRight("ABCDE", 10, '.') ;
	EXPECT_EQ(std::string(".....ABCDE"), result) ;

	result = padRight("ABCDE", 5, '.') ;
	EXPECT_EQ(std::string("ABCDE"), result) ;

	result = padRight("ABCDE", 2, '.') ;
	EXPECT_EQ(std::string("ABCDE"), result) ;

	result = padRight("", 10, '-') ;
	EXPECT_EQ(std::string("----------"), result) ;
}



//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, RemoveSpaces)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = removeSpaces(" A  B C   DE  ") ;
	EXPECT_EQ(std::string("ABCDE"), result) ;
	result = removeSpaces("A  B C   DE ") ;
	EXPECT_EQ(std::string("ABCDE"), result) ;
	result = removeSpaces("A  B C   DE") ;
	EXPECT_EQ(std::string("ABCDE"), result) ;
	result = removeSpaces("ABCDE") ;
	EXPECT_EQ(std::string("ABCDE"), result) ;
	result = removeSpaces("") ;
	EXPECT_EQ(std::string(""), result) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, ToLower)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = toLower("ABCDE") ;
	EXPECT_EQ(std::string("abcde"), result) ;
	result = toLower("AbcDe") ;
	EXPECT_EQ(std::string("abcde"), result) ;
	result = toLower("abcde") ;
	EXPECT_EQ(std::string("abcde"), result) ;
	result = toLower("") ;
	EXPECT_EQ(std::string(""), result) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, ToUpper)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::string result ;
	result = toUpper("ABCDE") ;
	EXPECT_EQ(std::string("ABCDE"), result) ;
	result = toUpper("AbcDe") ;
	EXPECT_EQ(std::string("ABCDE"), result) ;
	result = toUpper("abcde") ;
	EXPECT_EQ(std::string("ABCDE"), result) ;
	result = toUpper("") ;
	EXPECT_EQ(std::string(""), result) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, ToInitialCapital)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::string result ;
	result = toInitialCapital("ABCDE") ;
	EXPECT_EQ(std::string("Abcde"), result) ;
	result = toInitialCapital("AbcDe") ;
	EXPECT_EQ(std::string("Abcde"), result) ;
	result = toInitialCapital("abcde") ;
	EXPECT_EQ(std::string("Abcde"), result) ;
	result = toInitialCapital("aBCDE") ;
	EXPECT_EQ(std::string("Abcde"), result) ;
	result = toInitialCapital("a") ;
	EXPECT_EQ(std::string("A"), result) ;
	result = toInitialCapital("") ;
	EXPECT_EQ(std::string(""), result) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, StartsWith)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	EXPECT_TRUE(startsWith("ABCxyz", "ABC")) ;
	EXPECT_TRUE(startsWith("ABCABC", "ABC")) ;
	EXPECT_FALSE(startsWith(" ABCxyz", "ABC")) ;
	EXPECT_FALSE(startsWith("xyzABC", "ABC")) ;
	EXPECT_FALSE(startsWith("", "ABC")) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, Follows)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::string result ;
	result = follows("ABCDEFGHIJKLMNOP", "GHI") ;
	EXPECT_EQ(std::string("JKLMNOP"), result) ;
	result = follows("", "GHI") ;
	EXPECT_EQ(std::string(""), result) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, TrimRight)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = trim_right(" A  B C   DE  ", " ") ;
	EXPECT_EQ(std::string(" A  B C   DE"), result) ;
	result = trim_right(" A  B C   DE  ", " xyz") ;
	EXPECT_EQ(std::string(" A  B C   DE"), result) ;
	result = trim_right(" A  B C   DE  ", "xyz") ;
	EXPECT_EQ(std::string(" A  B C   DE  "), result) ;
	result = trim_right(" A  B C   DE  ", " DE") ;
	EXPECT_EQ(std::string(" A  B C"), result) ;
	result = trim_right(" A  B C   DE  ", " AB") ;
	EXPECT_EQ(std::string(" A  B C   DE"), result) ;
	result = trim_right("   ", " ") ;
	EXPECT_EQ(std::string(""), result) ;
	result = trim_right("", " ") ;
	EXPECT_EQ(std::string(""), result) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, Trim)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = trim(" A  B C   DE  ", " ") ;
	EXPECT_EQ(std::string("A  B C   DE"), result) ;
	result = trim(" A  B C   DE  ", " xyz") ;
	EXPECT_EQ(std::string("A  B C   DE"), result) ;
	result = trim(" A  B C   DE  ", "xyz") ;
	EXPECT_EQ(std::string(" A  B C   DE  "), result) ;
	result = trim(" A  B C   DE  ", " DE") ;
	EXPECT_EQ(std::string("A  B C"), result) ;
	result = trim(" A  B C   DE  ", " AB") ;
	EXPECT_EQ(std::string("C   DE"), result) ;
	result = trim("   ", " ") ;
	EXPECT_EQ(std::string(""), result) ;
	result = trim("", " ") ;
	EXPECT_EQ(std::string(""), result) ;


	std::string api("m6/c1VtwKU6tfj6GzbOQNQ\n") ;
	api.push_back('\0') ;
	std::cerr << "DATA: " ;
	for (char cc : api)
	{
		std::cerr << std::hex << " 0x" << (unsigned)cc ;
	}
	std::cerr << std::dec << std::endl ;

	std::string spaces(" \r\n") ;
	spaces.push_back('\0') ;

	result = trim(api, spaces) ;
	EXPECT_EQ(std::string("m6/c1VtwKU6tfj6GzbOQNQ"), result) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, TrimLeft)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = trim_left(" A  B C   DE  ", " ") ;
	EXPECT_EQ(std::string("A  B C   DE  "), result) ;
	result = trim_left(" A  B C   DE  ", " xyz") ;
	EXPECT_EQ(std::string("A  B C   DE  "), result) ;
	result = trim_left(" A  B C   DE  ", "xyz") ;
	EXPECT_EQ(std::string(" A  B C   DE  "), result) ;
	result = trim_left(" A  B C   DE  ", " DE") ;
	EXPECT_EQ(std::string("A  B C   DE  "), result) ;
	result = trim_left(" A  B C   DE  ", " AB") ;
	EXPECT_EQ(std::string("C   DE  "), result) ;
	result = trim_left("   ", " ") ;
	EXPECT_EQ(std::string(""), result) ;
	result = trim_left("", " ") ;
	EXPECT_EQ(std::string(""), result) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, ReplaceChars)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = replaceChars(" A  B C   DE  ", " ", '.') ;
	EXPECT_EQ(std::string(".A..B.C...DE.."), result) ;
	result = replaceChars(" A  B C   DE  ", " xyz", '.') ;
	EXPECT_EQ(std::string(".A..B.C...DE.."), result) ;
	result = replaceChars(" A  B C   DE  ", "xyz", '.') ;
	EXPECT_EQ(std::string(" A  B C   DE  "), result) ;
	result = replaceChars(" A  B C   DE  ", " DE", '.') ;
	EXPECT_EQ(std::string(".A..B.C......."), result) ;
	result = replaceChars(" A  B C   DE  ", " AB", '.') ;
	EXPECT_EQ(std::string("......C...DE.."), result) ;
	result = replaceChars("", " ", '.') ;
	EXPECT_EQ(std::string(""), result) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, ReplaceStrs)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = replaceStrs(" A  B C   DE  ", " ", ".") ;
	EXPECT_EQ(std::string(".A..B.C...DE.."), result) ;
	result = replaceStrs(" A  B C   DE  ", " D", ".") ;
	EXPECT_EQ(std::string(" A  B C  .E  "), result) ;
	result = replaceStrs("", " ", ".") ;
	EXPECT_EQ(std::string(""), result) ;

	result = replaceStrs("/A/.B/C.x/.DE.x/F", "/.", "/") ;
	EXPECT_EQ(std::string("/A/B/C.x/DE.x/F"), result) ;

	result = replaceStrs(".A..B.C...DE..", ".", "/.") ;
	EXPECT_EQ(std::string("/.A/./.B/.C/././.DE/./."), result) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, TrimFloat)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = trim_float("123.45") ;
	EXPECT_EQ(std::string("123.45"), result) ;
	result = trim_float("123.450") ;
	EXPECT_EQ(std::string("123.45"), result) ;
	result = trim_float("123.45000") ;
	EXPECT_EQ(std::string("123.45"), result) ;
	result = trim_float("123.000") ;
	EXPECT_EQ(std::string("123"), result) ;
	result = trim_float("123000") ;
	EXPECT_EQ(std::string("123000"), result) ;
	result = trim_float("123000.") ;
	EXPECT_EQ(std::string("123000"), result) ;
	result = trim_float("123000.0") ;
	EXPECT_EQ(std::string("123000"), result) ;
	result = trim_float("123000.000") ;
	EXPECT_EQ(std::string("123000"), result) ;
	result = trim_float("") ;
	EXPECT_EQ(std::string(""), result) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, LongestCommonPrefix)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;
	result = longestCommonPrefix("ABCDE", "") ;
	EXPECT_TRUE(result.empty()) ;
	result = longestCommonPrefix("", "ABCDE") ;
	EXPECT_TRUE(result.empty()) ;

	result = longestCommonPrefix("ABCDEfgh", "ABCDE") ;
	EXPECT_EQ("ABCDE", result) ;

	result = longestCommonPrefix("ABCDEfgh", "ABCDEjkl") ;
	EXPECT_EQ("ABCDE", result) ;

	result = longestCommonPrefix("ABCDE", "ABCDEfgh") ;
	EXPECT_EQ("ABCDE", result) ;

	result = longestCommonPrefix("A", "A") ;
	EXPECT_EQ("A", result) ;
	result = longestCommonPrefix("Axfg", "A") ;
	EXPECT_EQ("A", result) ;
	result = longestCommonPrefix("A", "Auyiyui") ;
	EXPECT_EQ("A", result) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, LongestCommonPrefixVector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::string result ;

	std::vector<std::string> test1{
		"ABCDEahjfhjfhj",
		"ABCDEahjfhjfhjryuryru",
		"ABCDEahjfhjfhjryuryrufui",
		"ABCDEahjarat",
		"ABCDE",
	} ;
	result = longestCommonPrefix(test1) ;
	EXPECT_EQ("ABCDE", result) ;

	std::vector<std::string> test2{
		"ABCDEahjfhjfhj",
		"",
		"ABCDEahjfhjfhjryuryrufui",
		"ABCDEahjarat",
		"ABCDE",
	} ;
	result = longestCommonPrefix(test2) ;
	EXPECT_TRUE(result.empty()) ;

	std::vector<std::string> test3{
		"ABCDEahjfhjfhj",
		"AB",
		"ABCDEahjfhjfhjryuryrufui",
		"ABCDEahjarat",
		"A",
	} ;
	result = longestCommonPrefix(test3) ;
	EXPECT_EQ("A", result) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, ExtractInt)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	bool ok ;

	EXPECT_EQ(1, extractInt("1", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(12, extractInt("12", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(123, extractInt("  123  ", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(1234, extractInt("xx 1234", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(-123, extractInt("-123", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(-123, extractInt(" -123 ", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(-1234, extractInt("xx-1234", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(0, extractInt(" - 123 ", ok)) ;
	EXPECT_FALSE(ok) ;

	EXPECT_EQ(123, extractInt(" - 123 ", ok, 2)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(0, extractInt(" xyz ", ok)) ;
	EXPECT_FALSE(ok) ;

	EXPECT_EQ(0, extractInt("", ok)) ;
	EXPECT_FALSE(ok) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, ExtractUnsigned)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	bool ok ;

	EXPECT_EQ(1u, extractUnsigned("1", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(12u, extractUnsigned("12", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(123u, extractUnsigned("  123  ", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(1234u, extractUnsigned("xx 1234", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(123u, extractUnsigned("-123", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(123u, extractUnsigned(" -123 ", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(1234u, extractUnsigned("xx-1234", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(123u, extractUnsigned(" - 123 ", ok)) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(0u, extractUnsigned(" xyz ", ok)) ;
	EXPECT_FALSE(ok) ;

	EXPECT_EQ(0u, extractUnsigned("", ok)) ;
	EXPECT_FALSE(ok) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, ExpandStr)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::map<std::string, std::string> vars{
		{ "a", "10" },
		{ "b", "20" },
		{ "c", "30" },
		{ "var1", "x" },
		{ "var2", "y" },
		{ "var3", "z" },
	} ;

	std::string result ;

	result = expandStr("...${a}..${b}.${c}", vars) ;
	EXPECT_EQ(result, "...10..20.30") ;

	result = expandStr("...${var1}..${var2}.${var3}", vars) ;
	EXPECT_EQ(result, "...x..y.z") ;

	result = expandStr("...${a}..${b}.${c", vars) ;
	EXPECT_EQ(result, "...10..20.${c") ;

	result = expandStr("...${a}..${b}.$c}", vars) ;
	EXPECT_EQ(result, "...10..20.$c}") ;

	result = expandStr("...${a}..$b}.${c}", vars) ;
	EXPECT_EQ(result, "...10..$b}.30") ;

	result = expandStr("...${a..${b}.${c}", vars) ;
	EXPECT_EQ(result, "....30") ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(stringfunc, MacId)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::map<std::string, uint64_t> mactest{
		// invalid
		{ "a", 0 },
		{ "11:22:33:44:55-66", 0 },
		{ "1::22:33:44:55:66", 0 },
		{ "11:22:33:x4:55:66", 0 },
		// valid
		{ "11:22:33:44:55:66", 0x112233445566UL },
		{ "11:00:33:AA:55:BB", 0x110033AA55BBUL },
		{ "01:00:03:0A:05:0B", 0x0100030A050BUL },
	} ;

	std::string macstr ;
	uint64_t macid ;

	// convert from string to mac
	for (auto entry : mactest)
	{
		macid = strToMac(entry.first) ;
		EXPECT_EQ(entry.second, macid) ;
	}

	// convert from mac to string
	for (auto entry : mactest)
	{
		if (entry.second == 0)
			continue ;

		macstr = macToStr(entry.second) ;
		EXPECT_EQ(entry.first, macstr) ;
	}

}


