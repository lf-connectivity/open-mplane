/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITestDpdVswrClient.h
 * \brief     Interface to a client Observer interested in DPD VSWR measurements
 *
 *
 * \details
 *
 */


#ifndef ITestDpdVswrClient_H_
#define ITestDpdVswrClient_H_

#include "Observer.hpp"
#include "data/ITestDpdVswr.h"


namespace Mplane {

class ITestDpdVswrClient : public Observer<ITestDpdVswrClient, const ITestDpdVswr&>
{
public:
	ITestDpdVswrClient() {}
	virtual ~ITestDpdVswrClient() {}

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(ITestDpdVswrClient& subject) {}	// not used
    virtual void update(ITestDpdVswrClient& subject, const ITestDpdVswr& data) =0 ;

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const = 0;

} ;

}

#endif /* ITestDpdVswrClient_H_ */
