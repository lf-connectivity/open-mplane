/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaMsgTokens.h
 * \brief     Base class that implements most of IFpgaMsgTokens functionality
 *
 *
 * \details
 *
 */


#ifndef FPGAMSGTOKENS_H_
#define FPGAMSGTOKENS_H_

#include <utility>
#include <map>
#include <set>

#include "IFpgaMsgTokens.h"

namespace Mplane {

class FpgaMsgTokens : public IFpgaMsgTokens
{
public:

	struct StateType {
		std::string typeStr ;
		DataVariantType::Type type ;
		std::string defaultVal ;
	};


	FpgaMsgTokens(unsigned apiVersion,
		const std::map<std::string, unsigned>& commandMap,
		const std::map<std::string, unsigned>& stateMap,
		const std::map<std::string, unsigned>& tokenMap,
		const std::map<std::string, StateType>& stateTypes
	) ;
	virtual ~FpgaMsgTokens() ;

	/**
	 * Get the version for the PIM interface
	 * @return version for PIM API
	 */
	virtual unsigned getApiVersion() const override ;

	/**
	 * Convert command token string into a value
	 * @param tokenStr
	 * @return token value, or <0 if not found
	 */
	virtual int getCmdToken(const std::string& tokenStr) const override ;

	/**
	 * Is this a valid command token string
	 * @param tokenStr
	 * @return true if valid
	 */
	virtual bool isCmdToken(const std::string& tokenStr) const override ;

	/**
	 * Is this a valid command token
	 * @param token
	 * @return true if valid
	 */
	virtual bool isCmdToken(unsigned token) const override ;

	/**
	 * Convert command token value into a string
	 * @param token
	 * @return token string, or empty string if not found
	 */
	virtual std::string getCmdTokenStr(unsigned token) const override ;

	/**
	 * Get the complete list of command token strings
	 */
	virtual std::vector<std::string> getCmds() const override ;

	/**
	 * Convert state token string into a value
	 * @param tokenStr
	 * @return token value, or <0 if not found
	 */
	virtual int getStateToken(const std::string& tokenStr) const override ;

	/**
	 * Is this a valid state token string
	 * @param tokenStr
	 * @return true if valid
	 */
	virtual bool isStateToken(const std::string& tokenStr) const override ;

	/**
	 * Is this a valid state token
	 * @param token
	 * @return true if valid
	 */
	virtual bool isStateToken(unsigned token) const override ;

	/**
	 * Get the data type of this state variable
	 * @param tokenStr	Variable name
	 * @return data type
	 */
	virtual std::string getStateTypeStr(const std::string& tokenStr) const override ;

	/**
	 * Get the data type of this state variable
	 * @param token	Variable id
	 * @return data type
	 */
	virtual std::string getStateTypeStr(unsigned token) const override ;

	/**
	 * Get the data type of this state variable
	 * @param tokenStr	Variable name
	 * @return data type
	 */
	virtual DataVariantType::Type getStateType(const std::string& tokenStr) const override ;

	/**
	 * Get the data type of this state variable
	 * @param token	Variable id
	 * @return data type
	 */
	virtual DataVariantType::Type getStateType(unsigned token) const override ;

	/**
	 * Get the default value of this state variable
	 * @param tokenStr	Variable name
	 * @return default value
	 */
	virtual std::string getStateDefault(const std::string& tokenStr) const override ;

	/**
	 * Get the default value of this state variable
	 * @param token	Variable id
	 * @return default value
	 */
	virtual std::string getStateDefault(unsigned token) const override ;

	/**
	 * Convert state token value into a string
	 * @param token
	 * @return token string, or empty string if not found
	 */
	virtual std::string getStateTokenStr(unsigned token) const override ;

	/**
	 * Get the complete list of state token strings
	 */
	virtual std::vector<std::string> getStates() const override ;

	/**
	 * Convert token string into a value
	 * @param tokenStr
	 * @return token value, or <0 if not found
	 */
	virtual int getToken(const std::string& tokenStr) const override ;

	/**
	 * Is this a valid token string into a value
	 * @param tokenStr
	 * @return true if valid
	 */
	virtual bool isToken(const std::string& tokenStr) const override ;

	/**
	 * Is this a valid token string into a value
	 * @param tokenStr
	 * @return true if valid
	 */
	virtual bool isToken(unsigned token) const override ;

	/**
	 * Convert token value into a string
	 * @param token
	 * @return token string, or empty string if not found
	 */
	virtual std::string getTokenStr(unsigned token) const override ;

private:
	std::pair<unsigned, unsigned> minMaxMap(const std::map<std::string, unsigned>& map) const;
	std::vector<std::string> revMap(const std::map<std::string, unsigned>& map,
			const std::pair<unsigned, unsigned>& range) const;
	std::vector<StateType> revTypeMap(const std::map<std::string, StateType>& map,
			const std::pair<unsigned, unsigned>& range) const;

private:
	unsigned mApiVersion ;
	const std::map<std::string, unsigned> mCommandMap;
	const std::map<std::string, unsigned> mStateMap;
	const std::map<std::string, unsigned> mTokenMap;
	const std::map<std::string, StateType> mStateTypes;

	// Calculated ranges - assumes the map ids are continuous
	std::pair<unsigned, unsigned> mCommandRange ;
	std::pair<unsigned, unsigned> mStateRange ;
	std::pair<unsigned, unsigned> mTokenRange ;

	// Vectors reverse mapping the above based on normalised IDs
	const std::vector<std::string> mRevCommandMap;
	const std::vector<std::string> mRevStateMap;
	const std::vector<std::string> mRevTokenMap;
	const std::vector<StateType> mRevStateTypes;
} ;

}

#endif /* FPGAMSGTOKENS_H_ */
