/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SharedArbTestHelper.h
 * \brief     ARB command helper
 *
 *
 * \details
 *
 */


#ifndef SHAREDARBTESTHELPER_H_
#define SHAREDARBTESTHELPER_H_

#include <memory>
#include <string>
#include <vector>

#include "Mutex.h"
#include "DataVariant.h"
#include "Frequency.h"
#include "Loggable.h"

#include "ICarrier.h"
#include "ITxPort.h"
#include "IRxPort.h"

namespace Mplane {

//------------------------------------------------------------------------------------------
// Some utility classes used to store user settings

class ArbData {
public:
	ArbData(const std::string& wavename, bool resourcePresent, unsigned carrier) :
		mWavename(wavename),
		mResourcePresent(resourcePresent),
		mCarrier(carrier),

		mFilename(""),
		mTrigger(306438),
		mDepth(0),
		mEnable(false)
	{}

	virtual ~ArbData() {}

	unsigned getCarrier() const {
		return mCarrier;
	}

	unsigned getDepth() const {
		return mDepth;
	}

	void setDepth(unsigned depth) {
		mDepth = depth;
	}

	bool isEnable() const {
		return mEnable;
	}

	void setEnable(bool enable) {
		mEnable = enable;
	}

	int getTrigger() const {
		return mTrigger;
	}

	void setTrigger(int trigger) {
		mTrigger = trigger;
	}

	const std::string& getWavename() const {
		return mWavename;
	}

	const std::string& getFilename() const {
		return mFilename;
	}

	void setFilename(const std::string& filename) {
		mFilename = filename;
	}

	bool isResourcePresent() const {
		return mResourcePresent;
	}

private:
	std::string mWavename ;
	bool mResourcePresent ;
	unsigned mCarrier ;

	std::string mFilename ;
	int mTrigger ;
	unsigned mDepth ;
	bool mEnable ;
};


class ArbPlayback : public ArbData {
public:
	ArbPlayback(const std::string& wavename, bool resourcePresent, unsigned carrier) :
		ArbData(wavename, resourcePresent, carrier)
	{}

	virtual ~ArbPlayback() {}
};

class ArbCapture : public ArbData {
public:
	ArbCapture(const std::string& wavename, bool resourcePresent, unsigned carrier) :
		ArbData(wavename, resourcePresent, carrier)
	{}

	virtual ~ArbCapture() {}
};


//------------------------------------------------------------------------------------------
// The helper class
class SharedArbTestHelper : public Loggable
{
public:
	// singleton
	static std::shared_ptr<SharedArbTestHelper> getInstance() ;

	virtual ~SharedArbTestHelper() ;

	// TIF interface

	/**
	 * Called with:
	 *   ENUM(LTE) air-std
	 *   ENUM(5MHz:10MHz:15MHz:20MHz) bw
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void set( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void show( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT port
	 *   [STRING waveform]
	 *   [INT depth]
	 *   [INT trigger]
	 *   [BOOL(off:on) enable]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void cpriCapture( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT port
	 *   [STRING waveform]
	 *   [INT trigger]
	 *   [BOOL(off:on) multicast]
	 *   [BOOL(off:on) enable]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void cpriPlayback( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT port
	 *   [STRING waveform]
	 *   [INT depth]
	 *   [INT trigger]
	 *   [BOOL(off:on) enable]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void rfCapture( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT port
	 *   [STRING waveform]
	 *   [INT trigger]
	 *   [BOOL(off:on) multicast]
	 *   [BOOL(off:on) enable]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void rfPlayback( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   [STRING path]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void playbackFiles( DataVariantList *callList, DataVariantList *returnList ) const;

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void playbackStart( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void playbackStop( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   BOOL(off:on) enable
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void playbackMulticast( DataVariantList *callList, DataVariantList *returnList );


	/**
	 * Called with:
	 *   [STRING path]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void captureFiles( DataVariantList *callList, DataVariantList *returnList ) const;

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void captureStart( DataVariantList *callList, DataVariantList *returnList );


protected:
	SharedArbTestHelper() ;

	// Initialise the object and the hardware
	void init() ;

private:
	ICarrierSetter& getCarrierSetter(bool& ok, unsigned index, DataVariantList *returnList) const ;
	const ICarrier& getCarrier(bool& ok, unsigned index, DataVariantList *returnList) const ;
	std::shared_ptr<ITxPort> getTxPort(unsigned index, DataVariantList *returnList) const ;
	std::shared_ptr<IRxPort> getRxPort(unsigned index, DataVariantList *returnList) const ;

	bool checkState(bool ok, const std::string& param, DataVariantList *returnList) const ;
	bool checkSettings(DataVariantList *returnList) const ;
	bool setCarrier(
		unsigned index,
		const std::string& typeStr,
		const Frequency& centreFreq,
		unsigned groupSize,
		DataVariantList *returnList) const ;
	bool getPortNum(unsigned& port, DataVariantList *callList, DataVariantList *returnList) const ;
	bool setAllCarriersState(bool enable, DataVariantList *returnList) const ;
	bool setCarrierState(unsigned index, bool enable, DataVariantList *returnList) const ;
	void showFiles(const std::string& path, DataVariantList *returnList) const ;

private:
	Mutex mMutex ;
	std::string mAirStd ;
	std::string mBw ;

	// Are carriers required (i.e. any playback that use carriers)?
	bool mCarriersRequired ;

	// Model of playback/capture settings
	bool mPlaybackMulticast ;
	std::vector<ArbPlayback> mRfPlayback ;
	std::vector<ArbPlayback> mCpriPlayback ;
	std::vector<ArbCapture> mRfCapture ;
	std::vector<ArbCapture> mCpriCapture ;

} ;

}

#endif /* SHAREDARBTESTHELPER_H_ */
