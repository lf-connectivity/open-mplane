/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IWaveformManager.h
 * \brief     Interface to waveform management
 *
 *
 * \details   Handles all of the hardware interfacing (writing to fpga registers) etc for waveforms
 *
 */


#ifndef IWAVEFORMMANAGER_H_
#define IWAVEFORMMANAGER_H_

#include <iostream>
#include <string>

#include <memory>
#include "IFileMgr.h"
#include "ICarrier.h"
#include "IWaveformControl.h"
#include "IWaveform.h"

namespace Mplane {

class IWaveformManager {
public:
	/**
	 * Singleton factory
	 * @return pointer to the single instance of the Waveform Manager
	 */
	static std::shared_ptr<IWaveformManager> getInstance(void) ;

	// Destructor
	virtual ~IWaveformManager() {}

	/**
	 * Waveform initialisation. Called to define the supported waveform hardware objects for this instance of the waveform
	 * manager. Can be overridden by derived objects to define their own waveforms
	 */
	virtual bool init() =0 ;

	/**
	 * Create a new waveform with the given name
	 * @param name
	 * @return true if able to create the new waveform
	 */
	virtual bool createWave(const std::string& name, IWaveform::WaveType type) = 0 ;

	/**
	 * Does the named waveform exist
	 * @param name
	 * @return true exists
	 */
	virtual bool hasWave(const std::string& name) const = 0 ;

	/**
	 * Get the named waveform exist
	 * @param name
	 * @return waveform pointer
	 */
	virtual std::shared_ptr<IWaveform> getWave(const std::string& name) const = 0 ;

	/**
	 * Delete the named waveform
	 * @param name
	 * @return true if able to delete the waveform
	 */
	virtual bool deleteWave(const std::string& name) = 0 ;

	// set waveform settings
	virtual bool setAntennaPort(const std::string& waveName, unsigned antennaPort) = 0 ;
	virtual bool setCarrierIdx(const std::string& waveName, unsigned carrierIdx) = 0 ;
	virtual bool setDirection(const std::string& waveName, IWaveform::WaveDirection direction) = 0 ;
	virtual bool setFilename(const std::string& waveName, const std::string& filename) = 0 ;
	virtual bool setEnable(const std::string& waveName, bool enable) = 0 ;
	virtual bool setDepth(const std::string& waveName, unsigned depth) = 0 ;
	virtual bool setGain(const std::string& waveName, float gain) = 0 ;
	virtual bool setGainFilename(const std::string& waveName, const std::string& gainFilename) = 0 ;
	virtual bool setTrigger(const std::string& waveName, unsigned trigger) = 0 ;
	virtual bool setScalingGain(const std::string& waveName, float scalingValue ) = 0 ;
	virtual bool setCaptureCallback(const std::string& waveName, IWaveform::CaptureCallback callback) = 0 ;

	// wrxcal-specific waveform settings
	virtual bool setStreaming(const std::string& waveName, bool streaming) = 0 ;
	virtual bool setAveraging(const std::string& waveName, unsigned averaging) = 0 ;
	virtual bool setNco(const std::string& waveName, double offset) = 0 ;
	virtual bool setDecimation(const std::string& waveName, IWaveform::WrxcalDecimation decimation) = 0 ;


	/**
	 * For playback waveforms read the playback file and determine the depth based on the file size. Assumes filename
	 * has been set.
	 *
	 * For capture types or error returns 0.
	 */
	virtual unsigned getFileDepth(const std::string& waveName) const =0 ;

	/**
	 * Get the FileMgr instance for playback files
	 */
	virtual std::shared_ptr<IFileMgr> getPlaybackFileMgr() =0 ;


	// Resource checking - resources are 0 indexed

	/**
	 * Determine if the indexed resource is actually present in the hardware
	 * @param index
	 * @return true if resource present
	 */
	virtual bool isResourcePresent(unsigned index) const =0 ;


	// All waveform

	/**
	 * Given a carrier type, calculate the equivalent waveform sample rate
	 * @param carrier type
	 * @return sample rate in ksps
	 */
	virtual unsigned calcSampleRateKsps(ICarrier::Type) const =0 ;

	/**
	 * Enable/disable capture/playback on all capture and playback waveforms
	 * @param enable
	 * @return
	 */
	virtual bool setCapturePlayback(bool captureEnable, bool playbackEnable) = 0 ;

	/**
	 * Get the reason for an error
	 * @return error string
	 */
	virtual std::string getErrorReason() = 0 ;

	/**
	 * Get the number of waveform resources supported
	 */
	virtual unsigned supportedWaveforms() const = 0 ;

	/**
	 * Get the number of waveform resources currently created
	 */
	virtual unsigned numWaveforms() const = 0 ;

	/**
	 * Get current playback enable setting
	 */
	virtual bool isPlaybackEnabled() const = 0 ;

	/**
	 * Get current capture enable setting
	 */
	virtual bool isCaptureEnabled() const = 0 ;

	/**
	 * Get directory path for where playback files are stored
	 * @return directory
	 */
	virtual std::string getPlaybackDirectory() const =0 ;

	/**
	 * Get directory path for where capture files are stored
	 * @return directory
	 */
	virtual std::string getCaptureDirectory() const =0 ;


	// Debug
	virtual void show(std::ostream& os = std::cout) const = 0 ;
	virtual void show(const std::string& waveName, std::ostream& os = std::cout) const = 0 ;

	virtual void showWaveformReg(const std::string& waveName, std::ostream& os = std::cout) =0;
	virtual void showWaveformMasterReg(std::ostream& os) =0;


protected:
	// Utility methods used by the waveform managers but may be overridden by derived objects

	// allocate waveform resources
	virtual bool allocateCapture() =0 ;

	// validate settings
	virtual bool validateCapture() =0 ;

	// schedule waveform captures to ensure we don't overload the SDRAM interface
	virtual bool scheduleCapture() =0 ;

	// update the hardware
	virtual bool updateHardwareCapture() =0 ;

	// free waveform resources
	virtual bool deallocateCapture() =0 ;

	// allocate waveform resources
	virtual bool allocatePlayback() =0 ;

	// validate settings
	virtual bool validatePlayback() =0 ;

	// update the hardware
	virtual bool updateHardwarePlayback() =0 ;

	// free waveform resources
	virtual bool deallocatePlayback() =0 ;

	// convert waveform name to a resource index
	virtual unsigned waveNameToIndex(const std::string& name) const =0 ;

	// get antenna port from waveform name
	virtual unsigned getPortFromWaveName(const std::string& name) const =0;

	// is the name a valid wave name?
	virtual bool validWaveName(const std::string& name) =0 ;

	// Create a new WaveformControl instance
	virtual std::shared_ptr<IWaveformControl> createWaveControl() const =0 ;

} ;

}

#endif /* IWAVEFORMMANAGER_H_ */
