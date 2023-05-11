/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRxCalData.h
 * \brief     Virtual interface for RX calibration data
 *
 *
 * \details
 *
 */


#ifndef IRXCALDATA_H_
#define IRXCALDATA_H_

#include <memory>
#include "ICalData.h"

namespace Mplane {

/**
 * Class containing RX calibration information
 */

class IRxOpenLoop ;

class IRxCalData : public ICalData {
public:
	IRxCalData() {}
	virtual ~IRxCalData() {}

    /**
     * Method used to get access to the Rx open loop calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<IRxOpenLoop> getRxOpenLoop( int path ) =0 ;


} ;

/**
 * Class that manages multiple calibration objects, in particular the RX calibration object
 */
class IRxCalDataContainer {
public:
	IRxCalDataContainer(){}
	virtual ~IRxCalDataContainer(){}

	/**
	 * Get the IRxCalData object instance
	 */
    virtual std::shared_ptr<IRxCalData> getRxCal() =0 ;
};


}

#endif /* IRXCALDATA_H_ */
