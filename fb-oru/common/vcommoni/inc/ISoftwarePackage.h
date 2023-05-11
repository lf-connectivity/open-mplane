/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISoftwarePackage.h
 * \brief     Represents a complete software package
 *
 *
 * \details   Maintains the information about a software installation package and reads/writes a config file that contains the
 * 				latest settings/status of that package. A package can then be allocated to a software slot.
 *
 */


#ifndef VCOMMONI_INC_ISOFTWAREPACKAGE_H_
#define VCOMMONI_INC_ISOFTWAREPACKAGE_H_

#include <string>
#include <iostream>
#include <memory>

namespace Mplane {

/*!
 * \class  ISoftwarePackage
 * \brief
 * \details
 *
 */
class ISoftwarePackage {
public:
	ISoftwarePackage() {}
	virtual ~ISoftwarePackage() {}

	/**
	 * Get the path of the manifest file
	 */
	virtual std::string manifestPath() const =0 ;

	/**
	 * Make this package active
	 */
	virtual bool activate() =0 ;

	/**
	 * is this the active package
	 */
	virtual bool isActive() const =0 ;

	/**
	 * is this a read-only package
	 */
	virtual bool isReadOnly() const =0 ;

	/**
	 * Change the read-only status
	 */
	virtual bool setReadOnly(bool readOnly) =0 ;

	/**
	 * Is this package valid and ok to be activated?
	 */
	virtual bool isValid() const =0 ;

	/**
	 * Is this the running package?
	 */
	virtual bool isRunning() const =0 ;

	/**
	 * Use IImageManagement object to determine what the expected maximum time for installation will be
	 */
	virtual unsigned requiredInstallTimeSecs() const =0 ;

	/**
	 * Use the IImageManagement object to install this package. If timeoutSecs > 0 then
	 * maintains a timeout timer and aborts the install if timer expires.
	 *
	 * Returns FALSE with error reason on error; TRUE on success
	 */
	virtual bool installImage(unsigned timeoutSecs, std::string& error) =0 ;

	/**
	 * Create the required md5 files (as necessary) to go with the package files
	 */
	virtual bool createMd5Files(std::string& error) =0 ;

	/*
	 * Debug - output the current slot information
	 */
	virtual void show(std::ostream& os = std::cout) =0 ;

	// Manifest API

	virtual std::string vendorCode() const =0 ;
	virtual std::string productCode() const =0 ;
	virtual std::string buildName() const =0 ;
	virtual std::string buildVersion() const =0 ;
	virtual std::string buildId() const =0 ;

	virtual std::string osFileName() const =0 ;
	virtual std::string osFileVersion() const =0 ;
	virtual std::string osPath() const =0 ;
	virtual std::string osChecksum() const =0 ;
	virtual bool osIntegrity() const =0 ;

	virtual std::string appFileName() const =0 ;
	virtual std::string appFileVersion() const =0 ;
	virtual std::string appPath() const =0 ;
	virtual std::string appChecksum() const =0 ;
	virtual bool appIntegrity() const =0 ;

} ;

}

#endif /* VCOMMONI_INC_ISOFTWAREPACKAGE_H_ */
