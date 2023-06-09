/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierTestHelper.h
 * \brief     Test helper for common
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __CARRIERTESTHELPER__H_
#define __CARRIERTESTHELPER__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <vector>
#include <memory>
#include "IRtiMsgParser.h"
#include "DataVariant.h"

// Add any specific includes here %%-->
#include "ICarrier.h"
#include "ITifIoctl.h"
// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class CarrierTestHelper
// Add any extra inheritance %%-->

// <--%%
{
public:

	// Add any class settings %%-->

	// <--%%

	// singleton
	static std::shared_ptr<CarrierTestHelper> getInstance() ;


	CarrierTestHelper();

    virtual ~CarrierTestHelper();

	/**
	 * Called with:
	 *   INT Index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void del( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT Index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   INT Index
	 *   ENUM(${CARRIER_TYPES}) Type
	 *   ENUM(${CARRIER_STATES}) State
	 *   ENUM(${CARRIER_SIGNALS}) SigType
	 *   FLOAT TxPower (dBm)
	 *   FLOAT TxFreq (kHz)
	 *   FLOAT RxFreq (kHz)
	 *   INT GroupUp
	 *   INT GroupDown
	 *   FLOAT TxScaling (dBm)
	 *   FLOAT UplinkNoise (dBm)
	 *   BOOL(off:on) Loopback
	 *   INT[] TxContainer
	 *   INT[] RxContainer
	 *   INT[] TxFibre
	 *   INT[] RxFibre
	 *   INT UlDlConfig
	 *   INT SSConfig
	 *   ENUM(normal:extended) UlPrefixLen
	 *   ENUM(normal:extended) DlPrefixLen
	 *   ENUM(NONE:1kHz25:3kHz75:5kHz:7kHz25:15kHz:30kHz:60kHz:120kHz:240kHz) ulScs
	 *   ENUM(NONE:1kHz25:3kHz75:5kHz:7kHz25:15kHz:30kHz:60kHz:120kHz:240kHz) dlScs
	 *   ENUM(NONE:256:512:1024:1536:2048:4096) ulFFT
	 *   ENUM(NONE:256:512:1024:1536:2048:4096) dlFFT
	 *   INT[] ulEAXCID
	 *   INT[] dlEAXCID
	 *   STRING ulMAC
	 *   ENUM(LTE:5GNR) mode
	 *   INT ulCp0Size
	 *   INT dlCp0Size
	 *   INT ulCp1Size
	 *   INT dlCp1Size
	 *
	 */
	void get( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT Index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *   FLOAT[] Rssi (dBm)
	 *
	 */
	void getRssi( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT Index
	 *   [ENUM(${CARRIER_TYPES}) Type]
	 *   [ENUM(${CARRIER_STATES}) State]
	 *   [ENUM(${CARRIER_SIGNALS}) SigType]
	 *   [FLOAT TxPower (dBm)]
	 *   [FLOAT TxFreq (kHz)]
	 *   [FLOAT RxFreq (kHz)]
	 *   [INT GroupUp]
	 *   [INT GroupDown]
	 *   [FLOAT TxScaling (dBm)]
	 *   [INT[] TxContainer]
	 *   [INT[] RxContainer]
	 *   [INT[] TxFibre]
	 *   [INT[] RxFibre]
	 *   [FLOAT UplinkNoise (dBm)]
	 *   [BOOL(off:on) Loopback]
	 *   [INT uldlConfig]
	 *   [INT ssConfig]
	 *   [ENUM(normal:extended) ulPrefixLen]
	 *   [ENUM(normal:extended) dlPrefixLen]
	 *   [ENUM(NONE:1.25KHZ:3.75KHZ:5KHZ:7.25KHZ:15KHZ:30KHZ:60KHZ:120KHZ:240KHZ) ulScs]
	 *   [ENUM(NONE:1.25KHZ:3.75KHZ:5KHZ:7.25KHZ:15KHZ:30KHZ:60KHZ:120KHZ:240KHZ) dlScs]
	 *   [ENUM(NONE:256:512:1024:1536:2048:4096) ulFFT]
	 *   [ENUM(NONE:256:512:1024:1536:2048:4096) dlFFT]
	 *   [INT[] ulEAXCID]
	 *   [INT[] dlEAXCID]
	 *   [STRING ulMAC]
	 *   [ENUM(LTE:5GNR) mode]
	 *   [INT ulCp0Size]
	 *   [INT dlCp0Size]
	 *   [INT ulCp1Size]
	 *   [INT dlCp1Size]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void set( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT Index
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void show( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	void showAll( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );



	/**
	 * Getter method for read-only variable NumCarriers
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void NumCarriersGet( const std::string& pathname, DataVariantList *returnList ) ;

	/**
	 * Getter method for read-only variable RxPaths
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void RxPathsGet( const std::string& pathname, DataVariantList *returnList ) ;

	/**
	 * Getter method for read-only variable TxPaths
	 *
	 * @param pathname Variable path name used as the variable name in the returnList
	 * @param returnList DataVariantList use to return variable value
	 *
	 */
	static void TxPathsGet( const std::string& pathname, DataVariantList *returnList ) ;




// Add any extra methods %%-->
private:
	static ICarrierSetter& getCarrierSetter(bool& ok, DataVariantList *callList, DataVariantList *returnList);
	static const ICarrier& getCarrier(bool& ok, DataVariantList *callList, DataVariantList *returnList);
	static bool checkState(bool ok, const std::string& param, DataVariantList *returnList) ;
//	std::shared_ptr<ITifIoctl> getChainWorker() const ;

// <--%%

};



// Add any Mplane namespace code here %%-->

// <--%%


} // Mplane

// Add any global namespace code here %%-->

// <--%%


#endif /* __CARRIERTESTHELPER__H_*/
