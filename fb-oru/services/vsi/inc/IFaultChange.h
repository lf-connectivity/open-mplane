#ifndef _VSI_IFAULT_CHANGE__H_
#define _VSI_IFAULT_CHANGE__H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFaultChange.h
 * \brief     A file to define generic interface to a Fault changing implementation
 *
 *
 * \details   A file to define generic interface to a Fault changing implementation
 *
 */

// Includes go here, before the namespace
#include <memory>
#include <set>

#include "GlobalTypeDefs.h"

namespace Mplane
{

/*! \brief  Generic Fault Change interface
 *
 *  A virtual interface base class defining an interface to a Fault changing implementation
 */
class IFaultChange
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~IFaultChange() { };

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the Fault Change within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IFaultChange> getInstance( void );

    /*! \brief Pure virtual method to get the frequency
     *
     * \return The Frequency
     */
    virtual const std::string& getFaultName( void ) = 0;

    /*! \brief Pure virtual method to get the frequency
      *
      * \return The Frequency
      */
     virtual void setFaultName( const std::string& faultName ) = 0;
};

} /* namespace Mplane */

#endif /* _VSI_IFAULT_CHANGE__H_ */
