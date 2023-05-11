/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFaultBuilder.h
 * \brief     Interface to class that creates faults
 *
 *
 * \details   The application will instantiate the IFaultBuilder singleton which will create all of the application's
 * 				faults (by creating all the required IFaultPackage objects). The final IFaultBuilder singleton may well
 * 				be part of an IFaultBuilder hierarchy, starting with common faults which will be in all applications,
 * 				progressing down through hardware-specific and application-specific faults
 *
 */


#ifndef IFAULTBUILDER_H_
#define IFAULTBUILDER_H_

#include <memory>

namespace Mplane {

// forward
class IFaultPackage ;

class IFaultBuilder {
public:
	IFaultBuilder() {}
	virtual ~IFaultBuilder() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IFaultBuilder> getInstance() ;

protected:
	/**
	 * Derived objects use this method to create and store new IFaultPackage objects
	 * @param package
	 */
	virtual void addFaultPackage(std::shared_ptr<IFaultPackage> package) =0 ;
} ;

}

#endif /* IFAULTBUILDER_H_ */
