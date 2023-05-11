/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IWaveform.h
 * \brief     Interface to waveform settings
 *
 *
 * \details
 *
 */


#ifndef IWAVEFORM_H_
#define IWAVEFORM_H_

#include <cstdint>
#include <functional>
#include <vector>

namespace Mplane {

class IWaveform {
public:
	IWaveform() {}
	virtual ~IWaveform() {}

	// Waveform type
	enum WaveType {
		WAVEFORM_NONE,
		WAVEFORM_PLAYBACK,
		WAVEFORM_CAPTURE,
	};

	// Direction in terms of this unit
	enum WaveDirection {
		WAVE_TX,
		WAVE_RX,
	};

	/**
	 * Callback for capture data. Data is stored as a vector of bytes which are passed into the callback
	 * (for example to then send out over a tcp port)
	 */
	using CaptureCallback = std::function<void(std::vector<uint8_t>)> ;

	// Accessors

	virtual unsigned getAntennaPort() const =0 ;

	virtual void setAntennaPort(unsigned antennaPort) =0 ;

	virtual unsigned getCarrierIdx() const =0 ;

	virtual void setCarrierIdx(unsigned carrierIdx) =0 ;

	virtual WaveDirection getDirection() const =0 ;

	virtual void setDirection(WaveDirection direction) =0 ;

	virtual const std::string& getFilename() const =0 ;

	virtual void setFilename(const std::string& filename) =0 ;

	virtual const std::string& getName() const =0 ;

	virtual void setName(const std::string& name) =0 ;

	virtual WaveType getType() const =0 ;

	virtual void setType(WaveType type) =0 ;

	virtual bool isEnable() const =0 ;

	virtual void setEnable(bool enable) =0 ;

	virtual unsigned getDepth() const =0 ;

	virtual void setDepth(unsigned depth) =0 ;

	virtual float getGain() const =0 ;

	virtual void setGain(float gain) =0 ;

	virtual const std::string& getGainFilename() const =0 ;

	virtual void setGainFilename(const std::string& gainFilename) =0 ;

	virtual unsigned getTrigger() const =0 ;

	virtual void setTrigger(unsigned trigger) =0 ;

	virtual unsigned getSampleRateKsps() const =0 ;

	virtual void setSampleRateKsps(unsigned sampleRateKsps) =0 ;

	virtual bool isSamplerateSet() const =0 ;

	virtual float getScalingGain() const =0 ;

	virtual void setScalingGain(float scalingGain) =0 ;

	virtual bool isScalingGainSet() const =0 ;

	virtual CaptureCallback getCaptureCallback() const =0 ;

	virtual void setCaptureCallback(CaptureCallback callback) =0 ;

	virtual void show(std::ostream& os = std::cout) const =0 ;

	virtual bool isValueChanged() const =0 ;

	virtual bool isDepthChanged() const =0 ;

	virtual void clearValueChanged() =0 ;

	virtual bool isCarrierSet() const =0 ;

	// wrxcal-specific parameters
	// NOTE: The decimate fpga reg is written with +1 this value
	enum WrxcalDecimation {
		DECIMATE_NONE	= 0,
		DECIMATE_BY_2	= 1,
		DECIMATE_BY_4	= 2,
		DECIMATE_BY_8	= 3,
		DECIMATE_BY_16	= 4,
		DECIMATE_BY_32	= 5,
		DECIMATE_BY_64	= 6,
		DECIMATE_BY_1024= 7,
	};
	virtual void setStreaming(bool streaming) =0 ;
	virtual bool getStreaming() const =0 ;
	virtual void setAveraging(unsigned averaging) =0 ;
	virtual unsigned getAveraging() const =0 ;
	virtual void setNco(double offset) =0 ;
	virtual double getNco() const =0 ;
	virtual void setDecimation(WrxcalDecimation decimation) =0 ;
	virtual WrxcalDecimation getDecimation() const =0 ;

	/**
	 * Calculate the end of a capture using the current settings. Calculated in "trigger" units
	 */
	virtual unsigned getCaptureEnd() const =0 ;

	/**
	 * Calculate the end of a capture using the current settings. Calculated in millisecs
	 */
	virtual unsigned getCaptureEndMs() const =0 ;

	/**
	 * Set a number of air frames to delay the trigger by
	 */
	virtual void setDelayFrames(unsigned delayFrames) =0 ;
	virtual unsigned getDelayFrames() const =0 ;

	/**
	 * Returns the trigger value including any air frame delays
	 */
	virtual unsigned getDelayedTrigger() const =0 ;
} ;

}

#endif /* IWAVEFORM_H_ */
