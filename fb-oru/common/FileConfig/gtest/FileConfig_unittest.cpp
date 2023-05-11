/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileConfig_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#include <unistd.h>

#include "gtest/gtest.h"

#include "Path.h"
#include "FileConfig.h"
#include "FileConfigWriter.h"

using namespace Mplane ;

//===================================================================================================================
const std::string TESTDIR("../../../FileConfig/gtest/test/") ;

//===================================================================================================================
class FileConfigTest : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
    	const ::testing::TestInfo* const test_info =
    	  ::testing::UnitTest::GetInstance()->current_test_info();

    	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    	std::cout << test_info->name() << " - START" <<  std::endl;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }

    void dumpValues(const std::map<std::string, std::string>& got)
    {
    	std::cerr << "VALUES" << std::endl ;
    	for (auto val : got)
    	{
    		std::cerr << " + '" << val.first << "' = " << " '" << val.second << "'" << std::endl ;
    	}
    }

    bool compareSections(const std::set<std::string>& expected, const FileConfigBase& fc)
    {
    	std::vector<std::string> sections(fc.sections()) ;
    	if (expected.size() != sections.size())
    	{
    		std::cerr << "Different number of sections: expected " << expected.size() << " got " << sections.size() << std::endl ;
    		return false ;
    	}
    	for (auto section : sections)
    	{
    		if (expected.find(section) == expected.end())
    		{
    			std::cerr << "Cannot find section " << section << " in expected list" << std::endl ;
    			return false ;
    		}
    	}

    	return true ;
    }

    bool compareGlobals(const std::map<std::string, std::string>& expected, const FileConfigBase& fc)
    {
    	for (auto expect : expected)
    	{
    		if (!fc.isVariable(expect.first))
    		{
    			std::cerr << "Cannot find var '" << expect.first << "'" << std::endl ;
    			return false ;
    		}

    		if (expect.second != fc.value(expect.first))
    		{
    			std::cerr << "Value mismatch var '" << expect.first << "' = '" << expect.second << "' got '" << fc.value(expect.first) << "'" << std::endl ;
    			return false ;
    		}
    	}
    	return true ;
    }

    bool compareVars(const std::map<std::string, std::map<std::string, std::string>>& expected,
    		const std::map<std::string, std::string>& globals, const FileConfigBase& fc)
    {
    	for (auto sectionEntry : expected)
    	{
    		std::string section(sectionEntry.first) ;
    		if (!fc.isSection(section))
    		{
    			std::cerr << "Missing expected section " << section << std::endl ;
    			return false ;
    		}

        	for (auto expect : sectionEntry.second)
        	{
        		if (!fc.isVariable(section, expect.first))
        		{
        			std::cerr << "Cannot find section " << section << " var '" << expect.first << "'" << std::endl ;
        			return false ;
        		}

        		if (expect.second != fc.value(section, expect.first))
        		{
        			std::cerr << "Section " << section << " value mismatch var '" << expect.first << "' = '" << expect.second << "' got '" << fc.value(section, expect.first) << "'" << std::endl ;
        			return false ;
        		}
        	}

        	// globals
        	for (auto expect : globals)
        	{
        		if (!fc.isVariable(section, expect.first))
        		{
        			std::cerr << "Cannot find global var '" << expect.first << "'" << std::endl ;
        			return false ;
        		}

        		std::string expectedValue(expect.second) ;
        		if (sectionEntry.second.find(expect.first) != sectionEntry.second.end())
        		{
        			// overwrite value with section value
        			expectedValue = sectionEntry.second[expect.first] ;
        		}

        		if (expectedValue != fc.value(section, expect.first))
        		{
        			std::cerr << "Global value mismatch var '" << expect.first << "' = '" << expectedValue << "' got '" << fc.value(section, expect.first) << "'" << std::endl ;
        			return false ;
        		}
        	}


    	}
    	return true ;
    }


    bool compareVars(const std::map<std::string, std::string>& expected, const FileConfigBase& fc)
    {
    	std::vector<std::pair<std::string, std::string>> values(fc.values()) ;
    	if (values.size() != expected.size())
    	{
    		std::cerr << "Config size " << values.size() << " different to expected size " << expected.size() << std::endl ;
    		return false ;
    	}

    	for (auto valpair : values)
    	{
    		if (expected.find(valpair.first) == expected.end())
    		{
    			std::cerr << "Unexpected vaue :" << valpair.first << " = " << valpair.second << std::endl ;
    			return false ;
    		}

    		if (valpair.second != expected.at(valpair.first))
    		{
    			std::cerr << "Mismatch for " << valpair.first << " : got " << valpair.second << ", expected " << expected.at(valpair.first) << std::endl ;
    			return false ;
    		}
    	}

    	FileConfigBase fc2(expected) ;
    	if (fc != fc2)
    	{
			std::cerr << "Config mismatch" << std::endl ;
			return false ;
    	}

    	return true ;
    }


};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, create)
{
	FileConfig fc ;
	EXPECT_EQ("", fc.error()) ;
	EXPECT_FALSE(fc.isValid()) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test1)
{
	std::map<std::string, std::string> globalExpected{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
	} ;

	std::set<std::string> expectedSections{"app", "os"} ;

	std::map<std::string, std::map<std::string, std::string>> sectionExpected{
		{"os", {
				{ "fileName", "os.ZCU111-local-123-0.0.tgz" },
				{ "fileVersion", "0.0" },
				{ "path", "os.ZCU111-local-123-0.0.tgz" },
				{ "checksum", "eefbd5954726853b11c9fde5ba94f926" },
		}},
		{"app", {
				{ "fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
				{ "fileVersion", "1.0.0.4" },
				{ "path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
				{ "checksum", "8bea77757de1339db0ea4fb93a63cb17" },
		}},
	};

	FileConfig fc(TESTDIR + "test1.txt") ;
	EXPECT_EQ("", fc.error()) ;
	EXPECT_TRUE(fc.isValid()) ;

	EXPECT_TRUE(compareSections(expectedSections, fc)) ;
	EXPECT_TRUE(compareGlobals(globalExpected, fc)) ;
	EXPECT_TRUE(compareVars(sectionExpected, globalExpected, fc)) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test1Paths)
{
	std::map<std::string, std::string> globalExpected{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	FileConfig fc(TESTDIR + "test1.txt") ;
	EXPECT_EQ("", fc.error()) ;
	EXPECT_TRUE(fc.isValid()) ;

	EXPECT_TRUE(compareGlobals(globalExpected, fc)) ;

}



//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test2)
{
	std::map<std::string, std::string> globalExpected{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
	} ;

	std::set<std::string> expectedSections{"app", "os"} ;

	std::map<std::string, std::map<std::string, std::string>> sectionExpected{
		{"os", {
				{ "fileName", "os.ZCU111-local-123-0.0.tgz" },
				{ "fileVersion", "0.0" },
				{ "path", "os.ZCU111-local-123-0.0.tgz" },
				{ "checksum", "eefbd5954726853b11c9fde5ba94f926" },
				{ "name", "os" },
				{ "local", "os-local" },
		}},
		{"app", {
				{ "fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
				{ "fileVersion", "1.0.0.4" },
				{ "path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
				{ "checksum", "8bea77757de1339db0ea4fb93a63cb17" },
				{ "name", "app" },
				{ "local", "app-local" },
		}},
	};

	FileConfig fc(TESTDIR + "test2.txt") ;
	EXPECT_EQ("", fc.error()) ;
	EXPECT_TRUE(fc.isValid()) ;

	EXPECT_TRUE(compareSections(expectedSections, fc)) ;
	EXPECT_TRUE(compareGlobals(globalExpected, fc)) ;
	EXPECT_TRUE(compareVars(sectionExpected, globalExpected, fc)) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test3Defaults)
{
	std::map<std::string, std::string> defaults{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	std::map<std::string, std::string> expected{
		{ "vendor", "AXIS" },
		{ "code", "AXIS-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	FileConfig fc(TESTDIR + "test3.txt", defaults) ;
	EXPECT_EQ("", fc.error()) ;
	EXPECT_TRUE(fc.isValid()) ;

	fc.show() ;

	EXPECT_TRUE(compareGlobals(expected, fc)) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test4Write)
{
	std::map<std::string, std::string> defaults{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	std::map<std::string, std::string> expected{
		{ "vendor", "AXIS" },
		{ "vendor2", "XILINX" },
		{ "code", "AXIS-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-456-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.666-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
		{ "new/entry", "a value" },
		{ "new/entry2", "another value" },
	} ;

	FileConfigWriter fc(defaults) ;
	Path::remove("./test4.txt") ;
	fc.setPath("./test4.txt") ;
//	(void)fc.error() ;
	EXPECT_EQ("", fc.error()) ;
	EXPECT_TRUE(fc.isValid()) ;



	EXPECT_TRUE(compareGlobals(defaults, fc)) ;

	// Check that we can only modify existing vars
	EXPECT_TRUE(fc.modifyValue("vendor", "AXIS")) ;
	EXPECT_TRUE(fc.modifyValue("code", "AXIS-12345678")) ;
	EXPECT_FALSE(fc.modifyValue("vendor2", "ALTERA")) ;
	EXPECT_TRUE(fc.modifyValue("os/fileName", "os.ZCU111-local-456-0.0.tgz")) ;
	EXPECT_TRUE(fc.modifyValue("app", "fileName", "ZCU111-FBC-ORANRRH-1.0.0.666-240-APP.tgz")) ;

	// Now set a value
	EXPECT_TRUE(fc.setValue("vendor2", "XILINX")) ;
	EXPECT_TRUE(fc.setValue("new/entry", "a value")) ;
	EXPECT_TRUE(fc.setValue("new", "entry2", "another value")) ;

	fc.show() ;


	EXPECT_TRUE(compareGlobals(expected, fc)) ;

	EXPECT_TRUE(fc.save()) ;
	EXPECT_EQ("", fc.error()) ;


	std::cerr << "== READ SAVED CONFIG ==" << std::endl ;
	FileConfig fc2("./test4.txt") ;
	EXPECT_EQ("", fc2.error()) ;
	EXPECT_TRUE(fc2.isValid()) ;
	fc2.show() ;

	EXPECT_TRUE(compareGlobals(expected, fc2)) ;

	std::cerr << "== READ SAVED CONFIG (WRITER) ==" << std::endl ;
	FileConfigWriter fc3("./test4.txt") ;
	EXPECT_EQ("", fc3.error()) ;
	EXPECT_TRUE(fc3.read()) ;
	EXPECT_EQ("", fc3.error()) ;
	EXPECT_TRUE(fc3.isValid()) ;
	fc3.show() ;

	EXPECT_TRUE(compareGlobals(expected, fc3)) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test5WriteNumbers)
{
	std::map<std::string, std::string> defaults{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	std::map<std::string, std::string> expected{
		{ "vendor", "AXIS" },
		{ "vendor2", "XILINX" },
		{ "code", "AXIS-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-456-0.0.tgz" },
		{ "os/fileVersion", "123.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.666-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
		{ "new/entry", "a value" },
		{ "new/entry2", "another value" },
		{ "new/entry3", "567" },
	} ;

	FileConfigWriter fc(defaults) ;
	Path::remove("./test5.txt") ;
	fc.setPath("./test5.txt") ;
	EXPECT_EQ("", fc.error()) ;
	EXPECT_TRUE(fc.isValid()) ;

	EXPECT_TRUE(compareGlobals(defaults, fc)) ;
	EXPECT_EQ(0.0, fc.doubleValue("os/fileVersion")) ;
	EXPECT_EQ(0.0, fc.doubleValue("os", "fileVersion")) ;

	// Check that we can only modify existing vars
	EXPECT_TRUE(fc.modifyValue("vendor", "AXIS")) ;
	EXPECT_TRUE(fc.modifyValue("code", "AXIS-12345678")) ;
	EXPECT_FALSE(fc.modifyValue("vendor2", "ALTERA")) ;
	EXPECT_TRUE(fc.modifyValue("os/fileName", "os.ZCU111-local-456-0.0.tgz")) ;
	EXPECT_TRUE(fc.modifyValue("app", "fileName", "ZCU111-FBC-ORANRRH-1.0.0.666-240-APP.tgz")) ;

	EXPECT_TRUE(fc.modifyValue("os/fileVersion", "1.2")) ;
	EXPECT_EQ(1.2, fc.doubleValue("os/fileVersion")) ;
	EXPECT_EQ(1.2, fc.doubleValue("os", "fileVersion")) ;

	EXPECT_TRUE(fc.modifyValue("os", "fileVersion", "3.4")) ;
	EXPECT_EQ(3.4, fc.doubleValue("os/fileVersion")) ;
	EXPECT_EQ(3.4, fc.doubleValue("os", "fileVersion")) ;

	EXPECT_TRUE(fc.setValue("os/fileVersion", "1.2")) ;
	EXPECT_EQ(1.2, fc.doubleValue("os/fileVersion")) ;
	EXPECT_EQ(1.2, fc.doubleValue("os", "fileVersion")) ;

	EXPECT_TRUE(fc.setValue("os", "fileVersion", "3.4")) ;
	EXPECT_EQ(3.4, fc.doubleValue("os/fileVersion")) ;
	EXPECT_EQ(3.4, fc.doubleValue("os", "fileVersion")) ;

	EXPECT_TRUE(fc.modifyValue("os/fileVersion", "123.0")) ;


	// Now set a value
	EXPECT_TRUE(fc.setValue("vendor2", "XILINX")) ;
	EXPECT_TRUE(fc.setValue("new/entry", "a value")) ;
	EXPECT_TRUE(fc.setValue("new", "entry2", "another value")) ;
	EXPECT_TRUE(fc.setValue("new", "entry3", 567)) ;

	fc.show() ;


	EXPECT_TRUE(compareGlobals(expected, fc)) ;

	EXPECT_TRUE(fc.save()) ;
	EXPECT_EQ("", fc.error()) ;


	std::cerr << "== READ SAVED CONFIG ==" << std::endl ;
	FileConfig fc2("./test5.txt") ;
	EXPECT_EQ("", fc2.error()) ;
	EXPECT_TRUE(fc2.isValid()) ;
	fc2.show() ;

	EXPECT_TRUE(compareGlobals(expected, fc2)) ;


}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test6Compare)
{
	std::map<std::string, std::string> defaults1{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	std::map<std::string, std::string> defaults2{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "DIFFERENT" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	std::map<std::string, std::string> defaults3{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
//		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	std::map<std::string, std::string> defaults4{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
		{ "app/new", "A NEW VARIABLE" },
	} ;


	FileConfig fc1(defaults1) ;
	FileConfigWriter fc1b(defaults1) ;
//	std::shared_ptr<FileConfigWriter> fcp1(std::make_shared<FileConfigWriter>(defaults1)) ;

	FileConfigWriter fc2(defaults2) ;
//	std::shared_ptr<FileConfig> fcp2(std::make_shared<FileConfig>(defaults2)) ;

	FileConfig fc3(defaults3) ;
//	std::shared_ptr<FileConfigWriter> fcp3(std::make_shared<FileConfigWriter>(defaults3)) ;

	FileConfigWriter fc4(defaults4) ;
//	std::shared_ptr<FileConfig> fcp4(std::make_shared<FileConfig>(defaults4)) ;

//	EXPECT_TRUE( fc1 == fcp1 ) ;
//	EXPECT_TRUE( fcp1 == fc1 ) ;
//	EXPECT_FALSE( fc1 != fcp1 ) ;
//	EXPECT_FALSE( fcp1 != fc1 ) ;

	EXPECT_TRUE( fc1 == fc1b ) ;
	EXPECT_TRUE( fc1b == fc1 ) ;
	EXPECT_FALSE( fc1 != fc1b ) ;
	EXPECT_FALSE( fc1b != fc1 ) ;

	EXPECT_TRUE( fc1 != fc2 ) ;
//	EXPECT_TRUE( fcp1 != fcp2 ) ;
	EXPECT_FALSE( fc1 == fc2 ) ;
//	EXPECT_FALSE( fcp1 == fcp2 ) ;

	EXPECT_TRUE( fc1 != fc3 ) ;
//	EXPECT_TRUE( fcp1 != fcp3 ) ;
	EXPECT_FALSE( fc1 == fc3 ) ;
//	EXPECT_FALSE( fcp1 == fcp3 ) ;

	EXPECT_TRUE( fc1 != fc4 ) ;
//	EXPECT_TRUE( fcp1 != fcp4 ) ;
	EXPECT_FALSE( fc1 == fc4 ) ;
//	EXPECT_FALSE( fcp1 == fcp4 ) ;


}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test7Clean)
{
	std::map<std::string, std::string> defaults{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
	} ;

	std::map<std::string, std::string> values{
		{ "vendor", "AXIS" },
		{ "vendor2", "XILINX" },
		{ "code", "AXIS-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-456-0.0.tgz" },
		{ "os/fileVersion", "1.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.666-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.5" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
		{ "new/entry", "a value" },
		{ "new/entry2", "another value" },
	} ;

	std::map<std::string, std::string> expected{
		{ "vendor", "AXIS" },
		{ "code", "AXIS-12345678" },
		{ "os/fileName", "os.ZCU111-local-456-0.0.tgz" },
		{ "os/fileVersion", "1.0" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.666-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.5" },
	} ;

	FileConfigWriter fc(defaults) ;
	std::cerr << "== DEFAULTS ==" << std::endl ;
	fc.show() ;

	// write value changes and new values
	for (auto entry : values)
	{
		fc.setValue(entry.first, entry.second) ;
	}
	std::cerr << "== NEW VALUES ==" << std::endl ;
	fc.show() ;

	// clean out any variables not in defaults list
	EXPECT_TRUE(fc.clean()) ;
	std::cerr << "== CLEANED ==" << std::endl ;
	fc.show() ;

	// check we have the expected set
	EXPECT_TRUE(compareVars(expected, fc)) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test8CopyConstruct)
{
	std::map<std::string, std::string> defaults1{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	FileConfig fc1(defaults1) ;
	FileConfigWriter fc1b(defaults1) ;

	FileConfig fc2(fc1) ;

	FileConfigWriter fc3(fc1) ;
	FileConfigWriter fc3b(fc1b) ;

	EXPECT_TRUE( fc1 == fc1b ) ;
	EXPECT_TRUE( fc1b == fc1 ) ;

	EXPECT_TRUE( fc1 == fc2 ) ;

	EXPECT_TRUE( fc1 == fc3 ) ;
	EXPECT_TRUE( fc1 == fc3b ) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FileConfigTest, test9Assign)
{
	std::map<std::string, std::string> defaults1{
		{ "vendor", "FB" },
		{ "code", "FBOR-12345678" },
		{ "name", "ZCU111-FBC-ORANRRH-1.0.0.4#240" },
		{ "build-Id", "1" },
		{ "os/fileName", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/fileVersion", "0.0" },
		{ "os/path", "os.ZCU111-local-123-0.0.tgz" },
		{ "os/checksum", "eefbd5954726853b11c9fde5ba94f926" },
		{ "app/fileName", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/fileVersion", "1.0.0.4" },
		{ "app/path", "ZCU111-FBC-ORANRRH-1.0.0.4-240-APP.tgz" },
		{ "app/checksum", "8bea77757de1339db0ea4fb93a63cb17" },
	} ;

	FileConfig fc1(defaults1) ;
	FileConfigWriter fc1b(defaults1) ;

	FileConfig fc2 ;
	FileConfigWriter fc3 ;
	FileConfigWriter fc3b ;

	fc2 = fc1 ;

	fc3 = fc1 ;
	fc3b = fc1b ;

	EXPECT_TRUE( fc1 == fc1b ) ;
	EXPECT_TRUE( fc1b == fc1 ) ;

	EXPECT_TRUE( fc1 == fc2 ) ;

	EXPECT_TRUE( fc1 == fc3 ) ;
	EXPECT_TRUE( fc1 == fc3b ) ;

}



//===================================================================================================================
