/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Fbzcu27MplaneOranrrhRxPortTestHandler.h
 * \brief     Test methods for FBZCU27-MPLANE-ORANRRH
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __FBZCU27MPLANEORANRRHRXPORTTESTHANDLER__H_
#define __FBZCU27MPLANEORANRRHRXPORTTESTHANDLER__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <vector>
#include <memory>
#include "RxPortTestHelper.h"
#include "ITif.h"
#include "IRtiMsgParser.h"
#include "Nodes/EntryFunc.h"

// Add any specific includes here %%-->

// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class Fbzcu27MplaneOranrrhRxPortTestHandler: public virtual ITifEntry, public EntryFunc
{
public:

	Fbzcu27MplaneOranrrhRxPortTestHandler( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~Fbzcu27MplaneOranrrhRxPortTestHandler();

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

	/**
	 * Special constructor - only to be used for calling the static registerMethods()
	 */
	Fbzcu27MplaneOranrrhRxPortTestHandler();

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
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   FLOAT result (dBFS)
	 *   INT raw
	 *
	 */
	void getAdcRms( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   FLOAT value (dB)
	 *
	 */
	void getExtFilterLoss( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   INT value (kHz)
	 *
	 */
	void getFreq( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   FLOAT value (dB)
	 *
	 */
	void getIfAtten( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   INT path
	 *
	 */
	void getPath( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   FLOAT value (dB)
	 *
	 */
	void getRfAtten( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   FLOAT rssiResult (dBm)
	 *
	 */
	void getRssi( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   FLOAT result (DegC)
	 *
	 */
	void getTemp( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *   ENUM(on:off:follow) mode
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setEnable( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *   FLOAT{0.0..3.0} value (dB)
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setExtFilterLoss( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *   FLOAT value (kHz)
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setFreq( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *   FLOAT value (dB)
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setIfAtten( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *   INT path
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setPath( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *   FLOAT value (dB)
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void setRfAtten( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT{1..${NUM_RX_PORTS}} index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void showSynth( DataVariantList *callList, DataVariantList *returnList );



	/**
	 * Getter method for read-only variable Ports
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void PortsGet(  const std::string& pathname, DataVariantList *returnList ) ;




// Add any extra methods %%-->

// <--%%

private:
	std::shared_ptr<RxPortTestHelper> mHelper ;
};



} // MPLANE

#endif /* __FBZCU27MPLANEORANRRHRXPORTTESTHANDLER__H_*/
