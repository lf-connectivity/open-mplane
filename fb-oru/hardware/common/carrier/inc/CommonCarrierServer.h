#ifndef _MPLANE_COMMONCARRIERSERVER_H_
#define _MPLANE_COMMONCARRIERSERVER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierServer.h
 * \brief     Extends the ICarrierServer interface to provide a CommonCarrierServer
 *  base class
 *
 *
 * \details   Extends the ICarrierServer interface to provide a CommonCarrierServer
 *  base class
 *
 */

#include <map>
#include <vector>

#include <memory>
#include "Observer.hpp"
#include "Mutex.h"
#include "Frequency.h"
#include "Power.h"
#include "Loggable.h"

#include "ICarrierServer.h"

namespace Mplane
{

using namespace Mplane;

class ICarrierModel ;
class CarrierFreqMgr ;
class CarrierPowerMgr ;

/*! @brief  Common carrier server
 *
 *  The CommonCarrierServer class provides a base implementation of the ICarrierServer interface.
 *
 *  It provides all the basic data storage functionality required to create objects that implement
 *  the ICarrier and ICarrierSetter interfaces.
 *
 *  It also provides a carrier server data change listener implementation that can therefore be
 *  common to all radio specific implementations.
 *
 *  The implementation does not implement the setCarrier method, this must be implemented by the
 *  radio specific carrier server objects that extend this base class.
 *
 */
class CommonCarrierServer : public virtual ICarrierServer,
	public Loggable,
	public Subject<ITxOn, const ITxEventData&>,
	public Subject<ITxOff, const ITxEventData&>,
	public Subject<ITxPower, const ITxEventData&>,
	public Subject<ITxChange, const ITxEventData&>
{
public:

    /**
      * This method is called to register an object that implements the
      * ICarrierServerObserver in order to receive synchronous notification of
      * carrier changes.
      * @param observer
      * @return true if registration OK, otherwise false.
      */
     virtual bool registerObserver(ICarrierServerObserver &observer );

     /**
       * This method is called to unregister an object from the notification list.
       * @param observer
       * @return true if unregistered OK, otherwise false.
       */
      virtual bool unregisterObserver(ICarrierServerObserver &observer );


     /*! @brief  Get a specific carrier
      *
      *  Method used to get a reference to the carrier information related
      *  to a specific carrier number.
      *
      *  @param  carrierIndex   the carrier number to return
      *
      *  @return the carrier instance, or 0 if the carrier is unknown
      */
     virtual const ICarrier& getCarrier(unsigned carrierIndex) const;


     /*! @brief  Get the number of supported carriers
      *
      *  Method to obtain the Maximum Number of carriers supported. This varies
      *  with both hardware type, board frequency and air interface standard
      *  (CDMA, UMTS or LTE).
      *
      *  @return the Maximum number of carriers the hardware Supports
      */
     virtual const unsigned getMaxCarriers(void) const;

     /** @brief Get maximum transmit carrier paths
      *
      * Method used to return the maximum number of transmit carrier paths supported
      * by this instance of the carrier server.
      *
      * @return max tranmit carrier paths
      */
     virtual const unsigned getMaxTxPaths(void) const;

     /** @brief Get maximum receive carrier paths
      *
      * Method used to return the maximum number of receive carrier paths supported
      * by this instance of the carrier server.
      *
      * @return max receive carrier paths
      */
     virtual const unsigned getMaxRxPaths(void) const;

     /*! @brief  Get the maximum number of transmit carriers per port
      *
      *  Method to obtain the maximum number of transmit carriers supported
      *  by each port
      *
      *  @return the maximum number of carriers per tx port
      */
     virtual const unsigned getMaxTxCarriersPerPort(void) const;

     /*! @brief  Get the maximum number of receive carriers per port
      *
      *  Method to obtain the maximum number of receive carriers supported
      *  by each port
      *
      *  @return the maximum number of carriers per rx port
      */
     virtual const unsigned getMaxRxCarriersPerPort(void) const;


     /*! @brief  Get a specific carrier
      *
      *  Method used to get a reference to the carrier information related
      *  to a specific carrier number. The carrier number is zero based and
      *  must be less than the CarrierServer.maxCarriers() value.
      *
      *  @param  carrierIndex   the carrier number to return
      *
      *  @return the carrier instance, or 0 if the carrier is unknown
      */
     virtual ICarrierSetter& getCarrierSetter(unsigned carrierIndex) ;

     /**at least one
      * This method is called by the by the CarrierControl implementation in order to attempt
      * to set the carrier data.
      *
      * If the carrier data is valid it is sent within the carrier server and it returns true.
      *
      * If the carrier data is rejected false is returned. On failure the getSetCarrierFailureStr()
      * can be called to retrieve a string that describes the failure condition.
      *
      * @param carrier a reference to the carrier carrier data for a specific carrier index, as provided
      * by the getCarrier() method
      * @return true for valid carrier data otherwise false.
      */
     virtual bool setCarrier( ICarrierSetter &carrier );

     /*! @brief  Validate the carrier change
      *
      * Ensure the proposed carrier change is valid
      * @param carrier new carrier reference
      * @return true on success; false on failure (use getSetCarrierFailureStr() method to get reason string)
      */
     virtual bool validateChange(const ICarrierSetter& carrier) ;

     /**at least one
      * This method can be used to get the index of the last carrier data to be modified.
      *
      * This method will be useful in the ICarrierServerObserver to determine
      * which carrier data has changed.
      *
      * @return the carrier index of the last modified carrier
      */
     virtual const unsigned lastCarrierIndexModified() const;

     /**
      * Method used to retrieve an error string relating to the last setCarrier() method call.
      * @return
      */
     virtual const std::string getSetCarrierFailureStr();

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
      * Gets the combined TX power of all active carriers on this TX port
      * @param path zero based Tx path selector
      * @return combined TX power
      */
     virtual Power getTxPower(unsigned path) const ;

     /**
       * Gets the power of the lowest powered carrier on this TX port
       * @param path zero based Tx path selector
       * @return power
       */
     virtual Power getLowestCarrierPower(unsigned path) const;

     /**
      * Set the calibration mode. In calibration mode certain automatic actions are disabled to allow for RX/TX calibration
      */
     virtual void setCalibrationMode(bool calibrationMode) override ;

     /**
      * Get the current calibration mode setting
      */
     virtual bool isCalibrationMode() const override ;

     /**
      * Shutdown any carriers associated with this TX path. Also generates TXOFF event for the path.
      * @param path zero based Tx path selector
      */
     virtual void shutdownPath(unsigned path) override ;

     /**
      * Gets the Tx active path for all carriers
      * @param path zero based Tx path selector
      * @return true if path Tx has active
      */
     virtual bool isTxActivePath(unsigned path) override ;

     /*! @brief  Un-configure specific carrier
      *
      *  Clears out all of the carrier's settings ensuring it is DISABLED with no TX or RX containers
      *
      *  @param  carrierIndex   the carrier number to return
      *
      *  @return true on success
      */
     virtual bool unconfigCarrier(unsigned carrierIndex) override ;


protected:


    /*! @brief  Constructor
     *
     *  Construct the server, specifying the number of supported carriers
     *
     *  This base constructor will initialise the base constant variables for maximum, carriers,
     *  carrier paths and physical path and size the two carrier lists but it does not create
     *  and add carriers, this must be implemented by the extending class.
     *
     * @note Does not populate the carrier lists with ICarrierSetter or ICarrier objects, this
     * must be done using the CommonCarrierServerr::addCarrierSetter and CommonCarrierServer::addCarrier
     * methods.
     *
     * @param maxCarriers
     * @param maxCarrierPerTxPath
     * @param maxCarriersPerRxPath
     * @param maxTxPaths
     * @param maxRxPaths
     */
    CommonCarrierServer(unsigned maxCarriers, unsigned maxCarrierPerTxPath,
            unsigned maxCarriersPerRxPath, unsigned maxTxPaths, unsigned maxRxPaths);

    /*! @brief  Destructor
     *
     *  Protect the singleton pattern
     */
    virtual ~CommonCarrierServer();

    /**
     * Method used by extending class to store a string that describes the reason for the last setCarrier
     * failure, if any.
     * @param errorMsg
     */
    virtual void setCarrierFailureStr( const std::string& errorMsg );


    /**
     * Method called in the setCarrier() radio specific implementation after the carrier is configured
     * in order to notify carrier server change listeners of the carrier change.
     */
    virtual void callCarrierServerObservers();

    /**
     * This method can be called by the radio specific carrier server implementation in order to add
     * a radio specific extended carrier setter. The ICarrierSetter reference is stored in the m_carrierSetList
     * using its index.
     *
     * @param carrierSetter a reference to a carrier object that implements the ICarrierSetter interface
     * @return true if added successfully otherwise false, eg invalid index.
     */
    virtual bool addCarrierSetter( ICarrierSetter& carrierSetter );

    /**
     * This method can be called by the radio specific carrier server implementation in order to add
     * a radio specific extended carrier. The ICarrier reference is stored in the m_carrierSetList
     * using its index.
     *
     * @param carrier a reference to a carrier object that implements the ICarrier interface.
     * @return true if added successfully, otherwise false, eg invalid index.
     */
    virtual bool addCarrier( ICarrier& carrier );

    /**
     * Used to clear the list of ICarrierSetters created using addCarrierSetter(). Used by derived classes to build a new
     * list
     */
    virtual void clearCarrierSetters() ;

    /**
     * Used to clear the list of ICarriers created using addCarrier(). Used by derived classes to build a new
     * list
     */
    virtual void clearCarriers() ;

    /**
     * Update the state of the TX EVENT list and notify clients if a change is detected
     * @param carrier
     */
    void updateTxOffEvent(const ICarrier& carrier) ;
    void updateTxOnPowerEvent(const ICarrier& carrier, const std::vector<bool>& carrierTxChange) ;

    /**
     * Update any managers (e.g. CarrierFreqMgr, CarrierPowerMgr etc) with the new carrier setting
     * @param carrier
     * @param failReason
     * @return false on error (sets carrier server error string)
     */
    bool updateManagers(const ICarrier& carrier) ;

    /**
     * Create an ICarrierSetter
     * @param index
     * @param maxTxPaths
     * @param maxRxPaths
     * @return
     */
    virtual ICarrierSetter* createCarrierSetter(unsigned index, unsigned maxTxPaths, unsigned maxRxPaths) ;

    /**
     * Create an ICarrier
     * @param index
     * @param maxTxPaths
     * @param maxRxPaths
     * @return
     */
    virtual ICarrier* createCarrier(unsigned index, unsigned maxTxPaths, unsigned maxRxPaths) ;

    /**
     * Calculate whether the carrier changes will activate/deactive each TX
     * @param currentCarrier
     * @param newCarrier
     * @return vector of bools, one per TX indicating whether carrier is changing on that TX
     */
    std::vector<bool> calcCarrierTxChange(const ICarrier* currentCarrier, const ICarrier& newCarrier) ;

protected:
    bool	mCalibrationMode ;
    Frequency mLowestRxFrequency;      //!< The lowest Rx frequency of any carrier in the committed carrier list
    Frequency mLowestTxFrequency;      //!< The lowest Tx frequency of any carrier in the committed carrier list
    bool mWideBand;
    unsigned mLastModifiedIndex;                //!<Holds the index of the last modified carrier

    /*
     * Constants
     */
    const unsigned mMaxCarriers;            //!< The number of carriers supported
    const unsigned mMaxCarriersPerTxPath;   //!< Maximum carriers for each Tx path.
    const unsigned mMaxCarriersPerRxPath;   //!< Maximum carriers for each Rx path.
    const unsigned mMaxTxPaths;             //!< Maximum number of Tx paths supported by the hardware
    const unsigned mMaxRxPaths;             //!< Maximum number of Rx paths supported by the hardware.

    std::string mErrorMsg;                       //!< error message string

    /**
     * The carrier data set by the ICarrierControl implementer.
     */
    std::vector< ICarrierSetter*> mCarrierSetList;
    /**
    * The committed carrier list, ie those  carrier that have been validated and implemented
    * by the setCarrier method.
    */
    std::vector< ICarrier*> mCommittedCarrierList;


    struct CommonCarrierServerObserver
    {
        ICarrierServerObserver *observer;
    };

    std::vector<CommonCarrierServerObserver> mCarrierServerObservers; //!< holds a list of registered carrier server observers

    /**
    * A carrier model to model/change the hardware
    */
    std::shared_ptr<ICarrierModel> mCarrierModel;

    /**
     * Carrier frequencies manager - manages the frequency band usage of carriers on each TX/RX port
     */
    std::shared_ptr<CarrierFreqMgr> mCarrierFreqMgr;

    /**
     * Carrier powers manager - manages the total power of carriers on each TX port
     */
    std::shared_ptr<CarrierPowerMgr> mCarrierPowerMgr;

    /**
     * Mutex to protect carriers from being changed by multiple threads
     */
    Mutex mCarrierMutex ;

    /**
     * Array of bools that contain the current on/off state of each of the TX ports. Used to notify
     * Observers of an ON/OFF change
     */
    std::vector<bool> mTxOn ;

    /**
     * Array of Powers that contain the current total power on each of the TX ports. Used to notify
     * Observers of a TXPOWER change event
     */
    std::vector<Power> mTxPower;

};



}


#endif /* _MPLANE_COMMONCARRIERSERVER_H_ */
