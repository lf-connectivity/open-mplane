/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdApp.h
 * \brief     Virtual interface to DPD application
 *
 *
 * \details
 *
 */


#ifndef IDPDAPP_H_
#define IDPDAPP_H_

#include <memory>

namespace Mplane {

class IDpdApp {
public:
	IDpdApp() {}
	virtual ~IDpdApp() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IDpdApp> getInstance() ;

	/**
	 * Start the DPD application running
	 */
	virtual bool start() =0 ;

	/**
	 * Is the DPD application up and running
	 */
	virtual bool isDpdRunning() const =0 ;

	/**
	 * Provide an interface to the C code for it to wait until the capture is completed or timed out
	 * @param timeoutMs
	 * @return true if done; false if timed out
	 */
	virtual bool waitCaptureDone(unsigned timeoutMs) =0 ;

	/**
	 * Provide an interface to the C code for it to set up the SRX frequency for the specified (0 based) TX port
	 * @param tx
	 */
	virtual bool setSrxFreq(unsigned tx) =0 ;

	/**
	 * Is the srx power measurement in progress?
	 */
	virtual bool getMeasurementInProgress() =0;

} ;

}

#endif /* IDPDAPP_H_ */
