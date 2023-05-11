#ifndef VHI_INC_IPIMD_H_
#define VHI_INC_IPIMD_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPimD.h
 * \brief     A file to define generic interface to PIM analyser
 *
 *
 * \details   A file to define generic interface to PIM analyser
 *
 */

// Includes go here, before the namespace
#include <memory>

#include "GlobalTypeDefs.h"
#include "Power.h"
#include "Frequency.h"

namespace Mplane
{

/*! \brief  PIM analyser interface
 *
 * A virtual interface base class implementation to setup and run the PIM
 * detector tests. It contains interface to configure the system for the test
 * and interfaces to run the tests.
 *
 */
class IPimD
{
public:
    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the PimD
     *  within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IPimD> getInstance(void);

    /*! \brief  Setup the Nimrod board for PIM test
     *
     *  Setup the CW tones with desired power and remove intermod and select correct receive path
     *  for PIM measurement
     *
     *  \param tone1Power - power for tone1 (dbm)
     *  \param tone2Power - power for tone2 (dbm)     *
     *  \param tone1Loss - External losses for tone 1
     *  \param tone2Loss - External losses for tone 2
     *  \param tone1Freq - tone 1 offset (MHz)
     *  \param tone2Freq - tone 2 offset (MHz)
     *  \param imOrder - IM component to be cancelled
     *  \param startingBO - Initial Backoff power before attempting to ramp
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setup(Power tone1Power, Power tone2Power, Power tone1Loss, Power tone2Loss,
    		double bbCarrierFreq1, double bbCarrierFreq2, int imOrder, Power startingBO) = 0;

    /*! \brief  Ramp CW tones to target rms power
     *
     *  Ramp the power using a feedback loop
     *
     *  \param targetPower  The target average power for the 2 tones
     *  \param startingBO - Initial Backoff power before attempting to ramp
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State rampToPower (Power targetPower, Power startingBO) = 0;

    /*! \brief  Level the 2 tones
     *
     *  Level the tones within the provided margin
     *
     *  \param targetAdcRms
     *  \param margin
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State levelSRX (Power targetAdcRms, Power margin) = 0;

    /*! \brief  Equalise the tones
     *
     *  Adjust the tones so that the delta power between them is within a certain tolerance
     *
     *  \param tone1Freq
     *  \param tone2Freq
     *  \param tone1Power - power for tone1 (dbm)
     *  \param tone2Power - power for tone2 (dbm)
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State equaliseTones (double tone1Freq, double tone2Freq,
    		Power tone1Power, Power tone2Power) = 0;

    /*! \brief  Cancel the specified IM order
     *
     *  Run algorithm to cancel the IM component of specific order
     *
     *  \param imOrder
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setIMCanceller(int imOrder, float &suppression) = 0;

	/**
	 * Get the reason for an error
	 * @return error string
	 */
	virtual std::string getErrorReason() = 0;

    /*! \brief  Destructor
     *
     */

    virtual ~IPimD() {};
};

}

#endif /* VHI_INC_IPIMD_H_ */
