/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111MplaneOranrrhCarrierTestHandler.cpp
 * \brief     Test methods for ZCU111-MPLANE-ORANRRH
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run)
 *
 * Add any file header comments here %%-->

 * <--%%
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Nodes/RtiDirEntry.h"
#include "Nodes/TestVar.h"
#include "Nodes/TestReadVar.h"
#include "Nodes/TestWriteVar.h"
#include "Nodes/DirClass.h"
#include "RtiKeyword.h"
#include "Zcu111MplaneOranrrhCarrierTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/carrier", "Carrier settings functions", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhCarrierTestHandler("/carrier/del",
			"INT Index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Unconfigure all carrier parameters",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhCarrierTestHandler("/carrier/get",
			"INT Index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],INT Index,ENUM(${CARRIER_TYPES}) Type,ENUM(${CARRIER_STATES}) State,ENUM(${CARRIER_SIGNALS}) SigType,FLOAT TxPower (dBm),FLOAT TxFreq (kHz),FLOAT RxFreq (kHz),INT GroupUp,INT GroupDown,FLOAT TxScaling (dBm),FLOAT UplinkNoise (dBm),BOOL(off:on) Loopback,INT[] TxContainer,INT[] RxContainer,INT[] TxFibre,INT[] RxFibre,INT UlDlConfig,INT SSConfig,ENUM(normal:extended) UlPrefixLen,ENUM(normal:extended) DlPrefixLen,ENUM(NONE:1kHz25:3kHz75:5kHz:7kHz25:15kHz:30kHz:60kHz:120kHz:240kHz) ulScs,ENUM(NONE:1kHz25:3kHz75:5kHz:7kHz25:15kHz:30kHz:60kHz:120kHz:240kHz) dlScs,ENUM(NONE:256:512:1024:1536:2048:4096) ulFFT,ENUM(NONE:256:512:1024:1536:2048:4096) dlFFT,INT[] ulEAXCID,INT[] dlEAXCID,STRING ulMAC,ENUM(LTE:5GNR) mode,INT ulCp0Size,INT dlCp0Size,INT ulCp1Size,INT dlCp1Size",
			"Get current carrier parameters",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhCarrierTestHandler("/carrier/getRssi",
			"INT Index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],FLOAT[] Rssi (dBm)",
			"For the carrier selected by Index get the RSSI for each RX port that may be associated with that carrier",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhCarrierTestHandler("/carrier/set",
			"INT Index,[ENUM(${CARRIER_TYPES}) Type],[ENUM(${CARRIER_STATES}) State],[ENUM(${CARRIER_SIGNALS}) SigType],[FLOAT TxPower (dBm)],[FLOAT TxFreq (kHz)],[FLOAT RxFreq (kHz)],[INT GroupUp],[INT GroupDown],[FLOAT TxScaling (dBm)],[INT[] TxContainer],[INT[] RxContainer],[INT[] TxFibre],[INT[] RxFibre],[FLOAT UplinkNoise (dBm)],[BOOL(off:on) Loopback],[INT uldlConfig],[INT ssConfig],[ENUM(normal:extended) ulPrefixLen],[ENUM(normal:extended) dlPrefixLen],[ENUM(NONE:1.25KHZ:3.75KHZ:5KHZ:7.25KHZ:15KHZ:30KHZ:60KHZ:120KHZ:240KHZ) ulScs],[ENUM(NONE:1.25KHZ:3.75KHZ:5KHZ:7.25KHZ:15KHZ:30KHZ:60KHZ:120KHZ:240KHZ) dlScs],[ENUM(NONE:256:512:1024:1536:2048:4096) ulFFT],[ENUM(NONE:256:512:1024:1536:2048:4096) dlFFT],[INT[] ulEAXCID],[INT[] dlEAXCID],[STRING ulMAC],[ENUM(LTE:5GNR) mode],[INT ulCp0Size],[INT dlCp0Size],[INT ulCp1Size],[INT dlCp1Size]",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set carrier parameters",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhCarrierTestHandler("/carrier/show",
			"INT Index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show debug details of a carrier",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhCarrierTestHandler("/carrier/showAll",
			"",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show debug details of all carriers",
			msgParser, settings))
	);




	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/carrier/NumCarriers", "INT",
			"Number of carriers",
			NumCarriersGet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/carrier/RxPaths", "INT",
			"Number of RX paths",
			RxPathsGet,
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/carrier/TxPaths", "INT",
			"Number of TX paths",
			TxPathsGet,
			msgParser, settings))
	);



}




//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
Zcu111MplaneOranrrhCarrierTestHandler::Zcu111MplaneOranrrhCarrierTestHandler() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS),
	mHelper(CarrierTestHelper::getInstance())
{
	// NOTE: This is a dummy object creator only provided so build features can get access
	// to the registerEntry() method
}

