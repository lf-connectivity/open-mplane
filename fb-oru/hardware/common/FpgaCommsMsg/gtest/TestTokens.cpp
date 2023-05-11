/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestTokens.cpp
 * \brief     Fixed set of tokens for test purposes
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "test_tok.h"
#include "TestTokens.h"

using namespace Mplane;

static const std::map<std::string, unsigned> CommandMap{
	{ "apiVersion", CMD_apiVersion},
	{ "set", CMD_set},
	{ "get", CMD_get},
	{ "restart", CMD_restart},
	{ "search", CMD_search},
	{ "initialSearch", CMD_initialSearch},
	{ "dispersiveSearch", CMD_dispersiveSearch},
	{ "update", CMD_update},
	{ "start", CMD_start},
	{ "stop", CMD_stop},
	{ "startTssi", CMD_startTssi},
	{ "stopTssi", CMD_stopTssi},
	{ "orthogonalise", CMD_orthogonalise},
	{ "pdp", CMD_pdp},
	{ "avgPdp", CMD_avgPdp},
	{ "enableStim", CMD_enableStim},
	{ "disableStim", CMD_disableStim},
	{ "dump", CMD_dump},
	{ "reset", CMD_reset},
	{ "runTest", CMD_runTest},
	{ "frd", CMD_frd},
	{ "fwr", CMD_fwr},
	{ "capture", CMD_capture},
	{ "getCoeffs", CMD_getCoeffs},
	{ "xcorr", CMD_xcorr},
} ;

static const std::map<std::string, unsigned> StateMap{
	{ "response", 200},
	{ "msgId", 201},
	{ "command", 202},
	{ "succeeded", 203},
	{ "buildNo", 204},
	{ "debug", 205},
	{ "logTrace", 206},
	{ "logVerbose", 207},
	{ "logMatlab", 208},
	{ "logConsole", 209},
	{ "uptime", 210},
	{ "t", 211},
	{ "dt", 212},
	{ "block", 213},
	{ "canceller", 214},
	{ "track", 215},
	{ "trackN", 216},
	{ "lockN", 217},
	{ "Ta", 218},
	{ "Tb", 219},
	{ "CNL3", 220},
	{ "CNL5", 221},
	{ "CNL7", 222},
	{ "FOM0", 223},
	{ "FOM1", 224},
	{ "FOM2", 225},
	{ "FOM3", 226},
	{ "pFOM", 227},
	{ "dFOM", 228},
	{ "stimRe", 229},
	{ "stimIm", 230},
	{ "pimGain", 231},
	{ "period", 232},
	{ "pMin", 233},
	{ "pimState", 234},
	{ "adaptCanceller", 235},
	{ "adaptOrthogonalisation", 236},
	{ "branches", 237},
	{ "mask", 238},
	{ "afStart", 239},
	{ "dlBbSrc", 240},
	{ "ulBbSrc", 241},
	{ "ulBbDst", 242},
	{ "srcBw", 243},
	{ "dstBw", 244},
	{ "dl0", 245},
	{ "dl1", 246},
	{ "dl2", 247},
	{ "f0", 248},
	{ "f1", 249},
	{ "f2", 250},
	{ "fd0", 251},
	{ "fd1", 252},
	{ "tssi0", 253},
	{ "tssi1", 254},
	{ "tssi2", 255},
	{ "tssiPim", 256},
	{ "testCase", 257},
	{ "n", 258},
	{ "addr", 259},
	{ "data", 260},
} ;

static const std::map<std::string, unsigned> TokenMap{
	{ "NO", 100},
	{ "YES", 101},
	{ "OFF", 102},
	{ "ON", 103},
	{ "disabled", 104},
	{ "enabled", 105},
	{ "auto", 106},
	{ "NACK", 107},
	{ "ACK", 108},
	{ "none", 109},
	{ "error", 110},
} ;

