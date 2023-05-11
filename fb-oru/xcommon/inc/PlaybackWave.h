/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PlaybackWave.h
 * \brief     Manages playback waveform files
 *
 *
 * \details   Common class that encapsulates IQ data (at the GUI/SCPI end on the PC) and loads encapsulated data (in the embedded application)
 *
 */


#ifndef PLAYBACKWAVE_H_
#define PLAYBACKWAVE_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

// Uncomment to revert back to normal "ART" waveform playback
//#define USE_UNECRYPTED_PLAYBACK

namespace Mplane {

class IKey ;
class IFeature ;
class Lzo ;
class Crypt ;
class PlaybackWaveHeader ;
class EncapFile ;
class PlaybackFileInfo ;

class PlaybackWave {
public:
	PlaybackWave(std::shared_ptr<IKey> key) ;
	virtual ~PlaybackWave() ;

	/**
	 * Encapsulate the raw waveform IQ data in a header and block encode. Saves the data to outData vector
	 * @param basename	Base filename (without any mPath)
	 * @param inData
	 * @param outData
	 * @return false on error
	 */
	virtual bool encapsulate(const std::string& basename, const std::vector<uint8_t>& inData, std::vector<uint8_t>& outData) ;

	/**
	 * Encapsulate the raw waveform IQ data in a header and block encode. Writes the results to a file
	 * @param basename	Base filename (without any mPath)
	 * @param inData
	 * @param outFilename	File to write encapsulated data to
	 * @return false on error
	 */
	virtual bool encapsulate(const std::string& basename, const std::vector<uint8_t>& inData, const std::string& outFilename) ;

	/**
	 * Set the file mPath. Used for loading data and determining the playback file's characteristics
	 * @param filepath Full mPath to file
	 */
	virtual void setFilepath(const std::string& filepath) ;

	/**
	 * Sets up the object to read encapsulated data from the file mPath specified in setFilepath() method. Checks the header and sets up internal
	 * pointers ready to read the first block
	 * @param filename		Full mPath to input file
	 * @return false on error
	 */
	virtual bool loadEncapsulated() ;

	/**
	 * Sets up the object to read encapsulated data from the specified file mPath. Checks the header and sets up internal
	 * pointers ready to read the first block
	 * @param filename		Full mPath to input file
	 * @return false on error
	 */
	virtual bool loadEncapsulated(const std::string& filepath) ;

	/**
	 * Reads in the next block of data from the encapsulated file. Does any decryption/decompression necessary and saves the
	 * raw IQ data in the data vector. Sets the EOF flag at end of data
	 * @param data
	 * @return false on error
	 */
	virtual bool loadNextBlock(std::vector<uint8_t>& data, bool& eof) ;

	/**
	 * Checks the file against the supported features. If all file features are supported it will return true
	 * @param features
	 * @return true if all features used in the file are supported
	 */
	virtual bool checkFeatures(std::shared_ptr<IFeature> features) ;

	/**
	 * Get error string set if any method returns false
	 * @return error string containing all error messages
	 */
	virtual std::string getError() ;

	/**
	 * Process the file to determine the total number of bytes of data (i.e. the file size of the unencrypted/uncompressed
	 * file without any headers)
	 */
	virtual unsigned dataSize() ;

// Protected access to PlaybackFileInfo for testing
protected:
	std::string getFilepath() const ;
	std::string getFile() const ;
	std::string getPath() const ;
	std::string getSeparator() const ;
	std::string getAirStd() const ;
	std::string getBase() const ;
	std::string getBw() const ;
	std::string getCellId() const ;
	std::string getDuplex() const ;
	std::string getExtension() const ;
	std::string getRate() const ;
	std::string getTm() const ;

private:
	void setError(const std::string& error) ;
	bool encapsulateBlock(
		std::vector<uint8_t>::const_iterator dataStart,
		std::vector<uint8_t>::const_iterator dataEnd,
		std::vector<uint8_t>& outData) ;

private:
	std::shared_ptr<IKey> mKey ;
	std::shared_ptr<PlaybackWaveHeader> mHeader ;
	std::shared_ptr<Lzo> mLzo ;
	std::shared_ptr<Crypt> mCrypt ;
	std::string mError ;
	std::shared_ptr<EncapFile> mEncapFile ;

	std::shared_ptr<PlaybackFileInfo> mFileInfo ;

} ;

}

#endif /* PLAYBACKWAVE_H_ */
