/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDataType.h
 * \brief
 *
 *
 */


#ifndef INC_IDATATYPE_H_
#define INC_IDATATYPE_H_

#include <complex>
#include <string>

namespace Mplane {

/*!
 * \class  IDataType
 * \brief
 * \details
 *
 */
class IDataType {
public:

	// Supported data types
	enum DataType {
		DATA_NULL,
		DATA_INT,
		DATA_FLOAT,
		DATA_DOUBLE,
		DATA_COMPLEX_FLOAT,
		DATA_COMPLEX_DOUBLE,
	};

	// A pointer to the array of data
	union DataPtr {
		int* int_ptr ;
		float *float_ptr ;
		double* double_ptr ;
		std::complex<float>* complex_float_ptr ;
		std::complex<double>* complex_double_ptr ;
	};

	// A const pointer to the array of data
	union ConstDataPtr {
		const int* int_ptr ;
		const float *float_ptr ;
		const double* double_ptr ;
		const std::complex<float>* complex_float_ptr ;
		const std::complex<double>* complex_double_ptr ;
	};

	// Value representation
	enum ValueRep {
		VALUE_COMPLEX_POWER,	//<! IQ values are power values
		VALUE_COMPLEX_VOLT,		//<! IQ values are volt values
		VALUE_POWER_DB,			//<! Only I values used (Q=0) and are power values in dB
	};

	/**
	 * Convert type to string
	 */
	static std::string typeStr(DataType type) ;

	/**
	 * Convert Value representation to string
	 */
	static std::string valueRepStr(ValueRep rep) ;

} ;

}

#endif /* INC_IDATATYPE_H_ */
