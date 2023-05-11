
#ifndef _RX_EQUALISER_H_
#define _RX_EQUALISER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxEqualiser.h
 * \brief     A file to define the interface to the rx equaliser for 100MHz
 *
 *
 * \details   A file to define the interface to the rx equaliser for 100MHz
 *
 */

#include "CommonRxEqualiser.h"
#include "Frequency.h"
#include "FrequencyOffset.h"
#include "Power.h"
#include "FftCalc.hpp"
#include "IFpgaMgr.h"

namespace Mplane
{

class RxEqualiser : public CommonRxEqualiser
{
public:

	/*!
     * \brief RxEqualiser constructor
     */
	RxEqualiser(int index, const char* name);

    /*!
     * \brief RxEqualiser destructor
     */
    virtual ~RxEqualiser();

    /*! \brief Method to calculate equaliser for Rx path
     *
     * \param  path
     * \return Return state of the set calculation is successful or not
     */
    virtual ReturnType::State calculateEqualiser(void) override;

    /**
     * @brief Print out contents of equaliser to stdout
     * Used for debug only
     */
    virtual void show(std::ostream& os = std::cout) const override;

    static const float RX_IF_MIN_FREQ;
    static const float RX_IF_MAX_FREQ;
    static const float RX_IF_FREQ_STEP;
    static const float RX_RF_FREQ_STEP;
    static const float INTERPOLATION_MIN_FREQ;
    static const float INTERPOLATION_MAX_FREQ;
    static const unsigned int INTERPOLATION_SIZE;
    static const float INTERPOLATION_SECOND_FREQ;
    static const float INTERPOLATION_SECOND_LAST_FREQ;

private:

	//For unit testing purpose
	friend class TestRxEqTestCases;

    ReturnType::State extractIfFreqResp(std::vector<EqPoint> &freqGainTable);
    ReturnType::State extractRfFreqResp(std::vector<EqPoint> &freqGainTable);
    void writeEqualiserCoeff(std::complex<float> input[], bool bypass);
    Power getIfCentreFreqGain(void);
    Power getRfCentreFreqGain(void);

private:

    /**
     * Uses the CommonFpga to set the fpga regs
     */
    std::shared_ptr<IFpgaAntennaRegs> mFpga;

    /**
     * RFDSA setting used to calculate gain at a frequency point (using the calibration data)
     */
    Power mRfdsa;

};

}

#endif /* _RX_EQUALISER_H_ */
