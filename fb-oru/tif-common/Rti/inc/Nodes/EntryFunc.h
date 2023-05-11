/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Nodes/EntryFunc.h
 * \brief     "Directory" entry for RTI that implements a function
 *
 *
 * \details   Each directory entry of this type can be executed using it's predefined argument list. Must be derived from.
 *
 */


#ifndef RTIDIRFUNC_H_
#define RTIDIRFUNC_H_

#include <string>
#include "DataVariant.h"
#include "Nodes/RtiDirEntry.h"

namespace Mplane {

/**
 * Class containing the information for a single directory entry
 */
struct EntryFunc : public RtiDirEntry
{
public:
    EntryFunc( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
			IRtiMsgParser& msgParser, IRtiSettings& settings);
    virtual ~EntryFunc();

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

protected:

    /**
     * Execute the function
     * @return reply string
     */
    virtual std::string operator()(const std::string& functionName) = 0 ;

protected:
    DataVariantList *callVarList;	//<! List of arguments created from XML specification
    DataVariantList *returnVarList;	//<! List of return values created from XML specification
};


}
#endif /* RTIDIRFUNC_H_ */
