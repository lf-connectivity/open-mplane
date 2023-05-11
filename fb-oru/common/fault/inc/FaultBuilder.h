/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultBuilder.h
 * \brief     Creates and stores IFaultPackage objects (creating the faults for the application)
 *
 *
 * \details
 *
 */


#ifndef FAULTBUILDER_H_
#define FAULTBUILDER_H_

#include <vector>

#include "IFaultBuilder.h"
#include "IFaultPackage.h"

namespace Mplane {

class FaultBuilder : public IFaultBuilder
{
public:
	FaultBuilder() ;
	virtual ~FaultBuilder() ;

protected:
	/**
	 * Derived objects use this method to create and store new IFaultPackage objects
	 * @param package
	 */
	virtual void addFaultPackage(std::shared_ptr<IFaultPackage> package) override ;

private:
	std::vector<std::shared_ptr<IFaultPackage>> mPackages ;
} ;

}

#endif /* FAULTBUILDER_H_ */
