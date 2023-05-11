/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemReboot.h
 * \brief     Reboots the system
 *
 *
 * \details
 *
 */


#ifndef SYSTEMREBOOT_H_
#define SYSTEMREBOOT_H_

#include "ISystemReboot.h"
#include "Mutex.h"

namespace Mplane {

class SystemReboot : public ISystemReboot {
public:
	explicit SystemReboot() ;
	virtual ~SystemReboot() ;

	/*
	 * Reboot system now
	 */
	virtual int now() override;

private:
	// Protect the reboot
	mutable Mutex mMutex ;

} ;

}

#endif /* SYSTEMREBOOT_H_ */
