/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeEnum.h
 * \brief     Represents DataVariant type "ENUM"
 *
 *
 * \details
 *
 */


#ifndef DvTypeEnum_H_
#define DvTypeEnum_H_

#include "DvTypeBase.h"

namespace Mplane {

class DvTypeEnum : public DvTypeBase {
public:
	explicit DvTypeEnum(const std::string& typeStr = "") ;
	virtual ~DvTypeEnum() ;

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
     * Get the DataVariant type as a string, ie, INT, FLOAT, HEXINT, STRING, ENUM
     * @return variant type as a string
     */
    virtual const std::string getTypeStr() const override ;

    /**
     * Get the DataVariant type
     * @return variant type
     */
    virtual const DataVariantType::Type getType() const override ;

    // IDvAccess interface

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


protected:
    // Set the enumeration list
    void setEnum(const std::vector< std::string >& enumList) ;

    // Set the enumeration value from a string
    bool setEnumValue(const std::string& valueStr) ;

    // Set the enumeration value from an unsigned int
    bool setEnumValue(unsigned value) ;

    // Get the enumeration index value
    unsigned getEnumValue() const ;

    // find the enumeration value in the list of valid values
    std::vector< std::string >::const_iterator findEnum(const std::string& value) const ;

    // return the enumeration list as a ':' separated string
    std::string getEnumStr() const ;

    // get the enumeration list
    std::vector< std::string > getEnum() const ;


private:
    unsigned mEnumIdx ;
    std::vector< std::string > mEnum ;	//<! ENUM
} ;

}

#endif /* DvTypeEnum_H_ */
