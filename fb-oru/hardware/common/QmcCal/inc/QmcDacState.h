/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcDacState.h
 * \brief     Store the DAC state
 *
 *
 * \details   Stores the state of the DAC so that the initial values can be restored. Normally restores
 * 				state on destruction, but will not if the "no restore" flag is set
 *
 */


#ifndef QMCDACSTATE_H_
#define QMCDACSTATE_H_

#include <memory>
#include <vector>
#include "QmcVal.h"

namespace Mplane {

class QmcDacState {
public:
	explicit QmcDacState(unsigned index) ;
	virtual ~QmcDacState() ;

	/**
	 * Do not restore state
	 */
	virtual void noRestore() ;

private:
	bool mRestore ;
	unsigned mIndex ;
	std::vector< std::shared_ptr<QmcVal> > mState ;
} ;

}

#endif /* QMCDACSTATE_H_ */
