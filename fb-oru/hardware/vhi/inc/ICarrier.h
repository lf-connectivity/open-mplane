#ifndef _ACE_AXIS_ICARRIER_H_
#define _ACE_AXIS_ICARRIER_H_

#include <iostream>
#include <string>
#include <set>

#include "Frequency.h"
#include "FrequencyOffset.h"
#include "Power.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrier.h
 * \brief     Defines an interface to data for a single carrier
 *
 *
 * \details   Defines an interface to data for a single carrier
 *
 */

namespace Mplane
{


/*! @brief  Carrier interface
 *
 *  This class contains the carrier information and methods to retrieve
 *  all data related to a particular instance of a carrier.
 *
 *  It is a pure interface. All carrier data is stored in the radio specific
 *  implementation of this interface.
 *
 *  When the carrier is created it is assigned a unique carrier index. The carrier server
 *  that implements the CarrierServer interface is responsible for maintaining the
 *  supported list of Carrier objects.
 *
 *  The Carrier interface can also be used retrieve the transmit and receive
 *  path data associated with this carrier.
 *
 */
class ICarrier
{
public:

    /*! @brief  The carriers state
     *
     *  The current state of the carrier
     */
    enum State
    {
        STATE_DISABLE = 0,
        STATE_ENABLE,
        STATE_OTHER
    };

    /**
     * Convert state to a string
     * @param type
     * @return string representation of state
     */
    static std::string stateToStr(State state) ;

    /**
     * Convert state string into a state
     * @param stateStr
     * @return state
     */
    static State strToState(const std::string& stateStr) ;

    /**
     * Get the set of all possible states
     */
    static std::set<std::string> getAllStates() ;


    /*! @brief  Carrier signal type
     *
     *  The signal type of the carrier
     */
    enum Signals
    {
        SIGTYPE_NONE = 0,
        SIGTYPE_TX,
        SIGTYPE_CW,
        SIGTYPE_OTHER
    };

    /**
     * Convert signals to a string
     * @param type
     * @return string representation of signals
     */
    static std::string signalsToStr(Signals signals) ;

    /**
     * Convert signals string into a signals
     * @param signalsStr
     * @return signals
     */
    static Signals strToSignals(const std::string& signalsStr) ;

    /**
     * Get the set of all possible signals
     */
    static std::set<std::string> getAllSignals() ;


    /*! @brief  Carrier type
     *
     *  The type of the carrier
     *
     *  NOTE: These values are used to index lookup arrays, so do *not* change the enumeration value
     *  NOTE2: Do NOT confuse this enum with the FPGA channel BW encodings. These types are completely separate,
     *  the only reason for the encoding integer is to ensure consistent array/vector lookup
     */
    enum Type
    {
        CARRTYPE_NONE		= 0,
        CARRTYPE_LTE1_4		= 1,
        CARRTYPE_LTE3		= 2,
        CARRTYPE_LTE5		= 3,
        CARRTYPE_LTE10		= 4,
        CARRTYPE_LTE15		= 5,
        CARRTYPE_LTE20		= 6,
        CARRTYPE_WCDMA		= 7,

        // PIM settings
        CARRTYPE_PIM1_4		= 8,
        CARRTYPE_PIM3		= 9,
        CARRTYPE_PIM5		= 10,
        CARRTYPE_PIM10		= 11,
        CARRTYPE_PIM15		= 12,
        CARRTYPE_PIM20		= 13,

        // Wideband carrier types
        CARRTYPE_IBW153_6	= 14,
        CARRTYPE_IBW122_88	= 15,

		// 5G
		CARRTYPE_5GNR5      = 16,
		CARRTYPE_5GNR10     = 17,
		CARRTYPE_5GNR15     = 18,
		CARRTYPE_5GNR20     = 19,
		CARRTYPE_5GNR25     = 20,
		CARRTYPE_5GNR30     = 21,
		CARRTYPE_5GNR40     = 22,
		CARRTYPE_5GNR50     = 23,
		CARRTYPE_5GNR60     = 24,
		CARRTYPE_5GNR70     = 25,
		CARRTYPE_5GNR80     = 26,
		CARRTYPE_5GNR90     = 27,
		CARRTYPE_5GNR100    = 28,

		// 5G NB-IoT
		CARRTYPE_NBIOT		= 29,

        CARRYTPE_MAX	= CARRTYPE_NBIOT,
    };