//-------------------------------------------------------------------------------------------------------------
Zcu111MplaneOranrrhCarrierTestHandler::Zcu111MplaneOranrrhCarrierTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(CarrierTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
Zcu111MplaneOranrrhCarrierTestHandler::~Zcu111MplaneOranrrhCarrierTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111MplaneOranrrhCarrierTestHandler::registerEntry(ITif* tif)
{
	// Convert ITif object into it's expected subclasses
	IRtiMsgParser* msgParser(dynamic_cast<IRtiMsgParser*>(tif)) ;
	IRtiSettings* settings(dynamic_cast<IRtiSettings*>(tif)) ;
	if (!msgParser)
		return false ;
	if (!settings)
		return false ;

	// now call this object's registerMethods() method to do the actual work
	registerMethods(*msgParser, *settings) ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::string Zcu111MplaneOranrrhCarrierTestHandler::operator()(const std::string& functionName)
{

    if( functionName == "del")
    {
        del( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "get")
    {
        get( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getRssi")
    {
        getRssi( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "set")
    {
        set( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "show")
    {
        show( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "showAll")
    {
        showAll( callVarList, returnVarList  );
        return "" ;
    }



    return "";
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::del(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT Index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->del( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::get(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT Index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * INT Index
	// * ENUM(${CARRIER_TYPES}) Type
	// * ENUM(${CARRIER_STATES}) State
	// * ENUM(${CARRIER_SIGNALS}) SigType
	// * FLOAT TxPower (dBm)
	// * FLOAT TxFreq (kHz)
	// * FLOAT RxFreq (kHz)
	// * INT GroupUp
	// * INT GroupDown
	// * FLOAT TxScaling (dBm)
	// * FLOAT UplinkNoise (dBm)
	// * BOOL(off:on) Loopback
	// * INT[] TxContainer
	// * INT[] RxContainer
	// * INT[] TxFibre
	// * INT[] RxFibre
	// * INT UlDlConfig
	// * INT SSConfig
	// * ENUM(normal:extended) UlPrefixLen
	// * ENUM(normal:extended) DlPrefixLen
	// * ENUM(NONE:1kHz25:3kHz75:5kHz:7kHz25:15kHz:30kHz:60kHz:120kHz:240kHz) ulScs
	// * ENUM(NONE:1kHz25:3kHz75:5kHz:7kHz25:15kHz:30kHz:60kHz:120kHz:240kHz) dlScs
	// * ENUM(NONE:256:512:1024:1536:2048:4096) ulFFT
	// * ENUM(NONE:256:512:1024:1536:2048:4096) dlFFT
	// * INT[] ulEAXCID
	// * INT[] dlEAXCID
	// * STRING ulMAC
	// * ENUM(LTE:5GNR) mode
	// * INT ulCp0Size
	// * INT dlCp0Size
	// * INT ulCp1Size
	// * INT dlCp1Size
	//
	mHelper->get( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::getRssi(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT Index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT[] Rssi (dBm)
	//
	mHelper->getRssi( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::set(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT Index
	// * [ENUM(${CARRIER_TYPES}) Type]
	// * [ENUM(${CARRIER_STATES}) State]
	// * [ENUM(${CARRIER_SIGNALS}) SigType]
	// * [FLOAT TxPower (dBm)]
	// * [FLOAT TxFreq (kHz)]
	// * [FLOAT RxFreq (kHz)]
	// * [INT GroupUp]
	// * [INT GroupDown]
	// * [FLOAT TxScaling (dBm)]
	// * [INT[] TxContainer]
	// * [INT[] RxContainer]
	// * [INT[] TxFibre]
	// * [INT[] RxFibre]
	// * [FLOAT UplinkNoise (dBm)]
	// * [BOOL(off:on) Loopback]
	// * [INT uldlConfig]
	// * [INT ssConfig]
	// * [ENUM(normal:extended) ulPrefixLen]
	// * [ENUM(normal:extended) dlPrefixLen]
	// * [ENUM(NONE:1.25KHZ:3.75KHZ:5KHZ:7.25KHZ:15KHZ:30KHZ:60KHZ:120KHZ:240KHZ) ulScs]
	// * [ENUM(NONE:1.25KHZ:3.75KHZ:5KHZ:7.25KHZ:15KHZ:30KHZ:60KHZ:120KHZ:240KHZ) dlScs]
	// * [ENUM(NONE:256:512:1024:1536:2048:4096) ulFFT]
	// * [ENUM(NONE:256:512:1024:1536:2048:4096) dlFFT]
	// * [INT[] ulEAXCID]
	// * [INT[] dlEAXCID]
	// * [STRING ulMAC]
	// * [ENUM(LTE:5GNR) mode]
	// * [INT ulCp0Size]
	// * [INT dlCp0Size]
	// * [INT ulCp1Size]
	// * [INT dlCp1Size]
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->set( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::show(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT Index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->show( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::showAll(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// *
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->showAll( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}




//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::NumCarriersGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/carrier/NumCarriers"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<CarrierTestHelper> helper(CarrierTestHelper::getInstance()) ;
	helper->NumCarriersGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::RxPathsGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/carrier/RxPaths"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<CarrierTestHelper> helper(CarrierTestHelper::getInstance()) ;
	helper->RxPathsGet( pathname, returnList ) ;
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhCarrierTestHandler::TxPathsGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/carrier/TxPaths"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<CarrierTestHelper> helper(CarrierTestHelper::getInstance()) ;
	helper->TxPathsGet( pathname, returnList ) ;
}








// Add any statics, private methods etc here %%-->

// <--%%
