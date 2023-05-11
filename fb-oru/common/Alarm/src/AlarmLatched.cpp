/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmLatched.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "AlarmLatched.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AlarmLatched::AlarmLatched(const std::string& name, const std::string& description) :
	Alarm(name, "LATCHED", description)
{
}

//-------------------------------------------------------------------------------------------------------------
AlarmLatched::AlarmLatched(const std::string& name, const std::string& description, IAlarm::AlarmSeverity severity) :
	Alarm(name, "LATCHED", description, severity)
{
}

//-------------------------------------------------------------------------------------------------------------
AlarmLatched::~AlarmLatched()
{
}

//-------------------------------------------------------------------------------------------------------------
void AlarmLatched::update(IFault& subject)
{
	logDebugNormal("%s %s: %s %s", getName().c_str(), __func__,
		subject.getName().c_str(), subject.getFaultPresentString().c_str()
	);

	// Only set the alarm if any Fault is present
	for (auto obs : getObservers())
	{
		std::shared_ptr<IFault> fault( obs->getSubject() ) ;
		if (fault->isFaultPresent())
		{
			Alarm::setRootCause( fault->getName() );
			setStatus(true);
			return ;
		}
	}
}