    /**
     * Convert type to a string
     * @param type
     * @return string representation of type
     */
    static std::string typeToStr(Type type) ;

    /**
     * Convert type string into a type
     * @param typeStr
     * @return type
     */
    static Type strToType(const std::string& typeStr) ;

    /*! @brief  Uplink/Downlink cyclic prefix length
         *
         *  The type of the ul/dl cyclic prefix length
         *
         *  NOTE: These values are used to index lookup arrays, so do *not* change the enumeration value
         */
	enum CyclicPrefixLenType {
		PREFIX_LENGTH_NORMAL    = 0,
		PREFIX_LENGTH_EXTENDED	= 1,
		PREFIX_NONE
	};

    /**
     * Convert prefix length into a string
     * @param prefixLen
     * @return string representation of prefix length
     */
    static std::string prefixLenToStr(ICarrier::CyclicPrefixLenType prefixLen);

    /**
     * Convert prefix length string into a prefix length
     * @param PrefixLenStr
     * @return CyclicPrefixLenType
     */
    static CyclicPrefixLenType strToPrefixLen(const std::string& PrefixLenStr) ;

    // Subcarrer spacing
    enum ScsType {
    	SCS_NONE,
		SCS_1kHz25,
		SCS_3kHz75,
		SCS_5kHz,
		SCS_7kHz5,
		SCS_15kHz,
		SCS_30kHz,
		SCS_60kHz,
		SCS_120kHz,
		SCS_240kHz,
    };

    static std::string scsToStr(ScsType scs) ;
    static ScsType strToScs(const std::string& str) ;


    enum FFTsizeType {
    	FFT_NONE,
		FFT_128,
		FFT_256,
		FFT_512,
		FFT_1024,
		FFT_1536,
		FFT_2048,
		FFT_4096,
    };

    static std::string fftsizeToStr(FFTsizeType fftsize) ;
    static FFTsizeType strToFftsize(const std::string& str) ;

    enum ModeType {
    	MODE_LTE,
		MODE_5GNR,
    };

    static std::string modeToStr(ModeType mode) ;
    static ModeType strToMode(const std::string& str) ;

    /**
     * Get the set of all possible types
     */
    static std::set<std::string> getAllTypes() ;

    /**
     * Get just the set of RRH types
     */
    static std::set<std::string> getRrhTypes() ;

    /**
     * Get just the set of PIM types (i.e. all RRH types + PIM-specific)
     */
    static std::set<std::string> getPimTypes() ;





    /*! @brief  Get tx path count
     *
     *  Method used to retrieve the maximum possible number of transmit carrier
     *  paths available.
     *
     *  @return number of transmit carrier paths.
     */
    virtual const unsigned getNumberTxPaths(void) const = 0;

    /*! @brief  Get rx path count
     *
     *  Method used to retrieve the maximum possible number of receive carrier
     *  paths available.
     *
     *  @return number of transmit carrier paths.
     */
    virtual const unsigned getNumberRxPaths(void) const = 0;

    /*! @brief  Get the carrier number
     *
     *  Method used to return the carrier number associated with this carrier
     *  object.
     *
     *  @return carrier number
     */
    virtual const unsigned getIndex(void) const = 0;

    /*! @brief  Get the carrier state
     *
     *  Method used to return the current state of this carrier object.
     *
     *  @return carrier state
     */
    virtual const ICarrier::State getState(void) const = 0;

    /*! @brief  Get the carrier signal type
     *
     *  Method used to return the signal type of this carrier object.
     *
     *  @return carrier signal is either normal or test.
     */
    virtual const ICarrier::Signals getSigType(void) const = 0;

    /*! @brief  Get the carrier type
     *
     *  Method used to return the carrier type of this carrier object.
     *
     *  @return carrier type i.e WCDMA, LTE5, LTE10 etc.
     */
    virtual const ICarrier::Type getType(void) const = 0;

    /**
     * Method to get the carrier transmit frequency in kHz. This value will be derived either
     * from the value set via setTxFrequency() or the offset set via setTxFrequencyOffset()
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return transmit frequency in kHz
     */
    virtual const Frequency getTxFrequency() const = 0;

    /**
     * Method to get the carrier receive frequency in kHz. This value will be derived either
     * from the value set via setRxFrequency() or the offset set via setRxFrequencyOffset()
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return receive frequency in kHz
     */
    virtual const Frequency getRxFrequency() const = 0;

