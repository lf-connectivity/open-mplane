#ifndef _ENTRYCMD_H_
#define _ENTRYCMD_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CmdNode/EntryCmd.h
 * \brief     Builtin command handler
 *
 *
 * \details   Creates a hidden directory containing all of the builtin commands
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
class EntryCmd : public EntryFunc
{
public:
	typedef EntryFunc super ;

	EntryCmd(const std::string& pathname, const std::string& callFields,
			const std::string& returnFields, const std::string& comment,
			IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~EntryCmd();

    /**
     * Create an instance of this object for each entry in the directory
     * @param msgParser
     * @param settings
     */
    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

    /**
     * Returns the path to the hidden builtins directory
     */
    static std::string getBuiltinDir() ;

    /**
     * Takes a raw builtin command and creates the full path to the command
     * @param cmd
     * @return commad full path
     */
    static std::string getBuiltinCommand(const std::string& cmd) ;

protected:

    /**
     * Hook called to process the function
     * @param funcEntry	Pointer to a function
     * @return reply string
     */
    virtual std::string operator()(const std::string& functionName) ;

private:
    std::string cmdCd() ;
    std::string cmdLs() ;
    std::string cmdHelp() ;
    std::string cmdSu() ;
    std::string cmdMemory() ;
    std::string cmdQuit() ;
    std::string cmdSleep() ;

private:
    std::string mPassword ;
    static std::string mBuiltinCommandHelp ;
};

}
#endif /* _ENTRYCMD_H_ */
