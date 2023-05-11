/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectivityMinorFault.h
 * \brief     ORAN C/U-Plane Connectivity minor fault
 *
 *
 * \details   ORAN C/U-Plane Connectivity minor fault container
 *
 */

#ifndef CUPLANE_CONNECTIVITY_MINOR_FAULT_H_
#define CUPLANE_CONNECTIVITY_MINOR_FAULT_H_

#include "Fault.h"

namespace Mplane
{

class CUPlaneConnectivityMinorFault : public Fault
{
public:
	CUPlaneConnectivityMinorFault();
	virtual ~CUPlaneConnectivityMinorFault();
	static const char* NAME;

};

}

#endif /* CUPLANE_CONNECTIVITY_MINOR_FAULT_H_ */