    /**
     * Method to get the carrier transmit frequency offset in kHz
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return transmit frequency in kHz
     */
    virtual const FrequencyOffset getTxFrequencyOffset() const = 0;

    /**
     * Method to get the carrier receive frequency offset in kHz
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return receive frequency in kHz
     */
    virtual const FrequencyOffset getRxFrequencyOffset() const = 0;

    /**
     * Is the TX frequency offset set to be used?
     */
    virtual bool isTxFreqOffsetSet() const =0 ;

    /**
     * Is the RX frequency offset set to be used?
     */
    virtual bool isRxFreqOffsetSet() const =0 ;

    /**
     * Method to get the carrier transmit frequency in kHz. This method returns the value set
     * via setTxFrequency()
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return transmit frequency in kHz
     */
    virtual const Frequency getTxFrequencySetting() const = 0;

    /**
     * Method to get the carrier receive frequency in kHz. This method returns the value set
     * via setRxFrequency()
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return receive frequency in kHz
     */
    virtual const Frequency getRxFrequencySetting() const = 0;


    /**
     * @brief Get the carrier power setpoint dBm
     *
     * This method is used to return the carrier power setting in units
     * of dBm.
     *
     * @return carrier power dBm.
     */
    virtual const Power getTxPower() const = 0;

    /**
     * @brief Get the container number for a given Tx path
     *
     * This method is used to get the transmit container associated with
     * this carrier transmit path. The path is a zero based identifier, so
     * 0 is the first TX port, 1 is the second and so on.
     *
     * @param path zero based Tx path selector
     * @return container 0 = path disabled, >0 source data selector for path.
     */
    virtual const unsigned getTxContainer(unsigned path) const = 0;

    /**
     * @brief Get the fibre number for a given Rx path
     *
     * This method is used to get the receive fibre associated with
     * this carrier receive path. The path is a zero based identifier, so
     * 0 is the first RX port, 1 is the second and so on.
     *
     * @param path zero based Rx path selector
     * @return zero based fibre number
     */
    virtual const unsigned getRxFibre(unsigned path) const = 0;

    /**
     * @brief Get the fibre number for a given Tx path
     *
     * This method is used to get the transmit fibre associated with
     * this carrier transmit path. The path is a zero based identifier, so
     * 0 is the first TX port, 1 is the second and so on.
     *
     * @param path zero based Tx path selector
     * @return zero based fibre number
     */
    virtual const unsigned getTxFibre(unsigned path) const = 0;

    /**
     * @brief Get the container number for a given Rx path
     *
     * This method is used to get the receive container associated with
     * this carrier receive path. The path is a zero based identifier, so
     * 0 is the first RX port, 1 is the second and so on.
     *
     * @param path zero based Rx path selector
     * @return container 0 = path disabled, >0 source data selector for path.
     */
    virtual const unsigned getRxContainer(unsigned path) const = 0;

    /**
     * @brief Get the group size for the up link path
     *
     * This method is used to return the up link group size that has been set
     * for this carrier.
     *
     * @return group size value, expected to be between 1 and 8
     */
    virtual const unsigned getGroupSizeUp() const = 0;

    /**
     * @brief Get the group size for the down link path
     *
     * This method is used to return the down link group size that has been set
     * for this carrier.
     *
     * @return group size value, expected to be between 1 and 8
     */
    virtual const unsigned getGroupSizeDown() const = 0;

    /**
     * @brief Get the up link noise
     *
     * Method used to return the up link noise in dBFS.
     *
     * @return Uplink noise in dBFS
     */
    virtual const Power getUplinkNoise() const = 0;

    /**
     * @brief Get the DL scaling
     *
     * Method used to return the DL scaling in dBFS.
     *
     * @return DL scaling factor in dBFS
     */
    virtual const Power getTxScaling() const = 0;


	/**
	 * Is this a CPRI carrier (i.e. requires AxC / group settings) ?
	 *
	 * NOTE: At some point this may well turn into getting an ENUMERATED type
	 */
	virtual bool isCPRI() const =0 ;

    /**
     * @brief True if configured and active
     *
     * Method used to verify to caller that the carrier data has been successfully configured
     * and is valid.
     *
     * @return true if configured
     */
    virtual const bool isConfigured() const = 0;

