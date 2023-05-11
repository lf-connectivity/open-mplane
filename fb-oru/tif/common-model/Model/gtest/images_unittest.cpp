/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      images_unittest.cpp
 * \brief     Unit tests for the image management TIF class
 *
 *
 * \details   Unit tests for the image management TIF class
 *
 */
#include "gtest/gtest.h"

#include "model_fixture.h"

using namespace Mplane ;
using namespace std ;

//static const std::string TEMP_INSTALL_DIR("/tmp/nandflash") ;

class ImageModelTests : public ModelTests
{
public:
//	using super = ModelTests ;

//    virtual void SetUp()
//    {
//    	this->super::SetUp() ;
//    }

};

//===================================================================================================================
/*
 * Unit tests
 */


//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImageModelTests, ShowTests)
{
    std::string result;

    result = runCmdOk("ls /image");
    result = runCmdOk(".image.show");
    result = runCmdOk(".image.showDetail");
    result = runCmdOk(".image.app.show");
    result = runCmdOk(".image.fpga.show");
    result = runCmdOk(".image.lib.show");
    result = runCmdOk(".image.os.show");
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImageModelTests, Commands)
{
    std::string result;

    // just run the command to ensure there is no segfault
    result = runCmdNoErrorCheck(".image.url");
    result = runCmdNoErrorCheck(".image.bank");
    result = runCmdNoErrorCheck(".image.uboot");

    result = runCmdNoErrorCheck(".image.url http://somedummy");
    result = runCmdNoErrorCheck(".image.uboot no");

    result = runCmdNoErrorCheck(".image.url");
    EXPECT_TRUE(result.find("http://somedummy") != std::string::npos) ;
    result = runCmdNoErrorCheck(".image.uboot");
    EXPECT_TRUE(result.find("no") != std::string::npos) ;

    result = runCmdNoErrorCheck(".image.clean");
    result = runCmdNoErrorCheck(".image.install fred bloggs");
    result = runCmdNoErrorCheck(".image.installFile fred-bloggs.pkg");

    result = runCmdNoErrorCheck(".image.app.clean");
    result = runCmdNoErrorCheck(".image.app.install fred bloggs");
    result = runCmdNoErrorCheck(".image.app.installFile fred-bloggs.pkg");

    result = runCmdNoErrorCheck(".image.lib.clean");
    result = runCmdNoErrorCheck(".image.lib.install fred bloggs");
    result = runCmdNoErrorCheck(".image.lib.installFile fred-bloggs.pkg");

    result = runCmdNoErrorCheck(".image.fpga.clean");
    result = runCmdNoErrorCheck(".image.fpga.installFile fred-bloggs.pkg");

    result = runCmdNoErrorCheck(".image.os.clean");
    result = runCmdNoErrorCheck(".image.os.install fred bloggs");
    result = runCmdNoErrorCheck(".image.os.installFile fred-bloggs.pkg");
}

