/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdInfoClient.h
 * \brief     Interface to a client Observer interested in DPD information (*NOT* DPD alarm)
 *
 *
 * \details
 *
 */


#ifndef IDPDINFOCLIENT_H_
#define IDPDINFOCLIENT_H_

#include "Observer.hpp"
#include "data/IDpdInfo.h"

namespace Mplane {

class IDpdInfoClient : public Observer<IDpdInfoClient, const IDpdInfo&>
{
public:
	IDpdInfoClient() {}
	virtual ~IDpdInfoClient() {}

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the RadioState within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IDpdInfoClient> getInstance( void );

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IDpdInfoClient& subject) {}	// not used
    virtual void update(IDpdInfoClient& subject, const IDpdInfo& data) =0 ;

    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const = 0;

} ;

}

#endif /* IDPDINFOCLIENT_H_ */
