/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiBusEmu.h
 * \brief     SPI bus emulator
 *
 *
 * \details
 *
 */


#ifndef SpiBusEmu_H_
#define SpiBusEmu_H_

#include <memory>
#include <vector>
#include "OffTargetFPGA.h"
#include "GlobalTypeDefs.h"
#include "TaskEvent.h"

#include "ISpiPlugin.h"

namespace Mplane {

/*!
 * \class SpiBusEmu
 */
class SpiBusEmu : public TaskEvent {
public:
	explicit SpiBusEmu(unsigned index) ;
	virtual ~SpiBusEmu() ;

	/**
	 * Register a plugin with the particular SPI bus
	 * @param plugin
	 * @return true if registered ok
	 */
	virtual bool registerDevice(std::shared_ptr<ISpiPlugin> plugin) ;

	/**
	 * Unregister a plugin
	 * @param devId
	 * @param devNum
	 * @param shift
	 * @return true if unregistered ok
	 */
	virtual bool unregisterDevice(unsigned devId, unsigned devNum, unsigned shift=0) ;

	/**
	 * Given a name, returns the plugin of that name
	 * @param name
	 * @return plugin or null pointer
	 */
	virtual std::shared_ptr<ISpiPlugin> getPlugin(const std::string& name) const ;

	/**
	 * Given device parameters, returns the plugin of that is registered for those parameters
	 * @param devId
	 * @param devNum
	 * @param shift
	 * @return plugin or null pointer
	 */
	virtual std::shared_ptr<ISpiPlugin> getPlugin(unsigned devId, unsigned devNum, unsigned shift=0) const ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
	UINT16 writeSelectHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readSelectHandler(const UINT32 address, const UINT16 mask) ;


private:
	unsigned mIndex ;
	std::string mPrefix ;
	Mutex mEmuMutex ;
	std::shared_ptr<OffTargetFPGA> mFpga ;
	std::string mStatusField ;
	UINT16 mSelect ;

	std::map<unsigned, std::shared_ptr<ISpiPlugin>> mPlugins ;
} ;

}

#endif /* SpiBusEmu_H_ */