#if 0
//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImageModelTests, ImgGetCommandTests)
{
    // do the 'img get' command tests
    std::string result;
    std::string cmdInfoString;
    std::string fromUrl;
    std::string fileNameOption;
    std::string bgOption;

    std::shared_ptr<ITifImageCommandHandler> iTich = ITifImageCommandHandler::getInterface();

    /***************************************************
     *  test 1:  the GET GEN command to get a pkg file
     ***************************************************/
    cmdInfoString = ".image.get GEN ";
    fromUrl = "http://10.15.20.11/~pnewborough/build/rse/test_files/gigha/FRGV1-AA_test25589.pkg";
    cmdInfoString += fromUrl;
    cout << "TIF command get test 1: get GEN command : " << cmdInfoString << endl;

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
    while (iTich->isCommandInProgress());  // wait for action to complete

    /***************************************************
     *  test 2:  the GET GEN command to get the pkg.md5 file
     ***************************************************/
    cmdInfoString = ".image.get GEN ";
    fromUrl = "http://10.15.20.11/~pnewborough/build/rse/test_files/gigha/FRGV1-AA_test25589.pkg.md5";
    cmdInfoString += fromUrl;
    cout << "TIF command get test 2: get GEN command : " << cmdInfoString << endl;

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
    while (iTich->isCommandInProgress());  // wait for action to complete

    /***************************************************
     *  test 3:  the GET GEN command to get a pkg file using -f option
     ***************************************************/
    fileNameOption = " -ffileoption1.pkg";  // the destination file name
    cmdInfoString = ".image.get GEN ";
    fromUrl = "http://10.15.20.11/~pnewborough/build/rse/test_files/gigha/FRGV1-AA_test25589.pkg";
    cmdInfoString += fromUrl;
    cmdInfoString += fileNameOption;
    cout << "TIF command get test 3: get GEN command : " << cmdInfoString << endl;

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
    while (iTich->isCommandInProgress());  // wait for action to complete

    /***************************************************
     *  test 4:  the GET GEN command to get a pkg file using -f and -bg options
     ***************************************************/
    bgOption = " -bg";
    fileNameOption = " -ffileoption2.pkg";  // the destination file name
    cmdInfoString = ".image.get GEN ";
    fromUrl = "http://10.15.20.11/~pnewborough/build/rse/test_files/gigha/FRGV1-AA_test25589.pkg";
    cmdInfoString += fromUrl;
    cmdInfoString += fileNameOption;
    cmdInfoString += bgOption;
    cout << "TIF command get test 4: get GEN command : " << cmdInfoString << endl;

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
    while (iTich->isCommandInProgress());  // wait for background action to complete

    /***************************************************
     *  test 5:  the GET APP command to get a tgz file
     ***************************************************/
    cmdInfoString = ".image.get APP ";
    fromUrl = "http://10.15.20.11/~pnewborough/build/rse/test_files/gigha/test-DPD-CDRS-OBSAI-5-LTE-v6lx130t-RRH-Multi-test-25589-NSN-0.0.0.0.tgz";
    cmdInfoString += fromUrl;
    cmdInfoString += bgOption;
    cout << "TIF command get test 5: get APP command : " << cmdInfoString << endl;

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
    while (iTich->isCommandInProgress());  // wait for background action to complete

    /***************************************************
     *  test 6:  the GET FPGA command to get a tgz file
     ***************************************************/
    cmdInfoString = ".image.get FPGA ";
    fromUrl = "http://10.15.20.11/~pnewborough/build/rse/test_files/gigha/test-DPD-FPGA-test-25589-OBSAI-4408-LTE-v6lx130t-RRH-Multi.tgz";
    cmdInfoString += fromUrl;
    cmdInfoString += bgOption;
    cout << "TIF command get test 6: get FPGA command : " << cmdInfoString << endl;

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
    while (iTich->isCommandInProgress());  // wait for background action to complete

    /***************************************************
     *  test 7:  the GET ROS command to get a ROS file
     ***************************************************/
    cmdInfoString = ".image.get ROS ";
    fromUrl = "http://10.15.20.11/~pnewborough/build/rse/test_files/ros1_pImage.DEV-pnewborough";
    cmdInfoString += fromUrl;
    cmdInfoString += bgOption;
    cout << "TIF command get test 7: get ROS command : " << cmdInfoString << endl;

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
    while (iTich->isCommandInProgress());  // wait for background action to complete

    // Now show the status
    result = runCmdNoErrorCheck(".image.show");
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImageModelTests, ImgInstallCommandTests)
{
    // do the 'img install' command tests
    std::string result;
    std::string cmdInfoString = ".image.ins GEN ";
    std::string fileName;

    std::shared_ptr<ITifImageCommandHandler> iTich = ITifImageCommandHandler::getInterface();

    fileName = "FRGV1-AA_test25589.pkg";  // the file name to install
    cmdInfoString += fileName;
    cout << "TIF command install test 1: ins GEN command : " << cmdInfoString << endl;

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
    while (iTich->isCommandInProgress());  // wait for action to complete

    // Now show the status
    result = runCmdNoErrorCheck(".image.show");
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
}
#endif

#if 0
//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImageModelTests, ImgCurrentCommandTests)
{
    // do the 'img current' command tests
    std::string result;
    std::string cmdInfoString = ".image.cur GEN";

    result = runCmdOk(cmdInfoString);
    EXPECT_TRUE( result.find("Status=OK") != std::string::npos );
}
#endif

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ImageModelTests, ImgCleanCommandTest)
{
    std::string result;
    std::string cmdInfoString = ".image.clean";

    result = runCmdOk(cmdInfoString);
}
//===================================================================================================================
