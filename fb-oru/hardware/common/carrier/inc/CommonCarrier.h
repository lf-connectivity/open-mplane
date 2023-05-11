#ifndef _MPLANE_COMMONCARRIER_H_
#define _MPLANE_COMMONCARRIER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrier.h
 * \brief     Extends the ICarrier interface to provide a CarrierData base class
 *
 *
 * \details   Extends the ICarrier interface to provide a CarrierData base class
 *
 */

#include "ICarrier.h"
#include "Frequency.h"
#include "Power.h"
#include "Mutex.h"
#include <vector>

namespace Mplane
{

using namespace Mplane;

class CommonCarrier : public ICarrierSetter
{
public:

    /*! @brief  Constructor
     *
     * Carrier constructor. The carrier constructor allows for the creation
     * of a carrier object that is associated with a specific carrier index.
     * The maximum index corresponds to the maximum number of carriers that
     * can be supported by the radio hardware implementation.
     *
     * The constructor is protected so ensure that it can only created by the
     * implementing class
     *
     * @param carrierIndex the index of the carrier being created.
     * @param maxTxPaths maximum possible transmit paths associated with this carrier
     * @param maxRxPaths maximum possible receive paths associated with this carrier
     * @param carrierSetter Set to true if this is to be used as an ICarrierSetter rather than an ICarrier
     */
    CommonCarrier(unsigned carrierIndex, unsigned maxTxPaths, unsigned maxRxPaths, bool carrierSetter = false);

    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~CommonCarrier();

    // ICarrier

    /*! @brief  Get tx path count
     *
     *  Method used to retrieve the maximum possible number of transmit carrier
     *  paths available.
     *
     *  @return number of transmit carrier paths.
     */
    virtual const unsigned getNumberTxPaths(void) const override ;

    /*! @brief  Get rx path count
     *
     *  Method used to retrieve the maximum possible number of receive carrier
     *  paths available.
     *
     *  @return number of transmit carrier paths.
     */
    virtual const unsigned getNumberRxPaths(void) const override ;

    /*! @brief  Get the carrier number
     *
     *  Method used to return the carrier number associated with this carrier
     *  object.
     *
     *  @return carrier number
     */
    virtual const unsigned getIndex(void) const override ;

    /*! @brief  Get the carrier state
     *
     *  Method used to return the current state of this carrier object.
     *
     *  @return carrier state
     */
    virtual const ICarrier::State getState(void) const override ;

    /*! @brief  Get the carrier signal type
     *
     *  Method used to return the signal type of this carrier object.
     *
     *  @return carrier signal is either normal or test.
     */
    virtual const ICarrier::Signals getSigType(void) const override ;

    /*! @brief  Get the carrier type
     *
     *  Method used to return the carrier type of this carrier object.
     *
     *  @return carrier type i.e WCDMA, LTE5, LTE10 etc.
     */
    virtual const ICarrier::Type getType(void) const override ;

    /**
     * Method to get the carrier transmit frequency in kHz. This value will be derived either
     * from the value set via setTxFrequency() or the offset set via setTxFrequencyOffset()
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return transmit frequency in kHz
     */
    virtual const Frequency getTxFrequency() const override ;

    /**
     * Method to get the carrier receive frequency in kHz. This value will be derived either
     * from the value set via setRxFrequency() or the offset set via setRxFrequencyOffset()
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return receive frequency in kHz
     */
    virtual const Frequency getRxFrequency() const override ;

    /**
     * Method to get the carrier transmit frequency offset in kHz
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return transmit frequency in kHz
     */
    virtual const FrequencyOffset getTxFrequencyOffset() const override ;

    /**
     * Method to get the carrier receive frequency offset in kHz
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return receive frequency in kHz
     */
    virtual const FrequencyOffset getRxFrequencyOffset() const override ;

    /**
     * Is the TX frequency offset set to be used?
     */
    virtual bool isTxFreqOffsetSet() const override ;

    /**
     * Is the RX frequency offset set to be used?
     */
    virtual bool isRxFreqOffsetSet() const override ;


    /**
     * Method to get the carrier transmit frequency in kHz. This method returns the value set
     * via setTxFrequency()
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return transmit frequency in kHz
     */
    virtual const Frequency getTxFrequencySetting() const override;

