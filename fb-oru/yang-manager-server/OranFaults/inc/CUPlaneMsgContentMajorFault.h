/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneMsgContentMajorFault.h
 * \brief     ORAN C/U-Plane Message Content  major fault
 *
 *
 * \details   ORAN C/U-Plane Message Content major fault container
 *
 */


#ifndef CUPLANE_MSG_CONTENT_MAJOR_FAULT_H_
#define CUPLANE_MSG_CONTENT_MAJOR_FAULT_H_

#include "Fault.h"

namespace Mplane
{

class CUPlaneMsgContentMajorFault : public Fault
{
public:
	CUPlaneMsgContentMajorFault();
	virtual ~CUPlaneMsgContentMajorFault();
	static const char* NAME;

};

}

#endif /* CUPLANE_MSG_CONTENT_MAJOR_FAULT_H_ */
