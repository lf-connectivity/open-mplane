/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangParamSysrepo.cpp
 * \brief     YANG parameters for sysrepo datastores
 *
 *
 * \details   Adds sysrepo methods to YANG parameter class
 *
 */

// *****************************************************************************
// Includes
// *****************************************************************************
#include "YangParamSysrepo.h"

using namespace Mplane;

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// sysrepo YANG parameter class
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        YangParamSysrepo
// Description:  sysrepo YANG parameter container class.
// -----------------------------------------------------------------------------

//=============================================================================================================
// PUBLIC
//=============================================================================================================
YangParamSysrepo::YangParamSysrepo()
{
}

YangParamSysrepo::~YangParamSysrepo()
{
}

YangParamSysrepo::YangParamSysrepo(std::shared_ptr<YangParam> param) :
	YangParamSysrepo(*param)
{
}

YangParamSysrepo::YangParamSysrepo(const YangParam &param)
{
	switch (param.getType())
	{
	case YangParamType_E::BOOL:
		setBool(param.getBool()) ;
		break ;
	case YangParamType_E::STRING:
		setString(std::string(param.getString())) ;
		break ;
	case YangParamType_E::BINARY:
		setBinary(param.getBinaryEncoded(), true) ;
		break ;
	case YangParamType_E::INT8:
		setInt8(param.getInt8()) ;
		break ;
	case YangParamType_E::INT16:
		setInt16(param.getInt16()) ;
		break ;
	case YangParamType_E::INT32:
		setInt32(param.getInt32()) ;
		break ;
	case YangParamType_E::INT64:
		setInt64(param.getInt64()) ;
		break ;
	case YangParamType_E::UINT8:
		setUInt8(param.getUInt8()) ;
		break ;
	case YangParamType_E::UINT16:
		setUInt16(param.getUInt16()) ;
		break ;
	case YangParamType_E::UINT32:
		setUInt32(param.getUInt32()) ;
		break ;
	case YangParamType_E::UINT64:
		setUInt64(param.getUInt64()) ;
		break ;
	case YangParamType_E::DECIMAL64:
		setDecimal64(param.getDecimal64()) ;
		break ;

	case YangParamType_E::UNKNOWN:
	default:
		break ;
	}
}

YangParamSysrepo::YangParamSysrepo(sysrepo::S_Val value)
	: YangParam()
{
	setSysrepo(value);
}

