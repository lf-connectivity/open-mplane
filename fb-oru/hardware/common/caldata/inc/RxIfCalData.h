#ifndef _RXIFCALDATA_H_
#define _RXIFCALDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxIfCalData.h
 * \brief     RX IF calibration object
 *
 *
 * \details
 *
 */
#include <vector>

#include "libtinyxml2/tinyxml2.h"
#include "Power.h"
#include "Temperature.h"
#include "FrequencyOffset.h"
#include "CommonCalBase.h"

#include "ICalDownload.h"
#include "IRxIfCalData.h"

#include "RxIfCal.h"

namespace Mplane
{

class RxIfCalData: public CommonCalBase, public IRxIfCalData
{
public:
    explicit RxIfCalData( std::shared_ptr<ICalDownload> calDownLoad );

    virtual ~RxIfCalData();


    /**
     * Method implemented to fulfil the Loggable public interface contract.
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
    virtual std::shared_ptr<IRxIfResponse> getRxIfResponse( int path ) override ;

protected:
    virtual std::shared_ptr<RxIfCal> createRxIfCal(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator) ;

protected:
    bool parseRxIfCal(tinyxml2::XMLElement* node) ;
    bool extractRxIfResponse(std::shared_ptr<RxIfCal> mRxIfCal, tinyxml2::XMLElement* a_node) ;
    bool extractOffsetFrequency(std::shared_ptr<RxIfResponse> rxIfResponse, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyOffsetTable(std::shared_ptr<RxIfOffsetFrequency> offsetFrequency, tinyxml2::XMLElement* a_node) ;
    bool extractCalPoints(std::shared_ptr<RxIfFrequencyOffsetTable> frequencyTable, tinyxml2::XMLElement* a_node) ;

    // Map of attributes
    using AttrMap = std::map<std::string, std::string> ;
//    typedef AttrMap::iterator AttrMapIterator ;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;

// Protected for testbench access
protected:
    std::shared_ptr<ICalDownload> mCalDownload;

    /**
     * This is set to the full path of the cal file for this cal data handler type in the constructor
     * using the ICalDownload implementation passed to it by the calibration data manager.
     */
    std::string mCalFilePath;
    std::shared_ptr<RxIfCal>   mRxIfCal;
};

}



#endif /* _RXIFCALDATA_H_ */
