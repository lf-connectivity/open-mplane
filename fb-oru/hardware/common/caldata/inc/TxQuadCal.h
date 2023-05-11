#ifndef _MPLANE__TXQUADPHASEOFFSETCAL_H_
#define _MPLANE__TXQUADPHASEOFFSETCAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxQuadCal.h
 * \brief     A collection of classes that described the Tx Quadrature Offset calibration data, extracted from
 *            the TxQuadratureOffset.xml file.
 *
 *
 * \details   A collection of classes that described the Tx Quadrature Offset calibration data, extracted from
 *            the TxQuadratureOffset.xml file.
 *
 */

#include "libtinyxml2/tinyxml2.h"

#include "string.h"
#include "CommonCalBase.h"
#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"
#include "TxQuadCalDownload.h"

#include <memory>
#include <list>
#include <vector>
#include <map>

namespace Mplane
{


class TxQuadOffsetFrequency
{
public:
    friend class TxQuadOffsetCalTestCase;

    TxQuadOffsetFrequency( Frequency frequency, float temperature, int iOffset, int qOffset, int iMag, int qMag ):
        mFrequency( frequency ),
        mTemperature( temperature ),
        mIPhaseOffset( iOffset ),
        mQPhaseOffset( qOffset ),
        mIMag( iMag ),
        mQMag( qMag )
    {
    }

    ~TxQuadOffsetFrequency()
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

    const int getIPhaseOffset()
    {
        return mIPhaseOffset;
    }

    const int getQPhaseOffset()
    {
        return mQPhaseOffset;
    }

    const int getIMag()
    {
        return mIMag;
    }

    const int getQMag()
    {
        return mQMag;
    }

    static const std::string name;
    static const std::string FrequencyStr;
    static const std::string TemperatureStr;
    static const std::string IPhaseOffsetStr;
    static const std::string QPhaseOffsetStr;
    static const std::string IMagStr;
    static const std::string QMagStr;

protected:
    /**
     * The frequency about which this calibration data was created.
     */
    Frequency mFrequency;
    float mTemperature;
    int mIPhaseOffset;
    int mQPhaseOffset;
    int mIMag;
    int mQMag;
};

class TxQuadOffset
{
public:
    friend class TxQuadOffsetCalTestCase;

    TxQuadOffset( int path , float tempCoeff, const std::string& date ):
        mPath( path ),
        mTempCoeff( tempCoeff ),
        mDate( date )
    {
    }

    ~TxQuadOffset()
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

    void addFrequencyTable( std::shared_ptr<TxQuadOffsetFrequency> frequencyTable );


    bool getData( Frequency frequency, float &temperature,  int &iPhaseOffset, int &qPhaseOffset, int &iMag, int &qMag );


    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;
//    static const std::string LinearTemperatureCompensation;
//    static const std::string CoefficientStr;

protected:

    bool findFrequency( Frequency freq, std::shared_ptr<TxQuadOffsetFrequency> &frequencyTable );

    int mPath;
    float mTempCoeff;
    std::string mDate;
    std::list<std::shared_ptr<TxQuadOffsetFrequency>> mFrequencyTables;

};

class TxQuadOffsetCal
{
public:
    friend class TxQuadOffsetCalTestCase;


    TxQuadOffsetCal( const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator):
        mVersion( version ),
        mCountry( country ),
        mFacility( facility ),
        mOperator( theoperator )
    {
    }

    ~TxQuadOffsetCal()
    {
    }

    std::shared_ptr<TxQuadOffset> getTxQuadOffset( int path );

   void addTxQuadOffset( int path, std::shared_ptr<TxQuadOffset> txQuadOffset );

   static const std::string name;

protected:
   std::string mVersion;
   std::string mCountry;
   std::string mFacility;
   std::string mOperator;

   std::map<int, std::shared_ptr<TxQuadOffset> > mTxQuadOffsetData;

};


class TxQuadOffsetCalData: public CommonCalBase
{
public:
    friend class TxQuadOffsetCalTestCase;

    explicit TxQuadOffsetCalData(  std::shared_ptr<ICalDownload> calDownload );

    virtual ~TxQuadOffsetCalData();

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
    std::shared_ptr<TxQuadOffset> getTxQuadOffset( int path );


protected:
    bool parseTxQuadOffsetCal(tinyxml2::XMLElement* node) ;
    bool extractTxQuadOffset(std::shared_ptr<TxQuadOffsetCal> txQuadOffsetCal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyTable(std::shared_ptr<TxQuadOffset> txQuadOffset, tinyxml2::XMLElement* a_node) ;


    std::shared_ptr<ICalDownload> mCalDownload;


    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    /**
     * Set to the full path of the cal file for this object
     */
    std::string mCalFilePath;

    std::shared_ptr<TxQuadOffsetCal>   mTxQuadOffsetCal;

    int mCalPath;
    std::vector<bool> mFirstTempPath;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;
};





}

#endif /* _MPLANE__TxPhaseOffsetCAL_H_ */
