/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierTests.cpp
 * \brief     Google test main
 *
 *
 * \details   Google test main for common carrier tests
 *
 */
#include "gtest/gtest.h"

#include "ICarrierModel.h"
#include "ICarrierServer.h"
#include "TestCarrier.h"
#include "CommonCarrierModel.h"

using namespace Mplane ;

int main( int argc, char* argv[] )
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

//=============================================================================================================
// SERVER TEST CLASS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierModel> ICarrierModel::createInstance(unsigned maxCarriers)
{
	static std::shared_ptr<ICarrierModel> model( new CommonCarrierModel(maxCarriers) );
	return model ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierModel> ICarrierModel::getInstance()
{
	return ICarrierModel::createInstance(0) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierServer> ICarrierServer::getInstance()
{
    static std::shared_ptr<ICarrierServer> carrierServer(new TestRadioCarrierServer());
    return carrierServer ;
}
