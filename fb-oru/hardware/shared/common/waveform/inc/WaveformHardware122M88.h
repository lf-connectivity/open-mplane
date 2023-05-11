/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardware122M88.h
 * \brief     CPRI playback/capture at 122.88MSPS
 *
 *
 * \details
 *
 */


#ifndef WAVEFORMHARDWARE122M88_H_
#define WAVEFORMHARDWARE122M88_H_

#include "WaveformHardware.h"

namespace Mplane {

class WaveformHardware122M88 : public WaveformHardware {
public:
	using super = WaveformHardware ;

	explicit WaveformHardware122M88(unsigned index, unsigned port) ;
	virtual ~WaveformHardware122M88() ;

	/**
	 * Check that the carrier associated with this waveform is set up and valid for this waveform
	 * @param error ref to string that contains the error message on error
	 * @return true if ok
	 */
	virtual bool checkCarrier(std::string& error) const override ;

	/**
	 * Returns the current sample rate in Ksps
	 */
	virtual unsigned getSampleRateKsps() const override ;

protected:
	// set the playback sample rate regs
	virtual bool setPlaybackSamplerate() override ;

} ;

}

#endif /* WAVEFORMHARDWARE122M88_H_ */
