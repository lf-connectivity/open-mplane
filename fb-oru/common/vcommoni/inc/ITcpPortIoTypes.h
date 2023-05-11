/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortIoTypes.h
 * \brief     Types used by tcp port
 *
 *
 * \details
 *
 */


#ifndef ITCPPORTIOTYPES_H_
#define ITCPPORTIOTYPES_H_

#include <vector>
#include <cstdint>
#include <functional>

namespace Mplane {

class ITcpPortIoTypes {
public:
	/**
	 * Port directions
	 */
	enum TcpPortType {
		TCP_PORT_IN,   //!< TCP_PORT_IN
		TCP_PORT_OUT,  //!< TCP_PORT_OUT
		TCP_PORT_INOUT,//!< TCP_PORT_INOUT
	};

	/**
	 * Callback function for receive data. Uses the passed in data up to the expected message size. Any
	 * additional bytes are lost.
	 * @return Returns false on error or end of data
	 */
	using ReceiveCallback = std::function<bool(const std::vector<uint8_t>& data)> ;


} ;

}

#endif /* ITCPPORTIOTYPES_H_ */
