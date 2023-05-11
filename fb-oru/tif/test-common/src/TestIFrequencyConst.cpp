
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIFrequencyConst.h
 * \brief     This interface class provides access to the radios constant frequency
 *
 *
 * \details   This interface class provides access to the radios constant frequency
 *
 */

#include <memory>
#include "Frequency.h"

#include "TestIFrequencyConst.h"

using namespace Mplane;

const Frequency TestITxFrequencyConst::getMinimum() const
{
    return Frequency(700.0);
}

const Frequency TestITxFrequencyConst::getMaximum() const
{
    return Frequency(900.0);
}

const Frequency TestITxFrequencyConst::getCentre() const
{
    return Frequency(800.0);
}

const Frequency TestITxFrequencyConst::getFilterMinimum() const
{
    return Frequency(600.0);
}

const Frequency TestITxFrequencyConst::getFilterMaximum() const
{
    return Frequency(1000.0);
}

const Frequency TestITxFrequencyConst::get3GMinimum() const
{
    return Frequency(700.0);
}

const Frequency TestITxFrequencyConst::get3GMaximum() const
{
    return Frequency(900.0);
}

const Frequency TestITxFrequencyConst::getBandwidth() const
{
    return Frequency(200.0);
}

const Frequency TestITxFrequencyConst::getRaster() const
{
    return Frequency(1.0, Frequency::KHz);
}

const Injection_t TestITxFrequencyConst::getCarrierFlip() const
{
    return HIGHSIDE;
}

const Injection_t TestITxFrequencyConst::getLOInjection() const
{
    return LOWSIDE;
}

const unsigned int TestITxFrequencyConst::getNumberOfRFLO() const
{
    return 1;
}

void TestITxFrequencyConst::show()
{
}

const Frequency TestIRxFrequencyConst::getMinimum() const
{
    return Frequency(700.0);
}

const Frequency TestIRxFrequencyConst::getMaximum() const
{
    return Frequency(900.0);
}

const Frequency TestIRxFrequencyConst::getCentre() const
{
    return Frequency(800.0);
}

const Frequency TestIRxFrequencyConst::getFilterMinimum() const
{
    return Frequency(600.0);
}

const Frequency TestIRxFrequencyConst::getFilterMaximum() const
{
    return Frequency(1000.0);
}

const Frequency TestIRxFrequencyConst::get3GMinimum() const
{
    return Frequency(700.0);
}

const Frequency TestIRxFrequencyConst::get3GMaximum() const
{
    return Frequency(900.0);
}

const Frequency TestIRxFrequencyConst::getBandwidth() const
{
    return Frequency(200.0);
}

const Frequency TestIRxFrequencyConst::getRaster() const
{
    return Frequency(1.0, Frequency::KHz);
}

const Injection_t TestIRxFrequencyConst::getCarrierFlip() const
{
    return HIGHSIDE;
}

const Injection_t TestIRxFrequencyConst::getLOInjection() const
{
    return LOWSIDE;
}

const unsigned int TestIRxFrequencyConst::getNumberOfRFLO() const
{
    return 1;
}

void TestIRxFrequencyConst::show()
{
}
