/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdData.h
 * \brief     Virtual interface to data
 *
 *
 * \details   The data setter sets the class data based on the map of attributes passed to it from the DPD message dispatcher
 *
 */


#ifndef IDPDDATA_H_
#define IDPDDATA_H_

#include<memory>
#include<map>
#include<string>

#include "DataVariant.h"

namespace Mplane {

class IDpdData {
public:
	IDpdData() {}
	virtual ~IDpdData() {}

	/**
	 * Predicate used to determine whether this data will be used
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if data is to be used
	 */
	virtual bool predicate(const std::map<std::string, DataVariant>& attributes) =0 ;

} ;

class IDpdDataSetter {
public:
	IDpdDataSetter() {}
	virtual ~IDpdDataSetter() {}

	/**
	 * Data setter. Each derived class must provide this method to set it's member data
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if set ok; false on failure
	 */
	virtual bool setData(const std::map<std::string, DataVariant>& attributes) =0 ;

} ;

}

#endif /* IDPDDATASETTER_H_ */
