/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusSettings.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef COMMON_BUS_INC_I2CBUSSETTINGS_H_
#define COMMON_BUS_INC_I2CBUSSETTINGS_H_

#include "II2cBusSettings.h"
#include "BusSettings.hpp"

namespace Mplane {

/*!
 * \class  I2cBusSettings
 * \brief
 * \details
 *
 */
class I2cBusSettings : public virtual II2cBusSettings, public BusSettings {
public:
	I2cBusSettings() :
		BusSettings()
	{}
	virtual ~I2cBusSettings() {}

} ;

}

#endif /* COMMON_BUS_INC_I2CBUSSETTINGS_H_ */
