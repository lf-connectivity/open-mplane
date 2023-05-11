/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ati.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IBootTimer.h"
#include "TifControl.hpp"
#include "Ati.h"

using namespace Mplane;


//=============================================================================================================
// CONST
//=============================================================================================================
const int ATI_PRIORITY{Task::PRIORITY_HIGH} ;

//=============================================================================================================
// ACTIONS
//=============================================================================================================

namespace Mplane {

//-------------------------------------------------------------------------------------------------------------
class Ati::TifAction {
public:
	explicit TifAction(Ati* ati) :
		mAti(ati)
	{}
	virtual ~TifAction() {}
	virtual bool operator()(std::shared_ptr<SocketServer> server, std::shared_ptr<ITif> tif)
	{
		return false;
	}

protected:
	Ati* mAti;
};

//-------------------------------------------------------------------------------------------------------------
class TifStartAction : public Ati::TifAction {
public:
	explicit TifStartAction(Ati* ati) :
		Ati::TifAction(ati)
	{}
	virtual ~TifStartAction() {}

	/**
	 * Run start
	 */
	virtual bool operator()(std::shared_ptr<SocketServer> server, std::shared_ptr<ITif> tif) override
	{
		// Skip start if already running
		if (server->isRunning())
			return true ;

		// start
		server->start();

		// make sure the RTI is running before calling the isRunning() method
		server->msSleep( 10 );

		return true ;
	}
};


//-------------------------------------------------------------------------------------------------------------
class TifInjectAction : public Ati::TifAction {
public:
	TifInjectAction(Ati* ati, std::shared_ptr<ITifEntry> entry) :
		Ati::TifAction(ati),
		mEntry(entry)
	{}
	virtual ~TifInjectAction() {}

	/**
	 * Run start
	 */
	virtual bool operator()(std::shared_ptr<SocketServer> server, std::shared_ptr<ITif> tif) override
	{
		return tif->doInject(mEntry) ;
	}

private:
	std::shared_ptr<ITifEntry> mEntry ;
};

//-------------------------------------------------------------------------------------------------------------
class TifRenameAction : public Ati::TifAction {
public:
	TifRenameAction(Ati* ati, const std::string& dir, const std::string& newName) :
		Ati::TifAction(ati),
		mDir(dir),
		mName(newName)
	{}
	virtual ~TifRenameAction() {}

	/**
	 * Run start
	 */
	virtual bool operator()(std::shared_ptr<SocketServer> server, std::shared_ptr<ITif> tif) override
	{
		return tif->doRename(mDir, mName) ;
	}

private:
	std::string mDir ;
	std::string mName ;
};

//-------------------------------------------------------------------------------------------------------------
class TifHideAction : public Ati::TifAction {
public:
	TifHideAction(Ati* ati, const std::string& dir) :
		Ati::TifAction(ati),
		mDir(dir)
	{}
	virtual ~TifHideAction() {}

	/**
	 * Run start
	 */
	virtual bool operator()(std::shared_ptr<SocketServer> server, std::shared_ptr<ITif> tif) override
	{
		return tif->doHideDir(mDir) ;
	}

private:
	std::string mDir ;
};

//-------------------------------------------------------------------------------------------------------------
class TifUnhideAction : public Ati::TifAction {
public:
	TifUnhideAction(Ati* ati, const std::string& dir) :
		Ati::TifAction(ati),
		mDir(dir)
	{}
	virtual ~TifUnhideAction() {}

	/**
	 * Run start
	 */
	virtual bool operator()(std::shared_ptr<SocketServer> server, std::shared_ptr<ITif> tif) override
	{
		return tif->doUnhideDir(mDir) ;
	}

private:
	std::string mDir ;
};

}


