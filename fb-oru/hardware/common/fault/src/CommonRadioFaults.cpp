/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRadioFaults.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <memory>

#include "IFault.h"
#include "CommonRadioFaults.h"

using namespace Mplane;

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getPclConvergenceMajor( int index ) /* throw (std::invalid_argument) */
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getPclOverPowerMajor( int index ) /* throw (std::invalid_argument) */
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getPclPowerMeasurementMajor( int index ) /* throw (std::invalid_argument) */
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getCpriLossOfSignalFaultMajor(int index) /* throw (std::invalid_argument) */
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getCpriLossOfFrameFaultMajor(int index) /* throw (std::invalid_argument) */
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getCpriRemoteAlarmIndicationFaultMajor(int index) /* throw (std::invalid_argument) */
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getCpriSapDefectIndFaultMajor(int index) /* throw (std::invalid_argument) */
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getSystemSynthFault( void )
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getVswrMajor(int index)
        /* throw (std::invalid_argument) */
{
    std::invalid_argument e("Fault not supported");
    throw(e);
    return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getDpdTxFaultMajor(
		int index) /* throw (std::invalid_argument) */
{
	std::invalid_argument e("Fault not supported");
	throw(e);
	return std::shared_ptr<IFault>();
}

std::shared_ptr<IFault> Mplane::CommonRadioFaults::getDpdTxFaultMinor(
		int index) /* throw (std::invalid_argument) */
{
	std::invalid_argument e("Fault not supported");
	throw(e);
	return std::shared_ptr<IFault>();
}
