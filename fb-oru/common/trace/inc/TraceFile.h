/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceFile.h
 * \brief     Base class implementing a trace log file
 *
 *
 * \details   Base class implementing a trace log file. This base class needs a data gather function to be
 *            defined. Otherwise derived classes can override the dataGather() method.
 *
 */


#ifndef TRACING_INC_TRACEFILE_H_
#define TRACING_INC_TRACEFILE_H_

#include "ORanLogFile.h"

namespace Mplane
{

/*!
 * \class  TraceFile
 * \brief
 * \details
 *
 */
class TraceFile : public ORanLogFile
{
	public:
		TraceFile(const std::string & filename);
		virtual ~TraceFile();

	protected:

	private:

};

}

#endif /* TRACING_INC_TRACEFILE_H_ */
