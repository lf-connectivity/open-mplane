/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PathUtils.h
 * \brief     Cross-platform file mPath related utilities
 *
 *
 * \details   File mPath related utilities
 *
 */
#ifndef _PATHUTILS_DEFINED_
#define _PATHUTILS_DEFINED_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

#ifdef _MSC_VER
using mode_t = int;

static const mode_t S_ISUID = 0x08000000; ///< does nothing
static const mode_t S_ISGID = 0x04000000; ///< does nothing
static const mode_t S_ISVTX = 0x02000000; ///< does nothing
static const mode_t S_IRUSR = mode_t(_S_IREAD); ///< read by user
static const mode_t S_IWUSR = mode_t(_S_IWRITE); ///< write by user
static const mode_t S_IXUSR = 0x00400000; ///< does nothing
static const mode_t S_IRGRP = mode_t(_S_IREAD); ///< read by *USER*
static const mode_t S_IWGRP = mode_t(_S_IWRITE); ///< write by *USER*
static const mode_t S_IXGRP = 0x00080000; ///< does nothing
static const mode_t S_IROTH = mode_t(_S_IREAD); ///< read by *USER*
static const mode_t S_IWOTH = mode_t(_S_IWRITE); ///< write by *USER*
static const mode_t S_IXOTH = 0x00010000; ///< does nothing
static const mode_t S_IRWXU =
    mode_t(_S_IREAD | _S_IWRITE); ///< read/write/execute by user
static const mode_t S_IRWXG =
    mode_t(_S_IREAD | _S_IWRITE); ///< read/write/execute by *USER*

#endif

namespace Mplane {

/**
 * Class wrapper for std::ifstream. Uses RAII to auto-close when object goes out
 * of scope
 */
class IfStream {
 public:
  /**
   * Construct by opening file
   * @param filename
   */
  explicit IfStream(const std::string& filename) {
    mFile.open(filename.c_str());
  }

  /**
   * Destroy by closing file if open
   */
  ~IfStream() {
    if (mFile.is_open())
      mFile.close();
  }

  /**
   * Forward to ifstream
   * @return ifstream.good()
   */
  bool
  good() {
    return mFile.good();
  }

  /**
   * Forward to ifstream
   * @return ifstream.is_open()
   */
  bool
  is_open() {
    return mFile.is_open();
  }

  /**
   * Access the std::ifstream
   */
  std::ifstream&
  operator()() {
    return mFile;
  }

 private:
  std::ifstream mFile;
};

/**
 * Class containing static utility methods for file-related tasks
 */
class PathUtils {
 public:
  static std::string SEPARATOR;

  /**
   * Create a directory mPath including intermediate directories
   * @param mPath
   * @param mode
   * @return status 0 if ok
   */
  static int mkpath(const std::string& path, mode_t mode = S_IRWXU | S_IRWXG);

  /**
   * Make a single directory. Parent directories must be available
   * @param mPath
   * @param mode
   * @return status 0 if ok
   */
  static int mkdir(const std::string& path, mode_t mode = S_IRWXU | S_IRWXG);

  /**
   * Remove a directory
   * @param mPath
   * @return status 0 if ok
   */
  static int rmdir(const std::string& path);

  /**
   * Remove a file
   * @param mPath
   * @return status 0 if ok
   */
  static int remove(const std::string& path);

  /**
   * Delete all of the files in a directory. Optionally recursively delete any
   * sub-directories
   * @param mPath
   * @return true if ok
   */
  static bool removeDirContents(
      const std::string& path, bool recursive = false);

  /**
   * move a file
   * @param oldpath    Original filename
   * @param newpath    New filename
   * @return status 0 if ok
   */
  static int move(const std::string& oldpath, const std::string& newpath);

  /**
   * Is mPath a directory
   * @param mPath
   * @return true if directory
   */
  static bool isDir(const std::string& path);

  /**
   * Is mPath a file
   * @param mPath
   * @return true if file
   */
  static bool isFile(const std::string& path);

  /**
   * Is mPath a link
   * @param mPath
   * @return true if link
   */
  static bool isLink(const std::string& path);

  /**
   * Read the link specified by mPath. If able to, sets 'link' to the mPath the
   * link points to
   * @param mPath
   * @param link set to link mPath
   * @return true if able to read link
   */
  static bool readLink(const std::string& path, std::string& link);

  /**
   * Create a link from 'link' to 'mPath'. 'mPath' is the full mPath to the
   * link, 'link' is the contents of the link (i.e. what the link links to)
   *
   * @param mPath the mPath to the symbolic link to be created
   * @param link what the link points to
   * @return true if able to create link
   */
  static bool createLink(const std::string& path, std::string link);

  /**
   * Get the directory contents
   * @param mPath
   * @return vector of paths
   */
  static std::vector<std::string> dirContents(const std::string& path);

  /**
   * Does mPath exist
   * @param mPath
   * @return true if exists
   */
  static bool exists(const std::string& path);

  /**
   * Split mPath into directory and basename
   * @param mPath
   * @return basename
   */
  static std::string basename(const std::string& path);

  /**
   * Split mPath into directory and basename
   * @param mPath
   * @return directory
   */
  static std::string dir(const std::string& path);

  /**
   * Join a directory and filename back into a full mPath
   * @param dir
   * @param filename
   * @return mPath
   */
  static std::string join(const std::string& dir, const std::string& filename);

  /**
   * Extract last extension from filename. Examples:
   *
   * mPath                extension
   * "file.txt"        ".txt"
   * "file.tgz.md5"    ".md5"
   * "file"            ""
   *
   * @param mPath
   * @return extension
   */
  static std::string extension(const std::string& path);

  /**
   * Copy a file from src to dest
   * @param src    File mPath
   * @param dest    File mPath or directory mPath. If directory, then copies
   * file in with same name
   * @return true if copied ok
   */
  static bool fileCopy(const std::string& src, const std::string& dest);

  /**
   * Returns the size of the file
   * @param mPath    Path to file
   */
  static unsigned fileSize(const std::string& path);

  /**
   * Gets the amount of free space left on the file system that contains this
   * directory mPath (or file mPath)
   * @param mPath
   * @return amount of space left
   */
  static unsigned long long freeSpace(const std::string& path);

  /**
   * Compare text files, optionally skipping the first 'skipStart' lines before
   * doing the comparison
   * @param filename1
   * @param filename2
   * @param skipStart    Skip this number of lines before comparing. Useful for
   * ignoring changed headers
   * @return true if files are different; false if same
   */
  static bool filesDifferent(
      const std::string& filename1,
      const std::string& filename2,
      unsigned skipStart = 0);

  /**

  */
  static std::string sanitisePath(const std::string& path);

 private:
  static std::mutex mReaddirMutex;
};

} // namespace Mplane
#endif // _PATHUTILS_DEFINED_
