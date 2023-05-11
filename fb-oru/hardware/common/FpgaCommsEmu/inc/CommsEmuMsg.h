/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommsEmuMsg.h
 * \brief     COMMS emulator message
 *
 *
 * \details   Wraps up information about a COMMS emulator message, such as the data, type, whether it was valid etc
 *
 */


#ifndef COMMSEMUMSG_H_
#define COMMSEMUMSG_H_

#include <vector>
#include <string>
#include "GlobalTypeDefs.h"

#include "FpgaPdu.h"

namespace Mplane {

class CommsEmuMsg {
public:
	CommsEmuMsg(UINT8 type, const std::vector<UINT8>& data, bool valid) ;

	CommsEmuMsg(FpgaPdu::PduDataType type, const std::vector<UINT8>& data) ;
	CommsEmuMsg(FpgaPdu::PduDataType type, const std::string& str) ;

	virtual ~CommsEmuMsg() ;

	/**
	 * Is the message valid of does it contain errors?
	 * @return true if ok
	 */
	bool isValid() const ;

	/**
	 * Get raw data bytes
	 * @return vector of bytes
	 */
	std::vector<UINT8> getData() const ;

	/**
	 * Get the type byte
	 * @return type byte
	 */
	UINT8 getType() const ;

	/**
	 * Get the underlying message
	 * @return FpgaPdu
	 */
	FpgaPdu getPdu() const ;

	static CommsEmuMsg createCommand(const std::vector<UINT8>& data) ;
	static CommsEmuMsg createResponse(const std::vector<UINT8>& data) ;
	static CommsEmuMsg createEvent(const std::vector<UINT8>& data) ;
	static CommsEmuMsg createLog(const std::string& msg) ;
	static CommsEmuMsg createMatlab(const std::string& msg) ;
	static CommsEmuMsg createText(const std::string& msg) ;

private:
	bool mValid ;
	FpgaPdu mPdu ;
} ;

}

#endif /* COMMSEMUMSG_H_ */
