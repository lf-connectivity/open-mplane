/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Waveform.h
 * \brief     Waveform settings
 *
 *
 * \details   Stores the waveform settings and updates the hardware
 *
 */

#ifndef WAVEFORM_H_
#define WAVEFORM_H_

#include <iostream>
#include <memory>
#include "IWaveform.h"

namespace Mplane {

class Waveform : public IWaveform {
public:
	Waveform() :
		mName(""),
		mType(WAVEFORM_NONE),
		mFilename(""),
		mCarrierSet(false),
		mCarrierIdx(0),
		mAntennaPort(0),
		mDirection(WAVE_TX),
		mSamplerateSet(false),
		mSampleRateKsps(0),
		mEnable(false),
		mTrigger(0),
		mTriggerDelayFrames(0),
		mDepth(0),
		mGain(0.0),
		mGainFilename(""),
		mValueChanged(false),
		mDepthChanged(false),
        mScalingGainSet(false),
        mScalingGain(0),
    	mDecimation(IWaveform::DECIMATE_NONE),
    	mStreamingEnable(false),
    	mAveraging(1),
    	mNco(0.0),
        mCaptureCallback()
	{}
	explicit Waveform(IWaveform& rhs) :
		mName(rhs.getName()),
		mType(rhs.getType()),
		mFilename(rhs.getFilename()),
		mCarrierSet(rhs.isCarrierSet()),
		mCarrierIdx(rhs.getCarrierIdx()),
		mAntennaPort(rhs.getAntennaPort()),
		mDirection(rhs.getDirection()),
		mSamplerateSet(rhs.isSamplerateSet()),
		mSampleRateKsps(rhs.getSampleRateKsps()),
		mEnable(rhs.isEnable()),
		mTrigger(rhs.getTrigger()),
		mTriggerDelayFrames(rhs.getDelayFrames()),
		mDepth(rhs.getDepth()),
		mGain(rhs.getGain()),
		mGainFilename(rhs.getGainFilename()),
		mValueChanged(rhs.isValueChanged()),
		mDepthChanged(rhs.isDepthChanged()),
        mScalingGainSet(rhs.isScalingGainSet()),
        mScalingGain(rhs.getScalingGain()),
    	mDecimation(rhs.getDecimation()),
    	mStreamingEnable(rhs.getStreaming()),
    	mAveraging(rhs.getAveraging()),
    	mNco(rhs.getNco()),
        mCaptureCallback(rhs.getCaptureCallback())
	{}
	virtual ~Waveform() {}

	// Accessors

	virtual unsigned getAntennaPort() const override {
		return mAntennaPort;
	}

	virtual void setAntennaPort(unsigned antennaPort) override {
		mAntennaPort = antennaPort;
		mValueChanged = true ;
	}

	virtual unsigned getCarrierIdx() const override {
		return mCarrierIdx;
	}

	virtual void setCarrierIdx(unsigned carrierIdx) override {
		mCarrierIdx = carrierIdx;
		mCarrierSet = true ;
		mValueChanged = true ;
	}

	virtual WaveDirection getDirection() const override {
		return mDirection;
	}

	virtual void setDirection(WaveDirection direction) override {
		mDirection = direction;
		mValueChanged = true ;
	}

	virtual const std::string& getFilename() const override {
		return mFilename;
	}

	virtual void setFilename(const std::string& filename) override {
		mFilename = filename;
		mValueChanged = true ;
	}

	virtual const std::string& getName() const override {
		return mName;
	}

	virtual void setName(const std::string& name) override {
		mName = name;
		mValueChanged = true ;
	}

	virtual WaveType getType() const override {
		return mType;
	}

	virtual void setType(WaveType type) override {
		mType = type;
		mValueChanged = true ;
	}

	virtual bool isEnable() const override {
		return mEnable;
	}

	virtual void setEnable(bool enable) override {
		mEnable = enable;
		mValueChanged = true ;
	}

