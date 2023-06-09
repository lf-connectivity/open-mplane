/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fbzcu27MplaneOranrrhFpgaTestHandler.h
 * \brief     Test methods for FBZCU27-MPLANE-ORANRRH
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __FBZCU27MPLANEORANRRHFPGATESTHANDLER__H_
#define __FBZCU27MPLANEORANRRHFPGATESTHANDLER__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <vector>
#include <memory>
#include "FpgaTestHelper.h"
#include "ITif.h"
#include "IRtiMsgParser.h"
#include "Nodes/EntryFunc.h"

// Add any specific includes here %%-->

// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class Fbzcu27MplaneOranrrhFpgaTestHandler: public virtual ITifEntry, public EntryFunc
{
public:

	Fbzcu27MplaneOranrrhFpgaTestHandler( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~Fbzcu27MplaneOranrrhFpgaTestHandler();

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

	/**
	 * Special constructor - only to be used for calling the static registerMethods()
	 */
	Fbzcu27MplaneOranrrhFpgaTestHandler();

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
	 *   UINT{0..1048575} Offset
	 *   [UINT{1..} Count]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   HEXINT[] Hex
	 *
	 */
	void read( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   UINT{0..1048575} Offset
	 *   UINT{0..65535} WriteValue
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void write( DataVariantList *callList, DataVariantList *returnList );






// Add any extra methods %%-->

// <--%%

private:
	std::shared_ptr<FpgaTestHelper> mHelper ;
};



} // MPLANE

#endif /* __FBZCU27MPLANEORANRRHFPGATESTHANDLER__H_*/
