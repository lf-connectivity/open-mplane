#ifndef _MPLANE__FTUTXCAL_H_
#define _MPLANE__FTUTXCAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxCal.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "string.h"
#include "CommonCalBase.h"
#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"
#include "ITxCal.h"
#include "ITxCalData.h"

#include <memory>
#include <list>
#include <vector>
#include <map>

namespace Mplane
{

/**
 * The Point class defines a simple data class used to store a measured power
 * against attenuation.
 *
 * These objects are created during the parsing of the transmit calibration
 * data and added to the PwerBand data class.
 */
class Point
{
public:
    Power power;
    Power varDsa;
};

/**
 * The TX PowerBand class is created from the TX calibration data file TxCal.xml.
 * This file contains a number of power bands across the operating frequency range.
 * The purpose of the class is to allow the operational software to find the optimum
 * attenuator settings for a given output power at the current port frequency.
 *
 * It will first search the calibration data for a power band that matches its
 * frequency and required power range, then pass the required power to the
 * findNearestPower() method.
 *
 * PowerBand objects are created by parsing XML data similar to the following:
 *
 *          <PowerBand comment="This Upper PowerBand is for high Power CW tone generation">
 *              <Upper>15.0</Upper>
 *              <Lower>13.0</Lower>
 *              <BB >-3.0</BB>
 *              <Temperature>23.5</Temperature>
 *              <Point>
 *                  <Power>14.64</Power>
 *                  <RFAtten>6.0</RFAtten>
 *              </Point>
 *              <Point>
 *                  <Power>14.00</Power>
 *                  <RFAtten>7.0</RFAtten>
 *              </Point>
 *              <Point>
 *                  <Power>13.64</Power>
 *                  <RFAtten>8.0</RFAtten>
 *              </Point>
 *              <Point>
 *                  <Power>13.0</Power>
 *                  <RFAtten>9.0</RFAtten>
 *              </Point>
 *            </PowerBand>
 *
 */
class PowerBand
{
public:
    friend class TxCalTestCase;

    static const std::string name;
    static const std::string UpperStr;
    static const std::string LowerStr;
    static const std::string BBStr;
    static const std::string RFAttenStr;
    static const std::string TemperatureStr;
    static const std::string PointStr;
    static const std::string PowerStr;


    /**
     * PowerBand object constructor, created by the TX calibration data file parser
     * using its data fields.
     * @param upper power in the band
     * @param lower power in the band
     * @param baseband power used at cal time
     * @param temperature transmit path temperature during calibration
     */
    PowerBand( Power upper, Power lower, Power baseband, float temperature );

    /**
     * Default constructor
     */
    ~PowerBand();

    /**
     * Used by the calibration data file parser to add power points to this power band.
     * @param point
     */
    void addPointPower( Point &point );

    /**
     * Method used to return the calibration baseband power
     * @return base band power
     */
    Power& getBaseBand();

    /**
     * Method used to get all the power against attenuation data records
     * associated with this power band.
     * @return
     */
    const std::vector<Point>& getCalPoints() const;

    /**
     * Get the lower power in the band
     * @return low power in band
     */
    const Power& getLower() const;

    /**
     * Get the calibration temperature
     * @return calibration temperature
     */
    float getTemperature();

    /**
     * Get the upper power in the band
     * @return upper power in band
     */
    const Power& getUpper() const;

    /**
     * This method will return a calibration power point that is closest to the
     * given power.
     * @param power ro search for
     * @param calPoint [out] a reference to the nearest calibration data point to the given power
     * @return
     */
    ReturnType::State findNearestPower( Power power, Point &calPoint );

    /**
     * This method will return a calibration point where the attenuation value
     * is closest to the given attenuation
     * @param atten to search for
     * @param point a reference to the point nearest to the given attenuation
     * @return true if found else false.
     */
    bool findAtten( Power atten, Point &point );

    std::shared_ptr<PowerBand> getPrevious();

    std::shared_ptr<PowerBand> getNext();

    void setPrevious( std::shared_ptr<PowerBand> previous);

    void setNext( std::shared_ptr<PowerBand> next);

protected:
    /**
     * The upper power for this power band calibration data
     */
    Power mUpper;
    /**
     * The lower power for this power band calibration data
     */
    Power mLower;
    /**
     * The base band digital power used when collating the calibration data
     */
    Power mBaseBand;

    /**
     * The temperature at which the calibration data was collected.
     */
    float mTemperature;
    /**
     * This is a map of the clibration data points that is a map of IF digital attenuator power
     * settings against the measure power at that setting.
     */
    std::vector<Point> mCalPoints;

