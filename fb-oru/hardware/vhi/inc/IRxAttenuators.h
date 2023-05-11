/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRxAttenuators.h
 * \brief     Virtual interface to access the RX attenuators
 *
 *
 * \details
 *
 */


#ifndef IRXATTENUATORS_H_
#define IRXATTENUATORS_H_

#include <memory>
#include "IAttenuator.h"

namespace Mplane {

class IRxAttenuators {
public:
	IRxAttenuators() {}
	virtual ~IRxAttenuators() {}

	/**
	 * Access singleton
	 * @param port 0-based RX port index
	 */
	static std::shared_ptr<IRxAttenuators> getInstance(unsigned port) ;


    /*! \brief  Get the Rx IF attenuator
     *
     *  Used to access the Rx IF attenuator object
     *
     *  \return IF attenuator object
     */
    virtual std::shared_ptr<IAttenuator> getIfAttenuator() =0 ;

    /*! \brief  Get the Rx RF attenuator
     *
     *  Used to access the Rx RF attenuator object
     *
     *  \return IF attenuator object
     */
    virtual std::shared_ptr<IAttenuator> getRfAttenuator() =0 ;
} ;

}

#endif /* IRXATTENUATORS_H_ */
