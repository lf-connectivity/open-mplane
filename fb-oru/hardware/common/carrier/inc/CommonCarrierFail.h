#ifndef _ACE_AXIS_COMMONCARRIERFAIL_H_
#define _ACE_AXIS_COMMONCARRIERFAIL_H_

#include <string>
#include "ICarrierFail.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierFail.h
 * \brief     Defines an interface for carrier failure
 *
 *
 * \details   Implements the carrier failure capture interface so that these common methods (used by multiple carrier
 * classes) can be stored in the single object. Object is not expected to be instantiated stand-alone, but rather
 * part of multiple inheritance.
 *
 */

namespace Mplane
{


class CommonCarrierFail : public ICarrierFail
{
public:

    /*! @brief  Constructor
     *
     *  Allow construction through the interface
     */
    CommonCarrierFail();


    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~CommonCarrierFail() ;


    /*! @brief  Get failure reason
     *
     *  If a method fails, then this method will return a
     *  string describing the reason for failure
     * @return string containing reason for failure, or empty string if no fail
     */
    virtual std::string failReason(void) ;


    /*! @brief  Set failure reason
     *
     *  Set the failure reason string
     * @param reason string containing reason for failure
     */
    virtual void setFailReason(const std::string& reason) ;

    /*! @brief  Clear failure reason
     *
     * Clear out the failure reason string
     * @param reason string containing reason for failure
     */
    virtual void clearFailReason() ;

private:

    /**
     * Failure reason
     */
    std::string mFailureReason ;

};


}
#endif /* _ACE_AXIS_COMMONCarrierFail_H_ */
