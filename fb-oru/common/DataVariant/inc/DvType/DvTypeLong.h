/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeLong.h
 * \brief     Represents DataVariant type "LONG"
 *
 *
 * \details
 *
 */


#ifndef DvTypeLong_H_
#define DvTypeLong_H_

#include "IDvLong.h"
#include "DvTypeBase.h"

namespace Mplane {

class DvTypeLong : public virtual IDvLong, public DvTypeBase {
public:
	explicit DvTypeLong(const std::string& typeStr = "") ;
	virtual ~DvTypeLong() ;

    /**
     * Can this type have units (e.g. KHz)
     */
    virtual bool canHaveUnits() const override ;

    /**
     * Can we set the value of this particular type using the specified string?
     * @param value string
     * @return true if the value string is valid for setting this type
     */
    virtual bool canSetValue(const std::string& value) const override ;

    /**
     * Can we set this particular type using the specified string?
     * @param type string
     * @return true if the type string is valid for setting this type
     */
    virtual bool canSetType(const std::string& type) const override ;


    /**
     * Clears out any current value
     */
    virtual void clear() override ;

    /**
     * Get the DataVariant type as a string, ie, INT, LONG, HEXINT, STRING, ENUM
     * @return variant type as a string
     */
    virtual const std::string getTypeStr() const override ;

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
     * Get the DataVariant type
     * @return variant type
     */
    virtual const DataVariantType::Type getType() const override ;

    /**
     * Sets limits for either an INT or LONG type ; does nothing for any other type
     * @param limitsStr	String in the format "min..max/step"
     * @return true if set ok (or type not INT/LONG); false on error
     */
    virtual bool setLimits(const std::string& limitsStr)  override ;

    /**
     * Set limits from min/max/step strings
     * @param minStr
     * @param maxStr
     * @param stepStr
     * @return true if set ok (or type not INT/LONG); false on error
     */
    virtual bool setLimits(const std::string& minStr, const std::string& maxStr, const std::string& stepStr)  override ;

    /**
     * Check the INT/LONG type current value against any set limits. Note that this method may adjust the value
     * based on the limits setting.
     * @return false if INT/LONG value does not match limits; true otherwise
     */
    virtual bool checkLimits(std::string& error)  override ;


    // IDvLong

    /**
     * Method returns the current variant value as a long long
     *
     * @return variant value as a long long.
     */
    virtual long long toLong() const override ;

    /**
     * Set the value of the variant to the long long value. If the variant is
     * type Int, the value is cast to an integer internally.
     *
     * @param value
     */
    virtual bool setLong( long long value ) override ;

    // IDvAccess

    /**
     * Set value using string
     * @param value
     * @return true if value string is valid
     */
    virtual bool set(const std::string& value) override ;

	/**
	 * Convert from specific type to intermediate type
	 */
	virtual IDvAccess::InterInt toInterInt() const override ;

	/**
	 * Convert from specific type to intermediate type
	 */
	virtual IDvAccess::InterFloat toInterFloat() const override ;

	/**
	 * Convert from intermediate type to specific type
	 * @param value
	 * @return false on error
	 */
	virtual bool fromInterInt(const IDvAccess::InterInt& value) override ;

	/**
	 * Convert from intermediate type to specific type
	 * @param value
	 * @return false on error
	 */
	virtual bool fromInterFloat(const IDvAccess::InterFloat& value) override ;


private:
    long long mLong;		//<! LONG

    Limits<long long>		mLimits ;
} ;

}

#endif /* DvTypeLong_H_ */
