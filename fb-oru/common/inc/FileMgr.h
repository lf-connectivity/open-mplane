/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileMgr.h
 * \brief     File manager
 *
 *
 * \details   Manages files in a specified directory. Allows for adding more files (downloaded from a url) or deleting
 * 				existing files.
 *
 */


#ifndef FILEMGR_H_
#define FILEMGR_H_

#include "IFileMgr.h"

namespace Mplane {

class FileMgr : public virtual IFileMgr {
public:
	FileMgr() ;
	explicit FileMgr(const std::string& dir) ;
	virtual ~FileMgr() ;

	/**
	 * Set the directory path to where these files are stored locally. Upload/download will use this
	 * directory
	 * @param dir
	 * @param mkdir	Optional parameter: if set then automatically creates the path to this directory if it doesn't exist
	 * @return true if able to switch to this directory (i.e. it exists etc)
	 */
	virtual bool setDir(const std::string& dir, bool mkdir = false) override ;

	/**
	 * Set the temporary directory path to where these files are temporarily downloaded to. Using this method
	 * overrides the default location
	 * @param dir
	 * @param mkdir	Optional parameter: if set then automatically creates the path to this directory if it doesn't exist
	 * @param clear	Optional parameter: if set then clears out any existing files/directories found in the specified directory
	 * @return true if able to switch to this directory (i.e. it exists etc)
	 */
	virtual bool setTempDir(const std::string& dir, bool mkdir = true, bool clear = true) override ;


	/**
	 * Get the current directory setting
	 */
	virtual std::string getDir() const override ;

	/**
	 * Get the current temporary directory setting
	 */
	virtual std::string getTempDir() const override ;

	/**
	 * Returns any error string created by running these methods. Clears out the stored error
	 * @return error string or empty
	 */
	virtual std::string getError() override ;


	/**
	 * List the files stored in the directory set via the 'setDir()' method. If an extension has been set via
	 * setExtension then this will show only those files that have the extension
	 * @return list of files
	 */
	virtual std::vector<std::string> listFiles() override ;


	/**
	 * Delete based on filename but also accepts * wildcard. If just '*' is specified then deletes all files, otherwise
	 * expects the start of a filename ending in '*' and will then delete all files starting with the specified string
	 * @param filename
	 * @return true if deleted ok
	 */
	virtual bool delfile(const std::string& filename) override ;

	/**
	 * Delete the specified file
	 * @param filename
	 * @return true if file deleted
	 */
	virtual bool del(const std::string& filename) override ;

	/**
	 * Delete the specified file. Uses the index from the list of files (as returned by listFiles() method)
	 * @param fileIndex 0-based file index
	 * @return true if file deleted
	 */
	virtual bool del(unsigned fileIndex) override ;

	/**
	 * Download the file from the specified url
	 * @param url Where to get file from
	 * @param filename Local filename to store file as
	 * @param status Optional status callback function
	 * @return true if file downloaded
	 */
	virtual bool download(const std::string& url, const std::string& filename) override ;

	virtual bool download(const std::string& url, const std::string& filename,
			std::shared_ptr<IFileStatus> status) override ;

	/**
	 * Start transferring data via a TCP PORT IN port onto the unit to be saved in the current directory using the specified filename
	 * If everything is set up ok, returns a pointer to a newly created IFileMgrWriter object which will manage the file writes
	 * @return pointer to a newly created IFileMgrWrite object; null pointer on error
	 */
	virtual std::shared_ptr<IFileMgrWriter> portTransferStart(const std::string& filename, unsigned fileSize) override ;

	/**
	 * Start transferring data via a TCP PORT IN port onto the unit to be saved in the current directory using the specified filename
	 * If everything is set up ok, returns a pointer to a newly created IFileMgrWriter object which will manage the file writes
	 * @return pointer to a newly created IFileMgrWrite object; null pointer on error
	 */
	virtual std::shared_ptr<IFileMgrWriter> portTransferStart(const std::string& filename,
			unsigned fileSize, std::shared_ptr<IFileStatus> status) override ;

	/**
	 * Stop the port transfer. If transfer completed with no errors, runs the final tidy up and any file moving required
	 * @return true if everything completed without errors
	 */
	virtual bool portTransferEnd(bool ok) override ;

	/**
	 * Get the amount (approximately) of free space available in the directory specified by setDir() method
	 */
	virtual unsigned long long dirFreeSpace() const override ;

protected:
	bool downloadStart(const std::string& filename) ;
	bool downloadComplete(bool error, bool timedOut) ;

	/**
	 * Convert 0-based index into a filename
	 * @param index
	 * @return filename or empty string if not found
	 */
	std::string indexToFilename(unsigned index) ;

	/**
	 * Add this string the the error string
	 * @param error
	 */
	void setError(const std::string& error) ;

	/**
	 * Is there enough free space in the specified directory to store a file of the specified size?
	 * @param dir
	 * @param requiredSize
	 * @return true if enough space
	 */
	bool isFreeFileSpace(const std::string& dir, unsigned requiredSize) ;


private:
	std::string mDir ;
	std::string mTempDir ;
	std::string mError ;

	// Download settings
	std::string mFilename ;
	std::string mUrl ;
	std::string mTempFilepath ;
	std::string mDestFilepath ;
} ;

}

#endif /* FILEMGR_H_ */
