#ifndef _hardware_LED_SYSTEM_H_
#define _hardware_LED_SYSTEM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LedSystem.h
 * \brief     A file to define the interface to the System LED.
 *
 *
 * \details   A file to define the interface to the System LED.
 *
 */

#include "GlobalTypeDefs.h"
#include "Loggable.h"

#include "IGpioKernel.h"

#include "Task.h"
#include "Conditional.h"

namespace Mplane
{

/*!
 *
 * \brief The LedSystem class is used specifically to program the System board LED
 *
 */
class LedSystem : public Task
{
public:

    friend class LedSystemTestCases;

    /*!
     *
     * \brief LedSystem constructor
     *
     * \param gpioAddress The GPIO address for this LED driver device
     *
     */
    explicit LedSystem( UINT16 writeGpioAddress );

    /*!
     * \brief LedSystem destructor
     */
    virtual ~LedSystem();

    /*!
     *
     * \brief Method used to initialise the LED driver device.
     *
     * \param no parameters are required for this method
     * \return RT_OK if successful, RT_other otherwise
     */
    virtual ReturnType::State initialise(void);

    /*!
     *
     * \brief Method used to set the individual LED parameters.
     *
     * \param   ledNumber   Led number from 0 to 7
     * \param   ledColour   Uses the ILed definitions for red/amber/green
     * \param   ledState    Uses the ILed definitions for on/off/flash/breath
     * \param   ledRate     Transition effects rate for flashing and breathing
     * \return RT_OK if successful, RT_other otherwise
     */
    ReturnType::State setLed(UINT8 ledNumber, UINT8 ledColour, UINT8 ledState, UINT8 ledRate);

    /*!
     *
     * \brief Method used to change the LED from its current setting.
     *
     * \param data buffer containing the data to write
     * \param the data length
     *
     * \return RT_OK if successful, RT_other otherwise
     */
    virtual ReturnType::State write(UINT32 regOffset, UINT32 value, UINT32 mask);

    /*!
     *
     * \brief shows the device parameter settings
     *
     * \return none
     * \param none
     */
    virtual void show(void);

private:

    // LED definitions; NOTE this must align with the SystemLed.h definitions.
    static const UINT8 systemLed = 0;    //!> Index for the system led

    static const UINT8 NUM_LEDS  = 1;    //!> Maximum number of LED's

protected:

    UINT16 mWriteGpioAddress; //!> Write GPIO address

    std::shared_ptr<IGpioKernel> gpioDevice ; //!> Kernel interface singleton

    bool   mEnableFlashLed;   //!> Flashing LED is enabled
    UINT32 mSolidColour;      //!> LED solid colour red/green/yellow
    UINT32 mToggleState;	  //!> LED flash toggling state on/off
    UINT32 mFlashColour;      //!> LED flash colour red/green/yellow
    UINT32 mFlashRate;        //!> LED rate

    UINT32 mFlashTimerCounter;//!> 50ms divider counter for flashing the LED.

    static const UINT32 GREEN_LED          = 0x01; //!> Bit definition for the green led
    static const UINT32 YELLOW_LED         = 0x02; //!> Bit definition for the yellow led
    static const UINT32 RED_LED            = 0x04; //!> Bit definition for the red led

    static const unsigned SYS_LED_BASE_REG = 25;   //!> Base register bit position for the led's

    static const UINT32 SYS_LED_MASK       = 0x07; //!> Mask for the LED's

    static const UINT32 SYS_LED_OFF        = 0x00; //!> System LED off definition
    static const UINT32 SYS_LED_ON         = 0x01; //!> System LED on definition
    static const UINT32 SYS_LED_FLASH      = 0x02; //!> System LED flash definition

    // Methods supporting the task inheritance
    // ---------------------------------------
    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int  run();      //!> Implementation of the flashing LED
    virtual void shutdown(void);

    bool mTaskRunning; 		 //!> Task loop control

    /**
     * This conditional is used in the main run loop by calling the
     * conditionals wait with timeout method the service() method will either
     * be called as a result of the timer expiring or being notified by
     * a call to the conditional signal method.
     */
    Conditional mConditional;

    mutable Mutex mMutex ;   //!> Mutex control to prevent methods from being called from within and outside of the task.
};

}  // end of namespace AxeAxis

#endif /* _hardware_LED_SYSTEM_H_ */
