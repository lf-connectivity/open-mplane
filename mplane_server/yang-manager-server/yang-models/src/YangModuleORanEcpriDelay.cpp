/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanEcpriDelay.cpp
 * \brief     Module ORanEcpriDelay interface
 *
 *
 * \details   This file defines the YANG module o-ran-ecpri-delay interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-ecpri-delay"
 *            YANG Filename:    "o-ran-ecpri-delay.yang"
 *            Module Prefix:    "o-ran-msg5"
 *            Module namespace: "urn:o-ran:message5:1.0"
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
#include "YangModuleORanEcpriDelay.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanEcpriDelay_NS;

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
// Container:   ecpri-delay-message
// Description: top level tree covering off O-DU to O-RU msg5 delay measurement
// -----------------------------------------------------------------------------
CntEcpriDelayMessage::CntEcpriDelayMessage(uint32_t id)
    : YangContainer("ecpri-delay-message", id) {}

CntEcpriDelayMessage::~CntEcpriDelayMessage() {}

YangResult_E
CntEcpriDelayMessage::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /ecpri-delay-message/msg5-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpMsg5Group msg5GroupInst(ITEM_MSG5_GROUP);
  msg5GroupInst.initialise();
  addGroup(msg5GroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    msg5-group
// Description:
// -----------------------------------------------------------------------------
GrpMsg5Group::GrpMsg5Group(uint32_t id) : YangGroup("msg5-group", id) {}

GrpMsg5Group::~GrpMsg5Group() {}

YangResult_E
GrpMsg5Group::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /msg5-group/enable-message5
  // Description: whether O-RU's eCPRI message 5 handling is enabled.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafEnableMessage5 enableMessage5Inst(ITEM_ENABLE_MESSAGE5);
  addLeaf(enableMessage5Inst);

  // -----------------------------------------------------------------------------
  // Container:   /msg5-group/ru-compensation
  // Description: leafs for ru timing compensation based on message 5 handling
  // -----------------------------------------------------------------------------
  CntRuCompensation ruCompensationInst(ITEM_RU_COMPENSATION);
  ruCompensationInst.initialise();
  addContainer(ruCompensationInst);

  // -----------------------------------------------------------------------------
  // Container:   /msg5-group/message5-sessions
  // Description: session information for eCPRI message 5
  // -----------------------------------------------------------------------------
  CntMessage5Sessions message5SessionsInst(ITEM_MESSAGE5_SESSIONS);
  message5SessionsInst.initialise();
  addContainer(message5SessionsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /msg5-group/enable-message5
// Description: whether O-RU's eCPRI message 5 handling is enabled.
// -----------------------------------------------------------------------------
GrpMsg5Group::LeafEnableMessage5::LeafEnableMessage5(uint32_t id)
    : YangLeaf("enable-message5", id) {}

GrpMsg5Group::LeafEnableMessage5::~LeafEnableMessage5() {}

// -----------------------------------------------------------------------------
// Container:   ru-compensation
// Description: leafs for ru timing compensation based on message 5 handling
// -----------------------------------------------------------------------------
GrpMsg5Group::CntRuCompensation::CntRuCompensation(uint32_t id)
    : YangContainer("ru-compensation", id) {}

GrpMsg5Group::CntRuCompensation::~CntRuCompensation() {}

YangResult_E
GrpMsg5Group::CntRuCompensation::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /msg5-group/ru-compensation/tcv2
  // Description: a compensation value to account for expected delay from packet
  //              receipt at R2 to timestamping in the O-RU
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafTcv2 tcv2Inst(ITEM_TCV2);
  addLeaf(tcv2Inst);

  // -----------------------------------------------------------------------------
  // Leaf:        /msg5-group/ru-compensation/tcv1
  // Description: a compensation value to account for expected processing time
  // from
  //              timestamping in the O-RU until actual packet transmission at
  //              R3
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafTcv1 tcv1Inst(ITEM_TCV1);
  addLeaf(tcv1Inst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /msg5-group/ru-compensation/tcv2
// Description: a compensation value to account for expected delay from packet
//              receipt at R2 to timestamping in the O-RU
// -----------------------------------------------------------------------------
GrpMsg5Group::CntRuCompensation::LeafTcv2::LeafTcv2(uint32_t id)
    : YangLeaf("tcv2", id) {}

GrpMsg5Group::CntRuCompensation::LeafTcv2::~LeafTcv2() {}

// -----------------------------------------------------------------------------
// Leaf:        /msg5-group/ru-compensation/tcv1
// Description: a compensation value to account for expected processing time
// from
//              timestamping in the O-RU until actual packet transmission at R3
// -----------------------------------------------------------------------------
GrpMsg5Group::CntRuCompensation::LeafTcv1::LeafTcv1(uint32_t id)
    : YangLeaf("tcv1", id) {}

GrpMsg5Group::CntRuCompensation::LeafTcv1::~LeafTcv1() {}

// -----------------------------------------------------------------------------
// Container:   message5-sessions
// Description: session information for eCPRI message 5
// -----------------------------------------------------------------------------
GrpMsg5Group::CntMessage5Sessions::CntMessage5Sessions(uint32_t id)
    : YangContainer("message5-sessions", id) {}

GrpMsg5Group::CntMessage5Sessions::~CntMessage5Sessions() {}

YangResult_E
GrpMsg5Group::CntMessage5Sessions::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /msg5-group/message5-sessions/session-parameters
  // Description: list of MSG5 session information
  // Array Key:
  // -----------------------------------------------------------------------------
  LstSessionParameters sessionParametersInst(ITEM_SESSION_PARAMETERS);
  sessionParametersInst.initialise();
  addList(sessionParametersInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        session-parameters
// Description: list of MSG5 session information
// -----------------------------------------------------------------------------
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::LstSessionParameters(
    uint32_t id)
    : YangList("session-parameters", id) {}

GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::
    ~LstSessionParameters() {}

YangResult_E
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /msg5-group/message5-sessions/session-parameters/session-id
  // Description: Session ID for MSG5 responder
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafSessionId sessionIdInst(ITEM_SESSION_ID);
  addLeaf(sessionIdInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /msg5-group/message5-sessions/session-parameters/processing-element-name
  // Description: the name of the processing element used for MSG5
  // Ref:
  // /o-ran-processing-element:processing-elements/o-ran-processing-element:ru-elements/o-ran-processing-element:name
  // Units:
  // -----------------------------------------------------------------------------
  RefProcessingElementName processingElementNameInst(
      ITEM_PROCESSING_ELEMENT_NAME);
  addReference(processingElementNameInst);

  // -----------------------------------------------------------------------------
  // Container:   /msg5-group/message5-sessions/session-parameters/flow-state
  // Description: MSG5 flow state
  // -----------------------------------------------------------------------------
  CntFlowState flowStateInst(ITEM_FLOW_STATE);
  flowStateInst.initialise();
  addContainer(flowStateInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /msg5-group/message5-sessions/session-parameters/session-id
// Description: Session ID for MSG5 responder
// -----------------------------------------------------------------------------
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::LeafSessionId::
    LeafSessionId(uint32_t id)
    : YangLeaf("session-id", id) {}

GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::LeafSessionId::
    ~LeafSessionId() {}

// -----------------------------------------------------------------------------
// Reference:
// /msg5-group/message5-sessions/session-parameters/processing-element-name
// Description: the name of the processing element used for MSG5
// -----------------------------------------------------------------------------
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::
    RefProcessingElementName::RefProcessingElementName(uint32_t id)
    : YangReference(
          "processing-element-name",
          id,
          "/o-ran-processing-element:processing-elements/"
          "o-ran-processing-element:ru-elements/"
          "o-ran-processing-element:name") {}

GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::
    RefProcessingElementName::~RefProcessingElementName() {}

// -----------------------------------------------------------------------------
// Container:   flow-state
// Description: MSG5 flow state
// -----------------------------------------------------------------------------
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    CntFlowState(uint32_t id)
    : YangContainer("flow-state", id) {}

GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    ~CntFlowState() {}

YangResult_E
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /msg5-group/message5-sessions/session-parameters/flow-state/responses-transmitted
  // Description: The total number of eCPRI mesage 5 response messages
  // transmitted by
  //              the O-RU.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafResponsesTransmitted responsesTransmittedInst(ITEM_RESPONSES_TRANSMITTED);
  addLeaf(responsesTransmittedInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /msg5-group/message5-sessions/session-parameters/flow-state/requests-transmitted
  // Description: The total number of eCPRI mesage 5 request messages
  // transmitted by
  //              the O-RU.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafRequestsTransmitted requestsTransmittedInst(ITEM_REQUESTS_TRANSMITTED);
  addLeaf(requestsTransmittedInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /msg5-group/message5-sessions/session-parameters/flow-state/followups-transmitted
  // Description: The total number of eCPRI mesage 5 follow up messages
  // transmitted by
  //              the O-RU.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafFollowupsTransmitted followupsTransmittedInst(ITEM_FOLLOWUPS_TRANSMITTED);
  addLeaf(followupsTransmittedInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /msg5-group/message5-sessions/session-parameters/flow-state/responses-transmitted
// Description: The total number of eCPRI mesage 5 response messages transmitted
// by
//              the O-RU.
// -----------------------------------------------------------------------------
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    LeafResponsesTransmitted::LeafResponsesTransmitted(uint32_t id)
    : YangLeaf("responses-transmitted", id) {}

GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    LeafResponsesTransmitted::~LeafResponsesTransmitted() {}

// -----------------------------------------------------------------------------
// Leaf:
// /msg5-group/message5-sessions/session-parameters/flow-state/requests-transmitted
// Description: The total number of eCPRI mesage 5 request messages transmitted
// by
//              the O-RU.
// -----------------------------------------------------------------------------
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    LeafRequestsTransmitted::LeafRequestsTransmitted(uint32_t id)
    : YangLeaf("requests-transmitted", id) {}

GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    LeafRequestsTransmitted::~LeafRequestsTransmitted() {}

// -----------------------------------------------------------------------------
// Leaf:
// /msg5-group/message5-sessions/session-parameters/flow-state/followups-transmitted
// Description: The total number of eCPRI mesage 5 follow up messages
// transmitted by
//              the O-RU.
// -----------------------------------------------------------------------------
GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    LeafFollowupsTransmitted::LeafFollowupsTransmitted(uint32_t id)
    : YangLeaf("followups-transmitted", id) {}

GrpMsg5Group::CntMessage5Sessions::LstSessionParameters::CntFlowState::
    LeafFollowupsTransmitted::~LeafFollowupsTransmitted() {}

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
// Module:      o-ran-ecpri-delay
// Description: This module is an optional module for supporting eCPRI message 5
// handling
//              used for eCPRI based delay measurements.
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
ModuleORanEcpriDelay::ModuleORanEcpriDelay(uint32_t id)
    : YangModule(
          "o-ran-ecpri-delay",
          "o-ran-ecpri-delay.yang",
          "o-ran-msg5",
          "urn:o-ran:message5:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /ecpri-delay-message
  // Description: top level tree covering off O-DU to O-RU msg5 delay
  // measurement
  // -----------------------------------------------------------------------------
  CntEcpriDelayMessage ecpriDelayMessageInst(ITEM_ECPRI_DELAY_MESSAGE);
  ecpriDelayMessageInst.initialise();
  addContainer(ecpriDelayMessageInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanEcpriDelay::~ModuleORanEcpriDelay() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanEcpriDelay::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanEcpriDelay>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanEcpriDelay::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
