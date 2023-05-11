#ifndef _MPLANE_ICARRIERSERVER_H_
#define _MPLANE_ICARRIERSERVER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierServer.h
 * \brief     Defines an interface to the services that manage carrier control
 *
 *
 * \details   Defines an interface to the services that manage carrier control
 *
 */

#include <memory>

#include "Power.h"

namespace Mplane
{

/**
 * TX event data class - passed to ICarrierServer observers so that they can determine which port changed
 * on a particular port.
 *
 * The subject will be defined something like:
 *
 *    CarrierServer : public Subject<ITxOn, const ITxEventData&> { ... };
 *
 * Then the observer will be defined as:
 *
 *    AnObserver : public Observer<ITxOn, const ITxEventData&> {
 *
 *    ...
 *
 *    void update(ITxOn& subject, const ITxEventData& txOnOff) ;
 *
 *    }
 */
class ITxEventData {
public:
	ITxEventData() {}
	virtual ~ITxEventData() {}

	/**
	 * Returns the 0-based port index relating to this event
	 */
	virtual unsigned getPort() const =0 ;
};

/**
 * TXON event class - used to notify ICarrierServer observers that at least one carrier has been enabled
 * on a particular port
 */
class ITxOn {
};

/**
 * TXOFF event class - used to notify ICarrierServer observers that all carriers have been disabled
 * on a particular port
 */
class ITxOff {
};

/**
 * TXPOWER event class - used to notify ICarrierServer observers that the TX power has changed
 * on a particular port
 */
class ITxPower {
};

/**
 * TXCHANGE event class - used to notify ICarrierServer observers that a carrier change has occurred
 * on a particular TX port. There must be at least 1 carrier still enabled on the port, and this event is
 * not generated if a TXON event happens at the same time.
 */
class ITxChange {
};



class ICarrier;
class ICarrierSetter;
class ICarrierControl;
class ICarrierServerObserver;

/*! @brief  Carrier Server
 *
 * The purpose of the ICarrierServer class is to provide a generic
 * interface to the carrier configuration capabilities of the radio
 * hardware. Its implementation can collate all the physical characteristics
 * of the hardware in relation to the carrier data allowing it to configure
 * digital up and down converters (NCOs), synthesisers, CFR etc, using the
 * appropriate to the carrier air interface type.
 *
 * In order to ensure the integrity of the carrier configuration coming down from
 * the higher level application software, only one control entity will be allowed
 * to create and configure carriers through the carrier server interface. This
 * controlling entity must implement the ICarrierControl class in order to access
 * the protected setters of the interface.
 *
 * Once one or more carriers are configured other systems can access the carrier
 * data, in order to read carrier related data such as reference frequency
 * or power information.
 *
 * In order to ensure the validity of the carrier data, in relation to the
 * configuration supplied by the controlling entity, the carrier server
 * provides an observer notification mechanism to allow objects to informed
 * of changes. These objects will be called in the context of the controlling
 * carrier server.
 *
 * The details of the implementation of the carrier server are left to the design
 * of a specific radio variant. The common radio implementation can be used as a
 * base class for the carrier server. It will maintain a simple list of actual
 * and requested carrier data.
 *
 * The Carrier Server implements the singleton pattern so that only one carrier
 * server can exist with the system.
 */
class ICarrierServer
{
public:

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the carrier
     *  server within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<ICarrierServer> getInstance(void);

    /**
     * This method is called to register an object that implements the
     * ICarrierServerObserver in order to receive synchronous notification of
     * carrier changes.
     * @param observer
     * @return true if registration OK, otherwise false.
     */
    virtual bool registerObserver(ICarrierServerObserver &observer ) = 0;

    /**
      * This method is called to unregister an object from the notification list.
      * @param observer
      * @return true if unregistered OK, otherwise false.
      */
     virtual bool unregisterObserver(ICarrierServerObserver &observer ) = 0 ;

    /*! @brief  Get a specific carrier
     *
     *  Method used to get a reference to the carrier information related
     *  to a specific carrier number.
     *
     *  @param  carrierIndex   the carrier number to return
     *
     *  @return the carrier instance, or 0 if the carrier is unknown
     */
    virtual const ICarrier& getCarrier(unsigned carrierIndex) const = 0;


    /*! @brief  Get the number of supported carriers
     *
     *  Method to obtain the Maximum Number of carriers supported. This varies
     *  with both hardware type, board frequency and air interface standard
     *  (CDMA, UMTS or LTE).
     *
     *  @return the Maximum number of carriers the hardware Supports
     */
    virtual const unsigned getMaxCarriers(void) const = 0;

    /** @brief Get maximum transmit carrier paths
     *
     * Method used to return the maximum number of transmit carrier paths supported
     * by this instance of the carrier server.
     *
     * @return max transmit carrier paths
     */
    virtual const unsigned getMaxTxPaths(void) const = 0;

    /** @brief Get maximum receive carrier paths
     *
     * Method used to return the maximum number of receive carrier paths supported
     * by this instance of the carrier server.
     *
     * @return max receive carrier paths
     */
    virtual const unsigned getMaxRxPaths(void) const = 0;

