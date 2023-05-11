/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandler.h
 * \brief     Handler layer between YANG models and application
 *
 *
 * \details   Registers callbacks with the YANG models so that changes in YANG model parameters can be reflected in the application
 *
 */


#ifndef YANG_HANDLERS_INC_YANGHANDLER_H_
#define YANG_HANDLERS_INC_YANGHANDLER_H_

#include <string>
#include <memory>

#include "IYangPersist.h"
#include "IYangHandler.h"
#include "IYangModuleMgr.h"

#include "ICarrier.h"

#include "YangModule.h"

namespace Mplane {

/*!
 * \class  YangHandler
 * \brief
 * \details
 *
 */
class YangHandler : public virtual IYangHandler {
public:
	YangHandler(const std::string& name, std::shared_ptr<IYangModuleMgr> moduleMgr) ;
	virtual ~YangHandler() ;

	/**
	 * Name (mainly for debug)
	 */
	virtual std::string name() const override ;

	/**
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override ;

protected:
	/**
	 * Get the module manager (to get the modules)
	 */
	std::shared_ptr<IYangModuleMgr> moduleMgr() const ;

	/**
	 * get the persistence object
	 */
	std::shared_ptr<IYangPersist> persistMgr() const ;

	/**
	 * Add this/these paths to a list of paths that will be stored in flash and restored on restart
	 */
	virtual void makePersistent(const std::set<std::string>& xpath) ;

	/**
	 * Add this path to a list of paths that will be stored in flash and restored on restart
	 */
	virtual void makePersistent(const std::string& xpath) ;


	/**
	 * Extract the leaf name of this xpath
	 */
	std::string leafName(const std::string& xpath) const ;

	/**
	 * Get the *first* index (i.e. in "[]") contained in the xpath. Sets key and value when xpath is of the form:
	 *   /o-ran-uplane-conf:user-plane-configuration/rx-array-carriers[name='rxcco']/name
	 *
	 *   This will set: listName=rx-array-carriers, key=name, value=rxcc0
	 *
	 * will only set value when xpath is of the form:
	 *   /o-ran-uplane-conf:user-plane-configuration/rx-array-carriers['rxcco']/name
	 *
	 *   This will set: listName=rx-array-carriers, key=, value=rxcc0
	 *
	 * Value will have the '' stripped off
	 *
	 * @return true if found
	 */
	bool listIndex(const std::string& xpath, std::string& listName, std::string& key, std::string& value) const ;

	/**
	 * Get the *first* index (i.e. in "[]") contained in the xpath. Value string is converted into an integer
	 */
	bool listIndex(const std::string& xpath, std::string& listName, std::string& key, int& value) const ;

	/**
	 * Get an unsigned value. Sets ok to TRUE on success; FALSE on any error
	 */
	unsigned getParamUint16(uint32_t moduleId, const std::string& xpath, bool& ok) ;

	/**
	 * Get a parameter value. Returns null pointer on error
	 */
	std::shared_ptr<YangParam> getParam(uint32_t moduleId, const std::string& xpath) ;

	/**
	 * Convert an ORAN frame-struct into an ICarrier fft size type
	 */
	ICarrier::FFTsizeType frameStructToFFTsize(uint8_t frameStruct) ;

	/**
	 * Convert an ORAN frame-struct into an ICarrier SCS type
	 */
	ICarrier::ScsType frameStructToScsType(uint8_t frameStruct) ;


private:
	std::string mName ;
	std::shared_ptr<IYangModuleMgr> mModuleMgr ;
	std::shared_ptr<IYangPersist> mPersist ;
} ;

}

#endif /* YANG_HANDLERS_INC_YANGHANDLER_H_ */
