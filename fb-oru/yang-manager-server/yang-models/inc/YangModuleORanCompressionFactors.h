#ifndef _MODULE_O_RAN_COMPRESSION_FACTORS_H_
#define _MODULE_O_RAN_COMPRESSION_FACTORS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanCompressionFactors.h
 * \brief     Module ORanCompressionFactors interface
 *
 *
 * \details   This file defines the YANG module o-ran-compression-factors interface.
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
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// -----------------------------------------------------------------------------
// Common
// -----------------------------------------------------------------------------

#include "YangModule.h"

// -----------------------------------------------------------------------------
// External Modules
// -----------------------------------------------------------------------------


namespace Mplane {

namespace ModuleORanCompressionFactors_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

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
// Grouping:    /compression-params
// Description:
// -----------------------------------------------------------------------------
class GrpCompressionParams : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_COMPRESSION_TYPE,  // LeafCompressionType
		ITEM_BITWIDTH,  // LeafBitwidth
		ITEM_COMPRESSION_FORMAT,  // ChoiceCompressionFormat
	};

	GrpCompressionParams(uint32_t id);
	~GrpCompressionParams();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /compression-params/compression-type
	// Description: Compression type that O-DU wants to be supported
	// -----------------------------------------------------------------------------
	class LeafCompressionType : public YangLeaf
	{
	public:

		// Compression type that O-DU wants to be supported
		enum class CompressionType_E : uint32_t
		{
			STATIC,	// Indicates that static compression method will be used (both compression and IQ bitwidth)
			DYNAMIC,	// Indicates that dynamic compression method will be used

			Num_CompressionType_E
		};

		LeafCompressionType(uint32_t id);
		~LeafCompressionType();

	}; // LeafCompressionType

	// -----------------------------------------------------------------------------
	// Leaf:        /compression-params/bitwidth
	// Description: Bitwidth to be used in compression
	// -----------------------------------------------------------------------------
	class LeafBitwidth : public YangLeaf
	{
	public:

		LeafBitwidth(uint32_t id);
		~LeafBitwidth();

	}; // LeafBitwidth

	// -----------------------------------------------------------------------------
	// Choice:      /compression-params/compression-format
	// Description: Choice of compression format for particular element
	// -----------------------------------------------------------------------------
	class ChoiceCompressionFormat : public YangChoice
	{
	public:
		// Choice Option
		enum : uint32_t
		{
			ITEM_NO_COMPRESISON,  // OptNoCompresison
			ITEM_BLOCK_FLOATING_POINT,  // OptBlockFloatingPoint
			ITEM_BLOCK_SCALING,  // OptBlockScaling
			ITEM_U_LAW,  // OptULaw
			ITEM_BEAM_SPACE_COMPRESSION,  // OptBeamSpaceCompression
			ITEM_MODULATION_COMPRESSION,  // OptModulationCompression
		};

		ChoiceCompressionFormat(uint32_t id);
		~ChoiceCompressionFormat();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Option: /compression-params/compression-format[no-compresison]
		// -----------------------------------------------------------------------------
		class OptNoCompresison : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			OptNoCompresison(uint32_t id);
			~OptNoCompresison();

			YangResult_E initialise(void);

		}; // OptNoCompresison


		// -----------------------------------------------------------------------------
		// Option: /compression-params/compression-format[block-floating-point]
		// -----------------------------------------------------------------------------
		class OptBlockFloatingPoint : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_EXPONENT,  // LeafExponent
			};

			OptBlockFloatingPoint(uint32_t id);
			~OptBlockFloatingPoint();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /compression-params/compression-format[block-floating-point]/exponent
			// Description: Exponent bit width size in number of bits used when encoding in udCompParam.
			// -----------------------------------------------------------------------------
			class LeafExponent : public YangLeaf
			{
			public:

				LeafExponent(uint32_t id);
				~LeafExponent();

			}; // LeafExponent

		}; // OptBlockFloatingPoint


		// -----------------------------------------------------------------------------
		// Option: /compression-params/compression-format[block-scaling]
		// -----------------------------------------------------------------------------
		class OptBlockScaling : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_BLOCK_SCALAR,  // LeafBlockScalar
			};

			OptBlockScaling(uint32_t id);
			~OptBlockScaling();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /compression-params/compression-format[block-scaling]/block-scalar
			// Description: Common scaler for compressed PRB
			// -----------------------------------------------------------------------------
			class LeafBlockScalar : public YangLeaf
			{
			public:

				LeafBlockScalar(uint32_t id);
				~LeafBlockScalar();

			}; // LeafBlockScalar

		}; // OptBlockScaling


		// -----------------------------------------------------------------------------
		// Option: /compression-params/compression-format[u-law]
		// -----------------------------------------------------------------------------
		class OptULaw : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_COMP_BIT_WIDTH,  // LeafCompBitWidth
				ITEM_COMP_SHIFT,  // LeafCompShift
			};

			OptULaw(uint32_t id);
			~OptULaw();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /compression-params/compression-format[u-law]/comp-bit-width
			// Description: Bit with for u-law compression
			// -----------------------------------------------------------------------------
			class LeafCompBitWidth : public YangLeaf
			{
			public:

				LeafCompBitWidth(uint32_t id);
				~LeafCompBitWidth();

			}; // LeafCompBitWidth

			// -----------------------------------------------------------------------------
			// Leaf:        /compression-params/compression-format[u-law]/comp-shift
			// Description: the shift applied to the entire PRB
			// -----------------------------------------------------------------------------
			class LeafCompShift : public YangLeaf
			{
			public:

				LeafCompShift(uint32_t id);
				~LeafCompShift();

			}; // LeafCompShift

		}; // OptULaw


		// -----------------------------------------------------------------------------
		// Option: /compression-params/compression-format[beam-space-compression]
		// -----------------------------------------------------------------------------
		class OptBeamSpaceCompression : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_BLOCK_SCALER,  // LeafBlockScaler
				ITEM_ACTIVE_BEAM_SPACE_COEFICIENT_MASK,  // LstActiveBeamSpaceCoeficientMask
			};

			OptBeamSpaceCompression(uint32_t id);
			~OptBeamSpaceCompression();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /compression-params/compression-format[beam-space-compression]/block-scaler
			// Description: Common scaler for compressed beamforming coefficients
			// -----------------------------------------------------------------------------
			class LeafBlockScaler : public YangLeaf
			{
			public:

				LeafBlockScaler(uint32_t id);
				~LeafBlockScaler();

			}; // LeafBlockScaler

			// -----------------------------------------------------------------------------
			// List:        /compression-params/compression-format[beam-space-compression]/active-beam-space-coeficient-mask
			// Description: active beamspace coefficient indices associated with the compressed beamforming vector
			// -----------------------------------------------------------------------------
			class LstActiveBeamSpaceCoeficientMask : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
				};

				LstActiveBeamSpaceCoeficientMask(uint32_t id);
				~LstActiveBeamSpaceCoeficientMask();

				YangResult_E initialise(void);

			}; // LstActiveBeamSpaceCoeficientMask

		}; // OptBeamSpaceCompression


		// -----------------------------------------------------------------------------
		// Option: /compression-params/compression-format[modulation-compression]
		// -----------------------------------------------------------------------------
		class OptModulationCompression : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_CSF,  // LeafCsf
				ITEM_MOD_COMP_SCALER,  // LeafModCompScaler
			};

			OptModulationCompression(uint32_t id);
			~OptModulationCompression();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /compression-params/compression-format[modulation-compression]/csf
			// Description: Constallation shift flag
			// -----------------------------------------------------------------------------
			class LeafCsf : public YangLeaf
			{
			public:

				LeafCsf(uint32_t id);
				~LeafCsf();

			}; // LeafCsf

			// -----------------------------------------------------------------------------
			// Leaf:        /compression-params/compression-format[modulation-compression]/mod-comp-scaler
			// Description: Modulation compression scaler value.
			// -----------------------------------------------------------------------------
			class LeafModCompScaler : public YangLeaf
			{
			public:

				LeafModCompScaler(uint32_t id);
				~LeafModCompScaler();

			}; // LeafModCompScaler

		}; // OptModulationCompression

	}; // ChoiceCompressionFormat

}; // GrpCompressionParams

