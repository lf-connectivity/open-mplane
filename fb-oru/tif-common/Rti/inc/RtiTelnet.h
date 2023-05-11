/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiTelnet.h
 * \brief     RTI Telnet command handler
 *
 *
 * \details   Handles telnet commands
 *
 */

#ifndef RTITELNET_H_
#define RTITELNET_H_

#include <map>
#include <vector>
#include <string>

#include "ITelnet.h"

namespace Mplane {

/**
 * Telnet handler
 */
class RtiTelnet {
public:
	explicit RtiTelnet(ITelnet* telnet) ;
	virtual ~RtiTelnet() ;

	/**
	 * Use the telnet interface to try getting some more characters and process them (if any)
	 * @param command	Set to the complete command when a terminating CR is seen
	 * @param tabCompletion	List of tab completion paths
	 * @return true if we received some characters; false if not
	 */
	virtual bool handle(std::string& command) ;

	/**
	 * Initially we will be in the state where server & client are in 'no echo' mode. We only leave this state if
	 * the client negotiates a change.
	 * @return true if in no echo mode
	 */
	virtual bool noEchoMode() const ;

private:
	// see if char is handled by one of these methods
	bool checkTelnet(const char cc) ;

	// Send the settings to set the client into char mode
	void sendCharModeOptions() ;

	// get negative reponse for the IAC command
	char negativeIac(char iacCmd) const ;

	// get the positive response of IAC command
	char positiveIac(char iacCmd) const ;

private:
	// the telnet class
	ITelnet* mTelnet ;

	// Keep track of the number of telnet control chars received
	unsigned mNumTelnetChars ;
	bool mSubNegotiating ;
	unsigned mMaxTelnetChars ;
	char mIacCmd ;

	// Buffer for the received chars
	unsigned mRecvIdx ;
	std::string mRecvBuffer ;

	// echo mode
	bool mNoEcho ;
	bool mClientRejectsEcho ;
} ;

}

#endif /* RTITELNET_H_ */
