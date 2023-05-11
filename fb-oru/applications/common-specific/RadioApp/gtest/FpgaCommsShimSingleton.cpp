/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsShimSingleton.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IFpgaCommsShim.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class TestCommsShim : public virtual IFpgaCommsShim {
public:
	TestCommsShim()
	{}

	virtual ~TestCommsShim() {}

};

std::shared_ptr<IFpgaCommsShim> IFpgaCommsShim::getInstance()
{
	static std::shared_ptr<IFpgaCommsShim> instance(std::make_shared<TestCommsShim>()) ;
	return instance ;
}
