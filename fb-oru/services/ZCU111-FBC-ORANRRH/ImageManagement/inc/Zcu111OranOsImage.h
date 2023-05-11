/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111OranOsImage.h
 * \brief     Os image class
 *
 *
 * \details   Handles download and install of OS images
 *
 * OS image handling is different to app/lib images. Here we download, extract, and save the OS images into NOR flash then
 * delete the tarball to save space.
 *
 * The 'current' link is maintained in the os-images directory, but in this case it points at the MD5 file that is saved
 * in the directory.
 *
 * Also, links 'boot1', 'boot2', 'dtb1', 'dtb2', and 'u-boot' are maintained pointing to the current MD5 of the tarball
 * programmed into that NOR partition. These are used to determine if the partition needs to be updated.
 *
 */


#ifndef Zcu111OranOsIMAGE_H_
#define Zcu111OranOsIMAGE_H_

#include "IOsImage.h"
#include "IImageManagement.h"
#include "ImageBase.h"

namespace Mplane {

class IBootEnv ;

class Zcu111OranOsImage : public virtual IOsImage, public ImageBase
{
public:
	using super = ImageBase ;

    // Constructor
	explicit Zcu111OranOsImage(ImageTask& task) ;

	// Destructor
	virtual ~Zcu111OranOsImage() ;

	/**
	 * Returns the number of files that this IImage class needs to download. Used to determine total progress
	 */
	virtual unsigned numFiles() const override ;

	/**
	 * Get an (over) estimate of the total install time, in seconds, for this image
	 */
	virtual unsigned installTimeSecs() const override ;

	/**
	 * Called after object creation in order to perform any other initialisation tasks that can't be done
	 * during initialisation (i.e. ensures all virtual methods get called correctly)
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if initialised ok, false otherwise
	 */
	virtual bool initialise(std::string& failReason) override ;

	/**
	 * Utility provided by the derived class that converts a version and build number into a full image name. Uses
	 * the current build settings for this application along with the type of the derived object (e.g. app, library, os etc)
	 * to create the name
	 *
	 * @param version
	 * @param buildNumber
	 */
	virtual std::string formatName(const std::string& version, const std::string& buildNumber) override ;


    /*! @brief  Display information about this image type
     *
     */
    virtual void show(std::ostream& os = std::cout) const override ;

    /**
     * Utility that returns information on the current install image - for OS this shows all links
     * @return string containing information, or empty string if none
     */
    virtual std::string info() const override ;


	/**
	 * Get the currently active OS bank
	 */
	virtual IImageTypes::OsImageBank getOsBank(void) override ;

	/**
	 * Set whether next OS install will also install a new u-boot
	 * @param ubootInstall	if true will install u-boot
     * @param failReason Set to failure reason if returns false
	 * @return true if ok
	 */
	virtual bool setUbootInstall(bool ubootInstall, std::string& failReason) override ;

	/**
	 * Get current u-boot install value
	 */
	virtual bool getUbootInstall(void) override ;

    /**
     * Roll install back to previous installation
     * @param failReason
     * @return true if rollback was successful
     */
    virtual bool usePrevious(std::string failReason) override ;

	/**
	 * Clean out old images from the install directory. This instance does nothing
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool clean(std::string& failReason) override ;


protected:

    // Overridable ALGORITHM methods

    /**
     * Has the required file already been downloaded and exist in the install directory, and passes check
     * @param failReason Set to failure reason if returns false
     * @return true if exists and passes check
     */
    virtual bool alreadyDownloaded() override ;

    /**
     * Has the required file already been downloaded and installed
     * @param failReason Set to failure reason if returns false
     * @return true if installed
     */
    virtual bool alreadyInstalled() override ;

    /**
     * Download the file(s) ready for checking
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    virtual bool download(std::string& failReason) override ;

    /**
     * Check the file(s)
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    virtual bool check(std::string& failReason) override ;

    /**
     * Install the file(s)
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    virtual bool install(std::string& failReason) override ;

private:

    /**
     * Private utility for finding out if *any* os is installed in the specified bank
     * @param bank
     * @return true if something is installed
     */
    bool isBankInstalled(IImageTypes::OsImageBank bank) const ;

    /**
     * Private utility for finding out if specific os is installed in the specified bank
     * @param bank
     * @return true if something is installed
     */
    bool isBankVersionInstalled(IImageTypes::OsImageBank bank) const ;

    /**
     * Install the file(s) into the specified bank
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    bool installBank(IImageTypes::OsImageBank bank, std::string& failReason) ;


    /**
     * Program the image into the specified partition
     * @param filePath	Path to image
     * @param partition	Full partition name
     * @param failReason	Failure reason string set on failure
     * @return true if programmed ok
     */
    bool flashNor(const std::string& filePath, const std::string& partition, std::string& failReason) ;

    /**
     * Program the image into the specified partition
     * @param filePath	Path to image
     * @param partition	Partition base name - has bank number appended to create full partition name
     * @param failReason	Failure reason string set on failure
     * @return true if programmed ok
     */
    bool flashBank(IImageTypes::OsImageBank bank, const std::string& filePath, const std::string& partition, std::string& failReason) ;

    /**
     * Manage the OS links - create appropriate links for this download
     * @param failReason
     * @return true if ok
     */
    bool manageLinks(IImageTypes::OsImageBank bank, std::string& failReason) ;

    /**
     * Given a base name and a bank, create a bank-specific name
     * @param name	Base name
     * @param bank	Memory bank
     * @return bank name
     */
    std::string bankName(const std::string& name, IImageTypes::OsImageBank bank) const ;

    /**
     * Given a bank, returns the other
     * @param bank
     * @return other bank
     */
    IImageTypes::OsImageBank getOtherBank(IImageTypes::OsImageBank bank) const ;

    /**
     * Get the currently active OS bank
     * @return active bank
     */
    IImageTypes::OsImageBank getActiveBank() const ;

    /**
     * Set the currently active OS bank
     * @return true if ok
     */
    bool setActiveBank(IImageTypes::OsImageBank bank) ;

private:
	// skip files (for file status)
	void skipUboot() ;
	void skipBank() ;
	void skipFiles() ;

private:
    // Boot environment
	std::shared_ptr<IBootEnv> mBootEnv ;

	// Active OS bank at boot up
	IImageTypes::OsImageBank mBootBank ;

	// Current active OS bank
	IImageTypes::OsImageBank mActiveBank ;

	// whether to install u-boot or not
	bool mUbootInstall ;

	// Nor partition names and their MTD device
	std::map<std::string, std::string> mPartitionNames ;

	// timings to use to estimate how long a flash will take (use 1.5 times for timeout)
	std::map<std::string, unsigned> mDefaultFlashTimes ;


} ;


}

#endif /* Zcu111OranOsIMAGE_H_ */
