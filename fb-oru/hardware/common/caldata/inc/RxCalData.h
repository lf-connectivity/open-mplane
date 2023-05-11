#ifndef _ETNA_FTU_RXCALDATA_H_
#define _ETNA_FTU_RXCALDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxCalData.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include <vector>

#include "libtinyxml2/tinyxml2.h"
#include "Power.h"
#include "Temperature.h"
#include "Frequency.h"
#include "CommonCalBase.h"

#include "ICalDownload.h"
#include "IRxCalData.h"

#include "RxCal.h"

namespace Mplane
{

class RxCalData: public CommonCalBase, public IRxCalData
{
public:

    friend class RxCalTestCase;

    explicit RxCalData( std::shared_ptr<ICalDownload> calDownLoad );

    virtual ~RxCalData();


    /**
     * Method implemented to fulfil the Loggable puclic interface contract.
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
    virtual std::shared_ptr<IRxOpenLoop> getRxOpenLoop( int path ) override ;

protected:
    virtual std::shared_ptr<RxCal> createRxCal(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator) ;

protected:

    std::shared_ptr<ICalDownload> mCalDownload;

    /**
     * This is set to the full path of the cal file for this cal data handler type in the constructor
     * using the ICalDownload implementation passed to it by the calibration data manager.
     */
    std::string mCalFilePath;


    bool parseRxCal(tinyxml2::XMLElement* node) ;
    bool extractRxOpenLoop(std::shared_ptr<RxCal> mRxCal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyBand(std::shared_ptr<RxOpenLoop> rxOpenLoop, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyTable(std::shared_ptr<RxFrequencyBand> frequencyBand, tinyxml2::XMLElement* a_node) ;
    bool extractIFAttenTable(std::shared_ptr<RxFrequencyBand> frequencyBand, tinyxml2::XMLElement* a_node) ;
    bool extractCalSteps(std::shared_ptr<IFAttenTable> frequencyTable, tinyxml2::XMLElement* a_node) ;
    bool extractCalPoints(std::shared_ptr<RxFrequencyTable> frequencyTable, tinyxml2::XMLElement* a_node) ;

    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    std::shared_ptr<RxCal>   mRxCal;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;

    /**
     * FCreate a vector of first temperature path flags, so we know that each one is done in turn
     */
    std::vector<bool> mFirstTempPath;
    int mCalPath;

};

}



#endif /* _ETNA_FTU_RXCALDATA_H_ */
