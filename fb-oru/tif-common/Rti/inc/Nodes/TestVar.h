/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Nodes/TestVar.h
 * \brief     "Directory" entry implementing a variable with set/get method calls for RTI
 *
 *
 * \details   Creates a directory node variable that reads & writes an underlying "variable" via access methods
 *
 */

#ifndef RTITESTVAR_H_
#define RTITESTVAR_H_

#include "Nodes/EntryFunc.h"
#include "Nodes/EntryVar.h"

namespace Mplane {

struct TestVar : public EntryVar
{
public:
	typedef EntryVar super ;

	typedef bool (*Setter)(const std::string& pathname, DataVariant *setVal, DataVariantList *returnList) ;
	typedef void (*Getter)(const std::string& pathname, DataVariantList *returnList) ;

	/**
	 * Constructor - creates a local DataVariant of the correct type
	 * @param pathname	Pathname to directory location
	 * @param varType	DataVariant type
	 * @param comment	Optional comment
	 */
    TestVar(const std::string& pathname, const std::string& varType, const std::string& comment,
    		Getter getMethod, Setter setMethod,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~TestVar();

    /**
     * Process the ls command for this device/class
     * @return ls string
     */
    virtual std::string ls();

protected:
    std::string operator()(const std::string& name) ;

    void getValue();
    void setValue();

protected:
    std::string mPathname ;

    /**
     * Keep get/set methods
     */
    Getter mGetMethod;
    Setter mSetMethod;
};


}
#endif /* RTITESTVAR_H_ */
