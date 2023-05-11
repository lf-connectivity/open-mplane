/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GlobalKey.h
 * \brief     Global key instance that is shared among all applications
 *
 *
 * \details
 *
 */


#ifndef GLOBALKEY_H_
#define GLOBALKEY_H_

#include "Key.h"

namespace Mplane {

class GlobalKey : public Key {
public:
	GlobalKey() ;
	virtual ~GlobalKey() ;

} ;

}

#endif /* GLOBALKEY_H_ */
