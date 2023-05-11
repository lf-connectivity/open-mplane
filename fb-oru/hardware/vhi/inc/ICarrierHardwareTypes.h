/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierHardwareTypes.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef ICARRIERHARDWARETYPES_H_
#define ICARRIERHARDWARETYPES_H_


namespace Mplane {

class ICarrierHardwareTypes {
public:
	// Air standard coding
	enum AirstdType {
		AIRSTD_LTE		= 0,
		AIRSTD_WCDMA	= 1,
		AIRSTD_WIMAX	= 2,

		// special internal settings (for waveform, pim etc modules)
		AIRSTD_RXIQ		= 3,
		AIRSTD_CALRXADC	= 4,
		AIRSTD_NONE		= 5,

		AIRSTD_MIN		= AIRSTD_LTE,
		AIRSTD_MAX		= AIRSTD_NONE,
		AIRSTD_UNSET	= 0xFF,
	};

	/**
	 * Convert air std enum into a string
	 * @param status
	 * @return string
	 */
	static std::string airstdToStr(AirstdType airstd) ;

	// Channel bandwidth mappings
	enum ChbwType {
		CHBW_3500		= 0,
		CHBW_5000		= 1,
		CHBW_7000		= 2,
		CHBW_10000		= 3,
		CHBW_1400		= 4,
		CHBW_3000		= 5,
		CHBW_15000		= 6,
		CHBW_20000		= 7,

		CHBW_153600		= 8,

		CHBW_122880		= 9,

		CHBW_200		= 10, //<! NB-IoT

		CHBW_25000      = 16,
		CHBW_30000      = 17,
		CHBW_40000      = 18,
		CHBW_50000      = 19,
		CHBW_60000      = 20,
		CHBW_70000      = 21,
		CHBW_80000      = 22,
		CHBW_90000      = 23,
		CHBW_100000     = 24,

		CHBW_MIN		= CHBW_3500,
		CHBW_MAX		= CHBW_100000,
		CHBW_UNSET		= 0xff,
	};

	/**
	 * Convert chbw enum into a string
	 * @param status
	 * @return string
	 */
	static std::string chbwToStr(ChbwType chbw) ;

	// Clocks per sample = integral + numerator/denominator
	// Values stored are the values to be written i.e. .integral = N-1, .numerator = A, .denominator = B-1
	struct SampleRate {
		int		integral ;
		int		numerator ;
		int		denominator ;

		// This is the target sample rate (used by CPRI)
		int		rate_ksps ;
	};


	enum ScheduleStatus {
		// Scheduled ok
		SCHEDULE_OK,

		// no more fibre iq streams available on this fibre
		SCHEDULE_NO_FIBREIQ,

		// No chains that support this airstd/chbw, or all existing chains already allocated to alternative settings
		SCHEDULE_NO_CHAINS,

		// no more chain iq streams available on this chain
		SCHEDULE_NO_CHAINIQ,

		// Cannot find a chain iq stream that matches the requirements
		SCHEDULE_NO_MATCHING_CHAINIQ,

		// Failed for some unknown reason
		SCHEDULE_FAIL,
	};

	/**
	 * Convert status enum into a failure string
	 * @param status
	 * @return string
	 */
	static std::string scheduleStatusStr(ScheduleStatus status) ;
} ;

}


#endif /* ICARRIERHARDWARETYPES_H_ */
