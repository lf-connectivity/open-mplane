/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111MplaneOranrrhTxPortTestHandler.cpp
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
#include "Zcu111MplaneOranrrhTxPortTestHandler.h"

// Add any specific includes here %%-->

// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.addDir( new DirClass("/tx", "Tx Port settings", msgParser, settings) ) ;


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/getAtten",
			"INT{1..${NUM_TX_PORTS}} index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],FLOAT value (dB)",
			"Get Tx path overall attenuation value",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/getCWPower",
			"INT{1..${NUM_TX_PORTS}} index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],FLOAT result (dBFS)",
			"Get CW tone power setting",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/getFreq",
			"INT{1..${NUM_TX_PORTS}} index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],FLOAT value (kHz)",
			"Get Tx port frequency value",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/getFwdPower",
			"INT{1..${NUM_TX_PORTS}} index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],FLOAT rf (dBm),FLOAT digital (dB)",
			"Get forward power measurement reading",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/getRevPower",
			"INT{1..${NUM_TX_PORTS}} index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],FLOAT rf (dBm),FLOAT digital (dB)",
			"Get reverse power measurement reading",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/getScaler",
			"INT{1..${NUM_TX_PORTS}} index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],FLOAT result (dBfs)",
			"Get digital scaler power correction",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/getTemp",
			"INT{1..${NUM_TX_PORTS}} index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message],FLOAT result (DegC)",
			"Get Tx path temperature value in degrees C",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/setAtten",
			"INT{1..${NUM_TX_PORTS}} index,FLOAT value (dB)",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set Tx path overall attenuation value",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/setCWPower",
			"INT{1..${NUM_TX_PORTS}} index,[FLOAT value (dBFS)]",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set CW test tone power for a port",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/setEnable",
			"INT{1..${NUM_TX_PORTS}} index,ENUM(on:off:follow) mode",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set the Tx enable to on/off/follow",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/setFreq",
			"INT{1..${NUM_TX_PORTS}} index,FLOAT value (kHz)",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set Tx port frequency value",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/setMode",
			"INT{1..${NUM_TX_PORTS}} index,ENUM(modulated:cw) mode",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set the Tx mode between modulated or cw with given power",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/setScaler",
			"INT{1..${NUM_TX_PORTS}} index,[FLOAT value (dBFS)]",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Set +/- digital power scaler in dBfs",
			msgParser, settings))
	);


	msgParser.add( static_cast<RtiDirEntry *>(new Zcu111MplaneOranrrhTxPortTestHandler("/tx/showSynth",
			"INT{1..${NUM_TX_PORTS}} index",
			"ENUM(OK:ERROR) Status=OK,[STRING Info],[STRING Message]",
			"Show debug information for the Rx synthesiser",
			msgParser, settings))
	);




	msgParser.add( static_cast<RtiDirEntry *>(new TestReadVar("/tx/Ports", "INT",
			"Number of TX ports",
			PortsGet,
			msgParser, settings))
	);



}




//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
Zcu111MplaneOranrrhTxPortTestHandler::Zcu111MplaneOranrrhTxPortTestHandler() :
	EntryFunc("", "", "", "", *ITifControl::NULL_MSG_PARSER, *ITifControl::NULL_SETTINGS),
	mHelper(TxPortTestHelper::getInstance())
{
	// NOTE: This is a dummy object creator only provided so build features can get access
	// to the registerEntry() method
}

//-------------------------------------------------------------------------------------------------------------
Zcu111MplaneOranrrhTxPortTestHandler::Zcu111MplaneOranrrhTxPortTestHandler(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mHelper(TxPortTestHelper::getInstance())
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
Zcu111MplaneOranrrhTxPortTestHandler::~Zcu111MplaneOranrrhTxPortTestHandler()
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111MplaneOranrrhTxPortTestHandler::registerEntry(ITif* tif)
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
std::string Zcu111MplaneOranrrhTxPortTestHandler::operator()(const std::string& functionName)
{

    if( functionName == "getAtten")
    {
        getAtten( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getCWPower")
    {
        getCWPower( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getFreq")
    {
        getFreq( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getFwdPower")
    {
        getFwdPower( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getRevPower")
    {
        getRevPower( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getScaler")
    {
        getScaler( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "getTemp")
    {
        getTemp( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "setAtten")
    {
        setAtten( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "setCWPower")
    {
        setCWPower( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "setEnable")
    {
        setEnable( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "setFreq")
    {
        setFreq( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "setMode")
    {
        setMode( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "setScaler")
    {
        setScaler( callVarList, returnVarList  );
        return "" ;
    }


    if( functionName == "showSynth")
    {
        showSynth( callVarList, returnVarList  );
        return "" ;
    }



    return "";
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::getAtten(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT value (dB)
	//
	mHelper->getAtten( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::getCWPower(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT result (dBFS)
	//
	mHelper->getCWPower( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::getFreq(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT value (kHz)
	//
	mHelper->getFreq( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::getFwdPower(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT rf (dBm)
	// * FLOAT digital (dB)
	//
	mHelper->getFwdPower( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::getRevPower(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT rf (dBm)
	// * FLOAT digital (dB)
	//
	mHelper->getRevPower( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::getScaler(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT result (dBfs)
	//
	mHelper->getScaler( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::getTemp(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	// * FLOAT result (DegC)
	//
	mHelper->getTemp( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::setAtten(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// * FLOAT value (dB)
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->setAtten( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::setCWPower(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// * [FLOAT value (dBFS)]
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->setCWPower( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::setEnable(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// * ENUM(on:off:follow) mode
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->setEnable( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::setFreq(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// * FLOAT value (kHz)
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->setFreq( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::setMode(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// * ENUM(modulated:cw) mode
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->setMode( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::setScaler(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// * [FLOAT value (dBFS)]
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->setScaler( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::showSynth(  DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * INT{1..${NUM_TX_PORTS}} index
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//
	mHelper->showSynth( mMsgParser, callList, returnList ) ;

	// Insert your code here : %%-->

	// <--%%
}




//-------------------------------------------------------------------------------------------------------------
void Zcu111MplaneOranrrhTxPortTestHandler::PortsGet(  const std::string& pathname, DataVariantList *returnList )
{
	// Getter for "/tx/Ports"
	//
	// Return the variable value using the returnList using something like:
	//
	//   returnList->find(pathname)->set(someValue) ;
	//


	// Insert your code here : %%-->

	// <--%%

	std::shared_ptr<TxPortTestHelper> helper(TxPortTestHelper::getInstance()) ;
	helper->PortsGet( pathname, returnList ) ;
}








// Add any statics, private methods etc here %%-->

// <--%%