    /**
     * Method to get the carrier receive frequency in kHz. This method returns the value set
     * via setRxFrequency()
     *
     * If the frequency has not been set for this carrier, zero is returned.
     *
     * @return receive frequency in kHz
     */
    virtual const Frequency getRxFrequencySetting() const override;




    /**
     * @brief Get the carrier power setpoint dBm
     *
     * This method is used to return the carrier power setting in units
     * of dBm.
     *
     * @return carrier power dBm.
     */
    virtual const Power getTxPower() const override ;
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
    virtual const unsigned getTxContainer(unsigned path) const override ;

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
    virtual const unsigned getRxContainer(unsigned path) const override ;

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
    virtual const unsigned getRxFibre(unsigned path) const;

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
    virtual const unsigned getTxFibre(unsigned path) const;


    /**
     * @brief Get the group size for the up link path
     *
     * This method is used to return the up link group size that has been set
     * for this carrier.
     *
     * @return group size value, expected to be between 1 and 8
     */
    virtual const unsigned getGroupSizeUp() const override ;

    /**
     * @brief Get the group size for the down link path
     *
     * This method is used to return the down link group size that has been set
     * for this carrier.
     *
     * @return group size value, expected to be between 1 and 8
     */
    virtual const unsigned getGroupSizeDown() const override ;


    /**
     * @brief Get the up link noise
     *
     * Method used to return the up link noise in dBFS.
     *
     * @return Up link in dBFS
     */
    virtual const Power getUplinkNoise() const override ;

    /**
     * @brief Get the DL scaling
     *
     * Method used to return the DL scaling in dBFS.
     *
     * @return DL scaling factor in dBFS
     */
    virtual const Power getTxScaling() const override ;


	/**
	 * Is this a CPRI carrier (i.e. requires AxC / group settings) ?
	 */
	virtual bool isCPRI() const override ;


    /**
     * @brief True if configured and active
     *
     * Method used to verify to caller that the carrier data has been successfully configured
     * and is valid.
     *
     * @return true if configured
     */
    virtual const bool isConfigured() const override ;

    /**
     * @brief True if configured and active
     *
     * Method used to verify to caller that the carrier data has been successfully configured
     * and is valid.
     *
     * @return true if configured
     */
    virtual const bool isTxConfigured() const override ;

    /**
     * @brief True if configured and active
     *
     * Method used to verify to caller that the carrier data has been successfully configured
     * and is valid.
     *
     * @return true if configured
     */
    virtual const bool isRxConfigured() const override ;

    /**
     * @brief True if this a configured Tx carrier
     *
     * Method used to verify to the caller that this is a transmit carrier (assigned
     * non-zero transmit containers).
     *
     * @return true if transmit carrier that is configured and active
     */
    virtual const bool isTx() const override ;

    /**
     * @brief True if this a configured Tx carrier
     *
     * Method used to verify to the caller that this is a transmit carrier (assigned
     * non-zero transmit containers) on the specified path
     *
     * @param txpath	0-based antenna path to check TX is assigned on
     * @return true if transmit carrier that is configured and active is on this tx path
     */
    virtual const bool isTx(const unsigned txpath) const override ;

    /**
     * @brief True if this a configured Rx carrier
     *
     * Method used to verify to the caller that this is a receive carrier (assigned
     * non-zero receive containers).
     *
     * @return true if receive carrier that is configured and active
     */
    virtual const bool isRx() const override ;

    /**
     * @brief True if this a configured Rx carrier
     *
     * Method used to verify to the caller that this is a receive carrier (assigned
     * non-zero receive containers).
     *
     * @param rxpath	0-based antenna path to check RX is assigned on
     * @return true if receive carrier that is configured and active on this rx path
     */
    virtual const bool isRx(const unsigned rxpath) const override ;

    /**
     * @brief Get the IF frequency associated with given transmit path
     *
     * Method used to obtain the IF frequency for a given transmit path. This may be
     * port specific or common to all ports and carriers depending on the radio hardware.
     *
     * @param path transmit path
     * @return the transmit path IF frequency on kiloHertz
     */
    virtual const Frequency getTxIfFrequency( unsigned path ) const override ;

    /**
     * @brief Get the IF frequency associated with given receive path
     *
     * Method used to obtain the IF frequency for a given receive path. This may be
     * port specific or common to all ports and carriers depending on the radio hardware.
     *
     * @param path receive path
     * @return the receive path IF frequency on kiloHertz
     */
    virtual const Frequency getRxIfFrequency( unsigned path ) const override ;

