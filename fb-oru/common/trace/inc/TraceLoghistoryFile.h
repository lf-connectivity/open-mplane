/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceLoghistoryFile.h
 * \brief     An IORanLogFile for logging trace history
 *
 *
 * \details   Creates a tracing file which contains the rolling history of previous logs
 *
 */


#ifndef TRACE_INC_TRACELOGHISTORYFILE_H_
#define TRACE_INC_TRACELOGHISTORYFILE_H_

#include "TraceFile.h"

namespace Mplane
{

/*!
 * \class  TraceLoghistoryFile
 * \brief
 * \details
 *
 */
class TraceLoghistoryFile : public TraceFile
{
public:
	TraceLoghistoryFile(const std::string& filename = "history_trace.log");
	virtual ~TraceLoghistoryFile();

protected:
	/**
	 * Data gather hook that can be overridden by derived classes. This default uses whatever data gather function has been registered
	 */
	virtual std::string dataGather() override;

} ;

}

#endif /* TRACE_INC_TRACELOGHISTORYFILE_H_ */