// -----------------------------------------------------------------------------
// Grouping:    /compression-details
// Description:
// -----------------------------------------------------------------------------
class GrpCompressionDetails : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_IQ_BITWIDTH,  // LeafIqBitwidth
		ITEM_COMPRESSION_PARAMS,  // Use GrpCompressionParams
	};

	GrpCompressionDetails(uint32_t id);
	~GrpCompressionDetails();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /compression-details/iq-bitwidth
	// Description: Bitwidth to be used in compression
	// -----------------------------------------------------------------------------
	class LeafIqBitwidth : public YangLeaf
	{
	public:

		LeafIqBitwidth(uint32_t id);
		~LeafIqBitwidth();

	}; // LeafIqBitwidth

}; // GrpCompressionDetails


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
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
//              AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//              IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//              ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//              LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//              CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//              SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//              INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//              ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//              POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or without
//              modification, are permitted provided that the following conditions are met:
//
//              * Redistributions of source code must retain the above copyright notice,
//              this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above copyright notice,
//              this list of conditions and the above disclaimer in the documentation
//              and/or other materials provided with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived from
//              this software without specific prior written permission.
// -----------------------------------------------------------------------------
class ModuleORanCompressionFactors : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
	};

	ModuleORanCompressionFactors(uint32_t id);
	~ModuleORanCompressionFactors();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanCompressionFactors_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_COMPRESSION_FACTORS_H_ */
