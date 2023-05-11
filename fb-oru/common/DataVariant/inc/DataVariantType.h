/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantType.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef DATAVARIANTTYPE_H_
#define DATAVARIANTTYPE_H_


namespace Mplane {

class DataVariantType {
public:
    enum Type
    {
        None,
        String,
        Int,
        Float,
        Bool,
        Enum,
        Complex,
        Freq,
        Power,
        Uint,
        Long,
        Double
    };

} ;

}

#endif /* DATAVARIANTTYPE_H_ */
