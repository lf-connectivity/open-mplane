/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdVswrClient.h
 * \brief     Interface to a client Observer interested in DPD VSWR measurements
 *
 *
 * \details
 *
 */


#ifndef IDPDVSWRCLIENT_H_
#define IDPDVSWRCLIENT_H_

#include "Observer.hpp"
#include "data/IDpdVswr.h"


namespace Mplane {

class IDpdVswrClient : public Observer<IDpdVswrClient, const IDpdVswr&>
{
public:
	IDpdVswrClient() {}
	virtual ~IDpdVswrClient() {}

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IDpdVswrClient& subject) {}	// not used
    virtual void update(IDpdVswrClient& subject, const IDpdVswr& data) =0 ;

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const = 0;

} ;

}

#endif /* IDPDVSWRCLIENT_H_ */
