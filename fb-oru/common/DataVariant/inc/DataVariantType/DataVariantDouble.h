/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantDouble.h
 * \brief     Provides access methods for DOUBLE type
 *
 *
 * \details   Provides the methods used to access the DataVariant as an DOUBLE
 *
 */


#ifndef DATAVARIANTDOUBLE_H_
#define DATAVARIANTDOUBLE_H_

#include "IDvDouble.h"
#include "DataVariantTypeBase.h"

namespace Mplane {

class DataVariantDouble : public DataVariantTypeBase, public virtual IDvDouble {
public:
	explicit DataVariantDouble(std::shared_ptr<IDvType>& dv) ;
	virtual ~DataVariantDouble() ;

    /**
     * Set the value of the the variant to the double value. If the variant
     * is type Double, the value is cast to a double internally.
     *
     *
     * @param value
     */
    virtual bool setDouble( double value ) override ;

    /**
     * Method returns the current variant value as an double
     *
     * @return variant value as an double
     */
    virtual double toDouble() const override ;
} ;

}

#endif /* DATAVARIANTDOUBLE_H_ */
