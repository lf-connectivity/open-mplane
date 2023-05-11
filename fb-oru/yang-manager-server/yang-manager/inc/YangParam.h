/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangParam.h
 * \brief     YANG parameters for datastores
 *
 *
 * \details   YANG parameter wrappers
 *
 */

#ifndef YANG_PARAM_H_
#define YANG_PARAM_H_

// *****************************************************************************
// Includes
// *****************************************************************************
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "YangTypes.h"

namespace Mplane {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// YANG Parameter Classes
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        YangParam
// Description:  YANG parameter container class.
// -----------------------------------------------------------------------------
class YangParam
{
public:
	YangParam();
	~YangParam();
	YangParam(bool param, const std::string& name = "");
	YangParam(int8_t param, const std::string& name = "");
	YangParam(int16_t param, const std::string& name = "");
	YangParam(int32_t param, const std::string& name = "");
	YangParam(int64_t param, const std::string& name = "");
	YangParam(uint8_t param, const std::string& name = "");
	YangParam(uint16_t param, const std::string& name = "");
	YangParam(uint32_t param, const std::string& name = "");
	YangParam(uint64_t param, const std::string& name = "");
	YangParam(double param, const std::string& name = "");
	YangParam(const char* param, const std::string& name = "");
	YangParam(const std::string& param, const std::string& name = "");
	YangParam(const std::vector<uint8_t>& param, const std::string& name = "", bool encoded = true);

	virtual YangParamType_E getType(void) const;
	virtual std::string name() const ;

	virtual bool        getBool     (void) const; 	// BOOL
	virtual int8_t      getInt8     (void) const; 	// INT8
	virtual int16_t     getInt16    (void) const; 	// INT16
	virtual int32_t     getInt32    (void) const; 	// INT32
	virtual int64_t     getInt64    (void) const; 	// INT64
	virtual uint8_t     getUInt8    (void) const; 	// UINT8
	virtual uint16_t    getUInt16   (void) const; 	// UINT16
	virtual uint32_t    getUInt32   (void) const; 	// UINT32
	virtual uint64_t    getUInt64   (void) const; 	// UINT64
	virtual std::string getString   (void) const; 	// STRING
	virtual double      getDecimal64(void) const; 	// DECIMAL64
	virtual std::vector<uint8_t> getBinaryEncoded (void) const; // BINARY
	virtual std::vector<uint8_t> getBinaryDecoded (void) const; // BINARY

	// Debug
	virtual std::string getText(void);	// String version of any parameter type
	void dump();

protected:
	virtual void setBool      (bool param);
	virtual void setInt8      (int8_t param);
	virtual void setInt16     (int16_t param);
	virtual void setInt32     (int32_t param);
	virtual void setInt64     (int64_t param);
	virtual void setUInt8     (uint8_t param);
	virtual void setUInt16    (uint16_t param);
	virtual void setUInt32    (uint32_t param);
	virtual void setUInt64    (uint64_t param);
	virtual void setString    (const std::string param);
	virtual void setDecimal64 (double param);
	virtual void setBinary (std::vector<uint8_t> param, bool encoded);

	virtual void setName(const std::string& name) ;

private:
	YangParamType_E mType;
	struct uYangData_t
	{
		uYangData_t();
		~uYangData_t();
		double      valDecimal64; 	// DECIMAL64
		bool        valBool;      	// BOOL
		int8_t      valInt8;      	// INT8
		int16_t     valInt16;     	// INT16
		int32_t     valInt32;     	// INT32
		int64_t     valInt64;     	// INT64
		uint8_t     valUInt8;     	// UINT8
		uint16_t    valUInt16;    	// UINT16
		uint32_t    valUInt32;    	// UINT32
		uint64_t    valUInt64;    	// UINT64
		std::string valString;    	// STRING
		std::vector<uint8_t> valBinary; //BINARY
	};
	uYangData_t mData;
	std::string mName ;
};

// -----------------------------------------------------------------------------
// Class:        YangParams
// Description:  Group of YANG parameters container class.
// -----------------------------------------------------------------------------
class YangParams
{
public:
	YangParams();
	~YangParams();
	YangParams(std::vector<std::shared_ptr<YangParam>> params);

	YangResult_E addParam(std::shared_ptr<YangParams> params);
	YangResult_E addParam(std::shared_ptr<YangParam> param);
	YangResult_E addParam(bool param, const std::string& name = "");
	YangResult_E addParam(int8_t param, const std::string& name = "");
	YangResult_E addParam(int16_t param, const std::string& name = "");
	YangResult_E addParam(int32_t param, const std::string& name = "");
	YangResult_E addParam(int64_t param, const std::string& name = "");
	YangResult_E addParam(uint8_t param, const std::string& name = "");
	YangResult_E addParam(uint16_t param, const std::string& name = "");
	YangResult_E addParam(uint32_t param, const std::string& name = "");
	YangResult_E addParam(uint64_t param, const std::string& name = "");
	YangResult_E addParam(const std::string& param, const std::string& name = "");
	YangResult_E addParam(const char* param, const std::string& name = "");
	YangResult_E addParam(double param, const std::string& name = "");
	YangResult_E addParam(const std::vector<uint8_t>& param, const std::string& name = "", bool encoded = true);

	uint32_t getNumParams(void) const;
	std::shared_ptr<YangParam> getParam(uint32_t index) const;
	std::vector<std::shared_ptr<YangParam>> getParamList(void);

	YangParamType_E getType(uint32_t index) const;

	bool        getBool      (uint32_t index) const; 	// BOOL
	int8_t      getInt8      (uint32_t index) const; 	// INT8
	int16_t     getInt16     (uint32_t index) const; 	// INT16
	int32_t     getInt32     (uint32_t index) const; 	// INT32
	int64_t     getInt64     (uint32_t index) const; 	// INT64
	uint8_t     getUInt8     (uint32_t index) const; 	// UINT8
	uint16_t    getUInt16    (uint32_t index) const; 	// UINT16
	uint32_t    getUInt32    (uint32_t index) const; 	// UINT32
	uint64_t    getUInt64    (uint32_t index) const; 	// UINT64
	std::string getString    (uint32_t index) const; 	// STRING
	double      getDecimal64 (uint32_t index) const; 	// DECIMAL64
	std::vector<uint8_t> getBinaryEncoded    (uint32_t index) const; 	// BINARY
	std::vector<uint8_t> getBinaryDecoded    (uint32_t index) const; 	// BINARY

	// Debug
	std::string getText(uint32_t index);	// String version of any parameter type
	void dump();

protected:

private:
	std::vector<std::shared_ptr<YangParam>> mParams;

};

} /* namespace Mplane */

#endif /* YANG_PARAM_H_ */
