/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiMsgEditor.h
 * \brief     Telnet handler to make TIF more user friendly
 *
 *
 * \details   Provides interface to make the TIF more user friendly. Supports command line editing, history, CTRL-C,
 * 			TAB completion etc.
 *
 */

#ifndef RTIMSGEDITOR_H_
#define RTIMSGEDITOR_H_

#include <map>
#include <vector>
#include <string>

#include "ITelnet.h"

namespace Mplane {


/**
 * Message editor class
 */
class RtiMsgEditor {
public:
	RtiMsgEditor(ITelnetSend* telnetSend, const std::string& pathSeparators, unsigned historyLength = 128) ;
	virtual ~RtiMsgEditor() ;

	/**
	 * Process received chars
	 * @param command	Set to the complete command when a terminating CR is seen
	 * @param tabCompletion	List of tab completion paths
	 * @return true if we received some characters; false if not
	 */
	virtual bool handle(const std::string& recv, std::string& command, const std::vector<std::string>& tabCompletion, const std::string& prompt) ;

private:
	// see if char is handled by one of these methods
	bool checkEdit(const char cc, const std::vector<std::string>& tabCompletion, const std::string& prompt) ;
	bool checkNewline(const char cc) ;

	// handle the chars
	void handleEdit(const std::vector<std::string>& tabCompletion, const std::string& prompt) ;
	void handleChar(const char cc) ;

	// history
	void historyAdd(const std::string& command) ;
	std::string historyUp() ;
	std::string historyDown() ;
	std::string historyGet(unsigned idx) const ;

	// tab complete
	std::string tabComplete(const std::vector<std::string>& tabCompletion) ;
	std::string tabCompleteAlternatives(const std::vector<std::string>& tabCompletion) ;
	std::vector<std::string> tabCompleteList(std::string& prefix, std::string& frag,
			const std::vector<std::string>& tabCompletion);

	// edit utils
	void deleteLine() ;
	void setCmd(const std::string& newCommand) ;

private:
	ITelnetSend* mTelnetSend ;

	// list of characters that have been used as path separators
	std::string mPathSeparators ;

	// storage for the history of commands
	std::vector<std::string> mHistory ;
	const unsigned mMaxHistory ;
	unsigned mHistoryIdx ;

	// buffer for the command so far
	std::string mCommand ;

	// cursor position in command
	std::size_t mCursor ;

	// buffer for echoing chars back to client as we go
	std::string mEcho ;

	// Keep track of control chars and escape codes
	unsigned mControlIdx ;
	std::string mControlBuffer ;
	unsigned mTabCount ;

	// Buffer for the received chars
	unsigned mRecvIdx ;
	std::string mRecvBuffer ;
} ;

}

#endif /* RTIMSGEDITOR_H_ */
