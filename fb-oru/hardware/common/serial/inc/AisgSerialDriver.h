/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AisgSerialDriver.h
 * \brief     Provides methods to access the serial device on the Aisg bus
 *
 *
 * \details   This file defines methods to access the serial device on the Aisg bus
 *
 */

#ifndef _HARDWARE_AISGSERIALDRIVER_H_
#define _HARDWARE_AISGSERIALDRIVER_H_

#include <vector>
#include <mutex>
#include "SerialDriver.h"
#include "CommonGpio.h"

namespace Mplane
{

/*! \brief A generic serial driver class.
 *
 * The Serial driver class
 */
class AisgSerialDriver : public SerialDriver
{

public:

	static const unsigned int AISG_TX_EN_BIT;
	static const unsigned int AISG_RX_EN_N_BIT;
	static const unsigned int AISG_TX_RX_MASK;

    /*! \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the Aisg
     *  serial driver object.
     */
    static std::shared_ptr<AisgSerialDriver> getInstance(std::string devPath, unsigned int baud);

    /**
     * Simple Aisg Serial driver object constructor.
     */
	AisgSerialDriver(std::string devPath, unsigned int baud);

    /**
     * Virtual Aisg Serial driver object destructor.
     */
	virtual ~AisgSerialDriver(void){};

    /**
     * Method to write data to the serial device
     */
	virtual bool write(unsigned char* data, unsigned int dataLen) override;

protected:

    /**
     * Method to allow transmission on the Aisg bus
     */
	virtual void setTx(void);

    /**
     * Method to allow reception on the Aisg bus
     */
	virtual void setRx(void);

private:

	std::shared_ptr<CommonGpio> mGpio;

	std::mutex mMutex;
};

} /* namespace Mplane */

#endif /* _HARDWARE_AISGSERIALDRIVER_H_ */
