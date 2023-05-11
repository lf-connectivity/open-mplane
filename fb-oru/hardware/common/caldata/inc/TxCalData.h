#ifndef _ETNA_FTU_TXCALDATA_H_
#define _ETNA_FTU_TXCALDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxCalData.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "libtinyxml2/tinyxml2.h"
#include "CommonCalBase.h"
#include "TxCal.h"
#include <memory>
#include "ICalDownload.h"
#include "ITxCalData.h"

namespace Mplane
{

class TxCalData: public CommonCalBase, public ITxCalData
{
public:
    friend class TxCalTestCase;

    explicit TxCalData(std::shared_ptr<ICalDownload> calDownLoad);

    virtual ~TxCalData();

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
    std::shared_ptr<ITxOpenLoop> getTxOpenLoop( int path );


protected:
    bool parseTxCal(tinyxml2::XMLElement* node) ;
    bool extractTxOpenLoop(std::shared_ptr<TxCal> mTxCal, tinyxml2::XMLElement* a_node) ;
    bool extractFrequecnyTable(std::shared_ptr<TxOpenLoop> txOpenLoop, tinyxml2::XMLElement* a_node) ;
    bool extractPowerBand(std::shared_ptr<FrequencyTable> frequencyTable, tinyxml2::XMLElement* a_node) ;
    bool extractCalPoints(std::shared_ptr<PowerBand> powerBand, tinyxml2::XMLElement* a_node) ;


    std::shared_ptr<ICalDownload> mCalDownload;

    /**
     * Set to the full path of the cal file for this object
     */
    std::string mCalFilePath;

    // Map of attributes
    typedef std::map<std::string, std::string> AttrMap ;
    typedef AttrMap::iterator AttrMapIterator ;


    std::shared_ptr<TxCal>   mTxCal;

    /**
     * Fill a map with the attributes
     * @param attrMap
     */
    void getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const ;
};

}



#endif /* _ETNA_FTU_TXCALDATA_H_ */
