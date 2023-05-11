/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialDriverunittest.h
 * \brief     Test case header file for the serial driver
 *
 *
 * \details   Test case header file for the serial driver
 *
 */

#ifndef TEST_SERIAL_DRIVER_TESTCASE_H_
#define TEST_SERIAL_DRIVER_TESTCASE_H_


// Includes go here, before the namespace
#include "gtest/gtest.h"

#include "AisgSerialDriver.h"
#include "ISerialDriver.h"
#include "ISerialDataReceived.h"
#include "Observer.hpp"


namespace Mplane
{

class TestSerialDriver : public Observer<ISerialDataReceived>
{
public:

	TestSerialDriver();

    ~TestSerialDriver(){};

	int getMasterFd(void){return masterFd;};

	std::vector<unsigned char> getSerialData(void);

	void clearSerialData(void);

	bool isDataReceived(void);

	bool write(unsigned char* data, unsigned int len);

protected:

	virtual void update(ISerialDataReceived& subject);

	virtual const char* name() const ;

	std::shared_ptr<ISerialDriver> mAisgDrv;            //!> Pointer to Aisg serial driver

	int masterFd;                                       //!> Master file descriptor for the psuedoterminal master
	char* slave_name;                                   //!> Slave for psuedoterminal

	std::vector<unsigned char> mData;                   //!> Serial data received
	bool mRecvData;

};

} /* namespace Mplane */

#endif /* TEST_SERIAL_DRIVER_TESTCASE_H_ */
