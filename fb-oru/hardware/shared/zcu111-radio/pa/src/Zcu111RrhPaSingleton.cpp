/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111RrhPaSingleton.cpp
 * \brief     Implementation of the IPa factories for unit tests
 *
 *
 * \details   This file defines the stub implementation of the
 *            factory required for IPa unit tests.
 *
 */
#include <iostream>
#include "CommonPa.h"

using namespace std;
using namespace Mplane;


/**
 * Implement static PA creation factory. This
 * base implementation is for test purposes only as
 * expected to be extended by hardware specific implementation.
 */
static const unsigned MAX_PAS = 4 ;

//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<IPa> > IPaFactory::createPAs( int &maxPorts )
{
	maxPorts = MAX_PAS ;
    return IPaFactory::getPAs() ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<IPa> > IPaFactory::getPAs( )
{
	static std::vector< std::shared_ptr<IPa> > paList;

	// set the number of PA's for the host radio test implementation
    if( paList.empty())
    {
        for( unsigned index = 0; index < MAX_PAS; index++)
        {
        	paList.push_back (  std::shared_ptr<IPa>(new CommonPa( index, "Zcu111Rrh_PA")) );
        }
    }
    return paList;
}

//-------------------------------------------------------------------------------------------------------------
int IPaFactory::getNumberOfPAs()
{
	return MAX_PAS;
}
