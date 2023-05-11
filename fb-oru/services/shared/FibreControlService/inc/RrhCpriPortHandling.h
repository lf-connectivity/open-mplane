#ifndef _RADIOSVCS_RRHCPRIPORTHANDLING_H_
#define _RADIOSVCS_RRHCPRIPORTHANDLING_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhCpriPortHandling.h
 * \brief     The class definition to control and monitor the CPRI link
 *
 *
 * \details   The class definition to control and monitor the CPRI link
 *
 */

#include <vector>
#include <memory>
#include "Loggable.h"
#include "ICpriPortHandler.h"
#include "ICpri.h"
#include "ICpriCore.h"
#include "Observer.hpp"

#include "CpriPortHandling.h"

namespace Mplane
{

/**
 * This class provides a facility to control and monitor the CPRI link.
 *
 * There is one instance of this class for each CPRI port.
 *
 * This class provides a Subject for observers to attach to if they want to be informed when
 * CPRI port changes state.
 */
class RrhCpriPortHandler: public CpriPortHandler
{
public:
    /**
     * Factory for creating instances of this CpriPortHandler for a particular port
     * @param port
     * @return shared pointer to new instance
     */
    static std::shared_ptr<ICpriPortHandler> factory(unsigned port, std::shared_ptr<ICpriSfpControlLogic> sfpLogic) ;

    virtual ~RrhCpriPortHandler();

protected:

    /**
     * Method to do default slave port setup for Auto Negotiating. This is the preferred method of setting
     * the line rate.\n
     * It will be called as part of the default core setup and if re-enabling the slave port if it has been disabled.
     */
    virtual void setupAutoNeg() override ;

    /**
     * Get the current setting for the allowable line rates
     */
    virtual ICpriCore::LineRateCapability getAllowableRates() override ;


protected:
    /** the constructor is supplied with the port instance number and the SFP control logic reference.
     *
     * \param instance is the port number instance, zero-based
     * \param sfpLogic is a reference to the class that contains specifics about the SFP control logic
     */
    RrhCpriPortHandler(UINT32 instance, std::shared_ptr<ICpriSfpControlLogic> sfpLogic);

};

} /* namespace Mplane */

#endif /* _RADIOSVCS_RRHCPRIPORTHANDLING_H_ */
