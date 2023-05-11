/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestAldPortSingleton.cpp
 * \brief     Factory implementation to get Ald port implementation for ZCU111 RRH
 *
 *
 * \details   Factory implementation to get Ald port implementation for ZCU111 RRH
 *
 */

#include "CommonAldPort.h"

using namespace Mplane;

/**
 * Implement static AldPort creation factory for the CommonAldPort. This
 * base implementation is for test purposes only as CommonAldPort is also
 * expected to be extended by hardware specific implementation.
 */
static const unsigned MAX_PORTS = 0 ;

//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<IAldPort> > IAldPortFactory::createPorts( int &maxPorts )
{
	maxPorts = MAX_PORTS ;
    return IAldPortFactory::getPorts() ;
}


//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<IAldPort> > IAldPortFactory::getPorts( )
{
	static std::vector< std::shared_ptr<IAldPort> > aldPortList;

	// TODO Port list will be populated once the hardware details are known

	for (int index = 0; index < (int)MAX_PORTS; index++)
	{
		// Create Serial bus

		// Create HDLC

		// Create ALD PORT
	}

    return aldPortList;
}
