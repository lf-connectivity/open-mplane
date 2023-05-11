/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaMsgTokens.h
 * \brief     Interface to tokens that encode IFpgaMsg commands/variables
 *
 *
 * \details
 *
 */


#ifndef IFPGAMSGTOKENS_H_
#define IFPGAMSGTOKENS_H_

#include <vector>
#include <memory>
#include <string>

#include "DataVariant.h"

namespace Mplane {

class IFpgaMsgTokens {
public:
	IFpgaMsgTokens() {}
	virtual ~IFpgaMsgTokens() {}

	/**
	 * Get the version for the PIM interface
	 * @return version for PIM API
	 */
	virtual unsigned getApiVersion() const =0 ;

	/**
	 * Convert command token string into a value
	 * @param tokenStr
	 * @return token value, or <0 if not found
	 */
	virtual int getCmdToken(const std::string& tokenStr) const =0 ;

	/**
	 * Is this a valid command token string
	 * @param tokenStr
	 * @return true if valid
	 */
	virtual bool isCmdToken(const std::string& tokenStr) const =0 ;

	/**
	 * Is this a valid command token
	 * @param token
	 * @return true if valid
	 */
	virtual bool isCmdToken(unsigned token) const =0 ;

	/**
	 * Convert command token value into a string
	 * @param token
	 * @return token string, or empty string if not found
	 */
	virtual std::string getCmdTokenStr(unsigned token) const =0 ;

	/**
	 * Get the complete list of command token strings
	 */
	virtual std::vector<std::string> getCmds() const =0 ;

	/**
	 * Convert state token string into a value
	 * @param tokenStr
	 * @return token value, or <0 if not found
	 */
	virtual int getStateToken(const std::string& tokenStr) const =0 ;

	/**
	 * Is this a valid state token string
	 * @param tokenStr
	 * @return true if valid
	 */
	virtual bool isStateToken(const std::string& tokenStr) const =0 ;

	/**
	 * Is this a valid state token
	 * @param token
	 * @return true if valid
	 */
	virtual bool isStateToken(unsigned token) const =0 ;

	/**
	 * Get the data type of this state variable
	 * @param tokenStr	Variable name
	 * @return data type
	 */
	virtual std::string getStateTypeStr(const std::string& tokenStr) const =0 ;

	/**
	 * Get the data type of this state variable
	 * @param token	Variable id
	 * @return data type
	 */
	virtual std::string getStateTypeStr(unsigned token) const =0 ;

	/**
	 * Get the data type of this state variable
	 * @param tokenStr	Variable name
	 * @return data type
	 */
	virtual DataVariantType::Type getStateType(const std::string& tokenStr) const =0 ;

	/**
	 * Get the data type of this state variable
	 * @param token	Variable id
	 * @return data type
	 */
	virtual DataVariantType::Type getStateType(unsigned token) const =0 ;

	/**
	 * Get the default value of this state variable
	 * @param tokenStr	Variable name
	 * @return default value
	 */
	virtual std::string getStateDefault(const std::string& tokenStr) const =0 ;

	/**
	 * Get the default value of this state variable
	 * @param token	Variable id
	 * @return default value
	 */
	virtual std::string getStateDefault(unsigned token) const =0 ;


	/**
	 * Convert state token value into a string
	 * @param token
	 * @return token string, or empty string if not found
	 */
	virtual std::string getStateTokenStr(unsigned token) const =0 ;

	/**
	 * Get the complete list of state token strings
	 */
	virtual std::vector<std::string> getStates() const =0 ;


	/**
	 * Convert token string into a value
	 * @param tokenStr
	 * @return token value, or <0 if not found
	 */
	virtual int getToken(const std::string& tokenStr) const =0 ;

	/**
	 * Is this a valid token string into a value
	 * @param tokenStr
	 * @return true if valid
	 */
	virtual bool isToken(const std::string& tokenStr) const =0 ;

	/**
	 * Is this a valid token string into a value
	 * @param tokenStr
	 * @return true if valid
	 */
	virtual bool isToken(unsigned token) const =0 ;

	/**
	 * Convert token value into a string
	 * @param token
	 * @return token string, or empty string if not found
	 */
	virtual std::string getTokenStr(unsigned token) const =0 ;

} ;

}

#endif /* IFPGAMSGTOKENS_H_ */
