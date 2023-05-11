/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRegData.h
 * \brief     A file to define generic interface to get initialisation data for all drivers
 *
 *
 * \details   This file defines a generic interface to get initialisation data for all drivers
 *
 */

#ifndef _VRH_IREGDATA_H_
#define _VRH_IREGDATA_H_

// Includes go here, before the namespace
#include <vector>
#include <utility>
#include <cstdint>
#include <memory>

#include "GlobalTypeDefs.h"


// forward declarations go here, before the namespace
using namespace std;

namespace Mplane
{

/*! \brief  Generic reference to get the register initialisation data for all drivers
 *
 *  A generic virtual interface base class that provides method to
 *  return data that should be programmed into the registers of a chip.
 *
 *  The data that gets programmed into a chip's registers is based on the
 *  board layout/application requirement. This virtual interface enables the
 *  driver to be independent of the board specific register initialisation data.
 *
 */
class IRegData
{
public:
    /**
     * Method implements a singleton that provides access to register init data
     * @return a reference to the register init data.
     */
    static std::shared_ptr<IRegData> singleton();

    virtual ~IRegData() {};

    /*! \brief  Retrieve the register data set as vector of register addresses and values
     *
     *
     *  \param the reference to the vector containing register addresses and values
     */
    virtual ReturnType::State getRegisterData(std::string driverName, std::vector< std::pair< uint32_t, uint32_t> > & regData ) = 0;

    /*! \brief  Retrieve the register data set as vector of values
     *
     *
     *  \param the reference to the vector containing values
     */
    virtual ReturnType::State getRegisterData(std::string driverName, std::vector< uint32_t > & regData ) = 0;
};

} /* namespace Mplane */

#endif /* _VRH_IREGDATA_H_ */
