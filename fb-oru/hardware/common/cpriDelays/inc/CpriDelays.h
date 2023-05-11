/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriDelays.h
 * \brief     CPRI delay reporting
 *
 *
 */

#ifndef _CPRI_DELAYS_H_
#define _CPRI_DELAYS_H_

#include <memory>

#include "ICpriDelays.h"

namespace Mplane
{

class CpriDelays : public ICpriDelays
{
public:

	// Singleton
	static std::shared_ptr<ICpriDelays> getInterface() ;

	virtual const Delay getCpriDlDelay(unsigned int fibre);
	virtual const Delay getCpriUlDelay(unsigned int fibre);
	virtual const Delay getCpriFrameRxDelay(unsigned int fibre);
	virtual const Delay getCpriFrameTxDelay(unsigned int fibre);
	virtual const Delay getAntUpDelay(unsigned int fibre);
	virtual const Delay getAntDownDelay(unsigned int fibre);

	virtual void setCpriFrameTxDelay(unsigned int fibre, const Delay delay);
	virtual void setSyncOffset(unsigned int fibre, syncOffsetMasterSlave_T masterOrSlave);

	CpriDelays();

	virtual ~CpriDelays() {};

protected:
	/**
	 * Core xilinx delays
	 */
	struct CoreDelays {

		CoreDelays() :
			Tfifo(),
			Ttxfifo(),
			Tbarrel(),
			Tgtprx(),
			Tcorerx(),
			Tgtptx(),
			Tcoretx()
		{}

		Delay Tfifo ;
		Delay Ttxfifo ;
		Delay Tbarrel ;
		Delay Tgtprx ;
		Delay Tcorerx ;
		Delay Tgtptx ;
		Delay Tcoretx ;
	};

	CoreDelays getCoreDelays(unsigned int fibre) ;
	void updateLineRate(unsigned int fibre);

	float getLineRateMHz(void)
	{
		return mLineRateMHz;
	}

private:

	Delay BASIC_FRAME = Delay(1.0, Delay::BF) ;

	/**
	 * T2a calc includes a fixed delay that is cpri core dependent
	 */
	Delay mT2aFixedDelay ;

	/**
	 * Ta3 calc includes a fixed delay that is cpri core dependent
	 */
	Delay mTa3FixedDelay ;

	/**
	 * Line rate of this fibre at the time the delays were calculated
	 */
	float mLineRateMHz ;
};

}
#endif /* _CPRI_DELAYS_H_ */
