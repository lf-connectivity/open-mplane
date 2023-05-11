/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantTypeBase.h
 * \brief     Base class for DataVariantX types
 *
 *
 * \details
 *
 */


#ifndef DATAVARIANTTYPEBASE_H_
#define DATAVARIANTTYPEBASE_H_

#include <memory>
#include "IDvType.h"

namespace Mplane {

class DataVariantTypeBase {
public:
	explicit DataVariantTypeBase(std::shared_ptr<IDvType>& dv) ;
	virtual ~DataVariantTypeBase() ;

protected:
	void updateType(DataVariantType::Type type) ;

protected:
	std::shared_ptr<IDvType>& mDvRef ;

} ;

}

#endif /* DATAVARIANTTYPEBASE_H_ */
