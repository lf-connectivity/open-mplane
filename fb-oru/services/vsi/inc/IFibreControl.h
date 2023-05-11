#ifndef _VRS_IFIBRECONTROL_H_
#define _VRS_IFIBRECONTROL_H_

#include <memory>

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFibreControl.h
 * \brief     Pure virtual interface that defines methods needed to control a Fibre interface
 *
 *
 * \details   Pure virtual interface that defines methods needed to control a Fibre interface
 *
 */

namespace Mplane
{

/*! \brief Provides a standard interface to the Fibre links.
 *
 * The IFibreControl interface is provided to allow for the creation of
 * a singleton class that will provide the entry point to the fibre control
 * process. The following example shows how the interface is used.
 *
 * \code
 *
 * {
 *     IFibreControl& fibreController = IFibreControl::getInterface();
 *
 *     fibreController.start();
 * }
 * \endcode
 *
 */
class IFibreControl
{
public:

    /**
     * Method defines a static method used to get the single instance of
     * the fibre controlling module.
     *
     * \return a reference to the fibre control interface class
     */
    static std::shared_ptr<IFibreControl> getInterface();

    /**
     * This method is to show the fibre control status.
     */
    virtual void showFibreControl() = 0;

    /**
     * This method is the entry point to the fibre controlling application.
     * It will start the radio specific Fibre controlling task and initialise the fibre
     * hardware.
     *
     * After a successful start up process, it will implement fibre control operations,\n
     * eg. monitoring for alarms, responding to OAM requests.
     */
    virtual void startFibreControl() = 0;

    /**
     * Method that is called periodically, eg. 1 second, to perform fibre controlling functions.
     */
    virtual void serviceFibreControl() = 0;

    /**
     * This method will reset the fibre control
     */
    virtual void resetFibreControl() = 0;

    /**
     * Destructor - will never be called in normal execution
     */
    virtual ~IFibreControl() { }


protected:

};


} /* namespace Mplane */

#endif /* _VRS_IFIBRECONTROL_H_ */
