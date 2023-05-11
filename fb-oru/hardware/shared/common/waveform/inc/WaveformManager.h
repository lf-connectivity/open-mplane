/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformManager.h
 * \brief     Manages all the waveform blocks
 *
 *
 * \details   Keeps a list of all the available waveform resources and manages configuring them and their playback/capture
 *
 */


#ifndef WAVEFORMMANAGER_H_
#define WAVEFORMMANAGER_H_

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Mutex.h"
#include "IWaveformManager.h"
#include <memory>

#include "IWaveformHardware.h"
#include "WaveMemMgr.h"

namespace Mplane {

class WaveformManager : public virtual IWaveformManager {
public:
	WaveformManager(
		unsigned waveMemSize = WaveMemMgr::DEFAULT_MEMSIZE,
		unsigned waveMemStart = WaveMemMgr::DEFAULT_MEMSTART,
		unsigned waveMemAlignment = WaveMemMgr::DEFAULT_MEMALIGN
	) ;
	virtual ~WaveformManager() ;

	/**
	 * Waveform initialisation. Called to define the supported waveform hardware objects for this instance of the waveform
	 * manager. Can be overridden by derived objects to define their own waveforms
	 */
	virtual bool init() override ;

	// Individual waveform management

	/**
	 * Create a new waveform with the given name
	 * @param name
	 * @return true if able to create the new waveform
	 */
	virtual bool createWave(const std::string& name, IWaveform::WaveType type) override ;

	/**
	 * Does the named waveform exist
	 * @param name
	 * @return true exists
	 */
	virtual bool hasWave(const std::string& name) const override ;

	/**
	 * Get the named waveform exist
	 * @param name
	 * @return waveform pointer
	 */
	virtual std::shared_ptr<IWaveform> getWave(const std::string& name) const override ;

	/**
	 * Delete the named waveform
	 * @param name
	 * @return true if able to delete the waveform
	 */
	virtual bool deleteWave(const std::string& name) override ;

	// set waveform settings
	virtual bool setAntennaPort(const std::string& waveName, unsigned antennaPort) override ;
	virtual bool setCarrierIdx(const std::string& waveName, unsigned carrierIdx) override ;
	virtual bool setDirection(const std::string& waveName, IWaveform::WaveDirection direction) override ;
	virtual bool setFilename(const std::string& waveName, const std::string& filename) override ;
	virtual bool setEnable(const std::string& waveName, bool enable) override ;
	virtual bool setDepth(const std::string& waveName, unsigned depth) override ;
	virtual bool setGain(const std::string& waveName, float gain) override ;
	virtual bool setGainFilename(const std::string& waveName, const std::string& gainFilename) override ;
	virtual bool setTrigger(const std::string& waveName, unsigned trigger) override ;
    virtual bool setScalingGain(const std::string& waveName, float scalingGain ) override ;
	virtual bool setCaptureCallback(const std::string& waveName, IWaveform::CaptureCallback callback) override ;

	// wrxcal-specific waveform settings
	virtual bool setStreaming(const std::string& waveName, bool streaming) override ;
	virtual bool setAveraging(const std::string& waveName, unsigned averaging) override ;
	virtual bool setNco(const std::string& waveName, double offset) override ;
	virtual bool setDecimation(const std::string& waveName, IWaveform::WrxcalDecimation decimation) override ;



	/**
	 * For playback waveforms read the playback file and determine the depth based on the file size. Assumes filename
	 * has been set.
	 *
	 * For capture types or error returns 0.
	 */
	virtual unsigned getFileDepth(const std::string& waveName) const override ;

	/**
	 * Get the FileMgr instance for playback files
	 */
	virtual std::shared_ptr<IFileMgr> getPlaybackFileMgr() override ;


	// Resource checking - resources are 0 indexed

	/**
	 * Determine if the indexed resource is actually present in the hardware
	 * @param index
	 * @return true if resource present
	 */
	virtual bool isResourcePresent(unsigned index) const override ;


