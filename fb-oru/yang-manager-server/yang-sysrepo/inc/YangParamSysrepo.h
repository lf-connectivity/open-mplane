/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangParamSysrepo.h
 * \brief     YANG parameters for sysrepo datastores
 *
 *
 * \details   Adds sysrepo methods to YANG parameter class
 *
 */

#ifndef YANG_PARAM_SYSREPO_H_
#define YANG_PARAM_SYSREPO_H_

// *****************************************************************************
// Includes
// *****************************************************************************
#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Sysrepo.hpp>

#include "YangParam.h"

namespace Mplane {

// *****************************************************************************
// sysrepo YANG parameter class
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        YangParamSysrepo
// Description:  sysrepo YANG parameter container class.
// -----------------------------------------------------------------------------
class YangParamSysrepo : public YangParam
{
public:
	YangParamSysrepo();
	~YangParamSysrepo();
	YangParamSysrepo(std::shared_ptr<YangParam> param);
	YangParamSysrepo(const YangParam& param);
	YangParamSysrepo(sysrepo::S_Val value);
	YangParamSysrepo(bool param);
	YangParamSysrepo(int8_t param);
	YangParamSysrepo(int16_t param);
	YangParamSysrepo(int32_t param);
	YangParamSysrepo(int64_t param);
	YangParamSysrepo(uint8_t param);
	YangParamSysrepo(uint16_t param);
	YangParamSysrepo(uint32_t param);
	YangParamSysrepo(uint64_t param);
	YangParamSysrepo(std::string param);

	virtual sysrepo::S_Val getSysrepo(void) const;	// SYSREPO

protected:
	virtual void setSysrepo(sysrepo::S_Val value);

private:

};

#if 0
// -----------------------------------------------------------------------------
// Class:        YangParamsSysrepo
// Description:  sysrepo group of YANG parameter container class.
// -----------------------------------------------------------------------------
class YangParamsSysrepo
{
public:
	YangParamsSysrepo();
	~YangParamsSysrepo();
	YangParamsSysrepo(std::vector<std::shared_ptr<YangParams>> params);

	YangResult_E addParam(sysrepo::S_Val param);	// SYSREPO
	YangResult_E addParam(sysrepo::S_Vals params);	// SYSREPO

protected:
	virtual void setSysrepo(sysrepo::S_Vals values);

private:

};
#endif

} /* namespace Mplane */

#endif /* YANG_PARAM_SYSREPO_H_ */
