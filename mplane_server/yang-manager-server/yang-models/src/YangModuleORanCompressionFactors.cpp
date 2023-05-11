/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanCompressionFactors.cpp
 * \brief     Module ORanCompressionFactors interface
 *
 *
 * \details   This file defines the YANG module o-ran-compression-factors
 interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-compression-factors"
 *            YANG Filename:    "o-ran-compression-factors.yang"
 *            Module Prefix:    "o-ran-compression-factors"
 *            Module namespace: "urn:o-ran:compression-factors:1.0"
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
#include "YangModuleORanCompressionFactors.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanCompressionFactors_NS;

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
// Grouping:    compression-params
// Description:
// -----------------------------------------------------------------------------
GrpCompressionParams::GrpCompressionParams(uint32_t id)
    : YangGroup("compression-params", id) {}

GrpCompressionParams::~GrpCompressionParams() {}

YangResult_E
GrpCompressionParams::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /compression-params/compression-type
  // Description: Compression type that O-DU wants to be supported
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafCompressionType compressionTypeInst(ITEM_COMPRESSION_TYPE);
  addLeaf(compressionTypeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /compression-params/bitwidth
  // Description: Bitwidth to be used in compression
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafBitwidth bitwidthInst(ITEM_BITWIDTH);
  addLeaf(bitwidthInst);

  // -----------------------------------------------------------------------------
  // Choice:      /compression-params/compression-format
  // Description: Choice of compression format for particular element
  // Type:        CompressionFormat_E
  // Units:       -
  // -----------------------------------------------------------------------------
  ChoiceCompressionFormat compressionFormatInst(ITEM_COMPRESSION_FORMAT);
  compressionFormatInst.initialise();
  addChoice(compressionFormatInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /compression-params/compression-type
// Description: Compression type that O-DU wants to be supported
// -----------------------------------------------------------------------------
GrpCompressionParams::LeafCompressionType::LeafCompressionType(uint32_t id)
    : YangLeaf("compression-type", id) {}

GrpCompressionParams::LeafCompressionType::~LeafCompressionType() {}

// -----------------------------------------------------------------------------
// Leaf:        /compression-params/bitwidth
// Description: Bitwidth to be used in compression
// -----------------------------------------------------------------------------
GrpCompressionParams::LeafBitwidth::LeafBitwidth(uint32_t id)
    : YangLeaf("bitwidth", id) {}

GrpCompressionParams::LeafBitwidth::~LeafBitwidth() {}

// -----------------------------------------------------------------------------
// Choice:      compression-format
// Description: Choice of compression format for particular element
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::ChoiceCompressionFormat(
    uint32_t id)
    : YangChoice("compression-format", id) {}

GrpCompressionParams::ChoiceCompressionFormat::~ChoiceCompressionFormat() {}

YangResult_E
GrpCompressionParams::ChoiceCompressionFormat::initialise(void) {

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptNoCompresison noCompresison(ITEM_NO_COMPRESISON);
  noCompresison.initialise();
  addOption(noCompresison);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptBlockFloatingPoint blockFloatingPoint(ITEM_BLOCK_FLOATING_POINT);
  blockFloatingPoint.initialise();
  addOption(blockFloatingPoint);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptBlockScaling blockScaling(ITEM_BLOCK_SCALING);
  blockScaling.initialise();
  addOption(blockScaling);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptULaw uLaw(ITEM_U_LAW);
  uLaw.initialise();
  addOption(uLaw);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptBeamSpaceCompression beamSpaceCompression(ITEM_BEAM_SPACE_COMPRESSION);
  beamSpaceCompression.initialise();
  addOption(beamSpaceCompression);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptModulationCompression modulationCompression(ITEM_MODULATION_COMPRESSION);
  modulationCompression.initialise();
  addOption(modulationCompression);

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:      /compression-params/compression-format[no-compresison]
// -------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptNoCompresison::
    OptNoCompresison(uint32_t id)
    : YangChoiceOption("no-compresison", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptNoCompresison::
    ~OptNoCompresison() {}

YangResult_E
GrpCompressionParams::ChoiceCompressionFormat::OptNoCompresison::initialise(
    void) {

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:      /compression-params/compression-format[block-floating-point]
// -------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptBlockFloatingPoint::
    OptBlockFloatingPoint(uint32_t id)
    : YangChoiceOption("block-floating-point", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptBlockFloatingPoint::
    ~OptBlockFloatingPoint() {}

YangResult_E
GrpCompressionParams::ChoiceCompressionFormat::OptBlockFloatingPoint::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /compression-params/compression-format[block-floating-point]/exponent
  // Description: Exponent bit width size in number of bits used when encoding
  // in udCompParam. Type:        uint8 Units:
  // -----------------------------------------------------------------------------
  LeafExponent exponentInst(ITEM_EXPONENT);
  addLeaf(exponentInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /compression-params/compression-format[block-floating-point]/exponent
// Description: Exponent bit width size in number of bits used when encoding in
// udCompParam.
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptBlockFloatingPoint::
    LeafExponent::LeafExponent(uint32_t id)
    : YangLeaf("exponent", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptBlockFloatingPoint::
    LeafExponent::~LeafExponent() {}

// -------------------------------------------------------------------------
// Option:      /compression-params/compression-format[block-scaling]
// -------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptBlockScaling::OptBlockScaling(
    uint32_t id)
    : YangChoiceOption("block-scaling", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptBlockScaling::
    ~OptBlockScaling() {}

YangResult_E
GrpCompressionParams::ChoiceCompressionFormat::OptBlockScaling::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // Leaf: /compression-params/compression-format[block-scaling]/block-scalar
  // Description: Common scaler for compressed PRB
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafBlockScalar blockScalarInst(ITEM_BLOCK_SCALAR);
  addLeaf(blockScalarInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /compression-params/compression-format[block-scaling]/block-scalar
// Description: Common scaler for compressed PRB
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptBlockScaling::
    LeafBlockScalar::LeafBlockScalar(uint32_t id)
    : YangLeaf("block-scalar", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptBlockScaling::
    LeafBlockScalar::~LeafBlockScalar() {}

// -------------------------------------------------------------------------
// Option:      /compression-params/compression-format[u-law]
// -------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptULaw::OptULaw(uint32_t id)
    : YangChoiceOption("u-law", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptULaw::~OptULaw() {}

YangResult_E
GrpCompressionParams::ChoiceCompressionFormat::OptULaw::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /compression-params/compression-format[u-law]/comp-bit-width
  // Description: Bit with for u-law compression
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafCompBitWidth compBitWidthInst(ITEM_COMP_BIT_WIDTH);
  addLeaf(compBitWidthInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /compression-params/compression-format[u-law]/comp-shift
  // Description: the shift applied to the entire PRB
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafCompShift compShiftInst(ITEM_COMP_SHIFT);
  addLeaf(compShiftInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /compression-params/compression-format[u-law]/comp-bit-width
// Description: Bit with for u-law compression
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptULaw::LeafCompBitWidth::
    LeafCompBitWidth(uint32_t id)
    : YangLeaf("comp-bit-width", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptULaw::LeafCompBitWidth::
    ~LeafCompBitWidth() {}

// -----------------------------------------------------------------------------
// Leaf:        /compression-params/compression-format[u-law]/comp-shift
// Description: the shift applied to the entire PRB
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptULaw::LeafCompShift::
    LeafCompShift(uint32_t id)
    : YangLeaf("comp-shift", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptULaw::LeafCompShift::
    ~LeafCompShift() {}

// -------------------------------------------------------------------------
// Option:      /compression-params/compression-format[beam-space-compression]
// -------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptBeamSpaceCompression::
    OptBeamSpaceCompression(uint32_t id)
    : YangChoiceOption("beam-space-compression", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptBeamSpaceCompression::
    ~OptBeamSpaceCompression() {}

YangResult_E
GrpCompressionParams::ChoiceCompressionFormat::OptBeamSpaceCompression::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /compression-params/compression-format[beam-space-compression]/block-scaler
  // Description: Common scaler for compressed beamforming coefficients
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafBlockScaler blockScalerInst(ITEM_BLOCK_SCALER);
  addLeaf(blockScalerInst);

  // -----------------------------------------------------------------------------
  // List:
  // /compression-params/compression-format[beam-space-compression]/active-beam-space-coeficient-mask
  // Description: active beamspace coefficient indices associated with the
  // compressed beamforming vector Array Key:
  // -----------------------------------------------------------------------------
  LstActiveBeamSpaceCoeficientMask activeBeamSpaceCoeficientMaskInst(
      ITEM_ACTIVE_BEAM_SPACE_COEFICIENT_MASK);
  activeBeamSpaceCoeficientMaskInst.initialise();
  addList(activeBeamSpaceCoeficientMaskInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /compression-params/compression-format[beam-space-compression]/block-scaler
// Description: Common scaler for compressed beamforming coefficients
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptBeamSpaceCompression::
    LeafBlockScaler::LeafBlockScaler(uint32_t id)
    : YangLeaf("block-scaler", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptBeamSpaceCompression::
    LeafBlockScaler::~LeafBlockScaler() {}

// -----------------------------------------------------------------------------
// List:        active-beam-space-coeficient-mask
// Description: active beamspace coefficient indices associated with the
// compressed beamforming vector
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptBeamSpaceCompression::
    LstActiveBeamSpaceCoeficientMask::LstActiveBeamSpaceCoeficientMask(
        uint32_t id)
    : YangList("active-beam-space-coeficient-mask", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptBeamSpaceCompression::
    LstActiveBeamSpaceCoeficientMask::~LstActiveBeamSpaceCoeficientMask() {}

YangResult_E
GrpCompressionParams::ChoiceCompressionFormat::OptBeamSpaceCompression::
    LstActiveBeamSpaceCoeficientMask::initialise(void) {

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:      /compression-params/compression-format[modulation-compression]
// -------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptModulationCompression::
    OptModulationCompression(uint32_t id)
    : YangChoiceOption("modulation-compression", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptModulationCompression::
    ~OptModulationCompression() {}

YangResult_E
GrpCompressionParams::ChoiceCompressionFormat::OptModulationCompression::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /compression-params/compression-format[modulation-compression]/csf
  // Description: Constallation shift flag
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafCsf csfInst(ITEM_CSF);
  addLeaf(csfInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /compression-params/compression-format[modulation-compression]/mod-comp-scaler
  // Description: Modulation compression scaler value.
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafModCompScaler modCompScalerInst(ITEM_MOD_COMP_SCALER);
  addLeaf(modCompScalerInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /compression-params/compression-format[modulation-compression]/csf
// Description: Constallation shift flag
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptModulationCompression::
    LeafCsf::LeafCsf(uint32_t id)
    : YangLeaf("csf", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptModulationCompression::
    LeafCsf::~LeafCsf() {}

// -----------------------------------------------------------------------------
// Leaf:
// /compression-params/compression-format[modulation-compression]/mod-comp-scaler
// Description: Modulation compression scaler value.
// -----------------------------------------------------------------------------
GrpCompressionParams::ChoiceCompressionFormat::OptModulationCompression::
    LeafModCompScaler::LeafModCompScaler(uint32_t id)
    : YangLeaf("mod-comp-scaler", id) {}

GrpCompressionParams::ChoiceCompressionFormat::OptModulationCompression::
    LeafModCompScaler::~LeafModCompScaler() {}

// -----------------------------------------------------------------------------
// Grouping:    compression-details
// Description:
// -----------------------------------------------------------------------------
GrpCompressionDetails::GrpCompressionDetails(uint32_t id)
    : YangGroup("compression-details", id) {}

GrpCompressionDetails::~GrpCompressionDetails() {}

YangResult_E
GrpCompressionDetails::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /compression-details/iq-bitwidth
  // Description: Bitwidth to be used in compression
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafIqBitwidth iqBitwidthInst(ITEM_IQ_BITWIDTH);
  addLeaf(iqBitwidthInst);

  // -----------------------------------------------------------------------------
  // Uses:        /compression-details/compression-params
  // Description:
  // -----------------------------------------------------------------------------
  GrpCompressionParams compressionParamsInst(ITEM_COMPRESSION_PARAMS);
  compressionParamsInst.initialise();
  addGroup(compressionParamsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /compression-details/iq-bitwidth
// Description: Bitwidth to be used in compression
// -----------------------------------------------------------------------------
GrpCompressionDetails::LeafIqBitwidth::LeafIqBitwidth(uint32_t id)
    : YangLeaf("iq-bitwidth", id) {}

GrpCompressionDetails::LeafIqBitwidth::~LeafIqBitwidth() {}

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
// Module:      o-ran-compression-factors
// Description: This module defines the module capabilities for
//              the O-RAN Radio Unit U-Plane configuration.
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
ModuleORanCompressionFactors::ModuleORanCompressionFactors(uint32_t id)
    : YangModule(
          "o-ran-compression-factors",
          "o-ran-compression-factors.yang",
          "o-ran-compression-factors",
          "urn:o-ran:compression-factors:1.0",
          id)
// Add user code here
// %%->

// <-%%
{

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanCompressionFactors::~ModuleORanCompressionFactors() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanCompressionFactors::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanCompressionFactors>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanCompressionFactors::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