    /**
     * @brief True if configured and active
     *
     * Method used to verify to caller that the carrier data has been successfully configured
     * and is valid.
     *
     * @return true if configured
     */
    virtual const bool isTxConfigured() const = 0;

    /**
     * @brief True if configured and active
     *
     * Method used to verify to caller that the carrier data has been successfully configured
     * and is valid.
     *
     * @return true if configured
     */
    virtual const bool isRxConfigured() const = 0;

    /**
     * @brief True if this a configured Tx carrier
     *
     * Method used to verify to the caller that this is a transmit carrier (assigned
     * non-zero transmit containers).
     *
     * @return true if transmit carrier that is configured and active
     */
    virtual const bool isTx() const = 0;

    /**
     * @brief True if this a configured Tx carrier
     *
     * Method used to verify to the caller that this is a transmit carrier (assigned
     * non-zero transmit containers) on the specified path
     *
     * @param txpath	0-based antenna path to check TX is assigned on
     * @return true if transmit carrier that is configured and active is on this tx path
     */
    virtual const bool isTx(const unsigned txpath) const = 0;

    /**
     * @brief True if this a configured Rx carrier
     *
     * Method used to verify to the caller that this is a receive carrier (assigned
     * non-zero receive containers).
     *
     * @return true if receive carrier that is configured and active
     */
    virtual const bool isRx() const = 0;

    /**
     * @brief True if this a configured Rx carrier
     *
     * Method used to verify to the caller that this is a receive carrier (assigned
     * non-zero receive containers).
     *
     * @param rxpath	0-based antenna path to check RX is assigned on
     * @return true if receive carrier that is configured and active on this rx path
     */
    virtual const bool isRx(const unsigned rxpath) const = 0;

    /**
     * @brief Get the IF frequency associated with given transmit path
     *
     * Method used to obtain the IF frequency for a given transmit path. This may be
     * port specific or common to all ports and carriers depending on the radio hardware.
     *
     * @param path transmit path
     * @return the transmit path IF frequency on kiloHertz
     */
    virtual const Frequency getTxIfFrequency( unsigned path ) const = 0;

    /**
     * @brief Get the IF frequency associated with given receive path
     *
     * Method used to obtain the IF frequency for a given receive path. This may be
     * port specific or common to all ports and carriers depending on the radio hardware.
     *
     * @param path receive path
     * @return the receive path IF frequency on kiloHertz
     */
    virtual const Frequency getRxIfFrequency( unsigned path ) const = 0;

    /**
     * @brief Applies all changes
     *
     * Method clears all the "changed" flags used in the get*Changed() methods
     */
    virtual const void applyChanges(void) = 0;

    /**
     * @brief See if the container number for a given Tx path has changed
     *
     * @param path zero based Tx path selector
     * @return true if changed
     */
    virtual const bool getTxContainerChanged(unsigned path) const = 0;

    /**
     * @brief See if the container number for a given Rx path has changed
     *
     * @param path zero based Rx path selector
     * @return true if changed
     */
    virtual const bool getRxContainerChanged(unsigned path) const = 0;

    /**
     * @brief See if the fibre number for a given Tx path has changed
     *
     * @param path zero based Tx path selector
     * @return true if changed
     */
    virtual const bool getTxFibreChanged(unsigned path) const = 0;

    /**
     * @brief See if the fibre number for a given Rx path has changed
     *
     * @param path zero based Rx path selector
     * @return true if changed
     */
    virtual const bool getRxFibreChanged(unsigned path) const = 0;

    /**
     * @brief See if the carrier power setpoint power has changed
     *
     * @return true if changed
     */
    virtual const bool getTxPowerChanged(void) const = 0;

    /*! @brief  See if the carrier signal type has changed
     *
     * @return true if changed
     */
    virtual const bool getSigTypeChanged(void) const = 0;

    /*! @brief  See if the carrier type has changed
     *
     * @return true if changed
     */
    virtual const bool getTypeChanged(void) const = 0;

    /**
     * See if the carrier transmit frequency has changed
     *
     * @return true if changed
     */
    virtual const bool getTxFrequencyChanged(void) const = 0;

    /**
     * See if the carrier transmit frequency offset has changed
     *
     * @return true if changed
     */
    virtual const bool getTxFrequencyOffsetChanged(void) const = 0;

