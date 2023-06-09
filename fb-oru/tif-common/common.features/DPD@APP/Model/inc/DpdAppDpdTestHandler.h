/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdAppDpdTestHandler.h
 * \brief     Test methods for DPD@APP
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run).
 *
 */

#ifndef __DPDAPPDPDTESTHANDLER__H_
#define __DPDAPPDPDTESTHANDLER__H_


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <vector>
#include <memory>
#include "DpdTestHelper.h"
#include "ITif.h"
#include "IRtiMsgParser.h"
#include "Nodes/EntryFunc.h"

// Add any specific includes here %%-->

// <--%%

//=============================================================================================================
// CLASS
//=============================================================================================================

namespace Mplane {

class DpdAppDpdTestHandler: public virtual ITifEntry, public EntryFunc
{
public:

	DpdAppDpdTestHandler( const std::string& pathname, const std::string& comment,
    		const std::string& callFields, const std::string& returnFields,
    		IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~DpdAppDpdTestHandler();

    static void registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings) ;

	/**
	 * Special constructor - only to be used for calling the static registerMethods()
	 */
	DpdAppDpdTestHandler();

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
	void checkApi( DataVariantList *callList, DataVariantList *returnList );

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
	void debugStatus( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT addr
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void frd( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT addr
	 *   INT data
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void fwr( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   [STRING arg0]
	 *   [STRING arg1]
	 *   [STRING arg2]
	 *   [STRING arg3]
	 *   [STRING arg4]
	 *   [STRING arg5]
	 *   [STRING arg6]
	 *   [STRING arg7]
	 *   [STRING arg8]
	 *   [STRING arg9]
	 *   [STRING arg10]
	 *   [STRING arg11]
	 *   [STRING arg12]
	 *   [STRING arg13]
	 *   [STRING arg14]
	 *   [STRING arg15]
	 *   [STRING arg16]
	 *   [STRING arg17]
	 *   [STRING arg18]
	 *   [STRING arg19]
	 *   [STRING arg20]
	 *   [STRING arg21]
	 *   [STRING arg22]
	 *   [STRING arg23]
	 *   [STRING arg24]
	 *   [STRING arg25]
	 *   [STRING arg26]
	 *   [STRING arg27]
	 *   [STRING arg28]
	 *   [STRING arg29]
	 *   [STRING arg30]
	 *   [STRING arg31]
	 *   [STRING arg32]
	 *   [STRING arg33]
	 *   [STRING arg34]
	 *   [STRING arg35]
	 *   [STRING arg36]
	 *   [STRING arg37]
	 *   [STRING arg38]
	 *   [STRING arg39]
	 *   [STRING arg40]
	 *   [STRING arg41]
	 *   [STRING arg42]
	 *   [STRING arg43]
	 *   [STRING arg44]
	 *   [STRING arg45]
	 *   [STRING arg46]
	 *   [STRING arg47]
	 *   [STRING arg48]
	 *   [STRING arg49]
	 *   [STRING arg50]
	 *   [STRING arg51]
	 *   [STRING arg52]
	 *   [STRING arg53]
	 *   [STRING arg54]
	 *   [STRING arg55]
	 *   [STRING arg56]
	 *   [STRING arg57]
	 *   [STRING arg58]
	 *   [STRING arg59]
	 *   [STRING arg60]
	 *   [STRING arg61]
	 *   [STRING arg62]
	 *   [STRING arg63]
	 *   [STRING arg64]
	 *   [STRING arg65]
	 *   [STRING arg66]
	 *   [STRING arg67]
	 *   [STRING arg68]
	 *   [STRING arg69]
	 *   [STRING arg70]
	 *   [STRING arg71]
	 *   [STRING arg72]
	 *   [STRING arg73]
	 *   [STRING arg74]
	 *   [STRING arg75]
	 *   [STRING arg76]
	 *   [INT tx]
	 *   [ENUM(MINOR:MAJOR) severity]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void get( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(CMD:REPLY:EVENT:LOG:MATLAB:TEXT) type
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void logClose( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(CMD:REPLY:EVENT:LOG:MATLAB:TEXT) type
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void logOpen( DataVariantList *callList, DataVariantList *returnList );

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
	void logShow( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(CMD:REPLY:EVENT:LOG:MATLAB:TEXT) type
	 *   INT port
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void portClose( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(CMD:REPLY:EVENT:LOG:MATLAB:TEXT) type
	 *   INT port
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void portOpen( DataVariantList *callList, DataVariantList *returnList );

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
	void portShow( DataVariantList *callList, DataVariantList *returnList );

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
	void printCfr( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   INT addr
	 *   INT i
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void printFpga( DataVariantList *callList, DataVariantList *returnList );

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
	void printLuts( DataVariantList *callList, DataVariantList *returnList );

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
	void printModel( DataVariantList *callList, DataVariantList *returnList );

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
	void reboot( DataVariantList *callList, DataVariantList *returnList );

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
	void reset( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   [ENUM(NACK:ACK) response]
	 *   [INT msgId]
	 *   [INT version]
	 *   [FLOAT fpgaVersion]
	 *   [INT build]
	 *   [INT precision]
	 *   [ENUM(OFF:ON) trace]
	 *   [ENUM(OFF:ON) verbose]
	 *   [ENUM(OFF:ON) matlab]
	 *   [ENUM(OFF:ON) console]
	 *   [INT uptime]
	 *   [INT t]
	 *   [INT dt]
	 *   [INT tx]
	 *   [INT Q]
	 *   [INT B]
	 *   [INT N]
	 *   [FLOAT G]
	 *   [FLOAT Gqmc]
	 *   [FLOAT Gagc]
	 *   [INT taps]
	 *   [INT mags]
	 *   [FLOAT C1]
	 *   [FLOAT C2]
	 *   [INT clip]
	 *   [INT occupancy]
	 *   [FLOAT XcfrRef]
	 *   [INT XrmsRef]
	 *   [INT XminRef]
	 *   [INT YrmsRef]
	 *   [FLOAT srxAtten]
	 *   [FLOAT srxLimit]
	 *   [FLOAT fwdGerr]
	 *   [FLOAT revGerr]
	 *   [ENUM(OFF:ON) srxAgc]
	 *   [ENUM(IDLE:WAITMODEL:RESET:WAITBB:TA:CONVERGE:TRACK:NONE) state]
	 *   [INT success]
	 *   [INT fail]
	 *   [ENUM(OK:UNKNOWN:TIMEALIGNMENT:LOWBB:MUXFAIL:DCUFAIL:LOWSRX:HIGHSRX:YERROR:ZERROR:DIMENSIONING:SOLVER:LUTS:NORMALISATION:RANGE:COVERAGE:UPDATESTRATEGY:EFFICIENCY:EXPANSION:INSANE:SPURIOUS:INHIBIT) err]
	 *   [FLOAT eff]
	 *   [FLOAT Elim]
	 *   [FLOAT Gexp]
	 *   [FLOAT Glim]
	 *   [FLOAT evm]
	 *   [INT lock]
	 *   [FLOAT Tabs]
	 *   [FLOAT Tdelta]
	 *   [FLOAT Tlim]
	 *   [FLOAT Gadj]
	 *   [ENUM(OFF:ON) norm]
	 *   [INT Tconv]
	 *   [FLOAT Vlim]
	 *   [ENUM(OFF:ON:ENHANCED:X:Z) ta]
	 *   [ENUM(FULL:ERROR) mode]
	 *   [ENUM(OFF:ON:DECIMATED:BYPASS) dpd]
	 *   [ENUM(OFF:ON:FAST:DCONLY:X:Z) qmc]
	 *   [ENUM(OFF:ON) fdf]
	 *   [ENUM(OFF:ON) converge]
	 *   [INT skew]
	 *   [ENUM(OFF:ON:BLOCK) afc]
	 *   [ENUM(OFF:ON) dynamic]
	 *   [ENUM(OFF:ON) alarm]
	 *   [ENUM(MINOR:MAJOR) severity]
	 *   [ENUM(OFF:ON:INVALID:CLEAR:PENDING:ACTIVE:ACK) alarmState]
	 *   [INT alarmN]
	 *   [INT alarmT1]
	 *   [INT alarmT2]
	 *   [ENUM(OFF:ON) decimation]
	 *   [INT Iconv]
	 *   [INT i]
	 *   [INT addr]
	 *   [INT data]
	 *   [INT id]
	 *   [INT level]
	 *   [ENUM(X:Z:RAW) src]
	 *   [INT debug]
	 *   [INT apiVersion]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void set( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   [ENUM(NACK:ACK) response]
	 *   [INT msgId]
	 *   [INT version]
	 *   [FLOAT fpgaVersion]
	 *   [INT build]
	 *   [INT precision]
	 *   [ENUM(OFF:ON) trace]
	 *   [ENUM(OFF:ON) verbose]
	 *   [ENUM(OFF:ON) matlab]
	 *   [ENUM(OFF:ON) console]
	 *   [INT uptime]
	 *   [INT t]
	 *   [INT dt]
	 *   [INT tx]
	 *   [INT Q]
	 *   [INT B]
	 *   [INT N]
	 *   [FLOAT G]
	 *   [FLOAT Gqmc]
	 *   [FLOAT Gagc]
	 *   [INT taps]
	 *   [INT mags]
	 *   [FLOAT C1]
	 *   [FLOAT C2]
	 *   [INT clip]
	 *   [INT occupancy]
	 *   [FLOAT XcfrRef]
	 *   [INT XrmsRef]
	 *   [INT XminRef]
	 *   [INT YrmsRef]
	 *   [FLOAT srxAtten]
	 *   [FLOAT srxLimit]
	 *   [FLOAT fwdGerr]
	 *   [FLOAT revGerr]
	 *   [ENUM(OFF:ON) srxAgc]
	 *   [ENUM(IDLE:WAITMODEL:RESET:WAITBB:TA:CONVERGE:TRACK:NONE) state]
	 *   [INT success]
	 *   [INT fail]
	 *   [ENUM(OK:UNKNOWN:TIMEALIGNMENT:LOWBB:MUXFAIL:DCUFAIL:LOWSRX:HIGHSRX:YERROR:ZERROR:DIMENSIONING:SOLVER:LUTS:NORMALISATION:RANGE:COVERAGE:UPDATESTRATEGY:EFFICIENCY:EXPANSION:INSANE:SPURIOUS:INHIBIT) err]
	 *   [FLOAT eff]
	 *   [FLOAT Elim]
	 *   [FLOAT Gexp]
	 *   [FLOAT Glim]
	 *   [FLOAT evm]
	 *   [INT lock]
	 *   [FLOAT Tabs]
	 *   [FLOAT Tdelta]
	 *   [FLOAT Tlim]
	 *   [FLOAT Gadj]
	 *   [ENUM(OFF:ON) norm]
	 *   [INT Tconv]
	 *   [FLOAT Vlim]
	 *   [ENUM(OFF:ON:ENHANCED:X:Z) ta]
	 *   [ENUM(FULL:ERROR) mode]
	 *   [ENUM(OFF:ON:DECIMATED:BYPASS) dpd]
	 *   [ENUM(OFF:ON:FAST:DCONLY:X:Z) qmc]
	 *   [ENUM(OFF:ON) fdf]
	 *   [ENUM(OFF:ON) converge]
	 *   [INT skew]
	 *   [ENUM(OFF:ON:BLOCK) afc]
	 *   [ENUM(OFF:ON) dynamic]
	 *   [ENUM(OFF:ON) alarm]
	 *   [ENUM(MINOR:MAJOR) severity]
	 *   [ENUM(OFF:ON:INVALID:CLEAR:PENDING:ACTIVE:ACK) alarmState]
	 *   [INT alarmN]
	 *   [INT alarmT1]
	 *   [INT alarmT2]
	 *   [ENUM(OFF:ON) decimation]
	 *   [INT Iconv]
	 *   [INT i]
	 *   [INT addr]
	 *   [INT data]
	 *   [INT id]
	 *   [INT level]
	 *   [ENUM(X:Z:RAW) src]
	 *   [INT debug]
	 *   [INT apiVersion]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void start( DataVariantList *callList, DataVariantList *returnList );

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
	void stop( DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   [INT tx]
	 *   [INT id]
	 *   [INT i]
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	void test( DataVariantList *callList, DataVariantList *returnList );






// Add any extra methods %%-->

// <--%%

private:
	std::shared_ptr<DpdTestHelper> mHelper ;
};



} // Mplane

#endif /* __DPDAPPDPDTESTHANDLER__H_*/
