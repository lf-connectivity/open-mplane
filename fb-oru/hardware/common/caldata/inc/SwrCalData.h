#ifndef _MPLANE__SWRCALDATA_H_
#define _MPLANE__SWRCALDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SwrCalData.h
 * \brief     Interface implementation for reverse power measurement calibration data
 *
 *
 * \details   Interface implementation for reverse power measurement calibration data
 *
 */
#include <vector>

#include "libtinyxml2/tinyxml2.h"
#include "Power.h"
#include "Temperature.h"
#include "Frequency.h"
#include "CommonCalBase.h"

#include "ICalDownload.h"
#include "ISwrCalData.h"

#include "SwrCal.h"

namespace Mplane
{

class SwrCalData: public CommonCalBase, public ISwrCalData
{
public:

    friend class SwrCalTestCase;

    explicit SwrCalData( std::shared_ptr<ICalDownload> calDownLoad );

    virtual ~SwrCalData();


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
    virtual std::shared_ptr<ISwrOpenLoop> getSwrOpenLoop( int path ) override;

protected:

    std::shared_ptr<ICalDownload> mCalDownload;

    /**
     * This is set to the full path of the cal file for this cal data handler type in the constructor
     * using the ICalDownload implementation passed to it by the calibration data manager.
     */
    std::string mCalFilePath;


    bool parseSwrCal(tinyxml2::XMLElement* node) ;
    bool extractSwrOpenLoop(std::shared_ptr<SwrCal> mSRxCal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyBand(std::shared_ptr<SwrOpenLoop> sRrxOpenLoop, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyTable(std::shared_ptr<SwrFrequencyBand> frequencyBand, tinyxml2::XMLElement* a_node) ;
    bool extractCalPoints(std::shared_ptr<SwrFrequencyTable> frequencyTable, tinyxml2::XMLElement* a_node) ;

    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    std::shared_ptr<SwrCal>   mSwrCal;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;



};

}



#endif /* _MPLANE_ETNA_SRXCALDATA_H_ */
