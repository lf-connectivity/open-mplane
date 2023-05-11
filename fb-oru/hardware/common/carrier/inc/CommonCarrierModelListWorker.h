#ifndef _ACE_AXIS_COMMONCARRIERMODELLISTWORKER_H_
#define _ACE_AXIS_COMMONCARRIERMODELLISTWORKER_H_

#include <string>
#include <memory>
#include "ICarrierFail.h"
#include "ICarrierModel.h"
#include "ICarrierHardware.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierModelListWorker.h
 * \brief     Common base for Carrier Model Workers (carrier hardware list)
 *
 *
 * \details   Defines the common functions of a carrier model worker that contains a Carrier Hardware List. This template
 * 			  performs all the common operations
 *
 */

namespace Mplane
{

/*! @brief  Carrier Model Worker interface
 *
 *  This class contains the information and methods for performing the carrier model actions
 *  on particular areas of the hardware representation of the carriers.
 *
 */
class CommonCarrierModelListWorker : public ICarrierModelWorker
{
public:

    /**
     *
     */
	CommonCarrierModelListWorker(unsigned maxCarriers, std::shared_ptr<ICarrierHardwareList> carrierList) ;

    /*! @brief  Initialise
     *
     *  Initialise this worker
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool initialise(void) ;

    /**
     * Method used to add a carrier reference to an underlying carrier list (expected to
     * be an ICarrierHardwareList but could be anything)
     *
     * @param carrier a reference to a carrier object that implements the ICarrier interface.
     * @return true if added successfully, otherwise false, eg invalid index.
     */
    virtual bool addCarrier( const ICarrier& carrier ) ;

    /*! @brief  Validate the carrier change
     *
     *  Ensure this worker is happy with the proposed carrier change
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool validateChange(const ICarrier& carrier) ;

    /*! @brief  Carrier change
     *
     *  Pass in the carrier settings for the newly changed carrier.
     * @param carrier new carrier reference
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool carrierChange(const ICarrier& carrier) ;

    /*! @brief  About to apply changes to hardware
     *
     * Called just prior to calling the updateHardware() method. Allows carrier to disable anything
     * that might affect the TX while changing setting (for example)
     * @return false if cannot accept the carrier settings
     */
    virtual bool preUpdate() ;

    /*! @brief  Apply changes to hardware
     *
     * Called after carrierChange() to actively apply the changed values to the hardware
     * @return false if cannot accept the carrier settings
     */
    virtual bool updateHardware() ;

    /*! @brief  Have just applied changes to hardware
     *
     * Called just after calling the updateHardware() method. Allows carrier to re-enable anything previously
     * disabled
     * @return false if cannot accept the carrier settings
     */
    virtual bool postUpdate() ;

    /*! @brief  All changes are complete
     *
     * Called after postUpdate() to indicate that all changes have been completed
     */
    virtual void changeComplete() ;


    /*! @brief  Get failure reason
     *
     *  If a method fails, then this method will return a
     *  string describing the reason for failure
     * @return string containing reason for failure, or empty string if no fail
     */
    virtual std::string failReason(void) ;

    /**
     * Show method required by Loggable
     */
    virtual void show() ;

    /**
     * Dump object contents to stream
     * @param os	Output stream
     */
    virtual void show(std::ostream& os) ;

    /**
     * Allow setting a fail reason from derived classes
     */
    virtual void setFailReason(std::string reason);

    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~CommonCarrierModelListWorker() ;


private:

    /**
     * Maximum number of carriers supported
     */
    unsigned mMaxCarriers ;

    /**
     * Reason for failure
     */
    std::shared_ptr<ICarrierFail> mFailureReason ;

    /**
     * List of carrier hardware objects
     */
    std::shared_ptr<ICarrierHardwareList> mCarrierList ;
};


}

#endif /* _ACE_AXIS_COMMONCARRIERMODELLISTWORKER_H_ */
