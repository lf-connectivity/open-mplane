/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantTypes.h
 * \brief     Collects together all of the supported types
 *
 *
 * \details   Inherits the methods from all supported types into a convenience class so we only have to inherit this in DataVariantBase
 *
 */


#ifndef DATAVARIANTTYPES_H_
#define DATAVARIANTTYPES_H_

#include "DataVariantType/DataVariantInt.h"
#include "DataVariantType/DataVariantFloat.h"
#include "DataVariantType/DataVariantComplex.h"
#include "DataVariantType/DataVariantBool.h"
#include "DataVariantType/DataVariantEnum.h"
#include "DataVariantType/DataVariantFreq.h"
#include "DataVariantType/DataVariantPower.h"
#include "DataVariantType/DataVariantUint.h"
#include "DataVariantType/DataVariantLong.h"
#include "DataVariantType/DataVariantDouble.h"

namespace Mplane {

class DataVariantTypes :
	public DataVariantFloat,
	public DataVariantComplex,
	public DataVariantEnum,
	public DataVariantBool,
	public DataVariantFreq,
	public DataVariantPower,
	public DataVariantUint,
	public DataVariantLong,
	public DataVariantDouble,

	public DataVariantInt

{
public:
	explicit DataVariantTypes(std::shared_ptr<IDvType>& dv) ;
	virtual ~DataVariantTypes() ;

} ;

}

#endif /* DATAVARIANTTYPES_H_ */
