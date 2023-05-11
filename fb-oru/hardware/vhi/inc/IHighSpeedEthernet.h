/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IHighSpeedEthernet.h
 * \brief     Virtual interface to high-speed (10G/25G) Ethernet interface
 *
 *
 * \details   Virtual interface to high-speed (10G/25G) Ethernet interface
 *
 * 			NOTE: This assumes there will only be one high-speed ethernet interface for baseband. If/when we support multiple high-speed interfaces
 * 			then this API will have to change (use an index?)
 *
 */


#ifndef VHI_INC_IHIGHSPEEDETHERNET_H_
#define VHI_INC_IHIGHSPEEDETHERNET_H_

#include <cstdint>
#include <memory>
#include <string>

namespace Mplane {

/*!
 * \class  IHighSpeedEthernet
 * \brief
 * \details
 *
 */
class IHighSpeedEthernet {
public:
	IHighSpeedEthernet() {}
	virtual ~IHighSpeedEthernet() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IHighSpeedEthernet> singleton() ;

	enum EthernetSpeed {
		// Interface is fixed at a set speed
		ENET_STANDALONE_25G,
		ENET_STANDALONE_10G,

		// Interface is auto-negotiated to this speed
		ENET_AUTO_25G,
		ENET_AUTO_10G,
	};

	/**
	 * Convert enum to string
	 */
	static std::string enetSpeed2Str(EthernetSpeed speed) ;

	/**
	 * get the core's current speed
	 */
	virtual EthernetSpeed speed() const =0 ;

	/**
	 * Simplify the speed to 10G or 25G
	 */
	virtual bool is25G() const =0 ;

	/**
	 * Read any register offset
	 */
	virtual uint32_t read(uint32_t address) const =0 ;


} ;

}

#endif /* VHI_INC_IHIGHSPEEDETHERNET_H_ */
