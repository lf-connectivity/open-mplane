/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Limits.hpp
 * \brief     DataVariant limits
 *
 *
 * \details
 *
 */


#ifndef LIMITS_HPP_
#define LIMITS_HPP_

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "Frequency.h"
#include "Power.h"
#include "SetVal.hpp"

namespace Mplane {

/**
 * Base conversion class
 */
class ValConvertBase {
public:
	explicit ValConvertBase(const std::string& unitsStr) :
		mOk(false), mUnitsStr(unitsStr) {}
	~ValConvertBase() {}

	bool isOk() const {return mOk;}

	// Handle special case where limit is being set via a variable
	// Variable must be in the form "${NAME}"
	static bool isVariable(const std::string& valstr)
	{
		// must consist of at least ${x}
		if (valstr.size() < 4)
			return false ;

		if ( (valstr[0] == '$') && (valstr[1] == '{') && (valstr.back() == '}') )
			return true ;

		return false ;
	}

	// Given variable (must be in the form "${NAME}") returns the "NAME" part
	static std::string variableName(const std::string& valstr)
	{
		if (!isVariable(valstr))
			return "" ;

		return valstr.substr(2, valstr.size()-3) ;
	}

protected:
	bool mOk ;
	std::string mUnitsStr ;
};

/**
 * Class for converting values
 */
template <typename T>
class ValConvert : public ValConvertBase {
public:
	explicit ValConvert<T>(const std::string& valstr, const std::string& unitsStr) : ValConvertBase(unitsStr) {}
	~ValConvert<T>() {}
	T val() const {return T();}
};

/**
 * Specialised template for value conversion: float
 */
template <>
class ValConvert<float> : public ValConvertBase {
public:
	ValConvert<float>(const std::string& valstr, const std::string& unitsStr) : ValConvertBase(unitsStr), mVal(0.0) {

		mOk=true ;
		try {
			mVal = std::stof(valstr) ;
			mOk=true ;
		}
		catch(...) {
			mOk = isVariable(valstr) ;
		}
	}
	~ValConvert<float>() {}
	float val() const {return mVal;}

private:
	float mVal ;
};

/**
 * Specialised template for value conversion: integer
 */
template <>
class ValConvert<int> : public ValConvertBase {
public:
	ValConvert<int>(const std::string& valstr, const std::string& unitsStr) : ValConvertBase(unitsStr), mVal(0.0) {

		try {
			mVal = static_cast<int>(std::stol(valstr)) ;
			mOk=true ;
		}
		catch(...) {
			mOk = isVariable(valstr) ;
		}
	}
	~ValConvert<int>() {}
	int val() const {return mVal;}

private:
	int mVal ;
};

/**
 * Specialised template for value conversion: unsigned integer
 */
template <>
class ValConvert<unsigned> : public ValConvertBase {
public:
	ValConvert<unsigned>(const std::string& valstr, const std::string& unitsStr) : ValConvertBase(unitsStr), mVal(0.0) {

		try {
			mVal = static_cast<unsigned>(std::stol(valstr)) ;
			mOk=true ;
		}
		catch(...) {
			mOk = isVariable(valstr) ;
		}
	}
	~ValConvert<unsigned>() {}
	unsigned val() const {return mVal;}

private:
	unsigned mVal ;
};

/**
 * Specialised template for value conversion: Frequency
 */
template <>
class ValConvert<Frequency> : public ValConvertBase {
public:
	ValConvert<Frequency>(const std::string& valstr, const std::string& unitsStr) : ValConvertBase(unitsStr), mVal(0.0) {

		mOk=true ;
		try {
			mVal = Frequency(std::stod(valstr), Frequency::str2unit(mUnitsStr)) ;
			mOk=true ;
		}
		catch(...) {
			mOk = isVariable(valstr) ;
		}
	}
	~ValConvert<Frequency>() {}
	Frequency val() const {return mVal;}

private:
	Frequency mVal ;
};

/**
 * Specialised template for value conversion: Power
 */
template <>
class ValConvert<Power> : public ValConvertBase {
public:
	ValConvert<Power>(const std::string& valstr, const std::string& unitsStr) : ValConvertBase(unitsStr), mVal(0.0) {

		mOk=true ;
		try {
			mVal = Power(std::stod(valstr), Power::str2unit(mUnitsStr)) ;
			mOk=true ;
		}
		catch(...) {
			mOk = isVariable(valstr) ;
		}
	}
	~ValConvert<Power>() {}
	Power val() const {return mVal;}

private:
	Power mVal ;
};

/**
 * Generic limit value template
 */
template <typename T>
class LimitVal {
public:
	LimitVal<T>() : mVal(), mValStr(""), mIsVariable(false) {}
	explicit LimitVal<T>(const LimitVal<T>& other) :
		mVal(other.mVal),
		mValStr(other.mValStr),
		mIsVariable(other.mIsVariable)
	{}
	virtual ~LimitVal<T>() {}

