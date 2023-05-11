/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiMsgEditor_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "stringfunc.hpp"
#include "rti_fixture.h"

#include "RtiMsgEditor.h"
using namespace Mplane ;

class RtiMsgEditorTests : public RtiTests {

};

class TestTelnetSrc : public ITelnet {
public:
	TestTelnetSrc() :
		mMsgIdx(0),
		mMsgList(),
		mSentList()
	{}
	TestTelnetSrc(std::vector<std::string> messages) :
		mMsgIdx(0),
		mMsgList(messages.begin(), messages.end()),
		mSentList()
	{ }
	virtual ~TestTelnetSrc() {}

	/**
	 * Send a message to the telnet interface
	 * @param msg
	 */
	virtual bool send(const std::string& msg)
	{
		std::cerr << "SENT: "  ; dumpchars(msg) ;
		mSentList.push_back(msg) ;
		return true ;
	}

	/**
	 * Receive a message from the telnet interface
	 * @param msg
	 */
	virtual int recv(std::string& msg)
	{
		msg.clear() ;
		if (mMsgIdx < mMsgList.size())
			msg = mMsgList[mMsgIdx++] ;
		return msg.size() ;
	}

	// Test Interface
	void addMsg(std::string msg)
	{
		mMsgList.push_back(msg) ;
	}

	void reset()
	{
		mMsgIdx = 0 ;
		mSentList.clear() ;
	}

	std::vector<std::string> getSent()
	{
		std::vector<std::string> sent ;
		using std::swap ;
		swap(sent, mSentList) ;
		return sent ;
	}

	static void dumpchars(const std::string& data)
	{
		std::cerr << "'"  ;
		for (std::string::const_iterator iter(data.begin()); iter != data.end(); ++iter)
		{
			if ((*iter >= ' ') && (*iter < 0x7f))
				std::cerr << *iter ;
			else
				std::cerr << std::hex << "[" << (unsigned)((unsigned char)(*iter)&0xff) << "]" << std::dec ;
		}
		std::cerr <<  "'" << std::endl ;
	}

private:
	unsigned mMsgIdx ;
	std::vector<std::string> mMsgList ;

	std::vector<std::string> mSentList ;
};



//===================================================================================================================
/*
 * Unit tests
 */

#if 0
//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiMsgEditorTests, Basic)
{
	std::string result ;
	TestTelnetSrc tsrc ;

    std::string pathSeperators( DirNode::PATHSEP + "." ) ;
	RtiMsgEditor msgEd(&tsrc, pathSeperators) ;

	std::string prompt(">") ;
	std::string command ;
	std::vector<std::string> tabCompletion ;

	msgEd.handle(command, tabCompletion, prompt) ;
	tsrc.reset() ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiMsgEditorTests, Newline)
{
	std::string result ;
	TestTelnetSrc tsrc ;

    std::string pathSeperators( DirNode::PATHSEP + "." ) ;
	RtiMsgEditor msgEd(&tsrc, pathSeperators) ;

	tsrc.addMsg(std::string("\r\n\0")) ;
	tsrc.addMsg(std::string("cmd1\r\n\r\r\r\0")) ;
	tsrc.addMsg(std::string("cmd2\n")) ;

	std::string prompt(">") ;
	std::string command ;
	std::vector<std::string> tabCompletion ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("cmd1\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("cmd2\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiMsgEditorTests, IAC)
{
	std::string result ;
	TestTelnetSrc tsrc ;

    std::string pathSeperators( DirNode::PATHSEP + "." ) ;
	RtiMsgEditor msgEd(&tsrc, pathSeperators) ;

	// send max num telnet chars
	tsrc.addMsg(std::string("\377-1")) ;

	// start sub negotiation
	tsrc.addMsg(std::string("\377\372 01234567890")) ;

	// end of sub-neg
	tsrc.addMsg(std::string("\377\360")) ;

	std::string prompt(">") ;
	std::string command ;
	std::vector<std::string> tabCompletion ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string(""), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string(""), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string(""), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RtiMsgEditorTests, Edit)
{
	std::string result ;
	TestTelnetSrc tsrc ;

    std::string pathSeperators( DirNode::PATHSEP + "." ) ;
	RtiMsgEditor msgEd(&tsrc, pathSeperators) ;

	// max CTRL seq
	tsrc.addMsg(std::string("\001-12")) ;

	// TAB TAB
	tsrc.addMsg(std::string("\t\t")) ;

	// TAB TAB UP DOWN
	tsrc.addMsg(std::string("\t\t\033[A\033[B")) ;

	// String [0123456789]
	tsrc.addMsg(std::string("0123456789\n")) ;

	// UP LEFT RIGHT HOME END HOME END [0123456789]
	tsrc.addMsg(std::string("\033[A\033[D\033[C\033[1~\033[4~\033[H\033[F\n")) ;

	// UP BACK BACK AB [01234567AB]
	tsrc.addMsg(std::string("\033[A\b\177AB\n")) ;

	// UP LEFT LEFT DEL [01234567B]
	tsrc.addMsg(std::string("\033[A\033[D\033[D\033[3~\n")) ;

	// INS not supported
	// UP HOME INS abcd [abcd01234567B]
	tsrc.addMsg(std::string("\033[A\033[H\033[2~abcd\n")) ;

	// UP PGUP PGDOWN ?
	tsrc.addMsg(std::string("\033[A\033[5~\033[6~\n")) ;

	std::string prompt(">") ;
	std::string command ;
	std::vector<std::string> tabCompletion ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string(""), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string(""), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string(""), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	// string [0123456789]
	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("0123456789\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	// string [0123456789]
	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("0123456789\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	// string [01234567AB]
	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("01234567AB\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	// string [01234567B]
	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("01234567B\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	// string [abcd01234567B]
	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("abcd01234567B\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

	// string [abcd01234567B]
	EXPECT_TRUE(msgEd.handle(command, tabCompletion, prompt)) ;
	EXPECT_EQ(std::string("abcd01234567B\r"), command) ;
	std::cerr << "Command: " ; tsrc.dumpchars(command) ; std::cerr << std::endl ;

}
#endif

//===================================================================================================================
