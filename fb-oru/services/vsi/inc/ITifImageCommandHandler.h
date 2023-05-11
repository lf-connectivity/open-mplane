#ifndef _VRS_ITIFIMAGECOMMANDHANDLER_H_
#define _VRS_ITIFIMAGECOMMANDHANDLER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITifImageCommandHandler.h
 * \brief     Interface class that controls and monitors the TIF commands for Image Management
 *
 *
 * \details   The class interface definition for TIF commands for Image Management
 *
 */

#include "GlobalTypeDefs.h"
#include <memory>
#include <string>

namespace Mplane
{

// forward declarations go here


/*! \brief The TIF commands handler for image handling.
 *
 * The TifImageCommandHandler class provides methods to handle a TIF interface to the
 * image management functions, allowing a tester to access and manipulate images.
 *
 * The image handling provides interfaces to:\n
 * software download, install, clean, list, delete, swap, fallback
 *
 *
 * Non-customer download:
 * A non-customer download sequence involves a file 'fetch, process, persist'.
 *
 * See legacy file FlashImage.pm for implementation example.
 *
 * This sequence describes the steps that make up a non-customer image download on legacy RRHs,
 * triggered by the appropriate command via the user command interface, eg. with an 'img get' command.
 *
 * Executes the three sequential stages to fetch, process and make persistent the image:
 * - prepare by making the image directory that will store temporary files during the sequence, '/tmp'
 * - a. fetch the image and its md5 file validate them.
 *   - returns "nack" with '...error info...', or "ack" with localPath and localPathMd5 details
 *   - handle the manifest data:
 *     - read the file /manifest (installed from the OS) that contains the manifests for the OS, SW and FPGA
 *       used to initialise the RRH
 *     - load in the configured manifest from /nandflash/config/manifest if it exists, to override the data
 *       in the os-provided one
 *     - combine the manifests
 *   - extract the current build info from the manifest data
 *   - Create the destination filenames from the URL destination file, tmpfile and tmpfilemd5
 *     - Determine whether the source URL is a file URL or not
 *       - File URL:
 *         - check the files exist, error exit if not
 *         - if the source md5 file does not exist then create it now using command
 *           'md5sum <srcfilename> > <srcfilename.md5>'
 *         - check the MD5 is correct, exit with error if failed
 *         - Note:  the tmpfile contains the full URL to the local file
 *       - Not file URL:
 *         - check it is a valid URL, error exit if not
 *         - extract the target file name from the URL, error exit if invalid or bad filename
 *     - We now have the destination filenames tmpfile and tmpfilemd5
 *   - get the build type information from the tar file as it is fetched from the server, error exit if failed
 *     - file URL:  tar the file to stdout, 'tar zxOf'
 *     - non file URL:  get the file from the server, then tar the file to stdout, 'tar zxOf'
 *     - parse the manifest information to extract the manifest info
 *   - check the build types, error exit if invalid
 *   - For a non-file URL:
 *     - Perform the download from URL to destination tmpfile, 'wget -q -O <tmpfile> <URL>',
 *       error exit if failed
 *     - Perform the download from URL to destination tmpfile.md5, 'wget -q -O <tmpfile.md5> <URL.md5>',
 *        error exit if failed
 *     - if the source md5 file does not exist then create it now using command
 *       'md5sum <tmpfile> > <tmpfile.md5>'
 *     - check the MD5 is correct, exit with error if failed
 *   - At this stage the fetch is complete and we have the 'localPath' and 'localPathMd5' details
 * - b. process the files from the fetch process above
 *   - returns "nack" with '...error info...', or "ack" with the files to persist
 *   - create the 'pkg' .info file in the temporary location for the downloaded file
 *     - extract the build number from the tar file, 'tar xzOf <localPath> <file>', exit with error if failed
 *     - read the md5 file <tmpfile.md5>, exit with error if failed
 *     - create the info file with the contents for software, fpga, os, all:
 *       - name
 *       - type
 *       - md5
 *       - build number
 * - c. persist the files from the image
 *   - for each of the files downloaded and their derivatives, i.e. the tar'd extracted files
 *     - if the destination file already exists and is exactly the same as the source file then do not copy to NVM
 *     - move the files to the NVM destination path already determined
 *       eg. 'flash-write mv -f fileToWrite, destPath'
 *   - tidy up: tidy up all the temporary files that were created during the sequence
 *   - verify the file after move to nandflash, for the target and md5 files only, exit with error if failed
 *
 *
 * Debug levels used in this class:
 * - LOG_DEBUG_LEVEL_1 : Background command in progress
 * - LOG_DEBUG_LEVEL_2 : Parsing TIF Command parameters
 * - LOG_DEBUG_LEVEL_3 : Handle TIF command
 *
 */
class ITifImageCommandHandler
{

public:

