#ifndef _HW_COMMON_CALDATA_SRXCAL_H_
#define _HW_COMMON_CALDATA_SRXCAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SRxCal.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
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

#include "ISRxCal.h"

namespace Mplane
{

class SRxPoint
{
public:
    Power rfDSA;
    Power dBFS2dBm;
};


class SRxFrequencyTable
{
public:
    friend class SRxCalTestCase;

    SRxFrequencyTable( Frequency frequency, float temperature );

    ~SRxFrequencyTable();

    Frequency &getFrequency();

    float getTemperature();

    void addPoint( SRxPoint &point );

    const std::vector<SRxPoint>& getCalPoints() const;

    SRxPoint findNearestPower( Power power );

    SRxPoint findPowerForDSASetting( Power power );

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
     * This is a map of the calibration data points that is a map of IF digital attenuator power
     * settings against the measure power at that setting.
     */
    std::vector<SRxPoint> mCalPoints;

};

class SRxFrequencyBand
{
public:
    friend class SRxCalTestCase;


    SRxFrequencyBand( Frequency upper, Frequency lower );

    ~SRxFrequencyBand();

    void addFrequencyTable( std::shared_ptr<SRxFrequencyTable> frequencyTable );

    const Frequency& getLower() const;

    const Frequency& getUpper() const;


    bool findFreqTable( Frequency frequency, std::shared_ptr<SRxFrequencyTable> &freqTable );

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
     * The calibration data for multiple power bands against the give calibration frequency
     */
    std::list<std::shared_ptr<SRxFrequencyTable>> mFrequencyTables;

};

class SRxOpenLoop : public ISRxOpenLoop
{
public:
    friend class SRxCalTestCase;

    SRxOpenLoop( int path , float tempCoeef, const std::string& date );

    ~SRxOpenLoop();


    /**
     * Get the path associated with the calibration data.
     * @return SRX path
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
     * Find the dBfs to dBM conversion factor given the current attenuator setting,
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


    void addFrequencyBand( std::shared_ptr<SRxFrequencyBand> frequencyBand );

    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;
    static const std::string LinearTemperatureCompensation;
    static const std::string CoefficientStr;

protected:

    bool findFreqBand( Frequency frequency, std::shared_ptr<SRxFrequencyBand> &freqBand );

    int mPath;
    float mTempCoeff;
    std::string mDate;
    std::list<std::shared_ptr<SRxFrequencyBand>> mFrequencyBands;

};

class SRxCal : public ISRxCal
{
public:
    friend class SRxCalTestCase;

    SRxCal( const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator);

    ~SRxCal();

    virtual std::shared_ptr<ISRxOpenLoop> getSRxOpenLoop( int path );

    void addSRxOpenLoop( int path, std::shared_ptr<SRxOpenLoop> rxOpenLoop );


    static const std::string name;

protected:
    std::string mVersion;
    std::string mCountry;
    std::string mFacility;
    std::string mOperator;

    std::map<int, std::shared_ptr<SRxOpenLoop> > mSRxOpenLoopData;

};

}

#endif /* _HW_COMMON_CALDATA_SRXCAL_H_ */
