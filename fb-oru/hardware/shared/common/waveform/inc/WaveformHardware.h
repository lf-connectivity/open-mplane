/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardware.h
 * \brief     Interfaces with the hardware to set up the waveform block
 *
 *
 * \details   Handles all of the hardware interfacing (writing to fpga registers) etc for waveforms
 *
 */

#ifndef WAVEFORMHARDWARE_H_
#define WAVEFORMHARDWARE_H_

#include <iostream>

#include <memory>

#include "ICarrier.h"
#include "ICarrierServer.h"
#include "IFpgaMgr.h"
#include "ICarrierHardware.h"
#include "IHardwareSettings.h"
#include "Mutex.h"

#include "IWaveform.h"
#include "IWaveformMem.h"
#include "IWaveformHardware.h"

namespace Mplane {

/**
 * Waveform hardware class
 */
class WaveformHardware : public virtual IWaveformHardware {
public:
	explicit WaveformHardware(unsigned index, unsigned port) ;
	virtual ~WaveformHardware() ;

	using AirstdType = ICarrierHardwareTypes::AirstdType ;
	using ChbwType = ICarrierHardwareTypes::ChbwType ;
	using SampleRate = ICarrierHardwareTypes::SampleRate ;

	/**
	 * Init harwdare
	 * @return true if ok
	 */
	virtual bool init(std::string& error) override ;

	/**
	 * Update the settings
	 * @return true if ok
	 */
	virtual bool updateSettings(std::shared_ptr<IWaveform> waveform, std::shared_ptr<IWaveformMem> waveformMem, std::string& error) override ;

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
	virtual bool writeMemory(const short* buffer, unsigned bufferSize, bool& endOfData, std::string& error) override ;

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
	virtual bool readMemory(short* buffer, unsigned& bufferSize, unsigned maxReadSize, bool& endOfFile, std::string& error) override ;

	/**
	 * Validate that this waveform module is ok to enable
	 * @param error ref to string that contains the error message on error
	 * @return true if ok
	 */
	virtual bool validate(std::string& error) const override ;

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
	 * @return true if requires memory to be allocatedoverride ; false otherwise
	 */
	virtual bool requiresWaveformMem(void) const override ;

	/**
	 * Returns the maximum depth any waveform can be set to - used to check parameters
	 */
	virtual unsigned getMaxDepth(void) const override ;

	/**
	 * Get the capture time for this waveform hardware
	 * @return unsigned containing the delay in ns
	 */
	virtual const unsigned getCaptureTime(void) const override ;

	/**
	 * Do any necessary initialisation ready for capture
	 */
	virtual void captureInit(void) override ;

	/**
	 * Get the waveform index
	 */
	virtual unsigned getIndex(void) const override ;

	/**
	 * Is the waveform hardware present
	 * @return true if present
	 */
	virtual bool isPresent() const override ;

	/**
	 * Given the depth setting, returns the total number of bytes in the waveform data
	 */
	virtual unsigned getNumBytes(void) const override ;

	/**
	 * Returns the current sample rate in Ksps
	 */
	virtual unsigned getSampleRateKsps() const override ;

    /** set the playback scaling value regs - ok to do this live
     */
    virtual bool setPlaybackScalingValue() override ;

    /**
     * Does this waveform module use the FPGA bus? If so then the bandwidth it consumes must be factored into any scheduling
     * @return true if uses fpga bus
     */
    virtual bool usesFpgaBus() const override ;


	// Debug
	virtual void show(std::ostream& os = std::cout) const override ;
	virtual void showWaveformReg(std::ostream& os = std::cout) const override ;
	virtual void showWaveformMasterReg(std::ostream& os) const override ;

	// Accessors

	/**
	 * Get the waveform settings pointer for this controller
	 * @return pointer to waveform
	 */
	virtual std::shared_ptr<IWaveform> getWaveform() const override ;

	/**
	 * Get the waveform memory pointer for this controller
	 * @return pointer to waveform memory
	 */
	virtual std::shared_ptr<IWaveformMem> getWaveformMem() const override ;

	/**
	 * Set the memory parameters
	 * @return false on error
	 */
	virtual bool setWaveformMem() override ;


public:
	// All waveforms

	/**
	 * Initialise harwdare
	 */
	static bool initMaster(std::string& error) ;

	/**
	 * Start all enabled capture
	 * @param waveformHardwareList	List of waveform hardware to process
	 * @return true if ok
	 */
	static bool startAllCapture(bool playbackEnable, std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList, std::string& error) ;

	/**
	 * Start all enabled playback
	 * @param waveformHardwareList	List of waveform hardware to process
	 * @return true if ok
	 */
	static bool startAllPlayback(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList, std::string& error) ;

	/**
	 * Stop all enabled capture
	 * @param waveformHardwareList	List of waveform hardware to process
	 * @return true if ok
	 */
	static bool stopAllCapture(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList, std::string& error) ;

