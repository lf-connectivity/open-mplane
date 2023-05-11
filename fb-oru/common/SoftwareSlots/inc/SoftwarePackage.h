/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwarePackage.h
 * \brief     Represents a complete software package
 *
 *
 * \details   Maintains the information about a software installation package and reads/writes a config file that contains the
 * 				latest settings/status of that package. A package can then be allocated to a software slot.
 *
 */


#ifndef SOFTWARESLOTS_INC_SOFTWAREPACKAGE_H_
#define SOFTWARESLOTS_INC_SOFTWAREPACKAGE_H_

#include <string>
#include <iostream>
#include <memory>

#include "ISoftwarePackage.h"
#include "FileConfig.h"

namespace Mplane {

/*!
 * \class  SoftwarePackage
 * \brief
 * \details
 *
 */
class SoftwarePackage : public virtual ISoftwarePackage {
public:
	/**
	 * Created with the top-level management path and the path to a package manifest file
	 */
	SoftwarePackage(const std::string& mgmtPath, const std::string& appsPath, const std::string& osPath, const std::string& manifestFile) ;
	virtual ~SoftwarePackage() ;

	/**
	 * Get the path of the manifest file
	 */
	virtual std::string manifestPath() const override ;

	/**
	 * Make this package active
	 */
	virtual bool activate() override ;

	/**
	 * is this the active package
	 */
	virtual bool isActive() const override ;


	/**
	 * Is this package valid and ok to be activated?
	 */
	virtual bool isValid() const override ;

	/**
	 * Is this the running package?
	 */
	virtual bool isRunning() const override ;

	/**
	 * is this a read-only package
	 */
	virtual bool isReadOnly() const override ;

	/**
	 * Change the read-only status
	 */
	virtual bool setReadOnly(bool readOnly) override ;

	/**
	 * Use IImageManagement object to determine what the expected maximum time for installation will be
	 */
	virtual unsigned requiredInstallTimeSecs() const override ;


	/**
	 * Use the IImageManagement object to install this package. If timeoutSecs > 0 then
	 * maintains a timeout timer and aborts the install if timer expires.
	 *
	 * Returns FALSE with error reason on error; TRUE on success
	 */
	virtual bool installImage(unsigned timeoutSecs, std::string& error) override ;

	/**
	 * Create the required md5 files (as necessary) to go with the package files
	 */
	virtual bool createMd5Files(std::string& error) override ;


	/*
	 * Debug - output the current slot information
	 */
	virtual void show(std::ostream& os = std::cout) override ;

	// Manifest API

	virtual std::string vendorCode() const override ;
	virtual std::string productCode() const override ;
	virtual std::string buildName() const override ;
	virtual std::string buildVersion() const override ;
	virtual std::string buildId() const override ;

	virtual std::string osFileName() const override ;
	virtual std::string osFileVersion() const override ;
	virtual std::string osPath() const override ;
	virtual std::string osChecksum() const override ;
	virtual bool osIntegrity() const override ;

	virtual std::string appFileName() const override ;
	virtual std::string appFileVersion() const override ;
	virtual std::string appPath() const override ;
	virtual std::string appChecksum() const override ;
	virtual bool appIntegrity() const override ;

private:
	void checkValidityLinks() ;
	void checkManifest() ;
	std::string value(const std::string& variable) const ;
	std::string value(const std::string &section, const std::string& variable) const ;
	bool createMd5(const std::string& dir, const std::string& packageFile, const std::string& md5, std::string& error) ;

private:
	std::string mMgmtPath ;
	std::string mAppsPath ;
	std::string mOsPath ;
	std::string mManifestPath ;
	std::string mReadOnlyLink ;
	bool mRunning ;

	// Package information
	FileConfig mManifest ;

	bool mManifestValid ;
	bool mMarkedInvalid ;

	bool mAppIntegrity ;
	bool mOsIntegrity ;

} ;

}

#endif /* SOFTWARESLOTS_INC_SOFTWAREPACKAGE_H_ */