    /**
     * @brief Applies all changes
     *
     * Method clears all the "changed" flags used in the get*Changed() methods
     */
    virtual const void applyChanges(void) override ;

    /**
     * @brief See if the container number for a given Tx path has changed
     *
     * @param path zero based Tx path selector
     * @return true if changed
     */
    virtual const bool getTxContainerChanged(unsigned path) const override ;

    /**
     * @brief See if the container number for a given Rx path has changed
     *
     * @param path zero based Rx path selector
     * @return true if changed
     */
    virtual const bool getRxContainerChanged(unsigned path) const override ;

    /**
     * @brief See if the fibre number for a given Tx path has changed
     *
     * @param path zero based Tx path selector
     * @return true if changed
     */
    virtual const bool getTxFibreChanged(unsigned path) const;

    /**
     * @brief See if the fibre number for a given Rx path has changed
     *
     * @param path zero based Rx path selector
     * @return true if changed
     */
    virtual const bool getRxFibreChanged(unsigned path) const;

    /**
     * @brief See if the carrier power setpoint power has changed
     *
     * @return true if changed
     */
    virtual const bool getTxPowerChanged(void) const override ;

    /*! @brief  See if the carrier signal type has changed
     *
     * @return true if changed
     */
    virtual const bool getSigTypeChanged(void) const override ;

    /*! @brief  See if the carrier type has changed
     *
     * @return true if changed
     */
    virtual const bool getTypeChanged(void) const override ;

    /**
     * See if the carrier transmit frequency has changed
     *
     * @return true if changed
     */
    virtual const bool getTxFrequencyChanged(void) const override ;

    /**
     * See if  carrier receive frequency has changed
     *
     * @return true if changed
     */
    virtual const bool getRxFrequencyChanged(void) const override ;

    /**
     * See if the carrier transmit frequency offset has changed
     *
     * @return true if changed
     */
    virtual const bool getTxFrequencyOffsetChanged(void) const override ;

    /**
     * See if  carrier receive frequency offset has changed
     *
     * @return true if changed
     */
    virtual const bool getRxFrequencyOffsetChanged(void) const override ;

    /**
     * @brief See if the up link noise has changed
     *
     * @return true if changed
     */
    virtual const bool getUplinkNoiseChanged(void) const override ;

    /**
     * @brief See if the DL scaling has changed
     *
     * @return true if changed
     */
    virtual const bool getTxScalingChanged() const override ;

    /**
     * @brief See if the carrier up link data group size has changed
     *
     * @return true if changed
     */
    virtual const bool getGroupSizeUpChanged(void) const override ;

    /**
     * @brief See if the carrier down link data group size has changed
     *
     * @return true if changed
     */
    virtual const bool getGroupSizeDownChanged(void) const override ;


    /*! @brief  See the carrier state has changed
     *
     * @return true if changed
     */
    virtual const bool getStateChanged(void) const override ;

    /*! @brief  Get the loopback state
     *
     * @return true if loopback enabled
     */
    virtual const bool getLoopback(void) const override ;

    /*! @brief  Has the loopback state changed
     *
     * @return true if loopback changed
     */
    virtual const bool getLoopbackChanged(void) const override ;


    /**
     * Has this TX path been enabled or disabled
     * @param txpath	Path to check
     * @return true if this TX path has been enabled or disabled
     */
    virtual const bool getTxPathChanged(unsigned txpath) const override ;

    /**
     * Has this RX path been enabled or disabled
     * @param rxpath	Path to check
     * @return true if this RX path has been enabled or disabled
     */
    virtual const bool getRxPathChanged(unsigned rxpath) const override ;

    /*! @brief  Get the uplink/downlink configuration
	 *
	 * @return uplink/downlink configuration value, expected between 0 and 6 inclusive
	 */
	virtual const unsigned getUlDlConfig(void) const override;

	/*! @brief  Has the uplink/downlink configuration changed
	 *
	 * @return true if uplink/downlink configuration changed
	 */
	virtual const bool getUlDlConfigChanged(void) const override;

