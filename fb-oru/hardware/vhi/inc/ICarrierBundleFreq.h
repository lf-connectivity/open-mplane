/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierBundleFreq.h
 * \brief     Virtual interface to carrier bundle frequency updates
 *
 *
 * \details   Use this virtual interface to access the appropriate Subject to attach an Observer
 *
 */


#ifndef ICARRIERBUNDLEFREQ_H_
#define ICARRIERBUNDLEFREQ_H_

#include <memory>
#include "Observer.hpp"
#include "IFrequencyChange.h"

namespace Mplane {

class ICarrierBundleFreq {
public:
	ICarrierBundleFreq() {}
	virtual ~ICarrierBundleFreq() {}

	/**
	 * Attach a frequency change observer to the specified RX port
	 * @param port
	 * @param observer
	 */
	virtual void attachRx(unsigned port, Observer<IFrequencyChange>& observer) =0 ;

	/**
	 * Detach a frequency change observer from the specified RX port
	 * @param port
	 * @param observer
	 */
	virtual void detachRx(unsigned port, Observer<IFrequencyChange>& observer) =0 ;

	/**
	 * Attach a frequency change observer to the specified TX port
	 * @param port
	 * @param observer
	 */
	virtual void attachTx(unsigned port, Observer<IFrequencyChange>& observer) =0 ;

	/**
	 * Detach a frequency change observer from the specified RX port
	 * @param port
	 * @param observer
	 */
	virtual void detachTx(unsigned port, Observer<IFrequencyChange>& observer) =0 ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<ICarrierBundleFreq> getInstance() ;

} ;

}

#endif /* ICARRIERBUNDLEFREQ_H_ */
