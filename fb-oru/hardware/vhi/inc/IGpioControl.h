#ifndef _VRH_IGPIOCONTROL_H_
#define _VRH_IGPIOCONTROL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IGpioControl.h
 * \brief     A file to contain a generic gpio interface to control individual pins.
 *
 *
 * \details   This file defines a generic gpio interface to control individual pins
 *
 */

#include "GlobalTypeDefs.h"
#include <memory>
#include <string>

namespace Mplane
{

/*! \brief  Generic gpio pin control Interface
 *
 *  A virtual interface base class defining a functional interface that must be
 *  adopted by any implementation of a generic gpio interface that controls individual lines.
 *
 *  This virtual interface allows controlling the individual GPIO lines.
 *
 */
class IGpioControl
{
public:

    /**
     * Enumeration for GPIO direction
     */
    enum class GpioDirection {
    	DIR_OUT,
    	DIR_IN
    } ;

    /*! \brief  Set direction of GPIO line
     *
     *  Method used to set the direction of a GPIO line at a specified index.
     *
     *  \return  bool - Whether method is successful
     */
    virtual bool setDirection(unsigned index, GpioDirection dir) = 0;

    /*! \brief  Get direction of GPIO line
     *
     *  Method used to get the direction of a GPIO line at a specified index.
     *
     *  \return  bool - Whether method is successful
     */
    virtual bool getDirection(unsigned index, GpioDirection& dir) = 0;

    /*! \brief  Set value of GPIO line
     *
     *  Method used to set the value of a GPIO line at a specified index.
     *
     *  \return  bool - Whether method is successful
     */
    virtual bool setValue(unsigned index, int value) = 0;

    /*! \brief  Get value of GPIO line
     *
     *  Method used to get the value of a GPIO line at a specified index.
     *
     *  \return  bool - Whether method is successful
     */
    virtual bool getValue(unsigned index, int& value) = 0;

	/**
	 * Error string set whenever any method fails. Reading the error string clears the internal error string
	 */
	virtual std::string error() =0 ;

	/**
	 * DEBUG: Enable/disable debug
	 */
	virtual void setDebug(bool debug) =0 ;

    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~IGpioControl() { };

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    IGpioControl() {};


};



} /* namespace Mplane */

#endif // _VRH_IGPIOCONTROL_H_
