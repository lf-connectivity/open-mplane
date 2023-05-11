/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareFullrate.h
 * \brief     Derived waveform class for full rate
 *
 *
 * \details   Handles all of the hardware interfacing (writing to fpga registers) etc for waveforms
 *
 */

#ifndef WAVEFORMHARDWAREFR_H_
#define WAVEFORMHARDWAREFR_H_

#include <memory>
#include "WaveformHardware.h"

namespace Mplane {

/**
 * Waveform hardware class
 */
class WaveformHardwareFullrate : public WaveformHardware {
public:
	using super = WaveformHardware ;

	explicit WaveformHardwareFullrate(unsigned index, unsigned port) ;
	virtual ~WaveformHardwareFullrate() ;

	/**
	 * Init harwdare
	 * @return true if ok
	 */
	virtual bool init(std::string& error) override ;

	/**
	 * Update the hardware using current settings
	 * @return true if ok
	 */
	virtual bool updateHardware(std::string& error) override ;

	/**
	 * Wave hardware is informed of an enable change
	 */
	virtual void enableHasChanged(bool enable) override ;

	/**
	 * Check that the carrier associated with this waveform is set up and valid for this waveform
	 * @param error ref to string that contains the error message on error
	 * @return true if ok
	 */
	virtual bool checkCarrier(std::string& error) const override ;


protected:
	// set the playback sample rate regs
	virtual bool setPlaybackSamplerate() override ;

    // Get the sample rate for this instance
    virtual unsigned getInstanceSampleRateKsps(ICarrier::Type carrierType) const override ;

private:
	bool setMulticastDac(bool enable) ;

} ;

}



inline std::ostream& operator<<(std::ostream& os, const Mplane::WaveformHardwareFullrate& rhs)
{
	rhs.show(os) ;
	return os ;
}

inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Mplane::WaveformHardwareFullrate>& rhs)
{
	rhs->show(os) ;
	return os ;
}


#endif /* WAVEFORMHARDWAREFR_H_ */
