/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalDownloadMgrSingleton.cpp
 * \brief     SIngleton to create the CalDownloadManagement object
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CalDownloadManagement.h"

using namespace Mplane ;


//-------------------------------------------------------------------------------------------------------------
class CalDownloadMgr : public CalDownloadManagement {
public:
	CalDownloadMgr() :
		CalDownloadManagement()
	{
	}

	virtual ~CalDownloadMgr() {}
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICalDownloadManagement> ICalDownloadManagement::getInstance()
{
	static std::shared_ptr<ICalDownloadManagement> instance(new CalDownloadMgr()) ;
	static int start = std::dynamic_pointer_cast<CalDownloadManagement>(instance)->start() ;

	// avoid compiler warning
	int rc = start ; start = rc ;

	return instance ;
}
