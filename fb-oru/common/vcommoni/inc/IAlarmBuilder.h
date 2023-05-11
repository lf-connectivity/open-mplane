/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAlarmBuilder.h
 * \brief     Interface to class which builds all of the alarms
 *
 *
 * \details   The application will instantiate the IAlarmBuilder singleton which will create all of the application's
 * 				alarms (by creating all the required IAlarm objects). The final IlarmBuilder singleton may well
 * 				be part of an IAlarmBuilder hierarchy, starting with common Alarms which will be in all applications,
 * 				progressing down through hardware-specific and application-specific alarms
 *
 */


#ifndef IALARMBUILDER_H_
#define IALARMBUILDER_H_

#include <memory>

namespace Mplane {

// forward
class IAlarmPackage ;

/**
 * This IAlarmBuilder interface is deprecated
 *
 * @note Deprecated
 */
class IAlarmBuilder {
public:
	IAlarmBuilder() {}
	virtual ~IAlarmBuilder() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IAlarmBuilder> getInstance() ;

protected:
	/**
	 * Derived objects use this method to create and store new IAlarmPackage objects
	 */
	virtual void addAlarmPackage(std::shared_ptr<IAlarmPackage> package) =0 ;

} ;

}

#endif /* IALARMBUILDER_H_ */
