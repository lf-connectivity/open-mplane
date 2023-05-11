/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISRxCalData.h
 * \brief     Virtual interface for RX calibration data
 *
 *
 * \details
 *
 */


#ifndef ISRXCALDATA_H_
#define ISRXCALDATA_H_

#include <memory>
#include "ICalData.h"

namespace Mplane {

class ISRxOpenLoop ;

class ISRxCalData : public ICalData {
public:
	ISRxCalData() {}
	virtual ~ISRxCalData() {}

    /**
     * Method used to get access to the Tx open loop calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<ISRxOpenLoop> getSRxOpenLoop( int path ) =0 ;


} ;

/**
 * Class that manages multiple calibration objects, in particular the RX calibration object
 */
class ISRxCalDataContainer {
public:
	ISRxCalDataContainer(){}
	virtual ~ISRxCalDataContainer(){}

	/**
	 * Get the ISRxCalData object instance
	 */
    virtual std::shared_ptr<ISRxCalData> getSRxCal() =0 ;
};

}

#endif /* ISRXCALDATA_H_ */
