/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiMsgEditor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <sstream>
#include "RtiMsgEditor.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Define for debug - debug code to be removed when this is fully tested
//#define DEBUG_EDIT

static const char CHAR_DEL			= 0x7f ;

enum KeyCodes {
	KEY_CTRLC,
	KEY_BACK,
	KEY_TAB,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_HOME,
	KEY_END,
	KEY_INS,
	KEY_DEL,
	KEY_PGUP,
	KEY_PGDN,
};

typedef std::map<std::string, enum KeyCodes> KeyMapType ;
typedef std::map<std::string, enum KeyCodes>::const_iterator KeyMapIter ;


static std::pair<std::string, enum KeyCodes> mapData[] = {
	std::make_pair("\003",			KEY_CTRLC	),
	std::make_pair("\b",			KEY_BACK	),
	std::make_pair("\t",			KEY_TAB		),
	std::make_pair("\177",			KEY_BACK	),

	std::make_pair("\033[A",		KEY_UP 		),
	std::make_pair("\033[B",		KEY_DOWN	),
	std::make_pair("\033[D",		KEY_LEFT 	),
	std::make_pair("\033[C",		KEY_RIGHT 	),
	std::make_pair("\033[H",		KEY_HOME 	),
	std::make_pair("\033[F",		KEY_END		),

	std::make_pair("\033[2~",		KEY_INS 	),
	std::make_pair("\033[3~",		KEY_DEL 	),
	std::make_pair("\033[5~",		KEY_PGUP 	),
	std::make_pair("\033[6~",		KEY_PGDN 	),
	std::make_pair("\033[1~",		KEY_HOME 	),
	std::make_pair("\033[4~",		KEY_END		),
};

static KeyMapType keyMap(mapData, mapData + sizeof(mapData) / sizeof(mapData[0])) ;

static const unsigned maxControlSequence = 4 ;

//=============================================================================================================
// PROTOTYPES
//=============================================================================================================
#ifdef DEBUG_EDIT
static void dumpchars(const std::string& msg) ;
#endif

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RtiMsgEditor::RtiMsgEditor(ITelnetSend* telnetSend, const std::string& pathSeparators, unsigned historyLength) :
	mTelnetSend(telnetSend),
	mPathSeparators(pathSeparators),
	mHistory(),
	mMaxHistory(historyLength),
	mHistoryIdx(0),
	mCommand(""),
	mCursor(0),
	mEcho(""),
	mControlIdx(0),
	mControlBuffer(""),
	mTabCount(0),
	mRecvIdx(0),
	mRecvBuffer("")
{
	mHistory.reserve(mMaxHistory) ;


//#ifdef DEBUG_EDIT
//std::cerr << "[Ed] Keys:" << std::endl ;
//for (KeyMapIter iter(keyMap.begin()); iter != keyMap.end(); ++iter)
//{
//	dumpchars(iter->first) ;
//}
//#endif
}