static const std::map<std::string, FpgaMsgTokens::StateType> StateTypeMap{
	{ "response", {"ENUM(NACK:ACK)", DataVariantType::Enum, "NACK"} },
	{ "msgId", {"INT", DataVariantType::Int, "0"}},
	{ "command", {"INT", DataVariantType::Int, "0"}},
	{ "succeeded", {"ENUM(NO:YES)", DataVariantType::Enum, "NO"}},
	{ "buildNo", {"INT", DataVariantType::Int, "0"}},
	{ "debug", {"ENUM(NO:YES)", DataVariantType::Enum, "NO"}},
	{ "logTrace", {"ENUM(OFF:ON)", DataVariantType::Enum, "OFF"}},
	{ "logVerbose", {"ENUM(OFF:ON)", DataVariantType::Enum, "OFF"}},
	{ "logMatlab", {"ENUM(OFF:ON)", DataVariantType::Enum, "OFF"}},
	{ "logConsole", {"ENUM(OFF:ON)", DataVariantType::Enum, "OFF"}},
	{ "uptime", {"INT", DataVariantType::Int, "0"}},
	{ "t", {"INT", DataVariantType::Int, "0"}},
	{ "dt", {"INT", DataVariantType::Int, "0"}},
	{ "block", {"INT", DataVariantType::Int, "0"}},
	{ "canceller", {"INT", DataVariantType::Int, "0"}},
	{ "track", {"INT", DataVariantType::Int, "0"}},
	{ "trackN", {"INT", DataVariantType::Int, "0"}},
	{ "lockN", {"INT", DataVariantType::Int, "0"}},
	{ "Ta", {"INT", DataVariantType::Int, "0"}},
	{ "Tb", {"INT", DataVariantType::Int, "0"}},
	{ "CNL3", {"INT", DataVariantType::Int, "0"}},
	{ "CNL5", {"INT", DataVariantType::Int, "0"}},
	{ "CNL7", {"INT", DataVariantType::Int, "0"}},
	{ "FOM0", {"INT", DataVariantType::Int, "0"}},
	{ "FOM1", {"INT", DataVariantType::Int, "0"}},
	{ "FOM2", {"INT", DataVariantType::Int, "0"}},
	{ "FOM3", {"INT", DataVariantType::Int, "0"}},
	{ "pFOM", {"INT", DataVariantType::Int, "0"}},
	{ "dFOM", {"INT", DataVariantType::Int, "0"}},
	{ "stimRe", {"INT", DataVariantType::Int, "0"}},
	{ "stimIm", {"INT", DataVariantType::Int, "0"}},
	{ "pimGain", {"INT", DataVariantType::Int, "0"}},
	{ "period", {"INT", DataVariantType::Int, "0"}},
	{ "pMin", {"INT", DataVariantType::Int, "0"}},
	{ "pimState", {"INT", DataVariantType::Int, "0"}},
	{ "adaptCanceller", {"INT", DataVariantType::Int, "0"}},
	{ "adaptOrthogonalisation", {"INT", DataVariantType::Int, "0"}},
	{ "branches", {"INT", DataVariantType::Int, "0"}},
	{ "mask", {"INT", DataVariantType::Int, "0"}},
	{ "afStart", {"INT", DataVariantType::Int, "0"}},
	{ "dlBbSrc", {"INT", DataVariantType::Int, "0"}},
	{ "ulBbSrc", {"INT", DataVariantType::Int, "0"}},
	{ "ulBbDst", {"INT", DataVariantType::Int, "0"}},
	{ "srcBw", {"INT", DataVariantType::Int, "0"}},
	{ "dstBw", {"INT", DataVariantType::Int, "0"}},
	{ "dl0", {"INT", DataVariantType::Int, "0"}},
	{ "dl1", {"INT", DataVariantType::Int, "0"}},
	{ "dl2", {"INT", DataVariantType::Int, "0"}},
	{ "f0", {"INT", DataVariantType::Int, "0"}},
	{ "f1", {"INT", DataVariantType::Int, "0"}},
	{ "f2", {"INT", DataVariantType::Int, "0"}},
	{ "fd0", {"INT", DataVariantType::Int, "0"}},
	{ "fd1", {"INT", DataVariantType::Int, "0"}},
	{ "tssi0", {"INT", DataVariantType::Int, "0"}},
	{ "tssi1", {"INT", DataVariantType::Int, "0"}},
	{ "tssi2", {"INT", DataVariantType::Int, "0"}},
	{ "tssiPim", {"INT", DataVariantType::Int, "0"}},
	{ "testCase", {"INT", DataVariantType::Int, "0"}},
	{ "n", {"INT", DataVariantType::Int, "0"}},
	{ "addr", {"INT", DataVariantType::Int, "0"}},
	{ "data", {"INT", DataVariantType::Int, "0"}},
} ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

std::shared_ptr<IFpgaMsgTokens> TestTokens::getInterface()
{
	static std::shared_ptr<IFpgaMsgTokens> instance(std::make_shared<TestTokens>()) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TestTokens::TestTokens() :
	FpgaMsgTokens(
		API_VERSION,
		CommandMap,
		StateMap,
		TokenMap,
		StateTypeMap
	)
{
}

Mplane::TestTokens::~TestTokens() {
}
