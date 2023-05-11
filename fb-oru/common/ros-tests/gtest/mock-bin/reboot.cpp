/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      reboot.cpp
 * \brief     Mock simulation of reboot
 *
 *
 * \details   Just creates a file
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


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	std::cerr << "REBOOT MOCK" << std::endl ;
	::system("touch ./reboot-flag.txt") ;
	return 0 ;
}

