/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WebSocketPacket.h
 * \brief     Encodes/decodes data to WebSocket format RF6455 (or a simple subset)
 *
 *
 * \details
 *
 */


#ifndef WEBSOCKETPACKET_H_
#define WEBSOCKETPACKET_H_


namespace Mplane {

class WebSocketPacket {
public:
	WebSocketPacket() ;
	virtual ~WebSocketPacket() ;

	/**
	 * Create instance from a packet of data
	 * @param packet
	 * @return true if data valid
	 */
	bool setPacketData(const std::string& packet) ;

	/**
	 * Create inace from payload data (uses defaults for the packet header if not specified)
	 * @param payload
	 * @return true
	 */
	bool setPayloadData(const std::string& payload) ;

	/**
	 * Get the whole packet as a string of bytes
	 * @return string
	 */
	std::string getPacketData() ;

	/**
	 * get the payload string
	 * @return payload
	 */
	std::string getPayload() ;

	enum WsOpcode {
		CONTINUATION_FRAME	=0,
		TEXT_FRAME			=1,
		BINARY_FRAME		=2,
		CONNECTION_CLOSE	=8,
		PING				=9,
		PONG				=10,

		UNSET				= 0xff,
	};

	/**
	 * Get the packet opcode
	 */
	WsOpcode getOpcode() ;

private:
	/**
	 * Take the current settings and encode the packe tdata
	 */
	void encodePacket() ;

	/**
	 * Decode the packe tstring into packet data
	 * @param packet
	 * @return true if packet valid
	 */
	bool decodePacket(const std::string& packet) ;

private:
	bool mFin ;
	WsOpcode mOpcode ;
	bool mMasking ;
	uint64_t mPayloadLen ;
	std::vector<uint8_t> mMaskingKey ;
	std::string mPayload ;
	std::vector<uint8_t> mPacket ;
} ;

}

#endif /* WEBSOCKETPACKET_H_ */
