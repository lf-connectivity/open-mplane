/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialData.h
 * \brief     Serves as a container for data received on serial bus
 *
 *
 * \details   This file is a container for data received on serial bus
 *
 */

#ifndef _HARDWARE_SERIALDATA_H_
#define _HARDWARE_SERIALDATA_H_

#include <vector>


namespace Mplane
{

class SerialData
{

public:

    /**
     * Simple Serial data object constructor.
     */
	explicit SerialData(unsigned int readBlockSize);

    /**
     * Method to get the data
     */
	std::vector<unsigned char> getData(void);

    /**
     * Method to set the data
     */
	void setData(std::vector<unsigned char> data);

    /**
     * Method to append to the data
     */
	void appendData(std::vector<unsigned char> data);

    /**
     * Method to clear the data
     */
	void clearData(void);

private:

	std::vector<unsigned char> mData;   //!> Vector containing serial data
};

} /* namespace Mplane */

#endif /* _HARDWARE_SERIALDATA_H_ */
