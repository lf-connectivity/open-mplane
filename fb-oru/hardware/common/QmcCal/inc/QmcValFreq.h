/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcValFreq.h
 * \brief     Save/restore frequency setting
 *
 *
 * \details
 *
 */


#ifndef QMCVALFREQ_H_
#define QMCVALFREQ_H_

#include <functional>
#include "Frequency.h"
#include "QmcVal.h"

namespace Mplane {

class QmcValFreq : public QmcVal {
public:
	using FreqSaveFunc = std::function<Frequency()> ;
	using FreqRestoreFunc = std::function<void(const Frequency&)> ;

	QmcValFreq(FreqSaveFunc saveFunc, FreqRestoreFunc restoreFunc) ;
	virtual ~QmcValFreq() ;

	/**
	 * Save the state of a value
	 * @return true if saved ok
	 */
	virtual bool save() override ;

	/**
	 * Restore the state of a value
	 * @return true if restored ok
	 */
	virtual bool restore() override ;

private:
	Frequency mValue ;
	FreqSaveFunc mSaveFunc ;
	FreqRestoreFunc mRestoreFunc ;
} ;

}

#endif /* QMCVALFREQ_H_ */