//-------------------------------------------------------------------------------------------------------------
RtiMsgEditor::~RtiMsgEditor()
{
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgEditor::handle(const std::string& recv, std::string& command, const std::vector<std::string>& tabCompletion, const std::string& prompt)
{
	command = "" ;

	// stop if no chars
	if (!recv.empty())
		mRecvBuffer.append(recv) ;
	if (mRecvBuffer.empty())
		return false ;

	// Process each char - taking into account whether we're still processing telnet chars
	mEcho = "" ;
	while (mRecvIdx < mRecvBuffer.size())
	{
		char cc = mRecvBuffer[mRecvIdx++] ;

#ifdef DEBUG_EDIT
		std::cerr << "[Ed] CHAR [" << (unsigned)((unsigned char)(cc) & 0xff) << "]" << std::endl ;
#endif

		// check for CR
		if (checkNewline(cc))
		{
			command = mCommand ;
			setCmd("") ;
			break ;
		}

		// Check for edit chars
		if (checkEdit(cc, tabCompletion, prompt))
			continue ;


		// Handle remaining chars
		handleChar(cc) ;

	}

	// See if emptied out the receive buffer
	if (mRecvIdx == mRecvBuffer.size())
	{
		mRecvIdx = 0 ;
		mRecvBuffer = "" ;
#ifdef DEBUG_EDIT
		std::cerr << "[Ed] (clear rx buff)" <<std::endl ;
#endif
	}

	// echo chars
	if (!mEcho.empty())
		mTelnetSend->send(mEcho) ;

	// got some chars
	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgEditor::checkEdit(const char cc, const std::vector<std::string>& tabCompletion, const std::string& prompt)
{
	// skip nuls
	if ( (cc == '\0') && (mControlIdx == 0) )
		return false ;

	// look for start of control char or ESC sequence
	if (cc < ' ' || cc >= CHAR_DEL)
	{
		mControlBuffer = "" ;
		mControlBuffer.append(1, cc) ;
		mControlIdx = 1 ;
#ifdef DEBUG_EDIT
		std::cerr << "[Ed] CONTROL" << std::endl ;
#endif
		// check table for a match and process the edit command
		handleEdit(tabCompletion, prompt) ;

		return true ;
	}

	if (mControlIdx == 0)
		return false ;

	mControlIdx++ ;
	mControlBuffer.append(1, cc) ;

#ifdef DEBUG_EDIT
	std::cerr << "[Ed] ESC Char " << mControlIdx << std::endl ;
	dumpchars(mControlBuffer) ;
#endif

	// check table for a match and process the edit command
	handleEdit(tabCompletion, prompt) ;

	// check for unhandled
	if (mControlIdx >= maxControlSequence)
	{
#ifdef DEBUG_EDIT
		std::cerr << "[Ed] ESC ABORT" << std::endl ;
#endif
		mControlBuffer = "" ;
		mControlIdx = 0 ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgEditor::checkNewline(const char cc)
{
	if ((cc != '\r') && (cc != '\n'))
		return false ;

	// Save in history
	historyAdd(mCommand) ;

	// add CR NL
	mCommand += "\r" ;
	mEcho += "\r\n" ;

#ifdef DEBUG_EDIT
	std::cerr << "[Ed] Got command '" << mCommand << "'" <<std::endl ;
#endif

	// Strip out any multiple CR / LF / NUL
	if (mRecvIdx < mRecvBuffer.size())
	{
		char ccn = mRecvBuffer[mRecvIdx] ;
		while (mRecvIdx < mRecvBuffer.size() && (ccn=='\r' || ccn=='\n' || ccn == '\0') )
		{
			ccn = mRecvBuffer[++mRecvIdx] ;
		}
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void RtiMsgEditor::handleEdit(const std::vector<std::string>& tabCompletion, const std::string& prompt)
{
#ifdef DEBUG_EDIT
	std::cerr << "[Ed] Check buffer " ; dumpchars(mControlBuffer) ;
#endif

	KeyMapIter key(keyMap.find(mControlBuffer)) ;
	if (key == keyMap.end())
	{
		mTabCount = 0 ;
		return ;
	}

#ifdef DEBUG_EDIT
	std::cerr << "[Ed] ** Got KEY : command line '" << mCommand << "' **" << std::endl ;
#endif

	// empty out echo buffer (will only contain standard chars and will ensure client sees the current
	// state of the command buffer)
	if (!mEcho.empty())
		mTelnetSend->send(mEcho) ;
	mEcho = "" ;


	// track tab count
	if (key->second == KEY_TAB)
	{
		++mTabCount ;
	}
	else
	{
		mTabCount = 0 ;
	}

	// process key
	switch(key->second)
	{
	// Edit
	case KEY_LEFT:
		if (mCursor > 0)
		{
			// backspace to cursor pos
			mEcho.append(1, '\b') ;
			--mCursor ;
		}
		break ;
	case KEY_RIGHT:
		if (mCursor < mCommand.size())
		{
			// move forward by re-outputting command line chars
			mEcho.append(1, mCommand[mCursor]) ;
			++mCursor ;
		}
		break ;
	case KEY_HOME:
		if (mCursor > 0)
		{
			// backspace from cursor pos to start
			mEcho.append(mCursor, '\b') ;
		}
		mCursor = 0 ;
		break ;
	case KEY_END:
		if (mCursor < mCommand.size())
		{
			// move forward by re-outputting command line chars
			mEcho.append(mCommand.substr(mCursor)) ;
		}
		mCursor = mCommand.size() ;
		break ;
	case KEY_INS:
		// NO OP
		break ;
	case KEY_DEL:
		// Delete to right
		if (!mCommand.empty() && mCursor < mCommand.size())
		{
			mCommand.erase(mCursor, 1) ;

			// show remaining chars (add a space to blank out final deleted char)
			mEcho.append(mCommand.substr(mCursor)) ;
			mEcho.append(1, ' ') ;

			// backspace to cursor pos
			mEcho.append(1 + mCommand.size() - mCursor, '\b') ;
		}
		break ;
	case KEY_BACK:
		// Delete to left
		if (mCursor > 0)
		{
			mCommand.erase(--mCursor, 1) ;

			// show remaining chars (add a space to blank out final deleted char)
			mEcho.append(1, '\b') ;
			mEcho.append(mCommand.substr(mCursor)) ;
			mEcho.append(1, ' ') ;

			// backspace to cursor pos
			mEcho.append(1 + mCommand.size() - mCursor, '\b') ;
		}
		break ;
	case KEY_CTRLC:
		// Delete whole line
		deleteLine() ;
		break ;

	// Completion
	case KEY_TAB:
		if (mTabCount == 2)
		{
			// clear so we don't get continuous TAB/TAB
			mTabCount = 0 ;

			// TAB TAB - show any options
			std::string alternatives( tabCompleteAlternatives(tabCompletion) ) ;
			if (!alternatives.empty())
			{
				// Move to new line
				mEcho += "\r\n" ;

				// show alternates
				mEcho += alternatives ;

				// Now reshow command
				mEcho += "\r\n" ;
				mEcho += prompt ;
				mEcho += mCommand ;
			}
		}
		else
		{
			// TAB
			std::string newCommand( tabComplete(tabCompletion) ) ;
			if (newCommand != mCommand)
			{
				// Delete whole line
				deleteLine() ;

				// set to new command line
				setCmd(newCommand) ;

				// Reset count so next TAB will attempt to expand from here
				mTabCount = 0 ;
			}
		}
		break ;

	// History
	case KEY_UP:
		// Delete whole line
		deleteLine() ;

		// get command from history
		setCmd(historyUp()) ;
		break ;
	case KEY_DOWN:
		// Delete whole line
		deleteLine() ;

		// get command from history
		setCmd(historyDown()) ;
		break ;

	// ??
	case KEY_PGUP:
		// NO OP
		break ;
	case KEY_PGDN:
		// NO OP
		break ;

	default:
		break ;
	}


	// reset escape buffer
	mControlBuffer = "" ;
	mControlIdx = 0 ;
}

//-------------------------------------------------------------------------------------------------------------
void RtiMsgEditor::handleChar(const char cc)
{
	// Skip any invalid chars
	if ( (cc < ' ') || (cc >= CHAR_DEL) )
		return ;

	// ok to echo chars
	mCommand.insert(mCursor, 1, cc) ;

	// echo from cursor pos (new char) to end of command line - ensures if we're adding chars inside
	// string that the complete command line is echoed. Need to reposition cursor if not at end of string
	mEcho.append(mCommand.substr(mCursor)) ;
	mCursor++ ;
	if (mCursor < mCommand.size())
	{
		// backspace to cursor pos
		mEcho.append(mCommand.size() - mCursor, '\b') ;
	}
}


//-------------------------------------------------------------------------------------------------------------
void RtiMsgEditor::historyAdd(const std::string& command)
{
	// reset index
	mHistoryIdx = mHistory.size() ;

	// skip if command is identical to the last one
	if (!mHistory.empty() && mHistory[mHistory.size()-1] == command)
		return ;

	// If the history is full, drop the first entry
	if (mHistory.size() == mMaxHistory)
	{
		mHistory.erase(mHistory.begin()) ;
		--mHistoryIdx ;
	}
	mHistory.push_back(command) ;
	++mHistoryIdx ;

#ifdef DEBUG_EDIT
	std::cerr << "[Ed] History (idx=" << mHistoryIdx << ")" << std::endl ;
	for (unsigned idx=0; idx < mHistory.size(); ++idx)
	{
		std::cerr << (idx==mHistoryIdx ? ">" : " ") << mHistory[idx] << std::endl ;
	}
#endif
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgEditor::historyUp()
{
	if (mHistoryIdx > 0)
		return historyGet(--mHistoryIdx) ;

	return historyGet(0) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgEditor::historyDown()
{
	if (mHistoryIdx+1 < mHistory.size())
		return mHistory[++mHistoryIdx] ;

	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgEditor::historyGet(unsigned idx) const
{
	if (idx < mHistory.size())
		return mHistory[idx] ;

	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
void RtiMsgEditor::deleteLine()
{
	if (!mCommand.empty())
	{
		// backspace from cursor pos to start
		mEcho.append(mCursor, '\b') ;

		// overwrite line with spaces, then backspace to start
		mEcho.append(mCommand.size(), ' ') ;
		mEcho.append(mCommand.size(), '\b') ;

		setCmd("") ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void RtiMsgEditor::setCmd(const std::string& newCommand)
{
	// update the command
	mCommand = newCommand ;
	mCursor = mCommand.size() ;

	// update echo
	if (!newCommand.empty())
		mEcho.append(mCommand) ;
}


//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgEditor::tabComplete(const std::vector<std::string>& tabCompletion)
{
	// get the list
	std::string prefix ;
	std::string frag ;
	std::vector<std::string> matches(tabCompleteList(prefix, frag, tabCompletion)) ;

	// if no matches then stop
	if (matches.empty())
		return mCommand ;

	// If there's only one completion, then we're done
	if (matches.size() == 1)
	{
		prefix += matches[0] ;
		return prefix ;
	}

	// more than one match - so find max common string
	std::string maxCommon(prefix) ;
	for (unsigned ccIdx = 0 ; true; ++ccIdx)
	{
		char cc = '\0' ;
		for (std::vector<std::string>::const_iterator iter(matches.begin()); iter != matches.end(); cc=(*iter)[ccIdx], ++iter)
		{
			// stop now if this match has run out of chars
			if (ccIdx >= iter->size())
				return maxCommon ;

			// stop if char mismatch
			if (cc == '\0')
				continue ;
			if (cc != (*iter)[ccIdx])
				return maxCommon ;
		}

		// ok so add the char
		maxCommon.append(1, cc) ;
	}

	// should never get here
	return mCommand ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgEditor::tabCompleteAlternatives(const std::vector<std::string>& tabCompletion)
{
	// get the list
	std::string prefix ;
	std::string frag ;
	std::vector<std::string> matches(tabCompleteList(prefix, frag, tabCompletion)) ;

	// if no matches then stop
	if (matches.size() <= 1)
		return "" ;

	// Show the multiple matches
	std::string alternatives ;
	for (std::vector<std::string>::const_iterator iter(matches.begin()); iter != matches.end(); ++iter)
	{
		alternatives += *iter ;
		alternatives += "\r\n" ;
	}

	return alternatives ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> RtiMsgEditor::tabCompleteList(std::string& prefix, std::string& frag,
		const std::vector<std::string>& tabCompletion)
{
	// Get the last contiguous non-whitespace string:
	// cd tif:set -> tif:set
	//
	prefix = "" ;
	frag = mCommand ;
	if (!mCommand.empty())
	{
		std::size_t pos( mCommand.find_last_of(' ')) ;
		if (pos != std::string::npos)
		{
			frag = mCommand.substr(pos+1) ;
			prefix = mCommand.substr(0, pos+1) ;
		}
	}

	std::vector<std::string> matches ;

	// if we started with an empty string, then list the relative elements
	if (frag.empty())
	{
		for (std::vector<std::string>::const_iterator iter(tabCompletion.begin()); iter != tabCompletion.end(); ++iter)
		{
			// only add relative entries
			if (iter->find_first_of(mPathSeparators) != std::string::npos)
				continue ;

			// This is a valid completion
			matches.push_back(*iter) ;
		}
		return matches ;
	}

	// Find all that match
	unsigned fragLen(frag.length()) ;
	for (std::vector<std::string>::const_iterator iter(tabCompletion.begin()); iter != tabCompletion.end(); ++iter)
	{
		if (iter->find(frag) != 0)
			continue ;

		// This path does start with the fragment we're looking for.
		// Now weed out any paths that are in sub-directories
		if (iter->substr(fragLen).find_first_of(mPathSeparators) != std::string::npos)
			continue ;

		// This is a valid completion
		matches.push_back(*iter) ;
	}

	return matches ;
}


//=============================================================================================================
// LOCAL
//=============================================================================================================
#ifdef DEBUG_EDIT
//-------------------------------------------------------------------------------------------------------------
static void dumpchars(const std::string& data)
{
	std::cerr << "[Ed] Chars: '"  ;
	for (std::string::const_iterator iter(data.begin()); iter != data.end(); ++iter)
	{
		if ((*iter >= ' ') && (*iter < CHAR_DEL))
			std::cerr << *iter ;
		else
			std::cerr << std::hex << "[" << (unsigned)((unsigned char)(*iter)&0xff) << "]" << std::dec ;
	}
	std::cerr <<  "'" << std::endl ;
}

#endif
