/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Path.h
 * \brief     File path related utilities
 *
 *
 * \details   File path related utilities
 *
 */
#ifndef _PATH_DEFINED_
#define _PATH_DEFINED_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mutex>
#include <vector>

#include <errno.h>
#include <stdio.h>
#include <string>
#include <sys/stat.h>

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
class Path {
 public:
  static std::string SEPERATOR;

  /**
   * Create a directory path including intermediate directories
   * @param path
   * @param mode
   * @return status 0 if ok
   */
  static int mkpath(const std::string& path, mode_t mode = S_IRWXU | S_IRWXG);

  /**
   * Make a single directory. Parent directories must be available
   * @param path
   * @param mode
   * @return status 0 if ok
   */
  static int mkdir(const std::string& path, mode_t mode = S_IRWXU | S_IRWXG);

  /**
   * Remove a directory
   * @param path
   * @return status 0 if ok
   */
  static int rmdir(const std::string& path);

  /**
   * Remove a file
   * @param path
   * @return status 0 if ok
   */
  static int remove(const std::string& path);

  /**
   * Delete all of the files in a directory. Optionally recursively delete any
   * sub-directories
   * @param path
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
   * Is path a directory
   * @param path
   * @return true if directory
   */
  static bool isDir(const std::string& path);

  /**
   * Is path a file
   * @param path
   * @return true if file
   */
  static bool isFile(const std::string& path);

  /**
   * Is path a link
   * @param path
   * @return true if link
   */
  static bool isLink(const std::string& path);

  /**
   * Read the link specified by path. If able to, sets 'link' to the path the
   * link points to
   * @param path
   * @param link set to link path
   * @return true if able to read link
   */
  static bool readLink(const std::string& path, std::string& link);

  /**
   * Create a link from 'link' to 'path'. 'path' is the full path to the link,
   * 'link' is the contents of the link (i.e. what the link links to)
   *
   * @param path the path to the symbolic link to be created
   * @param link what the link points to
   * @return true if able to create link
   */
  static bool createLink(const std::string& path, std::string link);

  /**
   * Get the directory contents
   * @param path
   * @return vector of paths
   */
  static std::vector<std::string> dirContents(
      const std::string& path, bool chronologial = false);

  /**
   * Does path exist
   * @param path
   * @return true if exists
   */
  static bool exists(const std::string& path);

  /**
   * Split path into directory and basename (basename includes extension)
   * @param path
   * @return basename
   */
  static std::string basename(const std::string& path);

  /**
   * Split path into directory and basename
   * @param path
   * @return directory
   */
  static std::string dir(const std::string& path);

  /**
   * Join a directory and filename back into a full path
   * @param dir
   * @param filename
   * @return path
   */
  static std::string join(const std::string& dir, const std::string& filename);

  /**
   * Extract last extension from filename. Examples:
   *
   * path                extension
   * "file.txt"        ".txt"
   * "file.tgz.md5"    ".md5"
   * "file"            ""
   *
   * @param path
   * @return extension
   */
  static std::string extension(const std::string& path);

  /**
   * Get basename of path then remove filename extension to leave just the name
   *
   * @param path
   * @return name
   */
  static std::string name(const std::string& path);

  /**
   * Converts path into an absolute path (if it isn't already). Uses rootdir as
   * the base if path is relative. If rootdir is '.' or empty then uses the
   * current working directory
   */
  static std::string absolute(
      const std::string& path, const std::string& rootdir = ".");

  /**
   * Clean up path. Removes duplicated separators (e.g. //)
   */
  static std::string clean(const std::string& path);

  /**
   * Copy a file from src to dest
   * @param src    File path
   * @param dest    File path or directory path. If directory, then copies
   * file in with same name
   * @return true if copied ok
   */
  static bool fileCopy(const std::string& src, const std::string& dest);

  /**
   * Returns the size of the file
   * @param path    Path to file
   */
  static unsigned fileSize(const std::string& path);

  /**
   * Gets the amount of free space left on the file system that contains this
   * directory path (or file path)
   * @param path
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

 private:
  static std::mutex mReaddirMutex;
};

} // namespace Mplane
#endif // _PATH_DEFINED_