	/**
	 * Stop all enabled playback
	 * @param waveformHardwareList	List of waveform hardware to process
	 * @return true if ok
	 */
	static bool stopAllPlayback(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList, std::string& error) ;

	/**
	 * Is master playback enable set
	 * @return true if enabled
	 */
	static bool isMasterPlaybackEnabled() ;

	/**
	 * Is master capture enable set
	 * @return true if enabled
	 */
	static bool isMasterCaptureEnabled() ;

	/**
	 * Are we currently capturing? This is a software flag that tracks when we start/stop capturing and is independent
	 * of the fpga master capture bit
	 *
	 * @return true if capturing
	 */
	static bool isCapturing() ;


	/**
	 * Utility for waiting for N microseconds
	 * @param microsecs
	 */
	static void microSleep(unsigned microsecs) ;

	/**
	 * Given a carrier type, calculate the equivalent waveform sample rate
	 * @param carrier type
	 * @return sample rate in ksps
	 */
	static unsigned calcCarrierSampleRateKsps(ICarrier::Type) ;

protected:
	// override the default presence detection
	virtual void setPresent(bool present) ;

	// Set the capture params
	virtual bool updateCapture(std::string& error) ;

	// Set the playback params
	virtual bool updatePlayback(std::string& error) ;

	// Set depth of capture
	virtual bool setCaptureDepth(unsigned size) ;

	// Set capture trigger
	virtual bool setCaptureTrigger(unsigned trigger) ;

	// Set playback trigger
	virtual bool setPlaybackTrigger(unsigned trigger) ;

	// common set trigger
	virtual bool setTrigger(int airframeCountToTrigger) ;

	// set the playback sample rate regs
	virtual bool setPlaybackSamplerate() ;

	// wait until write fifo is empty
	virtual bool waitWriteFifoEmpty(std::string& error) ;

	// wait until read fifo is not empty
	virtual bool waitReadFifoNotEmpty(std::string& error) ;

	// Calculate the scaling value from the waveform scaling gain
    virtual unsigned calcScalingValue( void );

    // calculate the number of pairs to read in this block
    virtual unsigned calcNumPairsToRead(unsigned numOfPairsToRead) const ;

    // Get the sample rate for this instance
    virtual unsigned getInstanceSampleRateKsps(ICarrier::Type carrierType) const ;

protected:
	// get the maximum number of pairs we can read per block (due to hardware restrictions)
	static unsigned getMaxPairsPerBlockRead(void) ;

	// count the number of enabled waveforms
	static void countEnabled(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList,
			unsigned& numCapture, unsigned& numPlayback) ;

	// set memory size for all enabled playback waveforms
	static bool setAllWaveformMem(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList) ;

	// wait for all the capture done bits
	static bool waitCapturesDone(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList,
			unsigned maxCaptureTime_nsec, std::string& error) ;

	// change the state of the capturing flag
	static void setCapturingState(bool capturing) ;

protected:
	// Allocated to a particular hardware block
	unsigned mWaveIdx ;

	// Antenna port number that the hardware is linked to
	unsigned mPort ;

	// Need to protect the memory transfer portion of the fpga from simultaneous access
	Mutex mWaveAccessMutex ;

	// pointer to fpga registers
	std::shared_ptr<IFpgaWaveformRegs> mWaveformFpga ;

	// pointer to fpga antenna registers
	std::shared_ptr<IFpgaAntennaRegs> mAntennaFpga ;

	// carrier server instance
	std::shared_ptr<ICarrierServer> mCarrierServer ;

	// pointer to hardware data
	std::shared_ptr< ICarrierHardwareData> mHardwareData ;

	// pointer to hardware settings
	std::shared_ptr<const IHardwareSettings> mHardwareSettings ;

	// The following values are set on update

	// pointer to the current waveform settings
	std::shared_ptr<IWaveform> mWaveform ;

	// pointer to the current waveform memory settings
	std::shared_ptr<IWaveformMem> mWaveformMem ;

	// pointer to carrier
	const ICarrier* mCarrier ;

	// current carrier airstd/chbw
	AirstdType mAirstd ;
	ChbwType mChbw ;

	// Read address - used for memory reading
	unsigned mReadAddr ;
	unsigned mReadEndAddr ;

	// Write address   - used for memory writing
	unsigned mWriteAddr ;

	// Is the waveform hardware present
	bool mPresent ;

protected:
	// Track when we're capturing
	static Mutex mCaptureMutex ;
	static bool mCapturing ;

} ;

}

inline std::ostream& operator<<(std::ostream& os, const Mplane::IWaveformHardware& waveformHardware)
{
	waveformHardware.show(os) ;
	return os ;
}

inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Mplane::IWaveformHardware>& rhs)
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


#endif /* WAVEFORMHARDWARE_H_ */