	virtual unsigned getDepth() const override {
		return mDepth;
	}

	virtual void setDepth(unsigned depth) override {
		mDepth = depth;
		mValueChanged = true ;
		mDepthChanged = true ;
	}

	virtual float getGain() const override {
		return mGain;
	}

	virtual void setGain(float gain) override {
		mGain = gain;
		mValueChanged = true ;
	}

	virtual const std::string& getGainFilename() const override {
		return mGainFilename;
	}

	virtual void setGainFilename(const std::string& gainFilename) override {
		mGainFilename = gainFilename;
		mValueChanged = true ;
	}

	virtual unsigned getTrigger() const override {
		return mTrigger;
	}

	virtual void setTrigger(unsigned trigger) override {
		mTrigger = trigger;
		mValueChanged = true ;
	}

	virtual unsigned getSampleRateKsps() const override {
		return mSampleRateKsps;
	}

	virtual void setSampleRateKsps(unsigned sampleRateKsps) override {
		mSampleRateKsps = sampleRateKsps;
		mSamplerateSet  = true ;
		mValueChanged   = true ;
	}

	virtual bool isSamplerateSet() const override {
		return mSamplerateSet;
	}

	virtual float getScalingGain() const override {
        return mScalingGain;
    }

	virtual void setScalingGain(float scalingGain) override {
        mScalingGain    = scalingGain;
        mScalingGainSet = true ;
        mValueChanged   = true ;
    }

	virtual bool isScalingGainSet() const override {
        return mScalingGainSet;
    }

	virtual CaptureCallback getCaptureCallback() const override {
        return mCaptureCallback;
    }

	virtual void setCaptureCallback(CaptureCallback callback) override {
    	mCaptureCallback = callback;
    }


	virtual void show(std::ostream& os = std::cout) const override {
		os << "  Waveform " << mName << std::endl ;
#ifdef OFF_TARGET
		os << "  @  " << this << std::endl ;
#endif
		os << "   * Type............: " ;
		switch (mType)
		{
		case IWaveform::WAVEFORM_PLAYBACK:
			os << "PLAYBACK" ;
			break ;
		case IWaveform::WAVEFORM_CAPTURE:
			os << "CAPTURE" ;
			break ;
		case IWaveform::WAVEFORM_NONE:
			os << "(not configured)" ;
			break ;
		}
		os << std::endl ;

		os << "   * Carrier Index...: " ;
		if (mCarrierSet)
			os << mCarrierIdx ;
		else
			os << "UNSET" ;
		os << std::endl ;

		os << "   * Antenna.........: " << mAntennaPort << std::endl ;
		os << "   * Filename........: " << mFilename << std::endl ;
		os << "   * Enable..........: " << mEnable << std::endl ;
		os << "   * Trigger.........: " << mTrigger << std::endl ;
		os << "   * Depth...........: " << mDepth << std::endl ;

		if (mType == IWaveform::WAVEFORM_CAPTURE)
		{
			os << "   * Capture to......: " ;
			if (!mCaptureCallback)
				os << "FILE" ;
			else
				os << "PORT" ;
			os << std::endl ;
		}

		os << "   * Sample Rate.....: " ;
		if (mSamplerateSet)
			os << mSampleRateKsps << " Ksps" ;
		else
			os << "UNSET" ;
		os << std::endl ;

        os << "   * Scaling Gain....: " ;
        if (mScalingGainSet)
        {
            os << mScalingGain << " dB" ;
        }
        else
        {
            os << "UNSET" ;
        }
        os << std::endl ;
	}

	virtual bool isValueChanged() const override {
		return mValueChanged;
	}

	virtual bool isDepthChanged() const override {
		return mDepthChanged;
	}

	virtual void clearValueChanged() override {
		mValueChanged = false;
		mDepthChanged = false;
	}

	virtual bool isCarrierSet() const override {
		return mCarrierSet;
	}

	// wrxcal-specific settings

