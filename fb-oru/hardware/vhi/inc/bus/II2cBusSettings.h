/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      II2cBusSettings.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VHI_INC_BUS_II2CBUSSETTINGS_H_
#define VHI_INC_BUS_II2CBUSSETTINGS_H_

#include "IBusSettings.h"

namespace Mplane {

/*!
 * \class  II2cBusReadonlySettings
 * \brief
 * \details
 *
 */
class II2cBusReadonlySettings : public virtual IBusReadonlySettings {
public:
	II2cBusReadonlySettings() {}
	virtual ~II2cBusReadonlySettings() {}
} ;

/*!
 * \class  II2cBusSettings
 * \brief
 * \details
 *
 */
class II2cBusSettings : public virtual IBusSettings, public virtual II2cBusReadonlySettings {
public:
	II2cBusSettings() {}
	virtual ~II2cBusSettings() {}

} ;

}

#endif /* VHI_INC_BUS_II2CBUSSETTINGS_H_ */
