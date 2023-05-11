/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Nodes/TestWriteVar.h
 * \brief     "Directory" entry implementing a write-only variable with set method calls for RTI
 *
 *
 * \details   Creates a directory node variable that writes an underlying "variable" via access method
 *
 */

#ifndef RTITESTWRITEVAR_H_
#define RTITESTWRITEVAR_H_

#include "Nodes/EntryFunc.h"
#include "Nodes/EntryVar.h"

namespace Mplane {

struct TestWriteVar : public EntryVar
{
public:
	typedef EntryVar super ;

	typedef bool (*Setter)(const std::string& pathname, DataVariant *setVal, DataVariantList *returnList) ;

	/**
	 * Constructor - creates a local DataVariant of the correct type
	 * @param pathname	Pathname to directory location
	 * @param varType	DataVariant type
	 * @param comment	Optional comment
	 */
    TestWriteVar(const std::string& pathname, const std::string& varType, const std::string& comment,
    		Setter setMethod,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~TestWriteVar();

protected:
    std::string operator()(const std::string& name) ;

    void setValue();

protected:
    std::string mPathname ;

    /**
     * Keep get/set methods
     */
    Setter mSetMethod;
};


}
#endif /* RTITESTWRITEVAR_H_ */
