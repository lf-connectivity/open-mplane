/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriDelaysFactory.h
 * \brief     CPRI delay factory
 *
 *
 */

#include <memory>

#include "ICpriDelays.h"
#include "CpriDelays.h"

namespace Mplane
{

std::shared_ptr<ICpriDelays> ICpriDelays::getInterface()
{
	static std::shared_ptr<CpriDelays> instance(std::make_shared<CpriDelays>()) ;
	return instance ;
}

}