    Point mNearest;

    std::shared_ptr<PowerBand> mPrevious;

    std::shared_ptr<PowerBand> mNext;

};

/**
 * This class is used to represent the frequency data extracted from the TX calibration
 * data files.
 *
 * FrequencyTable objects are created by parsing XML data similar to the following:
 *
 *         <FrequencyTable>
 *          <Frequency>2355000</Frequency>
 *          <Coefficient units="dB/DegC">0.0625</Coefficient>
 *          <PowerBand comment="This Upper PowerBand is for high Power CW tone generation">
 *              <Upper>15.0</Upper>
 *              <Lower>13.0</Lower>
 *              <BB >-3.0</BB>
 *              <Temperature>23.5</Temperature>
 *              <Point>
 *                  <Power>14.64</Power>
 *                  <RfAtten>6.0</RfAtten>
 *              </Point>
 *          </PowerBand>
 *          .
 *          .
 *          </FrequencyTable>
 *
 */
class FrequencyTable
{
public:
    friend class TxCalTestCase;

    /**
     * Frequency tabl;e constructor assigns the frequency associated with table,
     * and a flag used to indicate that this tables includes linear temperature
     * coeefficient data.
     *
     * @param frequency associated with this data table
     * @param haveCoefficient true if this table includes a temperature coefficient
     * @param temperatureCoefficient the temperature coefficient value read from the calibration data table.
     */
    explicit FrequencyTable( Frequency frequency, bool haveCoefficient , float temperatureCoefficient );

    /**
     * Default destructor
     */
    ~FrequencyTable();

    /**
     * Get the frequency of this data table
     * @return frequency for this table
     */
    Frequency &getFrequency();

    /**
     * Used during the parsing of the calibration data to add power band data
     * to this frequency table.
     * @param powerBand chared pointer to an instance of PowerBand data class.
     */
    void addPowerBand( std::shared_ptr<PowerBand> powerBand );

    /**
     * Constant used in the parsing of the frequency table in the XML calibration file
     */
    static const std::string name;
    /**
     * Constant used in the parsing of the frequency value for the table defined in the XML calibration table.
     */
    static const std::string FrequencyStr;
    static const std::string CoefficientStr;


    /**
     * Method returns a reference to an Mplane::PowerBand object that contains the
     * given power
     * @param power to search for
     * @param powerBand reference to a power band that contains the given power
     * @return true is power found, otherwise false.
     */
    bool isPowerInBand( Power power, std::shared_ptr<PowerBand> &powerBand );

    /**
     * Get the Mplane::PowerBand that follows the  one for the given power.
     * @param power to search for
     * @param powerBand that follows that which contains power
     * @return true if found, otherwise false
     */
    bool getNextBand( Power power, std::shared_ptr<PowerBand> &powerBand );

    /**
     * Find a power band where the fixed attenuation matches
     * @param rfAtten
     * @param powerBand
     * @return true if found otherwise false
     */
    bool findPowerBandWithDsa( Power rfAtten, std::shared_ptr<PowerBand> &powerBand, Point &calPoint );

    /**
     * Get the attenuation and base band power for the first power band in the frequency table
     * @param[out] rfDsa
     * @param[out] ifDsa
     * @param[out] base band power
     * @return true if found otherwise false
     */
    bool getDataAtFirstPowerBand( Power &rfAtten, Power &baseBand);

    /**
     * Method used to determine is the calibration file being parsed includes a
     * per frequency calibration value. If it returns true then the frequency table
     * has a coefficent value that can be used when getting open loop power
     * settings.
     *
     * @return true if frequency has temperature compensation else false.
     */
    bool hasTemperatureCoefficient();

    /**
     * If the frequency table has a temperature coefficient field, this method
     * can be used to access it.
     * @return
     */
    float getTemperatureCoefficient();

protected:
    /**
     * The frequency about which this calibration data was created.
     */
    Frequency mFrequency;
    /**
     * The calibration data fro multiple power bands against the give calibration frequency
     */
    std::list<std::shared_ptr<PowerBand>> mPowerBands;

    bool mHasTemperatureCoefficient;

    float mTemperatureCoefficient;

    std::shared_ptr<PowerBand> mPrevPowerBand;

};

/**
 * This class is the main interface to the transmit path calibration data.
 * It provides a number of methods used to find calibration data based on
 * frequency and power.
 *
 * It is constructed by the TX calibration data parser when the TX cal data is loaded.
 */
class TxOpenLoop : public ITxOpenLoop
{
public:
    friend class TxCalTestCase;

