/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPamCalData.h
 * \brief     Virtual interface for PAM calibration data
 *
 *
 * \details
 *
 */


#ifndef IPAMCALDATA_H_
#define IPAMCALDATA_H_

#include <memory>
#include "ICalData.h"

namespace Mplane {

/**
 * Class containing PAM calibration information
 */

class IPaGainStep ;

class IPamCalData : public ICalData
{
public:
	IPamCalData() {}
	virtual ~IPamCalData() {}

    /**
     * Method used to get access to the PA Gain step calibration data for the given radio path.
     *
     * @param path
     * @return a reference to the calibration data interface.
     */
    virtual std::shared_ptr<IPaGainStep> getPaGainStep( int path ) = 0 ;


} ;

}  // namespace Mplane

#endif  // IPAMCALDATA_H_
