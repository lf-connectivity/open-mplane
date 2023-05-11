/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DelaysMgr.h
 * \brief	  Provides IDelaysMgr
 *
 *
 * \details
 *
 */


#ifndef DelaysMgr_H_
#define DelaysMgr_H_

#include <vector>
#include <map>

#include "IDelaysMgr.h"
#include "SetVal.hpp"
#include "Mutex.h"
#include "Loggable.h"

namespace Mplane {

/*!
 * \class DelaysMgr
 */
class DelaysMgr : public virtual IDelaysMgr, public Loggable {
public:
	DelaysMgr() ;
	virtual ~DelaysMgr() ;


	/**
	 * Singleton
	 */
	static std::shared_ptr<DelaysMgr> getInstance() ;

	/**
	 * Show contents
	 * @param os
	 */
	virtual void show(std::ostream& os = std::cout) const override ;

	/**
	 * On any failure the error string is set with the failure reason. This method returns that string and clears it
	 * @return failure reason
	 */
	virtual std::string getError() override ;


	// HARDWARE INTERFACE

	/**
	 * Clear out all settings (mainly used for testing)
	 * @return true if reset ok
	 */
	virtual bool reset() override ;

	/**
	 * The hardware side is responsible for initialising this object
	 * @param numTx
	 * @param numRx
	 * @param numCarriers
	 * @return true if initialised ok
	 */
	virtual bool initialise(unsigned numTx, unsigned numRx, unsigned numCarriers) override ;

	/**
	 * Hardware access for setting the delay
	 * @param attr		The delay attribute to set
	 * @param delay		Delay in ns
	 * @return true if set ok
	 */
	virtual bool hwSetDelay(IDelaysMgr::DelayAttr attr, unsigned delay) override ;

	/**
	 * Hardware access for setting the delay on a particular antenna
	 * @param attr		The delay attribute to set
	 * @param antenna	0-based antenna number
	 * @param delay		Delay in ns
	 * @return true if set ok
	 */
	virtual bool hwSetPathDelay(IDelaysMgr::DelayAttr attr, unsigned antenna, unsigned delay) override ;

	/**
	 * Hardware access for settings the carrier delay on a particular antenna
	 * @param attr			The delay attribute to set
	 * @param carrierIndex	0-based carrier index
	 * @param antenna		0-based antenna number
	 * @param delay			Delay in ns
	 * @return true if set ok
	 */
	virtual bool hwSetCarrierDelay(IDelaysMgr::DelayAttr attr,
			unsigned carrierIndex, unsigned antenna, unsigned delay) override ;

	/**
	 * Set the midband carrier delays. A set of midband carrier delays are calculated for each antenna. This set of delays is then used
	 * for any carrier delay which hasn't yet been set.
	 * @param attr			The delay attribute to set
	 * @param carrierIndex	0-based carrier index
	 * @param delay			Delay in ns
	 * @return true if set ok
	 */
	virtual bool hwSetMidbandDelay(IDelaysMgr::DelayAttr attr, unsigned antenna, unsigned delay) override ;

	/**
	 * Hardware method for registering a callback on a delay changed by the application
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool hwRegisterDelayCallback(IDelaysMgr::DelayAttr attr,
			SetDelay callback) override ;

	/**
	 * Hardware method for registering a callback on an antenna delay changed by the application
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool hwRegisterPathDelayCallback(IDelaysMgr::DelayAttr attr,
			SetAntDelay callback) override ;

	/**
	 * Hardware method for registering a callback on a carrier delay changed by the application
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool hwRegisterCarrierDelayCallback(IDelaysMgr::DelayAttr attr,
			SetCarrierDelay callback) override ;

	/**
	 * Unregister hardware callback for the attribute
	 * @param attr			The delay attribute to deregister
	 * @return
	 */
	virtual bool hwDeregisterCallback(IDelaysMgr::DelayAttr attr) override ;

    /**
     * Hardware interface to set the frame diff in frames
     * @param frames
     * @return true if set
     */
    virtual bool hwSetFrameDiff(unsigned frames) override ;

    /**
     * Hardware interface to set the delay limits
     * @param delayDown
     * @param stepDown
     * @param delayUp
     * @param stepUp
     * @return true if set
     */
    virtual bool hwSetAdjDelayLimit(unsigned delayDown, unsigned stepDown, unsigned delayUp, unsigned stepUp) override ;


	// APPLICATION INTERFACE

	/**
	 * Application access for setting the delay
	 * @param attr		The delay attribute to set
	 * @param delay		Delay in ns
	 * @return true if set ok
	 */
	virtual bool appSetDelay(IDelaysMgr::DelayAttr attr, unsigned delay) override ;

	/**
	 * Application access for setting the delay on a particular antenna
	 * @param attr		The delay attribute to set
	 * @param antenna	0-based antenna number
	 * @param delay		Delay in ns
	 * @return true if set ok
	 */
	virtual bool appSetPathDelay(IDelaysMgr::DelayAttr attr, unsigned antenna, unsigned delay) override ;

	/**
	 * Application access for settings the carrier delay on a particular antenna
	 * @param attr			The delay attribute to set
	 * @param carrierIndex	0-based carrier index
	 * @param antenna		0-based antenna number
	 * @param delay			Delay in ns
	 * @return true if set ok
	 */
	virtual bool appSetCarrierDelay(IDelaysMgr::DelayAttr attr,
			unsigned carrierIndex, unsigned antenna, unsigned delay) override ;

