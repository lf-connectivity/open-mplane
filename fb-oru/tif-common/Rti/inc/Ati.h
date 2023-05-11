/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ati.h
 * \brief     Application Test Interface class definition.
 *
 *
 * \details   Ati class definition.
 *
 */
#ifndef _ATI_TESTINTERFACE_H_
#define _ATI_TESTINTERFACE_H_

#include <string>
#include <memory>
#include <vector>

#include "ITif.h"
#include "Mutex.h"
#include "Socket.h"
#include "SocketServer.h"
#include "ILimitsSettings.h"
#include "TestInterfaceFactory.h"

namespace Mplane {


class Ati : public virtual ITifControl, public Task
{

public:
	Ati(unsigned PortNumber = 49500, unsigned NumConnections = 3) ;

	~Ati();

	/**
	 * Singleton creation
	 */
	static std::shared_ptr<Ati> createInstance(unsigned PortNumber = 49500, unsigned NumConnections = 3) ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<ITifControl> getInstance() ;

	/**
	 * Get the indexed ITif object
	 * @param index
	 */
	virtual std::shared_ptr<ITif> getTif(unsigned index) const ;

	/**
	 * Inject the directory(s) provided by this entity
	 * @return true if ok
	 */
	virtual bool doInject(std::shared_ptr<ITifEntry> entry) override ;

	/**
	 * Hide the directory at the given path if present in the tree
	 * @param dir
	 * @return true if found; false otherwise
	 */
	virtual bool doHideDir(const std::string& dir) override ;

	/**
	 * Un-Hide the directory at the given path if present in the tree
	 * @param dir
	 * @return true if found; false otherwise
	 */
	virtual bool doUnhideDir(const std::string& dir) override ;

	/**
	 * Rename the directory at the given path (if present in the tree)
	 * @param dir		Path to directory node (e.g. "/rx/adc")
	 * @param newName	New name of leaf directory (e.g. "ADC")
	 * @return true if found; false otherwise
	 */
	virtual bool doRename(const std::string& dir, const std::string& newName) override ;


	/**
	 * Adds a new server to the TIF control such that connections can also be made to TIF via this new interface
	 * @param server	Created by the caller
	 * @return true if added ok
	 */
	virtual bool addServer(std::shared_ptr<SocketServer> server) ;


	/**
	 * Disconnect all clients for all servers (e.g. when interface goes down)
	 */
	virtual void disconnectClients() ;


	// Internally used list of actions
    class TifAction ;

protected:
	virtual int run() override ;

    Ati( const Ati&);
    Ati& operator=(const Ati&);

    void addAction(std::shared_ptr<TifAction> action) ;
    void addActionNoMutex(std::shared_ptr<TifAction> action) ;

protected:
    std::vector<std::shared_ptr<SocketServer>> mServers;
    int mPortNumber;
    Mutex mMutex ;
    std::vector< std::shared_ptr<ITif> > mTif ;

    // Keep track of any renames/hides etc so they can be applied to any new servers that are added later
    std::vector<std::shared_ptr<TifAction>> mActions ;
};

}
#endif /* _ATI_TESTINTERFACE_H_ */
