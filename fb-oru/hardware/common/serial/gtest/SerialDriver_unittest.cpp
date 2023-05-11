/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialDriver_unittest.cpp
 * \brief     Google Test of SerialDriver
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the AisgSerialDriver class.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <termios.h>
#include <string.h>

#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <iostream>
#include <string>

#include <memory>
#include <stdlib.h>
#include "SerialDriver_unittest.h"
#include "Task.h"

using namespace Mplane;

TestSerialDriver::TestSerialDriver()
{
	//opens an unused pseudoterminal master
	masterFd = posix_openpt(O_RDWR | O_NOCTTY | O_SYNC );

	//to change the ownership and permissions of the
	//slave device that corresponds to the pseudoterminal master
	grantpt(masterFd);


	unlockpt(masterFd);

	slave_name = ptsname(masterFd);
	mRecvData = false;

	std::string dev_path = slave_name;

	mAisgDrv = AisgSerialDriver::getInstance(dev_path, 9600);
	// Attach to Aisg instance
	std::dynamic_pointer_cast<Subject<ISerialDataReceived>>(mAisgDrv)->attach(*this);
}

//-------------------------------------------------------------------------------------------------------------
void TestSerialDriver::update(ISerialDataReceived& subject)
{
	//Get the serial data
	SerialData data = mAisgDrv->getSerialData();

	mData = data.getData();

	mRecvData = true;
}

//-------------------------------------------------------------------------------------------------------------
const char* TestSerialDriver::name() const
{
	return "TestSerialDriver";
}

//-------------------------------------------------------------------------------------------------------------
std::vector<unsigned char> TestSerialDriver::getSerialData(void)
{
	return mData;
}

//-------------------------------------------------------------------------------------------------------------
void TestSerialDriver::clearSerialData(void)
{
	mData.clear();
}

//-------------------------------------------------------------------------------------------------------------
bool TestSerialDriver::isDataReceived(void)
{
	return mRecvData;
}

//-------------------------------------------------------------------------------------------------------------
bool TestSerialDriver::write(unsigned char* data, unsigned int len)
{
	return mAisgDrv->write(data, len);
}

//-------------------------------------------------------------------------------------------------------------
TEST(TestSerialDriverTestCases, ReadWrite)
{
#ifdef DISABLED_DUE_TO_SERVER_ISSUES

	TestSerialDriver drv;

	//Write a packet from the psuedoterminal master
	unsigned char buff[8] = {'1','2','3','4','5','6','7','8'} ;
	int ret = ::write(drv.getMasterFd(), buff, 5) ;
	//Check if write has succeeded
	EXPECT_GE(ret, 0);
	//Wait till data is received by the slave
	while (drv.isDataReceived() == false) Task::msSleep(100);
	//Read data and verify it matches the sent packet
	std::vector<unsigned char> data = drv.getSerialData();
	EXPECT_EQ(data.size(), 5);
	EXPECT_EQ(data[0], '1');
	EXPECT_EQ(data[1], '2');
	EXPECT_EQ(data[2], '3');
	EXPECT_EQ(data[3], '4');
	EXPECT_EQ(data[4], '5');

	unsigned char buff1[8] = {'a','b','c','d','e','f','g','h'} ;
	int nfds = 0 ;
	fd_set fds ;
	FD_ZERO(&fds) ;

	//Add the master descriptor to the list of file descriptors
	FD_SET(drv.getMasterFd(), &fds) ;
	nfds = drv.getMasterFd() + 1 ;

	//Make the slave send a packet
	bool ret1 = drv.write(buff1, 5);
	//Check that the write is successful
	EXPECT_TRUE(ret1);

	//Wait for the master to have some data
	int rc = ::select(nfds, &fds, NULL, NULL, NULL) ;
	//Check that there is no error
	EXPECT_GE(rc, 0);
	EXPECT_TRUE(FD_ISSET(drv.getMasterFd(), &fds));
	std::vector<char> buff2;
	buff2.resize(256);
	//Read from the master
	int num = ::read(drv.getMasterFd(), buff2.data(), buff2.size()) ;
	if (num < 0)
	{
		printf("%d %s",errno, strerror(errno));
	}
	EXPECT_EQ(num, 5);
	EXPECT_EQ(buff2[0], 'a');
	EXPECT_EQ(buff2[1], 'b');
	EXPECT_EQ(buff2[2], 'c');
	EXPECT_EQ(buff2[3], 'd');
	EXPECT_EQ(buff2[4], 'e');
	return;

#endif
}
