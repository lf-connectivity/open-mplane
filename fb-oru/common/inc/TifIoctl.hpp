/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TifIoctl.hpp
 * \brief     IOCTL-like interface for test interface
 *
 *
 * \details   Provides a mechanism for test interface commands to access objects (that they don't have access to)
 * 			  indirectly via other objects they do have access to.
 *
 * 			  Using this interface, a test method that understands the details of a specific object can access it's
 * 			  methods through the common test interface, without us needing to provide the low-level object specifics
 * 			  to the test interface.
 *
 * 			  Any low-level object (we wish the test interface test commands to access) must provide this interface. Also,
 * 			  the object that has access to the low-level objects must also provide this interface.
 *
 */


#ifndef TIFIOCTL_HPP_
#define TIFIOCTL_HPP_

#include <stdexcept>
#include "ITifIoctl.h"

namespace Mplane {

template <typename TClass>
class TifIoctl : public virtual ITifIoctl {

public:
	typedef bool (TClass::*TMethod)(DataVariantList* callerArgs, DataVariantList* returnArgs) ;

protected:
	struct Command {
		Command(const std::string& _callerArgs, const std::string& _returnArgs, TMethod _method) :
			callerArgs(_callerArgs),
			returnArgs(_returnArgs),
			method(_method)
		{}

		Command() :
			callerArgs(""),
			returnArgs(""),
			method(NULL)
		{}

		std::string callerArgs ;
		std::string returnArgs ;
		TMethod method ;
	};

public:

	/**
	 * Constructor
	 * @param parent	Parent object
	 */
	explicit TifIoctl<TClass>(TClass& parent) :
		mParent(parent)
	{}

	virtual ~TifIoctl<TClass>()
	{}

	/**
	 * Get a shared pointer to the named object providing an ITifIoctl interface. The object will be a child of this
	 * object
	 * @param objectName
	 * @return shared pointer to object
	 */
	virtual std::shared_ptr<ITifIoctl> getObject(const std::string& objectName) override
	{
		std::map<std::string, std::shared_ptr<ITifIoctl> >::iterator iter( mObjects.find(objectName) ) ;
		if (iter == mObjects.end() )
			throw std::runtime_error("Requested object is not registered") ;

		return iter->second ;
	}

	/**
	 * Execute the command with the provided arguments.
	 * @param command		command string
	 * @param callerArgs	calling arguments
	 * @param returnArgs	returned values
	 * @return true if command executed successfully; false if not
	 */
	virtual bool executeCommand(const std::string& command, DataVariantList* callerArgs, DataVariantList* returnArgs) override
	{
		auto iter( mCommands.find(command) ) ;
		if (iter == mCommands.end() )
			throw std::runtime_error("Requested command is not registered") ;

		// Check the caller args - must call with same (or more) calling arguments
		if (!callerArgs->superset(iter->second.callerArgs))
			throw std::runtime_error("Caller args not a superset of registered command args") ;

		// check the return args - must need same (or less) return arguments
		if (!returnArgs->subset(iter->second.returnArgs))
			throw std::runtime_error("Return args not a subset of registered return args") ;

		// Ensure all required return args are in the return list
		returnArgs->addFields( iter->second.returnArgs.c_str() ) ;

		// execute command
		return (mParent.*(iter->second.method))(callerArgs, returnArgs) ;
	}

	/**
	 * Check that command is available.
	 * @param command		command string
	 * @return true if command is available; false if not
	 */
	virtual bool isCommandAvailable(const std::string& command) const override
	{
		auto iter( mCommands.find(command) ) ;
		if (iter == mCommands.end() )
			return false ;

		return true ;
	}

protected:

	/**
	 * Register a child object by a name so that it can be returned
	 * @param objectName
	 * @param object
	 */
	void registerObject(const std::string& objectName, std::shared_ptr<ITifIoctl> object)
	{
		mObjects[objectName] = object ;
	}

	void registerCommand(const std::string& command, const std::string& callerArgs, const std::string& returnArgs,
			TMethod method)
	{
		mCommands[command] = Command(callerArgs, returnArgs, method) ;
	}


private:
	// Parent ref
	TClass& mParent ;

	// Map object names to objects
	std::map<std::string, std::shared_ptr<ITifIoctl> >	mObjects ;

	// Map of commands
	std::map<std::string, Command>	mCommands ;

} ;

}

#endif /* TIFIOCTL_HPP_ */
