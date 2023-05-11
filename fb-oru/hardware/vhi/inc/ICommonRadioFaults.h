#ifndef _ICOMMONRADIOFAULTS_H_
#define _ICOMMONRADIOFAULTS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICommonRadioFaults.h
 * \brief     Defines an interface for all common radio fault conditions
 *
 *
 * \details   Defines an interface for all common radio fault conditions
 *
 */
#include <memory>
#include <stdexcept>

#include "IFault.h"

namespace Mplane
{

/**
 * This class provides an interface to the common radio alarms defined for all radios. If a particular
 * fault is not supported by a customer specific radio implementation it will throw an exception.
 * This indicates a software programming error that must be corrected.
 *
 * The principle aim of this interface is to provide a generic method of obtaining fault references
 * so that the radio application implementation can take ownership of fault generation. All faults
 * are mapped singularly or in groups to higher customer visible alarms.
 *
 */
class ICommonRadioFaults
{
public:

    /**
     * This method provides a means to get a single instance of the common radio faults
     * object for this radio.
     *
     * @return a shared pointer to the ICommonRadioFaults implementation
     */
    static std::shared_ptr<ICommonRadioFaults> getInstance(void);

    /**
     *  Default virtual destructor.
     */
    virtual ~ICommonRadioFaults(){};

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
    virtual std::shared_ptr<IFault> getPclConvergenceMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getPclOverPowerMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getPclPowerMeasurementMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getCpriLossOfSignalFaultMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getCpriLossOfFrameFaultMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getCpriRemoteAlarmIndicationFaultMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getCpriSapDefectIndFaultMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getSystemSynthFault( void ) = 0;

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
    virtual std::shared_ptr<IFault> getVswrMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getDpdTxFaultMajor( int index ) =0; /* throw (std::invalid_argument) */

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
    virtual std::shared_ptr<IFault> getDpdTxFaultMinor( int index ) =0; /* throw (std::invalid_argument) */
};

}


#endif /* _ICOMMONRADIOFAULTS_H_ */
