#ifndef _COMMON_PAMCALDATA_H_
#define _COMMON_PAMCALDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PamCalData.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "libtinyxml2/tinyxml2.h"
#include "CommonCalBase.h"
#include <memory>
#include "ICalDownload.h"
#include "IPamCalData.h"

#include "PamCal.h"

namespace Mplane
{

class PamCalData: public CommonCalBase, public IPamCalData
{
public:
    friend class PamCalTestCase;

    explicit PamCalData(std::shared_ptr<ICalDownload> calDownLoad);

    virtual ~PamCalData();

    /**
     * Method implemented to fulfil the GeneralLog public interface contract.
     */
    virtual void show();

    /**
     * Method called during initialisation to load the calibration data from file
     * @return
     */
    virtual ReturnType::State load();

    /**
     * Method used to get access to the PaGainStep calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<IPaGainStep> getPaGainStep( int path ) override ;


protected:
    // Typedefs.............
    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;

    bool parsePamCal(tinyxml2::XMLElement* node) ;
    bool extractPaGainStep(std::shared_ptr<PamCal> pamCal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequencyTable(std::shared_ptr<PaGainStep> paGainStep, tinyxml2::XMLElement* a_node) ;
    bool extractPowerBand(std::shared_ptr<PgsFrequencyTable> frequencyTable, tinyxml2::XMLElement* a_node) ;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;

    std::shared_ptr<ICalDownload> mCalDownload;

    /**
     * Set to the full path of the cal file for this object
     */
    std::string mCalFilePath;

    std::shared_ptr<PamCal>  mPamCal;

};

}



#endif /* _COMMON_PAMCALDATA_H_ */
