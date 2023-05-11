/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PathUtils.cpp
 * \brief     Cross-platform file mPath related utilities
 *
 *
 * \details   File mPath related utilities
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// C lib
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _MSC_VER
#include <direct.h>
#include <windows.h>
#else
#include <dirent.h>
#include <sys/statvfs.h>
#include <unistd.h>
#endif

// C++
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "PathUtils.h"

using namespace Mplane;

//=============================================================================================================
// ALIAS
//=============================================================================================================
#ifdef _MSC_VER
#define RMDIR ::_rmdir
#define MKDIR(path, mode) ::_mkdir(path)
#define STAT ::_stat
#define STRDUP ::_strdup
using Stat = struct _stat;
#else
#define RMDIR ::rmdir
#define MKDIR ::mkdir
#define STAT ::stat
#define STRDUP ::strdup
using Stat = struct stat;
#endif

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================
static const std::string UNIX_SEPARATOR{"/"};
static const std::string WIN_SEPARATOR{"\\"};

#ifdef _MSC_VER
std::string PathUtils::SEPARATOR{WIN_SEPARATOR};
static const std::string OTHER_SEPARATOR{UNIX_SEPARATOR};
#else
std::string PathUtils::SEPARATOR{UNIX_SEPARATOR};
static const std::string OTHER_SEPARATOR{WIN_SEPARATOR};
#endif

//=============================================================================================================
// LOCAL
//=============================================================================================================
std::mutex PathUtils::mReaddirMutex;
static const char SEPARATOR_CHAR{PathUtils::SEPARATOR[0]};

namespace {

// Replace any characters in the string that are also in the string
// charsToReplace with the specified replacement character
inline std::string
replaceChars(
    const std::string& str,
    const std::string& charsToReplace,
    char replacement) {
  std::string result(str);
  std::size_t pos(result.find_first_of(charsToReplace));
  while (pos != std::string::npos) {
    result[pos] = replacement;
    pos = result.find_first_of(charsToReplace, pos + 1);
  }
  return result;
}

#ifdef _MSC_VER

#endif
}; // namespace

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int
PathUtils::mkdir(const std::string& _path, mode_t mode) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  int status = 0;
  if (!exists(path)) {
    /* Directory does not exist. EEXIST for race condition */
    if (MKDIR(path.c_str(), mode) != 0 && errno != EEXIST)
      status = -1;

  } else if (isDir(path)) {
    errno = ENOTDIR;
    status = -1;
  }

  return (status);
}

//-------------------------------------------------------------------------------------------------------------
/**
** mkpath - ensure all directories in mPath exist
** Algorithm takes the pessimistic view and works top-down to ensure
** each directory in mPath exists, rather than optimistically creating
** the last element and working backwards.
*/
int
PathUtils::mkpath(const std::string& _path, mode_t mode) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  int status(0);
  char* pp;
  char* sp;
  char* copypath = STRDUP(path.c_str());

  pp = copypath;
  while (status == 0 && (sp = strchr(pp, SEPARATOR_CHAR)) != 0) {
    if (sp != pp) {
      /* Neither root nor double slash in mPath */
      *sp = '\0';

      // make directory if it doesn't exist
      if (!isDir(copypath)) {
        status = PathUtils::mkdir(copypath, mode);
      }
      *sp = SEPARATOR_CHAR;
    }
    pp = sp + 1;
  }
  if (status == 0)
    status = PathUtils::mkdir(path, mode);

  free(copypath);

  return (status);
}

//-------------------------------------------------------------------------------------------------------------
int
PathUtils::rmdir(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  return RMDIR(path.c_str());
}

//-------------------------------------------------------------------------------------------------------------
int
PathUtils::remove(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  return ::remove(path.c_str());
}

//-------------------------------------------------------------------------------------------------------------
int
PathUtils::move(const std::string& _oldpath, const std::string& _newpath) {
#ifdef _MSC_VER
  const std::string oldpath(sanitisePath(_oldpath));
  const std::string newpath(sanitisePath(_newpath));
#else
  const std::string& oldpath(_oldpath);
  const std::string& newpath(_newpath);
#endif

  return ::rename(oldpath.c_str(), newpath.c_str());
}

//-------------------------------------------------------------------------------------------------------------
bool
PathUtils::isDir(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  // check that it's a dir
  Stat s;
  if (STAT(path.c_str(), &s) != 0)
    return false;

  if (s.st_mode & S_IFDIR)
    return true;
  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
PathUtils::isFile(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));

  // check that it's a file
  Stat s;
  if (STAT(path.c_str(), &s) != 0)
    return false;

  if (s.st_mode & S_IFREG)
    return true;

#else

  // check that it's a file
  Stat s;
  if (::lstat(_path.c_str(), &s) != 0)
    return false;

  if (S_ISREG(s.st_mode))
    return true;
#endif

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
PathUtils::isLink(const std::string& path) {
#ifdef _MSC_VER
#else
  // check that it's a file
  struct stat s;
  if (::lstat(path.c_str(), &s) != 0)
    return false;

  //    if( s.st_mode & S_IFLNK )
  if (S_ISLNK(s.st_mode))
    return true;
#endif

  return false;
}

