/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardware153M6.h
 * \brief     CPRI playback/capture at 153.6MSPS
 *
 *
 * \details
 *
 */


#ifndef WAVEFORMHARDWARE153M6_H_
#define WAVEFORMHARDWARE153M6_H_

#include "WaveformHardware.h"

namespace Mplane {

class WaveformHardware153M6 : public WaveformHardware {
public:
	using super = WaveformHardware ;

	explicit WaveformHardware153M6(unsigned index, unsigned port) ;
	virtual ~WaveformHardware153M6() ;

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

#endif /* WAVEFORMHARDWARE153M6_H_ */
