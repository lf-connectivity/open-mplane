/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantBool.h
 * \brief     Provides access methods for BOOL type
 *
 *
 * \details   Provides the methods used to access the DataVariant as a BOOL
 *
 */


#ifndef DATAVARIANTBOOL_H_
#define DATAVARIANTBOOL_H_

#include "IDvBool.h"
#include "DataVariantTypeBase.h"

namespace Mplane {

class DataVariantBool : public DataVariantTypeBase, public virtual IDvBool {
public:
	explicit DataVariantBool(std::shared_ptr<IDvType>& dv) ;
	virtual ~DataVariantBool() ;

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

} ;

}

#endif /* DATAVARIANTBOOL_H_ */
