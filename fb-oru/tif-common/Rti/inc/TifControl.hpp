/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TifControl.hpp
 * \brief     Helper utility functions
 *
 *
 * \details
 *
 */


#ifndef TIFCONTROL_HPP_
#define TIFCONTROL_HPP_

#include <memory>
#include <string>
#include "ITif.h"

namespace Mplane {

class TifControl {
public:

	template <class S>
	static std::shared_ptr<SocketServer> make_server(const std::string& name, unsigned port, unsigned maxConnections)
	{
		std::shared_ptr<S> server(std::make_shared<S>(name, port, maxConnections, ITifControl::getTaskPriority())) ;
		return std::dynamic_pointer_cast<SocketServer>(server) ;
	}
} ;

}

#endif /* TIFCONTROL_HPP_ */
