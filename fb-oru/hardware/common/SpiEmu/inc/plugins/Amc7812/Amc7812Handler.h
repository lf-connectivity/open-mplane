/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Handler.h
 * \brief     Base class for Amc7812 handlers
 *
 *
 * \details
 *
 */


#ifndef Amc7812Handler_H_
#define Amc7812Handler_H_

#include <memory>
#include "Loggable.h"
#include "IAmc7812Handler.h"

namespace Mplane {

/*!
 * \class Amc7812Handler
 */
class Amc7812Handler : public virtual IAmc7812Handler, public Loggable
{
public:
	Amc7812Handler(const std::string& name, float convertOffset, float convertFactor) ;
	virtual ~Amc7812Handler() ;

	/**
	 * Process a write
	 * @param writeData
	 * @return true if ok; false on error
	 */
	virtual bool writeData(unsigned address, unsigned writeData) override ;

	/**
	 * Process a read
	 * @param readData
	 * @return true if ok; false on error
	 */
	virtual bool readData(unsigned address, unsigned& readData) override ;

protected:
	// simplified hook - for read data just implement this to get the data and update any parameters
	virtual float getValue(unsigned address) ;

	// Hooks - override in derived objects
	virtual bool handleWrite(unsigned address, unsigned writeData) ;
	virtual bool handleRead(unsigned address, unsigned & readData) ;

protected:
	// Utility
	unsigned readbackByteSwap(unsigned data) ;
	unsigned convert(float value) ;

private:
	float mOffset ;
	float mFactor ;

} ;

}

#endif /* Amc7812Handler_H_ */
