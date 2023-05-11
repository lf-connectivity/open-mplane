/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegDriver.h
 * \brief     A register-based device driver
 *
 *
 * \details   Device driver with a register interface
 *
 */


#ifndef COMMON_REGDRIVER_INC_REGDRIVER_H_
#define COMMON_REGDRIVER_INC_REGDRIVER_H_

#include "IRegModel.h"
#include "IBus.h"
#include "Driver.h"

namespace Mplane {

/*!
 * \class  RegDriver
 * \brief
 * \details
 *
 */
class RegDriver : public Driver {
public:
	RegDriver(const std::string& name, std::shared_ptr<IBus> bus, std::shared_ptr<IRegModel> regModel) ;
	virtual ~RegDriver() ;

protected:
	// Allow derived class access to register model
	std::shared_ptr<IRegModel> regModel() ;

private:
	std::shared_ptr<IBus> mBus ;
	std::shared_ptr<IRegModel> mRegModel ;
} ;

}

#endif /* COMMON_REGDRIVER_INC_REGDRIVER_H_ */
