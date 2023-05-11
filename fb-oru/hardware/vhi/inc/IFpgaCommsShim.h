/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaCommsShim.h
 * \brief     Interface to fpga communications shim
 *
 *
 * \details   Interface to fpga communications shim - provides connection between POSIX message queues and
 * 				the proprietary communications link between processor and FPGA
 *
 */


#ifndef IFPGACOMMSSHIM_H_
#define IFPGACOMMSSHIM_H_

#include <memory>

namespace Mplane {

class IFpgaCommsShim {
public:
	IFpgaCommsShim() {}
	virtual ~IFpgaCommsShim() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IFpgaCommsShim> getInstance() ;

} ;

}

#endif /* IFPGACOMMSSHIM_H_ */
