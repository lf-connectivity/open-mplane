/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceExampleFile.h
 * \brief     A TraceFile for example
 *
 *
 * \details   A TraceFile for example
 *
 */


#ifndef SHARED_TRACE_INC_TRACEEXAMPLEFILE_H_
#define SHARED_TRACE_INC_TRACEEXAMPLEFILE_H_

#include "TraceFile.h"

namespace Mplane
{

/*!
 * \class  TraceExampleFile
 * \brief
 * \details
 *
 */
class TraceExampleFile : public TraceFile
{
public:
	TraceExampleFile();
	virtual ~TraceExampleFile();

protected:
	/**
	 * Data gather hook that can be overridden by derived classes. This default uses whatever data gather
	 * function has been registered.
	 */
	virtual std::string dataGather() override;

};

}

#endif /* SHARED_TRACE_INC_TRACEEXAMPLEFILE_H_ */
