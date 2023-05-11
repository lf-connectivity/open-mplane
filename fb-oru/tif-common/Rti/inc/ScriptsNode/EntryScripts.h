#ifndef _RTIFUNCTIONSCRIPTS_H_
#define _RTIFUNCTIONSCRIPTS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EntryScripts.h
 * \brief     Function handler for 'tif:scripts'
 *
 *
 * \details   Function handler for the special device 'tif:scripts' which supports the execution of script files
 *
 */
#include <string>
#include <vector>
#include <map>

#include "DataVariant.h"
#include "IRtiMsgParser.h"
#include "IRtiSettings.h"
#include "Nodes/EntryFunc.h"

namespace Mplane {

/**
 * Class containing all of the functions for a particular class or "device"
 */
class EntryScripts : public EntryFunc
{
public:
	typedef EntryFunc super ;

    /**
     * An entry in the scripts vector
     */
    struct ScriptInfo {

    	ScriptInfo(const std::string& setOsPath, const std::string& setDir, const std::string& setName,
    			const std::string& setComment ) :
    		osPath(setOsPath),
    		dir(setDir),
    		name(setName),
    		comment(setComment)
    	{}
    	std::string osPath ;		//<! File path in OS
    	std::string dir ;			//<! Sub-directory in which to place this node
    	std::string name ;			//<! Script name
    	std::string comment ;		//<! Script comment
    };

	EntryScripts(const std::string& pathname, const std::string& callFields,
			const std::string& returnFields, const std::string& comment,
			IRtiMsgParser& msgParser, IRtiSettings& settings,
			const std::map<std::string, const ScriptInfo*>& scriptsMap);

    virtual ~EntryScripts();

protected:

    /**
     * Hook called to process the function
     * @param funcEntry	Pointer to a function
     * @return reply string
     */
    virtual std::string operator()(const std::string& functionName) ;

private:
    /**
     * Reads out the script file putting any nonspace / non-comment lines into a list
     * @param filePath
     * @return list of commands with their line number
     */
    std::vector< std::pair<std::string, unsigned> > readCommands(const std::string& filePath);


private:
    const std::map<std::string, const ScriptInfo*>& mScriptsMap ;
};

}
#endif /* _RTIFUNCTIONSCRIPTS_H_ */
