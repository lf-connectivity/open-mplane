#ifndef _COMMONRADIOFAULTS_H_
#define _COMMONRADIOFAULTS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRadioFaults.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IFault.h"
#include "ICommonRadioFaults.h"

namespace Mplane
{

/**
 * This class provides a base class implementation of the ICommonRadioFaults interface that simply
 * throws a not supported exception for every method defined by the interface.
 *
 * In this way application specific implementations of the common radio faults interface must override
 * each fault that it supports to prevent software exception errors.
 *
 * The common implementation does not provide an implementation of the static ICommonRadioFaults::getInterface()
 * method as it should never be instantiated in itself.
 *
 */
class CommonRadioFaults: public ICommonRadioFaults
{
public:

    /**
     * Default destructor for common radio faults implementation
     */
    virtual ~CommonRadioFaults(){};

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
    virtual std::shared_ptr<IFault> getPclConvergenceMajor( int index ); /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getPclOverPowerMajor( int index ); /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getPclPowerMeasurementMajor( int index ); /* throw (std::invalid_argument) */


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
    virtual std::shared_ptr<IFault> getCpriLossOfSignalFaultMajor( int index ); /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getCpriLossOfFrameFaultMajor( int index ); /* throw (std::invalid_argument) */

    /**
     * Method use to return a reference to a fault created to hold the state of the Remote Alarm Indication
     * Fault Major, for each transmit path.
     *
     * This method throws an exception if the if the index is invalid. This must be considered a
     * programming error and should be corrected.
     *
     * @param index zero based reference to the transmit path
     * @return a pointer to the fault
     */
    virtual std::shared_ptr<IFault> getCpriRemoteAlarmIndicationFaultMajor( int index ); /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getCpriSapDefectIndFaultMajor( int index ); /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getSystemSynthFault( void );

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
    virtual std::shared_ptr<IFault> getVswrMajor( int index ); /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getDpdTxFaultMajor( int index ); /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getDpdTxFaultMinor( int index ); /* throw (std::invalid_argument) */


};

}


#endif /* _COMMONRADIOFAULTS_H_ */
