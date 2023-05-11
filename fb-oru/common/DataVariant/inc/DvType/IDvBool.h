/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvBool.h
 * \brief     Virtual interface to BOOL type
 *
 *
 * \details   Interface provides the conversion to/from the specific type (BOOL)
 *
 */


#ifndef IDVBOOL_H_
#define IDVBOOL_H_


namespace Mplane {

class IDvBool {
public:
	IDvBool() {}
	virtual ~IDvBool() {}

    /**
     * Set the value of the the variant to the float value.
     *
     * @param value
     */
    virtual bool setBool( bool value ) =0 ;

    /**
     * Method returns the current variant value as a bool
     *
     * @return variant value as a bool
     */
    virtual bool toBool() const =0 ;

} ;

}

#endif /* IDVBOOL_H_ */
