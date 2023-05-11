/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialBus.h
 * \brief     Base-level serial bus
 *
 *
 * \details   Base-level serial bus
 *
 */


#ifndef COMMON_BUS_INC_SERIALBUS_H_
#define COMMON_BUS_INC_SERIALBUS_H_

#include "Bus.h"

namespace Mplane {

/*!
 * \class  SerialBus
 * \brief
 * \details
 *
 */
class SerialBus : public Bus {
public:
	SerialBus(const std::string& busName, const std::string& busDetails, unsigned baudRate, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~SerialBus() ;


protected:
	/**
	 * Get the baud rate
	 */
	unsigned baud() const ;

private:
	unsigned mBaudRate ;
} ;

}

#endif /* COMMON_BUS_INC_SERIALBUS_H_ */
