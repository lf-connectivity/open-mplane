#ifndef _MPLANE__TXIFCAL_H_
#define _MPLANE__TXIFCAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxIfCal.h
 * \brief     TX IF calibration classes for storing the cal data
 *
 *
 */

#include <memory>
#include <list>
#include <vector>
#include <map>

#include "CommonCalBase.h"
#include "FrequencyOffset.h"
#include "Power.h"
#include "Temperature.h"

#include "ITxIfCal.h"

namespace Mplane
{

struct TxIfPoint
{
	TxIfPoint() : freqOffset(0.0), gain(0.0) {}

	TxIfPoint(const FrequencyOffset& offset, const Power& _gain) :
		freqOffset(offset),
		gain(_gain)
	{}

	FrequencyOffset freqOffset;
    Power 			gain;
};


class TxIfFrequencyOffsetTable
{
public:
	TxIfFrequencyOffsetTable( );
    ~TxIfFrequencyOffsetTable();

    /**
     * Add a new point to the table
     * @param point
     */
    void addTxIfPoint( const TxIfPoint &point );

    /**
     * Using the provided frequency offset, find the nearest TxIfPoint
     * @param freqOffset
     * @return nearest point
     */
    const TxIfPoint getPoint(const FrequencyOffset& freqOffset) const ;

public:
    // Used during XML parsing
    static const std::string name;
    static const std::string PointStr;
    static const std::string offsetStr;
    static const std::string gainStr;

private:
    /**
     * This is the contents of the table
     */
    std::vector<TxIfPoint> mCalPoints;

};

class TxIfOffsetFrequency
{
public:
    TxIfOffsetFrequency( FrequencyOffset upper, FrequencyOffset lower );

    ~TxIfOffsetFrequency();

    void addFrequencyOffsetTable( std::shared_ptr<TxIfFrequencyOffsetTable> frequencyTable );

    const FrequencyOffset getLower() const;

    const FrequencyOffset getUpper() const;

    /**
     * Given a frequency offset, find the table which contains this frequency (or closest match)
     * @param frequency
     * @return
     */
    std::shared_ptr<TxIfFrequencyOffsetTable> findFreqTable( FrequencyOffset frequency );

//    const std::list<std::shared_ptr<TxIfFrequencyOffsetTable>>& getFrequencyOffsetTables() const ;

public:
    // Used during XML parsing
    static const std::string name;
    static const std::string UpperStr;
    static const std::string LowerStr;

protected:
    /**
     * The upper power for this power band calibration data
     */
    FrequencyOffset mUpper;
    /**
     * The lower power for this power band calibration data
     */
    FrequencyOffset mLower;
    /**
     * List of tables - should only ever be one
     */
    std::list<std::shared_ptr<TxIfFrequencyOffsetTable>> mFrequencyOffsetTables;

};

class TxIfResponse : public ITxIfResponse
{
public:
    TxIfResponse( int path, float temperature, const std::string& date );

    ~TxIfResponse();

    virtual int getPath() override ;

//    virtual float getCoefficient() override ;

    virtual float getTemperature() override ;

    virtual std::string getDate() override ;

	virtual bool getGain( FrequencyOffset frequencyOffset, Power &gain ) override ;

    void addOffsetFrequency( std::shared_ptr<TxIfOffsetFrequency> offsetFrequencyOffset );

public:
    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;
    static const std::string TemperatureStr ;
//    static const std::string LinearTemperatureCompensation;
//    static const std::string CoefficientStr;

protected:
    std::shared_ptr<TxIfOffsetFrequency> findOffsetFreq( FrequencyOffset frequency );

private:
    int mPath;
    float mTemp;
    std::string mDate;
    std::list<std::shared_ptr<TxIfOffsetFrequency>> mOffsetFrequencies;

};

class TxIfCal : public ITxIfCal
{
public:
    TxIfCal(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator);

    ~TxIfCal();

	/**
	 * Get the Rx IF response for the specified path
	 * @param path
	 * @return
	 */
    virtual std::shared_ptr<ITxIfResponse> getTxIfResponse( int path );

    /**
     * Setter - add a new response
     * @param path
     * @param rxIfResponse
     */
    void addTxIfResponse( int path, std::shared_ptr<TxIfResponse> rxIfResponse );

    /**
     * Get version string
     * @return
     */
    virtual std::string getVersion() const override ;

    /**
     * Get country string
     * @return
     */
    virtual std::string getCountry() const override ;

    /**
     * Get facility string
     * @return
     */
    virtual std::string getFacility() const override ;

    /**
     * Get operator string
     * @return
     */
    virtual std::string getOperator() const override ;


public:
   static const std::string name;

protected:
   std::string mVersion;
   std::string mCountry;
   std::string mFacility;
   std::string mOperator;

   std::map<int, std::shared_ptr<TxIfResponse> > mTxIfResponseData;

};

}

#endif /* _MPLANE__TXIFCAL_H_ */
