/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IQmcCal.h
 * \brief     Virtual interface to QMC spot cal on a particular TX antenna
 *
 *
 * \details
 *
 */


#ifndef IQMCCAL_H_
#define IQMCCAL_H_

#include <memory>
#include <vector>
#include <string>

#include "Power.h"

namespace Mplane {

/**
 * The IQmcCal class provides the interface for performing spot QMC cal on a particular
 * TX port (set when the object is created)
 */
class IQmcCal {
public:
	IQmcCal() {}
	virtual ~IQmcCal() {}

	/**
	 * Get the 0-based TX port index
	 */
	virtual unsigned getIndex() const =0 ;

	/**
	 * Perform the calibration
	 * @return true on success
	 */
	virtual bool performCal() =0 ;

	/**
	 * Get the error string (if any)
	 * @return error string on error; empty string if no error
	 */
	virtual std::string error() =0 ;

	/**
	 * Get the carrier suppression figure from the last calibration
	 * @return
	 */
	virtual Power getCarrierSuppression() const =0 ;

	/**
	 * Get the image suppression figure from the last calibration
	 * @return
	 */
	virtual Power getImageSuppression() const =0 ;

	/**
	 * Either set the attenuators to minimum or leave at current setting during QMC
	 */
	enum AttenMode {
		ATTEN_MIN,    //!< ATTEN_MIN
		ATTEN_CURRENT,//!< ATTEN_CURRENT
	};
	virtual bool setAttenuatorMode(AttenMode attenMode) =0 ;

	/**
	 * Convert a string into the attenuator mode
	 * @param modestr
	 * @return mode
	 */
	static AttenMode strToAttenMode(const std::string& modestr) ;

} ;


/**
 * The IQmcCalFactory creates an IQmcCal instance for each of the TX ports
 */
class IQmcCalFactory
{
public:
    /**
     * Get the list of objects
     *
     * \return a vector containing maxPorts IQmcCal interface pointers.
     */
    static std::vector< std::shared_ptr<IQmcCal> > getList();

    /**
     * Get the single object at the specified index
     *
     * \return pointer to object or null if index is invalid
     */
    static std::shared_ptr<IQmcCal> get(unsigned index);
};


}

#endif /* IQMCCAL_H_ */
