/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanAld.cpp
 * \brief     Module ORanAld interface
 *
 *
 * \details   This file defines the YANG module o-ran-ald interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-ald"
 *            YANG Filename:    "o-ran-ald.yang"
 *            Module Prefix:    "o-ran-ald"
 *            Module namespace: "urn:o-ran:ald:1.0"
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
#include "YangModuleORanAld.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanAld_NS;

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

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    ald-input
// Description:
// -----------------------------------------------------------------------------
GrpAldInput::GrpAldInput(uint32_t id) : YangGroup("ald-input", id) {}

GrpAldInput::~GrpAldInput() {}

YangResult_E
GrpAldInput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /ald-input/ald-req-msg
  // Description: Response message to be forwarded to ALD in type of
  // binary-string Type:        ???BINARY Units:
  // -----------------------------------------------------------------------------
  LeafAldReqMsg aldReqMsgInst(ITEM_ALD_REQ_MSG);
  addLeaf(aldReqMsgInst);

  // -----------------------------------------------------------------------------
  // Reference:   /ald-input/port-id
  // Description: Unique ALD port identifier reported by radio
  // Ref:
  // /o-ran-ald-port:ald-ports-io/o-ran-ald-port:ald-port/o-ran-ald-port:port-id
  // Units:
  // -----------------------------------------------------------------------------
  RefPortId portIdInst(ITEM_PORT_ID);
  addReference(portIdInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /ald-input/ald-req-msg
// Description: Response message to be forwarded to ALD in type of binary-string
// -----------------------------------------------------------------------------
GrpAldInput::LeafAldReqMsg::LeafAldReqMsg(uint32_t id)
    : YangLeaf("ald-req-msg", id) {}

GrpAldInput::LeafAldReqMsg::~LeafAldReqMsg() {}

// -----------------------------------------------------------------------------
// Reference:   /ald-input/port-id
// Description: Unique ALD port identifier reported by radio
// -----------------------------------------------------------------------------
GrpAldInput::RefPortId::RefPortId(uint32_t id)
    : YangReference(
          "port-id",
          id,
          "/o-ran-ald-port:ald-ports-io/o-ran-ald-port:ald-port/"
          "o-ran-ald-port:port-id") {}

GrpAldInput::RefPortId::~RefPortId() {}

// -----------------------------------------------------------------------------
// Grouping:    ald-output
// Description:
// -----------------------------------------------------------------------------
GrpAldOutput::GrpAldOutput(uint32_t id) : YangGroup("ald-output", id) {}

GrpAldOutput::~GrpAldOutput() {}

YangResult_E
GrpAldOutput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /ald-output/status
  // Description: Status of RPC handling seen from equipment perspective
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ald-output/error-message
  // Description: Detailed error message when the status is rejected. E.g. wrong
  // ALD port identifier was used in RPC received from Netconf Client Type:
  // string Units:
  // -----------------------------------------------------------------------------
  LeafErrorMessage errorMessageInst(ITEM_ERROR_MESSAGE);
  addLeaf(errorMessageInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ald-output/ald-resp-msg
  // Description: Response message forwarded from ALD in type of binary-string
  // Type:        ???BINARY
  // Units:
  // -----------------------------------------------------------------------------
  LeafAldRespMsg aldRespMsgInst(ITEM_ALD_RESP_MSG);
  addLeaf(aldRespMsgInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ald-output/frames-with-wrong-crc
  // Description: Number of frames with incorrect CRC (FCS) received from ALD -
  // running counter Type:        uint32 Units:
  // -----------------------------------------------------------------------------
  LeafFramesWithWrongCrc framesWithWrongCrcInst(ITEM_FRAMES_WITH_WRONG_CRC);
  addLeaf(framesWithWrongCrcInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ald-output/frames-without-stop-flag
  // Description: Number of frames without stop flag received from ALD - running
  // counter Type:        uint32 Units:
  // -----------------------------------------------------------------------------
  LeafFramesWithoutStopFlag framesWithoutStopFlagInst(
      ITEM_FRAMES_WITHOUT_STOP_FLAG);
  addLeaf(framesWithoutStopFlagInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ald-output/number-of-received-octets
  // Description: Number of octets received from HDLC bus - running counter
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfReceivedOctets numberOfReceivedOctetsInst(
      ITEM_NUMBER_OF_RECEIVED_OCTETS);
  addLeaf(numberOfReceivedOctetsInst);

  // -----------------------------------------------------------------------------
  // Reference:   /ald-output/port-id
  // Description: Unique ALD port identifier reported by radio
  // Ref:
  // /o-ran-ald-port:ald-ports-io/o-ran-ald-port:ald-port/o-ran-ald-port:port-id
  // Units:
  // -----------------------------------------------------------------------------
  RefPortId portIdInst(ITEM_PORT_ID);
  addReference(portIdInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /ald-output/status
// Description: Status of RPC handling seen from equipment perspective
// -----------------------------------------------------------------------------
GrpAldOutput::LeafStatus::LeafStatus(uint32_t id) : YangLeaf("status", id) {}

GrpAldOutput::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /ald-output/error-message
// Description: Detailed error message when the status is rejected. E.g. wrong
// ALD port identifier was used in RPC received from Netconf Client
// -----------------------------------------------------------------------------
GrpAldOutput::LeafErrorMessage::LeafErrorMessage(uint32_t id)
    : YangLeaf("error-message", id) {}

GrpAldOutput::LeafErrorMessage::~LeafErrorMessage() {}

// -----------------------------------------------------------------------------
// Leaf:        /ald-output/ald-resp-msg
// Description: Response message forwarded from ALD in type of binary-string
// -----------------------------------------------------------------------------
GrpAldOutput::LeafAldRespMsg::LeafAldRespMsg(uint32_t id)
    : YangLeaf("ald-resp-msg", id) {}

GrpAldOutput::LeafAldRespMsg::~LeafAldRespMsg() {}

// -----------------------------------------------------------------------------
// Leaf:        /ald-output/frames-with-wrong-crc
// Description: Number of frames with incorrect CRC (FCS) received from ALD -
// running counter
// -----------------------------------------------------------------------------
GrpAldOutput::LeafFramesWithWrongCrc::LeafFramesWithWrongCrc(uint32_t id)
    : YangLeaf("frames-with-wrong-crc", id) {}

GrpAldOutput::LeafFramesWithWrongCrc::~LeafFramesWithWrongCrc() {}

// -----------------------------------------------------------------------------
// Leaf:        /ald-output/frames-without-stop-flag
// Description: Number of frames without stop flag received from ALD - running
// counter
// -----------------------------------------------------------------------------
GrpAldOutput::LeafFramesWithoutStopFlag::LeafFramesWithoutStopFlag(uint32_t id)
    : YangLeaf("frames-without-stop-flag", id) {}

GrpAldOutput::LeafFramesWithoutStopFlag::~LeafFramesWithoutStopFlag() {}

// -----------------------------------------------------------------------------
// Leaf:        /ald-output/number-of-received-octets
// Description: Number of octets received from HDLC bus - running counter
// -----------------------------------------------------------------------------
GrpAldOutput::LeafNumberOfReceivedOctets::LeafNumberOfReceivedOctets(
    uint32_t id)
    : YangLeaf("number-of-received-octets", id) {}

GrpAldOutput::LeafNumberOfReceivedOctets::~LeafNumberOfReceivedOctets() {}

// -----------------------------------------------------------------------------
// Reference:   /ald-output/port-id
// Description: Unique ALD port identifier reported by radio
// -----------------------------------------------------------------------------
GrpAldOutput::RefPortId::RefPortId(uint32_t id)
    : YangReference(
          "port-id",
          id,
          "/o-ran-ald-port:ald-ports-io/o-ran-ald-port:ald-port/"
          "o-ran-ald-port:port-id") {}

GrpAldOutput::RefPortId::~RefPortId() {}

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
// Module:      o-ran-ald
// Description: This module defines the module for the ald communication.
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
ModuleORanAld::ModuleORanAld(uint32_t id)
    : YangModule(
          "o-ran-ald", "o-ran-ald.yang", "o-ran-ald", "urn:o-ran:ald:1.0", id)
// Add user code here
// %%->

// <-%%
{

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanAld::~ModuleORanAld() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanAld::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(std::make_shared<ModuleORanAld>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanAld::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
