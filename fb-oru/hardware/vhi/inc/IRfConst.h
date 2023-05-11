/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRfConst.h
 * \brief     Constants used in RF calculations
 *
 *
 * \details
 *
 */


#ifndef IRFCONSTANTS_H_
#define IRFCONSTANTS_H_

#include <memory>
#include "Power.h"

namespace Mplane {

class IRfConst {
public:
	IRfConst() {}
	virtual ~IRfConst() {}

	/**
	 * Gain provided in the system by DDC
	 */
	virtual Power getSystemDdcGain() const =0 ;

	/**
	 * Digital gain applied after carrier RSSI
	 */
	virtual Power getCarrierRssiGain() const =0 ;


} ;


class IRfConstFactory
{
public:
    /**
     * Method implements a factory that uses the radio board type to
     * select and return an instance of a RF constant class
     * that implements the IRfConstanst interface.
     * @return a reference to this radios receive frequency constant data.
     */
    static std::shared_ptr<IRfConst> getInterface();

};

}

#endif /* IRFCONSTANTS_H_ */
