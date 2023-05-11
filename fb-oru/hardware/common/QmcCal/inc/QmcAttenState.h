/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcAttenState.h
 * \brief     Attenuator state
 *
 *
 * \details
 *
 */


#ifndef QMCATTENSTATE_H_
#define QMCATTENSTATE_H_

#include <memory>
#include <vector>
#include "QmcVal.h"

namespace Mplane {

class QmcAttenState {
public:
	explicit QmcAttenState(unsigned index) ;
	virtual ~QmcAttenState() ;

	/**
	 * Set attenuators to maximum
	 * @return true if set ok
	 */
	bool maxAtten() ;

private:
	unsigned mIndex ;
	std::vector< std::shared_ptr<QmcVal> > mState ;
} ;

}

#endif /* QMCATTENSTATE_H_ */
