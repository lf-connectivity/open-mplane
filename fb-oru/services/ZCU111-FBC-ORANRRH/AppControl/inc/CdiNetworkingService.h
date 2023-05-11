/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CdiNetworkingService.h
 * \brief     Networking for the debug interface
 *
 *
 */


#ifndef Zcu111_Zcu111APPCONTROL_INC_CDINETWORKINGSERVICE_H_
#define Zcu111_Zcu111APPCONTROL_INC_CDINETWORKINGSERVICE_H_

#include "Zcu111BaseNetworkingService.h"

// Uncomment this to run the BB networking algorithms on the CDI interface for testing
//#define TEST_BB_ON_CDI

namespace Mplane {

/*!
 * \class  CdiNetworkingService
 * \brief
 * \details
 *
 */
class CdiNetworkingService : public Zcu111BaseNetworkingService {
public:
	CdiNetworkingService(const std::string& interface) ;
	virtual ~CdiNetworkingService() ;

} ;

}

#endif /* Zcu111_Zcu111APPCONTROL_INC_CDINETWORKINGSERVICE_H_ */
