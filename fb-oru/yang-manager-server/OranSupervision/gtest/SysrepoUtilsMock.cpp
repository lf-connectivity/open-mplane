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
//std::shared_ptr<sysrepo::Vals> SysrepoUtils::paramsToVals(std::shared_ptr<YangParams> params)

//-------------------------------------------------------------------------------------------------------------
//std::shared_ptr<YangParams> SysrepoUtils::valsToParams(std::shared_ptr<sysrepo::Vals> vals)

//-------------------------------------------------------------------------------------------------------------
bool SysrepoUtils::paramsToValsHolder(std::shared_ptr<YangParams> params, std::shared_ptr<sysrepo::Vals_Holder> valsHolder)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void SysrepoUtils::dumpParamsMap(const std::map<std::string, std::shared_ptr<YangParam>>& values, const std::string& title)
{
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
