/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAppSettings.h
 * \brief     Application build settings
 *
 *
 * \details   Singleton object containing the current build settings for this particular application/customer/board
 * combination
 *
 */


#ifndef IAPPSETTINGS_H_
#define IAPPSETTINGS_H_

#include <string>
#include <vector>
#include <utility>

namespace Mplane {

/**
 * The IAppSettings is a pure virtual class that defines an interface to a common application
 * module that is used to provide 'build time' data to other modules within the software application.
 *
 * Any new application, customer or major feature must be added to the standard enumeration
 * within this base class. The application specific build creates a set of defines in a build
 * specific config.h file.
 *
 * @see The Mplane::AppSettings common implementation as an example.
 *
 * The Mplane::IAppSettingsFactory is used to get a reference to the current IAppSettings instance;
 *
 *
 */
class IAppSettings {
public:
	enum DuplexType {
		DUPLEX_FDD,         //!> Supports only Frequency Division Duplex
		DUPLEX_TDD,         //!> Supports only Time Division Duplex
		DUPLEX_FDD_TDD      //!> Supports both Time and Frequency Division Duplex
	} ;
	enum AppType {
		// Radio applications
		APP_RRH,			//!> Generic radio application
		APP_ORANRRH,		//!> ORAN Remote Radio Head
	} ;
	enum FibreInterfaceType {
		IF_ORAN,
	};
	enum BoardType {
		BOARD_HOST,
		BOARD_ZCU111,
		BOARD_ATLAS,
		BOARD_FBZCU27,
	};
	enum CustomerType {
		CUSTOMER_GENERIC,   //!> Generic "un-named" Customer
		CUSTOMER_FBC,		//!> FaceBook Consortium
		CUSTOMER_MPLANE,
	};

public:
	IAppSettings() {} ;
	virtual ~IAppSettings() {} ;

	/**
	 * Get the duplex type (TDD, FDD)
	 */
	virtual DuplexType getDuplex() const =0 ;
	/**
	 * Get the duplex type as a string
	 */
	virtual std::string getDuplexString() const =0 ;

	/**
	 * Get the application (Radio, DIT etc)
	 */
	virtual AppType getApp() const =0 ;
	/**
	 * Get the application as a string
	 */
	virtual std::string getAppString() const =0 ;

	/**
	 * Get fibre interface (CPRI, OBSAI etc)
	 */
	virtual FibreInterfaceType getFibreInterface() const =0 ;
	/**
	 * Get fibre interface as a string
	 */
	virtual std::string getFibreInterfaceString() const =0 ;

	/**
	 * Get board (ETNA, DEMI etc)
	 */
	virtual BoardType getBoard() const =0 ;
	/**
	 * Get board as a string
	 */
	virtual std::string getBoardString() const =0 ;

	/**
	 * Get customer (ALU etc)
	 */
	virtual CustomerType getCustomer() const =0 ;
	/**
	 * Get customer as a string
	 */
	virtual std::string getCustomerString() const =0 ;

	/**
	 * Get build version string in the form "VV.RR"
	 */
	virtual std::string getBuildVersion() const =0 ;

	/**
	 * Get the build number
	 */
	virtual unsigned getBuildNumber() const =0 ;

	/**
	 * FPGA part number this code was built with
	 */
	virtual std::string getFpgaPart() const =0 ;

	/**
	 * FPGA build number this code was built with
	 */
	virtual std::string getFpgaBuild() const =0 ;

	/**
	 * Get a list of the repositories and the git commit tags for each when this application was built
	 * @return vector of pairs. First is repository; second is git tag
	 */
	virtual std::vector< std::pair<std::string, std::string> > getGitVersions() const =0 ;
} ;

}

#endif /* IAPPSETTINGS_H_ */
