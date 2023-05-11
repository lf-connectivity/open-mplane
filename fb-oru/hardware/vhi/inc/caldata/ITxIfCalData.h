/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITxIfCalData.h
 * \brief     Virtual interface for RX IF calibration data
 *
 *
 * \details
 *
 */


#ifndef ITXIFCALDATA_H_
#define ITXIFCALDATA_H_

#include <memory>
#include "ICalData.h"

namespace Mplane {

/**
 * Class containing TX IF calibration information
 */

class ITxIfResponse ;

class ITxIfCalData : public ICalData {
public:
	ITxIfCalData() {}
	virtual ~ITxIfCalData() {}

    /**
     * Method used to get access to the Tx IF response calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<ITxIfResponse> getTxIfResponse( int path ) =0 ;


} ;

/**
 * Class that manages multiple calibration objects, in particular the RX IF calibration object
 */
class ITxIfCalDataContainer {
public:
	ITxIfCalDataContainer(){}
	virtual ~ITxIfCalDataContainer(){}

	/**
	 * Get the ITxIfCalData object instance
	 */
    virtual std::shared_ptr<ITxIfCalData> getTxIfCal() =0 ;
};


}

#endif /* ITXIFCALDATA_H_ */
