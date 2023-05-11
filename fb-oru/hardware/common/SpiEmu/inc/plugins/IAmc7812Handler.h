/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAmc7812Handler.h
 * \brief     Virtual interface for various devices within the Amc7812
 *
 *
 * \details
 *
 */


#ifndef IAMC7812HANDLER_H_
#define IAMC7812HANDLER_H_


namespace Mplane {

/*!
 * \class IAmc7812Handler
 */
class IAmc7812Handler {
public:
	IAmc7812Handler() {}
	virtual ~IAmc7812Handler() {}

	/**
	 * Process a write
	 * @param writeData
	 * @return true if ok; false on error
	 */
	virtual bool writeData(unsigned address, unsigned writeData) =0 ;

	/**
	 * Process a read
	 * @param readData
	 * @return true if ok; false on error
	 */
	virtual bool readData(unsigned address, unsigned& readData) =0 ;


} ;

}

#endif /* IAMC7812HANDLER_H_ */
