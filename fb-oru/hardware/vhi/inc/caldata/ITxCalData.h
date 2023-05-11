/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITxCalData.h
 * \brief     Virtual interface for TX RF calibration data
 *
 *
 * \details
 *
 */


#ifndef ITXCALDATA_H_
#define ITXCALDATA_H_

#include <memory>
#include "ICalData.h"

namespace Mplane {

/**
 * Class containing TX RF calibration information
 */

class ITxOpenLoop ;

class ITxCalData : public ICalData {
public:
	ITxCalData() {}
	virtual ~ITxCalData() {}

    /**
     * Method used to get access to the Tx open loop calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<ITxOpenLoop> getTxOpenLoop( int path ) =0 ;


} ;

/**
 * Class that manages multiple calibration objects, in particular the RX IF calibration object
 */
class ITxCalDataContainer {
public:
	ITxCalDataContainer(){}
	virtual ~ITxCalDataContainer(){}

	/**
	 * Get the ITxCalData object instance
	 */
    virtual std::shared_ptr<ITxCalData> getTxCal() =0 ;
};


}

#endif /* ITXCALDATA_H_ */
