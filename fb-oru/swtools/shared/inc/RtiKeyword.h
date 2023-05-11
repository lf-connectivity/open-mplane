/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiKeyword.h
 * \brief     Provides information about keywords
 *
 *
 * \details   Some call/return args are treated as special. This class provides information about them
 *
 */


#ifndef RTIKEYWORD_H_
#define RTIKEYWORD_H_

#include <string>
#include <vector>

namespace Mplane {

class RtiKeyword {
public:
	/**
	 * Special return args
	 */
	static const std::string StatusOK ;
	static const std::string StatusERROR ;

	static const std::string STATUS_VAR ;
	static const std::string INFO_VAR ;
	static const std::string MESSAGE_VAR ;

	/**
	 * Convenience function - returns the special variable type
	 * @param var
	 * @return type string
	 */
	static std::string getType(const std::string& var) ;

	/**
	 * Convenience function - returns the special variable default value
	 * @param var
	 * @return default string or empty if none
	 */
	static std::string getDefault(const std::string& var) ;

	/**
	 * Convenience function - whether the special variable is optional or not
	 * @param var
	 * @return true if optional
	 */
	static bool isOptional(const std::string& var) ;

	/**
	 * See if variable is reserved
	 * @param var
	 * @return true if reserved
	 */
	static bool isReserved(const std::string& var) ;

	/**
	 * Get the list of reserved variable names
	 * @return list of reserved variable names
	 */
	static std::vector<std::string> getReservedList() ;

	/**
	 * Convenience function. Adds the list of reserved keywords to an arguments string suitable for DataVariantList
	 * @param args	Current list of arguments as a string
	 * @return complete list of arguments in a string including the keywords
	 */
	static std::string addKeywordArgs(const std::string& returnArgs) ;


};

}

#endif /* RTIKEYWORD_H_ */
