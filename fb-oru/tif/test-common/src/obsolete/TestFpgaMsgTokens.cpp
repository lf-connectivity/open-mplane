/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestFpgaMsgTokens.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TestFpgaMsgTokens.h"

using namespace Mplane;

Mplane::TestFpgaMsgTokens::TestFpgaMsgTokens() {
}

Mplane::TestFpgaMsgTokens::~TestFpgaMsgTokens() {
}


unsigned Mplane::TestFpgaMsgTokens::getApiVersion() const {
	return 0 ;
}

int Mplane::TestFpgaMsgTokens::getCmdToken(const std::string& tokenStr) const {
	return -1 ;
}

bool Mplane::TestFpgaMsgTokens::isCmdToken(const std::string& tokenStr) const {
	return false ;
}

bool Mplane::TestFpgaMsgTokens::isCmdToken(unsigned token) const {
	return false ;
}

std::string Mplane::TestFpgaMsgTokens::getCmdTokenStr(unsigned token) const {
	return "" ;
}

std::vector<std::string> Mplane::TestFpgaMsgTokens::getCmds() const {
	return std::vector<std::string>() ;
}

int Mplane::TestFpgaMsgTokens::getStateToken(
		const std::string& tokenStr) const {
	return -1 ;
}

bool Mplane::TestFpgaMsgTokens::isStateToken(
		const std::string& tokenStr) const {
	return false ;
}

bool Mplane::TestFpgaMsgTokens::isStateToken(unsigned token) const {
	return false ;
}

std::string Mplane::TestFpgaMsgTokens::getStateTypeStr(
		const std::string& tokenStr) const {
	return "" ;
}

std::string Mplane::TestFpgaMsgTokens::getStateTypeStr(unsigned token) const {
	return "" ;
}

DataVariantType::Type Mplane::TestFpgaMsgTokens::getStateType(
		const std::string& tokenStr) const {
	return DataVariantType::None ;
}

DataVariantType::Type Mplane::TestFpgaMsgTokens::getStateType(
		unsigned token) const {
	return DataVariantType::None ;
}

std::string Mplane::TestFpgaMsgTokens::getStateDefault(
		const std::string& tokenStr) const {
	return "" ;
}

std::string Mplane::TestFpgaMsgTokens::getStateDefault(unsigned token) const {
	return "" ;
}

std::string Mplane::TestFpgaMsgTokens::getStateTokenStr(unsigned token) const {
	return "" ;
}

std::vector<std::string> Mplane::TestFpgaMsgTokens::getStates() const {
	return std::vector<std::string>() ;
}

int Mplane::TestFpgaMsgTokens::getToken(const std::string& tokenStr) const {
	return -1 ;
}

bool Mplane::TestFpgaMsgTokens::isToken(const std::string& tokenStr) const {
	return false ;
}

bool Mplane::TestFpgaMsgTokens::isToken(unsigned token) const {
	return false ;
}

std::string Mplane::TestFpgaMsgTokens::getTokenStr(unsigned token) const {
	return "" ;
}
