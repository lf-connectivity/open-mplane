/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceMgr.h
 * \brief     Manager of tracing files
 *
 *
 * \details   Singleton for collecting the tracing files in an application and for generating those files
 *
 */


#ifndef TRACE_INC_TRACEMGR_H_
#define TRACE_INC_TRACEMGR_H_

#include "ORanLogFileMgr.h"
#include "ITraceMgr.h"

namespace Mplane
{

/*!
 * \class  TraceMgr
 * \brief
 * \details
 *
 */
class TraceMgr : public virtual ITraceMgr, public ORanLogFileMgr
{
public:
	TraceMgr();
	virtual ~TraceMgr();

private:

private:

};

}

#endif /* TRACE_INC_TRACEMGR_H_ */
