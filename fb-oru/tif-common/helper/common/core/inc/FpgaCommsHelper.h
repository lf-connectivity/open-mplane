/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsHelper.h
 * \brief     Base class for communicating with an FPGA application
 *
 *
 * \details
 *
 */


#ifndef FPGACOMMSHELPER_H_
#define FPGACOMMSHELPER_H_

#include <string>
#include <memory>
#include <vector>
#include <map>

#include "DataVariant.h"
#include "Mutex.h"
#include "Loggable.h"

#include "IFpgaComms.h"
#include "IFpgaMsg.h"
#include "IRtiMsgParser.h"

namespace Mplane {

class FpgaCommsHelper : public Loggable
{
public:
	FpgaCommsHelper(const std::string& name, std::shared_ptr<IFpgaComms> fpgaComms, const std::string& stateVar) ;
	virtual ~FpgaCommsHelper() ;

	// Called when program is shutting down. Needs to ensure all ports etc. are closed down before the objects are destroyed
	virtual void shutdown() ;


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
	virtual void apiVersion( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void checkApi( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void debugStatus( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void dump( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void frd( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void fwr( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Get variable(s) value
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	virtual void get( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Set variable(s) value
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	virtual void set( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(REPLY:EVENT:LOG:MATLAB:TEXT) type
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	virtual void logClose( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(REPLY:EVENT:LOG:MATLAB:TEXT) type
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	virtual void logOpen( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void logShow( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(REPLY:EVENT:LOG:MATLAB:TEXT) type
	 *   INT port
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	virtual void portClose( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

	/**
	 * Called with:
	 *   ENUM(REPLY:EVENT:LOG:MATLAB:TEXT) type
	 *   INT port
	 *
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	virtual void portOpen( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void portShow( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void reset( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );

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
	virtual void restart( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList );


protected:
	/**
	 * Set variable(s) value and runs the command
	 * Returns:
	 *   ENUM(OK:ERROR) Status=OK
	 *   [STRING Info]
	 *   [STRING Message]
	 *
	 */
	virtual bool cmdWithSet( const std::string& command, DataVariantList *callList, DataVariantList *returnList );

	virtual bool cmdShowResponse( const std::string& command, DataVariantList *callList, DataVariantList *returnList ) ;
	virtual bool cmdWaitResponse( const std::string& command, DataVariantList *callList, DataVariantList *returnList ) ;
	virtual bool cmdGetResponse( const std::string& command, DataVariantList *callList, DataVariantList *returnList, std::shared_ptr<IFpgaMsg>& response ) ;

	virtual bool cmdShowResponse( const std::string& command, DataVariantList *returnList ) ;
	virtual bool cmdWaitResponse( const std::string& command, DataVariantList *returnList ) ;
	virtual bool cmdGetResponse( const std::string& command, DataVariantList *returnList, std::shared_ptr<IFpgaMsg>& response ) ;

	virtual bool commandShowResponse( std::shared_ptr<IFpgaMsg> msg, DataVariantList *returnList ) ;
	virtual bool commandWaitResponse( std::shared_ptr<IFpgaMsg> msg, DataVariantList *returnList ) ;
	virtual bool commandGetResponse( std::shared_ptr<IFpgaMsg> msg, DataVariantList *returnList, std::shared_ptr<IFpgaMsg>& response ) ;
	virtual bool commandWaitNotState( unsigned state, DataVariantList *returnList ) ;

	virtual std::shared_ptr<IFpgaMsg> msgFromCommand( const std::string& command, DataVariantList *callList ) ;

protected:
	static Mutex mMutex ;
	std::shared_ptr<IFpgaComms> mFpgaComms ;
	std::string mStateVar ;
} ;

}

#endif /* FPGACOMMSHELPER_H_ */
