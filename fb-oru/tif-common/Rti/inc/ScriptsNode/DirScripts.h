/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ScriptsNode/DirScripts.h
 * \brief     Directory entry for RTI scripts
 *
 *
 * \details   Container for the scripts. This class just modifies the default help slightly
 *
 */


#ifndef RTIDIRSCRIPTS_H_
#define RTIDIRSCRIPTS_H_

#include <mutex>

#include "ScriptsNode/DirScriptsBase.h"
#include "ScriptsNode/EntryScripts.h"

namespace Mplane {

/**
 * Class containing the information for a single directory entry for the scripts
 */
class DirScripts : public DirScriptsBase
{
public:
	typedef DirScriptsBase super ;
	typedef EntryScripts::ScriptInfo ScriptInfo ;

    DirScripts(IRtiMsgParser& msgParser, IRtiSettings& settings );
    virtual ~DirScripts();

    /**
     * Insert this object into the directory tree
     * @param msgParser
     * @param settings
     */
    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

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

private:
    /**
     * Set up the scripts tree
     */
    void updateScripts() ;

    /**
     * Read the directory to get a list of scripts
     * @param directory
     * @return list of script information
     */
    std::vector< ScriptInfo > getScripts(const std::string& directory) ;

    /**
     * Determine whether the any new scripts have been added (or removed) to the scripts directory
     * @param directory
     * @return true if changed
     */
    bool scriptsChanged(const std::string& directory) ;

    /**
     * Convert an OS file path into script name
     * @param directory	Scripts OS directory
     * @param path	Script OS file path
     * @return pair of strings: first is internal DirNode path, second is script name
     */
    std::pair<std::string, std::string> scriptPathToName(const std::string& directory, const std::string& path) ;

    /**
     * Read the first comment from a script file
     * @param filePath
     * @return comment string
     */
    std::string readComment(const std::string& filePath) ;

    /**
     * Reads an OS directory finding any files (optionally filtered by file extension)
     * @param directory
     * @param extension
     * @return list of file paths
     */
    std::vector< std::string > findFiles(const std::string& directory, const std::string& extension) ;

    /**
     * Creates a DirNode path of script containers
     * @param path		Path to add
     * @return true if added ok
     */
    bool makePath(const std::string& path);


private:
    // used to sort ScriptInfos by path
    struct ByPath {
    	bool operator()(ScriptInfo a, ScriptInfo b)
    	{
    		return a.osPath < b.osPath ;
    	}
    } ;

    /**
     * List of script info
     */
    std::vector< ScriptInfo > mScripts ;

    /**
     * Map from script name to a pointer to the script info in the scripts list
     */
    std::map<std::string, const ScriptInfo*> mScriptsMap ;

    std::mutex mReaddirMutex ;
};


}
#endif /* RTIDIRSCRIPTS_H_ */
