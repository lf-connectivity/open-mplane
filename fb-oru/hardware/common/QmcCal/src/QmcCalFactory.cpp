/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcCalFactory.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ITxPort.h"
#include "QmcCal.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<IQmcCal> > IQmcCalFactory::getList()
{
	static std::vector< std::shared_ptr<IQmcCal> > list;

    if( list.empty())
    {
    	std::vector< std::shared_ptr<ITxPort>> txports(ITxPortFactory::getPorts()) ;

        for( unsigned index = 0; index < txports.size(); index++)
        {
            list.push_back ( std::make_shared<QmcCal>(index) );
        }
    }
    return list;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IQmcCal> IQmcCalFactory::get(unsigned index)
{
	std::vector< std::shared_ptr<IQmcCal> > list(IQmcCalFactory::getList()) ;
	if (index >= list.size())
		return std::shared_ptr<IQmcCal>() ;

	return list[index] ;
}
