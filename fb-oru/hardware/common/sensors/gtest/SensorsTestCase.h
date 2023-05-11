#ifndef _SENSORSTESTCASE_H_
#define _SENSORSTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SensorsTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "NXPLM75B.h"
#include "IRegData.h"

namespace Mplane
{

class RegData : public virtual IRegData
{
public:
	RegData() {};
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
};


/*! @brief Unit test harness for the sensors implementation.
 *
 *  This class uses the google test facilities to perform unit testing
 */
class SensorsTestCase : public ::testing::Test
{

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

};


} /* namespace Mplane */





#endif /* _SENSORSTESTCASE_H_ */
