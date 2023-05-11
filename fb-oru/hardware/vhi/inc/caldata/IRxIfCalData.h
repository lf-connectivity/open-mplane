/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRxIfCalData.h
 * \brief     Virtual interface for RX IF calibration data
 *
 *
 * \details
 *
 */


#ifndef IRXIFCALDATA_H_
#define IRXIFCALDATA_H_

#include <memory>
#include "ICalData.h"

namespace Mplane {

/**
 * Class containing RX IF calibration information
 */

class IRxIfResponse ;

class IRxIfCalData : public ICalData {
public:
	IRxIfCalData() {}
	virtual ~IRxIfCalData() {}

    /**
     * Method used to get access to the Rx IF response calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<IRxIfResponse> getRxIfResponse( int path ) =0 ;


} ;

/**
 * Class that manages multiple calibration objects, in particular the RX IF calibration object
 */
class IRxIfCalDataContainer {
public:
	IRxIfCalDataContainer(){}
	virtual ~IRxIfCalDataContainer(){}

	/**
	 * Get the IRxIfCalData object instance
	 */
    virtual std::shared_ptr<IRxIfCalData> getRxIfCal() =0 ;
};


}

#endif /* IRXIFCALDATA_H_ */
