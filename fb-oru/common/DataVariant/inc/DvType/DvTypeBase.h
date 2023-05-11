/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeBase.h
 * \brief     DataVariant type base class
 *
 *
 * \details
 *
 */


#ifndef DVTYPEBASE_H_
#define DVTYPEBASE_H_

#include <vector>
#include <sstream>

#include "IDvType.h"
#include "DataVariant/Limits.hpp"

namespace Mplane {

class DvTypeBase : public virtual IDvType {
public:
	explicit DvTypeBase(const std::string& typeStr = "") ;
	virtual ~DvTypeBase() ;

	// IDvType interface

    /**
     * Can this type have units (e.g. KHz)
     */
    virtual bool canHaveUnits() const override ;

    /**
     * Clears out any current value
     */
    virtual void clear() override ;

    /**
     * Has the value been initialised
     * @return true if the value has been initialised
     */
    virtual bool isSet() const override ;

    /**
     * Method used to return the data variant value string
     *
     * @return value string
     */
    virtual std::string getValue() const override ;


    /**
     * Get the DataVariant limits as a string, "{min..max/step}"
     * @return limits as a string
     */
    virtual const std::string getLimitsStr() const override ;

    /**
     * Get the DataVariant limits minimum setting as a string
     * @return minimum as a string or empty string if not set
     */
    virtual const std::string getLimitsMin() const override ;

    /**
     * Get the DataVariant limits maximum setting as a string
     * @return maximum as a string or empty string if not set
     */
    virtual const std::string getLimitsMax() const override ;

    /**
     * Get the DataVariant limits step setting as a string
     * @return step as a string or empty string if not set
     */
    virtual const std::string getLimitsStep() const override ;

    /**
     * Is the value hex
     * @return true if value is in hex
     */
    virtual const bool isHex() const override ;

    /**
     * Sets limits for either an INT or FLOAT type ; does nothing for any other type
     * @param limitsStr	String in the format "min..max/step"
     * @return true if set ok (or type not INT/FLOAT); false on error
     */
    virtual bool setLimits(const std::string& limitsStr)  override ;

    /**
     * Set limits from min/max/step strings
     * @param minStr
     * @param maxStr
     * @param stepStr
     * @return true if set ok (or type not INT/FLOAT); false on error
     */
    virtual bool setLimits(const std::string& minStr, const std::string& maxStr, const std::string& stepStr)  override ;

    /**
     * Check the INT/FLOAT type current value against any set limits. Note that this method may adjust the value
     * based on the limits setting.
     * @return false if INT/FLOAT value does not match limits; true otherwise
     */
    virtual bool checkLimits(std::string& error)  override ;
    virtual bool checkLimits()  override ;

    /**
     * Set the units string
     * @param units string representing the value units (e.g. "dB", "W", "kHz" etc)
     */
    virtual void setUnits(const std::string& units) override ;

    /**
     * Get the units string
     * @return units string (which may be empty)
     */
    virtual const std::string getUnits() const override ;


    // IDvAccess interface

    /**
     * Method returns the current value of the variant as a string
     *
     * @return variant value as a string
     */
    virtual std::string toString() const override ;


protected:
    // get the type string used to create this class
    std::string getInitialTypeStr() const ;

    // save the string setting
    void setStr(const std::string& str) ;
    void setStr(int ival) ;
    void setStr(float fval) ;
    void setStr(const IDvAccess::InterInt& ival) ;
    void setStr(const IDvAccess::InterFloat& fval) ;
    void setStr(const std::complex<float>& complex) ;

    // format the limits string
    template<class T>
    std::string formatLimits(const Limits<T>& limits) const
    {
    	std::stringstream ss ;

    	limits.show(ss) ;
    	if (!ss.str().empty())
    		return "{" + ss.str() + "}" ;

    	return "" ;
    }

    /**
     * If value string has been specified with some units, then remove those units and return them. The value is expected
     * to be integer or float
     * @param value int or float string with/without units suffix
     * @param units get set to the uniits if any are present; unaffected otherwise
     */
    virtual std::string unitsFromStr(const std::string& value) ;

public:
    static bool strIsHex(const std::string& value);
    static bool strIsNumber(const std::string& value);
    static bool strIsUnsigned(const std::string& value);
    static bool strIsInt(const std::string& value);
    static bool strIsFloat(const std::string& value);
    static bool strIsBool(const std::string& value);
    static bool strIsComplex(const std::string& value, std::complex<float>& complexVal);
    static bool strToBool(const std::string& value);

    static std::vector< std::string > strToEnum(const std::string& str);

    static std::string complexToStr(const std::complex<float>& complex) ;
    static std::string floatToStr(const IDvAccess::InterFloat& fval) ;
    static std::string intToStr(const IDvAccess::InterInt& ival) ;
    static std::string floatToStr(float fval) ;
    static std::string intToStr(int ival) ;

private:
    std::string mTypeStr ;
    bool mIsSet ;
    std::string mStr ;

    /**
     * Optional units string. Just used for display purposes. App can access the units string and use it in any way
     * it sees fit
     */
    std::string mUnits ;

} ;

}

#endif /* DVTYPEBASE_H_ */
