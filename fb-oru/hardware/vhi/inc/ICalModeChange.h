#ifndef _VHI_ICALMODE_CHANGE__H_
#define _VHI_ICALMODE_CHANGE__H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICalModeChange.h
 * \brief     A file to define generic interface to a Calibration mode changing implementation
 *
 *
 * \details   A file to define generic interface to a Calibration mode changing implementation
 *
 */

namespace Mplane
{

/*! \brief  Generic Calibration mode Change interface
 *
 *  A virtual interface base class defining an interface to a Calibration mode changing implementation
 */
class ICalModeChange
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~ICalModeChange() { };

    /*! \brief Pure virtual method to get the cal mode
     *
     * \return The cal mode
     */
    virtual bool getCalMode( void ) = 0;
};

} /* namespace Mplane */

#endif /* _VHI_ICALMODE_CHANGE__H_ */