//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<Ati> Ati::createInstance(unsigned PortNumber, unsigned NumConnections)
{
	static std::shared_ptr<Ati> instance(std::make_shared<Ati>(PortNumber, NumConnections)) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITifControl> Ati::getInstance()
{
	return std::dynamic_pointer_cast<ITifControl>(createInstance()) ;
}

//=============================================================================================================
// ITifControl
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITif> ITifControl::getITif()
{
	std::shared_ptr<ITifControl> tifControl(ITifControl::getInstance()) ;
	std::shared_ptr<Ati> ati(std::dynamic_pointer_cast<Ati>(tifControl)) ;
	return ati->getTif(0) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITifControl> ITifControl::getInstance()
{
	return Ati::getInstance() ;
}

//-------------------------------------------------------------------------------------------------------------
bool ITifControl::inject(std::shared_ptr<ITifEntry> entry)
{
	return ITifControl::getInstance()->doInject(entry) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ITifControl::hideDir(const std::string& dir, bool hide)
{
	if (!hide)
		return true ;

	return ITifControl::getInstance()->doHideDir(dir) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ITifControl::rename(const std::string& dir, const std::string& newName)
{
	if (newName.empty())
		return true ;

	return ITifControl::getInstance()->doRename(dir, newName) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ITifControl::addServer(std::shared_ptr<SocketServer> server)
{
	return std::dynamic_pointer_cast<Ati>(ITifControl::getInstance())->addServer(server) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned ITifControl::getTaskPriority()
{
	return ATI_PRIORITY ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Ati::Ati(unsigned PortNumber, unsigned NumConnections) :
	Task( ATI_PRIORITY, MEDIUM_STACK, "AppTestItf", "TIF"),
	mServers(),
	mPortNumber(PortNumber),
	mMutex(),
	mTif(),
	mActions()
{
//	std::cerr << "ATI: NEW [port=" << PortNumber << ", max connections=" << NumConnections << "]" << std::endl ;

	// limits
	std::shared_ptr<ILimitsSettings> limitsSettings(ILimitsSettings::getInstance()) ;
	limitsSettings->registerSettings() ;

	// server
	std::shared_ptr<SocketServer> server(
		TifControl::make_server<SocketServer>("TIFSKtSrvr", mPortNumber, NumConnections)
	);
	addServer(server) ;

	// stop timing the tif startup time
	std::shared_ptr<IBootTimer> bootTimer(IBootTimer::getInstance()) ;
	bootTimer->tifStarted() ;
	eventInfo("(BENCH) Application time to tif: %.3fs [Total %.3fs]", bootTimer->getTifElapsed(), bootTimer->getTifTime()) ;
}

//-------------------------------------------------------------------------------------------------------------
Ati::~Ati()
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITif> Ati::getTif(unsigned index) const
{
	if (index >= mTif.size())
		return std::shared_ptr<ITif>() ;

	return mTif.at(index) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ati::doInject(std::shared_ptr<ITifEntry> entry)
{
//	std::cerr << "ATI: doInject" << std::endl ;

	for (auto tif : mTif)
	{
		if (!tif->doInject(entry))
			return false ;
	}

	// Add to list of actions
	addAction(std::make_shared<TifInjectAction>(this, entry)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ati::doHideDir(const std::string& dir)
{
//	std::cerr << "ATI: doHideDir " << dir << std::endl ;

	for (auto tif : mTif)
	{
		if (!tif->doHideDir(dir))
			return false ;
	}

	// Add to list of actions
	addAction(std::make_shared<TifHideAction>(this, dir)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ati::doUnhideDir(const std::string& dir)
{
//	std::cerr << "ATI: doUnhideDir " << dir << std::endl ;

	for (auto tif : mTif)
	{
		if (!tif->doUnhideDir(dir))
			return false ;
	}

	// Add to list of actions
	addAction(std::make_shared<TifUnhideAction>(this, dir)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ati::doRename(const std::string& dir, const std::string& newName)
{
//	std::cerr << "ATI: doRename " << dir << " " << newName << std::endl ;

	for (auto tif : mTif)
	{
		if (!tif->doRename(dir, newName))
			return false ;
	}

	// Add to list of actions
	addAction(std::make_shared<TifRenameAction>(this, dir, newName)) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ati::addServer(std::shared_ptr<SocketServer> server)
{
	Mutex::Lock lock(mMutex) ;
	{
		mServers.push_back(server) ;

		// Create socket handlers - 1 for each of the maximum supported clients
		for (unsigned idx=0; idx < server->getMaxConnections(); ++idx)
		{
			std::shared_ptr<TestInterfaceBase> tif( TestInterfaceFactory::createInstance() ) ;
			std::shared_ptr<ITif> itif(std::dynamic_pointer_cast<ITif>(tif)) ;

			mTif.push_back(itif) ;
			server->addSocketHandlers(tif);

			// Apply any actions
			for (auto action : mActions)
			{
				if (!(*action)(server, itif))
					return false ;
			}
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Ati::disconnectClients()
{
	Mutex::Lock lock(mMutex) ;

	for (auto server : mServers)
		server->disconnectClients();
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int Ati::run()
{

//std::cerr << "ATI: run" << std::endl ;

	{
		// Add to list of actions
		Mutex::Lock lock(mMutex) ;
		addActionNoMutex(std::make_shared<TifStartAction>(this)) ;

		for (auto server : mServers)
			server->start();
	}

	kickSoftwareWatchdog() ;
	Task::msSleep( 10 );	// make sure the RTI is running before calling the isRunning() method

	bool isRunning(false) ;
	do {

		isRunning = false ;

		{
			Mutex::Lock lock(mMutex) ;
			for (auto server : mServers)
			{
				if (server->isRunning())
					isRunning = true ;
			}
		}

		kickSoftwareWatchdog() ;
		Task::msSleep( 1000 );

	} while (isRunning) ;

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
void Ati::addAction(std::shared_ptr<TifAction> action)
{
	// Add to list of actions
	Mutex::Lock lock(mMutex) ;
	addActionNoMutex(action) ;
}

//-------------------------------------------------------------------------------------------------------------
void Ati::addActionNoMutex(std::shared_ptr<TifAction> action)
{
	// Add to list of actions
	mActions.push_back(action) ;
}
