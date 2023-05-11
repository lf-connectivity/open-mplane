/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvAccess.h
 * \brief     Virtual interface to DataVariant type access methods
 *
 *
 * \details   Virtual interface that provides methods to convert to/from specific type from/to a common type.
 * 			  To support all possible types, we need the common "type" to be either an array of long long or an array of double
 *
 */


#ifndef IDVACCESS_H_
#define IDVACCESS_H_

#include <vector>

namespace Mplane {

class IDvAccess {
public:
	IDvAccess() {}
	virtual ~IDvAccess() {}

	using InterInt = long long ;
	using InterFloat = double ;

	/**
	 * Convert from specific type to intermediate type
	 */
	virtual InterInt toInterInt() const =0 ;

	/**
	 * Convert from specific type to intermediate type
	 */
	virtual InterFloat toInterFloat() const =0 ;

	/**
	 * Convert from intermediate type to specific type
	 * @param value
	 * @return false on error
	 */
	virtual bool fromInterInt(const InterInt& value) =0 ;

	/**
	 * Convert from intermediate type to specific type
	 * @param value
	 * @return false on error
	 */
	virtual bool fromInterFloat(const InterFloat& value) =0 ;

    /**
     * Set value using string
     * @param value
     * @return true if value string is valid
     */
    virtual bool set(const std::string& value) =0 ;

    /**
     * Method returns the current value of the variant as a string
     *
     * @return variant value as a string
     */
    virtual std::string toString() const =0 ;

} ;

}

#endif /* IDVACCESS_H_ */