YangParamSysrepo::YangParamSysrepo(bool param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(int8_t param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(int16_t param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(int32_t param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(int64_t param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(uint8_t param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(uint16_t param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(uint32_t param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(uint64_t param)
	: YangParam(param)
{
}

YangParamSysrepo::YangParamSysrepo(std::string param)
	: YangParam(param)
{
}

sysrepo::S_Val YangParamSysrepo::getSysrepo(void) const
{
	sysrepo::S_Val value = nullptr;

	switch(getType())
	{
		case YangParamType_E::BOOL:
			{
			value = std::make_shared<sysrepo::Val>(getBool());
			}
			break;
		case YangParamType_E::INT8:
			{
			value = std::make_shared<sysrepo::Val>(getInt8());
			}
			break;
		case YangParamType_E::INT16:
			{
			value = std::make_shared<sysrepo::Val>(getInt16());
			}
			break;
		case YangParamType_E::INT32:
			{
			value = std::make_shared<sysrepo::Val>(getInt32());
			}
			break;
		case YangParamType_E::INT64:
			{
			value = std::make_shared<sysrepo::Val>(getInt64());
			}
			break;
		case YangParamType_E::UINT8:
			{
			value = std::make_shared<sysrepo::Val>(getUInt8());
			}
			break;
		case YangParamType_E::UINT16:
			{
			value = std::make_shared<sysrepo::Val>(getUInt16());
			}
			break;
		case YangParamType_E::UINT32:
			{
			value = std::make_shared<sysrepo::Val>(getUInt32());
			}
			break;
		case YangParamType_E::UINT64:
			{
			value = std::make_shared<sysrepo::Val>(getUInt64());
			}
			break;
		case YangParamType_E::STRING:
			{
			value = std::make_shared<sysrepo::Val>(getString().c_str());
			}
			break;
		case YangParamType_E::BINARY:
			{
				std::vector<uint8_t> data = getBinaryEncoded();
				std::string dataStr = std::string(data.begin(), data.end());
				value = std::make_shared<sysrepo::Val>(dataStr.c_str(), SR_BINARY_T);
			}
			break;
		case YangParamType_E::DECIMAL64:
			{
			value = std::make_shared<sysrepo::Val>(getDecimal64());
			}
			break;

		case YangParamType_E::UNKNOWN:
		default:
			break;
	}

	if (value && !name().empty())
		value->xpath_set(name().c_str()) ;

	return value;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================
void YangParamSysrepo::setSysrepo(sysrepo::S_Val value)
{
	setName(value->xpath()) ;
	switch (value->type())
	{
	/* types containing some data */
	case SR_BOOL_T:         /**< A boolean value ([RFC 7950 sec 9.5](http://tools.ietf.org/html/rfc7950#section-9.5)) */
		setBool(value->data()->get_bool()) ;
		break ;

	case SR_INT8_T:         /**< 8-bit signed integer ([RFC 7950 sec 9.2](https://tools.ietf.org/html/rfc7950#section-9.2)) */
		setInt8(value->data()->get_int8()) ;
		break ;

	case SR_INT16_T:        /**< 16-bit signed integer ([RFC 7950 sec 9.2](https://tools.ietf.org/html/rfc7950#section-9.2)) */
		setInt16(value->data()->get_int16()) ;
		break ;

	case SR_INT32_T:        /**< 32-bit signed integer ([RFC 7950 sec 9.2](https://tools.ietf.org/html/rfc7950#section-9.2)) */
		setInt32(value->data()->get_int32()) ;
		break ;

	case SR_INT64_T:        /**< 64-bit signed integer ([RFC 7950 sec 9.2](https://tools.ietf.org/html/rfc7950#section-9.2)) */
		setInt64(value->data()->get_int64()) ;
		break ;

	case SR_UINT8_T:        /**< 8-bit unsigned integer ([RFC 7950 sec 9.2](https://tools.ietf.org/html/rfc7950#section-9.2)) */
		setUInt8(value->data()->get_uint8()) ;
		break ;

	case SR_UINT16_T:       /**< 16-bit unsigned integer ([RFC 7950 sec 9.2](https://tools.ietf.org/html/rfc7950#section-9.2)) */
		setUInt16(value->data()->get_uint16()) ;
		break ;

	case SR_UINT32_T:       /**< 32-bit unsigned integer ([RFC 7950 sec 9.2](https://tools.ietf.org/html/rfc7950#section-9.2)) */
		setUInt32(value->data()->get_uint32()) ;
		break ;

	case SR_UINT64_T:       /**< 64-bit unsigned integer ([RFC 7950 sec 9.2](https://tools.ietf.org/html/rfc7950#section-9.2)) */
		setUInt64(value->data()->get_uint64()) ;
		break ;

	case SR_STRING_T:       /**< Human-readable string ([RFC 7950 sec 9.4](http://tools.ietf.org/html/rfc7950#section-9.4)) */
		setString(std::string(value->data()->get_string())) ;
		break ;

	case SR_DECIMAL64_T:    /**< 64-bit signed decimal number ([RFC 7950 sec 9.3](http://tools.ietf.org/html/rfc7950#section-9.3)) */
		setDecimal64(value->data()->get_decimal64()) ;
		break ;

	case sr_type_t::SR_BINARY_T:
	{
		std::string dataStr = value->data()->get_binary();
		std::vector<uint8_t> dataVec(dataStr.begin(), dataStr.end());
		setBinary(dataVec, true);
	}
	break;

	case sr_type_t::SR_BITS_T:
		setString(std::string(value->data()->get_bits()));
	break;

	case sr_type_t::SR_ENUM_T:
		setString(std::string(value->data()->get_enum()));
	break;

	case sr_type_t::SR_IDENTITYREF_T:
		setString(std::string(value->data()->get_identityref()));
	break;

	case sr_type_t::SR_INSTANCEID_T:
		setString(std::string(value->data()->get_instanceid()));
	break;

	case SR_UNKNOWN_T:              /**< Element unknown to sysrepo (unsupported element). */
	case SR_LIST_T:                 /**< List instance. ([RFC 7950 sec 7.8](http://tools.ietf.org/html/rfc7950#section-7.8)) */
	case SR_CONTAINER_T:            /**< Non-presence container. ([RFC 7950 sec 7.5](http://tools.ietf.org/html/rfc7950#section-7.5)) */
	case SR_CONTAINER_PRESENCE_T:   /**< Presence container. ([RFC 7950 sec 7.5.1](http://tools.ietf.org/html/rfc7950#section-7.5.1)) */
	case SR_LEAF_EMPTY_T:           /**< A leaf that does not hold any value ([RFC 7950 sec 9.11](http://tools.ietf.org/html/rfc7950#section-9.11)) */
	case SR_NOTIFICATION_T:         /**< Notification instance ([RFC 7095 sec 7.16](https://tools.ietf.org/html/rfc7950#section-7.16)) */
	case SR_ANYXML_T:       /**< Unknown chunk of XML ([RFC 7950 sec 7.10](https://tools.ietf.org/html/rfc7950#section-7.10)) */
	case SR_ANYDATA_T:      /**< Unknown set of nodes, encoded in XML ([RFC 7950 sec 7.10](https://tools.ietf.org/html/rfc7950#section-7.10)) */
	default:
		break ;
	}

}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
