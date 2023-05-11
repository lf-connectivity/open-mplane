/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneMsgContentMinorFault.h
 * \brief     ORAN C/U-Plane Message Content minor fault
 *
 *
 * \details   ORAN C/U-Plane Message Content minor fault container
 *
 */

#ifndef CUPLANE_MSG_CONTENT_MINOR_FAULT_H_
#define CUPLANE_MSG_CONTENT_MINOR_FAULT_H_

#include "Fault.h"

namespace Mplane
{

class CUPlaneMsgContentMinorFault : public Fault
{
public:
	CUPlaneMsgContentMinorFault();
	virtual ~CUPlaneMsgContentMinorFault();
	static const char* NAME;

};

}

#endif /* CUPLANE_MSG_CONTENT_MINOR_FAULT_H_ */
