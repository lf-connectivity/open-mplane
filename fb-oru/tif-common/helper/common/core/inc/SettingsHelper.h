/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SettingsHelper.h
 * \brief     Set up common limits settings
 *
 *
 * \details   Application settings objects (where the limits settings are defined) can use this object
 * 			  to initialise the common settings to the runtime values derived from this application's IRadio etc
 *
 */


#ifndef SETTINGSHELPER_H_
#define SETTINGSHELPER_H_


namespace Mplane {

class SettingsHelper {
public:
	SettingsHelper() ;
	virtual ~SettingsHelper() ;

	/**
	 * Set the common settings variables for an application
	 */
	static void commonSettings() ;

} ;

}

#endif /* SETTINGSHELPER_H_ */
