/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestSystemClockInput.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTSYSTEMCLOCKINPUT_H_
#define TESTSYSTEMCLOCKINPUT_H_

#include "ISystemClockInput.h"

namespace Mplane {

class TestSystemClockInput : public ISystemClockInput {
public:
	TestSystemClockInput(ISystemClockInput::ClkSource clkInput = ISystemClockInput::CLKIN_10MHZ) ;
	virtual ~TestSystemClockInput() ;

	/**
	 * Select the clock input
	 * @param clkInput
	 * @return true if clock input selected
	 */
	virtual bool setClockInput(ClkSource clkInput) override ;

	/**
	 * Show the current clock input
	 * @return clock input
	 */
	virtual ISystemClockInput::ClkSource getClockInput() override ;

private:
	ISystemClockInput::ClkSource mClkSource ;
} ;

}

#endif /* TESTSYSTEMCLOCKINPUT_H_ */
