/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ina226Rd.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include <memory>
#include <string>
#include <iostream>
#include <fstream>

#include "BusLock.hpp"
#include "Ina226.h"
#include "I2cBusSettings.hpp"
#include "I2cBusLinux.h"
#include "I2cBusLinuxMgr.h"

#include "Ina226Linux.h"
#include "Ina226LinuxMgr.h"

using namespace Mplane ;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

	//---------------------------------------------------------------------------------------------------------
	int help(char* const* argv)
	{
		std::cerr << argv[0] << " [options]" << std::endl ;
		std::cerr << "Options:" << std::endl ;
		std::cerr << " -h                  Help" << std::endl ;
		std::cerr << " -d                  Debug" << std::endl ;
		return 1 ;
	}
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int main(int argc, char* const* argv)
{
	// Process args
    int c;
    bool debug(false) ;
    while ((c = getopt(argc, argv, "hd")) != -1)
    {
		switch (c)
		{
			case 'd':
			debug = true;
			break;

			case 'h':
			help(argv) ;
			return 0 ;
			break ;

			default:
			fprintf(stderr, "Invalid option %c\n", c);
			help(argv) ;
			exit(1);
		}
    }

    (void)debug;

    std::map<std::string, std::string> names{
    	{ "ina226_u59", "VCCINT_IO_BRAM_PS_SDFEC" },
    	{ "ina226_u61", "VCC1V8" },
    	{ "ina226_u63", "VCCINT_RF" },
    	{ "ina226_u66", "MGT1V2" },
    	{ "ina226_u60", "VCC1V2" },
    	{ "ina226_u3",  "DAC_AVTT" },
    	{ "ina226_u64", "VADJ_FMC" },
    	{ "ina226_u65", "MGT1V8" },
    	{ "ina226_u67", "VCCINT" },
    	{ "ina226_u69", "MGTAVCC" },
    	{ "ina226_u71", "DAC_AVCCAUX" },
    	{ "ina226_u73", "ADC_AVCCAUX" },
    	{ "ina226_u77", "ADC_AVCC" },
    	{ "ina226_u79", "DAC_AVCC" },
    } ;

#if 0
    IRPS5401_A 		VCCINT_IO_BRAM_PS_SDFEC	0.85    10	U59	0x41	R394: 0.005
    IRPS5401_B 		VCC1V8					1.8		2	U61	0x42	R388: 0.005
    IRPS5401_C 		VCCINT_RF				0.85	7	U63	0x49	R389: 0.005
    IRPS5401_C 		MGT1V2					1.2		6	U66	0x47	R398: 0.005
    IRPS5401_A		VCC1V2					1.2		6	U60	0x43	R418: 0.005
    IRPS5401_B		DAC_AVTT			2.5/3.0   	0.5	U3	0x4A	R409: 0.005
    IRPS5401_C		VADJ_FMC				1.8		5	U64	0x45	R412: 0.005
    IRPS5401_LDO	MGT1V8					1.8		0.5	U65	0x48	R413: 0.005
    IR38064			VCCINT					0.85    30	U67	0x40	R447: 0.002
    IR38060			MGTAVCC					0.9		3	U69	0x46	R456: 0.002
    IFX1763			DAC_AVCCAUX				1.8		0.5	U71	0x4B	R463: 0.005
    IR38060			ADC_AVCCAUX				1.8		2	U73	0x4D	R471: 0.005
    ISL80112		ADC_AVCC				0.925	2	U77	0x4C	R489: 0.005
    ISL80112		DAC_AVCC				0.925	1	U79	0x4E	R494: 0.005
#endif

    Ina226LinuxMgr mgr(names) ;
    for (auto entry : names)
    {
    	auto ina226(mgr.getMonitor(entry.second)) ;
    	if (!ina226)
    		continue ;

    	std::cerr << "INA226: " << entry.first << " " << entry.second <<
    			" " << ina226->voltage() << "V " <<
				" " << ina226->power() << "W" <<
				" " << ina226->current() << "A" <<
				std::endl ;
    }
    return 0 ;
    /////////////////////

    argc -= optind;
    char* const* ap = argv + optind;

    std::string indexStr ;
    for ( ; ap && *ap; ++ap)
	{
    	if (indexStr.empty())
    	{
    		indexStr = std::string(*ap) ;
    		continue ;
    	}
	}

    unsigned index(0) ;
    if (!indexStr.empty())
        index = stoul(indexStr, nullptr, 0) ;


    // INA226 devices are connected to I2c bus 0, first mux port 0
	std::shared_ptr<II2cBus> i2c(II2cBusMgr::singleton()->deviceBus("/0/mux:0:0", 0x40 + index)) ;
    i2c->setDebug(debug) ;

    // Make the INA226 driver
    std::shared_ptr<Ina226> ina226(std::make_shared<Ina226>(i2c, "VCCINT_IO_BRAM", 10.0, 0.005)) ;
    ina226->initialise() ;

    ina226->show() ;


	return 0 ;
}
