#ifndef _MPLANE__TXVVACAL_H_
#define _MPLANE__TXVVACAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxVVACal.h
 * \brief     A collection of classes that described the Tx DAC DC Offset calibration data, extracted from
 *            the TxDcOffset.xml file.
 *
 *
 * \details   A collection of classes that described the Tx DAC DC Offset calibration data, extracted from
 *            the TxDcOffset.xml file.
 *
 */

#include "libtinyxml2/tinyxml2.h"

#include "string.h"
#include "CommonCalBase.h"
#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"
#include "TxDCOffsetCalDownload.h"
#include "Spline.h"

#include <memory>
#include <list>
#include <vector>
#include <map>

namespace Mplane
{


class TxVVAFrequency
{
public:
    friend class TxVVACalTestCase;

    TxVVAFrequency( Frequency frequency, float temperature ):
        mFrequency( frequency ),
        mTemperature( temperature )
    {
    }

    ~TxVVAFrequency()
    {
    }

    Frequency &getFrequency()
    {
        return mFrequency;
    }

    const float getTemperature()
    {
        return mTemperature;
    }

    void addPoint( float dBfs, float pwm )
    {
        spline.addpoint(dBfs,  pwm );
    }

    int getPWM( float dBfs )
    {
        return (int) spline.getY( dBfs );
    }

	float getDBM( int pwm )
    {
        return spline.getX( (float)pwm );
    }

    static const std::string name;
    static const std::string FrequencyStr;
    static const std::string TemperatureStr;
    static const std::string PointStr;
    static const std::string PWMStr;
    static const std::string DBStr;

protected:
    /**
     * The frequency about which this calibration data was created.
     */
    Frequency mFrequency;
    float mTemperature;
    Spline spline;
};

class TxVVA
{
public:
    friend class TxVVACalTestCase;

    TxVVA( int path , const std::string& date ):
        mPath( path ),
        mDate( date )
    {
    }

    ~TxVVA()
    {
    }

    const int getPath()
    {
        return mPath;
    }


    const std::string getDate()
    {
        return mDate;
    }

    void addFrequencyTable( std::shared_ptr<TxVVAFrequency> frequencyTable );


    bool getPWM( Frequency frequency, float db,  int &pwm );

	bool getDBM( Frequency frequency, int pwm,  float& dbm );


    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;

protected:

    bool findFrequency( Frequency freq, std::shared_ptr<TxVVAFrequency> &frequencyTable );

    int mPath;
    std::string mDate;
    std::list<std::shared_ptr<TxVVAFrequency>> mFrequencyTables;

};

class TxVVACal
{
public:
    friend class TxVVACalTestCase;


    TxVVACal( const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator):
        mVersion( version ),
        mCountry( country ),
        mFacility( facility ),
        mOperator( theoperator )
    {
    }

    ~TxVVACal()
    {
    }

    std::shared_ptr<TxVVA> getTxVVA( int path );

   void addTxVVA( int path, std::shared_ptr<TxVVA> txVVA );

   static const std::string name;

protected:
   std::string mVersion;
   std::string mCountry;
   std::string mFacility;
   std::string mOperator;

   std::map<int, std::shared_ptr<TxVVA> > mTxVVAData;

};


class TxVVACalData: public CommonCalBase
{
public:
    friend class TxVVACalTestCase;

    explicit TxVVACalData(  std::shared_ptr<ICalDownload> calDownload );

    virtual ~TxVVACalData();

    /**
     * Method implemented to fulfil the GeneralLog puclic interface contract.
     */
    virtual void show();

    /**
     * Method called during initialisation to load the calibration data from file
     * @return
     */
    virtual ReturnType::State load();

    /**
     * Method used to get access to the Tx open loop calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    std::shared_ptr<TxVVA> getTxVVA( int path );


protected:
    bool parseTxVVACal(tinyxml2::XMLElement* node) ;
    bool extractTxVVA(std::shared_ptr<TxVVACal> txVVACal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequecnyTable(std::shared_ptr<TxVVA> txVVA, tinyxml2::XMLElement* a_node) ;


    std::shared_ptr<ICalDownload> mCalDownload;


    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    /**
     * Set to the full path of the cal file for this object
     */
    std::string mCalFilePath;

    std::shared_ptr<TxVVACal>   mTxVVACal;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;
};





}

#endif /* _MPLANE__TXVVACAL_H_ */