    /*! @brief  Get the maximum number of transmit carriers per port
     *
     *  Method to obtain the maximum number of transmit carriers supported
     *  by each port
     *
     *  @return the maximum number of carriers per tx port
     */
    virtual const unsigned getMaxTxCarriersPerPort(void) const = 0;

    /*! @brief  Get the maximum number of receive carriers per port
     *
     *  Method to obtain the maximum number of receive carriers supported
     *  by each port
     *
     *  @return the maximum number of carriers per rx port
     */
    virtual const unsigned getMaxRxCarriersPerPort(void) const = 0;


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
    virtual ICarrierSetter& getCarrierSetter(unsigned carrierIndex) = 0;

    /**
     * This method is called by the CarrierControl implementation in order to attempt
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
    virtual bool setCarrier( ICarrierSetter &carrier ) = 0;

    /*! @brief  Validate the carrier change
     *
     * Ensure the proposed carrier change is valid
     * @param carrier new carrier reference
     * @return true on success; false on failure (use getSetCarrierFailureStr() method to get reason string)
     */
    virtual bool validateChange(const ICarrierSetter& carrier) = 0 ;

    /**
     * This method can be used to get the index of the last carrier data to be modified.
     *
     * This method will be useful in the ICarrierServerObserver to determine
     * which carrier data has changed.
     *
     * @return the carrier index of the last modified carrier
     */
    virtual const unsigned lastCarrierIndexModified() const = 0;

    /**
     * Method used to retrieve an error string relating to the last setCarrier() method call.
     * @return
     */
    virtual const std::string getSetCarrierFailureStr() = 0;

    /**
     * Show method required by Loggable
     */
    virtual void show() =0 ;

    /**
     * Dump object contents to stream
     * @param os	Output stream
     */
    virtual void show(std::ostream& os) =0 ;

    /**
     * Gets the combined TX power of all active carriers on this TX port
     * @param path zero based Tx path selector
     * @return combined TX power
     */
    virtual Power getTxPower(unsigned path) const =0 ;

    /**
       * Gets the power of the lowest powered carrier on this TX port
       * @param path zero based Tx path selector
       * @return power
       */
     virtual Power getLowestCarrierPower(unsigned path) const = 0;

    /*! @brief Destructor
     *
     */
    virtual ~ICarrierServer() {}


    /**
     * Set the calibration mode. In calibration mode certain automatic actions are disabled to allow for RX/TX calibration
     */
    virtual void setCalibrationMode(bool calibrationMode) =0 ;

    /**
     * Get the current calibration mode setting
     */
    virtual bool isCalibrationMode() const =0 ;

    /**
     * Shutdown any carriers associated with this TX path.
     * @param path zero based Tx path selector
     */
    virtual void shutdownPath(unsigned path) =0 ;

    /**
     * Gets the Tx active path for all carriers
     * @param path zero based Tx path selector
     * @return true if path Tx has active
     */
    virtual bool isTxActivePath(unsigned path) =0;

    /*! @brief  Un-configure specific carrier
     *
     *  Clears out all of the carrier's settings ensuring it is DISABLED with no TX or RX containers
     *
     *  @param  carrierIndex   the carrier number to return
     *
     *  @return true on success
     */
    virtual bool unconfigCarrier(unsigned carrierIndex) = 0;



};

/*! @brief  Carrier control interface
 *
 *  In order to access the the CarrierServer ICarrierSetter interface, any
 *  object that needs to act as a carrier controller must implement this
 *  ICarrierControl interface.
 *
 *  A reference to the interface implementation is passed into the CarrierServer's
 *  getCarrierSetter() method, the the getIndex() method is used to select
 *  the ICarrierSetter instance.
 */
class ICarrierControl
{
public:
    /**
     * This method must be implemented by any object that needs to perform
     * carrier control. A reference to the implementer is passed to the
     * carrier server implementation in order to authenticate it as a
     * carrier controller.
     *
     * The carrier control implementer must implement the getIndex method
     * to return a valid index, in order to use the CarrierServer getCarrierSeter()
     * method.
     *
     * @return a valid zero-based carrier index.
     */
    virtual const unsigned getIndex() const = 0;

protected:

    /*! @brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    ICarrierControl(void) { };

    /**
     * @brief Default destructor
     */
    virtual ~ICarrierControl() { };

};


/**
 * This class defines an observer interface that must be implemented by objects
 * that need to process carrier assignment data with a synchronous notification
 * within the context of the carrier service.
 *
 * Any object implementing this interface must register themselves with the
 * ICarrierServer using the registerObserver(ICarrierServerObserver &observer )
 * function in order to receive any notification.
 *
 */
class ICarrierServerObserver
{
public:
    /**
     * This observer notify() method is called by carrier service for all
     * registered observers.
     * @param carriertxData a reference to the transmit frequency and carrier data
     * @return true if data successfully processed, false for any failure condition
     */
    virtual bool notify( Mplane::ICarrierServer const &carrierServer ) = 0;

    /**
     * Method used to return the name of the registered observer object for
     * debug purposes.
     * @return
     */
    virtual char const * const getObjName() = 0;

    virtual ~ICarrierServerObserver() {}
};



}



#endif /* _MPLANE_ICARRIERSERVER_H_ */
