/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICUPlaneConnectService.h
 * \brief     ORAN C/U-Plane Connectivity Service virtual interface
 *
 *
 * \details   Virtual interface for ORAN C/U-Plane Connectivity supervision Service.
 *
 */

#ifndef _VYMS_INC_ICUPLANE_CONNECT_SERVICE_H_
#define _VYMS_INC_ICUPLANE_CONNECT_SERVICE_H_

#include <memory>
#include <string>

#include "GlobalTypeDefs.h"

namespace Mplane
{
	class ICUPlaneConnectService
	{
	public:
		ICUPlaneConnectService() {}
		virtual ~ICUPlaneConnectService() {}

		static std::shared_ptr<ICUPlaneConnectService> CUPlaneConnectServiceSingleton(void);	//!> C/U-Plane Connectivity Service singleton interface
	};
}

#endif /* _VYMS_INC_ICUPLANE_CONNECT_SERVICE_H_ */
