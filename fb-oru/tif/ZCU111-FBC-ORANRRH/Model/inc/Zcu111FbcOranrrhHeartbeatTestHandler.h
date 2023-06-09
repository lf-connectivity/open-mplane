/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHeartbeatTestHandler.h
 * \brief     Test methods for ZCU111-FBC-ORANRRH
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __ZCU111FBCORANRRHHEARTBEATTESTHANDLER__H_
#define __ZCU111FBCORANRRHHEARTBEATTESTHANDLER__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <vector>
#include <memory>
#include "HeartbeatTestHelper.h"
#include "ITif.h"
#include "IRtiMsgParser.h"
#include "Nodes/EntryFunc.h"

// Add any specific includes here %%-->

// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class Zcu111FbcOranrrhHeartbeatTestHandler: public virtual ITifEntry, public EntryFunc
{
public:

	Zcu111FbcOranrrhHeartbeatTestHandler( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~Zcu111FbcOranrrhHeartbeatTestHandler();

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

	/**
	 * Special constructor - only to be used for calling the static registerMethods()
	 */
	Zcu111FbcOranrrhHeartbeatTestHandler();

	/**
	 * Called by ITif::inject() to get this object to add it's entries
	 * @param tif
	 * @return true if ok
	 */
	virtual bool registerEntry(ITif* tif) override ;

protected:

    virtual std::string operator()(const std::string& functionName) ;

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   BOOL(OFF:ON) enable
	 *
	 */
	void getEnable( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   BOOL(OK:EXPIRED) state
	 *
	 */
	void getState( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   INT timeout (s)
	 *
	 */
	void getTimeout( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void ping( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   BOOL(OFF:ON) enable
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setEnable( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT timeout (s)
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setTimeout( DataVariantList *callList, DataVariantList *returnList );


	/**
	 * Setter method for variable enable
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param value DataVariant value
	 * @param returnList DataVariantList use to return variable value
	 * @return true if variable set; false if unable to set variable
	 *
	 */
	static bool enableSet(  const std::string& pathname, DataVariant *value, DataVariantList *returnList ) ;

	/**
	 * Getter method for variable enable
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void enableGet(  const std::string& pathname, DataVariantList *returnList ) ;

	/**
	 * Setter method for variable timeout
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param value DataVariant value
	 * @param returnList DataVariantList use to return variable value
	 * @return true if variable set; false if unable to set variable
	 *
	 */
	static bool timeoutSet(  const std::string& pathname, DataVariant *value, DataVariantList *returnList ) ;

	/**
	 * Getter method for variable timeout
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void timeoutGet(  const std::string& pathname, DataVariantList *returnList ) ;


	/**
	 * Getter method for read-only variable state
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void stateGet(  const std::string& pathname, DataVariantList *returnList ) ;




// Add any extra methods %%-->

// <--%%

private:
	std::shared_ptr<HeartbeatTestHelper> mHelper ;
};



} // Mplane

#endif /* __ZCU111FBCORANRRHHEARTBEATTESTHANDLER__H_*/
