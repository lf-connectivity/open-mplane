/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IOriCtrlMgmt.h
 * \brief     Interface for ORI Control and Management Service
 *
 *
 * \details   Defines the expected interface for the ORI Control and Management Service
 *
 */

#ifndef IORI_CTRL_MGMT_H_
#define IORI_CTRL_MGMT_H_

#include <memory>
#include "GlobalTypeDefs.h"

namespace Mplane
{

/*! @brief ORI Control and Management
 *
 * The purpose of the IOriCtrlMgmt class is to provide a generic
 * interface to the ORI Control and Management entity.
 *
 * The ORI Control and Management entity implements the singleton pattern so that only one
 * ORI Control and Management entity can exist with the system.
 *
 *
 */
class IOriCtrlMgmt
{
public:
	virtual ~IOriCtrlMgmt() {}

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the IOriCtrlMgmt within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IOriCtrlMgmt> getInstance( void );

    /**
     * Method used to create the TCP Ports (sockets) required for ORI.
     */
    virtual ReturnType::State createOriTcpPorts( void ) = 0;

} ;

}

#endif /* IORI_CTRL_MGMT_H_ */
