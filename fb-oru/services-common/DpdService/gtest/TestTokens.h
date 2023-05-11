/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestTokens.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTTOKENS_H_
#define TESTTOKENS_H_

#include "FpgaMsgTokens.h"

namespace Mplane {

class TestTokens : public FpgaMsgTokens
{
public:
	TestTokens() ;
	virtual ~TestTokens() ;

	static std::shared_ptr<IFpgaMsgTokens> getInterface() ;
} ;

}

#endif /* TESTTOKENS_H_ */
