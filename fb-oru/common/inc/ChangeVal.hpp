/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ChangeVal.hpp
 * \brief     Value that tracks changes
 *
 *
 * \details   Template for any type/class that keeps track of changes to it's underlying value
 *
 */


#ifndef CHANGEVAL_HPP_
#define CHANGEVAL_HPP_

#include "SetVal.hpp"

namespace Mplane {

template<typename T>
class ChangeVal {
public:
	using value_type = T ;

	/**
	 * Default constructor
	 */
	ChangeVal<T>() :
		mVal(),
		mChanged(false)
	{}

	/**
	 * Construct with a value setting
	 */
	ChangeVal<T>(T val) :
		mVal(val),
		mChanged(false)
	{}

	/**
	 * Destroy
	 */
	virtual ~ChangeVal<T>() {}

	/**
	 * Copy constructor
	 */
	ChangeVal<T>(const ChangeVal<T>& other) :
		mVal(other.mVal),
		mChanged(other.mChanged)
	{}

	/**
	 * Assignment constructor. If the new value is set then copy the value AND it's change status; otherwise
	 * leave the current value unchanged
	 * @param rhs
	 * @return
	 */
	ChangeVal<T>& operator=(const ChangeVal<T> & rhs)
	{
		// When assigning from another ChangeVal treat it like a copy constructor
		if (rhs.isSet())
		{
			mVal = rhs.mVal ;
			mChanged = rhs.mChanged ;
		}
	    return *this;
	}

	/**
	 * Assignment from value
	 * @param val
	 * @return
	 */
	ChangeVal<T>& operator=(const T & val)
	{
		set(val) ;
	    return *this;
	}

	/**
	 * Compare with value
	 * @param val
	 * @return
	 */
	bool operator==(const T & val)
	{
		return mVal == val ;
	}

	/**
	 * Compare with ChangeVal<T>
	 * @param rhs
	 * @return
	 */
	bool operator==(const ChangeVal<T> & rhs)
	{
		return mVal == rhs.mVal ;
	}

	/**
	 * Set the value
	 * @param val
	 */
	void set(T val) {
		if ( mVal.operator==(val) )
		{
			mChanged = false ;
		}
		else
		{
			mVal = val ;
			mChanged = true ;
		}
	}

	/**
	 * Accept any change
	 */
	void acceptChange() {
		mChanged = false ;
	}

	/**
	 * Accessor
	 * @return
	 */
	T get() const {
		return mVal.get();
	}

	/**
	 * Determine whether value is set
	 */
	bool isSet() const { return mVal.isSet(); }

	/**
	 * Determine whether value is changed
	 */
	bool isChanged() const { return mChanged; }

	/**
	 * Provide a swap
	 * @param other
	 */
	void swap(ChangeVal<T>& other)
	{
		using std::swap;
		swap(mVal, other.mVal) ;
		swap(mChanged, other.mChanged) ;
	}

	/**
	 * Display the value - shows UNSET if the value is not yet set, appends a '*' if the value has changed
	 * @param os Output stream
	 */
	void show(std::ostream& os) const
	{
		os << mVal ;
		if (mChanged)
			os << "*" ;
	}

private:
	SetVal<T>	mVal ;
	bool 		mChanged ;
} ;

/**
 * Make swap available as a std::swap overload
 * @param a
 * @param b
 */
template<typename T>
void swap(ChangeVal<T>& a, ChangeVal<T>& b)
{
	a.swap(b) ;
}

}

// Make ChangeVal printable
template<typename T>
inline std::ostream& operator << (std::ostream& os, const Mplane::ChangeVal<T>& val)
{
	val.show(os) ;
	return os;
}


#endif /* CHANGEVAL_HPP_ */