	LimitVal<T>& operator=(const LimitVal<T> & rhs)
	{
		mVal = rhs.mVal ;
		mValStr = rhs.mValStr ;
		mIsVariable = rhs.mIsVariable ;
	    return *this;
	}

	void set(T val, const std::string& valStr) {
		mVal = val ;
		mValStr = valStr ;
		mIsVariable = ValConvertBase::isVariable(valStr) ;
	}

	void clear() {
		mVal.clear() ;
		mValStr = "" ;
		mIsVariable = false ;
	}

	T get() const { return mVal.get(); }
	std::string getStr() const { return mValStr; }
	bool isSet() const { return mVal.isSet(); }
	bool isVariable() const { return mIsVariable; }


	void swap(LimitVal<T>& other)
	{
		using std::swap;
		swap(mVal, other.mVal) ;
		swap(mValStr, other.mValStr) ;
	}


private:
	SetVal<T> mVal ;
	std::string mValStr ;
	bool mIsVariable ;
} ;


/**
 * Generic limits template (uses ValConvert class for value conversion)
 */
template <typename T>
class Limits {
public:
	Limits<T>() : mMin(), mMax(), mStep(), mUnitsStr("") {}
	Limits<T>(const Limits<T>& other) :
		mMin(other.mMin),
		mMax(other.mMax),
		mStep(other.mStep),
		mUnitsStr(other.mUnitsStr)
	{}
	virtual ~Limits<T>() {}

	/**
	 * Assignment
	 * @param rhs
	 * @return this after assignment
	 */
	Limits<T>& operator=(const Limits<T> & rhs)
	{
		mMin = rhs.mMin ;
		mMax = rhs.mMax ;
		mStep = rhs.mStep ;
		mUnitsStr = rhs.mUnitsStr ;
	    return *this;
	}


	/**
	 * Sets the limits based on a string. String will be in the form:
	 *
	 * 	  min..max/step
	 *
	 * 	Where all but one of the parameters is optional at any one time. So the following are valid:
	 *
	 * 	  ..max/step
	 * 	  min../step
	 * 	  /step
	 * 	  min..
	 * 	  ..max
	 *
	 * @param limitsStr
	 * @return true if string is in a valid format and the limits have been set accordingly
	 */
	bool set(const std::string& limitsStr) {

		mMin.clear() ;
		mMax.clear() ;
		mStep.clear() ;

		std::size_t rangePos(limitsStr.find("..")) ;
		std::size_t stepPos(limitsStr.find("/")) ;

		// handle min/max range
		if (rangePos != std::string::npos)
		{
			std::string minStr(limitsStr.substr(0, rangePos)) ;
			std::string maxStr ;

			rangePos+=2 ;
			if (stepPos != std::string::npos)
				maxStr = limitsStr.substr(rangePos, stepPos-rangePos) ;
			else
				maxStr = limitsStr.substr(rangePos) ;

			if (!minStr.empty())
			{
				ValConvert<T> conv(minStr, mUnitsStr) ;
				if (conv.isOk())
					mMin.set(conv.val(), minStr) ;
			}
			if (!maxStr.empty())
			{
				ValConvert<T> conv(maxStr, mUnitsStr) ;
				if (conv.isOk())
					mMax.set(conv.val(), maxStr) ;
			}
		}

		// handle step
		if (stepPos != std::string::npos)
		{
			std::string stepStr(limitsStr.substr(stepPos+1)) ;
			if (!stepStr.empty())
			{
				ValConvert<T> conv(stepStr, mUnitsStr) ;
				if (conv.isOk())
					mStep.set(conv.val(), stepStr) ;
			}
		}

		// fail if nothing set
		if (!mMin.isSet() && !mMax.isSet() && !mStep.isSet())
			return false ;

		// Check max & min are the correct way round
		if (mMin.isSet() && mMax.isSet() && !mMin.isVariable() && !mMax.isVariable())
		{
			if (mMin.get() > mMax.get())
			{
				mMin.swap(mMax) ;
			}
		}

		return true ;
	}