//-------------------------------------------------------------------------------------------------------------
bool
PathUtils::readLink(const std::string& path, std::string& link) {
#ifdef _MSC_VER
  return false;
#else
  char buff[1024];
  ssize_t len = ::readlink(path.c_str(), buff, sizeof(buff) - 1);
  if (len == -1) {
    link = "";
    return false;
  }

  buff[len] = '\0';
  link = buff;
  return true;
#endif
}

//-------------------------------------------------------------------------------------------------------------
bool
PathUtils::createLink(const std::string& path, std::string link) {
#ifdef _MSC_VER
#else
  if (::symlink(link.c_str(), path.c_str()) == 0)
    return true;
#endif
  return false;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string>
PathUtils::dirContents(const std::string& _directory) {
#ifdef _MSC_VER
  const std::string directory(sanitisePath(_directory));
#else
  const std::string& directory(_directory);
#endif

  std::vector<std::string> contents;

  if (directory.empty() || !isDir(directory))
    return contents;

  // Ensure directory has '/' suffix
  std::string dirStr(directory);
  if (dirStr[dirStr.length() - 1] != SEPARATOR_CHAR)
    dirStr += SEPARATOR;

#ifdef _MSC_VER
  std::string glob(directory + "\\*");
  WIN32_FIND_DATA ffd;
  HANDLE hFind = FindFirstFile(glob.c_str(), &ffd);
  if (hFind == INVALID_HANDLE_VALUE)
    return contents;

  do {
    std::string name(ffd.cFileName);
    if ((name == ".") || (name == ".."))
      continue;

    std::string path(dirStr + name);

    // add to list
    contents.push_back(path);

  } while (FindNextFile(hFind, &ffd) != 0);

  FindClose(hFind);

#else
  std::unique_lock<std::mutex> lock(mReaddirMutex);

  // open directory
  DIR* dirp = opendir(directory.c_str());
  if (!dirp)
    return contents;

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
#endif

  return contents;
}

//-------------------------------------------------------------------------------------------------------------
bool
PathUtils::exists(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  Stat s;
  if (STAT(path.c_str(), &s) != 0)
    return false;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
PathUtils::basename(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  std::size_t sepPos(path.find_last_of(SEPARATOR));
  if (sepPos == std::string::npos)
    return path;

  return path.substr(sepPos + 1);
}

//-------------------------------------------------------------------------------------------------------------
std::string
PathUtils::dir(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  std::size_t sepPos(path.find_last_of(SEPARATOR));
  if (sepPos == std::string::npos)
    return "";

  return path.substr(0, sepPos + 1);
}

//-------------------------------------------------------------------------------------------------------------
std::string
PathUtils::join(const std::string& _dir, const std::string& _basename) {
#ifdef _MSC_VER
  const std::string dir(sanitisePath(_dir));
  const std::string basename(sanitisePath(_basename));
#else
  const std::string& dir(_dir);
  const std::string& basename(_basename);
#endif

  if (dir.empty())
    return basename;

  std::string path(dir);

  if (path.back() != SEPARATOR_CHAR)
    path.append(SEPARATOR);

  path.append(basename);
  return path;
}

//-------------------------------------------------------------------------------------------------------------
bool
PathUtils::fileCopy(const std::string& _src, const std::string& _dst) {
#ifdef _MSC_VER
  const std::string src(sanitisePath(_src));
  const std::string dst(sanitisePath(_dst));
#else
  const std::string& src(_src);
  const std::string& dst(_dst);
#endif

  if (!exists(src) || !isFile(src))
    return false;

  std::string dstFile(dst);
  if (isDir(dst)) {
    // Copying to a directory, so create the destination file name
    std::string name(basename(src));
    dstFile.append(SEPARATOR);
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
PathUtils::fileSize(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  Stat s;
  if (STAT(path.c_str(), &s) != 0)
    return 0;

  if (!(s.st_mode & S_IFREG))
    return 0;

  return static_cast<unsigned>(s.st_size);
}

//---------------------------------------------------------------------
// Use statvfs to return the free space for the disk that contains the
// specified mPath.
//
// NOTE: To work, the mPath (file or directory) *MUST* exist!
//
unsigned long long
PathUtils::freeSpace(const std::string& path) {
#ifdef _MSC_VER
  return 0ULL;
#else

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
#endif
}

//---------------------------------------------------------------------
bool
PathUtils::removeDirContents(const std::string& _path, bool recursive) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  // Check mPath exists and is a directory
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
PathUtils::extension(const std::string& _path) {
#ifdef _MSC_VER
  const std::string path(sanitisePath(_path));
#else
  const std::string& path(_path);
#endif

  std::string base(basename(path));

  // find the last '.'
  std::size_t pos(base.find_last_of('.'));
  if (pos == std::string::npos)
    return "";

  return base.substr(pos);
}

//---------------------------------------------------------------------
bool
PathUtils::filesDifferent(
    const std::string& _filename1,
    const std::string& _filename2,
    unsigned skipStart) {
#ifdef _MSC_VER
  const std::string filename1(sanitisePath(_filename1));
  const std::string filename2(sanitisePath(_filename2));
#else
  const std::string& filename1(_filename1);
  const std::string& filename2(_filename2);
#endif

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
PathUtils::sanitisePath(const std::string& path) {
  return replaceChars(path, OTHER_SEPARATOR, SEPARATOR_CHAR);
}
