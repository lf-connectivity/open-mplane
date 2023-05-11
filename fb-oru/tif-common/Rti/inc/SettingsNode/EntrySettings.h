#ifndef _RTIFUNCTIONSETTINGSS_H_
#define _RTIFUNCTIONSETTINGS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SettingsNode/EntrySettings.h
 * \brief     Function handler for 'tif:settings'
 *
 *
 * \details   Function handler for the special device 'tif:settings' which supports setting/getting test interface settings
 * variables
 *
 */

#include "DataVariant.h"
#include "IRtiMsgParser.h"
#include "IRtiSettings.h"
#include "Nodes/EntryFunc.h"

namespace Mplane {

/**
 * Class containing all of the functions for a particular class or "device"
 */
class EntrySettings : public EntryFunc
{
public:
	typedef EntryFunc super ;

	EntrySettings(const std::string& pathname, const std::string& callFields,
			const std::string& returnFields, const std::string& comment,
			IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~EntrySettings();

    /**
     * Register all the directory entries for this class
     * @param msgParser
     * @param settings
     */
    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

};

}
#endif /* _RTIFUNCTIONSETTINGS_H_ */
