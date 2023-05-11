/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PlaybackWave_unittest.cpp
 * \brief     Google Test of PlaybackWave
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the PlaybackWave class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <fstream>

#include <memory>

#include "IWaveFile.h"
#include "ByteTransfer.hpp"
#include "IKey.h"
#include "IFeature.h"

#include "PlaybackWave.h"

using namespace Mplane;

static const std::string LICENSE("0a00b000c111d111e222f22933383337");

#ifdef _MSC_VER
static const std::string TESTDIR("..\\..\\WaveFile\\gtest\\");
static const std::string PATHSEP("\\");
#else
static const std::string TESTDIR("../../../WaveFile/gtest/");
static const std::string PATHSEP("/");
#endif

//-------------------------------------------------------------------------------------------------------------
// Provide extra access to PlaybackWave internals
class TestPlaybackWave: public PlaybackWave {
public:
	using super = PlaybackWave;
	TestPlaybackWave(std::shared_ptr<IKey> key) :
			PlaybackWave(key) {
	}
	virtual ~TestPlaybackWave() {
	}

#define FILEINFO_TEST_ACCESS(method) \
	std::string method() const { \
		return this->super::method() ; \
	}

	FILEINFO_TEST_ACCESS(getFilepath)FILEINFO_TEST_ACCESS(getFile)
	FILEINFO_TEST_ACCESS(getPath)
	FILEINFO_TEST_ACCESS(getSeparator)
	FILEINFO_TEST_ACCESS(getAirStd)
	FILEINFO_TEST_ACCESS(getBase)
	FILEINFO_TEST_ACCESS(getBw)
	FILEINFO_TEST_ACCESS(getCellId)
	FILEINFO_TEST_ACCESS(getDuplex)
	FILEINFO_TEST_ACCESS(getExtension)
	FILEINFO_TEST_ACCESS(getRate)
	FILEINFO_TEST_ACCESS(getTm)
};

//-------------------------------------------------------------------------------------------------------------
namespace {

#ifndef USE_UNECRYPTED_PLAYBACK

void readFile(const std::string& path, std::vector<uint8_t>& data) {
	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file)
	{
		ASSERT_TRUE(false);
	}
	std::streamsize size(file.tellg());
	file.seekg(0, std::ios::beg);

	data.resize(size);
	if (!file.read((char *) data.data(), size))
	{
		ASSERT_TRUE(false);
	}
}

void testRawFile(const std::string& basename) {
	std::cerr << "testRawFile '" << basename << "'" << std::endl;

	std::string inDir(TESTDIR + "raw");
	std::string outDir(TESTDIR + "output");

	std::shared_ptr<IKey> key(IKey::factory());

	EXPECT_TRUE(key->setLicenseKey(LICENSE));

	std::vector<uint8_t> inData;
	readFile(inDir + PATHSEP + basename, inData);

	// ENCAPSULATE
	std::cerr << "** ENCAPSULATE **" << std::endl;
	PlaybackWave pbWave(key);
	EXPECT_TRUE(
			pbWave.encapsulate(basename, inData, outDir + PATHSEP + basename));
	EXPECT_EQ("", pbWave.getError());
	std::cerr << "** ENCAPSULATE - END **" << std::endl;

#ifdef _MSC_VER
	// create a Windows version for the Linux code to test against
	std::string winDir(TESTDIR + "win-output");
	EXPECT_TRUE(pbWave.encapsulate(basename, inData, winDir + PATHSEP + basename));
	EXPECT_EQ("", pbWave.getError());
#endif

	// DECAPSULATE
	std::cerr << "** DECAPSULATE **" << std::endl;
	EXPECT_TRUE(pbWave.loadEncapsulated(outDir + PATHSEP + basename));
	std::vector<uint8_t> inData2;
	bool eof(false);
//		std::cerr << "  ** LOAD BLOCK **" << std::endl ;
//unsigned block{0} ;
	while (pbWave.loadNextBlock(inData2, eof) && !eof) {
		// do nothing here
//			std::cerr << "  ** LOAD BLOCK " << block << " - DONE **" << std::endl ;
//			++block ;
//			if (!eof)
//				std::cerr << "  ** LOAD BLOCK " << block << " **" << std::endl ;
	}
	std::cerr << "** DECAPSULATE - END **" << std::endl;
	EXPECT_EQ("", pbWave.getError());

	// Compare data
	ASSERT_EQ(inData.size(), inData2.size());
	for (unsigned byte = 0; byte < inData.size(); ++byte) {
		ASSERT_EQ(inData[byte], inData2[byte]);
	}

}

