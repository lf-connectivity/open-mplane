/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectivityMajorFault.h
 * \brief     ORAN C/U-Plane Connectivity major fault
 *
 *
 * \details   ORAN C/U-Plane Connectivity major fault container
 *
 */

#ifndef CUPLANE_CONNECTIVITY_MAJOR_FAULT_H_
#define CUPLANE_CONNECTIVITY_MAJOR_FAULT_H_

#include "Fault.h"

namespace Mplane
{

class CUPlaneConnectivityMajorFault : public Fault
{
public:
	CUPlaneConnectivityMajorFault();
	virtual ~CUPlaneConnectivityMajorFault();
	static const char* NAME;

};

}

#endif /* CUPLANE_CONNECTIVITY_MAJOR_FAULT_H_ */
