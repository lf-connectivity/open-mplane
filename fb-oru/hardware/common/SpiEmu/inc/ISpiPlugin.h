/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISpiPlugin.h
 * \brief     Interface to plugin handler for data in the Spi emulator
 *
 *
 * \details
 *
 */


#ifndef ISPIPLUGIN_H_
#define ISPIPLUGIN_H_

#include <string>

namespace Mplane {

/*!
 * \class ISpiPlugin
 */
class ISpiPlugin {
public:
	ISpiPlugin() {}
	virtual ~ISpiPlugin() {}

	/**
	 * Is this the named plugin
	 * @param name
	 * @return true if named plugin
	 */
	virtual bool isPlugin(const std::string& name) const =0 ;

	/**
	 * Is this the plugin for the specified parameters
	 * @param devId
	 * @param devNum
	 * @param shift
	 * @return true if this is the plugin
	 */
	virtual bool isPlugin(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) const =0 ;

	/**
	 * Process the write data and read/write to the read data variable
	 * @param select
	 * @param writeData
	 * @param writeNumBits	Number of valid write bits within the 32-bit word
	 * @param readData
	 * @param readNumBits	Number of valid read bits within the 32-bit word
	 * @return true if ok; false on error
	 */
	virtual bool handleData(unsigned select, unsigned writeData, unsigned writeNumBits, unsigned& readData, unsigned readNumBits) =0 ;

	// Accessors
	virtual std::string getName() const =0 ;
	virtual unsigned getBus() const =0 ;
	virtual unsigned getDevId() const =0 ;
	virtual unsigned getDevNum() const =0 ;
	virtual unsigned getShift() const =0 ;
} ;

}

#endif /* ISPIPLUGIN_H_ */
