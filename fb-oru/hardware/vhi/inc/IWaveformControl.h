/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IWaveformControl.h
 * \brief     Virtual interface to waveform controller class
 *
 *
 * \details   Controls waveform playback/capture. Manages a single waveform resource and associates with it an object
 * 				containing waveform settings. Also moves data to/from files.
 *
 */

#ifndef IWAVEFORM_CONTROL_H_
#define IWAVEFORM_CONTROL_H_

#include <iostream>
#include <memory>

#include "IWaveformMem.h"
#include "IWaveformHardware.h"

namespace Mplane {

class IWaveformControl {
public:
	IWaveformControl() {}
	virtual ~IWaveformControl() {}

	/**
	 * Sets the associated hardware once this has been allocated to the named waveform
	 * @param waveformHardware
	 */
	virtual bool setWaveformHardware(std::shared_ptr<IWaveformHardware> waveformHardware, std::string& error) =0 ;

	/**
	 * Wave control is informed of an enable change
	 */
	virtual void enableHasChanged(bool enable) =0 ;

	/**
	 * Wave control is informed of a filename change
	 */
	virtual bool filenameHasChanged(std::string& error) =0 ;

	/**
	 * Validate the settings just before starting capture/playback
	 * @return true if settings are all valid
	 */
	virtual bool validate(std::string& error) =0 ;

	/**
	 * Having checked the validity of the settings, this method should then be called to set up the hardware registers
	 * prior to calling the start method
	 * @return true if ok
	 */
	virtual bool updateHardware(std::string& error) =0 ;

	/**
	 * Called when all other operations have completed
	 * @param error	Set on error
	 * @return true if ok
	 */
	virtual bool completeUpdate(std::string &error) =0 ;

	/**
	 * Shutdown capture/playback if running
	 * @param error
	 * @return true if ok
	 */
	virtual bool shutdown(std::string& error) =0 ;

	/**
	 * For playback waveforms read the playback file and determine the depth based on the file size. Assumes filename
	 * has been set.
	 *
	 * For capture types or error returns 0.
	 */
	virtual unsigned getFileDepth() =0 ;

	/**
	 * Change the playback scaling gain on the fly
	 * @param scalingGain
	 */
	virtual bool setScalingGain(float scalingGain) =0 ;

	/**
	 * Change the capture streaming on the fly
	 * @param enable
	 */
	virtual bool setStreaming(bool enable) =0 ;

	/**
	 * Check capture is complete if this is enabled for capture
	 * @param error
	 * @return false on error
	 */
	virtual bool checkCaptureComplete(std::string& error) =0 ;

	/**
	 * Resync streams for enabled playback
	 * @param error
	 * @return false on error
	 */
	virtual bool resyncPlaybackStreams(std::string& error) =0 ;

	// Accessors

	/**
	 * Get the waveform settings pointer for this controller
	 * @return pointer to waveform
	 */
	virtual std::shared_ptr<IWaveform> getWaveform() const =0 ;

	/**
	 * Get the waveform hardware pointer for this controller
	 * @return pointer to waveform hardware
	 */
	virtual std::shared_ptr<IWaveformHardware> getWaveformHardware() const =0 ;

	/**
	 * Get the waveform memory pointer for this controller
	 * @return pointer to waveform memory
	 */
	virtual std::shared_ptr<IWaveformMem> getWaveformMem() const =0 ;

	// Debug
	virtual void show(std::ostream& os = std::cout) const =0 ;

} ;

}

#endif /* IWAVEFORM_CONTROL_H_ */
