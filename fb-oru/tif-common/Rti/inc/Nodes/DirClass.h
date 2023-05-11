/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Nodes/DirClass.h
 * \brief     "Directory" entry for RTI
 *
 *
 * \details   Directory consists of class "directories", containing function/variable function "files". All entries are
 * derived from this common base class
 *
 */


#ifndef RTIDIRCLASS_H_
#define RTIDIRCLASS_H_

#include "Nodes/RtiDirEntry.h"

namespace Mplane {

/**
 * Class containing the information for a single directory entry
 */
class DirClass : public RtiDirEntry
{
public:
    DirClass( const std::string& pathname, const std::string& comment,
    		IRtiMsgParser& msgParser, IRtiSettings& settings );
    virtual ~DirClass();

    /**
     * Hook called to process the function
     * @param args	String containing function call arguments
     * @return reply string
     */
    virtual std::string processFunc(const std::string& args) ;

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

    /**
     * Output a help title and the help information for each entry iff there are any entries. Shows the name and comment
     * @param title
     * @param entryList
     * @return help string
     */
    std::string showSimpleHelp(const std::string& title, const std::vector< RtiDirEntry* >& entryList);


protected:
    /**
     * Split the directory contents into 3 lists: variables, functions, and classes. Each list is then sorted by name
     * @param varList
     * @param classList
     * @param funcList
     */
    void sortContents(
    		std::vector< RtiDirEntry* >& varList,
    		std::vector< RtiDirEntry* >& classList,
    		std::vector< RtiDirEntry* >& funcList) ;

    /**
     * Output a help title and the help information for each entry iff there are any entries. Calls the entry 'help' method
     * @param title
     * @param entryList
     * @return help string
     */
    std::string showSelfHelp(const std::string& title, const std::vector< RtiDirEntry* >& entryList);

    /**
     * Output the ls information for each entry iff there are any entries. Calls the entry 'ls' method
     * @param entryList
     * @return ls string
     */
    std::string showSelfLs(const std::vector< RtiDirEntry* >& entryList);

protected:
    std::string mVarTitle ;
    std::string mClassTitle ;
    std::string mFuncTitle ;
};


}
#endif /* RTIDIRCLASS_H_ */
