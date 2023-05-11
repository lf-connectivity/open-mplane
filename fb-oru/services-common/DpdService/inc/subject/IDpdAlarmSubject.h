/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdAlarmSubject.h
 * \brief     Virtual interface to Subject for IDpdAlarm
 *
 *
 * \details
 *
 */


#ifndef IDPDALARMSUBJECT_H_
#define IDPDALARMSUBJECT_H_

#include <memory>

#include "Observer.hpp"

#include "data/IDpdAlarm.h"
#include "client/IDpdAlarmClient.h"

namespace Mplane {

class IDpdAlarmSubject : public Subject<IDpdAlarmClient, const IDpdAlarm&>
{
public:
	IDpdAlarmSubject() {}
	virtual ~IDpdAlarmSubject() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IDpdAlarmSubject> getInstance() ;

	/**
	 * Register DPD alarm client
	 * @param client
	 */
	virtual void attachAlarm(IDpdAlarmClient& client) =0 ;

} ;

}

#endif /* IDPDALARMSUBJECT_H_ */
