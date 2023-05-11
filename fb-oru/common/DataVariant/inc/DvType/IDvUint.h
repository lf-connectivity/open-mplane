/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvUint.h
 * \brief     Virtual interface to UINT type
 *
 *
 * \details   Interface provides the conversion to/from the specific type (UINT)
 *
 */


#ifndef IDvUint_H_
#define IDvUint_H_


namespace Mplane {

class IDvUint {
public:
	IDvUint() {}
	virtual ~IDvUint() {}

    /**
     * Set the value of the the variant to the unsigned value.
     *
     * @param value
     */
    virtual bool setUint( unsigned value ) =0 ;

    /**
     * Method returns the current variant value as a unsigned
     *
     * @return variant value as a unsigned
     */
    virtual unsigned toUint() const =0 ;
} ;

}

#endif /* IDvUint_H_ */
