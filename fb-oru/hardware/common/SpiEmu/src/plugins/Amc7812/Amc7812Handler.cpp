/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Handler.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Amc7812Handler.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Amc7812Handler::Amc7812Handler(const std::string& name, float convertOffset, float convertFactor) :
	Loggable(name, "SpiEmu"),
	mOffset(convertOffset),
	mFactor(convertFactor)
{
}

//-------------------------------------------------------------------------------------------------------------
Amc7812Handler::~Amc7812Handler()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Amc7812Handler::writeData(unsigned address, unsigned writeData)
{
	return handleWrite(address, writeData) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Amc7812Handler::readData(unsigned address, unsigned & readData)
{
	unsigned data ;
	bool status(handleRead(address, data)) ;

	// byte swap
	readData = readbackByteSwap(data) ;

	return status ;
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float Amc7812Handler::getValue(unsigned address)
{
	return 0.0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool Amc7812Handler::handleWrite(unsigned address, unsigned writeData)
{
	// default handler does nothing
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Amc7812Handler::handleRead(unsigned address, unsigned & readData)
{
	// default handler gets the value, converts it and returns
	float value = getValue(address) ;
	readData = convert(value) ;

	logDebugVerbose("%s Value=%f Data=0x%08x", getInstanceName().c_str(), value, readData) ;

	return true ;
}



//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned Amc7812Handler::readbackByteSwap(unsigned data)
{
	// byte swap
	unsigned readData = (data & 0xff) << 8 ;
	readData |= (data >> 8) & 0xff ;
	readData |= (data & 0xff0000) << 24 ;
	readData |= (data >> 16) & 0xff0000 ;

	return readData ;
}


//-------------------------------------------------------------------------------------------------------------
unsigned Amc7812Handler::convert(float value)
{
	// Convert the float value using the specified conversion params
	float convert = value * mFactor + mOffset ;

	unsigned data( static_cast<unsigned>(convert) ) ;

	// handle -ve
	if (convert < 0.0)
	{
		convert = -convert ;
		data = static_cast<unsigned>(convert) ;
		data ^= 0xffff ;
		data += 1 ;
	}
	return data ;
}
