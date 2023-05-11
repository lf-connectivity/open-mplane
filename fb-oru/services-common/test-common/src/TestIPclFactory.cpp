/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIPcl.cpp
 * \brief     Test implementation of the IPcl class
 *
 *
 * \details   This file defines the stub implementation of the Pcl control
 *            interface IPcl class.
 *
 */

#include <memory>
#include "TestIPcl.h"
#include "IRadio.h"


using namespace Mplane;


/******* Base class interface implementation ***********/


std::shared_ptr<IPcl> Mplane::IPcl::getInstance(int index)
{

    static std::vector< std::shared_ptr<IPcl> > pclList;

    /* Get the number of TxPorts */
    std::shared_ptr<IRadio> radio( IRadioFactory::getInterface() );
    int numTxPorts = radio->getNumberOfTxPorts();

    /* Create a PCL instance for every TxPort if we haven't done so already */

    if( pclList.empty())
    {
        for( int i = 0; i <  numTxPorts; i++)
        {
            pclList.push_back ( std::shared_ptr<IPcl>(new TestIPcl));
        }
    }

    /* return a pointer to the requested PCL instance */
    return pclList[index];
}
