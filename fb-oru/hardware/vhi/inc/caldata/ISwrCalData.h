/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISwrCalData.h
 * \brief     Virtual interface for reverse power measurement calibration data
 *
 *
 * \details
 *
 */


#ifndef ISWRCALDATA_H_
#define ISWRCALDATA_H_

#include <memory>
#include "ICalData.h"

namespace Mplane {

class ISwrOpenLoop;

class ISwrCalData : public ICalData {
public:
	ISwrCalData() {}
	virtual ~ISwrCalData() {}

    /**
     * Method used to get access to the Tx open loop calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<ISwrOpenLoop> getSwrOpenLoop( int path ) =0 ;


} ;

/**
 * Class that manages multiple calibration objects, in particular the RX calibration object
 */
class ISwrCalDataContainer {
public:
	ISwrCalDataContainer(){}
	virtual ~ISwrCalDataContainer(){}

	/**
	 * Get the ISwrCalData object instance
	 */
    virtual std::shared_ptr<ISwrCalData> getSwrCal() =0 ;
};

}

#endif /* ISWRCALDATA_H_ */