    /**
     * See if  carrier receive frequency has changed
     *
     * @return true if changed
     */
    virtual const bool getRxFrequencyChanged(void) const = 0;

    /**
     * See if  carrier receive frequency offset has changed
     *
     * @return true if changed
     */
    virtual const bool getRxFrequencyOffsetChanged(void) const = 0;

    /**
     * @brief See if the up link noise has changed
     *
     * @return true if changed
     */
    virtual const bool getUplinkNoiseChanged(void) const = 0;

    /**
     * @brief See if the DL scaling hasd changed
     *
     * @return true if changed
     */
    virtual const bool getTxScalingChanged() const = 0;

    /**
     * @brief See if the carrier up link data group size has changed
     *
     * @return true if changed
     */
    virtual const bool getGroupSizeUpChanged(void) const = 0;

    /**
     * @brief See if the carrier down link data group size has changed
     *
     * @return true if changed
     */
    virtual const bool getGroupSizeDownChanged(void) const = 0;


    /*! @brief  See the carrier state has changed
     *
     * @return true if changed
     */
    virtual const bool getStateChanged(void) const = 0;

    /*! @brief  Get the loopback state
     *
     * @return true if loopback enabled
     */
    virtual const bool getLoopback(void) const = 0;

    /*! @brief  Has the loopback state changed
     *
     * @return true if loopback changed
     */
    virtual const bool getLoopbackChanged(void) const = 0;

    /**
     * Has this TX path been enabled or disabled
     * @param txpath	Path to check
     * @return true if this TX path has been enabled or disabled
     */
    virtual const bool getTxPathChanged(unsigned txpath) const = 0;

    /**
     * Has this RX path been enabled or disabled
     * @param rxpath	Path to check
     * @return true if this RX path has been enabled or disabled
     */
    virtual const bool getRxPathChanged(unsigned rxpath) const = 0;

    /*! @brief  Get the uplink/downlink configuration
	 *
	 * @return uplink/downlink configuration value, expected between 0 and 6 inclusive
	 */
	virtual const unsigned getUlDlConfig(void) const = 0;

	/*! @brief  Has the uplink/downlink configuration changed
	 *
	 * @return true if uplink/downlink configuration changed
	 */
	virtual const bool getUlDlConfigChanged(void) const = 0;

    /*! @brief  Get the special subframe configuration
	 *
	 * @return special subframe configuration value, expected between 0 and 10 inclusive
	 */
	virtual const unsigned getSpSuConfig(void) const = 0;

	/*! @brief  Has the special subframe configuration changed
	 *
	 * @return true if special subframe configuration changed
	 */
	virtual const bool getSpSuConfigChanged(void) const = 0;

    /*! @brief  Get the uplink cyclix prefix length
	 *
	 * @return special uplink cyclix prefix length (normal/extended)
	 */
	virtual const ICarrier::CyclicPrefixLenType getUlPrefixLen(void) const = 0;

	/*! @brief  Has the uplink cyclix prefix length changed
	 *
	 * @return true if uplink cyclix prefix length changed
	 */
	virtual const bool getUlPrefixLenChanged(void) const = 0;

    /*! @brief  Get the downlink cyclix prefix length
	 *
	 * @return special downlink cyclix prefix length (normal/extended)
	 */
	virtual const ICarrier::CyclicPrefixLenType getDlPrefixLen(void) const = 0;

	/*! @brief  Has the downlink cyclix prefix length changed
	 *
	 * @return true if downlink cyclix prefix length changed
	 */
	virtual const bool getDlPrefixLenChanged(void) const = 0;

	/**
	 * Get the subcarrier spacing for DL
	 */
	virtual ScsType getDlScs() const =0 ;

	/**
	 * Get the FFT size  for DL
	 */
	virtual FFTsizeType getDlFftSize() const =0 ;

	/**
	 * Get the subcarrier spacing for UL
	 */
	virtual ScsType getUlScs() const =0 ;

	/**
	 * Get the FFT size  for UL
	 */
	virtual FFTsizeType getUlFftSize() const =0 ;

	/**
	 * Get the UL extended Antenna-Carrier ID per port
	 */
	virtual unsigned getUlEaxcId(unsigned path) const =0 ;

	/**
	 * Get the DL extended Antenna-Carrier ID per port
	 */
	virtual unsigned getDlEaxcId(unsigned path) const =0 ;

