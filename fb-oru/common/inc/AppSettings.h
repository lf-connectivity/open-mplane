/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppSettings.h
 * \brief     Application build settings
 *
 *
 * \details   Singleton object containing the current build settings for this particular application/customer/board
 * combination
 *
 */


#ifndef APPSETTINGS_H_
#define APPSETTINGS_H_

#include <string>
#include <vector>
#include <utility>

#include "IAppSettings.h"

namespace Mplane {

class AppSettings : public IAppSettings {

public:
	AppSettings() ;
	virtual ~AppSettings() ;

	/**
	 * Get the duplex type (TDD, FDD)
	 */
	virtual DuplexType getDuplex() const ;
	/**
	 * Get the duplex type as a string
	 */
	virtual std::string getDuplexString() const ;

	/**
	 * Get the application (Radio, DIT etc)
	 */
	virtual AppType getApp() const ;
	/**
	 * Get the application as a string
	 */
	virtual std::string getAppString() const ;

	/**
	 * Get fibre interface (CPRI, OBSAI etc)
	 */
	virtual FibreInterfaceType getFibreInterface() const ;
	/**
	 * Get fibre interface as a string
	 */
	virtual std::string getFibreInterfaceString() const ;

	/**
	 * Get board (ETNA, DEMI etc)
	 */
	virtual BoardType getBoard() const ;
	/**
	 * Get board as a string
	 */
	virtual std::string getBoardString() const ;

	/**
	 * Get customer (ALU etc)
	 */
	virtual CustomerType getCustomer() const ;
	/**
	 * Get customer as a string
	 */
	virtual std::string getCustomerString() const ;

	/**
	 * Get build version string in the form "VV.RR"
	 */
	virtual std::string getBuildVersion() const ;

	/**
	 * Get the build number
	 */
	virtual unsigned getBuildNumber() const ;


	/**
	 * FPGA part number this code was built with
	 */
	virtual std::string getFpgaPart() const ;

	/**
	 * FPGA build number this code was built with
	 */
	virtual std::string getFpgaBuild() const ;

	/**
	 * Get a list of the repositories and the git commit tags for each when this application was built
	 * @return vector of pairs. First is repository; second is git tag
	 */
	virtual std::vector< std::pair<std::string, std::string> > getGitVersions() const override ;

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

#endif /* APPSETTINGS_H_ */
