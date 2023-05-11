/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITxPcl.h
 * \brief     Interface for transmit PCL
 *
 *
 * \details   Defines the expected interface for transmit path closed loop power control
 *
 */


#ifndef _HARDWARE_ITXPCL_H_
#define _HARDWARE_ITXPCL_H_

#include <memory>
#include "Observer.hpp"
#include "Power.h"
#include "Frequency.h"

namespace Mplane {


/**
 * A scoped enumerator class that defines the states associated with the
 */
enum class TxPclState
{
    INIT,     //!< INIT - initial state used to setup and register with data providers.
    OFF,      //!< OFF  - waiting for a TX ON event to start,
    OPENLOOP, //!< OPENLOOP -  set radio open loop power and wait for DPD, when all is well then RAMP
    RAMP,     //!< RAMP - coarse ramp to power within narrow band of target power
    CONVERGE, //!< CONVERGE - Turns on DPD and ramps until DPD starts Q=2 iterations
    TRACK,    //!< TRACK - fine power adjustments around target power.
    MANUAL,   //!< MANUAL - leave all settings at point of entering manual mode
    TESTING,  //!< TESTING - same as Manual mode with handling for TX_OFF events when responding to faults
};

/**
 * The following events are processed by the closed loop power control state machine.
 * The state machine is called with one of these events in order to progress between states
 */
enum class TxPclEvent
{
    TX_OFF,           //!< TX_OFF - go to the shutdown state from current state
    TX_ON,            //!< TX_ON - start closed loop control, go to open loop state
    MANUAL,           //!< MANUAL - go to manual state from the current state
    AUTO,             //!< AUTO - go back to automated control at the previous control state
    TIMER_TICK,       //!< TIMER_TICK - process a 100ms timer tick in the current state
    TESTING,          //!< TESTING - go to testing state from the current state
};


/*! @brief  Transmit Path Closed Power Control
 *
 * The purpose of the ITxPcl class is to provide a common
 * interface to the power control loop in the application.
 *
 * The PCL implements a factory pattern so that one power control loop object
 * can exist for each TX path in the system. Any object in the application can
 * register as observers of a power control instance without knowing what actually implements.
 *
 * An implementation of the ITxPcl needs to provide the getState() method so that the subject can get the current PCL state
 * and it also needs to call Subject notify() method on state changes.
 *
 */
class ITxPcl : public Subject<ITxPcl>
{
public:
	virtual ~ITxPcl() {}

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the PCL within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<ITxPcl> getInstance(int index);



	/* PCL service update rate - may become configurable at some point */
	static const unsigned PCL_SERVICE_UPDATE_RATE = 50;


	/**
	 * Call this method to send TX_ON event to he PCL state machine
	 *
	 * @return
	 */
	virtual bool setTxOn() = 0;

	/**
	 * Call this method to send a TX_OFF event to the PCL state machine
	 *
	 * @return
	 */
	virtual bool setTxOff() = 0;


	/**
	 * Call this method to set the PCL state machine into manual mode
	 * @return
	 */
	virtual bool setManual() = 0;

    /**
     * Call this method to set the PCL state machine into automatic mode, it
     * will return to its previous state
     * @return
     */
    virtual bool setAuto() = 0;

	/**
	 * Call this method to set the PCL state machine into testing mode
	 * @return
	 */
	virtual bool setTesting() = 0;

    /**
     * Calling this method will force an update to the loop in the current state.
     * This method is called periodically by the parent service of the closed
     * loop power control logic.
     * @return
     */
    virtual bool timerUpdate() = 0;

     /**
      * Returns the current PCL state
      * @return PCL state
      */
     virtual TxPclState getState() = 0 ;


     /**
      * Get the current power control loop state, as a string
      * @return
      */
     virtual std::string getStateStr() = 0 ;


     /**
      * This method is to show the PCL status.
      */
     virtual void showPcl() = 0;

     /**
      * Method used to return the target out power that the control loop is trying to achieve
      * @return
      */
     virtual Power getTargetPower(void) = 0;


     /**
      * Get the index into the TxPort to which this instance of PCL is attached
      * @return
      */
     virtual int getIndex() const = 0;

     /**
      * Method to return the current error between the target power and the actual power.
      *
      * @return
      */
     virtual Power getGainError() = 0;

     /**
      * Return the set point for the initial open loop radio power value.
      * @return
      */
     virtual Power getOpenLoopTarget() = 0;

     /**
      * Method to return the last output power reading associated with the path
      * @return
      */
     virtual Power getRfOutputPower() = 0;

     /**
      * Method to return the lasT digital input power reading associated with the path
      * @return
      */
     virtual Power getDigitalInputPower() = 0;

     /**
      * Method to return the last calculated TX path attenuation required
      * @return
      */
     virtual Power getAttenuation() = 0;


     /**
      * Method returns the value for the amount the initial open loop power set point to
      * backed off for the PA operational band limits (PA max-min power)
      * @return
      */
     virtual Power getPABandBackoff() = 0;


     /**
      * Method to return the maximum digital input power for the path
      * @return
      */
     virtual Power getMaxInputPower() = 0;

     /**
      * Method to return the reference level, the difference between the maximum expected
      * digital input power and the measured digital input power.
      * @return
      */
     virtual Power geInputRefPower() = 0;


} ;


/**
 * This class defines an observer interface that must be implemented by objects
 * that need to process PCL state changes.
 *
 * Any object implementing this interface must register themselves with the
 * IPcl using the registerObserver(IPclObserver &observer )
 * function in order to receive any notification.
 *
 */
class ITxPclObserver : public Observer<ITxPcl>
{
public:
    virtual ~ITxPclObserver() {}
};


}

#endif /* IPCL_H_ */
