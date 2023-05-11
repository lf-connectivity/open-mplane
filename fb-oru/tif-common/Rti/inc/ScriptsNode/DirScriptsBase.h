/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ScriptsNode/DirScriptsBase.h
 * \brief     Base class for a directory entry for RTI scripts
 *
 *
 * \details   Provides simple help/ls support for scripts directories
 *
 */


#ifndef RTIDIRSCRIPTSBASE_H_
#define RTIDIRSCRIPTSBASE_H_

#include "Nodes/DirClass.h"

namespace Mplane {

/**
 * Class containing the information for a single directory entry for the scripts
 */
class DirScriptsBase : public DirClass
{
public:
	typedef DirClass super ;

	DirScriptsBase(const std::string& pathname, const std::string& comment,
			IRtiMsgParser& msgParser, IRtiSettings& settings );
    virtual ~DirScriptsBase();

    /**
     * Process the help command for this device/class
     * @return help string
     */
    virtual std::string help();

    /**
     * Process the ls command for this device/class
     * @return ls string
     */
    virtual std::string ls();

};


}
#endif /* RTIDIRSCRIPTSBASE_H_ */
