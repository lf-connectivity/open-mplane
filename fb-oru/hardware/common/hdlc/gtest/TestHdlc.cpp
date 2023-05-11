/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestHdlc.cpp
 * \brief     HDLC test class
 *
 *
 * \details   HDLC test class.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "ISfpData.h"
#include "TestBus.h"
#include "TestHdlc.h"
#include "TestSfpData.h"

using namespace Mplane;

TestHdlc::TestHdlc(std::shared_ptr<IBus> phy):
		Hdlc(phy)
{
};

bool TestHdlc::run_once(void)
{
	return(runEvent());
}
