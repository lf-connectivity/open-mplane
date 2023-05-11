/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      gentool_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "stringfunc.hpp"
#include "rti_fixture.h"

#include "SettingsNode/EntrySettings.h"
#include "Nodes/DirClass.h"

#include "ISfpData.h"
#include "SfpData.h"
#include <string>
#include "TestBus.h"
#include "CommonCpri.h"
using namespace Mplane ;

#define MAX_PORTS 2

std::shared_ptr<ICpri> Mplane::ICpri::getInterface()
{
    static std::shared_ptr<ICpri> _pTestInstance(new CommonCpri());

    return _pTestInstance;
}

//-------------------------------------------------------------------------------------------------------------
int ISfpData::getPhysicalPortNum(int virtualFibreIndex)
{
	return virtualFibreIndex;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISfpData> ISfpData::getInstance(int port)
{
	std::vector< std::shared_ptr<ISfpData> > sfpList( ISfpData::getSfps() );

	if ((unsigned)port >= sfpList.size())
	{
		throw std::invalid_argument("ISfpData invalid port index");
	}

    return (sfpList[port]) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<ISfpData> > ISfpData::getSfps( void )
{
	static std::vector< std::shared_ptr<ISfpData> > sfpList;

	// Create SFPs for all ports
	if( sfpList.empty())
	{
		for( unsigned index = 0; index < MAX_PORTS; index++)
		{
		    // Create buses for I2C access for A0 and A1 chips
		    std::shared_ptr<II2cBus> i2cA0 = std::make_shared<TestI2cBus>("A0-SFP-" + std::to_string(index), "SFP I2C bus");
		    std::shared_ptr<II2cBus> i2cA1 = std::make_shared<TestI2cBus>("A2-SFP-" + std::to_string(index), "SFP I2C bus");

		    // Create SFP data
			sfpList.push_back ( std::shared_ptr<ISfpData>(std::make_shared<SfpData>(index, i2cA0, i2cA1)) );
		}
	}
	return sfpList;
}

class TestEntrySettings : public EntrySettings
{
public:
	TestEntrySettings(const std::string& pathname, const std::string& callFields,
			const std::string& returnFields, const std::string& comment,
			IRtiMsgParser& msgParser, IRtiSettings& settings) :
		EntrySettings(pathname, callFields, returnFields, comment, msgParser, settings)
	{}

    virtual ~TestEntrySettings(){}

protected:

    /**
     * Execute the function
     * @return reply string
     */
    virtual std::string operator()(const std::string& functionName) override
    {
    	return "" ;
    }

};


class DummyTestHandler2: public EntryFunc
{
public:

	DummyTestHandler2( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
    		IRtiMsgParser& msgParser, IRtiSettings& settings) :
		EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings)
	{}

    virtual ~DummyTestHandler2() {}

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) {

    }

protected:

    virtual std::string operator()(const std::string& functionName) {

    	std::cerr << "DummyTestHandler2 operator() " << functionName << std::endl ;
    	if( functionName == "install")
        {
            install( callVarList, returnVarList  );
            return "" ;
        }
        return "";
    }

	/**
	 * Called with:
	 *   [STRING filename]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void install( DataVariantList *callList, DataVariantList *returnList ) {

	}

};


class DummyTestHandler: public EntryFunc
{
public:

	DummyTestHandler( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
    		IRtiMsgParser& msgParser, IRtiSettings& settings) :
		EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings)
	{}

    virtual ~DummyTestHandler() {}

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) {

    }

protected:

    virtual std::string operator()(const std::string& functionName) {

    	std::cerr << "DummyTestHandler operator() " << functionName << std::endl ;
        if( functionName == "install")
        {
            install( callVarList, returnVarList  );
            return "" ;
        }
        return "";
    }

	/**
	 * Called with:
	 *   [STRING filename]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void install( DataVariantList *callList, DataVariantList *returnList ) {

	}

};


//===================================================================================================================
/*
 * Unit tests
 */


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, DirNode)
{
	std::string result ;

	// Create a directory to store the data in
	EXPECT_TRUE(addDir( new DirClass("/dummy/test", "Testing directory", *this, *this) ) ) ;
	EXPECT_TRUE(add( static_cast<RtiDirEntry *>(new DummyTestHandler("/dummy/test/install",
			"Get and install application",
			"[STRING filename]",
			"",
			*this, *this))
	));
	result = runCmdOk("/dummy/test/install filename=fred") ;

//	std::cerr << "== Inserted initial /dummy/test ====" << std::endl ;
//	mTreeRoot->showDetails() ;

	addDir( new DirClass("/dummy/test", "Overload testing directory", *this, *this) ) ;

//	std::cerr << "== Inserted overload /dummy/test ====" << std::endl ;
//	mTreeRoot->showDetails() ;

	EXPECT_TRUE(add( static_cast<RtiDirEntry *>(new DummyTestHandler("/dummy/test/overload",
			"new overload command",
			"[STRING filename]",
			"",
			*this, *this))
	));

//	std::cerr << "== Inserted overload /dummy/test/overload ====" << std::endl ;
//	mTreeRoot->showDetails() ;


	EXPECT_TRUE(add( static_cast<RtiDirEntry *>(new DummyTestHandler("/dummy/test/.hidden",
			"new hidden command",
			"[STRING filename]",
			"",
			*this, *this))
	));

//	std::cerr << "== Inserted overload /dummy/test/hidden ====" << std::endl ;
//	mTreeRoot->showDetails() ;

//	std::cerr << "== show ====" << std::endl ;
//	mTreeRoot->show() ;

	EXPECT_TRUE(mTreeRoot->findFile("/dummy/test/install") != 0) ;
	EXPECT_TRUE(mTreeRoot->findFile("/dummy/test/overload") != 0) ;
	EXPECT_TRUE(mTreeRoot->findFile("/dummy/test/hidden") != 0) ;


	std::cerr << "== ls /dummy/test/ (hide) ====" << std::endl ;
	DirNode* dummyTest(mTreeRoot->findDir("/dummy/test")) ;
	DirNode::setShowHidden(false) ;
	std::vector< DirNodePtr > contents(dummyTest->getDir()) ;
	for (auto entry : contents)
	{
		std::cout << entry->getFullPath() << std::endl ;
	}

	std::cerr << "== ls /dummy/test/ (show hidden) ====" << std::endl ;
	DirNode::setShowHidden(true) ;
	std::vector< DirNodePtr > contents2(dummyTest->getDir()) ;
	for (auto entry : contents2)
	{
		std::cout << entry->getFullPath() << std::endl ;
	}


	result = runCmdOk("/dummy/test/install filename=fred") ;
	result = runCmdError("/dummy/test/install path=1 filename=fred") ;

	// overload 'install' with a new command
	EXPECT_TRUE(addDir( new DirClass("/dummy/test", "Testing directory", *this, *this) ) ) ;
	EXPECT_TRUE(add( static_cast<RtiDirEntry *>(new DummyTestHandler2("/dummy/test/install",
			"Amended get and install application",
			"INT path,[STRING filename]",
			"",
			*this, *this))
	));
	result = runCmdOk("/dummy/test/install path=1 filename=fred") ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, Navigation)
{
	std::string result ;

	// chdir to testing
	result = runCmdOk("cd tif:testing") ;
	EXPECT_TRUE( result.find("Current directory: /tif:testing") != std::string::npos ) ;

	// chdir to scripts from here
	result = runCmdOk("cd /tif:scripts") ;
	EXPECT_TRUE( result.find("Current directory: /tif:scripts") != std::string::npos ) ;

	// chdir to /
	result = runCmdOk("cd") ;
	EXPECT_TRUE( result.find("Current directory: /") != std::string::npos ) ;

	// error handling
	result = runCmdError("cd xxx") ;

	// non-hidden
	result = runCmdOk("cd /tif:scripts") ;
	result = runCmdOk("cd ..") ;
	result = runCmdOk("cd /tif:scripts") ;
	result = runCmdOk("cd ../tif:testing") ;

	// hidden
	result = runCmdOk("cd /tif:scripts") ;
	result = runCmdError("cd /builtins") ;
	result = runCmdOk("su WangLi5H") ;
	result = runCmdOk("cd /builtins") ;
	result = runCmdOk("cd /") ;
	result = runCmdOk("su exit") ;
	result = runCmdError("cd /builtins") ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, Listing)
{
	std::string result ;

	// Should have the special test device
	result = runCmdOk("ls") ;
	EXPECT_TRUE( result.find("tif:testing/") != std::string::npos ) ;
	EXPECT_TRUE( result.find("tif:settings/") != std::string::npos ) ;
	EXPECT_TRUE( result.find("tif:scripts/") != std::string::npos ) ;

	result = runCmdOk("ls tif:testing") ;
	EXPECT_TRUE( result.find("getVersion()") != std::string::npos ) ;
	EXPECT_TRUE( result.find("read(INT Offset)") != std::string::npos ) ;
//	EXPECT_TRUE( result.find("test10args(INT ARG1,INT aRg2,STRING arg3,STRING ARG4,FLOAT arg5,FLOAT ARG6,HEXINT arg7,HEXINT arg8,INT arg9,INT arg10)") != std::string::npos ) ;
	EXPECT_TRUE( result.find("test10args(INT ARG1,") != std::string::npos ) ;
	EXPECT_TRUE( result.find("write(INT Offset,INT Value)") != std::string::npos ) ;

	result = runCmdOk("ls tif:settings") ;

	result = runCmdOk("ls tif:scripts") ;

	result = runCmdOk("ls /tif:testing") ;
	EXPECT_TRUE( result.find("getVersion()") != std::string::npos ) ;
	EXPECT_TRUE( result.find("read(INT Offset)") != std::string::npos ) ;
//	EXPECT_TRUE( result.find("test10args(INT ARG1,INT aRg2,STRING arg3,STRING ARG4,FLOAT arg5,FLOAT ARG6,HEXINT arg7,HEXINT arg8,INT arg9,INT arg10)") != std::string::npos ) ;
	EXPECT_TRUE( result.find("test10args(INT ARG1,") != std::string::npos ) ;
	EXPECT_TRUE( result.find("write(INT Offset,INT Value)") != std::string::npos ) ;

	result = runCmdError("ls xxx") ;
	EXPECT_TRUE( result.find("Error: Cannot run ls on xxx") != std::string::npos ) ;


}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, Help)
{
	std::string result ;

	result = runCmdOk("help") ;
	EXPECT_TRUE( result.find("Commands:") != std::string::npos ) ;

	result = runCmdOk("help tif:testing") ;
	EXPECT_TRUE( result.find("Commands:") == std::string::npos ) ;
	EXPECT_TRUE( result.find("Available Test Functions:") != std::string::npos ) ;
	EXPECT_TRUE( result.find("getVersion - get fpga version") != std::string::npos ) ;
	EXPECT_TRUE( result.find("call variables:") != std::string::npos ) ;
	EXPECT_TRUE( result.find("No calling args") != std::string::npos ) ;
	EXPECT_TRUE( result.find("return variables:") != std::string::npos ) ;
	EXPECT_TRUE( result.find("ENUM(OK:ERROR) Status,[STRING Info],[STRING Message],INT Version") != std::string::npos ) ;

	result = runCmdOk("help /tif:testing") ;
	EXPECT_TRUE( result.find("Commands:") == std::string::npos ) ;
	EXPECT_TRUE( result.find("Available Test Functions:") != std::string::npos ) ;
	EXPECT_TRUE( result.find("getVersion - get fpga version") != std::string::npos ) ;
	EXPECT_TRUE( result.find("call variables:") != std::string::npos ) ;
	EXPECT_TRUE( result.find("No calling args") != std::string::npos ) ;
	EXPECT_TRUE( result.find("return variables:") != std::string::npos ) ;
	EXPECT_TRUE( result.find("ENUM(OK:ERROR) Status,[STRING Info],[STRING Message],INT Version") != std::string::npos ) ;

/*
   getVersion - get fpga version
        call variables:
            No calling args
        return variables:
            ENUM(OK:ERROR) Status,[STRING Info],[STRING Message],INT Version
    read - read an fpga register
        call variables:
            INT Offset
        return variables:
            ENUM(OK:ERROR) Status,[STRING Info],[STRING Message],INT Value
    test10args - test command with 10 args to check arg parsing
        call variables:
            INT ARG1,INT aRg2,STRING arg3,STRING ARG4,FLOAT arg5,FLOAT ARG6,HEXINT arg7,HEXINT arg8,INT arg9,INT arg10
        return variables:
            ENUM(OK:ERROR) Status,[STRING Info],[STRING Message]
    write - write an fpga register
        call variables:
            INT Offset,INT Value
        return variables:
            ENUM(OK:ERROR) Status,[STRING Info],[STRING Message]

 */

	result = runCmdOk("help tif:settings") ;

	result = runCmdOk("help tif:scripts") ;

	result = runCmdOk("cd /tif:scripts") ;
	result = runCmdOk("help /tif:testing") ;
	EXPECT_TRUE( result.find("Commands:") == std::string::npos ) ;


	result = runCmdError("help xxx") ;
	EXPECT_TRUE( result.find("Error: Cannot run help on xxx") != std::string::npos ) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, NameCase)
{
	std::string result ;

	// chdir to /
	result = runCmdOk("cd") ;

	// Should have the special test device
	result = runCmdOk("ls TIF:Testing") ;
	EXPECT_TRUE( result.find("test10args") != std::string::npos ) ;

	result = runCmdOk("tif:testing.test10args 1 2 3 4 5 6 7 8 9 10") ;
	result = runCmdOk("Tif:Testing.test10args 1 2 3 4 5 6 7 8 9 10") ;
	result = runCmdOk("Tif:Testing.Test10Args 1 2 3 4 5 6 7 8 9 10") ;
	result = runCmdOk("Tif:Testing.Test10Args 1 2 ARG3=3 4 5 6 7 8 9 10") ;
	result = runCmdOk("Tif:Testing.Test10Args 1 2 ARG3=3 4 5 6 7 8 9 ARG10=10") ;


}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, CmdArgsPos)
{
	std::string result ;
	std::string msg ;

	// run write command
	result = runCmdOk("tif:testing.write 1234 5678") ;

	// check special test command
	result = runCmdOk("tif:testing.test10args 1 2 3 4 5 6 7 8 9 10") ;
	result = runCmdOk("tif:testing.test10args 1 2 3 4 5 arg6=6 arg7=7 arg8=8 arg9=9 arg10=10") ;
	result = runCmdOk("tif:testing.test10args 1 2 3 4 5 arg6=6 arg7=7 8 9 10") ;

	// too many args / too few
	result = runCmdError("tif:testing.test10args 1 2 3 4 5 6 7 8") ;
	result = runCmdError("tif:testing.test10args 1 2 3 4 5 6 7 8 9 10 11") ;

	// var/val pair moves us past the end
	result = runCmdError("tif:testing.test10args 1 2 3 4 5 arg9=9 arg10=10 11") ;

	// not all args set
	result = runCmdError("tif:testing.test10args 1 2 3 4 5 arg9=9 arg10=10") ;
	EXPECT_TRUE( toLower(result).find("arg6") != std::string::npos ) << "Missing args" ;
	EXPECT_TRUE( toLower(result).find("arg7") != std::string::npos ) << "Missing args" ;
	EXPECT_TRUE( toLower(result).find("arg8") != std::string::npos ) << "Missing args" ;

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, CmdIntArgs)
{
	std::string result ;
	std::string msg ;

	// run write command
	result = runCmdOk("tif:testing.write 0x1234 0x5678") ;
	EXPECT_TRUE( result.find("Offset=0x1234") != std::string::npos ) << "Offset" ;
	EXPECT_TRUE( result.find("Value=0x5678") != std::string::npos ) << "Value" ;

	result = runCmdOk("tif:testing.write 4660 22136") ;
	EXPECT_TRUE( result.find("Offset=0x1234") != std::string::npos ) << "Offset" ;
	EXPECT_TRUE( result.find("Value=0x5678") != std::string::npos ) << "Value" ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, Settings)
{
	std::string result ;

	result = runCmdOk("ls tif:settings") ;
	EXPECT_TRUE( result.find("showInfo") != std::string::npos ) ;
	EXPECT_TRUE( result.find("showColumn") != std::string::npos ) ;
	EXPECT_TRUE( result.find("scriptsDir") != std::string::npos ) ;

	result = runCmdOk("tif:settings.showInfo true") ;
	result = runCmdOk("tif:settings.showColumn true") ;
	result = runCmdOk("tif:settings.scriptsDir ~/git/builTools") ;

	result = runCmdOk("ls tif:settings") ;
	EXPECT_TRUE( result.find("showInfo=true") != std::string::npos ) ;
	EXPECT_TRUE( result.find("showColumn=true") != std::string::npos ) ;
	EXPECT_TRUE( result.find("scriptsDir=\"~/git/builTools\"") != std::string::npos ) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, ScriptsDir)
{
	std::string result ;

	result = runCmdOk("ls /") ;

	// running in build-local, point to test scripts under gtest
	result = runCmdOk("/tif:settings.scriptsDir ../../../Rti/gtest/scripts") ;
	result = runCmdOk("ls /tif:scripts") ;

	// refresh contents
	result = runCmdOk("cd /tif:scripts") ;
	result = runCmdOk("ls") ;
	result = runCmdOk("ls carrier") ;
	result = runCmdOk("/tif:scripts/simpleTest") ;
	result = runCmdOk("/tif:scripts/anotherTest") ;

}

////-------------------------------------------------------------------------------------------------------------------
//TEST_F(RtiTests, FpgaTestHandler)
//{
//	std::string result ;
//
//	result = runCmdOk("/fpga/write 0x70002 0x1234") ;
//	result = runCmdOk("/fpga/read 0x70002") ;
//}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiTests, SettingsInstance)
{
	TestEntrySettings settings("/settings", "", "", "a comment", *this, *this) ;
	settings.registerMethods(*this, *this) ;
}

//===================================================================================================================