	/**
	 * Application method for registering a callback on a delay changed by the hardware
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool appRegisterDelayCallback(IDelaysMgr::DelayAttr attr,
			SetDelay callback) override ;

	/**
	 * Application method for registering a callback on an antenna delay changed by the hardware
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool appRegisterPathDelayCallback(IDelaysMgr::DelayAttr attr,
			SetAntDelay callback) override ;

	/**
	 * Application method for registering a callback on a carrier delay changed by the hardware
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool appRegisterCarrierDelayCallback(IDelaysMgr::DelayAttr attr,
			SetCarrierDelay callback) override ;

	/**
	 * Unregister application callback for the attribute
	 * @param attr			The delay attribute to deregister
	 * @return
	 */
	virtual bool appDeregisterCallback(IDelaysMgr::DelayAttr attr) override ;


	// READ ACCESS

	/**
	 * Get the frame diff in frames
	 */
    virtual unsigned getFrameDiff() const override ;

    /**
     * Get the delay limits
     * @param delayDown
     * @param stepDown
     * @param delayUp
     * @param stepUp
     */
    virtual void getAdjDelayLimit(unsigned& delayDown, unsigned& stepDown, unsigned& delayUp, unsigned& stepUp) const override ;

    /**
     * Get the specified delay in ns
     * @param attr
     */
    virtual unsigned getDelay(IDelaysMgr::DelayAttr attr) const override ;

    /**
     * Get the specified antenna delay in ns
     * @param attr
	 * @param antenna		0-based antenna number
     */
    virtual unsigned getPathDelay(IDelaysMgr::DelayAttr attr, unsigned antenna) const override ;

    /**
     * Get the specified delay in ns
     * @param attr
	 * @param carrierIndex	0-based carrier index
	 * @param antenna		0-based antenna number
     */
    virtual unsigned getCarrierDelay(IDelaysMgr::DelayAttr attr, unsigned carrierIndex, unsigned antenna) const override ;

protected:
    bool checkAttr(IDelaysMgr::DelayAttr attr) const;
    bool checkPathAttr(IDelaysMgr::DelayAttr attr, unsigned antenna) const;
    bool checkCarrierAttr(IDelaysMgr::DelayAttr attr, unsigned carrierIndex, unsigned antenna) const;

    bool checkDelay(IDelaysMgr::DelayAttr attr) const;
    bool checkPathDelay(IDelaysMgr::DelayAttr attr, unsigned antenna) const;
    bool checkCarrierDelay(IDelaysMgr::DelayAttr attr, unsigned carrierIndex, unsigned antenna) const;

    bool isNonPathAttr(IDelaysMgr::DelayAttr attr) const;
    bool isPathAttr(IDelaysMgr::DelayAttr attr) const;
    bool isCarrierAttr(IDelaysMgr::DelayAttr attr) const;
    bool isTxAttr(IDelaysMgr::DelayAttr attr) const;
    bool isRxAttr(IDelaysMgr::DelayAttr attr) const;

    void setError(const std::string& error) const ;

private:
    mutable Mutex	mMutex ;
    unsigned mNumTx ;
    unsigned mNumRx ;
    unsigned mNumCarriers ;
    mutable std::string mError ;

    // Flags
    std::map<IDelaysMgr::DelayAttr, bool> mNonPathAttr ;
    std::map<IDelaysMgr::DelayAttr, bool> mPathAttr ;
    std::map<IDelaysMgr::DelayAttr, bool> mCarrierAttr ;
    std::map<IDelaysMgr::DelayAttr, bool> mTxAttr ;
    std::map<IDelaysMgr::DelayAttr, bool> mRxAttr ;

	// delays
    unsigned mAdjDelayLimitDelayDown ;
    unsigned mAdjDelayLimitStepDown ;
    unsigned mAdjDelayLimitDelayUp ;
    unsigned mAdjDelayLimitStepUp ;

    std::map<IDelaysMgr::DelayAttr, unsigned> mDelays ;
    std::map<IDelaysMgr::DelayAttr, std::vector<unsigned>> mPathDelays ;
    std::map<IDelaysMgr::DelayAttr, std::vector<std::vector<SetVal<unsigned>>> > mCarrierDelays ;
    std::map<IDelaysMgr::DelayAttr, std::vector<unsigned>> mMidbandDelays ;

    // Hardware callbacks
    std::map<IDelaysMgr::DelayAttr, SetDelay> mHwDelayCallbacks ;
    std::map<IDelaysMgr::DelayAttr, SetAntDelay> mHwPathCallbacks ;
    std::map<IDelaysMgr::DelayAttr, SetCarrierDelay> mHwCarrierCallbacks ;

    // Application callbacks
    std::map<IDelaysMgr::DelayAttr, SetDelay> mAppDelayCallbacks ;
    std::map<IDelaysMgr::DelayAttr, SetAntDelay> mAppPathCallbacks ;
    std::map<IDelaysMgr::DelayAttr, SetCarrierDelay> mAppCarrierCallbacks ;

} ;

}

#endif /* DelaysMgr_H_ */
