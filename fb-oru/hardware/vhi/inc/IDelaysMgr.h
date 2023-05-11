/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDelaysMgr.h
 * \brief     Defines interface for system delay adjustment
 *
 *
 * \details   Defines the interface with the system delays. Some of the delays are set up by the BBU and others
 * are calculated by the RRH. This interface defines the mechanism for the RRH to be notified of incoming delay
 * changes and also the mechanism for it to set delays it has calculated.
 *
 * Delay change notification is by means of callback functors which are passed the appropriate information in
 * the call to an object method.
 *
 * There are effectively 2 sides: the hardware side that actually implements the delays, and the application side which
 * can change delays and read them.
 *
 * Both sides use the same method to read the delays. Each side has it's own group of methods for setting the delays. Both
 * sides can also register their own callbacks to be notified of changes caused by the other side.
 *
 *
 */


#ifndef IDelaysMgr_H_
#define IDelaysMgr_H_

#include <iostream>
#include <memory>
#include <functional>
#include <string>

namespace Mplane {



class IDelaysMgr {
public:

	using SetDelay = std::function<bool(unsigned delay)> ;
	using SetAntDelay = std::function<bool(unsigned antenna, unsigned delay)> ;
	using SetCarrierDelay = std::function<bool(unsigned carrierIndex, unsigned antenna, unsigned delay)> ;

	// The complete set of valid delays
	enum DelayAttr {
		DELAY_NONE		= 0,

		OFFSET_DELAY	= 1,
		FRAMEDIFF		= 2,
		THRUDELAY_UP	= 3,
		THRUDELAY_DOWN	= 4,

		EXTDELAY_UP		= 5,
		EXTDELAY_DOWN	= 6,

		ANTDELAY_UP		= 7,
		ANTDELAY_DOWN	= 8,
		ADJDELAY_UP		= 9,
		ADJDELAY_DOWN	= 10,
		FRAMEOFF_UP		= 11,
		FRAMEOFF_DOWN	= 12,
		T12				= 13,
		CPRI_DOWN		= 14,
		CPRI_UP			= 15,
		CPRI_FRAME_RX	= 16,
		CPRI_FRAME_TX	= 17,

	};

	// Singleton
	static std::shared_ptr<IDelaysMgr> getInterface() ;

	/**
	 * Returns the string name of the delay attribute
	 * @param attr
	 * @return string name of attribute
	 */
	static std::string attrString(DelayAttr attr) ;

	/**
	 * Show contents
	 * @param os
	 */
	virtual void show(std::ostream& os = std::cout) const =0 ;

	/**
	 * On any failure the error string is set with the failure reason. This method returns that string and clears it
	 * @return failure reason
	 */
	virtual std::string getError() =0 ;


	// HARDWARE INTERFACE

	/**
	 * Clear out all settings (mainly used for testing)
	 * @return true if reset ok
	 */
	virtual bool reset() =0 ;

	/**
	 * The hardware side is responsible for initialising this object
	 * @param numTx
	 * @param numRx
	 * @param numCarriers
	 * @return true if initialised ok
	 */
	virtual bool initialise(unsigned numTx, unsigned numRx, unsigned numCarriers) =0 ;

	/**
	 * Hardware access for setting the delay
	 * @param attr		The delay attribute to set
	 * @param delay		Delay in ns
	 * @return true if set ok
	 */
	virtual bool hwSetDelay(DelayAttr attr, unsigned delay) =0 ;

	/**
	 * Hardware access for setting the delay on a particular antenna
	 * @param attr		The delay attribute to set
	 * @param antenna	0-based antenna number
	 * @param delay		Delay in ns
	 * @return true if set ok
	 */
	virtual bool hwSetPathDelay(DelayAttr attr, unsigned antenna, unsigned delay) =0 ;

	/**
	 * Hardware access for settings the carrier delay on a particular antenna
	 * @param attr			The delay attribute to set
	 * @param carrierIndex	0-based carrier index
	 * @param antenna		0-based antenna number
	 * @param delay			Delay in ns
	 * @return true if set ok
	 */
	virtual bool hwSetCarrierDelay(DelayAttr attr, unsigned carrierIndex, unsigned antenna, unsigned delay) =0 ;

	/**
	 * Set the midband carrier delays. A set of midband carrier delays are calculated for each antenna. This set of delays is then used
	 * for any carrier delay which hasn't yet been set.
	 * @param attr			The delay attribute to set
	 * @param carrierIndex	0-based carrier index
	 * @param delay			Delay in ns
	 * @return true if set ok
	 */
	virtual bool hwSetMidbandDelay(IDelaysMgr::DelayAttr attr, unsigned antenna, unsigned delay) =0 ;