void testEncryptedFile(const std::string& srcdir, const std::string& basename,
		bool expectPass = true) {
	std::cerr << "testEncryptedFile '" << basename << "'" << std::endl;

	std::string inDir(TESTDIR + srcdir);

	std::shared_ptr<IKey> key(IKey::factory());
	EXPECT_TRUE(key->setLicenseKey(LICENSE));
	PlaybackWave pbWave(key);

	// Read file
	pbWave.setFilepath(inDir + PATHSEP + basename);
	bool pass(pbWave.loadEncapsulated());
	EXPECT_EQ(expectPass, pass);
	if (!expectPass)
		return;

	std::vector<uint8_t> inData2;
	bool eof(false);
	while (pbWave.loadNextBlock(inData2, eof) && !eof) {
		// do nothing here
	}
	EXPECT_EQ("", pbWave.getError());

}

void testData(const std::string& basename) {
	std::string outDir(TESTDIR + "output");

	std::shared_ptr<IKey> key(IKey::factory());

	EXPECT_TRUE(key->setLicenseKey(LICENSE));

	std::streamsize size(64);
	std::vector<uint8_t> inData(size);
	for (unsigned byte = 0; byte < inData.size(); ++byte) {
		inData[byte] = (uint8_t) (byte & 0xff);
	}

	std::cout << "Raw Data:" << std::endl;
	ByteTransfer::dump(inData);

	// ENCAPSULATE
	PlaybackWave pbWave(key);
	EXPECT_TRUE(
			pbWave.encapsulate(basename, inData, outDir + PATHSEP + basename));
	EXPECT_EQ("", pbWave.getError());

	std::vector<uint8_t> outData;
	readFile(outDir + PATHSEP + basename, outData);
	std::cout << "Encapsulated FILE:" << std::endl;
	ByteTransfer::dump(outData);

	// DECAPSULATE
	EXPECT_TRUE(pbWave.loadEncapsulated(outDir + PATHSEP + basename));
	std::vector<uint8_t> inData2;
	bool eof(false);
	while (pbWave.loadNextBlock(inData2, eof) && !eof) {
		// do nothing here
	}
	EXPECT_EQ("", pbWave.getError());

	std::cout << "Decapsulated Data:" << std::endl;
	ByteTransfer::dump(inData2);

	// Compare data
	ASSERT_EQ(inData.size(), inData2.size());
	for (unsigned byte = 0; byte < inData.size(); ++byte) {
		ASSERT_EQ(inData[byte], inData2[byte]);
	}
}

void testData2(const std::string& basename) {
	std::string outDir(TESTDIR + "output");

	std::shared_ptr<IKey> key(IKey::factory());

	EXPECT_TRUE(key->setLicenseKey(LICENSE));

	std::streamsize size(8192 * 2);
	std::vector<uint8_t> inData(size);
	for (unsigned byte = 0; byte < inData.size(); ++byte) {
		inData[byte] = 0;
	}

//		std::cout << "Raw Data:" << std::endl;
//		ByteTransfer::dump(inData) ;

// ENCAPSULATE
	PlaybackWave pbWave(key);
	EXPECT_TRUE(
			pbWave.encapsulate(basename, inData, outDir + PATHSEP + basename));
	EXPECT_EQ("", pbWave.getError());

	std::vector<uint8_t> outData;
	readFile(outDir + PATHSEP + basename, outData);
//		std::cout << "Encapsulated FILE:" << std::endl;
//		ByteTransfer::dump(outData) ;

// DECAPSULATE
	EXPECT_TRUE(pbWave.loadEncapsulated(outDir + PATHSEP + basename));
	std::vector<uint8_t> inData2;
	bool eof(false);
	while (pbWave.loadNextBlock(inData2, eof) && !eof) {
		// do nothing here
	}
	EXPECT_EQ("", pbWave.getError());

//		std::cout << "Decapsulated Data:" << std::endl;
//		ByteTransfer::dump(inData2) ;

// Compare data
	ASSERT_EQ(inData.size(), inData2.size());
	for (unsigned byte = 0; byte < inData.size(); ++byte) {
		ASSERT_EQ(inData[byte], inData2[byte]);
	}
}
#endif

