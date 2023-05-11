/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITifIoctl.h
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


#ifndef ITIFIOCTL_H_
#define ITIFIOCTL_H_

#include <string>
#include <vector>
#include <map>

#include <memory>
#include "DataVariant.h"

namespace Mplane {

class ITifIoctl {
public:
	ITifIoctl() {} ;
	virtual ~ITifIoctl() {} ;

	/**
	 * Get a shared pointer to the named object providing an ITifIoctl interface. The object will be a child of this
	 * object
	 * @param objectName
	 * @return shared pointer to object
	 */
	virtual std::shared_ptr<ITifIoctl> getObject(const std::string& objectName) =0 ;

	/**
	 * Execute the command with the provided arguments.
	 * @param command		command string
	 * @param callerArgs	calling arguments
	 * @param returnArgs	returned values
	 * @return true if command executed successfully; false if not
	 */
	virtual bool executeCommand(const std::string& command, DataVariantList* callerArgs, DataVariantList* returnArgs) =0 ;

	/**
	 * Check that command is available.
	 * @param command		command string
	 * @return true if command is available; false if not
	 */
	virtual bool isCommandAvailable(const std::string& command) const =0 ;

} ;

}

#endif /* ITIFIOCTL_H_ */
