/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestTxPclFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "TestVswrMon.h"
#include "IRadio.h"

using namespace Mplane;

std::shared_ptr<IVswr> Mplane::IVswr::getInstance(int index)
{
    static std::vector< std::shared_ptr<IVswr> > vswrList;


    /* Create a PCL instance for every TxPort -if we haven't done so already */
    if( vswrList.empty())
    {
        /* Get the number of TxPorts */
        std::shared_ptr<IRadio> radio( IRadioFactory::getInterface() );
        int numTxPorts = radio->getNumberOfTxPorts();

        for( int i=0; i <  numTxPorts; i++)
        {
            vswrList.push_back ( std::shared_ptr<IVswr>(new TestVswrMon(i)));
        }
    }
    /* return a pointer to the requested PCL instance */
    return vswrList[index];
}
