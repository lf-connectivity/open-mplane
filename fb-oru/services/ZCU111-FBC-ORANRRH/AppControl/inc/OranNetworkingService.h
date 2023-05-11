/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranNetworkingService.h
 * \brief
 *
 *
 */


#ifndef Zcu111_Zcu111APPCONTROL_INC_ORANNETWORKINGSERVICE_H_
#define Zcu111_Zcu111APPCONTROL_INC_ORANNETWORKINGSERVICE_H_

#include "Zcu111BaseNetworkingService.h"

namespace Mplane {

/*!
 * \class  OranNetworkingService
 * \brief
 * \details
 *
 */
class OranNetworkingService : public Zcu111BaseNetworkingService {
public:
	OranNetworkingService(const std::string& interface) ;
	virtual ~OranNetworkingService() ;

} ;

}

#endif /* Zcu111_Zcu111APPCONTROL_INC_ORANNETWORKINGSERVICE_H_ */
