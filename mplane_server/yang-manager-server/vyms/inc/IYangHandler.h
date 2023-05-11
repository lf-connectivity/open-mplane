/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangHandler.h
 * \brief     Handler layer between YANG models and application
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef VYMS_INC_IYANGHANDLER_H_
#define VYMS_INC_IYANGHANDLER_H_

#include <string>

namespace Mplane {

/*!
 * \class  IYangHandler
 * \brief
 * \details
 *
 */
class IYangHandler {
public:
 IYangHandler() {}
 virtual ~IYangHandler() {}

 /**
  * Name (mainly for debug)
  */
 virtual std::string name() const = 0;

 /**
  * Run the initialisation of the handler (can only be done once the rest of the
  * YANG framework is up)
  */
 virtual bool initialise() = 0;
} ;

}

#endif /* VYMS_INC_IYANGHANDLER_H_ */
