
#ifndef _TX_EQUALISER_H_
#define _TX_EQUALISER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxEqualiser.h
 * \brief     A file to define the interface to the tx equaliser for 100MHz
 *
 *
 * \details   A file to define the interface to the tx equaliser for 100MHz
 *
 */

#include "CommonTxEqualiser.h"
#include "ITxPort.h"
#include "Frequency.h"
#include "FrequencyOffset.h"
#include "Power.h"
#include "FftCalc.hpp"
#include "IFpgaMgr.h"


namespace Mplane
{

class TxEqualiser : public CommonTxEqualiser
{
public:

	/*!
     * \brief TxEqualiser constructor
     */
	TxEqualiser(int index, const char* name);

    /*!
     * \brief TxEqualiser destructor
     */
    virtual ~TxEqualiser();

    /*! \brief Method to calculate equaliser for Tx path
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

public:

    static const float TX_IF_MIN_FREQ;
    static const float TX_IF_MAX_FREQ;
    static const float TX_IF_FREQ_STEP;
    static const float TX_RF_FREQ_STEP;
    static const float INTERPOLATION_MIN_FREQ;
    static const float INTERPOLATION_MAX_FREQ;
    static const float INTERPOLATION_STEP;
    static const unsigned int INTERPOLATION_SIZE;
    static const float INTERPOLATION_SECOND_FREQ;
    static const float INTERPOLATION_SECOND_LAST_FREQ;

protected:

	//For unit testing purpose
	friend class TestTxEqTestCases;

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

    /**
     * Baseband setting used to calculate gain at a frequency point (using the calibration data)
     */
    Power mBaseband;
};

}

#endif /* _TX_EQUALISER_H_ */
