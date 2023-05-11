/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangHandlerMgr.h
 * \brief     A manager that instantiates all of the application's YANG handlers
 *
 *
 * \details   There will be a singleton of this class which instantiates all of the required handlers for the specific application
 * 			  Singleton needs to be created for every application in the application-specific directory
 *
 */


#ifndef VYMS_INC_IYANGHANDLERMGR_H_
#define VYMS_INC_IYANGHANDLERMGR_H_

#include <memory>
#include <string>

#include "IYangModuleMgr.h"
#include "IYangHandler.h"

#include "DataVariant.h"

namespace Mplane {

/*!
 * \class  IYangHandlerMgr
 * \brief
 * \details
 *
 */
class IYangHandlerMgr {
public:
	IYangHandlerMgr() {}
	virtual ~IYangHandlerMgr() {}

	/**
	 * Create the singleton
	 */
	static std::shared_ptr<IYangHandlerMgr> create(std::shared_ptr<IYangModuleMgr> moduleMgr) ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<IYangHandlerMgr> singleton() ;

	/**
	 * Run the initialisation of the handlers (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() =0 ;

	/**
	 * Add a YANG handler to the list that this manager manages
	 */
	virtual bool registerHandler(std::shared_ptr<IYangHandler> handler) =0 ;


	/**
	 * Debug
	 */
	virtual bool testCallback(const std::string& xpath, std::shared_ptr<DataVariant> value) =0 ;


} ;

}

#endif /* VYMS_INC_IYANGHANDLERMGR_H_ */
