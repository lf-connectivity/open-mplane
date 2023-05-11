/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareRxAdc.h
 * \brief     Interfaces with the hardware to set up the waveform block specifically for Rx ADC
 *
 *
 * \details   Handles all of the hardware interfacing (writing to fpga registers) etc for waveforms
 *
 */

#ifndef WAVEFORMHARDWARERXADC_H_
#define WAVEFORMHARDWARERXADC_H_

#include "WaveformHardware.h"

namespace Mplane {

/**
 * Waveform hardware class
 */
class WaveformHardwareRxAdc : public WaveformHardware {
public:
	using super = WaveformHardware ;

	explicit WaveformHardwareRxAdc(unsigned index, unsigned port) ;
	virtual ~WaveformHardwareRxAdc() ;

	/**
	 * Init harwdare
	 * @return true if ok
	 */
	virtual bool init(std::string& error) override ;

	/**
	 * Update the settings
	 * @return true if ok
	 */
	virtual bool updateSettings(
		std::shared_ptr<IWaveform> waveform,
		std::shared_ptr<IWaveformMem> waveformMem,
		std::string& error) override ;

	/**
	 * Update the hardware using current settings
	 * @return true if ok
	 */
	virtual bool updateHardware(std::string& error) override ;

	/**
	 * Is there a capture write error for this waveform
	 * @return true on error
	 */
	virtual bool isCaptureWriteError() const override ;

	/**
	 * Is the capture complete for this waveform
	 * @return true on complete
	 */
	virtual bool isCaptureDone() const override ;

	/**
	 * Is playback enabled for this waveform
	 * @return true if enabled
	 */
	virtual bool isPlaybackEnabled() const override ;

	/**
	 * Was there a playback read error on this waveform
	 * @return true on error
	 */
	virtual bool isPlaybackReadError() const override ;

	/**
	 * Prepare for writing - must be called once before starting to write to memory (resets internal counters to start of
	 * memory)
	 */
	virtual void writeMemoryStart() override ;

	/**
	 * Write buffer to next address
	 * @param buffer
	 * @return true if write ok
	 */
	virtual bool writeMemory(const short* buffer, unsigned bufferSize, bool& endOfData, std::string& error)override ;

	/**
	 * Prepare for reading - must be called once before starting to read from memory (resets internal counters to start of
	 * memory)
	 */
	virtual void readMemoryStart() override ;

	/**
	 * Write buffer to next address
	 * @param buffer
	 * @param maxReadSize	Maximum amount to read in one go
	 * @return true if read ok
	 */
	virtual bool readMemory( short* buffer, unsigned& bufferSize, unsigned maxReadSize, bool& endOfFile, std::string& error);

	/**
	 * Check that the carrier associated with this waveform is set up and valid for this waveform
	 * @param error ref to string that contains the error message on error
	 * @return true if ok
	 */
	virtual bool checkCarrier(std::string& error) const override ;

	/**
	 * Stop playback/capture
	 * @param error
	 * @return true if ok
	 */
	virtual bool shutdown(std::string& error) override ;

	/**
	 * Does this Waveform Hardware require memory allocated in WaveformMem
	 * @return true if requires memory to be allocated; false otherwise
	 */
	virtual bool requiresWaveformMem(void) const override ;

	/**
	 * Returns the maximum depth any waveform can be set to - used to check parameters
	 */
	virtual unsigned getMaxDepth(void) const override ;

	/**
	 * Do any necessary initialisation ready for capture
	 */
	virtual void captureInit(void) override ;

	/**
	 * Given the depth setting, returns the total number of bytes in the waveform data
	 */
	virtual unsigned getNumBytes(void) const override ;

    /**
     * Does this waveform module use the FPGA bus? If so then the bandwidth it consumes must be factored into any scheduling
     * @return true if uses fpga bus
     */
    virtual bool usesFpgaBus() const override ;

	// Debug
	virtual void show(std::ostream& os = std::cout) const override ;
	virtual void showWaveformReg(std::ostream& os = std::cout) const override ;
	virtual void showWaveformMasterReg(std::ostream& os) const override ;

protected:
    // Get the sample rate for this instance
    virtual unsigned getInstanceSampleRateKsps(ICarrier::Type carrierType) const override ;


private:
	// Set the capture params
	virtual bool updateCapture(std::string& error) override ;

	// common set trigger
	virtual bool setTrigger(int airframeCountToTrigger) override ;

	// Set the streaming
	virtual void setStreaming(bool enable);

private:
	// Maximum capture depth supported
	unsigned mMaxCaptureDepth ;

} ;

}

inline std::ostream& operator<<(std::ostream& os, const Mplane::WaveformHardwareRxAdc& rhs)
{
	rhs.show(os) ;
	return os ;
}

inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Mplane::WaveformHardwareRxAdc>& rhs)
{
	rhs->show(os) ;
	return os ;
}



#endif /* WAVEFORMHARDWARERXADC_H_ */