    /*! @brief  Get the special subframe configuration
	 *
	 * @return special subframe configuration value, expected between 0 and 10 inclusive
	 */
	virtual const unsigned getSpSuConfig(void) const override;

	/*! @brief  Has the special subframe configuration changed
	 *
	 * @return true if special subframe configuration changed
	 */
	virtual const bool getSpSuConfigChanged(void) const override;

    /*! @brief  Get the uplink cyclix prefix length
	 *
	 * @return special uplink cyclix prefix length (normal/extended)
	 */
	virtual const ICarrier::CyclicPrefixLenType getUlPrefixLen(void) const override;

	/*! @brief  Has the uplink cyclix prefix length changed
	 *
	 * @return true if uplink cyclix prefix length changed
	 */
	virtual const bool getUlPrefixLenChanged(void) const override;

    /*! @brief  Get the downlink cyclix prefix length
	 *
	 * @return special downlink cyclix prefix length (normal/extended)
	 */
	virtual const ICarrier::CyclicPrefixLenType getDlPrefixLen(void) const override;

	/*! @brief  Has the downlink cyclix prefix length changed
	 *
	 * @return true if downlink cyclix prefix length changed
	 */
	virtual const bool getDlPrefixLenChanged(void) const override;

    /**
     * Has anything changed in the carrier
     * @return true if anything changed
     */
    virtual const bool isChanged(void) const override ;

    /**
     * Get the carrier-base RSSI measurement for this RX path
     * @param path		zero based Rx path selector
     * @param error		Set on any error
     * @return Carrier RSSI power
     */
    virtual Power getRssi(unsigned path, std::string& error) const override ;

    /**
     * Indicates to carrier that this TX path must be shutdown
     * @param path
     * @return tx shutdown state
     */
    virtual bool getShutdownTx(unsigned path) const override ;


	/**
	 * Get the subcarrier spacing for DL
	 */
	virtual ScsType getDlScs() const override ;

	/**
	 * Get the FFT size  for DL
	 */
	virtual FFTsizeType getDlFftSize() const override ;

	/**
	 * Get the subcarrier spacing for UL
	 */
	virtual ScsType getUlScs() const override ;

	/**
	 * Get the FFT size  for UL
	 */
	virtual FFTsizeType getUlFftSize() const override ;

	/**
	 * Get the UL extended Antenna-Carrier ID per port
	 */
	virtual unsigned getUlEaxcId(unsigned path) const override ;

	/**
	 * Get the DL extended Antenna-Carrier ID per port
	 */
	virtual unsigned getDlEaxcId(unsigned path) const override ;


	/**
	 * Get the O-DU MAC
	 */
	virtual uint64_t getUlMacId() const override ;

	/**
	 * Get the carrier mode
	 */
	virtual ICarrier::ModeType getMode() const ;

	/**
	 * Get length of UL cyclic prefix (in Ts) for first CP
	 */
	virtual unsigned getUlCpSize() const ;

	/**
	 * Get length of UL cyclic prefix (in Ts) for subsequent CP
	 */
	virtual unsigned getUlCpOtherSize() const ;

	/**
	 * Get length of DL cyclic prefix (in Ts) for first CP
	 */
	virtual unsigned getDlCpSize() const ;

	/**
	 * Get length of DL cyclic prefix (in Ts) for subsequent CP
	 */
	virtual unsigned getDlCpOtherSize() const ;



	/**
	 * Has the subcarrier spacing for DL changed?
	 */
	virtual bool getDlScsChanged() const override ;

	/**
	 * Has the FFT size  for DL changed?
	 */
	virtual bool getDlFftSizeChanged() const override ;

	/**
	 * Has the subcarrier spacing for UL changed?
	 */
	virtual bool getUlScsChanged() const override ;

	/**
	 * Has the FFT size  for UL changed?
	 */
	virtual bool getUlFftSizeChanged() const override ;

	/**
	 * Has the UL extended Antenna-Carrier ID per port changed?
	 */
	virtual bool getUlEaxcIdChanged(unsigned path) const override ;

	/**
	 * Has the DL extended Antenna-Carrier ID per port changed?
	 */
	virtual bool getDlEaxcIdChanged(unsigned path) const override ;

	/**
	 * Has the O-DU MAC changed
	 */
	virtual bool getUlMacIdChanged() const override ;

	/**
	 * Has the carrier mode changed?
	 */
	virtual bool getModeChanged() const ;

