/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantPower.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef DATAVARIANTPOWER_H_
#define DATAVARIANTPOWER_H_

#include "IDvPower.h"
#include "DataVariantTypeBase.h"

namespace Mplane {

class DataVariantPower : public DataVariantTypeBase, public virtual IDvPower {
public:
	explicit DataVariantPower(std::shared_ptr<IDvType>& dv) ;
	virtual ~DataVariantPower() ;

    /**
     * Set the value of the the variant to the frequency value.
     *
     * @param value
     */
    virtual bool setPower( const Power& value ) override ;

    /**
     * Method returns the current variant value as a frequency
     *
     * @return variant value as a frequency
     */
    virtual Power toPower() const override ;

} ;

}

#endif /* DATAVARIANTPOWER_H_ */
