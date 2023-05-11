/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestAppSettings.h
 * \brief     Application build settings
 *
 *
 * \details   Singleton object containing the current build settings for this particular application/customer/board
 * combination
 *
 */


#ifndef TESTAPPSETTINGS_H_
#define TESTAPPSETTINGS_H_

#include "IAppSettings.h"

namespace Mplane {

class TestAppSettings : public IAppSettings {

public:
	TestAppSettings() :
		mDuplex(DUPLEX_TDD),
		mApp(APP_ORANRRH),
		mFibreInterface(IF_ORAN),
		mBoard(BOARD_HOST),
		mCustomer(CUSTOMER_GENERIC),
		mBuildVersion("0.0"),
		mBuildNumber(1),
		mFpgaPart(""),
		mFpgaBuild(""),
		mGitVersions({ {"common", "1234"} })
	{}
	virtual ~TestAppSettings() {}

	/**
	 * Get the duplex type (TDD, FDD)
	 */
	virtual DuplexType getDuplex() const {return mDuplex;}
	virtual std::string getDuplexString() const {return mDuplexStr;}

	/**
	 * Get the application (Radio, DIT etc)
	 */
	virtual AppType getApp() const {return mApp;}
	virtual std::string getAppString() const {return mAppStr;}

	/**
	 * Get fibre interface (CPRI, OBSAI etc)
	 */
	virtual FibreInterfaceType getFibreInterface() const {return mFibreInterface;}
	virtual std::string getFibreInterfaceString() const {return mFibreInterfaceStr;}

	/**
	 * Get board (ETNA, DEMI etc)
	 */
	virtual BoardType getBoard() const {return mBoard;}
	virtual std::string getBoardString() const {return mBoardStr;}

	/**
	 * Get customer (ALU etc)
	 */
	virtual CustomerType getCustomer() const {return mCustomer;}
	virtual std::string getCustomerString() const {return mCustomerStr;}

	/**
	 * Get build version string in the form "VV.RR"
	 */
	virtual std::string getBuildVersion() const {return mBuildVersion;}

	/**
	 * Get the build number
	 */
	virtual unsigned getBuildNumber() const {return mBuildNumber;}

	/**
	 * FPGA part number this code was built with
	 */
	virtual std::string getFpgaPart() const { return mFpgaPart; }

	/**
	 * FPGA build number this code was built with
	 */
	virtual std::string getFpgaBuild() const { return mFpgaBuild; }

	virtual std::vector< std::pair<std::string, std::string> > getGitVersions() const override { return mGitVersions; }


	// Test Interface

	void setApp(AppType app) {
		mApp = app;
	}

	void setBoard(BoardType board) {
		mBoard = board;
	}

	void setBuildNumber(unsigned buildNumber) {
		mBuildNumber = buildNumber;
	}

	void setBuildVersion(const std::string& buildVersion) {
		mBuildVersion = buildVersion;
	}

	void setCustomer(CustomerType customer) {
		mCustomer = customer;
	}

	void setDuplex(DuplexType duplex) {
		mDuplex = duplex;
	}

	void setFibreInterface(FibreInterfaceType fibreInterface) {
		mFibreInterface = fibreInterface;
	}


	void setAppString(const std::string& str) {
		mAppStr = str;
	}

	void setBoardString(const std::string& str) {
		mBoardStr = str;
	}

	void setCustomerString(const std::string& str) {
		mCustomerStr = str;
	}

	void setDuplexString(const std::string& str) {
		mDuplexStr = str;
	}

	void setFibreInterfaceString(const std::string& str) {
		mFibreInterfaceStr = str;
	}


private:
	DuplexType mDuplex ;
	AppType mApp ;
	FibreInterfaceType mFibreInterface ;
	BoardType mBoard ;
	CustomerType mCustomer ;
	std::string mBuildVersion ;
	unsigned mBuildNumber ;

	// string representations
	std::string mDuplexStr ;
	std::string mAppStr ;
	std::string mFibreInterfaceStr ;
	std::string mBoardStr ;
	std::string mCustomerStr ;
	std::string mFpgaPart ;
	std::string mFpgaBuild ;

	std::vector< std::pair<std::string, std::string> > mGitVersions ;
} ;

}

#endif /* TESTAPPSETTINGS_H_ */
