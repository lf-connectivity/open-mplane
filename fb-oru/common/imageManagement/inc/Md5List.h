/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Md5List.h
 * \brief     Contains information stored in an .md5list file
 *
 *
 * \details   Represents the information contained in an md5list file such that 2 files can be compared for equivalence
 *
 */


#ifndef MD5LIST_H_
#define MD5LIST_H_

#include <string>
#include <map>

namespace Mplane {

class Md5List {
public:
	/**
	 * Construct the object from a file
	 */
	explicit Md5List(const std::string& filePath) ;


	virtual ~Md5List() ;

	/**
	 * Compare 2 md5list files
	 * @param rhs The other file to compare
	 * @return true if equal
	 */
	virtual bool operator==(const Md5List & rhs) const ;
	virtual bool operator!=(const Md5List & rhs) const ;

private:
	// Store the file contents
	std::map<std::string, std::string>	mData ;
} ;

}

#endif /* MD5LIST_H_ */
