#ifndef _ACE_AXIS_ICARRIERMODEL_H_
#define _ACE_AXIS_ICARRIERMODEL_H_

#include <string>
#include <memory>

#include "ICarrierHardwareIeq.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierModel.h
 * \brief     Defines an interface to data for HW carriers
 *
 *
 * \details   Defines an interface to data for the hardware implementation of the carriers.
 *
 */

namespace Mplane
{

class ICarrier ;

/*! @brief  Carrier Model Worker interface
 *
 *  This class contains the information and methods for performing the carrier model actions
 *  on particular areas of the hardware representation of the carriers. Each carrier model worker
 *  is intended to model that area of the hardware as well as interact with an ICarrierHardwareList
 *
 *  For example, and Etna carrier model worker for the FPGA chain will need to model the fpga chains and
 *  fibre iq such that new carriers can be scheduled on to the hardware.
 *
 *  As mentioned above, each worker is intended to interact with an ICarrierHardwareList. This allows
 *  the worker to (a) access the ICarrierHardware for a particular carrier (in order to set up the real
 *  hardware for that carrier) and (b) to be able to get a summary of the settings for all enabled carriers
 *  on antenna in order to (for example) correctly set the weighting factor etc.
 *
 */
class ICarrierModelWorker {
public:

    /**
     *
     */
    ICarrierModelWorker(unsigned maxCarriers = 0){};

    /*! @brief  Initialise
     *
     *  Initialise this worker
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool initialise(void) = 0 ;

    /**
     * Method used to add a carrier reference to an underlying carrier list (expected to
     * be an ICarrierHardwareList but could be anything)
     *
     * @param carrier a reference to a carrier object that implements the ICarrier interface.
     * @param carrier new carrier reference
     * @return true if added successfully, otherwise false, eg invalid index.
     */
    virtual bool addCarrier( const ICarrier& carrier ) = 0 ;

    /*! @brief  Validate the carrier change
     *
     *  Ensure this worker is happy with the proposed carrier change
     * @param carrier new carrier reference
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool validateChange(const ICarrier& carrier) = 0 ;

    /*! @brief  Carrier change
     *
     *  Pass in the carrier settings for the newly changed carrier.
     * @param carrier new carrier reference
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool carrierChange(const ICarrier& carrier) = 0 ;

    /*! @brief  About to apply changes to hardware
     *
     * Called just prior to calling the updateHardware() method. Allows carrier to disable anything
     * that might affect the TX while changing setting (for example)
     * @return false if cannot accept the carrier settings
     */
    virtual bool preUpdate() = 0 ;

    /*! @brief  Apply changes to hardware
     *
     * Called after carrierChange() to actively apply the changed values to the hardware
     * @return false if cannot accept the carrier settings
     */
    virtual bool updateHardware() = 0 ;

    /*! @brief  Have just applied changes to hardware
     *
     * Called just after calling the updateHardware() method. Allows carrier to re-enable anything previously
     * disabled
     * @return false if cannot accept the carrier settings
     */
    virtual bool postUpdate() = 0 ;

    /*! @brief  All changes are complete
     *
     * Called after postUpdate() to indicate that all changes have been completed
     */
    virtual void changeComplete() = 0 ;

    /*! @brief  Get failure reason
     *
     *  If a method fails, then this method will return a
     *  string describing the reason for failure
     * @return string containing reason for failure, or empty string if no fail
     */
    virtual std::string failReason(void) = 0 ;

    /**
     * Show method required by Loggable
     */
    virtual void show() =0 ;

    /**
     * Dump object contents to stream
     * @param os	Output stream
     */
    virtual void show(std::ostream& os) =0 ;

    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~ICarrierModelWorker()
    {
    }

};



/*! @brief  Carrier Model interface
 *
 *  The carrier model collects together 1 or more "workers" to which each of the actions are passed. It is these
 *  "workers" that perform the actual actions. The actions are called by the carrier server as carriers are added
 *  or removed.
 *
 *  Most of the carrier model functionality can be generic and performed in a common base class. A hardware-specific
 *  derived class will then wrap up the creation of the specific workers and provide a common interface to the carrier
 *  server so that nothing outside this class needs to know the hardware-specific details.
 *
 */
class ICarrierModel
{
public:

    /*! @brief  Create the singleton instance
     *
     *  Method used to obtain a reference to the single instance of this object within the system.
     *
     *  @param maxCarriers	Maximum number of carriers supported
     *  @return the singleton instance
     */
    static std::shared_ptr<ICarrierModel> createInstance(unsigned maxCarriers);

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of this object within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<ICarrierModel> getInstance();

    /*! @brief  Add a worker
     *
     *  Add another carrier model worker to the list
     */
	virtual void addWorker(std::shared_ptr<ICarrierModelWorker> worker) = 0 ;

    /*! @brief  Add a list worker
     *
     *  The special case of ICarrierModelWorker that manages an ICarrierHardwareList needs to
     *  have all of it's methods called before any other ICarrierModelWorker. This method
     *  ensures the "list worker" is always called first.
     */
	virtual void addListWorker(std::shared_ptr<ICarrierModelWorker> worker) = 0 ;

    /*! @brief  Initialise
     *
     *  Initialise all workers
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool initialise(void) = 0 ;

    /**
     * Method used to add a carrier reference to an underlying carrier list (expected to
     * be an ICarrierHardwareList but could be anything)
     *
     * @param carrier a reference to a carrier object that implements the ICarrier interface.
     * @return true if added successfully, otherwise false, eg invalid index.
     */
    virtual bool addCarrier( const ICarrier& carrier ) = 0 ;

    /*! @brief  Validate the carrier change
     *
     *  Ensure all workers are happy with the proposed carrier change
     * @param carrier new carrier reference
     * @return false if any worker cannot accept the carrier settings
     */
    virtual bool validateChange(const ICarrier& carrier) = 0 ;

    /*! @brief  Carrier change
     *
     *  Pass in the carrier settings for the newly changed carrier to all the workers.
     * @param carrier new carrier reference
     * @return false if any worker cannot accept the carrier settings
     */
    virtual bool carrierChange(const ICarrier& carrier) = 0 ;

    /*! @brief  Get failure reason
     *
     *  If a method fails, then this method will return a
     *  string describing the reason for failure
     * @return string containing reason for failure, or empty string if no fail
     */
    virtual std::string failReason(void) = 0 ;

    /**
     * Show method required by Loggable
     */
    virtual void show() =0 ;

    /**
     * Dump object contents to stream
     * @param os	Output stream
     */
    virtual void show(std::ostream& os) =0 ;

    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~ICarrierModel(){} ;

    /**
     * If supported, returns the smart pointer to an ICarrierHardwareIeq instance. Otherwise returns a null pointer
     */
    virtual std::shared_ptr<ICarrierHardwareIeq> getCarrierHardwareIeq() const =0 ;

protected:

    /**
     * Constructor (set default number of carriers to 0 to allow construction of empty std::vector)
     */
    ICarrierModel(unsigned maxCarriers = 0){};
};


}


#endif /* _ACE_AXIS_ICARRIERMODEL_H_ */
