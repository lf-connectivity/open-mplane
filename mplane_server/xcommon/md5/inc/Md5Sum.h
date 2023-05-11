/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Md5Sum.h
 * \brief     Object for creating md5 sum of a file
 *
 *
 * \details   Wrapper interface for the md5 C functions
 *
 */


#ifndef MD5_INC_MD5SUM_H_
#define MD5_INC_MD5SUM_H_

#include <string>

namespace Mplane {

/*!
 * \class  Md5Sum
 * \brief
 * \details
 *
 */
class Md5Sum {
public:
 Md5Sum();
 Md5Sum(const std::string& filename);
 virtual ~Md5Sum();

 /**
  * Set the filename to use
  */
 void setFilename(const std::string& filename);

 /**
  * Get the md5 sum of the file; returns empty string on error
  */
 std::string sum();

private:
 std::string mFilename;
 std::string mSum;
} ;

}

#endif /* MD5_INC_MD5SUM_H_ */