	virtual void setStreaming(bool streaming) override {
		mValueChanged = true ;
		mStreamingEnable = streaming ;
	}
	virtual bool getStreaming() const override {
		return mStreamingEnable ;
	}
	virtual void setAveraging(unsigned averaging) override {
		mValueChanged = true ;
		mAveraging = averaging ;
	}
	virtual unsigned getAveraging() const override {
		return mAveraging ;
	}
	virtual void setNco(double offset) override {
		mValueChanged = true ;
		mNco = offset ;
	}
	virtual double getNco() const override {
		return mNco ;
	}
	virtual void setDecimation(IWaveform::WrxcalDecimation decimation) override {
		mValueChanged = true ;
		mDecimation = decimation ;
	}
	virtual IWaveform::WrxcalDecimation getDecimation() const override {
		return mDecimation ;
	}



	/**
	 * Calculate the end of a capture using the current settings. Calculated in "trigger" units
	 */
	virtual unsigned getCaptureEnd() const override
	{
		float end = (float)getTrigger() + (((float)getDepth()  / (float)getSampleRateKsps()) * 30720.0) ;
		return static_cast<unsigned>(end) ;
	}

	/**
	 * Calculate the end of a capture using the current settings. Calculated in millisecs
	 */
	virtual unsigned getCaptureEndMs() const override
	{
		// Work out the buffer delay as : (number of samples) / sample rate
		float delay_ms = (float)getDepth() * (float)getAveraging() / (float)getSampleRateKsps() ;

		// add the trigger delay
		delay_ms +=  (float)getDelayedTrigger() / 30720.0 ;

		return static_cast<unsigned>(delay_ms) ;
	}


	/**
	 * Set a number of air frames to delay the trigger by
	 */
	virtual void setDelayFrames(unsigned delayFrames) override
	{
		mTriggerDelayFrames = delayFrames ;
	}

	virtual unsigned getDelayFrames() const override
	{
		return mTriggerDelayFrames ;
	}


	/**
	 * Returns the trigger value including any air frame delays
	 */
	virtual unsigned getDelayedTrigger() const override
	{
		return getTrigger() + ( getDelayFrames() * 307200 ) ;
	}

private:
	// == Parameters specifed by user ==

	// name
	std::string mName ;

	// playback or capture
	WaveType mType ;

	// filename for file transfer
	std::string mFilename ;

	// Characteristics of the carrier this waveform is associated with
	bool mCarrierSet ;
	unsigned mCarrierIdx ;
	unsigned mAntennaPort ;
	WaveDirection mDirection ;

	// Sample rate. Used for capture waveforms (to calc wait time) if carrier not set
	bool mSamplerateSet ;
	unsigned mSampleRateKsps ;

	// is waveform enabled?
	bool mEnable ;

	// trigger setting
	unsigned mTrigger ;

	// delay the trigger by a number of air frames
	unsigned mTriggerDelayFrames ;

	// depth
	unsigned mDepth ;

	// gain value
	// TODO: Change to Power ?
	float mGain ;

	// file of gains
	std::string mGainFilename ;

	// Have any values changed
	bool mValueChanged ;

	// Has depth changed
	bool mDepthChanged ;

	// Scaling value. Used to scale the playback waveform.
	bool  mScalingGainSet;
	float mScalingGain;

	// wrxcal values
	IWaveform::WrxcalDecimation mDecimation ;
	bool mStreamingEnable ;
	unsigned mAveraging ;
	double mNco ;

	// Callback used for capture data (rather than saving to file
	CaptureCallback mCaptureCallback ;

} ;

}

inline std::ostream& operator<<(std::ostream& os, const Mplane::IWaveform& rhs)
{
	rhs.show(os) ;
	return os ;
}

inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Mplane::IWaveform>& rhs)
{
	if (rhs.get() == 0)
	{
		os << "(null)" ;
	}
	else
	{
		os << *rhs ;
	}
	return os ;
}

#endif /* WAVEFORM_H_ */
