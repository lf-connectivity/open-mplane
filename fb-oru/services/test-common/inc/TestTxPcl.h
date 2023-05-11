#ifndef _TESTTXPCL_H_
#define _TESTTXPCL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestTxPcl.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "ITxPcl.h"

namespace Mplane
{

class TestTxPcl: public ITxPcl
{
public:

    TestTxPcl( int index ):
        mIndex(index)
    {

    }

    virtual ~TestTxPcl() {}


    /**
     * Call this method to send TX_ON event to he PCL state machine
     *
     * @return
     */
    virtual bool setTxOn()
    {
        return true;
    }

    /**
     * Call this method to send a TX_OFF event to the PCL state machine
     *
     * @return
     */
    virtual bool setTxOff()
    {
        return true;
    }

    /**
     * Call this method to send a TARGET_POWER event to the PCL state machine
     *
     * @return
     */
    virtual bool setTargetPower()
    {
        return true;
    }


    /**
     * Call this method to set the PCL state machine into manual mode
     * @return
     */
    virtual bool setManual()
    {
        return true;
    }

    /**
     * Call this method to set the PCL state machine into testing mode
     * @return
     */
    virtual bool setTesting()
    {
        return true;
    }

    /**
     * Call this method to set the PCL state machine into automatic mode, it
     * will return to its previous state
     * @return
     */
    virtual bool setAuto()
    {
        return true;
    }

    /**
     * Calling this method will force an update to the loop in the current state.
     * This method is called periodically by the parent service of the closed
     * loop power control logic.
     * @return
     */
    virtual bool timerUpdate()
    {
        return true;
    }

     /**
      * Returns the current PCL state
      * @return PCL state
      */
     virtual TxPclState getState()
     {
         return TxPclState::OFF;
     }


     /**
      * Get the current power control loop state, as a string
      * @return
      */
     virtual std::string getStateStr()
     {
         return "OFF";
     }


     /**
      * This method is to show the PCL status.
      */
     virtual void showPcl()
     {

     }

     /**
      * Method used to return the target out power that the control loop is trying to achieve
      * @return
      */
     virtual Power getTargetPower(void)
     {
         Power power(43.0);
         return power;
     }


     /**
      * Get the index into the TxPort to which this instance of PCL is attached
      * @return
      */
     virtual int getIndex() const
     {
         return mIndex;
     }

     /**
      * Method to return the current error between the target power and the actual power.
      *
      * @return
      */
     virtual Power getGainError()
     {
         Power power(3.0);
         return power;
     }

     /**
      * Return the set point for the initial open loop radio power value.
      * @return
      */
     virtual Power getOpenLoopTarget()
     {
         Power power(-12.0);
         return power;
     }

     /**
      * Method to return the last output power reading associated with the path
      * @return
      */
     virtual Power getRfOutputPower()
     {
         Power power(40.0);
         return power;
     }

     /**
      * Method to return the las digital input power reading associated with the path
      * @return
      */
     virtual Power getDigitalInputPower()
     {
         Power power(-14.0);
         return power;
     }

     /**
      * Method to return the last calculated TX path attenuation required
      * @return
      */
     virtual Power getAttenuation()
     {
         Power power(12.0);
         return power;
     }


     /**
      * Method returns the value for the amount the initial open loop power set point to
      * backed off for the PA operational band limits (PA max-min power)
      * @return
      */
     virtual Power getPABandBackoff()
     {
         Power power(24.0);
         return power;
     }

     /**
      * Method to return the maximum digital input power for the path
      * @return
      */
     virtual Power getMaxInputPower()
     {
         Power power(-13.0);
         return power;
     }

     /**
      * Method to return the reference level, the difference between the maximum expected
      * digital input power and the measured digital input power.
      * @return
      */
     virtual Power geInputRefPower()
     {
         Power power(1.0);
         return power;
     }


protected:
    int mIndex;
};

}

#endif /* _TESTTXPCL_H_ */
