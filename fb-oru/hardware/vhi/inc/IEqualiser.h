#ifndef _VHI_IEQUALISER_H_
#define _VHI_IEQUALISER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IEqualiser.h
 * \brief     A file to define generic interface to equaliser module
 *
 *
 * \details   A file to define generic interface to equaliser module
 *
 */

#include "GlobalTypeDefs.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

namespace Mplane
{

/*! \brief  Generic IEqualiser interface
 *
 *  A virtual interface base class defining an interface to equaliser in FPGA.
 *  The interface calculates the equaliser coefficients based on calibration data and center frequency.
 */
class IEqualiser
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~IEqualiser() { };

    /*! \brief Pure virtual method to calculate equaliser coefficients
     *
     * \param  path
     * \return Return state of the set calculation is successful or not
     */
    virtual ReturnType::State calculateEqualiser( void ) = 0;

    /*! \brief Pure virtual method to read whether equaliser is in
     * passthrough mode
     *
     * \return true/false
     */
    virtual bool getPassthroughMode( void ) = 0;

    /*! \brief Pure virtual method to enable/disable equaliser
     * passthrough mode
     *
     * \param enable - to turn ON/OFF the passthrough mode
     * \return None
     */
    virtual void setPassthroughMode( bool enable ) = 0;

    /**
     * @brief Print out contents of equaliser to stdout
     * Used for debug only
     */
    virtual void show(std::ostream& os = std::cout) const = 0 ;

protected:
    IEqualiser() {};
};

/**
 * The ITxEqualiserFactory is a polymorphic Tx equaliser interface factory that allows a
 * specific radio implementation to set the number of Tx equalisers supported by
 * that particular hardware implementation and return them as a vector that is
 * stored in the common radio implementation.
 *
 * @note This factory must be implemented by each radio type where its physical
 * characteristics have nothing in common with any existing implementation.
 */
class ITxEqualiserFactory
{
public:
    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a list of equalisers. The return value, is a vector of
     * pointers to the common IEqualiser interface.
     *
     * \return a vector containing maxPorts Tx equaliser interface pointers.
     */
    static std::vector< std::shared_ptr<IEqualiser> > getEqualisers( );
};

/**
 * The IRxEqualiserFactory is a polymorphic Rx equaliser interface factory that allows a
 * specific radio implementation to set the number of Rx equalisers supported by
 * that particular hardware implementation and return them as a vector that is
 * stored in the common radio implementation.
 *
 * @note This factory must be implemented by each radio type where its physical
 * characteristics have nothing in common with any existing implementation.
 */
class IRxEqualiserFactory
{
public:
    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a list of equalisers. The return value, is a vector of
     * pointers to the common IEqualiser interface.
     *
     * \return a vector containing maxPorts Rx equaliser interface pointers.
     */
    static std::vector< std::shared_ptr<IEqualiser> > getEqualisers( );
};

} /* namespace Mplane */

#endif /* _VHI_IEQUALISER_H_ */
