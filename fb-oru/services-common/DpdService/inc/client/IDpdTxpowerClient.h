/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdTxpowerClient.h
 * \brief     Interface to a client Observer interested in DPD TX power measurements
 *
 *
 * \details
 *
 */


#ifndef IDPDTXPOWERCLIENT_H_
#define IDPDTXPOWERCLIENT_H_

#include "Observer.hpp"
#include "data/IDpdTxpower.h"


namespace Mplane {

class IDpdTxpowerClient : public Observer<IDpdTxpowerClient, const IDpdTxpower&>
{
public:
	IDpdTxpowerClient() {}
	virtual ~IDpdTxpowerClient() {}

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IDpdTxpowerClient& subject) {}	// not used
    virtual void update(IDpdTxpowerClient& subject, const IDpdTxpower& data) =0 ;

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const = 0;
} ;

}

#endif /* IDPDTXPOWERCLIENT_H_ */
