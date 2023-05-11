/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootMgr.h
 * \brief     Manager of troubleshooting files
 *
 *
 * \details   Singleton for collecting the troubleshooting files in an application and for generating those files
 *
 */


#ifndef TROUBLESHOOTING_INC_TROUBLESHOOTMGR_H_
#define TROUBLESHOOTING_INC_TROUBLESHOOTMGR_H_

#include "ORanLogFileMgr.h"
#include "ITroubleshootMgr.h"

namespace Mplane
{

/*!
 * \class  TroubleshootMgr
 * \brief
 * \details
 *
 */
class TroubleshootMgr : public virtual ITroubleshootMgr, public ORanLogFileMgr
{
	public:
		TroubleshootMgr();
		virtual ~TroubleshootMgr();

	protected:

	private:

};

}

#endif /* TROUBLESHOOTING_INC_TROUBLESHOOTMGR_H_ */
