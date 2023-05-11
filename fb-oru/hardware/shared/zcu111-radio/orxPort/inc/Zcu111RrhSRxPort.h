#ifndef _Zcu111RrhSRXPORT_H_
#define _Zcu111RrhSRXPORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111RrhSRxPort.h
 * \brief     Zcu111 RRH radio SRxPort definition
 *
 *
 * \details   Zcu111 RRH radio SRxPort definition
 *
 */

#include "Loggable.h"
#include "Zcu111SRxPort.h"
#include "IFpgaMgr.h"
#include "ICalData.h"
#include "ISRxCal.h"
#include "ISRxCalData.h"
#include "ISwrCalData.h"
#include "ISwrCal.h"

namespace Mplane
{

/**
 * This class add the Zcu111 RRH specific hardware implementations. It adds methods used to extend the
 * Zcu111 radio virtual interface so that it may interface to the actual hardware.
 *
 */
class Zcu111RrhSRxPort: public Zcu111SRxPort
{
public:
	using super = Zcu111SRxPort;

    /**
     * Update power data reading direction
     */
    enum class Direction
    {
        FORWARD,//!< FORWARD
        REVERSE //!< REVERSE
    };

    Zcu111RrhSRxPort( int index, int txPortOffset, const char* name);

    virtual ~Zcu111RrhSRxPort();

    /*! \brief  The initialise method
     *
     *  Method called during system startup to setup the devices associated
     *  with the sample receiver path.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() override;

    /**
     * Method used to set the external feedback path connected to the sample receive path
     * @param path 0 to N-1 supported sample paths
     * @return RT_OK if index is valid else RT_OUT_OF_RANGE
     */
    virtual ReturnType::State setPath( int path );

    /**
     * \brief get wide band sample receiver power dBm
     *
     * Used to get the actual corrected sample receive path power in dbBm
     *
     * @return sample power in dBm
     */
    virtual Power getPower(void) override;

    /**
     * \brief get calibrated power correction for the current temperature and attenuation
     *
     * Used to get the correction factor used in the sample receive path power conversion
     * from dBfs to dBm
     *
     * This method will use the current attenuation value and path frequency
     * to determine the correction factor.
     *
     * @NOTE this value is not usually required by the application as it is used
     * in the getPower() method, it is however useful when converting capture power
     * data in an exrternal application
     *
     * @param path 0 to N-1 selects the input path associated power measurement
     * @return power correction factor
     */
    virtual Power getCorrection( void);

    /**
     * Method used where the SRX path is used to measure forward power
     * @param path
     * @param rf return the measured RF power
     * @param digital return the measured digital power
     * @return RT_OK if measurement OK, of RT_NOT_SUPPORTED
     */
    virtual ReturnType::State getFwdPower( int path, Power &rf, Power &digital );

    /**
     * Method used where the SRX path is used to measure reverse power
     * @param path
     * @param rf return the measured reverse RF power
     * @param digital return the measured digital power
     * @return RT_OK if measurement OK, of RT_NOT_SUPPORTED
     */
    virtual ReturnType::State getRevPower( int path, Power &rf, Power &digital );

    /**
     * Method used to take the target transmit power which is corrected by,
     * optimal measurement path power (-16.0 dBfs) and determine the required
     * path attenuation for that target power.
     *
     * @param path 0 for TX1 and 1 for TX2 forward path, 2 for Tx1 and 3 for TX2 reverse path
     * @param target target maximum transmit path power to be measured
     * @return RT_OK
     */
    virtual ReturnType::State setTargetPower( int path, Power target ) override;

    /*! \brief  Get the sampling receiver path attenuator value
     *
     *  Used to read the current sampling receiver path attenuation value
     *
     *  \param path 0 to N-1 supported sample paths
     *  \return float dBm value between 0 and 31.5
     */
    virtual ReturnType::State getPathAtten( int path, Power &attenuation ) override;

protected:

    /**
     * Method called by the parent radio updatePowerData method, to perform
     * power readings in the forward or reverse direction for all TX ports.
     *
     * @param direction FORWARD to outgoing power, REVERSE for reflective power
     * @return RT_OK is measurement OK.
     */
    virtual ReturnType::State updatePower( Direction direction );

protected:

    unsigned int mNumAssociatedTxPorts;
    struct pathData
    {
        Power attenuation;
        Power target;
        Power tssi;
        Power power;
    };

    std::vector<pathData> mPathData;

    std::shared_ptr<ISRxCalDataContainer> mCalData;

    std::shared_ptr<ISRxCalData> mSrxCal;

    std::vector<std::shared_ptr<ISRxOpenLoop>> mSrxol;


    std::shared_ptr<ISwrCalDataContainer> mSwrCalData;

    std::shared_ptr<ISwrCalData> mSwrCal;

    std::vector<std::shared_ptr<ISwrOpenLoop>> mSwrol;

    bool mFwdPowerUpdated = false;
    bool mRevPowerUpdated = false;

    /**
     * This is the optimal sample receiver power setting. It is used when establishing
     * the path attenuation for a given target transmit power.
     */
    Power mOptimaldBfs;

private:
    /**
     * Private method to update and retrieve the calibration data.
     *
     * @return RT_OK - successful retrieval of cal data.
     */
    virtual ReturnType::State getCalData(void);

};

}

#endif /* _Zcu111RrhSRXPORT_H_ */
