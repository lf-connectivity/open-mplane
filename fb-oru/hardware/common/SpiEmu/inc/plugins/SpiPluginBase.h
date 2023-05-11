/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiPluginBase.h
 * \brief     Base class for SPI emulator bus plugins
 *
 *
 * \details
 *
 */


#ifndef SPIPLUGINBASE_H_
#define SPIPLUGINBASE_H_

#include "ISpiPlugin.h"
#include "Loggable.h"

namespace Mplane {

/*!
 * \class SpiPluginBase
 */
class SpiPluginBase : public virtual ISpiPlugin, public Loggable {
public:
	SpiPluginBase(const std::string& name, unsigned bus, unsigned devId, unsigned devNum, unsigned shift) ;
	virtual ~SpiPluginBase() ;

	/**
	 * Is this the named plugin
	 * @param name
	 * @return true if named plugin
	 */
	virtual bool isPlugin(const std::string& name) const override ;

	/**
	 * Is this the plugin for the specified parameters
	 * @param devId
	 * @param devNum
	 * @param shift
	 * @return true if this is the plugin
	 */
	virtual bool isPlugin(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) const override ;

	// Accessors
	virtual std::string getName() const override ;
	virtual unsigned getBus() const override ;
	virtual unsigned getDevId() const override ;
	virtual unsigned getDevNum() const override ;
	virtual unsigned getShift() const override ;

private:
	unsigned mBus ;
	unsigned mDevId ;
	unsigned mDevNum ;
	unsigned mShift ;

} ;

}

#endif /* SPIPLUGINBASE_H_ */
