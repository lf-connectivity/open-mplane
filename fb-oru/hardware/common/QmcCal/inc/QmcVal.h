/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcVal.h
 * \brief     A single value of stored radio state
 *
 *
 * \details   Base class that provides the common interface for this saved state class. This class is
 * 				used to read a current setting from the radio (e.g. frequency, attenuation etc), store that
 * 				value and then restore the setting at a later time (once QMC cal is complete)
 *
 */


#ifndef QMCVAL_H_
#define QMCVAL_H_


namespace Mplane {

class QmcVal {
public:
	QmcVal() ;
	virtual ~QmcVal() ;

	/**
	 * Save the state of a value
	 * @return true if saved ok
	 */
	virtual bool save() ;

	/**
	 * Restore the state of a value
	 * @return true if restored ok
	 */
	virtual bool restore() ;

	/**
	 * Has the state been successfully saved for this value
	 * @return true if saved
	 */
	virtual bool isSaved() const ;

protected:
	void setSaved() ;

private:
	bool mSaved ;
} ;

}

#endif /* QMCVAL_H_ */
