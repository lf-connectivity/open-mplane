/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegData.h
 * \brief     Implements IRegData interface to retrieve initialisation data for all supported drivers
 *
 *
 * \details   Implements IRegData interface to retrieve initialisation data for all supported drivers
 *
 */

#ifndef _COMMON_REGDATA_H_
#define _COMMON_REGDATA_H_

#include "Loggable.h"
#include "GlobalTypeDefs.h"
#include "IRegData.h"

namespace Mplane
{

class RegData: public virtual IRegData
{
public:
	RegData();
    virtual ~RegData() {};

    /*! \brief  Retrieve the register data set as vector of register addresses and values
     *
     *
     *  \param the reference to the vector containing register addresses and values
     */
    virtual ReturnType::State getRegisterData(std::string driverName, std::vector< std::pair< uint32_t, uint32_t> > & regData ) override;

    /*! \brief  Retrieve the register data set as vector of values
     *
     *
     *  \param the reference to the vector containing values
     */
    virtual ReturnType::State getRegisterData(std::string driverName, std::vector< uint32_t > & regData ) override;

protected:
    std::map<std::string, std::vector< uint32_t >> mRegValues;
    std::map<std::string, std::vector< std::pair< uint32_t, uint32_t> >> mRegAddrValues;
};

} /* namespace Mplane */

#endif /* _COMMON_REGDATA_H_ */
