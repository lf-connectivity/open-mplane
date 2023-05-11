/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111BaseNetworkingService.h
 * \brief
 *
 *
 */


#ifndef Zcu111_Zcu111APPCONTROL_INC_Zcu111BaseNetworkingService_H_
#define Zcu111_Zcu111APPCONTROL_INC_Zcu111BaseNetworkingService_H_

#include "NetworkingService.h"

namespace Mplane {

/*!
 * \class  Zcu111BaseNetworkingService
 * \brief
 * \details
 *
 */
class Zcu111BaseNetworkingService : public NetworkingService {
public:
	Zcu111BaseNetworkingService(const std::string& interface) ;
	virtual ~Zcu111BaseNetworkingService() ;

} ;

}

#endif /* Zcu111_Zcu111APPCONTROL_INC_Zcu111BaseNetworkingService_H_ */
