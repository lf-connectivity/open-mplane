#ifndef _ETNA_FTU_RxAgcCalDATA_H_
#define _ETNA_FTU_RxAgcCalDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgcCalData.h
 * \brief     RX AGC cal data interface
 *
 *
 * \details   Cal data interface for RX AGC
 *
 */
#include <vector>

#include "IRxAgcCalData.h"
#include "RxCalData.h"

namespace Mplane
{

class RxAgcCalData: public RxCalData, public IRxAgcCalData
{
public:
	explicit RxAgcCalData( std::shared_ptr<ICalDownload> calDownLoad );

    virtual ~RxAgcCalData();

    /**
     * Returns the list of CG steps derived from the step size and the number of levels
     * @return list of CG steps
     */
    virtual std::vector<Power> getCgSteps(int path, unsigned int numLevels,
    		double attenuationStep = 6.0) override ;

    /**
     * Returns the list of CG steps as a fixed table
     * @return list of CG steps
     */
    virtual std::vector<Power> getCgSteps(int path) override ;

protected:
    virtual std::shared_ptr<RxCal> createRxAgcCal(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator) ;

};

}



#endif /* _ETNA_FTU_RxAgcCalDATA_H_ */
