/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 * ** AUTO-GENERATED - DO NOT EDIT THIS FILE **
 */


#ifndef COMMON_FPGA_INC_FPGAMGR_H_
#define COMMON_FPGA_INC_FPGAMGR_H_

#include "IFpgaMgr.h"

namespace Mplane {

/*!
 * \class  FpgaMgr
 * \brief
 * \details
 *
 */
class FpgaMgr : public virtual IFpgaMgr {
public:
	FpgaMgr() ;
	virtual ~FpgaMgr() ;

    /*! \brief  The initialise method
     *
     *  Method called during system startup, post FPGA image load, to fully
     *  initialise the device and to override any initial settings with
     *  board-specific ones.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise(void) override;


#if 0
    /*! \brief  Read an fpga 16-bit register
     *
     *  Method used to return the FPGA register value at the specified offset.
     *
     *  \return  UINT16 FPGA register contents
     */
    virtual UINT16 readRegister(unsigned offset) override;

    /*! \brief  Write an fpga 16-bit register
     *
     *  Method used to write an FPGA register value at the specified offset.
     *
     */
    virtual void writeRegister(unsigned offset, UINT16 value) override;

    /*! \brief  Modify an fpga 16-bit register
     *
     *  Method used to write an FPGA register value at the specified offset.
     *
     */
    virtual void modifyRegister(unsigned offset, UINT16 value, UINT16 mask) override;


    /*! \brief  Read an fpga 32-bit register
     *
     *  Method used to return the FPGA register value at the specified offset.
     *
     *  \return  FpgaVal FPGA register contents
     */
    virtual UINT32 readRegister32(unsigned offset) override;

    /*! \brief  Write an fpga 32-bit register
     *
     *  Method used to write an FPGA register value at the specified offset.
     *
     */
    virtual void writeRegister32(unsigned offset, UINT32 value) override;

    /*! \brief  Modify an fpga 32-bit register
     *
     *  Method used to write an FPGA register value at the specified offset.
     *
     */
    virtual void modifyRegister32(unsigned offset, UINT32 value, UINT32 mask) override;
#endif


    // Register access
    	virtual void setIFpgaAntennaRegs(std::shared_ptr<IFpgaAntennaRegs> regs) override ;
    	virtual void setIFpgaChainRegs(std::shared_ptr<IFpgaChainRegs> regs) override ;
    	virtual void setIFpgaCpri(std::shared_ptr<IFpgaCpri> regs) override ;
    	virtual void setIFpgaFibreRegs(std::shared_ptr<IFpgaFibreRegs> regs) override ;
    	virtual void setIFpgaIqRegs(std::shared_ptr<IFpgaIqRegs> regs) override ;
    	virtual void setIFpgaOranRegs(std::shared_ptr<IFpgaOranRegs> regs) override ;
    	virtual void setIFpgaSystemRegs(std::shared_ptr<IFpgaSystemRegs> regs) override ;
    	virtual void setIFpgaWaveformRegs(std::shared_ptr<IFpgaWaveformRegs> regs) override ;
    	virtual void setIFpgaWcdmaRegs(std::shared_ptr<IFpgaWcdmaRegs> regs) override ;


protected:
    	virtual std::shared_ptr<IFpgaAntennaRegs> _getIFpgaAntennaRegs() override ;
    	virtual std::shared_ptr<IFpgaChainRegs> _getIFpgaChainRegs() override ;
    	virtual std::shared_ptr<IFpgaCpri> _getIFpgaCpri() override ;
    	virtual std::shared_ptr<IFpgaFibreRegs> _getIFpgaFibreRegs() override ;
    	virtual std::shared_ptr<IFpgaIqRegs> _getIFpgaIqRegs() override ;
    	virtual std::shared_ptr<IFpgaOranRegs> _getIFpgaOranRegs() override ;
    	virtual std::shared_ptr<IFpgaSystemRegs> _getIFpgaSystemRegs() override ;
    	virtual std::shared_ptr<IFpgaWaveformRegs> _getIFpgaWaveformRegs() override ;
    	virtual std::shared_ptr<IFpgaWcdmaRegs> _getIFpgaWcdmaRegs() override ;
    virtual std::shared_ptr<IFpgaKernel> _kernel() override ;

private:
	bool mInitComplete ;
    std::shared_ptr<IFpgaKernel> mFpgaKernel ;

	std::shared_ptr<IFpgaAntennaRegs> mIFpgaAntennaRegs;
	std::shared_ptr<IFpgaChainRegs> mIFpgaChainRegs;
	std::shared_ptr<IFpgaCpri> mIFpgaCpri;
	std::shared_ptr<IFpgaFibreRegs> mIFpgaFibreRegs;
	std::shared_ptr<IFpgaIqRegs> mIFpgaIqRegs;
	std::shared_ptr<IFpgaOranRegs> mIFpgaOranRegs;
	std::shared_ptr<IFpgaSystemRegs> mIFpgaSystemRegs;
	std::shared_ptr<IFpgaWaveformRegs> mIFpgaWaveformRegs;
	std::shared_ptr<IFpgaWcdmaRegs> mIFpgaWcdmaRegs;
} ;

}

#endif /* COMMON_FPGA_INC_FPGAMGR_H_ */