	/**
	 * Has length of UL cyclic prefix (in Ts) for first CP changed?
	 */
	virtual bool getUlCpSizeChanged() const ;

	/**
	 * Has length of UL cyclic prefix (in Ts) for subsequent CP changed?
	 */
	virtual bool getUlCpOtherSizeChanged() const ;

	/**
	 * Has length of DL cyclic prefix (in Ts) for first CP changed?
	 */
	virtual bool getDlCpSizeChanged() const ;

	/**
	 * Has length of DL cyclic prefix (in Ts) for subsequent CP changed?
	 */
	virtual bool getDlCpOtherSizeChanged() const ;



    // ICarrierSetter

	/**
	 * Unconfigure this carrier (delete all of it's settings)
	 * @return true if ok
	 */
	virtual bool unconfigure() override ;

    /**
     * @brief Set carrier settings
     *
     * Given an Mplane::ICarrier object with new settings, this instances copies the settings
     * over.
     *
     * @param carrier ICarrier with new settings to apply
     * @return false if set fails otherwise true
     */
    virtual bool setCarrier(const ICarrier& carrier) override ;

    /**
     * @brief Set the state of the carrier.
     *
     * Method, called by the friend CarrierControl object to set the required
     * carrier state for this carrier.
     *
     * @param state
     * @return false if set fails otherwise true
     */
    virtual bool setState(ICarrier::State state) override ;

    /**
     * @brief Set carrier transmit frequency.
     *
     * Method, called by the friend CarrierControl object to set the required
     * transmit carrier frequency
     *
     * @param frequency in KHz fir this carrier
     * @return false if set fails otherwise true
     */
    virtual bool setTxFrequency(Frequency frequency) override ;

    /**
     * @brief Set carrier receive frequency
     *
     * Method, called by the friend CarrierControl o bject to set the required
     * receive carrier frequency
     *
     * @param frequency in KHz fir this carrier
     * @return false if set fails otherwise true
     */
    virtual bool setRxFrequency(Frequency frequency) override ;

    /**
     * @brief Set carrier transmit frequency offset.
     *
     * Method, called by the friend CarrierControl object to set the required
     * transmit carrier frequency
     *
     * @param frequency in KHz fir this carrier
     * @return false if set fails otherwise true
     */
    virtual bool setTxFrequencyOffset(FrequencyOffset frequency) override ;

    /**
     * @brief Set carrier receive frequency offset
     *
     * Method, called by the friend CarrierControl object to set the required
     * receive carrier frequency
     *
     * @param frequency in KHz fir this carrier
     * @return false if set fails otherwise true
     */
    virtual bool setRxFrequencyOffset(FrequencyOffset frequency) override ;


    /**
     * @brief Set the carrier transmit power setpoint dBm
     *
     * This method is used to set the carrier power setting in units
     * of dBm.
     *
     * @param power carrier power dBm.
     * @return false if set fails otherwise true
     */
    virtual bool setTxPower(Power dB) override ;

    /*! @brief  Set the carrier signal type
     *
     *  Method used to set the signal type of this carrier object.
     *
     *  @param sigType signal type required for the carrier.
     * @return false if set fails otherwise true
     */
    virtual bool setSigType(ICarrier::Signals sigType) override ;

    /*! @brief  Set the carrier type
     *
     *  Method used to set the carrier type of this carrier object.
     *
     * @param type ie CDMA, UMTS, LTE5, LTE10 etc.
     * @return false if set fails otherwise true
     */
    virtual bool setType(ICarrier::Type type) override ;

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
    virtual bool setTxContainer(unsigned path, unsigned container) override ;

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
    virtual bool setRxContainer(unsigned path, unsigned container) override ;

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
    virtual bool setTxFibre(unsigned path, unsigned fibre) override ;

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
    virtual bool setRxFibre(unsigned path, unsigned fibre) override ;

    /**
     * @brief Set the carrier up link data group size
     *
     * This method is used to set the up link data group size associated with
     * this carrier.
     *
     * @param grpSizeUp a valid group size from 1 to N
     * @return bool true is group size valid.
     */
    virtual bool setGroupSizeUp( unsigned grpSizeUp) override ;

