/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Path.cpp
 * \brief     File path related utilities
 *
 *
 * \details   File path related utilities
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// C lib
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <unistd.h>

// C++
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Path.h"
#include "stringfunc.hpp"

using namespace Mplane;
using namespace std;

//=============================================================================================================
// TYPES
//=============================================================================================================

using Stat = struct stat;

//=============================================================================================================
// PRIVATE STATIC
//=============================================================================================================
std::mutex Path::mReaddirMutex;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================
std::string Path::SEPERATOR{"/"};
static const char SEPERATOR_CHAR{Path::SEPERATOR[0]};

//-------------------------------------------------------------------------------------------------------------
int
Path::mkdir(const std::string& path, mode_t mode) {
  Stat st;
  int status = 0;

  if (::stat(path.c_str(), &st) != 0) {
    /* Directory does not exist. EEXIST for race condition */
    if (::mkdir(path.c_str(), mode) != 0 && errno != EEXIST)
      status = -1;

  } else if (!S_ISDIR(st.st_mode)) {
    errno = ENOTDIR;
    status = -1;
  }

  return (status);
}

//-------------------------------------------------------------------------------------------------------------
/**
** mkpath - ensure all directories in path exist
** Algorithm takes the pessimistic view and works top-down to ensure
** each directory in path exists, rather than optimistically creating
** the last element and working backwards.
*/
int
Path::mkpath(const std::string& path, mode_t mode) {
  char* pp;
  char* sp;
  int status;
  char* copypath = strdup(path.c_str());

  status = 0;
  pp = copypath;
  while (status == 0 && (sp = strchr(pp, SEPERATOR_CHAR)) != 0) {
    if (sp != pp) {
      /* Neither root nor double slash in path */
      *sp = '\0';
      status = Path::mkdir(copypath, mode);
      *sp = SEPERATOR_CHAR;
    }
    pp = sp + 1;
  }
  if (status == 0)
    status = Path::mkdir(path, mode);

  free(copypath);
  return (status);
}

//-------------------------------------------------------------------------------------------------------------
int
Path::rmdir(const std::string& path) {
  return ::rmdir(path.c_str());
}

//-------------------------------------------------------------------------------------------------------------
int
Path::remove(const std::string& path) {
  return ::remove(path.c_str());
}

//-------------------------------------------------------------------------------------------------------------
int
Path::move(const std::string& oldpath, const std::string& newpath) {
  return ::rename(oldpath.c_str(), newpath.c_str());
}

