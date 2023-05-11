/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantLong.h
 * \brief     Provides access methods for LONG type
 *
 *
 * \details   Provides the methods used to access the DataVariant as an LONG
 *
 */


#ifndef DATAVARIANTLONG_H_
#define DATAVARIANTLONG_H_

#include "IDvLong.h"
#include "DataVariantTypeBase.h"

namespace Mplane {

class DataVariantLong : public DataVariantTypeBase, public virtual IDvLong {
public:
	explicit DataVariantLong(std::shared_ptr<IDvType>& dv) ;
	virtual ~DataVariantLong() ;

    /**
     * Set the value of the the variant to the long long value. If the variant
     * is type Long, the value is cast to a long long internally.
     *
     *
     * @param value
     */
    virtual bool setLong( long long value ) override ;

    /**
     * Method returns the current variant value as an long long
     *
     * @return variant value as an long long
     */
    virtual long long toLong() const override ;
} ;

}

#endif /* DATAVARIANTLONG_H_ */
