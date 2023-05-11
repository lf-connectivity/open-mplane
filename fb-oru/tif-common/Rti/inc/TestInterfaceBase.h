/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestInterfaceBase.h
 * \brief     Base class for the test interface
 *
 *
 * \details   Provides common base "devices" such as 'tif:settings', 'tif:scripts' etc.
 *
 */


#ifndef TESTINTERFACEBASE_H_
#define TESTINTERFACEBASE_H_

#include "ITif.h"
#include "RtiMsgHandler.h"

namespace Mplane {

class TestInterfaceBase : public virtual ITif, public RtiMsgHandler
{
public:

    TestInterfaceBase();

    ~TestInterfaceBase();

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

};

}
#endif /* TESTINTERFACEBASE_H_ */