	/**
	 * Get the O-DU MAC
	 */
	virtual uint64_t getUlMacId() const =0 ;

	/**
	 * Get the carrier mode
	 */
	virtual ModeType getMode() const =0 ;

	/**
	 * Get length of UL cyclic prefix (in Ts) for first CP
	 */
	virtual unsigned getUlCpSize() const =0 ;

	/**
	 * Get length of UL cyclic prefix (in Ts) for subsequent CP
	 */
	virtual unsigned getUlCpOtherSize() const =0 ;

	/**
	 * Get length of DL cyclic prefix (in Ts) for first CP
	 */
	virtual unsigned getDlCpSize() const =0 ;

	/**
	 * Get length of DL cyclic prefix (in Ts) for subsequent CP
	 */
	virtual unsigned getDlCpOtherSize() const =0 ;


	/**
	 * Has the subcarrier spacing for DL changed?
	 */
	virtual bool getDlScsChanged() const =0 ;

	/**
	 * Has the FFT size  for DL changed?
	 */
	virtual bool getDlFftSizeChanged() const =0 ;

	/**
	 * Has the subcarrier spacing for UL changed?
	 */
	virtual bool getUlScsChanged() const =0 ;

	/**
	 * Has the FFT size  for UL changed?
	 */
	virtual bool getUlFftSizeChanged() const =0 ;

	/**
	 * Has the UL extended Antenna-Carrier ID per port changed?
	 */
	virtual bool getUlEaxcIdChanged(unsigned path) const =0 ;

	/**
	 * Has the DL extended Antenna-Carrier ID per port changed?
	 */
	virtual bool getDlEaxcIdChanged(unsigned path) const =0 ;

	/**
	 * Has the O-DU MAC changed
	 */
	virtual bool getUlMacIdChanged() const =0 ;

	/**
	 * Has the carrier mode changed?
	 */
	virtual bool getModeChanged() const =0 ;

	/**
	 * Has length of UL cyclic prefix (in Ts) for first CP changed?
	 */
	virtual bool getUlCpSizeChanged() const =0 ;

	/**
	 * Has length of UL cyclic prefix (in Ts) for subsequent CP changed?
	 */
	virtual bool getUlCpOtherSizeChanged() const =0 ;

	/**
	 * Has length of DL cyclic prefix (in Ts) for first CP changed?
	 */
	virtual bool getDlCpSizeChanged() const =0 ;

	/**
	 * Has length of DL cyclic prefix (in Ts) for subsequent CP changed?
	 */
	virtual bool getDlCpOtherSizeChanged() const =0 ;



    /**
     * Has anything changed in the carrier
     * @return true if anything changed
     */
    virtual const bool isChanged(void) const = 0;

    /**
     * @brief Print out contents of carrier to stdout
     * Used for debug only
     */
    virtual void showCarrier(std::ostream& os = std::cout) const = 0 ;

    /**
     * Get the carrier-base RSSI measurement for this RX path
     * @param path		zero based Rx path selector
     * @param error		Set on any error
     * @return Carrier RSSI power
     */
    virtual Power getRssi(unsigned path, std::string& error) const =0 ;

    /**
     * Indicates to carrier that this TX path must be shutdown
     * @param path
     * @return tx shutdown state
     */
    virtual bool getShutdownTx(unsigned path) const =0 ;




    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~ICarrier()
    {
    }

protected:

    /**
     *
     */
    ICarrier(){};

};


class ICarrierSetter : public ICarrier
{

public:

	/**
	 * Unconfigure this carrier (delete all of it's settings)
	 * @return true if ok
	 */
	virtual bool unconfigure() =0 ;

    /**
     * @brief Set carrier settings
     *
     * Given an Mplane::ICarrier object with new settings, this instances copies the settings
     * over.
     *
     * @param carrier ICarrier with new settngs to apply
     * @return false if set fails otherwise true
     */
    virtual bool setCarrier(const ICarrier& carrier) = 0;

    /**
     * @brief Set the state of the carrier.
     *
     * Method, called by the friend CarrierControl object to set the required
     * carrier state for this carrier.
     *
     * @param state
     * @return false if set fails otherwise true
     */
    virtual bool setState(ICarrier::State state) = 0;

