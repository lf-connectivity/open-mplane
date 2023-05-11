/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDataBus.h
 * \brief     Test bus that can be used to test serial data transfer.
 *
 *
 * \details   Test bus that can be used to test serial data transfer.
 *
 */


#ifndef COMMON_BUS_INC_TESTDATABUS_H_
#define COMMON_BUS_INC_TESTDATABUS_H_

#include <mutex>
#include <vector>
#include "Bus.h"
#include "FileMap.h"

namespace Mplane {

/*!
 * \class  TestDataBus
 * \brief
 * \details To test any bus that is not yet available in the hardware,
 * TestDataBus can be used. It currently implements read and write methods to transfer vector of bytes.
 * It does not support writing/read data to/from specific offsets. It uses a data file that can be modified
 * to test different conditions like Tx failed/Rx failed/specific Rx data being received.
 * The format of this file is:
	Wr=true
	Rd=true
	RxData=7E 01 30 12 01 00 00 7D 5E 87 7E
 * Wr field defines the result of write operation.
 * Rd field defines the result of the read operation
 * RxData contains the response bytes in hex
 *
 * This class is currently designed so that the read method returns the RxData from the data file
 * only after a write is called. So it is designed for a request response type of device. If required this
 * behaviour can be overridden to your needs.
 */
class TestDataBus : public Bus {
public:
	TestDataBus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~TestDataBus() ;

	static const std::string TestDataPath;
	static const std::string WriteResult;
	static const std::string ReadResult;
	static const std::string ReadData;

protected:

	// Implement the data transfer calls

	/**
	 * Write a block of bytes.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doWriteData(const std::vector<uint8_t>& bytes) override ;

	/**
	 * Read a block of bytes. If specified number of bytes is 0 then reads
	 * whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doReadData(std::vector<uint8_t>& bytes, unsigned numBytes=0) override ;

	bool mRead;
private:
	std::shared_ptr<FileMap> mFileMap;

} ;

}

#endif /* COMMON_BUS_INC_TESTDATABUS_H_ */
