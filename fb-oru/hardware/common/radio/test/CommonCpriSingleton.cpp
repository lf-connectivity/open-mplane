/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpriSingleton.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CommonCpri.h"
#include "ISfpData.h"
#include "SfpData.h"
#include <string>
#include "TestBus.h"


using namespace Mplane ;

#define MAX_PORTS 2

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
/**
 * The following provides the common CPRI interface class.
 */
std::shared_ptr<ICpri> Mplane::ICpri::getInterface()
{
    static std::shared_ptr<ICpri> _pInstance(new CommonCpri());

    return _pInstance;
}

//-------------------------------------------------------------------------------------------------------------
int ISfpData::getPhysicalPortNum(int virtualFibreIndex)
{
	std::shared_ptr<IFpgaFibreRegs> fpga = IFpgaMgr::getIFpgaFibreRegs();

	bool isMapping = fpga->read_virtualToPhysicalEnable(virtualFibreIndex);
	int port = virtualFibreIndex;

	if (isMapping)
	{
		port =  fpga->read_SFP_Number(virtualFibreIndex);
	}

	return port;
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
