/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanUdpEcho.cpp
 * \brief     Module ORanUdpEcho interface
 *
 *
 * \details   This file defines the YANG module o-ran-udp-echo interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-udp-echo"
 *            YANG Filename:    "o-ran-udp-echo.yang"
 *            Module Prefix:    "o-ran-echo"
 *            Module namespace: "urn:o-ran:udpecho:1.0"
 *
 * Add user description here
 *
 * %%->

 * <-%%
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleORanUdpEcho.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanUdpEcho_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************

// *****************************************************************************
// Leafs
// *****************************************************************************

// *****************************************************************************
// References
// *****************************************************************************

// *****************************************************************************
// Containers
// *****************************************************************************
// -----------------------------------------------------------------------------
// Container:   udp-echo
// Description: container for udp echo
// -----------------------------------------------------------------------------
CntUdpEcho::CntUdpEcho(uint32_t id) : YangContainer("udp-echo", id) {}

CntUdpEcho::~CntUdpEcho() {}

YangResult_E
CntUdpEcho::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /udp-echo/udp-echo-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpUdpEchoGroup udpEchoGroupInst(ITEM_UDP_ECHO_GROUP);
  udpEchoGroupInst.initialise();
  addGroup(udpEchoGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    udp-echo-group
// Description:
// -----------------------------------------------------------------------------
GrpUdpEchoGroup::GrpUdpEchoGroup(uint32_t id)
    : YangGroup("udp-echo-group", id) {}

GrpUdpEchoGroup::~GrpUdpEchoGroup() {}

YangResult_E
GrpUdpEchoGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /udp-echo-group/enable-udp-echo
  // Description: whether O-RU's UDP ech server is enabled
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafEnableUdpEcho enableUdpEchoInst(ITEM_ENABLE_UDP_ECHO);
  addLeaf(enableUdpEchoInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /udp-echo-group/dscp-config
  // Description: configuration of UDP echo DSCP
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafDscpConfig dscpConfigInst(ITEM_DSCP_CONFIG);
  addLeaf(dscpConfigInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /udp-echo-group/echo-replies-transmitted
  // Description: The total number of UDP echo replies transmitted by the O-RU.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafEchoRepliesTransmitted echoRepliesTransmittedInst(
      ITEM_ECHO_REPLIES_TRANSMITTED);
  addLeaf(echoRepliesTransmittedInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /udp-echo-group/enable-udp-echo
// Description: whether O-RU's UDP ech server is enabled
// -----------------------------------------------------------------------------
GrpUdpEchoGroup::LeafEnableUdpEcho::LeafEnableUdpEcho(uint32_t id)
    : YangLeaf("enable-udp-echo", id) {}

GrpUdpEchoGroup::LeafEnableUdpEcho::~LeafEnableUdpEcho() {}

// -----------------------------------------------------------------------------
// Leaf:        /udp-echo-group/dscp-config
// Description: configuration of UDP echo DSCP
// -----------------------------------------------------------------------------
GrpUdpEchoGroup::LeafDscpConfig::LeafDscpConfig(uint32_t id)
    : YangLeaf("dscp-config", id) {}

GrpUdpEchoGroup::LeafDscpConfig::~LeafDscpConfig() {}

// -----------------------------------------------------------------------------
// Leaf:        /udp-echo-group/echo-replies-transmitted
// Description: The total number of UDP echo replies transmitted by the O-RU.
// -----------------------------------------------------------------------------
GrpUdpEchoGroup::LeafEchoRepliesTransmitted::LeafEchoRepliesTransmitted(
    uint32_t id)
    : YangLeaf("echo-replies-transmitted", id) {}

GrpUdpEchoGroup::LeafEchoRepliesTransmitted::~LeafEchoRepliesTransmitted() {}

// *****************************************************************************
// Lists
// *****************************************************************************

// *****************************************************************************
// Choices
// *****************************************************************************

// *****************************************************************************
// Notifications
// *****************************************************************************

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-udp-echo
// Description: This module covers off aspects of interface transport
//              verification for UDP/IP based C/U plane connections based on UDP
//              Echo.
//
//              Copyright 2019 the O-RAN Alliance.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
//              CONTRIBUTORS 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES,
//              INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//              MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//              DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
//              CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
//              USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
//              AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//              LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//              IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//              THE POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following
//              conditions are met:
//
//              * Redistributions of source code must retain the above copyright
//              notice, this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above
//              copyright notice, this list of conditions and the above
//              disclaimer in the documentation and/or other materials provided
//              with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived
//              from this software without specific prior written permission.
// -----------------------------------------------------------------------------
ModuleORanUdpEcho::ModuleORanUdpEcho(uint32_t id)
    : YangModule(
          "o-ran-udp-echo",
          "o-ran-udp-echo.yang",
          "o-ran-echo",
          "urn:o-ran:udpecho:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /udp-echo
  // Description: container for udp echo
  // -----------------------------------------------------------------------------
  CntUdpEcho udpEchoInst(ITEM_UDP_ECHO);
  udpEchoInst.initialise();
  addContainer(udpEchoInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanUdpEcho::~ModuleORanUdpEcho() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanUdpEcho::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(std::make_shared<ModuleORanUdpEcho>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanUdpEcho::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
