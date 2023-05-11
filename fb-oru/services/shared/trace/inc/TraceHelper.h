/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TraceHelper.h
 * \brief     Static methods for setting up trace
 *
 *
 * \details   Static methods for setting up trace
 *
 */


#ifndef SHARED_TRACE_INC_TRACEHELPER_H_
#define SHARED_TRACE_INC_TRACEHELPER_H_


namespace Mplane
{

/*!
 * \class  TraceHelper
 * \brief
 * \details
 *
 */
class TraceHelper
{
public:
	/**
	 * Add the trace files that all applications will want
	 */
	static void commonSetup();

};

}

#endif /* SHARED_TRACE_INC_TRACEHELPER_H_ */