    /**
     * @brief Set the carrier down link data group size
     *
     * This method is used to set the down link data group size associated with
     * this carrier.
     *
     * @param grpSizeDown a valid group size from 1 to N
     * @return bool true is group size valid.
     */
    virtual bool setGroupSizeDown( unsigned grpSizeDown) override ;

    /**
     * @brief Set the up link noise
     *
     * Method used to set the up link noise in dBFS.
     *
     * @param upLinkNoise up link noise in dBFS
     * @return false if set fails otherwise true
     */
    virtual bool setUplinkNoise(Power upLinkNoisedB) override ;

    /**
     * @brief Set the DL scaling
     *
     * @param dlScaling DL scaling in dBFS
     * @return false if set fails otherwise true
     */
    virtual bool setTxScaling(Power dlScaling) override ;

    /*! @brief  Set the loopback state
     * @param loopback new lookback setting
     * @return false if set fails otherwise true
     */
    virtual bool setLoopback(bool loopBack) override ;

    /*! @brief  Set the uplink downlink configuration
     * @param uldlConfig new uplink downlink configuration setting
     * @return false if set fails otherwise true
     */
    virtual bool setUlDlConfig(unsigned uldlConfig) override;

    /*! @brief  Set the special subframe configuration
     * @param spsuConfig new special subframe configuration setting
     * @return false if set fails otherwise true
     */
    virtual bool setSpSuConfig(unsigned spsuConfig) override;

    /*! @brief  Set the uplink cyclic prefix length
     * @param ulPrefixLen new uplink cyclic prefix length setting
     * @return false if set fails otherwise true
     */
    virtual bool setUlPrefixLenConfig(ICarrier::CyclicPrefixLenType ulPrefixLen) override;

    /*! @brief  Set the downlink cyclic prefix length
     * @param dlPrefixLen new downlink cyclic prefix length setting
     * @return false if set fails otherwise true
     */
    virtual bool setDlPrefixLenConfig(ICarrier::CyclicPrefixLenType dlPrefixLen) override;

    /**
     * Indicates to carrier that this TX path must be shutdown
     * @param path
     * @return false if set fails
     */
    virtual bool setShutdownTx(unsigned path) override ;

	/**
	 * Set the subcarrier spacing for DL
	 */
	virtual bool setDlScs(ScsType scs) override ;

	/**
	 * Set the FFT size  for DL
	 */
	virtual bool setDlFftSize(FFTsizeType fftSize) override ;

	/**
	 * Set the subcarrier spacing for UL
	 */
	virtual bool setUlScs(ScsType scs) override ;

	/**
	 * Set the FFT size  for UL
	 */
	virtual bool setUlFftSize(FFTsizeType fftSize) override ;


	/**
	 * Set the UL extended Antenna-Carrier ID per port
	 */
	virtual bool setUlEaxcId(unsigned path, unsigned eaxcId) override ;

	/**
	 * Set the DL extended Antenna-Carrier ID per port
	 */
	virtual bool setDlEaxcId(unsigned path, unsigned eaxcId) override ;

	/**
	 * Set the O-DU MAC
	 */
	virtual bool setUlMacId(uint64_t macid) override ;

	/**
	 * Set the carrier mode
	 */
	virtual bool setMode(ICarrier::ModeType mode) ;

	/**
	 * Set length of UL cyclic prefix (in Ts) for first CP
	 */
	virtual bool setUlCpSize(unsigned sizeTs) ;

	/**
	 * Set length of UL cyclic prefix (in Ts) for subsequent CP
	 */
	virtual bool setUlCpOtherSize(unsigned sizeTs) ;

	/**
	 * Set length of DL cyclic prefix (in Ts) for first CP
	 */
	virtual bool setDlCpSize(unsigned sizeTs) ;

	/**
	 * Set length of DL cyclic prefix (in Ts) for subsequent CP
	 */
	virtual bool setDlCpOtherSize(unsigned sizeTs) ;





    /**
     * @brief Print out contents of carrier to stdout
     * Used for debug only
     */
    virtual void showCarrier(std::ostream& os = std::cout) const override ;


protected:
    // Internal flag used to determine whether this carrier is being used as an ICarrierSetter
    virtual bool isSetter() const ;

protected:
    // SDP: Why have we made this protected? Much safer/better OO design to have them all private and provide methods....
    Frequency mRxIFFrequency;
    Frequency mTxIFFrequency;

private:
    /**
     * Mutex to protect carrier from being changed by multiple threads
     */
    mutable Mutex mCarrierMutex ;

