/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcValType.hpp
 * \brief     Template class for saving/restoring any value type
 *
 *
 * \details
 *
 */


#ifndef QMCVALTYPE_HPP_
#define QMCVALTYPE_HPP_

#include <functional>
#include "QmcVal.h"

namespace Mplane {

/**
 * Template class that stores a single value of type T so that it can be restored
 */
template <class T>
class QmcValType : public QmcVal {
public:
	using GetFunc = std::function<T()> ;
	using SetFunc = std::function<bool(const T&)> ;

	QmcValType(GetFunc getFunc, SetFunc setFunc) :
		QmcVal(),
		mValue(),
		mGetFunc(getFunc),
		mSetFunc(setFunc)
	{
	}

	virtual ~QmcValType()
	{
	}

	/**
	 * Save the state of a value
	 * @return true if saved ok
	 */
	virtual bool save() override
	{
		mValue = mGetFunc() ;
		setSaved() ;
		return true ;
	}

	/**
	 * Restore the state of a value
	 * @return true if restored ok
	 */
	virtual bool restore() override
	{
		if (!isSaved())
			return false ;

		return mSetFunc(mValue) ;
	}

	/**
	 * Utility for setting any value (using the set func)
	 * @return true if restored ok
	 */
	virtual bool setVal(T value)
	{
		return mSetFunc(value) ;
	}

private:
	T mValue ;
	GetFunc mGetFunc ;
	SetFunc mSetFunc ;
} ;

/**
 * Template class that stores a pair of values of type T so they can be restored
 */
template <class T>
class QmcValPairType : public QmcVal {
public:
	using GetPairFunc = std::function<void(T&, T&)> ;
	using SetPairFunc = std::function<bool(const T& a, const T&)> ;

	QmcValPairType(GetPairFunc getFunc, SetPairFunc setFunc) :
		QmcVal(),
		mValueA(),
		mValueB(),
		mGetPairFunc(getFunc),
		mSetPairFunc(setFunc)
	{
	}

	virtual ~QmcValPairType()
	{
	}

	/**
	 * Save the state of a value
	 * @return true if saved ok
	 */
	virtual bool save() override
	{
		mGetPairFunc(mValueA, mValueB) ;
		setSaved() ;
		return true ;
	}

	/**
	 * Restore the state of a value
	 * @return true if restored ok
	 */
	virtual bool restore() override
	{
		if (!isSaved())
			return false ;

		return mSetPairFunc(mValueA, mValueB) ;
	}

private:
	T mValueA ;
	T mValueB ;
	GetPairFunc mGetPairFunc ;
	SetPairFunc mSetPairFunc ;
} ;

}

#endif /* QMCVALTYPE_HPP_ */
