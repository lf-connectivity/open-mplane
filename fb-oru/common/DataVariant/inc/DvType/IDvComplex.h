/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDvComplex.h
 * \brief     Virtual interface to COMPLEX type
 *
 *
 * \details   Interface provides the conversion to/from the specific type (COMPLEX)
 *
 */


#ifndef IDVCOMPLEX_H_
#define IDVCOMPLEX_H_

#include <complex>

namespace Mplane {

class IDvComplex {
public:
	IDvComplex() {}
	virtual ~IDvComplex() {}

    /**
     * Set the value of the the variant to the float value. If the variant
     * is type Complex, the value is cast to a float internally.
     *
     *
     * @param value
     */
    virtual bool setComplex( const std::complex<float>& value ) =0 ;

    /**
     * Method returns the current variant value as an float
     *
     * @return variant value as an float
     */
    virtual std::complex<float> toComplex() const =0 ;
} ;

}

#endif /* IDVCOMPLEX_H_ */
