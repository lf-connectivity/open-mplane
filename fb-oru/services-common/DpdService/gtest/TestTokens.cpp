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

#define API_VERSION 0x12345678

#include "TestTokens.h"

	enum DpdCmdType {
		DPDCMD_APIVERSION = 16384,
		DPDCMD_SET = 16385,
		DPDCMD_GET = 16386,
		DPDCMD_REBOOT = 16387,
		DPDCMD_FRD = 16388,
		DPDCMD_FWR = 16389,
		DPDCMD_PRINTFPGA = 16390,
		DPDCMD_PRINTLUTS = 16391,
		DPDCMD_PRINTCFR = 16392,
		DPDCMD_PRINTMODEL = 16393,
		DPDCMD_TEST = 16394,
		DPDCMD_CAPTURE = 16395,
		DPDCMD_START = 16396,
		DPDCMD_RESTART = 16397,
		DPDCMD_STOP = 16398,
		DPDCMD_RESUME = 16399,
		DPDCMD_RESET = 16400,
		DPDCMD_ABORT = 16401,
	};

using namespace Mplane;

static const std::map<std::string, unsigned> CommandMap{
	{ "apiVersion", DpdCmdType::DPDCMD_APIVERSION},
	{ "set", DpdCmdType::DPDCMD_SET},
	{ "get", DpdCmdType::DPDCMD_GET},
	{ "reboot", DpdCmdType::DPDCMD_REBOOT},
	{ "frd", DpdCmdType::DPDCMD_FRD},
	{ "fwr", DpdCmdType::DPDCMD_FWR},
	{ "printFpga", DpdCmdType::DPDCMD_PRINTFPGA},
	{ "printLuts", DpdCmdType::DPDCMD_PRINTLUTS},
	{ "printCfr", DpdCmdType::DPDCMD_PRINTCFR},
	{ "printModel", DpdCmdType::DPDCMD_PRINTMODEL},
	{ "test", DpdCmdType::DPDCMD_TEST},
	{ "capture", DpdCmdType::DPDCMD_CAPTURE},
	{ "start", DpdCmdType::DPDCMD_START},
	{ "restart", DpdCmdType::DPDCMD_RESTART},
	{ "stop", DpdCmdType::DPDCMD_STOP},
	{ "resume", DpdCmdType::DPDCMD_RESUME},
	{ "reset", DpdCmdType::DPDCMD_RESET},
	{ "abort", DpdCmdType::DPDCMD_ABORT},
} ;

static const std::map<std::string, unsigned> StateMap{
	{ "response", 8192},
	{ "msgId", 8193},
	{ "buildNo", 8194},
	{ "precision", 8195},
	{ "trace", 8196},
	{ "verbose", 8197},
	{ "matlab", 8198},
	{ "console", 8199},
	{ "uptime", 8200},
	{ "t", 8201},
	{ "dt", 8202},
	{ "tx", 8203},
	{ "Q", 8204},
	{ "B", 8205},
	{ "N", 8206},
	{ "G", 8207},
	{ "Gqmc", 8208},
	{ "taps", 8209},
	{ "mags", 8210},
	{ "C1", 8211},
	{ "C2", 8212},
	{ "clip", 8213},
	{ "occupancy", 8214},
	{ "XcfrRef", 8215},
	{ "XrmsRef", 8216},
	{ "XminRef", 8217},
	{ "YrmsRef", 8218},
	{ "srxAtten", 8219},
	{ "fwdGerr", 8220},
	{ "revGerr", 8221},
	{ "srxAgc", 8222},
	{ "state", 8223},
	{ "success", 8224},
	{ "fail", 8225},
	{ "err", 8226},
	{ "eff", 8227},
	{ "Gexp", 8228},
	{ "Glim", 8229},
	{ "evm", 8230},
	{ "lock", 8231},
	{ "Tabs", 8232},
	{ "Tdelta", 8233},
	{ "Gadj", 8234},
	{ "norm", 8235},
	{ "Dlim", 8237},
	{ "ta", 8238},
	{ "dpd", 8239},
	{ "qmc", 8240},
	{ "fdf", 8241},
	{ "converge", 8242},
	{ "bypass", 8243},
	{ "skew", 8244},
	{ "i", 8245},
	{ "addr", 8246},
	{ "data", 8247},
	{ "id", 8248},
	{ "level", 8249},
	{ "src", 8250},
	{ "debug", 8251},
	{ "apiVersion", 8252},
} ;

