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


#ifndef _SERVICES_IVSWR_H_
#define _SERVICES_IVSWR_H_

#include <memory>
#include "Power.h"
#include "Frequency.h"

namespace Mplane {


/*! @brief  Transmit Path Voltage Standing Wave Ratio Monitor
 *
 * The purpose of IVswr is to provide a common interface to the VSWR monitor functionality
 * of the radio transmit path. VSWR is used for historical purposes, the object in fact
 * provides a measurement of return loss.
 *
 * The return loss is then compared against a given threshold to determine the quality
 * of the antenna connection. If the threshold is continually exceeded a fault is
 * generated and the system can take appropriate action.
 *
 *
 */
class IVswr
{
public:
	virtual ~IVswr() {}

    /*! @brief  Get an instance on the IVswr interface for the given transmit path index
     *
     *  Method used to obtain a reference to the single instance of the VSWR monitor for each
     *  transmit path within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IVswr> getInstance(int index);



	/**
	 * This method allows the return loss fault threshold to be set. A value of zero
	 * will disable the threshold check.
	 *
	 * @param  threshold set point
	 * @return true if new threshold successfully set
	 */
	virtual bool setThreshold( Power threshold ) = 0;

	/**
	 * This method can be used to change the rate at which the return loss calculation
	 * is made.
	 *
	 * @param update rate in seconds
	 * @return true if a valid update rate is set
	 */
	virtual bool setPeriod( int seconds ) = 0;



	 /**
	  * Method used to return the currently set return loss threshold.
	  *
	  * @return threshold
	  */
     virtual Power getThreshold() = 0 ;

     /**
      * Method used to return the currently set measurement update period in seconds
      *
      * @return update period
      */
     virtual int getPeriod() = 0;

     /**
      * Method used to report the calculated return loss.
      *
      * @return
      */
     virtual Power getReturnLoss() = 0;

     /**
      * Method indicates whether VSWR monitoring is actual active
      *
      * @return false when threshold or period are 0, or no TX power, true when actively monitoring.
      */
     virtual bool isActive() = 0;


     /**
      * Method indicates whether the monitor has detected a VSWR fault state
      *
      * @return true is active and the return loss exceeds the threshold, otherwise false.
      */
     virtual bool faultState() = 0;

     /**
      * This method will be called every second by the TxService that creates it. It will
      * check the update period and update the return loss power calculation and if necessary
      * compare it to the current failure threshold.
      *
      */
     virtual void processMeasurements() = 0;

     typedef enum
     {
    	 automatic = 0,
		 manual
     } vswrShutdownMode_T;

     /**
      * This method is used to set the VSWR shutdown mode. The actual implementation and meaning
      * will be defined else where.
      */
     virtual void setShutdownMode(vswrShutdownMode_T shutdownMode) = 0;

     /**
      * This method is used to get the VSWR shutdown mode. The actual implementation and meaning
      * will be defined else where.
      */
     virtual vswrShutdownMode_T getShutdownMode() = 0;
} ;

}

#endif /* _SERVICES_IVSWR_H_ */
