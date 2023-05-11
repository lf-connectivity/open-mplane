#ifndef _VHI_IREF_H_
#define _VHI_IREF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRef.h
 * \brief     A file to define generic interface to an IRef (10MHz Reference) Module
 *
 *
 * \details   A file to define generic interface to an IRef (10MHz Reference) Module
 *
 */

#include <vector>
#include <stdexcept>
#include <memory>

#include "II2c.h"
#include "IDevice.h"

namespace Mplane
{

/*! \brief  Generic IRef interface
 *
 *  A virtual interface base class defining an interface to a IRef bus.
 *  The interface contains configuration and control aspects.
 */
class IRef : public virtual IDevice
{
public:

    /*! \brief Operating mode enumeration - Manual or Automatic
     *
     */
    typedef enum
    {
        manualMode    = 0,
        automaticMode = 1,
        unsetMode
    } opMode_T;

    /*! \brief Signal present enumeration - Signal Present or No Signal Present
     *
     */
    typedef enum
    {
        signalPresent    = 0,
        signalNotPresent = 1,
        signalUnset
    } sigPresent_T;

    /*! \brief Manual mode enumeration - External Input or Internal Input
     *
     */
    typedef enum
    {
        externalInput = 0,
        internalInput = 1,
        unsetInput
    } manualMode_T;

    /*! \brief Destructor
     *
     */
    virtual ~IRef() { };

    /*! \brief Pure virtual method to get the manual mode
     *
     * An enumerated type stating if the manual mode is internal or external
     *
     * \return Manual mode setting
     */
    virtual manualMode_T getManualMode() = 0;

    /*! \brief Pure virtual method to set the manual mode
     *
     * An enumerated type stating if the manual mode is internal or external
     *
     * \param manualMode_T manualModeToSet Set the manual mode to internal or external
     * \return none
     */
    virtual void setManualMode(manualMode_T manualModeToSet) = 0;

    /*! \brief Pure virtual method to get the reference operating mode
     *
     * An enumerated type stating if the operating mode is automatic or manual
     *
     * \return Operation mode setting
     */
    virtual opMode_T getOpMode() = 0;

    /*! \brief Pure virtual method to set the operating mode
     *
     * An enumerated type stating if the operating mode is automatic or manual
     *
     * \param opMode_T opModeToSet Set the operating mode to automatic or manual
     * \return none
     */
    virtual void setOpMode(opMode_T opModeToSet) = 0;

    /*! \brief Pure virtual method to get the reference signal present indication
     *
     * An enumerated type stating if the signal is present or not
     *
     * \return Signal present indication
     */
    virtual sigPresent_T getSigPresent() = 0;

    /**
     * \brief   Get an instance of the Reference interface
     * \return  return a reference to the interface
     */
    static std::shared_ptr<IRef> getInterface( int deviceIndex );

protected:
    IRef() {};
};

} /* namespace Mplane */

#endif /* _VHI_IREF_H_ */
