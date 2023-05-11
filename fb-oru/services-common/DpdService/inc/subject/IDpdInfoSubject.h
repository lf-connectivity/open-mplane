/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdInfoSubject.h
 * \brief     Virtual interface to Subject for IDpdInfo
 *
 *
 * \details
 *
 */


#ifndef IDPDINFOSUBJECT_H_
#define IDPDINFOSUBJECT_H_

#include <memory>

#include "Observer.hpp"

#include "data/IDpdInfo.h"
#include "client/IDpdInfoClient.h"

namespace Mplane {

class IDpdInfoSubject : public Subject<IDpdInfoClient, const IDpdInfo&>
{
public:
	IDpdInfoSubject() {}
	virtual ~IDpdInfoSubject() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IDpdInfoSubject> getInstance() ;

	/**
	 * Register DPD information client
	 * @param client
	 */
	virtual void attachInfo(IDpdInfoClient& client) =0 ;

} ;

}

#endif /* IDPDINFOSUBJECT_H_ */
