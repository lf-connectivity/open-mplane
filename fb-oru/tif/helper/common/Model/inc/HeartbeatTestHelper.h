/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HeartbeatTestHelper.h
 * \brief     Test helper for common
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __HEARTBEATTESTHELPER__H_
#define __HEARTBEATTESTHELPER__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <vector>
#include <memory>
#include "IRtiMsgParser.h"
#include "DataVariant.h"

// Add any specific includes here %%-->

// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class HeartbeatTestHelper
// Add any extra inheritance %%-->

// <--%%
{
public:

	// Add any class settings %%-->

	// <--%%

	// singleton
	static std::shared_ptr<HeartbeatTestHelper> getInstance() ;


	HeartbeatTestHelper();

    virtual ~HeartbeatTestHelper();

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
	void getEnable( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	void getState( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	void getTimeout( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	void ping( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	void setEnable( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	void setTimeout( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );


	/**
	 * Setter method for variable enable
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param value DataVariant value
	 * @param returnList DataVariantList use to return variable value
	 * @return true if variable set; false if unable to set variable
	 *
	 */
	static bool enableSet( const std::string& pathname, DataVariant *value, DataVariantList *returnList ) ;

	/**
	 * Getter method for variable enable
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void enableGet( const std::string& pathname, DataVariantList *returnList ) ;

	/**
	 * Setter method for variable timeout
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param value DataVariant value
	 * @param returnList DataVariantList use to return variable value
	 * @return true if variable set; false if unable to set variable
	 *
	 */
	static bool timeoutSet( const std::string& pathname, DataVariant *value, DataVariantList *returnList ) ;

	/**
	 * Getter method for variable timeout
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void timeoutGet( const std::string& pathname, DataVariantList *returnList ) ;


	/**
	 * Getter method for read-only variable state
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void stateGet( const std::string& pathname, DataVariantList *returnList ) ;




// Add any extra methods %%-->

// <--%%

};



// Add any Mplane namespace code here %%-->

// <--%%


} // Mplane

// Add any global namespace code here %%-->

// <--%%


#endif /* __HEARTBEATTESTHELPER__H_*/