	/**
	 * Set limits using individual strings for min/max/step
	 * @param minStr
	 * @param maxStr
	 * @param stepStr
	 * @return true if string is in a valid format and the limits have been set accordingly
	 */
	bool set(const std::string& minStr, const std::string& maxStr, const std::string& stepStr) {
		return set(minStr+".."+maxStr+"/"+stepStr) ;
	}

	/**
	 * Set a units string. If set, must be done so before setting any limits
	 * @param unitsStr
	 */
	void setUnits(const std::string& unitsStr) {
		mUnitsStr = unitsStr ;
	}

	/**
	 * Check the value against any of the set limits
	 * @param val
	 * @param error string set to reason for error
	 * @return true if value is within limits; false otherwise
	 */
	bool check(T val, std::string& error) const {

		std::stringstream ss ;
		error = "" ;

		if (mMin.isSet())
		{
			if (val < mMin.get())
			{
				ss << "less than minimum " << mMin.get() ;
				error = ss.str() ;
				return false ;
			}
		}

		if (mMax.isSet())
		{
			if (val > mMax.get())
			{
				ss << "greater than maximum " << mMax.get() ;
				error = ss.str() ;
				return false ;
			}
		}

		return true ;
	}

	/**
	 * Overload that just checks the value and discards error string
	 * @param val
	 * @return true if checks ok
	 */
	bool check(T val) const {
		std::string error ;
		return check(val, error) ;
	}

	/**
	 * Check the value against any of the set limits
	 * @param val
	 * @return true if value is within limits; false otherwise
	 */
	void show(std::ostream& os = std::cout) const {

		if (mMin.isSet())
			os << mMin.getStr() ;

		if (mMin.isSet() || mMax.isSet())
			os << ".." ;

		if (mMax.isSet())
			os << mMax.getStr() ;

		if (mStep.isSet())
			os << "/" << mStep.getStr() ;
	}

	/**
	 * Get minimum setting as a string
	 * @return minimum or empty string if not set
	 */
	std::string getMin() const { return mMin.getStr() ; }

	/**
	 * Get maximum setting as a string
	 * @return maximum or empty string if not set
	 */
	std::string getMax() const { return mMax.getStr() ; }

	/**
	 * Get step setting as a string
	 * @return step or empty string if not set
	 */
	std::string getStep() const { return mStep.getStr() ; }

private:
	LimitVal<T> mMin ;
	LimitVal<T> mMax ;
	LimitVal<T> mStep ;
	std::string mUnitsStr ;
} ;

}


/**
 * @brief Make Limits a printable object for debug
 * @param out ostream
 * @param Limits object to print
 * @return ostream
 */
template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Mplane::Limits<T>& limits)
{
	std::stringstream ss ;
	limits.show(ss) ;
	out << ss.str() ;
	return out ;
}

#endif /* LIMITS_HPP_ */