void testFileInfo(const std::string& filepath, const std::string& expectPath,
		const std::string& expectFile, const std::string& expectBase,
		const std::string& expectExt, const std::string& expectAirstd = "",
		const std::string& expectDuplex = "", const std::string& expectBw = "",
		const std::string& expectTm = "", const std::string& expectRate = "",
		const std::string& expectCellid = "") {
	std::shared_ptr<IKey> key(IKey::factory());
	EXPECT_TRUE(key->setLicenseKey(LICENSE));
	std::shared_ptr<TestPlaybackWave> pb(
			std::make_shared < TestPlaybackWave > (key));

	pb->setFilepath(filepath);
	EXPECT_EQ(filepath, pb->getFilepath());
	EXPECT_EQ(expectPath, pb->getPath());
	EXPECT_EQ(expectFile, pb->getFile());
	EXPECT_EQ(expectBase, pb->getBase());
	EXPECT_EQ(expectExt, pb->getExtension());

	EXPECT_EQ(expectAirstd, pb->getAirStd());
	EXPECT_EQ(expectDuplex, pb->getDuplex());
	EXPECT_EQ(expectBw, pb->getBw());
	EXPECT_EQ(expectTm, pb->getTm());
	EXPECT_EQ(expectRate, pb->getRate());
	EXPECT_EQ(expectCellid, pb->getCellId());
}

void testFeature(const std::string& filepath, std::shared_ptr<IFeature> feature,
		bool expectedPass) {
	std::shared_ptr<IKey> key(IKey::factory());
	EXPECT_TRUE(key->setLicenseKey(LICENSE));
	std::shared_ptr<PlaybackWave> pb(std::make_shared < PlaybackWave > (key));

	pb->setFilepath(filepath);
	EXPECT_EQ(expectedPass, pb->checkFeatures(feature)) << filepath;
	if (pb->checkFeatures(feature) != expectedPass)
	{
		std::cerr << "ERROR:" << pb->getError() << std::endl ;
		std::cerr << "Features enabled:" << std::endl ;
		feature->show(std::cerr) ;

		// for debug breakpoint
		pb->checkFeatures(feature) ;
	}
}

}

//-------------------------------------------------------------------------------------------------------------
TEST(PlaybackWave, FileInfo)
{
	const ::testing::TestInfo* const test_info =
	::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" << std::endl;
	std::cout << test_info->name() << " - START" << std::endl;

	testFileInfo("/some/path/Data.art", "/some/path", "Data.art", "Data", ".art");

	// Handle filenames of the type:
	//	LTE_FDD-1_10M_TM31_15.36MSPS.art    LTE_TDD38_10M_RXTM11_15.36MSPS.art
	//	LTE_TDD38-1_10M_TM31_15.36MSPS.art  LTE_TDD38_20M_RXTM11_30.72MSPS.art
	//	LTE_TDD38-1_20M_TM31_30.72MSPS.art  LTE_TDD38_5M_RXTM11_7.68MSPS.art
	//	LTE_TDD38-1_5M_TM31_7.68MSPS.art    QMC_cal_tone_1.92MHz_15.36MSPS.art
	//
	// <AIRSTD>_<DUPLEX>_<BW>_<TM>_<RATE>
	//
	// And DUPLEX can be <DUPLEX>-<CELL ID>
	//
	testFileInfo("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.art",
			"/nandflash/tif/playback",
			"LTE_FDD-1_10M_TM31_15.36MSPS.art",
			"LTE_FDD-1_10M_TM31_15.36MSPS",
			".art",

			"LTE",
			"FDD",
			"10M",
			"TM31",
			"15.36MSPS",
			"1"
	);

	testFileInfo("LTE_FDD-1_10M_TM31_15.36MSPS.art",
			"",
			"LTE_FDD-1_10M_TM31_15.36MSPS.art",
			"LTE_FDD-1_10M_TM31_15.36MSPS",
			".art",

			"LTE",
			"FDD",
			"10M",
			"TM31",
			"15.36MSPS",
			"1"
	);

	testFileInfo("\\nandflash\\tif\\playback\\LTE_FDD-1_10M_TM31_15.36MSPS.art",
			"\\nandflash\\tif\\playback",
			"LTE_FDD-1_10M_TM31_15.36MSPS.art",
			"LTE_FDD-1_10M_TM31_15.36MSPS",
			".art",

			"LTE",
			"FDD",
			"10M",
			"TM31",
			"15.36MSPS",
			"1"
	);

	testFileInfo("/nandflash/tif/playback/LTE_TDD38_5M_RXTM11_7.68MSPS.art",
			"/nandflash/tif/playback",
			"LTE_TDD38_5M_RXTM11_7.68MSPS.art",
			"LTE_TDD38_5M_RXTM11_7.68MSPS",
			".art",

			"LTE",
			"TDD38",
			"5M",
			"RXTM11",
			"7.68MSPS",
			""
	);

	testFileInfo("/nandflash/tif/playback/LTE_TDD38-1_10M_TM31_15.36MSPS.art",
			"/nandflash/tif/playback",
			"LTE_TDD38-1_10M_TM31_15.36MSPS.art",
			"LTE_TDD38-1_10M_TM31_15.36MSPS",
			".art",

			"LTE",
			"TDD38",
			"10M",
			"TM31",
			"15.36MSPS",
			"1"
	);

	testFileInfo("/nandflash/tif/playback/QMC_cal_tone_1.92MHz_15.36MSPS.art",
			"/nandflash/tif/playback",
			"QMC_cal_tone_1.92MHz_15.36MSPS.art",
			"QMC_cal_tone_1.92MHz_15.36MSPS",
			".art",

			"QMC",
			"cal",
			"tone",
			"1.92MHz",
			"15.36MSPS",
			""
	);

	// Invalid
	testFileInfo("/nandflash/tif/playback/LTE_TDD38_5M_RXTM11_7.68MSPS_extra.art",
			"/nandflash/tif/playback",
			"LTE_TDD38_5M_RXTM11_7.68MSPS_extra.art",
			"LTE_TDD38_5M_RXTM11_7.68MSPS_extra",
			".art",

			"",
			"",
			"",
			"",
			"",
			""
	);

	testFileInfo("/nandflash/tif/playback/LTE_TDD38_RXTM11_7.68MSPS.art",
			"/nandflash/tif/playback",
			"LTE_TDD38_RXTM11_7.68MSPS.art",
			"LTE_TDD38_RXTM11_7.68MSPS",
			".art",

			"",
			"",
			"",
			"",
			"",
			""
	);

}

