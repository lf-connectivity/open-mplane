/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdMinorAlarm.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef SHARED_DPD2SERVICE_INC_DPDMINORALARM_H_
#define SHARED_DPD2SERVICE_INC_DPDMINORALARM_H_

#include "Alarm.h"

namespace Mplane {

/*!
 * \class  DpdMinorAlarm
 * \brief
 * \details
 *
 */
class DpdMinorAlarm : public Alarm {
public:
	DpdMinorAlarm(const std::set<std::string>& minorFaultNames) ;
	virtual ~DpdMinorAlarm() ;

} ;

}

#endif /* SHARED_DPD2SERVICE_INC_DPDMINORALARM_H_ */