static const std::map<std::string, unsigned> TokenMap{
	{ "NACK", 8},
	{ "ACK", 9},
	{ "OFF", 10},
	{ "ON", 11},
	{ "WAITMODEL", 12},
	{ "RESET", 13},
	{ "WAITBB", 14},
	{ "TA", 15},
	{ "CONVERGE", 16},
	{ "TRACK", 17},
	{ "NONE", 18},
	{ "OK", 19},
	{ "UNKNOWN", 20},
	{ "TIMEALIGNMENT", 21},
	{ "LOWBB", 22},
	{ "DCUFAIL", 23},
	{ "LOWSRX", 24},
	{ "HIGHSRX", 25},
	{ "YERROR", 26},
	{ "ZERROR", 27},
	{ "DIMENSIONING", 28},
	{ "SOLVER", 29},
	{ "LUTS", 30},
	{ "NORMALISATION", 31},
	{ "RANGE", 32},
	{ "COVERAGE", 33},
	{ "UPDATESTRATEGY", 34},
	{ "EFFICIENCY", 35},
	{ "EXPANSION", 36},
	{ "INSANE", 37},
	{ "SPURIOUS", 38},
	{ "FREEZE", 39},
	{ "DCONLY", 40},
	{ "X", 41},
	{ "Z", 42},
} ;

static const std::map<std::string, FpgaMsgTokens::StateType> StateTypeMap{
	{ "response", { "ENUM(NACK:ACK)", DataVariantType::Enum, "NACK" } },
	{ "msgId", { "INT", DataVariantType::Int, "0" } },
	{ "buildNo", { "INT", DataVariantType::Int, "0" } },
	{ "precision", { "INT", DataVariantType::Int, "0" } },
	{ "trace", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "verbose", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "matlab", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "console", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "uptime", { "INT", DataVariantType::Int, "0" } },
	{ "t", { "INT", DataVariantType::Int, "0" } },
	{ "dt", { "INT", DataVariantType::Int, "0" } },
	{ "tx", { "INT", DataVariantType::Int, "0" } },
	{ "Q", { "INT", DataVariantType::Int, "0" } },
	{ "B", { "INT", DataVariantType::Int, "0" } },
	{ "N", { "INT", DataVariantType::Int, "0" } },
	{ "G", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "Gqmc", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "taps", { "INT", DataVariantType::Int, "0" } },
	{ "mags", { "INT", DataVariantType::Int, "0" } },
	{ "C1", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "C2", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "clip", { "INT", DataVariantType::Int, "0" } },
	{ "occupancy", { "INT", DataVariantType::Int, "0" } },
	{ "XcfrRef", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "XrmsRef", { "INT", DataVariantType::Int, "0" } },
	{ "XminRef", { "INT", DataVariantType::Int, "0" } },
	{ "YrmsRef", { "INT", DataVariantType::Int, "0" } },
	{ "srxAtten", { "INT", DataVariantType::Int, "0" } },
	{ "fwdGerr", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "revGerr", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "srxAgc", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "state", { "ENUM(WAITMODEL:RESET:WAITBB:TA:CONVERGE:TRACK:NONE)", DataVariantType::Enum, "WAITMODEL" } },
	{ "success", { "INT", DataVariantType::Int, "0" } },
	{ "fail", { "INT", DataVariantType::Int, "0" } },
	{ "err", { "ENUM(OK:UNKNOWN:TIMEALIGNMENT:LOWBB:DCUFAIL:LOWSRX:HIGHSRX:YERROR:ZERROR:DIMENSIONING:SOLVER:LUTS:NORMALISATION:RANGE:COVERAGE:UPDATESTRATEGY:EFFICIENCY:EXPANSION:INSANE:SPURIOUS)", DataVariantType::Enum, "OK" } },
	{ "eff", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "Gexp", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "Glim", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "evm", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "lock", { "INT", DataVariantType::Int, "0" } },
	{ "Tabs", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "Tdelta", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "Gadj", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "norm", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "Dlim", { "FLOAT", DataVariantType::Float, "0.0" } },
	{ "ta", { "ENUM(OFF:ON:FREEZE)", DataVariantType::Enum, "OFF" } },
	{ "dpd", { "ENUM(OFF:ON:FREEZE)", DataVariantType::Enum, "OFF" } },
	{ "qmc", { "ENUM(OFF:ON:DCONLY:FREEZE)", DataVariantType::Enum, "OFF" } },
	{ "fdf", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "converge", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "bypass", { "ENUM(OFF:ON:FREEZE)", DataVariantType::Enum, "OFF" } },
	{ "skew", { "INT", DataVariantType::Int, "0" } },
	{ "i", { "INT", DataVariantType::Int, "0" } },
	{ "addr", { "INT", DataVariantType::Int, "0" } },
	{ "data", { "INT", DataVariantType::Int, "0" } },
	{ "id", { "INT", DataVariantType::Int, "0" } },
	{ "level", { "INT", DataVariantType::Int, "0" } },
	{ "src", { "ENUM(X:Z)", DataVariantType::Enum, "X" } },
	{ "debug", { "ENUM(OFF:ON)", DataVariantType::Enum, "OFF" } },
	{ "apiVersion", { "INT", DataVariantType::Int, "0" } },
} ;

static const unsigned apiVersion = 0x344b6936 ;


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
