/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgcCal.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef RXAGCCAL_H_
#define RXAGCCAL_H_

#include "RxCal.h"

namespace Mplane {

class RxAgcCal : public RxCal {
public:
	RxAgcCal(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator) ;
	virtual ~RxAgcCal() ;

} ;

}

#endif /* RXAGCCAL_H_ */