//-------------------------------------------------------------------------------------------------------------
bool
Path::isDir(const std::string& path) {
  // check that it's a dir
  struct stat s;
  if (::lstat(path.c_str(), &s) != 0)
    return false;

  //    if( s.st_mode & S_IFDIR )
  if (S_ISDIR(s.st_mode))
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
Path::isFile(const std::string& path) {
  // check that it's a file
  struct stat s;
  if (::lstat(path.c_str(), &s) != 0)
    return false;

  //    if( s.st_mode & S_IFREG )
  if (S_ISREG(s.st_mode))
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
Path::isLink(const std::string& path) {
  // check that it's a file
  struct stat s;
  if (::lstat(path.c_str(), &s) != 0)
    return false;

  //    if( s.st_mode & S_IFLNK )
  if (S_ISLNK(s.st_mode))
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
Path::readLink(const std::string& path, std::string& link) {
  char buff[1024];
  ssize_t len = ::readlink(path.c_str(), buff, sizeof(buff) - 1);
  if (len == -1) {
    link = "";
    return false;
  }

  buff[len] = '\0';
  link = buff;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
Path::createLink(const std::string& link, std::string src) {
  int rc = ::symlink(src.c_str(), link.c_str());
  if (rc == 0)
    return true;

  return false;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
Path::dirContents(const std::string& directory, bool chronologial) {
  std::unique_lock<std::mutex> lock(mReaddirMutex);

  std::vector<std::string> contents;
  if (directory.empty())
    return contents;

  // open directory
  DIR* dirp = opendir(directory.c_str());
  if (!dirp)
    return contents;

  // Ensure directory has '/' suffix
  std::string dirStr(directory);
  if (dirStr[dirStr.length() - 1] != SEPERATOR_CHAR)
    dirStr += SEPERATOR;

  // Allocate a suitably sized buffer
  long name_max = pathconf(dirStr.c_str(), _PC_NAME_MAX);
  if (name_max == -1) /* Limit not defined, or error */
    name_max = 255; /* Take a guess */
  // can't use the gcc recommended method of calculating the size of the buffer
  // to allocate (gcc4.8.1 g++ doesn't provide offsetof) but allocating the
  // whole size of the structure + a buffer for the maximum name size should
  // provide ample space (though there's some controversy:
  // http://womble.decadent.org.uk/readdir_r-advisory.html who would have
  // thought reading a directory would be such a pain!)
  //
  //    size_t len = offsetof(struct dirent, d_name) + name_max + 1;
  size_t len = sizeof(struct dirent) + name_max + 1;
  struct dirent* dbuffp = (struct dirent*)malloc(len);

  // read the directory
  while (true) {
    struct dirent* dp;
    /**
     * The latest standards deprecate the use of readdir_r because it doesn't
     * allow the specification of the length of the buffer. It is preferred to
     * use readdir and add your own locks if necessary.
     */
    dp = readdir(dirp);
    if (dp == NULL)
      break;

    std::string name(dp->d_name);
    if ((name == ".") || (name == ".."))
      continue;

    std::string path(dirStr + name);

    // add to list
    contents.push_back(path);
  }

  // close
  closedir(dirp);

  free(dbuffp);

  // Sort the files chronologically if flag is set
  if (chronologial) {
    std::sort(
        contents.begin(),
        contents.end(),
        [](const std::string& lhs, const std::string& rhs) {
          struct stat attribLhs;
          struct stat attribRhs; // File attribute structs
          stat(lhs.c_str(), &attribLhs);
          stat(rhs.c_str(), &attribRhs); // Get file stats
          return attribLhs.st_mtime <
                 attribRhs.st_mtime; // Compare last modification dates
        });
  }

  return contents;
}

//-------------------------------------------------------------------------------------------------------------
bool
Path::exists(const std::string& path) {
  struct stat s;
  if (::lstat(path.c_str(), &s) != 0)
    return false;

  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
Path::basename(const std::string& path) {
  std::size_t sepPos(path.find_last_of(SEPERATOR));
  if (sepPos == std::string::npos)
    return path;

  return path.substr(sepPos + 1);
}

//-------------------------------------------------------------------------------------------------------------
std::string
Path::dir(const std::string& path) {
  std::size_t sepPos(path.find_last_of(SEPERATOR));
  if (sepPos == std::string::npos)
    return "";

  return path.substr(0, sepPos + 1);
}

//-------------------------------------------------------------------------------------------------------------
std::string
Path::join(const std::string& dir, const std::string& basename) {
  if (dir.empty())
    return basename;

  std::string path(dir);

  if (path.back() != SEPERATOR_CHAR)
    path.append(SEPERATOR);

  path.append(basename);
  return path;
}

//-------------------------------------------------------------------------------------------------------------
bool
Path::fileCopy(const std::string& src, const std::string& dst) {
  if (!exists(src) || !isFile(src))
    return false;

  std::string dstFile(dst);
  if (isDir(dst)) {
    // Copying to a directory, so create the destination file name
    std::string name(basename(src));
    dstFile.append(SEPERATOR);
    dstFile.append(name);
  }

  std::ifstream source(src.c_str(), std::ios::binary);
  if (!source.is_open())
    return false;
  std::ofstream dest(dstFile.c_str(), std::ios::binary);
  if (!dest.is_open())
    return false;

  dest << source.rdbuf();
  source.close();
  dest.close();
  return true;
}

//-------------------------------------------------------------------------------------------------------------
unsigned
Path::fileSize(const std::string& path) {
  // check that it's a file
  struct stat s;
  if (::lstat(path.c_str(), &s) != 0)
    return 0;

  if (!(s.st_mode & S_IFREG))
    return 0;

  return static_cast<unsigned>(s.st_size);
}

//---------------------------------------------------------------------
// Use statvfs to return the free space for the disk that contains the
// specified path.
//
// NOTE: To work, the path (file or directory) *MUST* exist!
//
unsigned long long
Path::freeSpace(const std::string& path) {
  unsigned long long result = 0;
  if (!exists(path))
    return result;

  // sync the file system first - if this is a UBIFS filesystem then running
  // sync will give a (slightly) more accurate result
  ::sync();

  // get space
  struct statvfs sfs;
  if (::statvfs(path.c_str(), &sfs) != -1) {
    result = (unsigned long long)sfs.f_bsize * sfs.f_bavail;
  }
  return result;
}

//---------------------------------------------------------------------
bool
Path::removeDirContents(const std::string& path, bool recursive) {
  // Check path exists and is a directory
  if (!exists(path) || !isDir(path))
    return false;

  // Get contents
  std::vector<std::string> contents(dirContents(path));

  // Delete files
  for (auto file : contents) {
    if (!isDir(file)) {
      if (remove(file) != 0)
        return false;
    }
  }

  if (!recursive)
    return true;

  // Empty directories
  for (auto dir : contents) {
    if (isDir(dir)) {
      if (!removeDirContents(dir, true))
        return false;

      if (rmdir(dir) != 0)
        return false;
    }
  }

  return true;
}

//---------------------------------------------------------------------
std::string
Path::extension(const std::string& path) {
  std::string base(basename(path));

  // find the last '.'
  std::size_t pos(base.find_last_of('.'));
  if (pos == std::string::npos)
    return "";

  return base.substr(pos);
}

//---------------------------------------------------------------------
std::string
Path::name(const std::string& path) {
  std::string base(basename(path));
  std::string ext(extension(path));
  return base.substr(0, base.size() - ext.size());
}

//---------------------------------------------------------------------
std::string
Path::absolute(const std::string& path, const std::string& rootdir) {
  std::string root(rootdir);
  if (root.empty() || (root[0] != '/')) {
    char buff[PATH_MAX];
    std::string wd(getcwd(buff, sizeof(buff)));

    root = wd;
  }

  // remove any trailing '/'
  if (root[root.size() - 1] == '/')
    root.resize(root.size() - 1);

  if (path.empty())
    return root;

  std::string abspath(path);
  if (path[0] != '/')
    abspath = root + '/' + path;

  return clean(abspath);
}

//---------------------------------------------------------------------
bool
Path::filesDifferent(
    const std::string& filename1,
    const std::string& filename2,
    unsigned skipStart) {

  IfStream infile1(filename1);
  if (!infile1.is_open())
    return true;

  IfStream infile2(filename2);
  if (!infile2.is_open())
    return true;

  std::string linebuff2;
  std::string linebuff1;
  unsigned lineNum = 0;
  while (infile1.good() && infile2.good()) {
    // get the line text string
    std::getline(infile1(), linebuff1);
    std::getline(infile2(), linebuff2);
    ++lineNum;

    if (lineNum <= skipStart)
      continue;

    if (linebuff1 != linebuff2)
      return true;
  }

  // see if one finished before the other
  if (infile1.good() || infile2.good())
    return true;

  // files are the same
  return false;
}

//---------------------------------------------------------------------
std::string
Mplane::Path::clean(const std::string& path) {
  std::string cleaned(replaceStrs(path, "//", "/"));

  return cleaned;
}
