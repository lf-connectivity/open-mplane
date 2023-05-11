/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAlarmPackage.h
 * \brief     Interface to class which packages up alarm and fault(s)
 *
 *
 * \details   Every IALarm must be managed be associated with one or more faults. This class creates a single object that an application can
 * 				create to add an alarm with the appropriate fault(s).
 *
 */


#ifndef IALARMPACKAGE_H_
#define IALARMPACKAGE_H_

#include <memory>
#include <set>

namespace Mplane {

// forward
class IAlarm ;

/**
 * This class defined an interface for the concept of an alarm package - this class is deprecated
 *
 * @note Deprecated
 *
 */
class IAlarmPackage {
public:
	IAlarmPackage() {}
	virtual ~IAlarmPackage() {}

protected:
	/**
	 * Derived objects use this method to associate faults with the new IAlarm object
	 * @param alarm
	 */
	virtual void addAlarm(std::shared_ptr<IAlarm> alarm, const std::set<std::string>& names) =0 ;
} ;

}

#endif /* IALARMPACKAGE_H_ */
