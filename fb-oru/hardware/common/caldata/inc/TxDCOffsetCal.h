#ifndef _MPLANE__TXDCOFFSETCAL_H_
#define _MPLANE__TXDCOFFSETCAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxDCOffsetCal.h
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

#include <memory>
#include <list>
#include <vector>
#include <map>

namespace Mplane
{


class TxDCOffsetFrequency
{
public:
    friend class TxDCOffsetCalTestCase;

    TxDCOffsetFrequency( Frequency frequency, float temperature, int iDCOffset, int qDCOffset ):
        mFrequency( frequency ),
        mTemperature( temperature ),
        mIDCOffset( iDCOffset ),
        mQDCOffset( qDCOffset )
    {
    }

    ~TxDCOffsetFrequency()
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

    const int getIDCOffset()
    {
        return mIDCOffset;
    }

    const int getQDCOffset()
    {
        return mQDCOffset;
    }

    static const std::string name;
    static const std::string FrequencyStr;
    static const std::string TemperatureStr;
    static const std::string IDCOffsetStr;
    static const std::string QDCOffsetStr;

protected:
    /**
     * The frequency about which this calibration data was created.
     */
    Frequency mFrequency;
    float mTemperature;
    int mIDCOffset;
    int mQDCOffset;
};

class TxDCOffset
{
public:
    friend class TxDCOffsetCalTestCase;

    TxDCOffset( int path , float tempCoeff, const std::string& date ):
        mPath( path ),
        mTempCoeff( tempCoeff ),
        mDate( date )
    {
    }

    ~TxDCOffset()
    {
    }

    const int getPath()
    {
        return mPath;
    }

    const float getCoefficient()
    {
        return mTempCoeff;
    }

    const std::string getDate()
    {
        return mDate;
    }

    void addFrequencyTable( std::shared_ptr<TxDCOffsetFrequency> frequencyTable );


    bool getIQOffsets( Frequency frequency, float &temperature,  int &iDCOffset, int &qDCOffset );


    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;
//    static const std::string LinearTemperatureCompensation;
//    static const std::string CoefficientStr;

protected:

    bool findFrequency( Frequency freq, std::shared_ptr<TxDCOffsetFrequency> &frequencyTable );

    int mPath;
    float mTempCoeff;
    std::string mDate;
    std::list<std::shared_ptr<TxDCOffsetFrequency>> mFrequencyTables;

};

class TxDCOffsetCal
{
public:
    friend class TxDCOffsetCalTestCase;


    TxDCOffsetCal( const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator):
        mVersion( version ),
        mCountry( country ),
        mFacility( facility ),
        mOperator( theoperator )
    {
    }

    ~TxDCOffsetCal()
    {
    }

    std::shared_ptr<TxDCOffset> getTxDCOffset( int path );

   void addTxDCOffset( int path, std::shared_ptr<TxDCOffset> txDCOffset );

   static const std::string name;

protected:
   std::string mVersion;
   std::string mCountry;
   std::string mFacility;
   std::string mOperator;

   std::map<int, std::shared_ptr<TxDCOffset> > mTxDCOffsetData;

};


class TxDCOffsetCalData: public CommonCalBase
{
public:
    friend class TxDCOffsetCalTestCase;

    explicit TxDCOffsetCalData(  std::shared_ptr<ICalDownload> calDownload );

    virtual ~TxDCOffsetCalData();

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
    std::shared_ptr<TxDCOffset> getTxDCOffset( int path );


protected:
    bool parseTxDCOffsetCal(tinyxml2::XMLElement* node) ;
    bool extractTxDCOffset(std::shared_ptr<TxDCOffsetCal> txDCOffsetCal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequecnyTable(std::shared_ptr<TxDCOffset> txDCOffset, tinyxml2::XMLElement* a_node) ;


    std::shared_ptr<ICalDownload> mCalDownload;


    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    /**
     * Set to the full path of the cal file for this object
     */
    std::string mCalFilePath;

    std::shared_ptr<TxDCOffsetCal>   mTxDCOffsetCal;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;
};





}

#endif /* _MPLANE__TXDCOFFSETCAL_H_ */
