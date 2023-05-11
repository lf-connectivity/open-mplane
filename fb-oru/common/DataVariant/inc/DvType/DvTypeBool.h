/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeBool.h
 * \brief     Represents DataVariant type "BOOL"
 *
 *
 * \details   This is a special case of ENUM where there are only 2 enumeration values that represent true and false
 *
 */


#ifndef DvTypeBool_H_
#define DvTypeBool_H_

#include "IDvBool.h"
#include "DvTypeEnum.h"

namespace Mplane {

class DvTypeBool : public virtual IDvBool, public DvTypeEnum {
public:
	using super = DvTypeEnum ;

	explicit DvTypeBool(const std::string& typeStr = "") ;
	virtual ~DvTypeBool() ;

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
     * Get the DataVariant type as a string, ie, INT, FLOAT, HEXINT, STRING, ENUM
     * @return variant type as a string
     */
    virtual const std::string getTypeStr() const override ;

    /**
     * Get the DataVariant type
     * @return variant type
     */
    virtual const DataVariantType::Type getType() const override ;


    // IDvBool

    /**
     * Set the value of the the variant to the float value.
     *
     * @param value
     */
    virtual bool setBool( bool value ) override ;

    /**
     * Method returns the current variant value as a bool
     *
     * @return variant value as a bool
     */
    virtual bool toBool() const override ;


    // IDvAccess interface

    /**
     * Set value using string
     * @param value
     * @return true if value string is valid
     */
    virtual bool set(const std::string& value) override ;

} ;

}

#endif /* DvTypeBool_H_ */