    const unsigned mIndex;               //!< Associated CARRIERCFG index
    const unsigned mMaxTxPaths;          //!< Maximum Tx paths associated with carrier
    const unsigned mMaxRxPaths;          //!< Maximum Rx paths associated with carrier

    bool mIsCpri ;
    Frequency mTxFrequency;         //!< Transmit frequency in kHz
    Frequency mRxFrequency;         //!< Receive frequency in kHz
    FrequencyOffset mTxFrequencyOffset;         //!< Transmit frequency offset in kHz
    FrequencyOffset mRxFrequencyOffset;         //!< Receive frequency offset in kHz
    bool mTxFreqOffsetSet ;
    bool mRxFreqOffsetSet ;
    ICarrier::State mState;         //!< DISABLE or ENABLE
    ICarrier::Signals mSignalType;  //!< NORMAL or TEST
    ICarrier::Type mType;           //!< Type of carrier being
    Power mPower;                   //!< Carrier power
    Power mUplinkNoise;             //!< Uplink noise
    Power mTxScaling;             	//!< DL scaling
    unsigned mGrpSizeUp;                 //!< Data link group size for the up link
    unsigned mGrpSizeDown;               //!< Data link group size for the down link
    bool mLoopback;					//!< Loopback setting

    std::vector<unsigned> mTxContainers;
    std::vector<unsigned> mRxContainers;

    std::vector<unsigned> mTxFibres;
    std::vector<unsigned> mRxFibres;

    mutable std::vector<bool> mShutdownTx;

    unsigned mUlDlConfig;            			 //uplink/downlink configuration (applicable if TDD is enabled)
    unsigned mSpSuConfig;            			 //special subframe configuration (applicable if TDD is enabled)
    ICarrier::CyclicPrefixLenType mUlPrefixLen;  //uplink cyclic prefix length (applicable if TDD is enabled)
    ICarrier::CyclicPrefixLenType mDlPrefixLen;  //downlink cyclic prefix length (applicable if TDD is enabled)

    ICarrier::ScsType mUlScs ;
    ICarrier::ScsType mDlScs ;
    ICarrier::FFTsizeType mUlFftSize ;
    ICarrier::FFTsizeType mDlFftSize ;

    std::vector<unsigned> mDlEaxcId;
    std::vector<unsigned> mUlEaxcId;
    uint64_t mUlMacId;

    ICarrier::ModeType mMode ;
    unsigned mDlCpSize ;
    unsigned mDlCpOtherSize ;
    unsigned mUlCpSize ;
    unsigned mUlCpOtherSize ;

    /**
     * Track any changes in these flags
     */
    class ChangeFlags {
    public:
    	ChangeFlags(const unsigned maxTxPaths, const unsigned maxRxPaths) ;
    	void clear(void) ;
    	bool mIsChanged;
        bool mTxFrequency;
        bool mRxFrequency;
        bool mTxFrequencyOffset;
        bool mRxFrequencyOffset;
        bool mState;
        bool mSignalType;
        bool mType;
        bool mPower;
        bool mUplinkNoise;
        bool mTxScaling;
        bool mGrpSizeUp;
        bool mGrpSizeDown;
        bool mLoopback;

        std::vector<bool> mTxContainers;
        std::vector<bool> mRxContainers;
        std::vector<bool> mTxFibres;
        std::vector<bool> mRxFibres;
        std::vector<bool> mTxPaths;
        std::vector<bool> mRxPaths;

        bool mUlDlConfig;
        bool mSpSuConfig;
        bool mUlPrefixLen;
        bool mDlPrefixLen;

        bool mUlScs ;
        bool mDlScs ;
        bool mUlFftSize ;
        bool mDlFftSize ;

        std::vector<bool> mDlEaxcId;
        std::vector<bool> mUlEaxcId;
        bool mUlMacId;

        bool mMode ;
        bool mDlCpSize ;
        bool mDlCpOtherSize ;
        bool mUlCpSize ;
        bool mUlCpOtherSize ;

    } mChangedFlags ;

    // Flag used to indicate whether this is an ICarrierSetter
    bool mCarrierSetter ;

};


}


#endif /* _MPLANE_COMMONCARRIER_H_ */
