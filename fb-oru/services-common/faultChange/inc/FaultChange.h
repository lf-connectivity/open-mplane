#ifndef _VSI_FAULT_CHANGE__H_
#define _VSI_FAULT_CHANGE__H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultChange.h
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
#include "Task.h"

#include "IFaultChange.h"

namespace Mplane
{

/*! \brief  Generic Fault Change interface
 *
 *  A virtual interface base class defining an interface to a Fault changing implementation
 */
class FaultChange : public IFaultChange
{
public:

	FaultChange();
    virtual ~FaultChange();

    /*! \brief Virtual method to get the fault name
     *
     * \return The Frequency
     */
    virtual const std::string& getFaultName( void );

    /*! \brief Virtual method to set the fault name
      *
      * \return The Frequency
      */
     virtual void setFaultName( const std::string& faultName );

private:
     std::string mFaultName; //!> The name of the fault to record.

     mutable Mutex mMutex ;   //!> Mutex control to prevent methods from being called from within and outside of the task.
};

} /* namespace Mplane */

#endif /* _VSI_FAULT_CHANGE__H_ */
