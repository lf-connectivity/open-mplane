/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareFastVss.h
 * \brief     Fast VSS Message Playback
 *
 *
 * \details
 *
 */


#ifndef WAVEFORMHARDWAREFASTVSS_H_
#define WAVEFORMHARDWAREFASTVSS_H_

#include <memory>
#include "WaveformHardware.h"

namespace Mplane {

/*!
 * \class WaveformHardwareFastVss
 */
class WaveformHardwareFastVss : public WaveformHardware {
public:
	using super = WaveformHardware ;

	explicit WaveformHardwareFastVss(unsigned index, unsigned port) ;
	virtual ~WaveformHardwareFastVss() ;

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

#endif /* WAVEFORMHARDWAREFASTVSS_H_ */
