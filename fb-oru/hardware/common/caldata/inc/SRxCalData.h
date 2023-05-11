#ifndef _MPLANE_ETNA_SRXCALDATA_H_
#define _MPLANE_ETNA_SRXCALDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SRxCalData.h
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
#include "ISRxCalData.h"

#include "SRxCal.h"

namespace Mplane
{

class SRxCalData: public CommonCalBase, public ISRxCalData
{
public:

    friend class SRxCalTestCase;

    explicit SRxCalData( std::shared_ptr<ICalDownload> calDownLoad );

    virtual ~SRxCalData();


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
    virtual std::shared_ptr<ISRxOpenLoop> getSRxOpenLoop( int path ) override;

protected:

    std::shared_ptr<ICalDownload> mCalDownload;

    /**
     * This is set to the full path of the cal file for this cal data handler type in the constructor
     * using the ICalDownload implementation passed to it by the calibration data manager.
     */
    std::string mCalFilePath;


    bool parseSRxCal(tinyxml2::XMLElement* node) ;
    bool extractSRxOpenLoop(std::shared_ptr<SRxCal> mSRxCal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyBand(std::shared_ptr<SRxOpenLoop> sRrxOpenLoop, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyTable(std::shared_ptr<SRxFrequencyBand> frequencyBand, tinyxml2::XMLElement* a_node) ;
    bool extractCalPoints(std::shared_ptr<SRxFrequencyTable> frequencyTable, tinyxml2::XMLElement* a_node) ;

    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    std::shared_ptr<SRxCal>   mSRxCal;

    int mCalPath;
    std::vector<bool> mFirstTempPath;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;



};

}



#endif /* _MPLANE_ETNA_SRXCALDATA_H_ */