    /**
     * @brief Set carrier transmit frequency.
     *
     * Method, called by the friend CarrierControl object to set the required
     * transmit carrier frequency
     *
     * @param frequency in KHz fir this carrier
     * @return false if set fails otherwise true
     */
    virtual bool setTxFrequency(Frequency frequency) = 0;

    /**
     * @brief Set carrier transmit frequency as an offset from the TX LO.
     *
     * Method, called by the friend CarrierControl object to set the required
     * transmit carrier frequency
     *
     * @param frequency in KHz for this carrier
     * @return false if set fails otherwise true
     */
    virtual bool setTxFrequencyOffset(FrequencyOffset frequency) = 0;

    /**
     * @brief Set carrier receive frequency
     *
     * Method, called by the friend CarrierControl object to set the required
     * receive carrier frequency
     *
     * @param frequency in KHz fir this carrier
     * @return false if set fails otherwise true
     */
    virtual bool setRxFrequency(Frequency frequency) = 0;

    /**
     * @brief Set carrier receive frequency as an offset from the RX LO.
     *
     * Method, called by the friend CarrierControl object to set the required
     * transmit carrier frequency
     *
     * @param frequency in KHz for this carrier
     * @return false if set fails otherwise true
     */
    virtual bool setRxFrequencyOffset(FrequencyOffset frequency) = 0;

    /**
     * @brief Set the carrier transmit power setpoint dBm
     *
     * This method is used to set the carrier power setting in units
     * of 0.1 dBm.
     *
     * @param power carrier power 0.1 dBm.
     * @return false if set fails otherwise true
     */
    virtual bool setTxPower(Power power) = 0;

    /*! @brief  Set the carrier signal type
     *
     *  Method used to set the signal type of this carrier object.
     *
     *  @param sigType signal type required for the carrier.
     * @return false if set fails otherwise true
     */
    virtual bool setSigType(ICarrier::Signals sigType) = 0;

    /*! @brief  Set the carrier type
     *
     *  Method used to set the carrier type of this carrier object.
     *
     * @param type ie CDMA, UMTS, LTE5, LTE10 etc.
     * @return false if set fails otherwise true
     */
    virtual bool setType(ICarrier::Type type) = 0;

    /**
     * @brief Set the container number for a Tx path
     *
     * This method is used to set the transmit container associated with
     * this carrier transmit path. The path is a zero based identifier, so
     * 0 is the first TX port, 1 if the second and so on.
     *
     * The container is used to select the data source for the given path. A container
     * value of 0 indicates the path is not enabled for this carrier.
     *
     * @param path zero based Tx path selector
     * @param container 0 = path disabled, >0 source data selector for path.
     * @return false if set fails otherwise true
     */
    virtual bool setTxContainer(unsigned path, unsigned container) = 0;

    /**
     * @brief Set the container number for a Rx path
     *
     * This method is used to set the receive container associated with
     * this carrier receive path. The path is a zero based identifier, so
     * 0 is the first RX port, 1 is the second and so on.
     *
     * The container is used to select the data destination for the given path. A container
     * value of 0 indicates the path is not enabled for this carrier.
     *
     * @param path zero based Rx path selector
     * @param container 0 = path disabled, >0 source data selector for path.
     * @return false if set fails otherwise true
     */
    virtual bool setRxContainer(unsigned path, unsigned container) = 0;

    /**
     * @brief Set the fibre number for a Tx path
     *
     * This method is used to set the transmit fibre associated with
     * this carrier transmit path. The path is a zero based identifier, so
     * 0 is the first TX port, 1 if the second and so on.
     *
     * The fibre is used to select the data source for the given path.
     *
     * @param path zero based Tx path selector
     * @param zero based fibre number
     * @return false if set fails otherwise true
     */
    virtual bool setTxFibre(unsigned path, unsigned fibre) = 0;

    /**
     * @brief Set the fibre number for a Rx path
     *
     * This method is used to set the receive fibre associated with
     * this carrier receive path. The path is a zero based identifier, so
     * 0 is the first RX port, 1 is the second and so on.
     *
     * The fibre is used to select the data destination for the given path.
     *
     * @param path zero based Rx path selector
     * @param zero based fibre number
     * @return false if set fails otherwise true
     */
    virtual bool setRxFibre(unsigned path, unsigned fibre) = 0;

    /**
     * @brief Set the carrier up link data group size
     *
     * This method is used to set the up link data group size associated with
     * this carrier.
     *
     * @param grpSizeUp a valid group size from 1 to N
     * @return bool true is group size valid.
     */
    virtual bool setGroupSizeUp( unsigned grpSizeUp) = 0;

