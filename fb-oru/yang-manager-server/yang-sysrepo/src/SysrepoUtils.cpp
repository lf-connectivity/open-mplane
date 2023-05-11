/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SysrepoUtils.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ILoggable.h"
#include "stringfunc.hpp"
#include "XpathUtils.h"
#include "YangParamUtils.h"
#include "YangMgrServer.h"
#include "RadioDatastoreSysrepo.h"

#include "SysrepoUtils.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool SysrepoUtils::setItemStr(std::shared_ptr<YangMgrServer> mgr, const std::string &xpath, const std::string &value)
{
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	YangResult_E result(ds->setItemStr(xpath, value)) ;
	return result == YangResult_E::OK ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>> SysrepoUtils::getKeyParams(
		std::shared_ptr<YangMgrServer> mgr, const std::string &path)
{
	return getKeyParams(mgr, path, (uint16_t)RadioDatastoreSysrepo::RadDs_E::RADIO_DS_RUNNING);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string>> SysrepoUtils::getKeyValues(std::shared_ptr<YangMgrServer> mgr, const std::string &path)
{
	return getKeyValues(mgr, path, (uint16_t)RadioDatastoreSysrepo::RadDs_E::RADIO_DS_RUNNING);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam>> SysrepoUtils::getParams(std::shared_ptr<YangMgrServer> mgr, const std::string &xpath)
{
	return getParams(mgr, xpath, (uint16_t)RadioDatastoreSysrepo::RadDs_E::RADIO_DS_RUNNING);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>> SysrepoUtils::getOperationalKeyParams(
		std::shared_ptr<YangMgrServer> mgr, const std::string &path)
{
	return getKeyParams(mgr, path, (uint16_t)RadioDatastoreSysrepo::RadDs_E::RADIO_DS_OPERATIONAL);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string>> SysrepoUtils::getOperationalKeyValues(std::shared_ptr<YangMgrServer> mgr, const std::string &path)
{
	return getKeyValues(mgr, path, (uint16_t)RadioDatastoreSysrepo::RadDs_E::RADIO_DS_OPERATIONAL);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam>> SysrepoUtils::getOperationalParams(std::shared_ptr<YangMgrServer> mgr, const std::string &xpath)
{
	return getParams(mgr, xpath, (uint16_t)RadioDatastoreSysrepo::RadDs_E::RADIO_DS_OPERATIONAL);
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam>> SysrepoUtils::paramsToMap(
		std::shared_ptr<YangParams> params)
{
	std::map<std::string, std::shared_ptr<YangParam>> values ;
	for (unsigned i=0; i < params->getNumParams(); ++i)
	{
		std::shared_ptr<YangParam> p(params->getParam(i)) ;
		std::string leaf(XpathUtils::leafName(p->name())) ;
		values[leaf] = p ;
	}
	return values ;
}


//-------------------------------------------------------------------------------------------------------------
std::string SysrepoUtils::paramVal(
		const std::map<std::string, std::shared_ptr<YangParam>> &values,
		const std::string &key)
{
	if (values.find(key) == values.end())
		return "" ;

	if (!values.at(key))
		return "" ;

	std::string error ;
	return YangParamUtils::toString(values.at(key), error) ;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t SysrepoUtils::paramValUInt8(
		const std::map<std::string, std::shared_ptr<YangParam>> &values,
		const std::string &key)
{
	if (values.find(key) == values.end())
		return 0 ;

	if (!values.at(key))
		return 0 ;

	std::string error ;
	return YangParamUtils::toUint8(values.at(key), error) ;
}

//-------------------------------------------------------------------------------------------------------------
uint16_t SysrepoUtils::paramValUInt16(
		const std::map<std::string, std::shared_ptr<YangParam>> &values,
		const std::string &key)
{
	if (values.find(key) == values.end())
		return 0 ;

	if (!values.at(key))
		return 0 ;

	std::string error ;
	return YangParamUtils::toUint16(values.at(key), error) ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t SysrepoUtils::paramValUInt32(
		const std::map<std::string, std::shared_ptr<YangParam>> &values,
		const std::string &key)
{
	if (values.find(key) == values.end())
		return 0 ;

	if (!values.at(key))
		return 0 ;

	std::string error ;
	return YangParamUtils::toUint32(values.at(key), error) ;
}

//-------------------------------------------------------------------------------------------------------------
uint64_t SysrepoUtils::paramValUInt64(
		const std::map<std::string, std::shared_ptr<YangParam>> &values,
		const std::string &key)
{
	if (values.find(key) == values.end())
		return 0 ;

	if (!values.at(key))
		return 0 ;

	std::string error ;
	return YangParamUtils::toUint64(values.at(key), error) ;
}

//-------------------------------------------------------------------------------------------------------------
double SysrepoUtils::paramValDecimal64(
		const std::map<std::string, std::shared_ptr<YangParam>> &values,
		const std::string &key)
{
	if (values.find(key) == values.end())
		return 0 ;

	if (!values.at(key))
		return 0 ;

	return values.at(key)->getDecimal64() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<sysrepo::Vals> SysrepoUtils::paramsToVals(std::shared_ptr<YangParams> params)
{
	unsigned numParams(params->getNumParams()) ;
	sysrepo::S_Vals vals(new sysrepo::Vals(numParams));
	for (unsigned i=0; i < numParams; ++i)
	{
		std::shared_ptr<YangParam> param(params->getParam(i));
		switch(param->getType())
		{
		case YangParamType_E::BOOL:
			vals->val(i)->set(param->name().c_str(), param->getBool(), SR_BOOL_T);
			break ;

		case YangParamType_E::STRING:
			vals->val(i)->set(param->name().c_str(), param->getString().c_str(), SR_STRING_T);
			break ;

		case YangParamType_E::BINARY:
		{
			std::vector<uint8_t> data = param->getBinaryEncoded();
			std::string dataStr = std::string(data.begin(), data.end());
			vals->val(i)->set(param->name().c_str(), dataStr.c_str(), SR_BINARY_T);
		}
		break ;

		case YangParamType_E::INT8:
			vals->val(i)->set(param->name().c_str(), param->getInt8());
			break ;

		case YangParamType_E::INT16:
			vals->val(i)->set(param->name().c_str(), param->getInt16());
			break ;

		case YangParamType_E::INT32:
			vals->val(i)->set(param->name().c_str(), param->getInt32());
			break ;

		case YangParamType_E::INT64:
			vals->val(i)->set(param->name().c_str(), param->getInt64(), SR_INT64_T);
			break ;

		case YangParamType_E::UINT8:
			vals->val(i)->set(param->name().c_str(), param->getUInt8());
			break ;

		case YangParamType_E::UINT16:
			vals->val(i)->set(param->name().c_str(), param->getUInt16());
			break ;

		case YangParamType_E::UINT32:
			vals->val(i)->set(param->name().c_str(), param->getUInt32());
			break ;

		case YangParamType_E::UINT64:
			vals->val(i)->set(param->name().c_str(), param->getUInt64());
			break ;

		case YangParamType_E::DECIMAL64:
			vals->val(i)->set(param->name().c_str(), param->getDecimal64());
			break ;

		case YangParamType_E::UNKNOWN:
		default:
			break ;
		}
	}

	return vals ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<YangParams> SysrepoUtils::valsToParams(std::shared_ptr<sysrepo::Vals> vals)
{
	std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;

	for (size_t i = 0; i < vals->val_cnt(); ++i)
	{
		auto val(vals->val(i)) ;
		switch(val->type())
		{
		case SR_BOOL_T:
			params->addParam(val->data()->get_bool(), val->xpath()) ;
			break ;

		case SR_DECIMAL64_T:
			params->addParam(val->data()->get_decimal64(), val->xpath()) ;
			break ;

		case SR_INT8_T:
			params->addParam(val->data()->get_int8(), val->xpath()) ;
			break ;

		case SR_INT16_T:
			params->addParam(val->data()->get_int16(), val->xpath()) ;
			break ;

		case SR_INT32_T:
			params->addParam(val->data()->get_int32(), val->xpath()) ;
			break ;

		case SR_INT64_T:
			params->addParam(val->data()->get_int64(), val->xpath()) ;
			break ;

		case SR_STRING_T:
			params->addParam(val->data()->get_string(), val->xpath()) ;
			break ;

		case SR_UINT8_T:
			params->addParam(val->data()->get_uint8(), val->xpath()) ;
			break ;

		case SR_UINT16_T:
			params->addParam(val->data()->get_uint16(), val->xpath()) ;
			break ;

		case SR_UINT32_T:
			params->addParam(val->data()->get_uint32(), val->xpath()) ;
			break ;

		case SR_UINT64_T:
			params->addParam(val->data()->get_uint64(), val->xpath()) ;
			break ;

		case SR_BINARY_T:
		{
			std::string dataStr = val->data()->get_binary();
			std::vector<uint8_t> dataVec(dataStr.begin(), dataStr.end());
			params->addParam(dataVec, val->xpath(), true) ;
		}
		break ;

		case SR_BITS_T:
			params->addParam(val->data()->get_bits(), val->xpath()) ;
			break ;

		case SR_ENUM_T:
			params->addParam(val->data()->get_enum(), val->xpath()) ;
			break ;

		case SR_IDENTITYREF_T:
			params->addParam(val->data()->get_identityref(), val->xpath()) ;
			break ;

		case SR_INSTANCEID_T:
			params->addParam(val->data()->get_instanceid(), val->xpath()) ;
			break ;

		case SR_ANYXML_T:
			ILoggable::logEventWarning("SYSREPO: Unhandled value type: ANYXML") ;
			break ;
		case SR_ANYDATA_T:
			ILoggable::logEventWarning("SYSREPO: Unhandled value type: ANYDATA") ;
			break ;

		default:
			auto data = val->data() ;
			(void)data ;
			break ;
		}

	}

	return params ;
}

//-------------------------------------------------------------------------------------------------------------
bool SysrepoUtils::paramsToValsHolder(std::shared_ptr<YangParams> params, std::shared_ptr<sysrepo::Vals_Holder> valsHolder)
{
	unsigned numParams(params->getNumParams()) ;
	auto vals(valsHolder->allocate(numParams)) ;
//std::cerr << "paramsToValsHolder " << numParams << std::endl ;
	for (unsigned i=0; i < numParams; ++i)
	{
		std::shared_ptr<YangParam> param(params->getParam(i));
		switch(param->getType())
		{
		case YangParamType_E::BOOL:
			vals->val(i)->set(param->name().c_str(), param->getBool(), SR_BOOL_T);
			break ;

		case YangParamType_E::STRING:
//std::cerr << " * [" << i << "] '" << param->name() << "' = '" << param->getString() << "'" << std::endl ;
			vals->val(i)->set(param->name().c_str(), param->getString().c_str(), SR_STRING_T);
			break ;

		case YangParamType_E::BINARY:
		{
			std::vector<uint8_t> data = param->getBinaryEncoded();
			std::string dataStr = std::string(data.begin(), data.end());
			vals->val(i)->set(param->name().c_str(), dataStr.c_str(), SR_BINARY_T);
		}
		break ;

		case YangParamType_E::INT8:
			vals->val(i)->set(param->name().c_str(), param->getInt8());
			break ;

		case YangParamType_E::INT16:
			vals->val(i)->set(param->name().c_str(), param->getInt16());
			break ;

		case YangParamType_E::INT32:
			vals->val(i)->set(param->name().c_str(), param->getInt32());
			break ;

		case YangParamType_E::INT64:
			vals->val(i)->set(param->name().c_str(), param->getInt64(), SR_INT64_T);
			break ;

		case YangParamType_E::UINT8:
			vals->val(i)->set(param->name().c_str(), param->getUInt8());
			break ;

		case YangParamType_E::UINT16:
			vals->val(i)->set(param->name().c_str(), param->getUInt16());
			break ;

		case YangParamType_E::UINT32:
			vals->val(i)->set(param->name().c_str(), param->getUInt32());
			break ;

		case YangParamType_E::UINT64:
			vals->val(i)->set(param->name().c_str(), param->getUInt64());
			break ;

		case YangParamType_E::DECIMAL64:
			vals->val(i)->set(param->name().c_str(), param->getDecimal64());
			break ;

		case YangParamType_E::UNKNOWN:
		default:
			return false ;
			break ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void SysrepoUtils::dumpParamsMap(const std::map<std::string, std::shared_ptr<YangParam>>& values, const std::string& title)
{
	if (!title.empty())
		std::cerr << title << std::endl ;

	for (auto entry : values)
	{
		std::string error ;
		std::cerr << entry.first << " [" << entry.second->name() << "] = " << YangParamUtils::toString(entry.second, error) << std::endl ;
	}
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>> SysrepoUtils::getKeyParams(std::shared_ptr<YangMgrServer> mgr,
                                                                                                    const std::string &path,
                                                                                                    uint16_t datastoreId)
{
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	std::shared_ptr<YangParams> params ;
	if (ds->getItems(path, params, datastoreId) != YangResult_E::OK)
		return std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>() ;
	if (!params)
		return std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>>() ;

	std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>> values ;
	for (unsigned i=0; i < params->getNumParams(); ++i)
	{
		auto param(params->getParam(i)) ;

		std::string listName;
		std::string key;
		std::string value;
		XpathUtils::listIndex(param->name(), listName, key, value) ;

		if (values.find(value) == values.end())
			values[value] = std::map<std::string, std::shared_ptr<YangParam>>() ;

		values[value][XpathUtils::leafName(param->name())] = param ;
	}
	return values ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string>> SysrepoUtils::getKeyValues(std::shared_ptr<YangMgrServer> mgr,
                                                                                     const std::string &path,
                                                                                     uint16_t datastoreId)
{
	std::map<std::string, std::map<std::string, std::shared_ptr<YangParam>>> params(getKeyParams(mgr, path, datastoreId)) ;

	std::map<std::string, std::map<std::string, std::string>> values ;
	for (auto entry : params)
	{
		values[entry.first] = std::map<std::string, std::string>() ;
		for (auto param : entry.second)
		{
			std::string error ;
			values[entry.first][param.first] = YangParamUtils::toString(param.second, error) ;
		}
	}
	return values ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam>> SysrepoUtils::getParams(std::shared_ptr<YangMgrServer> mgr,
                                                                          const std::string &xpath,
                                                                          uint16_t datastoreId)
{
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	std::shared_ptr<YangParams> params ;
	if (ds->getItems(xpath, params) != YangResult_E::OK)
		return std::map<std::string, std::shared_ptr<YangParam>>() ;

	if (!params)
		return std::map<std::string, std::shared_ptr<YangParam>>() ;

	return paramsToMap(params) ;
}
