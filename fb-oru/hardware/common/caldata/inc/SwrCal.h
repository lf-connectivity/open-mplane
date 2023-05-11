#ifndef _MPLANE__SWRCAL_H_
#define _MPLANE__SWRCAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SwrCal.h
 * \brief     Interface to reverse path power measurement calibration data
 *
 *
 * \details   Interface to reverse path power measurement calibration data
 *
 */

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "CommonCalBase.h"
#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"

#include "ISwrCal.h"

namespace Mplane
{

class SwrPoint
{
public:
    Power rfDSA;
    Power dBFS2dBm;
};


class SwrFrequencyTable
{
public:
    friend class SwrCalTestCase;

    SwrFrequencyTable( Frequency frequency, float temperature );

    ~SwrFrequencyTable();

    Frequency &getFrequency();

    float getTemperature();

    void addPoint( SwrPoint &point );

    const std::vector<SwrPoint>& getCalPoints() const;

    SwrPoint findNearestPower( Power power );

    SwrPoint findPowerForDSASetting( Power power );

    static const std::string name;
    static const std::string FrequencyStr;
    static const std::string TemperatureStr;
    static const std::string PointStr;
    static const std::string rfDSAStr;
    static const std::string dBFS2dBmStr;

protected:
    /**
     * The frequency about which this calibration data was created.
     */
    Frequency mFrequency;

    float mTemperature;

    /**
     * This is a map of the calibration data points that is a map of RF attenuator power
     * settings against the measure power at that setting.
     */
    std::vector<SwrPoint> mCalPoints;

};

class SwrFrequencyBand
{
public:
    friend class SRxCalTestCase;


    SwrFrequencyBand( Frequency upper, Frequency lower );

    ~SwrFrequencyBand();

    void addFrequencyTable( std::shared_ptr<SwrFrequencyTable> frequencyTable );

    const Frequency& getLower() const;

    const Frequency& getUpper() const;


    bool findFreqTable( Frequency frequency, std::shared_ptr<SwrFrequencyTable> &freqTable );

    static const std::string name;
    static const std::string UpperStr;
    static const std::string LowerStr;

protected:
    /**
     * The upper power for this power band calibration data
     */
    Frequency mUpper;
    /**
     * The lower power for this power band calibration data
     */
    Frequency mLower;
    /**
     * The calibration data fro multiple power bands against the give calibration frequency
     */
    std::list<std::shared_ptr<SwrFrequencyTable>> mFrequencyTables;

};

class SwrOpenLoop : public ISwrOpenLoop
{
public:
    friend class SwrCalTestCase;

    SwrOpenLoop( int path , float tempCoeef, const std::string& date );

    ~SwrOpenLoop();


    /**
     * Get the path associated with the calibration data.
     * @return Srx path
     */
    virtual int getPath() override ;

    /**
     * Get the SRX path temperature coefficient.
     *
     * @return temperature coefficient
     */
    virtual float getCoefficient() override ;

    /**
     * Get the calibration date
     * @return
     */
    virtual std::string getDate() override;

    /**
     * Find the dBfs to dbM conversion factor given the current attenuator setting,
     * frequency and temperature. This is used to convert the SRX RSSI reading from
     * dBfs to the actual dBm power.
     *
     * @param frequency
     * @param rfDsa
     * @param temperature
     * @return  power correction factor.
     */
    virtual Power dBfsTodBm( Frequency frequency, Power rfDsa, float temperature ) override ;

    /**
     * Look through the calibration file for the attenuation value that matches the nearest
     * target measurement power.
     *
     * @param frequency
     * @param target measure power
     * @return
     */
    virtual Power findNearestAttenuation( Frequency frequency, Power target ) override;


    void addFrequencyBand( std::shared_ptr<SwrFrequencyBand> frequencyBand );

    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;
    static const std::string LinearTemperatureCompensation;
    static const std::string CoefficientStr;

protected:

    bool findFreqBand( Frequency frequency, std::shared_ptr<SwrFrequencyBand> &freqBand );

    int mPath;
    float mTempCoeff;
    std::string mDate;
    std::list<std::shared_ptr<SwrFrequencyBand>> mFrequencyBands;

};

class SwrCal : public ISwrCal
{
public:
    friend class SwrCalTestCase;

	SwrCal( const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator);

	~SwrCal();

	virtual std::shared_ptr<ISwrOpenLoop> getSwrOpenLoop( int path );

	void addSwrOpenLoop( int path, std::shared_ptr<SwrOpenLoop> rxOpenLoop );


	static const std::string name;

protected:
   std::string mVersion;
   std::string mCountry;
   std::string mFacility;
   std::string mOperator;

   std::map<int, std::shared_ptr<SwrOpenLoop> > mSwrOpenLoopData;

};

}

#endif /* _MPLANE__SRXCAL_H_ */
