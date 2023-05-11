/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Nodes/TestReadVar.h
 * \brief     "Directory" entry implementing a variable with get method calls for RTI
 *
 *
 * \details   Creates a directory node variable that just reads an underlying (read only) "variable" via access methods
 *
 */

#ifndef RTITESTREADVAR_H_
#define RTITESTREADVAR_H_

#include "Nodes/TestVar.h"

namespace Mplane {

struct TestReadVar : public TestVar
{
public:
	typedef TestVar super ;

	typedef TestVar::Getter Getter ;

	/**
	 * Constructor - creates a local DataVariant of the correct type
	 * @param pathname	Pathname to directory location
	 * @param varType	DataVariant type
	 * @param comment	Optional comment
	 */
    TestReadVar(const std::string& pathname, const std::string& varType, const std::string& comment,
    		Getter getMethod,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~TestReadVar();

protected:
    std::string operator()(const std::string& name) ;

};

}
#endif /* RTITESTREADVAR_H_ */
