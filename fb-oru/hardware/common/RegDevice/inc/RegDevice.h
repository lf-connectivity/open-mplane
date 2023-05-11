/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegDevice.h
 * \brief     An IDevice for a device that has a register-based model
 *
 *
 * \details   An IDevice for a device that has a register-based model AND uses an IBus
 *
 */


#ifndef COMMON_REGDEVICE_INC_REGDEVICE_H_
#define COMMON_REGDEVICE_INC_REGDEVICE_H_

#include <memory>

#include "IBus.h"
#include "IRegModel.h"

#include "Device.h"

namespace Mplane {

/*!
 * \class  RegDevice
 * \brief
 * \details
 *
 */
class RegDevice : public Device {
public:
	virtual ~RegDevice() ;

protected:
	RegDevice(Device::Type type, int index,
		const std::string& name, std::shared_ptr<IBus> bus,
		unsigned addrWidth, unsigned dataWidth, unsigned addrLSB);


protected:
	// Allow derived class access to register model
	std::shared_ptr<IRegModel> regModel() ;

private:
	std::shared_ptr<IBus> mBus ;
	std::shared_ptr<IRegModel> mRegModel ;
} ;

}

#endif /* COMMON_REGDEVICE_INC_REGDEVICE_H_ */
