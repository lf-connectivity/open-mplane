/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPaprChange.h
 * \brief     Interface for monitoring changes in PAPR value
 *
 *
 * \details   This interface provides an interface for monitoring the target PAPR and when it changes.
 *
 */


#ifndef IPAPRCHANGE_H_
#define IPAPRCHANGE_H_

#include <memory>
#include <vector>
#include "Power.h"

namespace Mplane {

/** PAPR Change object - empty class used just to select the correct template
 *
 */
class IPaprChange {
} ;

/** PAPR change data
 *
 */
class IPaprData {
public:
	IPaprData() {}
	virtual ~IPaprData() {}

	// Get the TX port for this change [0..MAX_TX_PORTS-1]
	virtual unsigned getTxPort() const =0 ;

	// Get the PAPR
	virtual Power getPapr() const =0 ;
};

/** The subject class
 *
 */
class IPaprSubject {
public:
	IPaprSubject() {}
	virtual ~IPaprSubject() {}
};

/** The observer class
 *
 */
class IPaprObserver {
public:
	IPaprObserver() {}
	virtual ~IPaprObserver() {}

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IPaprSubject& subject, const IPaprData& data) =0 ;
};


/**
 * Get the list of subjects, one per TX port
 */
class IPaprFactory
{
public:

    /**
     * \return a vector containing PAPR subject interface pointers, one for each TX port.
     */
    static std::vector< std::shared_ptr<IPaprSubject> > getPaprSubjects( );
};

}

#endif /* IPAPRCHANGE_H_ */