    // these are the TIF commands available for image manipulation
    typedef enum tifImageCommand
    {
        GET = 1,  // get an image, i.e. download via http from a server
        INSTALL,  // install an already downloaded image, means make it current
        DELETE,   // delete an image
        CURRENT,  // list the current images
        LIST,     // list the available images
        SWAP     // swap the current and previous images
    } TifImageCommand_t;

    /**
     * mandatory destructor. Should never be called except by unit test code
     */
    virtual ~ITifImageCommandHandler() {} ;


    /*! The getInterface method to get the instance of TIF Image Command Handler
     *
     * \return Pointer to the ITifImageCommandHandler instance
     */
    static std::shared_ptr<ITifImageCommandHandler> getInterface();

    /**
     * @brief Print out the status of the image management to stdout
     * Used for debug only
     */
    virtual void showIm(std::ostream& os = std::cout) const = 0;

    virtual void clean() = 0;

    /**
     * Starts the TifImageCommandHandler class implementation.
     */
    virtual void startTich() = 0;

    /**
     * This is the method that takes two parameters for the 'command' and 'command info'
     * and executes the command either instantly or in background if the appropriate option is set.
     *
     * \param TIF command
     * \param command parameters
     * \param output stream to output the result to
     *
     * \return the exit status of task process
     */
    virtual ReturnType::State img(TifImageCommand_t tifCommand, std::string cmdInfo, std::ostream& os = std::cout) = 0;

    virtual ReturnType::State appimg(TifImageCommand_t tifCommand, std::string cmdInfo, std::ostream& os = std::cout) = 0;
    virtual ReturnType::State fpgaimg(TifImageCommand_t tifCommand, std::string cmdInfo, std::ostream& os = std::cout) = 0;
    virtual ReturnType::State osimg(TifImageCommand_t tifCommand, std::string cmdInfo, std::ostream& os = std::cout) = 0;
    virtual ReturnType::State tmpimg(TifImageCommand_t tifCommand, std::string cmdInfo, std::ostream& os = std::cout) = 0;

    /**
     * Sets the path to the image base directory where all images are stored in NVM.
     *
     * Note: This needs to be set prior to starting the object instance
     *       if the user wants to set the image base that is different from the default.
     *       eg. This would be done by a unit test case to set it's own base directory before running the tests.
     *
     * Defaults to '/nandflash' and is set during the constructor.
     *
     * \param basePath the full path to the image base directory in NVM
     *
     * \return true if path set successfully, false otherwise
     */
    virtual bool setPathToImageBase(char* path) = 0;

    /**
     * Sets the path to the destination directory for any downloaded image. This directory is a holding location where
     * the image is downloaded and verified before being stored to NVM.
     *
     * Note: This needs to be set prior to starting the object instance if the user wants to set the path to the
     *       destination directory for downloaded images that is different from the default.
     *       eg. This would be done by a unit test case to set it's own base directory before running the tests.
     *
     * Defaults to '/tmp/img' and is set during the constructor.
     *
     * \param destPath the full path to the destination directory for downloaded images
     *
     * \return true if path set successfully, false otherwise
     */
    virtual bool setDloadDestPath(char* destPath) = 0;

    /**
     * Sets the command prefix used when modifying contents of NVM flash memory. This prefix string is prepended
     * to the system commands when writing to flash memory, eg. when moving new images into flash or when
     * modifying existing images.
     *
     * Note: This needs to be set prior to starting the object instance if the user wants to set the prefix
     *       that is different from the default.
     *       eg. This would be done by a unit test case to set it's own base directory before running the tests.
     *
     * Defaults to 'flash-write ' and is set during the constructor.
     *
     * \param prefix the flash command prefix
     *
     * \return true if path set successfully, false otherwise
     */
    virtual bool setFlashCommandPrefix(char* prefix) = 0;

    /**
     * Returns the status of a command in progress.
     *
     * \return true if a command is currently in progress
     */
    virtual bool isCommandInProgress() = 0;

};

}  // end namespace Mplane

#endif /* _VRS_ITIFIMAGECOMMANDHANDLER_H_ */
