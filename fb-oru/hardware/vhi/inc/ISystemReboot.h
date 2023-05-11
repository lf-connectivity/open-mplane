/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISystemReboot.h
 * \brief     Reboots the system
 *
 *
 * \details
 *
 */


#ifndef ISYSTEMREBOOT_H_
#define ISYSTEMREBOOT_H_

#include <string>
#include <memory>

namespace Mplane {

class ISystemReboot {
public:
	ISystemReboot() {}
	virtual ~ISystemReboot() {}

	/*
	 * Get singleton instance
	 */
	static std::shared_ptr<ISystemReboot> getInstance();

	/*
	 * Reboot system now
	 */
	virtual int now() =0;

} ;

}

#endif /* ISYSTEMREBOOT_H_ */
