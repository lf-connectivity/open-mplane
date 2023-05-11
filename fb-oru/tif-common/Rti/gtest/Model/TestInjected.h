/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestInjected.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTINJECTED_H_
#define TESTINJECTED_H_

#include <string>
#include <vector>
#include <memory>
#include "ITif.h"
#include "IRtiMsgParser.h"
#include "Nodes/EntryFunc.h"

namespace Mplane {

/*!
 * \class TestInjected
 */
class TestInjected: public virtual ITifEntry, public EntryFunc {
public:

	/**
	 * Special constructor - only to be used for calling the static registerMethods()
	 */
	TestInjected();

	TestInjected( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~TestInjected();

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

	/**
	 * Called by ITif::inject() to get this object to add it's entries
	 * @param tif
	 * @return true if ok
	 */
	virtual bool registerEntry(ITif* tif) override ;

protected:

    virtual std::string operator()(const std::string& functionName) ;

	/**
	 * Called with:
	 *   [INT tx]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void abort( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void apiVersion( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   [INT tx]
	 *   [ENUM(X:Z:RAW) src]
	 *   [ENUM(OFF:ON) decimation]
	 *   [INT level]
	 *   [INT i]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void capture( DataVariantList *callList, DataVariantList *returnList );

};

}
#endif /* TESTINJECTED_H_ */
