/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CmdNode/DirCmd.h
 * \brief     Directory entry for RTI builtin commands
 *
 *
 * \details   Container for the builtin commands. This class just modifies the default help slightly
 *
 */


#ifndef RTIDIRCMDS_H_
#define RTIDIRCMDS_H_

#include "Nodes/DirClass.h"

namespace Mplane {

/**
 * Class containing the information for a single directory entry for the builtin commands
 */
class DirCmd : public DirClass
{
public:
    DirCmd( const std::string& pathname, const std::string& comment,
    		IRtiMsgParser& msgParser, IRtiSettings& settings );
    virtual ~DirCmd();

    /**
     * Process the help command for this device/class
     * @return help string
     */
    virtual std::string help();

};


}
#endif /* RTIDIRCMDS_H_ */
