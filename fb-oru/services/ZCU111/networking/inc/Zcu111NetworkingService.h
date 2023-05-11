/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111NetworkingService.h
 * \brief
 *
 *
 */


#ifndef Zcu111_Zcu111APPCONTROL_INC_Zcu111NETWORKINGSERVICE_H_
#define Zcu111_Zcu111APPCONTROL_INC_Zcu111NETWORKINGSERVICE_H_

#include "Zcu111BaseNetworkingService.h"

namespace Mplane {

/*!
 * \class  Zcu111NetworkingService
 * \brief
 * \details
 *
 */
class Zcu111NetworkingService : public Zcu111BaseNetworkingService {
public:
	Zcu111NetworkingService(const std::string& interface) ;
	virtual ~Zcu111NetworkingService() ;

} ;

}

#endif /* Zcu111_Zcu111APPCONTROL_INC_Zcu111NETWORKINGSERVICE_H_ */
