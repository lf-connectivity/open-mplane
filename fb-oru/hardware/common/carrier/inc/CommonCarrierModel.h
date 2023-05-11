#ifndef _ACE_AXIS_COMMONCARRIERMODEL_H_
#define _ACE_AXIS_COMMONCARRIERMODEL_H_

#include <vector>
#include <string>
#include "ICarrierModel.h"
#include "ICarrierFail.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierModel.h
 * \brief     Defines an interface to data for HW carriers
 *
 *
 * \details   Defines an interface to data for the hardware implementation of the carriers.
 *
 */

namespace Mplane
{


/*! @brief  Carrier Model interface
 *
 *  This class manages the application of carrier changes to the actual hardware the implements the carrier
 *  functions. The carrier model is intended to be implemented as common generic code that instantiates
 *  implementation-specific workers to interface to the real hardware (i.e. uses the "Template Method" pattern)
 *
 */
class CommonCarrierModel : public ICarrierModel
{
public:

	explicit CommonCarrierModel(unsigned maxCarriers);

    /*! @brief  Add a worker
     *
     *  Add another carrier model worker to the list
     */
    virtual void addWorker(std::shared_ptr<ICarrierModelWorker> worker) ;

    /*! @brief  Add a list worker
     *
     *  The special case of ICarrierModelWorker that manages an ICarrierHardwareList needs to
     *  have all of it's methods called before any other ICarrierModelWorker. This method
     *  ensures the "list worker" is always called first.
     */
	virtual void addListWorker(std::shared_ptr<ICarrierModelWorker> worker) ;

    /**
     * Method used to add a carrier reference to an underlying carrier list (expected to
     * be an ICarrierHardwareList but could be anything)
     *
     * @param carrier a reference to a carrier object that implements the ICarrier interface.
     * @return true if added successfully, otherwise false, eg invalid index.
     */
    virtual bool addCarrier( const ICarrier& carrier ) ;

    /*! @brief  Initialise
     *
     *  Initialise all workers
     */
    virtual bool initialise(void) ;

    /*! @brief  Validate the carrier change
     *
     *  Ensure all workers are happy with the proposed carrier change
     * @return false if any worker cannot accept the carrier settings
     */
    virtual bool validateChange(const ICarrier& carrier) ;

    /*! @brief  Carrier change
     *
     *  Pass in the carrier settings for the newly changed carrier to all the workers.
     * @return false if any worker cannot accept the carrier settings
     */
    virtual bool carrierChange(const ICarrier& carrier) ;

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

    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~CommonCarrierModel() ;

    /**
     * If supported, returns the smart pointer to an ICarrierHardwareIeq instance. Otherwise returns a null pointer
     */
    virtual std::shared_ptr<ICarrierHardwareIeq> getCarrierHardwareIeq() const override ;


private:

    /**
     * Maximum number of carriers supported
     */
    unsigned mMaxCarriers ;

    /**
     * Failure reason
     */
    std::shared_ptr<ICarrierFail> mFailureReason ;

    /**
     * Group all the workers into a vector
     */
    std::vector< std::shared_ptr<ICarrierModelWorker> > mWorkers ;
};


}
#endif /* _ACE_AXIS_COMMONCARRIERMODEL_H_ */
