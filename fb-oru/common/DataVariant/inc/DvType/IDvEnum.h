/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvEnum.h
 * \brief     Virtual interface to ENUM type
 *
 *
 * \details   Interface provides the conversion to/from the specific type (ENUM)
 *
 */


#ifndef IDvEnum_H_
#define IDvEnum_H_


namespace Mplane {

class IDvEnum {
public:
	IDvEnum() {}
	virtual ~IDvEnum() {}

    /**
     * Set the value of the the variant to the integer value of the enumeration
     *
     * @param value
     */
    virtual bool setEnum( int value ) =0 ;

    /**
     * Method returns the current variant value as an integer (representing the enumeration value)
     *
     * @return variant value as an integer
     */
    virtual int toEnum() const =0 ;
} ;

}

#endif /* IDvEnum_H_ */
