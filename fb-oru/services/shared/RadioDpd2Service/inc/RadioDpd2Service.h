/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioDpd2Service.h
 * \brief     Service DPD messages for Radio
 *
 *
 * \details
 *
 */


#ifndef RadioDpd2Service_H_
#define RadioDpd2Service_H_

#include <queue>
#include <memory>
#include <vector>
#include <map>
#include <string>

#include "FaultOwner.h"
#include "Dpd2Service.h"


namespace Mplane {

class RadioDpd2Service : public Dpd2Service, public FaultOwner
{
public:

	RadioDpd2Service() ;
	virtual ~RadioDpd2Service() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;


private:
	std::map<std::string, DataVariant> mAlarmAttributes ; //<! Attributes only set when a DPD alarm occurs
} ;

}

#endif /* RadioDpd2Service_H_ */
