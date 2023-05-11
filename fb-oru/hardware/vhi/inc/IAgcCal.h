/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAgcCal.h
 * \brief     Virtual interface to RX AGC cal data
 *
 *
 * \details
 *
 */


#ifndef IAGCCAL_H_
#define IAGCCAL_H_

#include <memory>

namespace Mplane {

class IAgcCal {
public:
	IAgcCal() {}
	virtual ~IAgcCal() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IAgcCal> getInstance() ;

	/**
	 * Get the list of CG steps to use in the AGC
	 * @return vector of CG step Powers
	 */
	virtual std::vector<Power> getCgSteps() const =0 ;

//	virtual bool getRfAtten( Frequency frequency, Power amplitude, Power &rfAtten ) const =0 ;
} ;

}

#endif /* IAGCCAL_H_ */
