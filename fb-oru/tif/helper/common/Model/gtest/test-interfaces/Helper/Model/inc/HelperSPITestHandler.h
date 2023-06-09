/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HelperSPITestHandler.h
 * \brief     Test methods for Helper
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __HELPERSPITESTHANDLER__H_
#define __HELPERSPITESTHANDLER__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <vector>
#include <memory>
#include "SPITestHelper.h"
#include "IRtiMsgParser.h"
#include "Nodes/EntryFunc.h"

// Add any specific includes here %%-->

// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class HelperSPITestHandler: public EntryFunc
{
public:

	HelperSPITestHandler( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~HelperSPITestHandler();

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

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
	 *   HEXINT busid
	 *   HEXINT chipsel
	 *   HEXINT clkdiv
	 *   ENUM(default:option) clkpha
	 *   ENUM(rising:falling) clkedge
	 *   [HEXINT wBits]
	 *   [HEXINT rBits]
	 *
	 */
	void get( DataVariantList *callList, DataVariantList *returnList );

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
	void lock( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   HEXINT address
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   HEXINT data
	 *
	 */
	void read( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   [HEXINT busid]
	 *   [HEXINT chipsel]
	 *   [HEXINT clkdiv]
	 *   [ENUM(default:option) clkpha]
	 *   [ENUM(rising:falling) clkedge]
	 *   [HEXINT wBits]
	 *   [HEXINT rBits]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void set( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   HEXINT busId
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setbus( DataVariantList *callList, DataVariantList *returnList );

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
	void unlock( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   HEXINT data
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void write( DataVariantList *callList, DataVariantList *returnList );






// Add any extra methods %%-->

// <--%%

private:
	std::shared_ptr<SPITestHelper> mHelper ;
};



} // Mplane

#endif /* __HELPERSPITESTHANDLER__H_*/
