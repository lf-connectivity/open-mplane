/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRxAgcCalData.h
 * \brief     Virtual interface for RX AGC calibration data
 *
 *
 * \details
 *
 */


#ifndef IRXAGCCALDATA_H_
#define IRXAGCCALDATA_H_

#include <memory>
#include <vector>
#include "Power.h"

#include "ICalData.h"

namespace Mplane {

/**
 * Class containing RX AGC calibration information
 */
class IRxAgcCalData : public ICalData {
public:
	IRxAgcCalData() {}
	virtual ~IRxAgcCalData() {}

    /**
     * Returns the list of CG steps derived from the cal data
     * @return list of CG steps
     */
    virtual std::vector<Power> getCgSteps(int path) =0 ;


    /**
     * Returns the list of CG steps derived from the step size and the number of levels
     * @return list of CG steps
     */
    virtual std::vector<Power> getCgSteps(int path, unsigned int numLevels,
    		double attenuationStep = 6.0) =0 ;


} ;


/**
 * Class that manages multiple calibration objects, in particular the RX AGC calibration object
 */
class IRxAgcCalDataContainer {
public:
	IRxAgcCalDataContainer(){}
	virtual ~IRxAgcCalDataContainer(){}

	/**
	 * Get the IRxAgcCalData object instance
	 */
    virtual std::shared_ptr<IRxAgcCalData> getRxAgcCal() =0 ;
};

}

#endif /* IRXAGCCALDATA_H_ */
