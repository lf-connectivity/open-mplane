/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICpriDelays.h
 * \brief     Defines interface for system delay reporting
 *
 *
 */


#ifndef _I_CPRI_DELAYS_H_
#define _I_CPRI_DELAYS_H_

#include <memory>

#include "Delay.h"

namespace Mplane
{

class ICpriDelays
{
public:

	typedef enum
	{
		MASTER = 0,
		SLAVE = 1,
	} syncOffsetMasterSlave_T;

	// Singleton
	static std::shared_ptr<ICpriDelays> getInterface() ;

	virtual const Delay getCpriDlDelay(unsigned int fibre)=0;
	virtual const Delay getCpriUlDelay(unsigned int fibre)=0;
	virtual const Delay getCpriFrameRxDelay(unsigned int fibre)=0;
	virtual const Delay getCpriFrameTxDelay(unsigned int fibre)=0;
	virtual const Delay getAntUpDelay(unsigned int fibre)=0;
	virtual const Delay getAntDownDelay(unsigned int fibre)=0;

	virtual void setCpriFrameTxDelay(unsigned int fibre, const Delay)=0;
	virtual void setSyncOffset(unsigned int fibre, syncOffsetMasterSlave_T masterOrSlave)=0;

	virtual ~ICpriDelays() {}

};

}
#endif /* _I_CPRI_DELAYS_H_ */
