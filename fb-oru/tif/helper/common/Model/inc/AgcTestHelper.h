/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AgcTestHelper.h
 * \brief     Test helper for common
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __AGCTESTHELPER__H_
#define __AGCTESTHELPER__H_


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

class AgcTestHelper
// Add any extra inheritance %%-->

// <--%%
{
public:

	// Add any class settings %%-->

	// <--%%

	// singleton
	static std::shared_ptr<AgcTestHelper> getInstance() ;


	AgcTestHelper();

    virtual ~AgcTestHelper();

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   ENUM(auto:manual) mode
	 *
	 */
	void getMode( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(auto:manual) mode
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setMode( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	void show( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	void showDetail( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );






// Add any extra methods %%-->

// <--%%

};



// Add any Mplane namespace code here %%-->

// <--%%


} // Mplane

// Add any global namespace code here %%-->

// <--%%


#endif /* __AGCTESTHELPER__H_*/
