/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111ORxPortTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "IFpgaMgr.h"
#include "TestCommonRxAgc.h"
#include "Zcu111ORxPortTestCase.h"
#include "Zcu111RrhSRxPort.h"

using namespace std;

using namespace Mplane;


/*
 * Unit test fixtures
 */
TEST_F(TestZcu111ORxPortTestCase, getAdcRms)
{
	cout << "TestZcu111ORxPortTestCase getAdcRms" << endl;

	Zcu111RrhSRxPort srxPort1(0, 0, "SRxPort1");
	Zcu111RrhSRxPort srxPort2(1, 2, "SRxPort2");

	srxPort1.initialise();
	srxPort2.initialise();

	std::shared_ptr<IFpgaAntennaRegs> antennaRegs = IFpgaMgr::getIFpgaAntennaRegs();
	Power adcPower(0.0);

	srxPort1.setPath(0);
	adcPower = srxPort1.getRawAdcRms();
	EXPECT_NEAR(adcPower.get(), -37.37, 0.01);
	EXPECT_EQ(antennaRegs->read_srxPortSelect(), (FpgaVal)0);
	EXPECT_EQ(antennaRegs->read_srxPathSelect(), (FpgaVal)0);

	srxPort1.setPath(1);
	adcPower = srxPort1.getRawAdcRms();
	EXPECT_NEAR(adcPower.get(), -37.37, 0.01);
	EXPECT_EQ(antennaRegs->read_srxPortSelect(), (FpgaVal)0);
	EXPECT_EQ(antennaRegs->read_srxPathSelect(), (FpgaVal)1);

	srxPort2.setPath(0);
	adcPower = srxPort2.getRawAdcRms();
	EXPECT_NEAR(adcPower.get(), -37.37, 0.01);
	EXPECT_EQ(antennaRegs->read_srxPortSelect(), (FpgaVal)1);
	EXPECT_EQ(antennaRegs->read_srxPathSelect(), (FpgaVal)0);

	srxPort2.setPath(1);
	adcPower = srxPort2.getRawAdcRms();
	EXPECT_NEAR(adcPower.get(), -37.37, 0.01);
	EXPECT_EQ(antennaRegs->read_srxPortSelect(), (FpgaVal)1);
	EXPECT_EQ(antennaRegs->read_srxPathSelect(), (FpgaVal)1);
}

TEST_F(TestZcu111ORxPortTestCase, getPower)
{
	cout << "TestZcu111ORxPortTestCase getPower" << endl;

	Zcu111RrhSRxPort srxPort1(0, 0, "SRxPort1");
	Zcu111RrhSRxPort srxPort2(1, 2, "SRxPort2");

	srxPort1.initialise();
	srxPort2.initialise();

	std::shared_ptr<IFpgaAntennaRegs> antennaRegs = IFpgaMgr::getIFpgaAntennaRegs();
	Power power(0.0);

	srxPort1.setPath(0);
	power = srxPort1.getPower();
	EXPECT_NEAR(power.get(), -37.37, 0.01);
	EXPECT_EQ(antennaRegs->read_srxPortSelect(), (FpgaVal)0);
	EXPECT_EQ(antennaRegs->read_srxPathSelect(), (FpgaVal)0);

	srxPort1.setPath(1);
	power = srxPort1.getPower();
	EXPECT_NEAR(power.get(), -37.37, 0.01);
	EXPECT_EQ(antennaRegs->read_srxPortSelect(), (FpgaVal)0);
	EXPECT_EQ(antennaRegs->read_srxPathSelect(), (FpgaVal)1);

	srxPort2.setPath(0);
	power = srxPort2.getPower();
	EXPECT_NEAR(power.get(), -37.37, 0.01);
	EXPECT_EQ(antennaRegs->read_srxPortSelect(), (FpgaVal)1);
	EXPECT_EQ(antennaRegs->read_srxPathSelect(), (FpgaVal)0);

	srxPort2.setPath(1);
	power = srxPort2.getPower();
	EXPECT_NEAR(power.get(), -37.37, 0.01);
	EXPECT_EQ(antennaRegs->read_srxPortSelect(), (FpgaVal)1);
	EXPECT_EQ(antennaRegs->read_srxPathSelect(), (FpgaVal)1);
}

TEST_F(TestZcu111ORxPortTestCase, getFwdRevPower)
{
	cout << "TestZcu111ORxPortTestCase getFwdPower" << endl;

	Zcu111RrhSRxPort srxPort1(0, 0, "SRxPort1");
	Zcu111RrhSRxPort srxPort2(1, 2, "SRxPort2");

	srxPort1.initialise();
	srxPort2.initialise();

	std::shared_ptr<IFpgaAntennaRegs> antennaRegs = IFpgaMgr::getIFpgaAntennaRegs();
	Power rf(0.0);
	Power digital(0.0);

	srxPort1.getFwdPower(0, rf, digital);
	EXPECT_NEAR(rf.get(), -29.59, 0.01);
	EXPECT_NEAR(digital.get(), -28.92, 0.01);
	EXPECT_EQ(antennaRegs->read_srxFwdRevSelect(0), (FpgaVal)0);

	srxPort1.getFwdPower(1, rf, digital);
	EXPECT_NEAR(rf.get(), -26.83, 0.01);
	EXPECT_NEAR(digital.get(), -26.46, 0.01);
	EXPECT_EQ(antennaRegs->read_srxFwdRevSelect(0), (FpgaVal)0);

	srxPort1.getRevPower(0, rf, digital);
	EXPECT_NEAR(rf.get(), -29.13, 0.01);
	EXPECT_NEAR(digital.get(), -28.72, 0.01);
	EXPECT_EQ(antennaRegs->read_srxFwdRevSelect(0), (FpgaVal)1);

	srxPort1.getRevPower(1, rf, digital);
	EXPECT_NEAR(rf.get(), -26.58, 0.01);
	EXPECT_NEAR(digital.get(), -26.34, 0.01);
	EXPECT_EQ(antennaRegs->read_srxFwdRevSelect(0), (FpgaVal)1);

	srxPort2.getFwdPower(0, rf, digital);
	EXPECT_NEAR(rf.get(), -25.15, 0.01);
	EXPECT_NEAR(digital.get(), -24.90, 0.01);
	EXPECT_EQ(antennaRegs->read_srxFwdRevSelect(1), (FpgaVal)0);

	srxPort2.getFwdPower(1, rf, digital);
	EXPECT_NEAR(rf.get(), -23.95, 0.01);
	EXPECT_NEAR(digital.get(), -23.75, 0.01);
	EXPECT_EQ(antennaRegs->read_srxFwdRevSelect(1), (FpgaVal)0);

	srxPort2.getRevPower(0, rf, digital);
	EXPECT_NEAR(rf.get(), -24.98, 0.01);
	EXPECT_NEAR(digital.get(), -24.82, 0.01);
	EXPECT_EQ(antennaRegs->read_srxFwdRevSelect(1), (FpgaVal)1);

	srxPort2.getRevPower(1, rf, digital);
	EXPECT_NEAR(rf.get(), -23.82, 0.01);
	EXPECT_NEAR(digital.get(), -23.69, 0.01);
	EXPECT_EQ(antennaRegs->read_srxFwdRevSelect(1), (FpgaVal)1);

}
