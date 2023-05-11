/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoRestart.h
 * \brief     LO interface restart when necessary
 *
 *
 * \details   Restarts the LO interface. For some reason the Linux kernel doesn't set up the
 * 			local routing table properly for the LO interface until you restart that interface.
 * 			This class just ensures that the LO is restarted only once
 *
 */


#ifndef ZCU111_NETWORKING_INC_LORESTART_H_
#define ZCU111_NETWORKING_INC_LORESTART_H_

#include <memory>

namespace Mplane {

/*!
 * \class  LoRestart
 * \brief
 * \details
 *
 */
class LoRestart {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<LoRestart> singleton() ;

	LoRestart() ;
	virtual ~LoRestart() ;

	/**
	 * restart the local interface if necessary
	 */
	void restart() ;

private:
	bool mRestarted ;

} ;

}

#endif /* ZCU111_NETWORKING_INC_LORESTART_H_ */
