
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111ORxPortSingleton.cpp
 * \brief     Singleton for ORX port
 *
 *
 * \details   Singleton for ORX port
 *
 */
#include <iostream>

#include "Zcu111RrhSRxPort.h"

using namespace Mplane;

static const unsigned MAX_SRX_PORTS = 2 ;
static const unsigned NUM_TX_PORTS_PER_SRX(2) ;


//-------------------------------------------------------------------------------------------------------------
unsigned int ISRxPortFactory::getNumAssociatedTxPorts( )
{
	return NUM_TX_PORTS_PER_SRX;
}

/**
 * Implement static SRxPort creation factory for the CommonSRxPort.
 */
//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<ISRxPort> > ISRxPortFactory::createPorts( int &maxPorts )
{
	maxPorts = MAX_SRX_PORTS ;
    return ISRxPortFactory::getPorts() ;
}


//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<ISRxPort> > ISRxPortFactory::getPorts( )
{
	static std::vector< std::shared_ptr<ISRxPort> > sRxPortList;

	// set the number of RX ports for the host radio test implementation
    if( sRxPortList.empty())
    {
    	unsigned txPortOffset = 0;
        for( unsigned index = 0; index < MAX_SRX_PORTS; index++)
        {
            sRxPortList.push_back (  std::shared_ptr<ISRxPort>(new Zcu111RrhSRxPort( index, txPortOffset, "Zcu111Rrh_ORX")) );
            txPortOffset += NUM_TX_PORTS_PER_SRX;
        }
    }
    return sRxPortList;
}
