/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CfrTestHelper.h
 * \brief     Test helper for common
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __CFRTESTHELPER__H_
#define __CFRTESTHELPER__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <vector>
#include <memory>
#include "IRtiMsgParser.h"
#include "DataVariant.h"

// Add any specific includes here %%-->
#include "ITifIoctl.h"
// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class CfrTestHelper
// Add any extra inheritance %%-->

// <--%%
{
public:

	// Add any class settings %%-->

	// <--%%

	// singleton
	static std::shared_ptr<CfrTestHelper> getInstance() ;


	CfrTestHelper();

    virtual ~CfrTestHelper();

	/**
	 * Called with:
	 *   [BOOL(OFF:ON) enable]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void set( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_TX_PORTS}} index
	 *   FLOAT[] threshold (dB)
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setThresholds( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	 *   INT{1..${NUM_TX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   FLOAT[] threshold (dB)
	 *
	 */
	void showThresholds( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );






// Add any extra methods %%-->
private:
	std::shared_ptr<ITifIoctl> getCfrWorker() const ;
// <--%%

};



// Add any Mplane namespace code here %%-->

// <--%%


} // Mplane

// Add any global namespace code here %%-->

// <--%%


#endif /* __CFRTESTHELPER__H_*/
