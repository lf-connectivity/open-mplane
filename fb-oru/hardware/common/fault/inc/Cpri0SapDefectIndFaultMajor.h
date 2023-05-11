/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0SapDefectIndFaultMajor.h
 * \brief     CPRI0 Service Access Point Defect Indication fault major
 *
 *
 * \details
 *
 */


#ifndef CPRI0_SAP_DEFECT_IND_FAULT_MAJOR_H_
#define CPRI0_SAP_DEFECT_IND_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Cpri0SapDefectIndFaultMajor : public Fault
{
public:
	Cpri0SapDefectIndFaultMajor() ;
	virtual ~Cpri0SapDefectIndFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* CPRI0_SAP_DEFECT_IND_FAULT_MAJOR_H_ */
