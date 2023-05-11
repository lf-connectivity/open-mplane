/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PkgImage.h
 * \brief     Package image class
 *
 *
 * \details   Handles download and install of packages. These are text files containing the list of images that make up the
 * package. This object behaves like the ImageManagement object in that it also co-ordinates the other Image objects in
 * order to get them to download and install their images.
 *
 */


#ifndef PkgIMAGE_H_
#define PkgIMAGE_H_

#include <map>
#include "IImageTypes.h"
#include "ImageBase.h"

namespace Mplane {

class PkgImage : public ImageBase
{
public:
	using super = ImageBase ;

    // Constructor
	explicit PkgImage(ImageTask& task) ;

	// Destructor
	virtual ~PkgImage() ;

	/**
	 * Returns the number of files that this IImage class needs to download. Used to determine total progress
	 */
	virtual unsigned numFiles() const override ;

	/**
	 * Called after object creation in order to perform any other initialisation tasks that can't be done
	 * during initialisation (i.e. ensures all virtual methods get called correctly)
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if initialised ok, false otherwise
	 */
	virtual bool initialise(std::string& failReason) override ;

	/**
	 * Set the url of the remote directory in which the file will be served from. Ensures that all Image objects
	 * are set to the same url
	 * @param url
     * @param failReason Set to failure reason if returns false
	 */
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) override ;

	/**
	 * Utility provided by the derived class that converts a version and build number into a full image name. Uses
	 * the current build settings for this Pkglication along with the type of the derived object (e.g. Pkg, library, os etc)
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


    // Specific to package

    /**
     * Returns the number of package files stored
     */
    virtual unsigned numPackagesInstalled() const ;


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
     * Install the file(s)
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    virtual bool install(std::string& failReason) override ;

private:
    /**
     * Read the package file and fill in the map with the settings
     * @param pkgMap		Map filled in with package file contents
     * @param failReason	Failure reason string if unable to read package
     * @return true if read ok; false otherwise
     */
    bool readPackageFile(std::map<IImageTypes::Type, std::string>& pkgMap, const std::string& filePath,
    		std::string& failReason) ;
} ;


}

#endif /* PkgIMAGE_H_ */
