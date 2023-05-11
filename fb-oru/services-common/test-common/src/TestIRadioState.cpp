/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIRadioState.h
 * \brief     Test Interface for RadioState
 *
 *
 * \details   Defines the expected interface for the radio state
 *
 */

#include "TestIRadioState.h"

using namespace Mplane;

/*! \brief  Stub of the IRadioState Interface
 *
 * This class provides an implementation of the IRadioState interface, for use
 * by unit tests.
 * Users/coders of the unit tests that use an IRadioState interface must ensure
 * that they code the TestIRadioState implementation that meets their unit test
 * cases.
 */

  IRadioState::RadioStatesType Mplane::TestRadioState::getState() const
  {
       return(mRadioState);
  }

  void Mplane::TestRadioState::showRadioState(void)
  {
  }