    /**
     * @brief Set the carrier down link data group size
     *
     * This method is used to set the down link data group size associated with
     * this carrier.
     *
     * @param grpSizeDown a valid group size from 1 to N
     * @return bool true is group size valid.
     */
    virtual bool setGroupSizeDown( unsigned grpSizeDown) = 0;

    /**
     * @brief Set the up link noise
     *
     * Method used to set the up link noise in dBFS.
     *
     * @param upLinkNoise up link noise in dBFS
     * @return false if set fails otherwise true
     */
    virtual bool setUplinkNoise(Power upLinkNoisedB) = 0;

    /**
     * @brief Set the DL scaling
     *
     * @param dlScaling DL scaling in dBFS
     * @return false if set fails otherwise true
     */
    virtual bool setTxScaling(Power dlScaling) = 0;

    /*! @brief  Set the loopback state
     * @param loopback new lookback setting
     * @return false if set fails otherwise true
     */
    virtual bool setLoopback(bool loopBack) = 0;

    /*! @brief  Set the uplink downlink configuration
     * @param uldlConfig new uplink downlink configuration setting
     * @return false if set fails otherwise true
     */
    virtual bool setUlDlConfig(unsigned uldlConfig) = 0;

    /*! @brief  Set the special subframe configuration
     * @param spsuConfig new special subframe configuration setting
     * @return false if set fails otherwise true
     */
    virtual bool setSpSuConfig(unsigned spsuConfig) = 0;

    /*! @brief  Set the uplink cyclic prefix length
     * @param ulPrefixLen new uplink cyclic prefix length setting
     * @return false if set fails otherwise true
     */
    virtual bool setUlPrefixLenConfig(ICarrier::CyclicPrefixLenType ulPrefixLen) = 0;

    /*! @brief  Set the downlink cyclic prefix length
     * @param dlPrefixLen new downlink cyclic prefix length setting
     * @return false if set fails otherwise true
     */
    virtual bool setDlPrefixLenConfig(ICarrier::CyclicPrefixLenType dlPrefixLen) = 0;

    /**
     * Indicates to carrier that this TX path must be shutdown
     * @param path
     * @return false if set fails
     */
    virtual bool setShutdownTx(unsigned path) =0 ;


	/**
	 * Set the subcarrier spacing for DL
	 */
	virtual bool setDlScs(ScsType scs) =0 ;

	/**
	 * Set the FFT size  for DL
	 */
	virtual bool setDlFftSize(FFTsizeType fftSize) =0 ;

	/**
	 * Set the subcarrier spacing for UL
	 */
	virtual bool setUlScs(ScsType scs) =0 ;

	/**
	 * Set the FFT size  for UL
	 */
	virtual bool setUlFftSize(FFTsizeType fftSize) =0 ;

	/**
	 * Set the UL extended Antenna-Carrier ID per port
	 */
	virtual bool setUlEaxcId(unsigned path, unsigned eaxcId) =0 ;

	/**
	 * Set the DL extended Antenna-Carrier ID per port
	 */
	virtual bool setDlEaxcId(unsigned path, unsigned eaxcId) =0 ;

	/**
	 * Set the O-DU MAC
	 */
	virtual bool setUlMacId(uint64_t macid) =0 ;

	/**
	 * Set the carrier mode
	 */
	virtual bool setMode(ModeType mode) =0 ;

	/**
	 * Set length of UL cyclic prefix (in Ts) for first CP
	 */
	virtual bool setUlCpSize(unsigned sizeTs) =0 ;

	/**
	 * Set length of UL cyclic prefix (in Ts) for subsequent CP
	 */
	virtual bool setUlCpOtherSize(unsigned sizeTs) =0 ;

	/**
	 * Set length of DL cyclic prefix (in Ts) for first CP
	 */
	virtual bool setDlCpSize(unsigned sizeTs) =0 ;

	/**
	 * Set length of DL cyclic prefix (in Ts) for subsequent CP
	 */
	virtual bool setDlCpOtherSize(unsigned sizeTs) =0 ;


    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~ICarrierSetter()
    {
    }

protected:


    ICarrierSetter(){};



};


}


#endif /* _ACE_AXIS_ICARRIER_H_ */
