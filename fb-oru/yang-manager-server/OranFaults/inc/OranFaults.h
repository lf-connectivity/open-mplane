/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranFaults.h
 * \brief     A file to contain the ORAN fault handler
 *
 *
 * \brief     This file defines ORAN fault handler
 *
 */

#ifndef _ORAN_FAULTS_H_
#define _ORAN_FAULTS_H_

// Includes go here, before the namespace
#include <vector>
#include <memory>

#include "IFault.h"

namespace Mplane
{
/*! \brief ORAN faults class.
 *
 * The Fault class contains all the ORAN faults and is instantiated
 * during application initialisation.
 */
class OranFaults
{
public:
	static std::shared_ptr<OranFaults> getInstance();


	OranFaults();
	virtual ~OranFaults();

	// C/U-Plane connectivity faults
	std::shared_ptr<IFault> mCUPlaneConnectivityMajorFault;
	std::shared_ptr<IFault> mCUPlaneConnectivityMinorFault;

	// C/U-Plane message content faults
	std::shared_ptr<IFault> mCUPlaneMsgContentMajorFault;
	std::shared_ptr<IFault> mCUPlaneMsgContentMinorFault;

};  // end of class OranFaults

}
#endif /* _ORAN_FAULTS_H_ */
