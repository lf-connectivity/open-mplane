/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiEmu.h
 * \brief     SPI emulator of all devices on all buses
 *
 *
 * \details   Contains a collection of SpiBusEmu objects, one for each SPI bus. Provide a mechanism for registering plugins
 * 			to emulate each of the target devices on a particular SPI bus
 *
 */


#ifndef SPIEMU_H_
#define SPIEMU_H_

#include <memory>
#include <vector>

#include "ISpiEmu.h"
#include "ISpiPlugin.h"
#include "Loggable.h"

namespace Mplane {

class SpiBusEmu ;

/*!
 * \class SpiEmu
 */
class SpiEmu : public virtual ISpiEmu, public Loggable {
public:
	explicit SpiEmu(unsigned numSpiBuses = 2) ;
	virtual ~SpiEmu() ;

	/**
	 * Register a plugin with the particular SPI bus
	 * @param plugin
	 * @return true if registered ok
	 */
	virtual bool registerDevice(std::shared_ptr<ISpiPlugin> plugin) override ;

	/**
	 * Unregister a plugin
	 * @param bus
	 * @param devId
	 * @param devNum
	 * @param shift
	 * @return true if unregistered ok
	 */
	virtual bool unregisterDevice(unsigned bus, unsigned devId, unsigned devNum, unsigned shift=0) override ;

	/**
	 * Given a name, returns the plugin of that name
	 * @param name
	 * @return plugin or null pointer
	 */
	virtual std::shared_ptr<ISpiPlugin> getPlugin(const std::string& name) const override ;

	/**
	 * Given device parameters, returns the plugin of that is registered for those parameters
	 * @param bus
	 * @param devId
	 * @param devNum
	 * @param shift
	 * @return plugin or null pointer
	 */
	virtual std::shared_ptr<ISpiPlugin> getPlugin(unsigned bus, unsigned devId, unsigned devNum, unsigned shift=0) const override ;


private:
	std::vector<std::shared_ptr<SpiBusEmu>> mSpiBus ;
} ;

}

#endif /* SPIEMU_H_ */
