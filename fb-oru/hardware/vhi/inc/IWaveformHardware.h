/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IWaveformHardware.h
 * \brief     Virtual interface to waveform hardware
 *
 *
 * \details
 *
 */


#ifndef IWAVEFORMHARDWARE_H_
#define IWAVEFORMHARDWARE_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "IWaveform.h"
#include "IWaveformMem.h"

namespace Mplane {

class IWaveformHardware {
public:
	IWaveformHardware() {}
	virtual ~IWaveformHardware() {}

	/**
	 * Init harwdare
	 * @return true if ok
	 */
	virtual bool init(std::string& error) =0 ;

	/**
	 * Update the settings
	 * @return true if ok
	 */
	virtual bool updateSettings(std::shared_ptr<IWaveform> waveform, std::shared_ptr<IWaveformMem> waveformMem, std::string& error) =0 ;

	/**
	 * Update the hardware using current settings
	 * @return true if ok
	 */
	virtual bool updateHardware(std::string& error) =0 ;

	/**
	 * Wave hardware is informed of an enable change
	 */
	virtual void enableHasChanged(bool enable) =0 ;

	/**
	 * Is there a capture write error for this waveform
	 * @return true on error
	 */
	virtual bool isCaptureWriteError() const =0 ;

	/**
	 * Is the capture complete for this waveform
	 * @return true on complete
	 */
	virtual bool isCaptureDone() const =0 ;

	/**
	 * Is playback enabled for this waveform
	 * @return true if enabled
	 */
	virtual bool isPlaybackEnabled() const =0 ;

	/**
	 * Was there a playback read error on this waveform
	 * @return true on error
	 */
	virtual bool isPlaybackReadError() const =0 ;

	/**
	 * Prepare for writing - must be called once before starting to write to memory (resets internal counters to start of
	 * memory)
	 */
	virtual void writeMemoryStart()=0 ;

	/**
	 * Write buffer to next address
	 * @param buffer
	 * @return true if write ok
	 */
	virtual bool writeMemory(const short* buffer, unsigned bufferSize, bool& endOfData, std::string& error)=0 ;

	/**
	 * Prepare for reading - must be called once before starting to read from memory (resets internal counters to start of
	 * memory)
	 */
	virtual void readMemoryStart()=0 ;

	/**
	 * Write buffer to next address
	 * @param buffer
	 * @param maxReadSize	Maximum amount to read in one go
	 * @return true if read ok
	 */
	virtual bool readMemory( short* buffer, unsigned& bufferSize, unsigned maxReadSize, bool& endOfFile, std::string& error)=0 ;

	/**
	 * Validate that this waveform module is ok to enable
	 * @param error ref to string that contains the error message on error
	 * @return true if ok
	 */
	virtual bool validate(std::string& error) const =0 ;

	/**
	 * Check that the carrier associated with this waveform is set up and valid for this waveform
	 * @param error ref to string that contains the error message on error
	 * @return true if ok
	 */
	virtual bool checkCarrier(std::string& error) const =0 ;

	/**
	 * Stop playback/capture
	 * @param error
	 * @return true if ok
	 */
	virtual bool shutdown(std::string& error) =0 ;

	/**
	 * Does this Waveform Hardware require memory allocated in WaveformMem
	 * @return true if requires memory to be allocated=0 ; false otherwise
	 */
	virtual bool requiresWaveformMem(void) const =0 ;

	/**
	 * Returns the maximum depth any waveform can be set to - used to check parameters
	 */
	virtual unsigned getMaxDepth(void) const =0 ;

	/**
	 * Get the capture time for this waveform hardware
	 * @return unsigned containing the delay in ns
	 */
	virtual const unsigned getCaptureTime(void) const =0 ;

	/**
	 * Do any necessary initialisation ready for capture
	 */
	virtual void captureInit(void) =0 ;

	/**
	 * Get the waveform index
	 */
	virtual unsigned getIndex(void) const =0 ;

	/**
	 * Is the waveform hardware present
	 * @return true if present
	 */
	virtual bool isPresent() const =0 ;

	/**
	 * Given the depth setting, returns the total number of bytes in the waveform data
	 */
	virtual unsigned getNumBytes(void) const =0 ;

	/**
	 * Returns the current sample rate in Ksps
	 */
	virtual unsigned getSampleRateKsps() const =0 ;

	/**
	 * set the playback scaling value regs - ok to do this live
	 * @return
	 */
    virtual bool setPlaybackScalingValue() =0 ;

    /**
     * Does this waveform module use the FPGA bus? If so then the bandwidth it consumes must be factored into any scheduling
     * @return true if uses fpga bus
     */
    virtual bool usesFpgaBus() const =0 ;

	// Debug
	virtual void show(std::ostream& os = std::cout) const =0 ;
	virtual void showWaveformReg(std::ostream& os = std::cout) const =0 ;
	virtual void showWaveformMasterReg(std::ostream& os) const =0 ;

	// Accessors

	/**
	 * Get the waveform settings pointer for this controller
	 * @return pointer to waveform
	 */
	virtual std::shared_ptr<IWaveform> getWaveform() const =0 ;

	/**
	 * Get the waveform memory pointer for this controller
	 * @return pointer to waveform memory
	 */
	virtual std::shared_ptr<IWaveformMem> getWaveformMem() const =0 ;

	/**
	 * Set the memory parameters
	 * @return false on error
	 */
	virtual bool setWaveformMem() =0 ;

} ;

}

#endif /* IWAVEFORMHARDWARE_H_ */
