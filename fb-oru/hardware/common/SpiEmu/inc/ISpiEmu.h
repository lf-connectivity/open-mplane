/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISpiEmu.h
 * \brief     Virtual interface to SPI emulator
 *
 *
 * \details
 *
 */


#ifndef ISPIEMU_H_
#define ISPIEMU_H_

#include <memory>
#include "ISpiPlugin.h"

namespace Mplane {

/*!
 * \class SpiEmu
 */
class ISpiEmu {
public:
	ISpiEmu() {}
	virtual ~ISpiEmu() {}

	static std::shared_ptr<ISpiEmu> getInstance() ;

	/**
	 * Register a plugin with the particular SPI bus
	 * @param plugin
	 * @return true if registered ok
	 */
	virtual bool registerDevice(std::shared_ptr<ISpiPlugin> plugin) =0 ;

	/**
	 * Unregister a plugin
	 * @param bus
	 * @param devId
	 * @param devNum
	 * @param shift
	 * @return true if unregistered ok
	 */
	virtual bool unregisterDevice(unsigned bus, unsigned devId, unsigned devNum, unsigned shift=0) =0 ;

	/**
	 * Given a name, returns the plugin of that name
	 * @param name
	 * @return plugin or null pointer
	 */
	virtual std::shared_ptr<ISpiPlugin> getPlugin(const std::string& name) const =0 ;

	/**
	 * Given device parameters, returns the plugin of that is registered for those parameters
	 * @param bus
	 * @param devId
	 * @param devNum
	 * @param shift
	 * @return plugin or null pointer
	 */
	virtual std::shared_ptr<ISpiPlugin> getPlugin(unsigned bus, unsigned devId, unsigned devNum, unsigned shift=0) const =0 ;

} ;

}

#endif /* ISPIEMU_H_ */
