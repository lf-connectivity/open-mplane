/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcState.h
 * \brief     Save/restore radio state
 *
 *
 * \details   RAII object that saves the current radio state when created, and restores that state when destroyed
 *
 */


#ifndef QMCSTATE_H_
#define QMCSTATE_H_

#include <vector>
#include "QmcVal.h"
#include "QmcAttenState.h"

namespace Mplane {

class QmcState {
public:
	explicit QmcState(unsigned index) ;
	virtual ~QmcState() ;

private:
	unsigned mIndex ;
	std::vector< std::shared_ptr<QmcVal> > mState ;
	std::shared_ptr<QmcAttenState> mAttenState ;
} ;

}

#endif /* QMCSTATE_H_ */
