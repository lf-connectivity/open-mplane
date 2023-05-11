/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdMajorAlarm.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef SHARED_DPD2SERVICE_INC_DPDMAJORALARM_H_
#define SHARED_DPD2SERVICE_INC_DPDMAJORALARM_H_

#include "Alarm.h"

namespace Mplane {

/*!
 * \class  DpdMajorAlarm
 * \brief
 * \details
 *
 */
class DpdMajorAlarm : public Alarm {
public:
	DpdMajorAlarm(const std::set<std::string>& majorFaultNames) ;
	virtual ~DpdMajorAlarm() ;

} ;

}

#endif /* SHARED_DPD2SERVICE_INC_DPDMAJORALARM_H_ */