//-------------------------------------------------------------------------------------------------------------
TEST(PlaybackWave, Features)
{
	const ::testing::TestInfo* const test_info =
	::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" << std::endl;
	std::cout << test_info->name() << " - START" << std::endl;

	// Start with no features enabled
	std::shared_ptr<IKey> key(IKey::factory());
	EXPECT_TRUE(key->setLicenseKey(LICENSE));
	std::shared_ptr<IFeature> featureNone(IFeature::factory(key));
	std::shared_ptr<IFeature> featureTddTm(IFeature::factory(key));
	std::shared_ptr<IFeature> featureFddTm(IFeature::factory(key));
	std::shared_ptr<IFeature> featureTddFrca(IFeature::factory(key));
	std::shared_ptr<IFeature> featureFddFrca(IFeature::factory(key));
	std::shared_ptr<IFeature> feature(IFeature::factory(key));

	// Handle filenames of the type:
	//	LTE_FDD-1_10M_TM31_15.36MSPS.art    LTE_TDD38_10M_RXTM11_15.36MSPS.art
	//	LTE_TDD38-1_10M_TM31_15.36MSPS.art  LTE_TDD38_20M_RXTM11_30.72MSPS.art
	//	LTE_TDD38-1_20M_TM31_30.72MSPS.art  LTE_TDD38_5M_RXTM11_7.68MSPS.art
	//	LTE_TDD38-1_5M_TM31_7.68MSPS.art    QMC_cal_tone_1.92MHz_15.36MSPS.art
	//
	// <AIRSTD>_<DUPLEX>_<BW>_<TM>_<RATE>
	//
	// And DUPLEX can be <DUPLEX>-<CELL ID>
	//

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	featureNone, false) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureNone, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureNone, false) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	featureNone, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		featureNone, false) ;
	// not valid filename for test model, so should always be valid
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		featureNone, true) ;
	testFeature("/nandflash/tif/playback/ucw_LTE_TDD38-1_5M_TM31.ewf",		featureNone, true) ;

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	feature, false) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, false) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	feature, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		feature, false) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		feature, true) ;


	// Enable LTE_FDD_TM
	std::cerr << "Enable LTE_FDD_TM" << std::endl ;
	EXPECT_TRUE(feature->enableFeature("LTE_FDD_TM"));
	EXPECT_TRUE(featureFddTm->enableFeature("LTE_FDD_TM"));

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	feature, true) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, false) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	feature, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		feature, false) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		feature, true) ;

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	featureFddTm, true) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureFddTm, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureFddTm, false) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	featureFddTm, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		featureFddTm, false) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		featureFddTm, true) ;

	// Enable LTE_TDD_TM
	std::cerr << "Enable LTE_TDD_TM" << std::endl ;
	EXPECT_TRUE(feature->enableFeature("LTE_TDD_TM"));
	EXPECT_TRUE(featureTddTm->enableFeature("LTE_TDD_TM"));

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	feature, true) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, false) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	feature, true) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		feature, true) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		feature, true) ;

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	featureTddTm, false) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureTddTm, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureTddTm, false) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	featureTddTm, true) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		featureTddTm, true) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		featureTddTm, true) ;

	// Enable LTE_TDD_FRCA
	std::cerr << "Enable LTE_TDD_FRCA" << std::endl ;
	EXPECT_TRUE(feature->enableFeature("LTE_TDD_FRCA"));
	EXPECT_TRUE(featureTddFrca->enableFeature("LTE_TDD_FRCA"));

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	feature, true) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, true) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	feature, true) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		feature, true) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		feature, true) ;

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	featureTddFrca, false) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureTddFrca, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureTddFrca, true) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	featureTddFrca, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		featureTddFrca, false) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		featureTddFrca, true) ;

	// Enable LTE_FDD_FRCA
	std::cerr << "Enable LTE_FDD_FRCA" << std::endl ;
	EXPECT_TRUE(feature->enableFeature("LTE_FDD_FRCA"));
	EXPECT_TRUE(featureFddFrca->enableFeature("LTE_FDD_FRCA"));

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	feature, true) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, true) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	feature, true) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	feature, true) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		feature, true) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		feature, true) ;

	testFeature("/nandflash/tif/playback/LTE_FDD-1_10M_TM31_15.36MSPS.ewf", 	featureFddFrca, false) ;
	testFeature("/nandflash/tif/playback/LTE_FDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureFddFrca, true) ;
	testFeature("/nandflash/tif/playback/LTE_TDD-1_5M_FRCA3-4_7.68MSPS.ewf",	featureFddFrca, false) ;
//	testFeature("/nandflash/tif/playback/LTE_TDD38_10M_RXTM11_15.36MSPS.ewf",	featureFddFrca, false) ;
	testFeature("/nandflash/tif/playback/LTE_TDD38-1_5M_TM31_7.68MSPS.ewf",		featureFddFrca, false) ;
	testFeature("/nandflash/tif/playback/LTETDD38-1_5M_TM31_7.68MSPS.ewf",		featureFddFrca, true) ;

}

