/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhFaultsSingleton.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <memory>

#include "ICommonRadioFaults.h"

#include "RrhFaults.h"

using namespace Mplane;

std::shared_ptr<RrhFaults> Mplane::RrhFaults::getInstance()
{
    static std::shared_ptr<RrhFaults> instance(std::make_shared <RrhFaults>()) ;
    return instance ;
}


std::shared_ptr<ICommonRadioFaults> ICommonRadioFaults::getInstance(void)
{
    return Mplane::RrhFaults::getInstance();
}
