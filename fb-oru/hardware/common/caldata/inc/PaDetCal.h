#ifndef _MPLANE__PADETCAL_H_
#define _MPLANE__PADETCAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaDetCal.h
 * \brief     A collection of classes that described the PA's detector characteristic using calibration data, extracted from
 *            the xxxxxxx.xml file.
 *
 *
 * \details   A collection of classes that described the PA's detector characteristic using calibration data, extracted from
 *            the xxxxxxx.xml file
 *
 */

#include "libtinyxml2/tinyxml2.h"

#include "string.h"
#include "CommonCalBase.h"
#include "Frequency.h"
#include "Power.h"
#include "Temperature.h"
#include "CalDownload.h"
#include "Spline.h"
#include "Loggable.h"

#include <memory>
#include <list>
#include <vector>
#include <map>

namespace Mplane
{


class PaDetFrequency
{
public:
    friend class PaDetCalTestCase;

    PaDetFrequency( Frequency frequency, float temperature ):
        mFrequency( frequency ),
        mTemperature( temperature )
    {
    }

    ~PaDetFrequency()
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

    void dBmAddPoint( float dBm, float pwrdet )
    {
        dBmSpline.addpoint(pwrdet,  dBm );
    }

    float getdBm( float pwrdet )
    {
        return dBmSpline.getYlinExtrap( pwrdet );
    }

    void pwrInAddPoint( float pwrOut, float pwrIn )
    {
        pwrInSpline.addpoint(pwrOut, pwrIn );
    }

    float getPwrIn( float pwrOut )
    {
        return pwrInSpline.getYlinExtrap( pwrOut );
    }

    static const std::string name;
    static const std::string FrequencyStr;
    static const std::string TemperatureStr;
    static const std::string PointStr;
    static const std::string PowerStr;
    static const std::string DetAdcStr;
    static const std::string PwrInStr;

protected:
    /**
     * The frequency about which this calibration data was created.
     */
    Frequency mFrequency;
    float     mTemperature;
    Spline    dBmSpline;
    Spline    pwrInSpline;
};

class PaDet
{
public:
    friend class PaDetCalTestCase;

    PaDet( int path , const std::string& date ):
        mPath( path ),
        mDate( date )
    {
    }

    ~PaDet()
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

    void addFrequencyTable( std::shared_ptr<PaDetFrequency> frequencyTable );

    bool getdBm(Frequency frequency, float pwrdet, float& dBm );
    bool getPwrIn(Frequency frequency, float pwrOut, float& pwrIn );

    static const std::string name;
    static const std::string PathStr;
    static const std::string DateStr ;

protected:

    bool findFrequencyTables( Frequency freq,
                        std::shared_ptr<PaDetFrequency> &frequencyTable1,
                        std::shared_ptr<PaDetFrequency> &frequencyTable2 );

    void findMinMaxFrequencies( Frequency& minFreq, Frequency& maxFreq);

    int mPath;
    std::string mDate;
    std::list<std::shared_ptr<PaDetFrequency>> mFrequencyTables;

};

class PaDetCal
{
public:
    friend class PaDetCalTestCase;


    PaDetCal( const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator):
        mVersion( version ),
        mCountry( country ),
        mFacility( facility ),
        mOperator( theoperator )
    {
    }

    ~PaDetCal()
    {
    }

    std::shared_ptr<PaDet> getPaDet( int path );

   void addPaDet( int path, std::shared_ptr<PaDet> paDet );

   static const std::string name;

protected:
   std::string mVersion;
   std::string mCountry;
   std::string mFacility;
   std::string mOperator;

   std::map<int, std::shared_ptr<PaDet> > mPaDetData;

};


class PaDetCalData: public CommonCalBase
{
public:
    friend class PaDetCalTestCase;

    explicit PaDetCalData(  std::shared_ptr<ICalDownload> calDownload );

    virtual ~PaDetCalData();

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
    std::shared_ptr<PaDet> getPaDet( int path );


protected:

    bool parsePaDetCal(tinyxml2::XMLElement* node) ;
    bool extractPaDet(std::shared_ptr<PaDetCal> paDetCal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyTable(std::shared_ptr<PaDet> paDet, tinyxml2::XMLElement* a_node) ;

    std::shared_ptr<ICalDownload> mCalDownload;


    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    /**
     * Set to the full path of the cal file for this object
     */
    std::string mCalFilePath;

    std::shared_ptr<PaDetCal>   mPaDetCal;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;
};





}

#endif /* _MPLANE__PADETCAL_H_ */
