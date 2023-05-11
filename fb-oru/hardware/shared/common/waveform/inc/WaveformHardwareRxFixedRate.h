/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareRxFixedRate.h
 * \brief     Fixed rate RX capture
 *
 *
 * \details
 *
 */


#ifndef WAVEFORMHARDWARERXFIXEDRATE_H_
#define WAVEFORMHARDWARERXFIXEDRATE_H_

#include "WaveformHardware.h"

namespace Mplane {

/*!
 * \class WaveformHardwareRxFixedRate
 */
class WaveformHardwareRxFixedRate : public WaveformHardware {
public:
	explicit WaveformHardwareRxFixedRate(unsigned index, unsigned port) ;
	virtual ~WaveformHardwareRxFixedRate() ;

	/**
	 * Check that the carrier associated with this waveform is set up and valid for this waveform
	 * @param error ref to string that contains the error message on error
	 * @return true if ok
	 */
	virtual bool checkCarrier(std::string& error) const override ;

protected:
    // Get the sample rate for this instance
    virtual unsigned getInstanceSampleRateKsps(ICarrier::Type carrierType) const override ;
} ;

}

#endif /* WAVEFORMHARDWARERXFIXEDRATE_H_ */
