#ifndef _COMMON_PAMCAL_H_
#define _COMMON_PAMCAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PamCal.h
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

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "IPamCal.h"

namespace Mplane
{

class PgsPowerBand
{
public:
    friend class PamCalTestCase;

    static const std::string name;
    static const std::string RadioTemperatureStr;
    static const std::string PamTemperatureStr;
    static const std::string VvaPwmStr;
    static const std::string LowGainOutputPowerStr;
    static const std::string HighGainOutputPowerStr;


    PgsPowerBand( float radioTemperature, float pamTemperature,
    		unsigned int vvaPwm, Power lowGainOutputPower, Power highGainOutputPower);

    ~PgsPowerBand();

    float& getRadioTemperature();

    float& getPamTemperature();

    unsigned int& getVvaPwm();

    Power& getLowGainOutputPower();

    Power& getHighGainOutputPower();


protected:

    /**
     * The radio calibration temperature about which this calibration data was created.
     */
    float mRadioTemperature;

    /**
     * The PAM calibration temperature about which this calibration data was created.
     */
    float mPamTemperature;

    /**
     * The VVA PWM setting for the output power measured
     */
    unsigned int mVvaPwm;

    /**
     * The output power measured when in low gain mode, the PA gain switch is active
     */
    Power mLowGainOutputPower;

    /**
     * The output power measured when in high gain mode, the PA gain switch is not active
     */
    Power mHighGainOutputPower;

};

class PgsFrequencyTable
{
public:
    friend class PamCalTestCase;

    static const std::string name;
    static const std::string FrequencyStr;

    explicit PgsFrequencyTable( Frequency frequency);

    ~PgsFrequencyTable();

    Frequency& getFrequency();

    void addPgsPowerBand( std::shared_ptr<PgsPowerBand> powerBand );

    /**
     * Method that tries to find the power band that has an exact match for the required
     * low gain power in the frequency table.
     *
     * @param power [in] the required low gain power to find
     * @param powerBand [out] the power band containing the found power
     *
     * @return true if exact match found, false otherwise
     */
    bool isLowGainPowerInBand( Power power, std::shared_ptr<PgsPowerBand> &powerBand );

    /**
     * Method that tries to find the power band that has an exact match for the required
     * high gain power in the frequency table.
     *
     * @param power [in] the required high gain power to find
     * @param powerBand [out] the power band containing the found power
     *
     * @return true if exact match found, false otherwise
     */
    bool isHighGainPowerInBand( Power power, std::shared_ptr<PgsPowerBand> &powerBand );

    /**
     * Method that tries to find the upper and lower power bands that contain the required power
     * and which will then require interpolation in order to get the required data
     *
     * @param power [in] the required power to find (either low or high gain power)
     * @param lwrPowerBand [out] the lower power band containing the found power
     * @param uprPowerBand [out] the upper power band containing the found power
     * @param ratio [out] the ratio to apply when using the power band data
     *
     * @return true if power found, false otherwise
     */
    bool findPowerBandWithPower( Power power, std::shared_ptr<PgsPowerBand> &lwrPowerBand, std::shared_ptr<PgsPowerBand> &uprPowerBand, float &ratio );


protected:

    /**
     * The frequency about which this calibration data was created.
     */
    Frequency mFrequency;

    /**
     * The calibration data for multiple power bands against the given calibration frequency
     */
    std::list<std::shared_ptr<PgsPowerBand>> mPowerBands;

};

class PaGainStep : public IPaGainStep
{
public:
    friend class PamCalTestCase;

    PaGainStep( int path , float tempStepCoeff, float tempCoeff, const std::string& date );

    ~PaGainStep();

    virtual int getPath() override ;

    virtual float getCoefficient() override ;

    virtual float getStepCoefficient() override ;

    virtual std::string getDate() override ;

    virtual bool getData( Frequency frequency, Power power, float &radioCalTemperature, float &pamCalTemperature,
    		unsigned int &vvaPwm, Power &lowGainOutputPower, Power &highGainOutputPower )  override ;

    void addFrequencyTable( std::shared_ptr<PgsFrequencyTable> frequencyTable );

    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;
    static const std::string LinearTemperatureCompensationStr;
    static const std::string CoefficientStr;
    static const std::string StepCoefficientStr;

protected:

    bool findFrequency( Frequency freq, std::shared_ptr<PgsFrequencyTable> &lwrFrequencyTable,
    		                            std::shared_ptr<PgsFrequencyTable> &uprFrequencyTable  );

    int mPath;
    float mTempStepCoeff;
    float mTempCoeff;
    std::string mDate;
    std::list<std::shared_ptr<PgsFrequencyTable>> mFrequencyTables;

};

class PamCal : public IPamCal
{
public:
    friend class PamCalTestCase;


    PamCal( const std::string& version, const std::string& country,
    		            const std::string& facility, const std::string& theoperator);

    ~PamCal();

    /**
     * Method used to get access to the PA Gain step calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<IPaGainStep> getPaGainStep( int path ) override ;

    void addPaGainStep( int path, std::shared_ptr<PaGainStep> paGainStep );

    static const std::string name;

protected:
   std::string mVersion;
   std::string mCountry;
   std::string mFacility;
   std::string mOperator;

   std::map<int, std::shared_ptr<PaGainStep> > mPaGainStepData;

};

}

#endif /* _COMMON_PAMCAL_H_ */
