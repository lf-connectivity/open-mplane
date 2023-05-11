/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Rs485BusLinux.h
 * \brief     Base-level RS485 bus
 *
 *
 * \details   Base-level RS485 bus
 *
 */


#ifndef COMMON_BUS_INC_RS485BUSLINUX_H_
#define COMMON_BUS_INC_RS485BUSLINUX_H_

#include "SerialBusLinux.h"

namespace Mplane {

/*!
 * \class  Rs485BusLinux
 * \brief
 * \details
 *
 */
class Rs485BusLinux : public SerialBusLinux {
public:
	Rs485BusLinux(const std::string& devicePath, unsigned baudRate, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~Rs485BusLinux() ;


protected:

	/**
	 * Write a block of bytes.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doWriteData(const std::vector<uint8_t>& bytes) override ;

    /**
     * Method to allow transmission on the RS485 bus
     */
	virtual void setTx(void);

    /**
     * Method to allow reception on the RS485 bus
     */
	virtual void setRx(void);

} ;

}

#endif /* COMMON_BUS_INC_RS485BUSLINUX_H_ */
