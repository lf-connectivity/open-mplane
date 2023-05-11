/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiMain.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "Ati.h"
#include "TestInterface.h"

#include <iostream>

using namespace Mplane;
using namespace std;


/*
 * Rti Socket Class
 */
int main( int argc, char* argv[] )
{
    cout << endl << "*** ATI Connection ***" << endl;

    std::shared_ptr< Ati > ati( new Ati() );

    ati->start() ;
    usleep(100*1000)  ;
    while(ati->isRunning()) ;

    return ati->getExitValue() ;
}
