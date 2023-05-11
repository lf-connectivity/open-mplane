/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantComplex.h
 * \brief     Provides access methods for Complex type
 *
 *
 * \details   Provides the methods used to access the DataVariant as an Complex
 *
 */


#ifndef DataVariantComplex_H_
#define DataVariantComplex_H_

#include "IDvComplex.h"
#include "DataVariantTypeBase.h"

namespace Mplane {

class DataVariantComplex : public DataVariantTypeBase, public virtual IDvComplex {
public:
	explicit DataVariantComplex(std::shared_ptr<IDvType>& dv) ;
	virtual ~DataVariantComplex() ;

    /**
     * Set the value of the the variant to the Complex value. If the variant
     * is type Complex, the value is cast to a Complex internally.
     *
     *
     * @param value
     */
    virtual bool setComplex( const std::complex<float>& value ) override ;

    /**
     * Method returns the current variant value as an Complex
     *
     * @return variant value as an Complex
     */
    virtual std::complex<float> toComplex() const override ;
} ;

}

#endif /* DataVariantComplex_H_ */
