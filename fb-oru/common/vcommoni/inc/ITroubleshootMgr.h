/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITroubleshootMgr.h
 * \brief     API for manager of troubleshooting files
 *
 *
 * \details   Singleton for collecting the troubleshooting files in an application and for generating those files
 *
 */


#ifndef VCOMMONI_INC_ITROUBLESHOOTMGR_H_
#define VCOMMONI_INC_ITROUBLESHOOTMGR_H_

#include <string>
#include <memory>
#include <vector>

#include "IORanLogFileMgr.h"

namespace Mplane
{

/*!
 * \class  ITroubleshootMgr
 * \brief
 * \details
 *
 */
class ITroubleshootMgr : public virtual IORanLogFileMgr
{
public:

	/**
	 * Singleton
	 */
	static std::shared_ptr<IORanLogFileMgr> singleton();

	ITroubleshootMgr() {}
	virtual ~ITroubleshootMgr() {}

} ;

}

#endif /* VCOMMONI_INC_ITROUBLESHOOTMGR_H_ */
