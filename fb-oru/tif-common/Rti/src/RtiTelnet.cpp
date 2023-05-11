/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiTelnet.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cctype>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "RtiTelnet.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Define for debug - debug code to be removed when this is fully tested
//#define DEBUG_TELNET

static const char TELNET_ECHO				= 1 ;
static const char TELNET_SUPPRESS_GOAHEAD	= 3 ;
static const char TELNET_TERMINAL_TYPE		= 24 ;
static const char TELNET_WINDOW_SIZE		= 31 ;
static const char TELNET_TERMINAL_SPEED		= 32 ;
static const char TELNET_REMOTE_FLOWCONTROL	= 33 ;
static const char TELNET_LINEMODE			= 34 ;
static const char TELNET_ENV_VARS			= 36 ;

static const char TELNET_SE			= (char)240 ;
static const char TELNET_SB			= (char)250 ;
static const char TELNET_WILL		= (char)251 ;
static const char TELNET_WONT		= (char)252 ;
static const char TELNET_DO			= (char)253 ;
static const char TELNET_DONT		= (char)254 ;
static const char TELNET_IAC		= (char)255 ;

static const unsigned maxControlSequence = 4 ;

// List of initial commands
static const std::vector< std::pair<char, char> > telnetInitOptions{
	std::make_pair( TELNET_LINEMODE,				TELNET_DO ),
	std::make_pair( TELNET_ECHO,					TELNET_WILL	),
//	std::make_pair( TELNET_SUPPRESS_GOAHEAD,		TELNET_WILL	),
} ;

//=============================================================================================================
// PROTOTYPES
//=============================================================================================================
#ifdef DEBUG_TELNET
static void dumpchars(const std::string& msg) ;
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RtiTelnet::RtiTelnet(ITelnet* telnet) :
	mTelnet(telnet),
	mNumTelnetChars(0),
	mSubNegotiating(false),
	mMaxTelnetChars(3),
	mIacCmd(0),
	mRecvIdx(0),
	mRecvBuffer(""),
	mNoEcho(true),
	mClientRejectsEcho(false)
{
	sendCharModeOptions() ;
}

//-------------------------------------------------------------------------------------------------------------
RtiTelnet::~RtiTelnet()
{
}

