#ifndef _VSWRMON_H_
#define _VSWRMON_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      VswrMon.h
 * \brief     Define an object that performs return loss calculations and raises antenna faults
 *
 *
 * \details   Define an object that performs return loss calculations and raises antenna faults
 *
 */

#include "Power.h"
#include "IVswr.h"
#include "FaultOwner.h"
#include "ICommonRadioFaults.h"
#include "ITxPort.h"
#include "Loggable.h"
#include "MovingAvg.hpp"
#include "ITxPcl.h"

namespace Mplane
{


class VswrMon: public IVswr,    public Loggable

{
public:

    explicit VswrMon( int path );

    virtual ~VswrMon();


    /**
     * This method allows the return loss fault threshold to be set. A value of zero
     * will disable the threshold check.
     *
     * @param  threshold set point
     * @return true if new threshold successfully set
     */
    virtual bool setThreshold( Power threshold );

    /**
     * This method can be used to change the rate at which the return loss calculation
     * is made.
     *
     * @param update rate in seconds
     * @return true if a valid update rate is set
     */
    virtual bool setPeriod( int seconds );



     /**
      * Method used to return the currently set return loss threshold.
      *
      * @return threshold
      */
     virtual Power getThreshold();

     /**
      * Method used to return the currently set measurement update period in seconds
      *
      * @return update period
      */
     virtual int getPeriod();

     /**
      * Method used to report the calculated return loss.
      *
      * @return
      */
     virtual Power getReturnLoss();

     /**
      * Method indicates whether VSWR monitoring is actual active
      *
      * @return false when threshold or period are 0, or no TX power, true when actively monitoring.
      */
     virtual bool isActive();


     /**
      * Method indicates whether the monitor has detected a VSWR fault state
      *
      * @return true is active and the return loss exceeds the threshold, otherwise false.
      */
     virtual bool faultState();


     /**
      * This method will be called every second by the TxService that creates it. It will
      * check the update period and update the return loss power calculation and if necessary
      * compare it to the current failure threshold.
      *
      */
     virtual void processMeasurements();

     /**
      * This method is used to set the VSWR shutdown mode. The actual implementation and meaning
      * will be defined else where.
      */
     virtual void setShutdownMode(IVswr::vswrShutdownMode_T shutdownMode);

     /**
      * This method is used to get the VSWR shutdown mode. The actual implementation and meaning
      * will be defined else where.
      */
     virtual IVswr::vswrShutdownMode_T getShutdownMode();

     /**
      *  This internal class acts as a simple wrapper for the VSWR fault interface. It is used internal
      *  to set and clear the fault condition.
      */
     class VswrFaultOwner: public FaultOwner
     {
     public:
         explicit VswrFaultOwner( int path );

         std::shared_ptr<IFault> getFault();

         void set();

         void clear();

     protected:
         std::shared_ptr<IFault> mFault;
     };

     static const int UPDATE_RATE = 5;           //!< value for 1 sec update based on the TxService running at a 200 msec cycle

     static void setMode(IVswr::vswrShutdownMode_T mode);
     static IVswr::vswrShutdownMode_T getMode();

protected:
     int                mPath;                            //!< which path this monitor is associated with
     Power              mThreshold;                       //!< power threshold for checking the return loss
     MovingAvg<Power>   mReturnLoss;                      //!< the calculated return loss
     int                mPeriod;                          //!< the monitor update period

     std::shared_ptr<ICommonRadioFaults>    mFaults;
     std::shared_ptr<VswrFaultOwner>        mVswrFaultOwner;
     std::shared_ptr<ITxPort>               mTxPort;

     int    mPeriodCount;
     bool   mActive;
     Power  mForward;
     Power  mReverse;
     Power  mFwdDigital;
     Power  mRevDigital;

     static const int DEFAULT_PERIOD;
     static const int PERIOD_OFF;
     static const float DEFAULT_THRESHOLD;
     static const float THRESHOLD_OFF;
     static const float MIN_DIGITAL_POWER;
     static const float MAX_DIGITAL_POWER_DIFF;
     static const float LOWER_DIGITAL_THRESHOLD;

     std::shared_ptr<ITxPcl> mPcl;

private:
     static IVswr::vswrShutdownMode_T mShutdownMode; //!> current VSWR shutdown mode
};

}

#endif /* _VSWRMON_H_ */