    /**
     * Constructor used by the TX calibration data parser to create an instance
     * to which the calibration data is added.
     * @param path  the transmit port to which the calibration data refers
     * @param tempCoeef the overall termperature coefficient for the path
     * @param date the date the calibration data was created.
     */
    TxOpenLoop( int path , float tempCoeef, const std::string& date );

    /**
     * Default constructor
     */
    ~TxOpenLoop();

    /**
     * Method to return the TX port index with which this open loop calibration
     * data is associated
     * @return TX port index
     */
    virtual int getPath() override;

    /**
     * Method returns the temperature coefficient for this TX path.
     * @return
     */
    virtual float getCoefficient() override;

    /**
     * Used by the TX calibration data parser to add frequency data, extracted from the calibration
     * data file to the open loop data interface.
     * @param frequencyTable
     */
    void addFrequencyTable( std::shared_ptr<FrequencyTable> frequencyTable );

    /**
     * Return the data string that records when the calibration data was created.
     * @return
     */
    virtual std::string getDate() override;

    /**
     * Method to return the IF and RF attenuation value and the
     * small correction error that is used to set the digital path scalar,
     * given the required power, frequency and temperature,
     * @param frequency [in] - frequency
     * @param power [in] - the required power
     * @param temperature [in] - the current temperature
     * @param baseBand [out] - the baseband power
     * @param correction [out] - the correction error
     * @param rfAtten [out] - the RF attenuation setting at the required power
     * @param ifAtten [out] - the IF attenuation setting at the required power
     * @param calTemperature [out] - the calibration temperature
     *
     * @return true if OK, false otherwise
     */
    virtual bool getData( Frequency frequency, Power power, float temperature,
            Power &baseBand, Power &correction, Power &rfAtten, float &calTemperature ) override;

    /**
     * Method to return the IF and RF attenuation value and the
     * base band power given the frequency
     * @param frequency [in] - frequency
     * @param baseBand [out] - the baseband power
     * @param rfAtten [out] - the RF attenuation setting at the first power band
     * @param ifAtten [out] - the IF attenuation setting at the first power band
     *
     * @return true if OK, false otherwise
     */
    virtual bool getData( Frequency frequency, Power &baseBand, Power &rfAtten) override;

    /**
     * Method to return the power given the frequency, base band power, and attenuation values
     * @param frequency [in] - frequency
     * @param baseBand [in] - the baseband power
     * @param rfAtten [in] - the RF attenuation setting
     * @param ifAtten [in] - the IF attenuation setting
     * @param power [out] - power at the given settings
     *
     * @return true if OK, false otherwise
     */
    virtual bool getPower( Frequency frequency, Power baseBand, Power rfAtten, Power &power) override;

    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;
    static const std::string LinearTemperatureCompensation;
    static const std::string CoefficientStr;

protected:

    /**
     * Method used internally to get the frequency tables associated with a given frequency.
     * @param freq
     * @param lwrFrequencyTable
     * @param uprFequencyTable
     * @return
     */
    bool findFrequency( Frequency freq, std::shared_ptr<FrequencyTable> &lwrFrequencyTable, std::shared_ptr<FrequencyTable> &uprFequencyTable  );

    int mPath;
    float mTempCoeff;
    std::string mDate;
    std::list<std::shared_ptr<FrequencyTable>> mFrequencyTables;

};

/**
 * This class is the top level TX calibration data class created during the calibration
 * data parsing process. It holds data for each TX path.
 */
class TxCal : public ITxCal
{
public:
    friend class TxCalTestCase;

    /**
     * Construct an instance of the TX calibration data
     * @param version of the calibration data
     * @param country where the calibration was performed
     * @param facility factory
     * @param theoperator who did this
     */
    TxCal( const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator);

    /**
     * Default destructor
     */
    ~TxCal();

    /**
     * Used to access the open loop calibration data interface for a given TX path
     * @param path
     * @return
     */
    virtual std::shared_ptr<ITxOpenLoop> getTxOpenLoop( int path ) override;

   /**
    * Used by the calibration data file parser to add open open loop calibration
    * data to the TxCal object.
    *
    * @param path
    * @param txOpenLoop
    */
   void addTxOpenLoop( int path, std::shared_ptr<TxOpenLoop> txOpenLoop );

   static const std::string name;

protected:
   std::string mVersion;
   std::string mCountry;
   std::string mFacility;
   std::string mOperator;


   std::map<int, std::shared_ptr<TxOpenLoop> > mTxOpenLoopData;

};

}

#endif /* _MPLANE__FTUTXCAL_H_ */
