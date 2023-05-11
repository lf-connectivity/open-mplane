/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxCal.h
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

#include "IRxCal.h"
//#include "Loggable.h"

#ifndef _HW_COMMON_CALDATA_RXCAL_H_
#define _HW_COMMON_CALDATA_RXCAL_H_

namespace Mplane
{

class RxStep
{
public:
    Power GainRed;
    Power IFDSARed;
};

class IFAttenTable
{
public:

    IFAttenTable();

    ~IFAttenTable();

    void addRxStep( RxStep &step );

    const std::vector<RxStep>& getCalSteps() const;

    RxStep findNearestGainRed( Power gainRed );

    static const std::string name;
    static const std::string StepStr;
    static const std::string GainRedStr;
    static const std::string IFDSARedStr;

protected:

    /**
     * This is a map of the steps that are a IFDSA reduction (absolute value of gain reduction from 0dB
     * reference value IFDSA) for an applied reduction.
     */
    std::vector<RxStep> mCalSteps;

};

class RxPoint
{
public:
    Power rfDSA;
    Power dBFS2dBm;
};

class RxFrequencyTable
{
public:
    friend class RxCalTestCase;

    RxFrequencyTable( Frequency frequency, float temperature );

    RxFrequencyTable( Frequency frequency, float temperature, Power IfDsa);

    ~RxFrequencyTable();

    Frequency &getFrequency();

    float getTemperature();

    Power& getIfDsa();

    void addRxPoint( RxPoint &point );

    const std::vector<RxPoint>& getCalPoints() const;

    RxPoint findNearestPower( Power power );

    RxPoint findPowerForDSASetting( Power power );

    static const std::string name;
    static const std::string FrequencyStr;
    static const std::string TemperatureStr;
    static const std::string PointStr;
    static const std::string rfDSAStr;
    static const std::string ifDSAStr;
    static const std::string dBFS2dBmStr;

protected:
    /**
     * The frequency about which this calibration data was created.
     */
    Frequency mFrequency;

    float mTemperature;

    Power mIfDsa;

    /**
     * This is a map of the calibration data points that is a map of IF digital attenuator power
     * settings against the measure power at that setting.
     */
    std::vector<RxPoint> mCalPoints;

};

class RxFrequencyBand
{
public:
    friend class RxCalTestCase;

    enum class IfDsaLoc { PerFreqBand, PerFreqTable }; //!> Used to indicate whether the IFDSA is specific to frequency band or frequency table


    RxFrequencyBand( Frequency upper, Frequency lower, Power IfDsa );

    RxFrequencyBand( Frequency upper, Frequency lower);

    ~RxFrequencyBand();

    void addIFAttenTable( std::shared_ptr<IFAttenTable> iFAttenTable );

    void addFrequencyTable( std::shared_ptr<RxFrequencyTable> frequencyTable );

    const Frequency& getLower() const;

    const Frequency& getUpper() const;

    Power& getIfDsa(Frequency freq);

    IfDsaLoc getIfDsaLoc();

    const std::shared_ptr<IFAttenTable>& getIFAttenTable() const ;

    bool findFreqTable( Frequency frequency, std::shared_ptr<RxFrequencyTable> &freqTable );

    const std::list<std::shared_ptr<RxFrequencyTable>>& getFrequencyTables() const ;

    static const std::string name;
    static const std::string UpperStr;
    static const std::string LowerStr;
    static const std::string IFDSAStr;

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
     * The RF digital attenuator setting used when collecting the IF attenuation power calibration data.
     */
    Power mIfDsa;
    /**
     * Whether the IFDSA is specific to frequency band or frequency table
     */
    IfDsaLoc mIfDsaLoc;
    /**
     * The calibration data for multiple power bands against the IF Atten steps for 40dB Rx Gain range
     */
    std::shared_ptr<IFAttenTable> mIFAttenTable;
    /**
     * The calibration data f0r multiple power bands against the give calibration frequency
     */
    std::list<std::shared_ptr<RxFrequencyTable>> mFrequencyTables;

};

//class RxOpenLoop : public IRxOpenLoop, public Loggable
class RxOpenLoop : public IRxOpenLoop
{
public:
    friend class RxCalTestCase;

    RxOpenLoop( int path , float tempCoeef, const std::string& date, float gainTarget = 7.0 );

    ~RxOpenLoop();

    virtual int getPath() override ;

    virtual float getCoefficient() override ;

    virtual float getGainTarget() override;

    virtual std::string getDate() override ;

    virtual bool getIfAtten( Frequency frequency, Power &ifAtten ) override ;
	virtual bool getIfAtten( Frequency frequency, Power &ifAtten, Temperature& calTemperature ) override ;

    virtual bool getRfAtten( Frequency frequency, Power amplitude, Power &rfAtten ) override ;
    virtual bool getRfAttenAndScaler( Power amplitude, Frequency frequency, Power tempCompIdeal, Power &rfAtten, Power &scaler ) override ;
    virtual Power getTempCompTarget(Frequency frequency, Power target, float temperature) override;
    virtual bool getNearestGainReduction(Power reduction, Frequency frequency, Power &nearestIFDSARed, Power &nearestGainRed) override;

    /**
     * Given the frequency and rfdsa, get the nearest power and compensate for temperature and IF attenuation
     */
    virtual Power dBfsTodBm( Frequency frequency, Power rfDsa, float temperature ) override;

    /**
     * Given the frequency and rfdsa, get the nearest power without compensating for temperature or IF attenuation
     */
	virtual Power dBfsTodBm(Frequency frequency, Power rfDsa) override;

    /**
     * Given the frequency, get the rsdsa for the first cal point in the file
     */
    virtual Power getRfdsaForFrequency(Frequency frequency) override;

    void addFrequencyBand( std::shared_ptr<RxFrequencyBand> frequencyBand );

    const std::list<std::shared_ptr<RxFrequencyBand>>& getFrequencyBands() const ;

public:
    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;
    static const std::string LinearTemperatureCompensation;
    static const std::string CoefficientStr;
    static const std::string GainTargetStr;

protected:

    bool findFreqBand( Frequency frequency, std::shared_ptr<RxFrequencyBand> &freqBand );

    int mPath;
    float mTempCoeff;
    std::string mDate;
    float mGainTarget;
    std::list<std::shared_ptr<RxFrequencyBand>> mFrequencyBands;

};

class RxCal : public IRxCal
{
public:
    friend class RxCalTestCase;


    RxCal(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator);

    ~RxCal();

    virtual std::shared_ptr<IRxOpenLoop> getRxOpenLoop( int path ) override;

    void addRxOpenLoop( int path, std::shared_ptr<RxOpenLoop> rxOpenLoop );

public:
    static const std::string name;

protected:
    std::string mVersion;
    std::string mCountry;
    std::string mFacility;
    std::string mOperator;

    std::map<int, std::shared_ptr<RxOpenLoop> > mRxOpenLoopData;

};

}

#endif /* _HW_COMMON_CALDATA_RXCAL_H_*/
