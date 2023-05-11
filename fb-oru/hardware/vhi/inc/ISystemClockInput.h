/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISystemClockInput.h
 * \brief     Selects the clock source for the system synth
 *
 *
 * \details
 *
 */


#ifndef ISYSTEMCLOCKINPUT_H_
#define ISYSTEMCLOCKINPUT_H_

#include <string>
#include <memory>

namespace Mplane {

class ISystemClockInput {
public:
	ISystemClockInput() {}
	virtual ~ISystemClockInput() {}

	enum ClkSource {
		CLKIN_NONE,
		CLKIN_INTERNAL,
		CLKIN_10MHZ,
		CLKIN_FIBRE,
		CLKIN_10G_SYNCE,
		CLKIN_25G_SYNCE
	};

	/**
	 * Convert clock source to string
	 * @param clkInput
	 * @return string representation of clock source
	 */
	static std::string clkinToStr(ClkSource clkInput) ;

	/**
	 * Convert clock source string to enum
	 * @param string representation of clock source
	 * @return clock source enum
	 */
	static ClkSource clkStrToEnum(const std::string& clkInput) ;

	/**
	 * Get singleton instance
	 */
	static std::shared_ptr<ISystemClockInput> getInstance() ;

	/**
	 * Select the clock input
	 * @param clkInput
	 * @return true if clock input selected
	 */
	virtual bool setClockInput(ClkSource clkInput) =0 ;

	/**
	 * Show the current clock input
	 * @return clock input
	 */
	virtual ClkSource getClockInput() =0 ;
} ;

}

#endif /* ISYSTEMCLOCKINPUT_H_ */
