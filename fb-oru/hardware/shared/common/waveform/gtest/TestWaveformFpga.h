#ifndef _RADIO_HARDWARE_TESTWAVEFPGA_H_
#define _RADIO_HARDWARE_TESTWAVEFPGA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestWaveformFpga.h
 * \brief     A file to contain the ETNA implementation of the FTU FPGA.
 *
 *
 * \details   This file defines the FTU-specific instance of the ETNA fpga.
 *
 */

#include "IFpga.h"

#include "CommonFpgaCpri.h"

// Combine in the register access
#include "CommonFPGA.h"
#include "regs/CommonFpgaWaveformRegs.h"

namespace Mplane
{

// TODO: We need to move the original code over to using "feature-based" register blocks - e.g. access the fibre iq regs
// as an object, rather than via CommonFPGA. Then we don't need to derive other fpgas from CommonFPGA
class TestWaveformFpga :
		public CommonFPGA,
		public CommonFpgaWaveformRegs
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class TestWaveformFpgaTestCase;

public:
    /*! \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the common FPGA
     *  object.
     */
    static std::shared_ptr<TestWaveformFpga> getInstance(void);


    /*
     * Protected methods to allow friend classes access to the FPGA
     */

    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~TestWaveformFpga() { };

    /*! \brief  Constructor
     *
     */
    TestWaveformFpga();


};

typedef std::shared_ptr<TestWaveformFpga> TestWaveformFpgaPtr ;


} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_TESTWAVEFPGA_H_ */
