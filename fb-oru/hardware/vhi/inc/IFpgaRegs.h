/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaRegs.h
 * \brief     Virtual base class for all FPGA regs
 *
 *
 * \details   Virtual base class for all FPGA regs
 *
 */


#ifndef VHI_INC_IFPGAREGS_H_
#define VHI_INC_IFPGAREGS_H_


namespace Mplane {

/*!
 * \class  IFpgaRegs
 * \brief
 * \details
 *
 */
class IFpgaRegs {
public:
	IFpgaRegs() {}
	virtual ~IFpgaRegs() {}

} ;

}

#endif /* VHI_INC_IFPGAREGS_H_ */
