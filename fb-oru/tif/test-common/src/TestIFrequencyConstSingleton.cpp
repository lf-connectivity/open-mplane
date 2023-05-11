
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIFrequencyConstSingleton.h
 * \brief     This interface class provides access to the radios constant frequency
 *
 *
 * \details   This interface class provides access to the radios constant frequency
 *
 */

#include <memory>
#include "Frequency.h"

#include "IFrequencyConst.h"
#include "TestIFrequencyConst.h"

using namespace Mplane;

std::shared_ptr<IRxFrequencyConst> IRxFrequencyConstFactory::getInterface()
{
    static std::shared_ptr<IRxFrequencyConst> instance(std::make_shared<TestIRxFrequencyConst>()) ;
    return instance ;
}

std::shared_ptr<ITxFrequencyConst> ITxFrequencyConstFactory::getInterface()
{
    static std::shared_ptr<ITxFrequencyConst> instance(std::make_shared<TestITxFrequencyConst>()) ;
    return instance ;
}
