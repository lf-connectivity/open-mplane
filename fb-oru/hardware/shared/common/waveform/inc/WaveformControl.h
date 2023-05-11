/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformControl.h
 * \brief     Implements the waveform playback/capture
 *
 *
 * \details   Controls waveform playback/capture. Manages a single waveform resource and associates with it an object
 * 				containing waveform settings. Also moves data to/from files.
 *
 */

#ifndef WAVEFORM_CONTROL_H_
#define WAVEFORM_CONTROL_H_

#include <iostream>

#include <memory>
#include "IWaveformControl.h"

namespace Mplane {

class WaveformControl : public virtual IWaveformControl {
public:
	WaveformControl() ;
	virtual ~WaveformControl() ;

	/**
	 * Sets the associated hardware once this has been allocated to the named waveform
	 * @param waveformHardware
	 */
	virtual bool setWaveformHardware(std::shared_ptr<IWaveformHardware> waveformHardware, std::string& error) override ;

	/**
	 * Wave control is informed of an enable change
	 */
	virtual void enableHasChanged(bool enable) override ;

	/**
	 * Wave control is informed of a filename change
	 */
	virtual bool filenameHasChanged(std::string& error) override ;

	/**
	 * Validate the settings just before starting capture/playback
	 * @return true if settings are all valid
	 */
	virtual bool validate(std::string& error) override ;

	/**
	 * Having checked the validity of the settings, this method should then be called to set up the hardware registers
	 * prior to calling the start method
	 * @return true if ok
	 */
	virtual bool updateHardware(std::string& error) override ;

	/**
	 * Called when all other operations have completed
	 * @param error	Set on error
	 * @return true if ok
	 */
	virtual bool completeUpdate(std::string &error) override ;

	/**
	 * Shutdown capture/playback if running
	 * @param error
	 * @return true if ok
	 */
	virtual bool shutdown(std::string& error) override ;

	/**
	 * For playback waveforms read the playback file and determine the depth based on the file size. Assumes filename
	 * has been set.
	 *
	 * For capture types or error returns 0.
	 */
	virtual unsigned getFileDepth() override ;

	/**
	 * Change the playback scaling gain on the fly
	 * @param scalingGain
	 */
	virtual bool setScalingGain(float scalingGain) override ;

	/**
	 * Change the capture streaming on the fly
	 * @param enable
	 */
	virtual bool setStreaming(bool enable) override;

	/**
	 * Check capture is complete if this is enabled for capture
	 * @param error
	 * @return false on error
	 */
	virtual bool checkCaptureComplete(std::string& error) override ;

	/**
	 * Resync streams for enabled playback
	 * @param error
	 * @return false on error
	 */
	virtual bool resyncPlaybackStreams(std::string& error) override ;


	// Accessors

	/**
	 * Get the waveform settings pointer for this controller
	 * @return pointer to waveform
	 */
	virtual std::shared_ptr<IWaveform> getWaveform() const override ;

	/**
	 * Get the waveform hardware pointer for this controller
	 * @return pointer to waveform hardware
	 */
	virtual std::shared_ptr<IWaveformHardware> getWaveformHardware() const override ;

	/**
	 * Get the waveform memory pointer for this controller
	 * @return pointer to waveform memory
	 */
	virtual std::shared_ptr<IWaveformMem> getWaveformMem() const override ;

	// Debug
	virtual void show(std::ostream& os = std::cout) const override ;

protected:
	// write memory from file
	virtual bool writeMemFromFile(const std::string& filename, std::shared_ptr<IWaveformHardware> waveformHardware,
			std::string& error) const ;

	// Check the filename setting is valid
	virtual bool checkFilename(std::string& error) const ;


public:
	// Start all enabled capture
	static bool startCapturePlayback(bool playbackEnable, std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves, std::string& error) ;

	// start all enabled playback
	static bool startPlayback(std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves, std::string& error) ;

	// stop all capture
	static bool stopCapture(std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves, std::string& error) ;

	// stop all playback
	static bool stopPlayback(std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves, std::string& error) ;

	// Tidy up
	static bool completeStartStop(std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves, std::string& error) ;

	// Directory paths for the files
	static std::string getPlaybackDirectory() ;
	static std::string getCaptureDirectory() ;

private:
	// Create list of waveform hardware
	static std::vector< std::shared_ptr<IWaveformHardware> > getWaveformHardwareList(std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves) ;

	// read memory out to file
	static bool readMemToFile(const std::string& filename, std::shared_ptr<IWaveformHardware> waveformHardware, std::string& error) ;

	// read memory out to tcp port (via callback)
	static bool readMemToCallback(IWaveform::CaptureCallback callback, std::shared_ptr<IWaveformHardware> waveformHardware, std::string& error) ;

protected:
	// Flag set when hardware settings need to be updated
	bool mUpdateRequired ;

	// pointer to the waveform settings - changes to these settings are then automatically picked up in this object
	std::shared_ptr<IWaveform> mWaveform ;

	// pointer to the allocated hardware - this will be set once the settings are complete
	std::shared_ptr<IWaveformHardware> mWaveformHardware ;

	// memory to use
	std::shared_ptr<IWaveformMem> mWaveformMem ;

} ;

}


inline std::ostream& operator<<(std::ostream& os, const Mplane::IWaveformControl& rhs)
{
	rhs.show(os) ;
	return os ;
}

inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Mplane::IWaveformControl>& rhs)
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


#endif /* WAVEFORM_CONTROL_H_ */
