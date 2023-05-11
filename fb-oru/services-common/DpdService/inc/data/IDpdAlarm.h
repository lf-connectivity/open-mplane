/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdAlarm.h
 * \brief     Interface object for data passed to DPD client interested in DPD alarms
 *
 *
 * \details
 *
 */


#ifndef IDPDALARM_H_
#define IDPDALARM_H_

#include "data/IDpdData.h"

namespace Mplane {

class IDpdAlarm : public virtual IDpdData {
public:
	IDpdAlarm() {}
	virtual ~IDpdAlarm() {}

	enum DpdAlarmType : int {
		OK,
		UNKNOWN,
		TIMEALIGNMENT,
		LOWBB,
        MUXFAIL,
        DCUFAIL,
		LOWSRX,
		HIGHSRX,
		YERROR,
		ZERROR,
		DIMENSIONING,
		SOLVER,
		LUTS,
		NORMALISATION,
		RANGE,
		COVERAGE,
		UPDATESTRATEGY,
		EFFICIENCY,
		EXPANSION,
		INSANE,
        SPURIOUS,
        INHIBIT
	} ;

    /* Assign strings to the DpdAlarmType ENUM above. Ensure that the
     * ordering is the same */
	const char* mAlarmNames[22] = { "OK",
									"UNKNOWN",
									"TIMEALIGNMENT",
									"LOWBB",
                                    "MUXFAIL",
                                    "DCUFAIL",
									"LOWSRX",
									"HIGHSRX",
									"YERROR",
									"ZERROR",
									"DIMENSIONING",
									"SOLVER",
									"LUTS",
									"NORMALISATION",
									"RANGE",
									"COVERAGE",
									"UPDATESTRATEGY",
									"EFFICIENCY",
									"EXPANSION",
                                    "INSANE",
                                    "SPURIOUS",
									"INHIBIT" };

	// Get the failure count
	virtual unsigned getFailCount() const =0;

	// Get the alarm type
	virtual DpdAlarmType getAlarmType() const =0 ;

	// Get the Tx Port
	virtual unsigned getTxPort() const =0;

} ;

}

#endif /* IDPDALARM_H_ */
