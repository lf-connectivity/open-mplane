/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri1SapDefectIndFaultMajor.h
 * \brief     CPRI1 Service Access Point Defect Indication fault major
 *
 *
 * \details
 *
 */


#ifndef CPRI1_SAP_DEFECT_IND_FAULT_MAJOR_H_
#define CPRI1_SAP_DEFECT_IND_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Cpri1SapDefectIndFaultMajor : public Fault
{
public:
	Cpri1SapDefectIndFaultMajor() ;
	virtual ~Cpri1SapDefectIndFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* CPRI1_SAP_DEFECT_IND_FAULT_MAJOR_H_ */