	/**
	 * Hardware method for registering a callback on a delay changed by the application
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool hwRegisterDelayCallback(DelayAttr attr, SetDelay callback) =0 ;

	/**
	 * Hardware method for registering a callback on an antenna delay changed by the application
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool hwRegisterPathDelayCallback(DelayAttr attr, SetAntDelay callback) =0 ;

	/**
	 * Hardware method for registering a callback on a carrier delay changed by the application
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool hwRegisterCarrierDelayCallback(DelayAttr attr, SetCarrierDelay callback) =0 ;

	/**
	 * Unregister hardware callback for the attribute
	 * @param attr			The delay attribute to deregister
	 * @return
	 */
	virtual bool hwDeregisterCallback(DelayAttr attr) =0 ;

    /**
     * Hardware interface to set the frame diff in frames
     * @param frames
     * @return true if set
     */
    virtual bool hwSetFrameDiff(unsigned frames) =0 ;

    /**
     * Hardware interface to set the delay limits
     * @param delayDown
     * @param stepDown
     * @param delayUp
     * @param stepUp
     * @return true if set
     */
    virtual bool hwSetAdjDelayLimit(unsigned delayDown, unsigned stepDown, unsigned delayUp, unsigned stepUp) =0 ;


	// APPLICATION INTERFACE

	/**
	 * Application access for setting the delay
	 * @param attr		The delay attribute to set
	 * @param delay		Delay in ns
	 * @return true if set ok
	 */
	virtual bool appSetDelay(DelayAttr attr, unsigned delay) =0 ;

	/**
	 * Application access for setting the delay on a particular antenna
	 * @param attr		The delay attribute to set
	 * @param antenna	0-based antenna number
	 * @param delay		Delay in ns
	 * @return true if set ok
	 */
	virtual bool appSetPathDelay(DelayAttr attr, unsigned antenna, unsigned delay) =0 ;

	/**
	 * Application access for settings the carrier delay on a particular antenna
	 * @param attr			The delay attribute to set
	 * @param carrierIndex	0-based carrier index
	 * @param antenna		0-based antenna number
	 * @param delay			Delay in ns
	 * @return true if set ok
	 */
	virtual bool appSetCarrierDelay(DelayAttr attr, unsigned carrierIndex, unsigned antenna, unsigned delay) =0 ;

	/**
	 * Application method for registering a callback on a delay changed by the hardware
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool appRegisterDelayCallback(DelayAttr attr, SetDelay callback) =0 ;

	/**
	 * Application method for registering a callback on an antenna delay changed by the hardware
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool appRegisterPathDelayCallback(DelayAttr attr, SetAntDelay callback) =0 ;

	/**
	 * Application method for registering a callback on a carrier delay changed by the hardware
	 * @param attr			The delay attribute to monitor
	 * @param callback
	 * @return true if registered
	 */
	virtual bool appRegisterCarrierDelayCallback(DelayAttr attr, SetCarrierDelay callback) =0 ;

	/**
	 * Unregister application callback for the attribute
	 * @param attr			The delay attribute to deregister
	 * @return
	 */
	virtual bool appDeregisterCallback(DelayAttr attr) =0 ;


	// READ ACCESS

	/**
	 * Get the frame diff in frames
	 */
    virtual unsigned getFrameDiff() const =0 ;

    /**
     * Get the delay limits
     * @param delayDown
     * @param stepDown
     * @param delayUp
     * @param stepUp
     */
    virtual void getAdjDelayLimit(unsigned& delayDown, unsigned& stepDown, unsigned& delayUp, unsigned& stepUp) const =0 ;

    /**
     * Get the specified delay in ns
     * @param attr
     */
    virtual unsigned getDelay(DelayAttr attr) const =0 ;

    /**
     * Get the specified antenna delay in ns
     * @param attr
	 * @param antenna		0-based antenna number
     */
    virtual unsigned getPathDelay(DelayAttr attr, unsigned antenna) const =0 ;

    /**
     * Get the specified delay in ns
     * @param attr
	 * @param carrierIndex	0-based carrier index
	 * @param antenna		0-based antenna number
     */
    virtual unsigned getCarrierDelay(DelayAttr attr, unsigned carrierIndex, unsigned antenna) const =0 ;


	virtual ~IDelaysMgr() {}

};

}
#endif /* IDelaysMgr_H_ */
