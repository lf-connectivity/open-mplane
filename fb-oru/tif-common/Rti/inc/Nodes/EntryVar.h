/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Nodes/EntryVar.h
 * \brief     "Directory" entry implementing a variable for RTI
 *
 *
 * \details   Each directory entry is represented as a DataVariant variable that will be shown for 'ls' commands. The
 * underlying function handles setting/getting the variable value. Must be derived from.
 *
 */

#ifndef RTIDIRVAR_H_
#define RTIDIRVAR_H_

#include <string>
#include <memory>
#include "DataVariant.h"
#include "Nodes/EntryFunc.h"

namespace Mplane {

struct EntryVar : public EntryFunc
{
public:
	/**
	 * Constructor - creates a local DataVariant of the correct type
	 * @param pathname	Pathname to directory location
	 * @param varType	DataVariant type
	 * @param comment	Optional comment
	 */
    EntryVar(const std::string& pathname, const std::string& varType, const std::string& comment,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    /**
     * Constructor - uses the passed in DataVariant
	 * @param pathname	Pathname to directory location
     * @param data		Shared pointer to the DataVariant
	 * @param comment	Optional comment
     */
    EntryVar(const std::string& pathname, std::shared_ptr<DataVariant> data, const std::string& comment,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);


    virtual ~EntryVar();

    /**
     * Process the ls command for this device/class
     * @return ls string
     */
    virtual std::string ls();

protected:
    std::string operator()(const std::string& name) ;

    void setData(const std::string& value) ;
    const std::string getTypeStr() ;

    static std::string setCallFields(const std::string& varType);
    static std::string setReturnFields(const std::string& varType);
    static const std::string& valueStr() ;



private:
    /**
     * Data - either created with this object, or passed in from outside
     */
    std::shared_ptr<DataVariant>	mData ;
};


}
#endif /* RTIDIRFUNC_H_ */