	// All waveform

	/**
	 * Given a carrier type, calculate the equivalent waveform sample rate
	 * @param carrier type
	 * @return sample rate in ksps
	 */
	virtual unsigned calcSampleRateKsps(ICarrier::Type) const override ;


	/**
	 * Enable/disable capture/playback on all capture and playback waveforms
	 * @param enable
	 * @return
	 */
	virtual bool setCapturePlayback(bool captureEnable, bool playbackEnable) override ;

	/**
	 * Get the reason for an error
	 * @return error string
	 */
	virtual std::string getErrorReason() override ;

	/**
	 * Get the number of waveform resources supported
	 */
	virtual unsigned supportedWaveforms() const override ;

	/**
	 * Get the number of waveform resources currently created
	 */
	virtual unsigned numWaveforms() const override ;

	/**
	 * Get current playback enable setting
	 */
	virtual bool isPlaybackEnabled() const override ;

	/**
	 * Get current capture enable setting
	 */
	virtual bool isCaptureEnabled() const override ;

	/**
	 * Get directory path for where playback files are stored
	 * @return directory
	 */
	virtual std::string getPlaybackDirectory() const override ;

	/**
	 * Get directory path for where capture files are stored
	 * @return directory
	 */
	virtual std::string getCaptureDirectory() const override ;


	// Debug
	virtual void show(std::ostream& os = std::cout) const override ;
	virtual void show(const std::string& waveName, std::ostream& os = std::cout) const override ;

	virtual void showWaveformReg(const std::string& waveName, std::ostream& os = std::cout) override ;
	virtual void showWaveformMasterReg(std::ostream& os) override ;

protected:
	// allocate waveform resources
	virtual bool allocateCapture() override ;

	// schedule waveform captures to ensure we don't overload the SDRAM interface
	virtual bool scheduleCapture() override ;

	// validate settings
	virtual bool validateCapture() override ;

	// update the hardware
	virtual bool updateHardwareCapture() override ;

	// free waveform resources
	virtual bool deallocateCapture() override ;

	// allocate waveform resources
	virtual bool allocatePlayback() override ;

	// validate settings
	virtual bool validatePlayback() override ;

	// update the hardware
	virtual bool updateHardwarePlayback() override ;

	// free waveform resources
	virtual bool deallocatePlayback() override ;

	// convert waveform name to a resource index
	virtual unsigned waveNameToIndex(const std::string& name) const override;

	// get antenna port from waveform name
	virtual unsigned getPortFromWaveName(const std::string& name) const override;

	// is the name a valid wave name?
	virtual bool validWaveName(const std::string& name) override;

	// Create a new IWaveformControl instance
	virtual std::shared_ptr<IWaveformControl> createWaveControl() const override ;

protected:
	std::shared_ptr<IWaveformControl> getWaveformControl(const std::string& name) const ;

	void setError(const std::string& error) ;

	void addResource(std::shared_ptr<IWaveformHardware> waveformHardware) {
		mWaveformResources.push_back(waveformHardware) ;
	}

	unsigned numResources() const {
		return mWaveformResources.size() ;
	}

private:
	// Make access thread-safe
	mutable Mutex mMutex ;

	// List of waveform hardware objects - one per physical resource
	std::vector< std::shared_ptr<IWaveformHardware> > mWaveformResources ;

	//Map of waveform names and the associated antenna port - nailed for now
	std::map<std::string, unsigned> mWaveformPortMap;

	// map the waveform names to controllers
	std::map< std::string, std::shared_ptr<IWaveformControl> > mWaveformMap ;
	typedef std::map< std::string, std::shared_ptr<IWaveformControl> >::iterator WaveformMapIter ;
	typedef std::map< std::string, std::shared_ptr<IWaveformControl> >::const_iterator WaveformMapConstIter ;

	// String set to the last error
	std::string mError ;

} ;

}

#endif /* WAVEFORMMANAGER_H_ */
