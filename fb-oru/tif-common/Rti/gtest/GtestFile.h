/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GtestFile.h
 * \brief     Various file checks for Google Test tests
 *
 *
 * \details   File checks and manipulation for Google Test testbenches. Expected to derive a test fixture from this class
 * to add it's methods (or just access the static methods direct)
 *
 */


#ifndef GTESTFILE_H_
#define GTESTFILE_H_

class GtestFile
{
public:
	/**
	 * Delete the file
	 * @param filename	File path
	 */
    static void deleteFile(const std::string& filename) ;

    /**
     * Check that the file exists. Uses EXPECT_* to test file file existence.
     * @param filename	File path
     * @return true if file exists.
     */
    static bool checkFileExists(const std::string& filename) ;

    /**
     * Read a file, line by line, doing a POSIX regular expression search to see if the expected regexp is found in any
     * lines. Uses ADD_FAILURE() and EXPECT_TRUE() to test for contents matching.
     * @param filename	File path
     * @param expected	POSIX regular expression
     * @return true if regexp is found in file
     */
    static bool checkFileContents(const std::string& filename, const std::string& expected) ;
};



#endif /* GTESTFILE_H_ */