//-------------------------------------------------------------------------------------------------------------
bool RtiTelnet::handle(std::string& command)
{
	command = "" ;

	// see if buffer already has characters left
	if (mRecvBuffer.empty())
	{
		// get any available characters
		mTelnet->recv(mRecvBuffer) ;

#ifdef DEBUG_TELNET
		if (!mRecvBuffer.empty())
		{
			std::cerr << "[Telnet] Rx " ; dumpchars(mRecvBuffer) ;
		}
#endif
	}
#ifdef DEBUG_TELNET
	else
	{
		std::cerr << "[Telnet] Buff size=" << mRecvBuffer.size() << " idx=" << mRecvIdx <<
				" '" << mRecvBuffer.substr(mRecvIdx) << "'" << std::endl ;
	}
#endif

	// stop if no chars
	if (mRecvBuffer.empty())
		return false ;

	// Process each char - taking into account whether we're still processing telnet chars
	while (mRecvIdx < mRecvBuffer.size())
	{
		char cc = mRecvBuffer[mRecvIdx++] ;

#ifdef DEBUG_TELNET
		std::cerr << std::endl << "[Telnet] CHAR [" << (unsigned)((unsigned char)(cc) & 0xff) << "]" << std::endl ;
#endif

		// just ditch any telnet command chars
		if (checkTelnet(cc))
			continue ;

		// Non-telnet char so add to command buffer
		command.append(1, cc) ;
	}

	// See if emptied out the receive buffer
	if (mRecvIdx == mRecvBuffer.size())
	{
		mRecvIdx = 0 ;
		mRecvBuffer = "" ;
#ifdef DEBUG_TELNET
		std::cerr << "[Telnet] (clear rx buff)" <<std::endl ;
#endif
	}

	// got some chars
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RtiTelnet::noEchoMode() const
{
//	return mNoEcho || mClientRejectsEcho ;
	// TODO fix no echo version
	return false ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool RtiTelnet::checkTelnet(const char cc)
{
	if (cc == TELNET_IAC)
	{
#ifdef DEBUG_TELNET
		std::cerr << "[Telnet] TELNET_IAC" << std::endl ;
#endif
		mNumTelnetChars = 1 ;
		mSubNegotiating = false ;
		mMaxTelnetChars = 3 ;
		mIacCmd = 0 ;

		// Assume we're now in echo (char edit) mode
		mNoEcho = false ;

		return true ;
	}

	// haven't seen initial IAC so this must be treated as a normal char
	if (mNumTelnetChars == 0)
		return false ;

	// inc counter
	if (++mNumTelnetChars > mMaxTelnetChars)
	{
		// not part of an IAC so stop
		mNumTelnetChars = 0 ;
		return false ;
	}

#ifdef DEBUG_TELNET
	std::cerr << "[Telnet] TELNET CHAR " <<
			std::hex << "[0x" << (unsigned)cc << "] " << std::dec <<
			mNumTelnetChars << " / " << mMaxTelnetChars <<
			" (sub? " << mSubNegotiating << ")" << std::endl ;
#endif

	// Save IAC command
	if (mNumTelnetChars==2)
	{
		mIacCmd = cc ;

		// check for start of sub-negotiation
		if (cc == TELNET_SB)
		{
			// start of sub-negotiation
			mMaxTelnetChars = 128 ;
			mSubNegotiating = true ;
		}

		// check for end of sub-negotiation
		else if (cc == TELNET_SE)
		{
			// end of sub-negotiation
			mNumTelnetChars = 0 ;
			mSubNegotiating = false ;
			mMaxTelnetChars = 3 ;
		}

		return true ;
	}


	// Skip if not 3rd byte
	if (mNumTelnetChars != 3)
		return true ;

	// If the command is in the init list, the resend our intention. Otherwise negate
	auto entry(std::find_if(telnetInitOptions.begin(), telnetInitOptions.end(),
		[cc](const std::pair<unsigned char, unsigned char>& a)->bool{
			return a.first == cc ;
		}
	)) ;
	if (entry != telnetInitOptions.end())
	{
		// if this was accepted then we're ok
		char ok(positiveIac(mIacCmd)) ;
		if (ok == 0 || ok == entry->second)
			return true ;

		// It turns out that some clients reply "DONT LINEMODE" even though they are
		// then happy to work in the requested manner!
		// Everything seems ok to just note whether the client negotiates (i.e. is a proper telnet client)
		// or doesn't (i.e. is a connecting application)

//		// client won't do as it's told, so revert back to dumb mode
//		mClientRejectsEcho = true ;

		return true ;
	}

	// reply with negative of request
	char replyCmd(negativeIac(mIacCmd)) ;
	if (replyCmd)
	{
		std::ostringstream os ;
		os << TELNET_IAC << replyCmd << cc ;
		mTelnet->send(os.str()) ;
#ifdef DEBUG_TELNET
std::cerr << "[Telnet] TELNET NEG REPLY " ; dumpchars(os.str()) ;
#endif
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RtiTelnet::sendCharModeOptions()
{
	std::ostringstream os ;
	for (auto options : telnetInitOptions)
	{
		os << TELNET_IAC << options.second << options.first ;
	}
	mTelnet->send(os.str()) ;

#ifdef DEBUG_TELNET
std::cerr << "[Telnet] TELNET INIT " ; dumpchars(os.str()) ;
#endif

}


//-------------------------------------------------------------------------------------------------------------
char Mplane::RtiTelnet::negativeIac(char iacCmd) const
{
	switch (iacCmd)
	{
	case TELNET_WILL:
		return TELNET_DONT ;
		break ;
	case TELNET_DO:
		return TELNET_WONT ;
		break ;
	case TELNET_WONT:
		return TELNET_DO ;
		break ;
	case TELNET_DONT:
		return TELNET_WILL ;
		break ;
	default:
		return iacCmd ;
		break ;
	}

	return iacCmd ;
}

//-------------------------------------------------------------------------------------------------------------
char Mplane::RtiTelnet::positiveIac(char iacCmd) const
{
	switch (iacCmd)
	{
	case TELNET_WILL:
		return TELNET_DO ;
		break ;
	case TELNET_DO:
		return TELNET_WILL ;
		break ;
	case TELNET_WONT:
		return TELNET_DONT ;
		break ;
	case TELNET_DONT:
		return TELNET_WONT ;
		break ;
	default:
		return 0 ;
		break ;
	}

	return 0 ;
}


//=============================================================================================================
// LOCAL
//=============================================================================================================
#ifdef DEBUG_TELNET
//-------------------------------------------------------------------------------------------------------------
static void dumpchars(const std::string& data)
{
	std::cerr << "Chars: '"  ;
	for (std::string::const_iterator iter(data.begin()); iter != data.end(); ++iter)
	{
		if (isprint(*iter))
			std::cerr << *iter ;
		else
			std::cerr << std::hex << "[" << (unsigned)((unsigned char)(*iter)&0xff) << "]" << std::dec ;
	}
	std::cerr <<  "'" << std::endl ;
}

#endif
