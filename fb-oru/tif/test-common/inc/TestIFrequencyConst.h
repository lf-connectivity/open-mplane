#ifndef _MPLANE_TEST_IFREQUENCYCONSTANTS_H_
#define _MPLANE_TEST_IFREQUENCYCONSTANTS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIFrequencyConstants.h
 * \brief     This interface class provides access to the radios constant frequency
 *
 *
 * \details   This interface class provides access to the radios constant frequency
 *
 */

#include <memory>
#include "Frequency.h"

#include "IFrequencyConst.h"

namespace Mplane
{

/**
 * Interface provides a minimum set of data relating to the constant frequency
 * data associated with the radios Rx port.
 */
class TestIRxFrequencyConst : virtual public IRxFrequencyConst
{
public:
    TestIRxFrequencyConst() {}

    virtual ~TestIRxFrequencyConst() {}

    const Frequency getMinimum() const;

    const Frequency getMaximum() const;

    const Frequency getCentre() const;

    const Frequency getFilterMinimum() const;

    const Frequency getFilterMaximum() const;

    const Frequency get3GMinimum() const;

    const Frequency get3GMaximum() const;

    const Frequency getBandwidth() const;

    const Frequency getRaster() const;

    const Injection_t getCarrierFlip() const;

    const Injection_t getLOInjection() const;

    const unsigned int getNumberOfRFLO() const;

    void show();

};

/**
 * Interface provides a minimum set of data relating to the constant frequency
 * data associated with the radios Tx port.
 */
class TestITxFrequencyConst : virtual public ITxFrequencyConst
{
public:
    TestITxFrequencyConst() {}

    virtual ~TestITxFrequencyConst() {}

    const Frequency getMinimum() const;

    const Frequency getMaximum() const;

    const Frequency getCentre() const;

    const Frequency getFilterMinimum() const;

    const Frequency getFilterMaximum() const;

    const Frequency get3GMinimum() const;

    const Frequency get3GMaximum() const;

    const Frequency getBandwidth() const;

    const Frequency getRaster() const;

    const Injection_t getCarrierFlip() const;

    const Injection_t getLOInjection() const;

    const unsigned int getNumberOfRFLO() const;

    void show();

};

}

#endif /* _MPLANE_IFREQUENCYCONSTANTS_H_ */
