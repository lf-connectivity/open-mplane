/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WebSocketPacket.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ByteTransfer.hpp"
#include "WebSocketPacket.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WebSocketPacket::WebSocketPacket() :
	mFin(true),
	mOpcode(UNSET),
	mMasking(false),
	mPayloadLen(0),
	mMaskingKey(),
	mPayload(""),
	mPacket()
{
}

//-------------------------------------------------------------------------------------------------------------
WebSocketPacket::~WebSocketPacket()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WebSocketPacket::setPacketData(const std::string& packet)
{
	// set the packet and decode
	return decodePacket(packet) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WebSocketPacket::setPayloadData(const std::string& payload)
{
	mOpcode = TEXT_FRAME ;
	mPayload = payload ;
	encodePacket() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string WebSocketPacket::getPacketData()
{
	return std::string(mPacket.begin(), mPacket.end()) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string WebSocketPacket::getPayload()
{
	return mPayload ;
}

//-------------------------------------------------------------------------------------------------------------
WebSocketPacket::WsOpcode WebSocketPacket::getOpcode()
{
	return mOpcode ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void WebSocketPacket::encodePacket()
{
	if (mMaskingKey.empty())
		mMasking = false ;

	mPayloadLen = static_cast<uint64_t>(mPayload.size()) ;

	uint8_t fin_rsvr_op(mFin ? 0x80 : 0x00) ;
	fin_rsvr_op += static_cast<uint8_t>(mOpcode) ;
	uint8_t mask_plen(mMasking ? 0x80 : 0x00) ;

	if (mPayloadLen > 0xffff)
	{
		mask_plen += 127 ;
	}
	else if (mPayloadLen >= 0x7f)
	{
		mask_plen += 126 ;
	}
	else
	{
		mask_plen += static_cast<uint8_t>(mPayloadLen) ;
	}

	mPacket.clear() ;
	mPacket.push_back(fin_rsvr_op) ;
	mPacket.push_back(mask_plen) ;

	if (mPayloadLen > 0xffff)
	{
		uint64_t len(mPayloadLen) ;
		for (unsigned byte=0; byte < 8; ++byte)
		{
			uint8_t byteVal( static_cast<uint8_t>(0xff & (len >> 56)) ) ;
			mPacket.push_back(byteVal) ;
			len <<= 8 ;
		}
	}
	else if (mPayloadLen >= 0x7f)
	{
		mPacket.push_back( static_cast<uint8_t>((mPayloadLen & 0xff00) >> 8) ) ;
		mPacket.push_back( static_cast<uint8_t>(mPayloadLen & 0x00ff) ) ;
	}

	if (mMasking)
	{
		for (auto mask : mMaskingKey)
		{
			mPacket.push_back(mask) ;
		}
	}

	mPacket.insert(mPacket.end(), mPayload.begin(), mPayload.end()) ;

//	std::cout << "----------------------" << std::endl ;
//	std::cout << "WebSocketPacket::encodePacket:" << std::endl ;
//	std::cout << "FIN=" << mFin << " Op=" << mOpcode << " Masking=" << mMasking << " Len=" << mPayloadLen << std::endl ;
//	std::cout << "'" << mPayload << "'" << std::endl ;
//	ByteTransfer::dump(mPacket) ;
//	std::cout << "----------------------\n\n" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool WebSocketPacket::decodePacket(const std::string& packet)
{
	std::vector<uint8_t> data(packet.begin(), packet.end()) ;
	auto dbegin(data.cbegin()) ;
	auto dend(data.cend()) ;

	uint8_t fin_rsvr_op(ByteTransfer::readByte(dbegin, dend)) ;
	uint8_t mask_plen(ByteTransfer::readByte(dbegin, dend)) ;

	mFin = ((fin_rsvr_op & 0x80) ? true : false) ;
	mOpcode = static_cast<WsOpcode>(fin_rsvr_op & 0x0f) ;
	mMasking = ((mask_plen & 0x80) ? true : false) ;
	mMaskingKey.clear() ;
	mPayloadLen = static_cast<uint64_t>(mask_plen & 0x7f) ;

//std::cerr << "WebSocketPacket::decodePacket opcode=0x" << std::hex << mOpcode << std::dec <<
//		" Len=" << mPayloadLen <<
//		" Masking=0x" << std::hex << mMasking << std::dec <<
//		std::endl ;

	if (mPayloadLen >= 126)
	{
		if (mPayloadLen == 126)
		{
			mPayloadLen = static_cast<uint64_t>(ByteTransfer::readShort(dbegin, dend)) ;
		}
		else
		{
			uint32_t hi = ByteTransfer::readWord(dbegin, dend) ;
			uint32_t lo = ByteTransfer::readWord(dbegin, dend) ;
			mPayloadLen = (static_cast<uint64_t>(hi) << 32) | static_cast<uint64_t>(lo) ;
		}
	}

	if (mMasking)
	{
		for (unsigned i=0; i < 4; ++i)
		{
			mMaskingKey.push_back(ByteTransfer::readByte(dbegin, dend)) ;
		}
	}

	mPayload = std::string(dbegin, dend) ;
//	std::cerr << "WebSocketPacket::decodePacket payload size=" << mPayload.size() << std::endl ;

	// Unmask if necessary
	if (mMasking)
	{
		for (unsigned i=0; i < mPayload.size(); ++i)
		{
			unsigned j = i % 4 ;
			uint8_t cc( static_cast<uint8_t>(mPayload[i]) ) ;
			uint8_t mask( static_cast<uint8_t>(mMaskingKey[j]) ) ;
			cc ^= mask ;
			mPayload[i] = static_cast<char>(cc) ;
		}
	}

//std::cout << "WebSocketPacket::decodePacket:" << std::endl ;
//ByteTransfer::dump(data) ;
//std::cout << "FIN=" << mFin << " Op=" << mOpcode << " Masking=" << mMasking << " Len=" << mPayloadLen << std::endl ;
//std::cout << mPayload << std::endl ;

	return true ;
}
