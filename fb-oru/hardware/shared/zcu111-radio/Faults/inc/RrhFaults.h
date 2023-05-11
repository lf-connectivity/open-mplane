/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhFaults.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _MPLANE_ZCU111_RRH_FAULTS__H_
#define _MPLANE_ZCU111_RRH_FAULTS__H_


#include <memory>
#include <vector>
#include "IFault.h"
#include "IFaultsList.h"

#include "CommonRadioFaults.h"

namespace Mplane
{

class RrhFaults: public CommonRadioFaults
{
public:

    static std::shared_ptr<RrhFaults> getInstance() ;

    ~RrhFaults(){};

    RrhFaults();

    /**
     * Method use to return a reference to a fault created to hold the state of the System Synth
     * Fault Major.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param none
     * @return a pointer to the fault
     */
    virtual std::shared_ptr<IFault> getSystemSynthFault( void ) override;

    /**
     * Method use to return a reference to a fault created to hold the state of the Cpri Loss Of
     * Signal Fault Major, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the fault
     */
    virtual std::shared_ptr<IFault> getCpriLossOfSignalFaultMajor( int index ) override;

	/**
     * Method use to return a reference to a fault created to hold the state of the Cpri Loss Of Frame
     * Fault Major, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the fault
     */
    virtual std::shared_ptr<IFault> getCpriLossOfFrameFaultMajor( int index ) override;

    /**
     * Method use to return a reference to a fault created to hold the state of the power loop control
     * Fault Major, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the fault
     */
    virtual std::shared_ptr<IFault> getCpriRemoteAlarmIndicationFaultMajor( int index ) override;

    /**
     * Method use to return a reference to a fault created to hold the state of the Cpri Sap Defect Ind
     * Fault Major, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the fault
     */
    virtual std::shared_ptr<IFault> getCpriSapDefectIndFaultMajor( int index ) override;

    /**
     * Method use to return a reference to a fault created to hold the state of the power loop control
     * convergence major fault, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the PCL convergence major fault
     */
    virtual std::shared_ptr<IFault> getPclConvergenceMajor( int index ) override;

    /**
     * Method use to return a reference to a fault created to hold the state of the power loop control
     * over power major fault, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the PCL over power major fault
     */
    virtual std::shared_ptr<IFault> getPclOverPowerMajor( int index ) override;

    /**
     * Method use to return a reference to a fault created to hold the state of the power loop control
     * power measurement major fault, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the PCL over power major fault
     */
    virtual std::shared_ptr<IFault> getPclPowerMeasurementMajor( int index ) override;

   /**
	* Method use to return a reference to a fault created to hold the state of the VSWR
	* monitor major fault, for each transmit path.
	*
	* This method throws an exception if the if the index is invalid. This must be considered a
	* programming error and should be corrected.
	*
	* @param index zero based reference to the transmit path
	* @return a pointer to the PCL over power major fault
	*/
    virtual std::shared_ptr<IFault> getVswrMajor( int index ) override;

    /**
     * Method use to return a reference to a fault created to hold the state of the DPD TX
     * Fault Major, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the fault
     */
    virtual std::shared_ptr<IFault> getDpdTxFaultMajor( int index ) override;

    /**
     * Method use to return a reference to a fault created to hold the state of the DPD TX
     * Fault Minor, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the fault
     */
    virtual std::shared_ptr<IFault> getDpdTxFaultMinor( int index ) override;


protected:
    std::shared_ptr<IFault> mCpri0LossOfSignalFaultMajor;
    std::shared_ptr<IFault> mCpri0LossOfFrameFaultMajor;
    std::shared_ptr<IFault> mCpri0RemoteAlarmIndicationFaultMajor;
    std::shared_ptr<IFault> mCpri0SapDefectIndFaultMajor;
    std::shared_ptr<IFault> mCpri1LossOfSignalFaultMajor;
    std::shared_ptr<IFault> mCpri1LossOfFrameFaultMajor;
    std::shared_ptr<IFault> mCpri1RemoteAlarmIndicationFaultMajor;
    std::shared_ptr<IFault> mCpri1SapDefectIndFaultMajor;

 	std::shared_ptr<IFault> mSynthClockFault;
    std::shared_ptr<IFault> mDpdPllLockFaultMajor;
    std::shared_ptr<IFault> mRxPllLockFaultMajor;
    std::shared_ptr<IFault> mTxPllLockFaultMajor;
    std::shared_ptr<IFault> mRefPllLockFaultMajor;

    std::vector<std::shared_ptr<IFault>> mTxOverPowerFaultMajor;

    std::vector<std::shared_ptr<IFault>> mTxOverPowerFaultMinor;

    std::vector<std::shared_ptr<IFault>> mTxUnderPowerFaultMinor;

    std::vector<std::shared_ptr<IFault>> mBoardTxOverTemperatureFaultMajor;

    std::vector<std::shared_ptr<IFault>> mPaOverTemperatureFaultMajor;

    std::vector<std::shared_ptr<IFault>> mBoardTxOverTemperatureFaultMinor;

    std::vector<std::shared_ptr<IFault>> mPaOverTemperatureFaultMinor;

    std::vector<std::shared_ptr<IFault>> mBoardTxUnderTemperatureFaultMajor;

    std::vector<std::shared_ptr<IFault>> mPaUnderTemperatureFaultMajor;

    std::vector<std::shared_ptr<IFault>> mPclTxConvergenceFaultMajor;

    std::vector<std::shared_ptr<IFault>> mPclTxOverPowerFaultMajor;

    std::vector<std::shared_ptr<IFault>> mDpdTxFaultMajor;

    std::vector<std::shared_ptr<IFault>> mDpdTxFaultMinor;

    std::vector<std::shared_ptr<IFault>> mPopTripTxFaultMajor;

    std::vector<std::shared_ptr<IFault>> mSrlTxFaultMajor;

    std::shared_ptr<IFault> mHeartBeatFaultMajor;

    std::vector<std::shared_ptr<IFault>> mTxPowerMeasurementFaultMajor;

    std::vector<std::shared_ptr<IFault>> mVswrTxFaultMajor;

    std::shared_ptr<IFaultsList> mFaultsList;
};

}

#endif  // _MPLANE_ZCU111_RRH_FAULTS__H_