#ifndef USE_UNECRYPTED_PLAYBACK

//-------------------------------------------------------------------------------------------------------------
TEST(PlaybackWave, Data)
{
	const ::testing::TestInfo* const test_info =
	::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" << std::endl;
	std::cout << test_info->name() << " - START" << std::endl;

	testData("Data.art");
}

//-------------------------------------------------------------------------------------------------------------
TEST(PlaybackWave, DataZero)
{
	const ::testing::TestInfo* const test_info =
	::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" << std::endl;
	std::cout << test_info->name() << " - START" << std::endl;

	testData2("DataZero.art");
}

//-------------------------------------------------------------------------------------------------------------
TEST(PlaybackWave, ReadFile)
{
	const ::testing::TestInfo* const test_info =
	::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" << std::endl;
	std::cout << test_info->name() << " - START" << std::endl;

	testEncryptedFile("encrypted", "Data.art", true);
	testEncryptedFile("encrypted", "DataZero.art", true);
	testEncryptedFile("encrypted", "LTE_FDD-1_10M_TM11_15.36MSPS.art", true);
	testEncryptedFile("encrypted", "LTE_TDD38-1_10M_TM31_15.36MSPS.art", true);

	// copied file should fail SHA1
	testEncryptedFile("encrypted", "Data-copied.art", false);

	// Test files encrypted on Windows
	testEncryptedFile("win-output", "LTE_FDD-1_10M_TM11_15.36MSPS.art", true);
	testEncryptedFile("win-output", "LTE_TDD38-1_10M_TM31_15.36MSPS.art", true);
}

//-------------------------------------------------------------------------------------------------------------
TEST(PlaybackWave, TDD)
{
	const ::testing::TestInfo* const test_info =
	::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" << std::endl;
	std::cout << test_info->name() << " - START" << std::endl;

	testRawFile("LTE_TDD38-1_10M_TM31_15.36MSPS.art");

}

//-------------------------------------------------------------------------------------------------------------
TEST(PlaybackWave, FDD)
{
	const ::testing::TestInfo* const test_info =
	::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" << std::endl;
	std::cout << test_info->name() << " - START" << std::endl;

	testRawFile("LTE_FDD-1_10M_TM11_15.36MSPS.art");

}
#endif
