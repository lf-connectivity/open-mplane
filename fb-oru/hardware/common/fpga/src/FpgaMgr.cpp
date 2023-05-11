/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FpgaMgr.h"

using namespace Mplane;


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMgr> IFpgaMgr::singleton()
{
	static std::shared_ptr<IFpgaMgr> instance(std::make_shared<FpgaMgr>()) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaKernel> IFpgaMgr::kernel()
{
	return IFpgaMgr::singleton()->_kernel() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaAntennaRegs> IFpgaMgr::getIFpgaAntennaRegs()
{
	return IFpgaMgr::singleton()->_getIFpgaAntennaRegs() ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaChainRegs> IFpgaMgr::getIFpgaChainRegs()
{
	return IFpgaMgr::singleton()->_getIFpgaChainRegs() ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaCpri> IFpgaMgr::getIFpgaCpri()
{
	return IFpgaMgr::singleton()->_getIFpgaCpri() ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaFibreRegs> IFpgaMgr::getIFpgaFibreRegs()
{
	return IFpgaMgr::singleton()->_getIFpgaFibreRegs() ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaIqRegs> IFpgaMgr::getIFpgaIqRegs()
{
	return IFpgaMgr::singleton()->_getIFpgaIqRegs() ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaOranRegs> IFpgaMgr::getIFpgaOranRegs()
{
	return IFpgaMgr::singleton()->_getIFpgaOranRegs() ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaSystemRegs> IFpgaMgr::getIFpgaSystemRegs()
{
	return IFpgaMgr::singleton()->_getIFpgaSystemRegs() ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaWaveformRegs> IFpgaMgr::getIFpgaWaveformRegs()
{
	return IFpgaMgr::singleton()->_getIFpgaWaveformRegs() ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaWcdmaRegs> IFpgaMgr::getIFpgaWcdmaRegs()
{
	return IFpgaMgr::singleton()->_getIFpgaWcdmaRegs() ;
}



//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
FpgaMgr::FpgaMgr() :
	mInitComplete(false)
	,mFpgaKernel()
	,mIFpgaAntennaRegs()
	,mIFpgaChainRegs()
	,mIFpgaCpri()
	,mIFpgaFibreRegs()
	,mIFpgaIqRegs()
	,mIFpgaOranRegs()
	,mIFpgaSystemRegs()
	,mIFpgaWaveformRegs()
	,mIFpgaWcdmaRegs()
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaMgr::~FpgaMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State FpgaMgr::initialise(void)
{
    if (mInitComplete)
    {
        /*! \TODO - add init trace here to indicate a false entry, should not
         * call it more than once.
         */

        // already initialised, so early exit, nothing to do
        return ReturnType::RT_ALREADY_INITIALISED;
    }

    /*! \TODO - add init trace here to indicate CommonFPGA init complete */

    mInitComplete = true;

    // Initialise the kernel device driver interface
    // TODO: Init each regs region?
    IFpgaKernel::getInstance()->initialise() ;

	return ReturnType::RT_OK ;
}

#if 0
//-------------------------------------------------------------------------------------------------------------
UINT16 FpgaMgr::readRegister(unsigned offset)
{
	return mFpgaKernel->read(offset) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::writeRegister(unsigned offset, UINT16 value)
{
	mFpgaKernel->write(offset, value) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::modifyRegister(unsigned offset, UINT16 value, UINT16 mask)
{
	mFpgaKernel->modify(offset, value, mask) ;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 FpgaMgr::readRegister32(unsigned offset)
{
	return mFpgaKernel->read(offset) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::writeRegister32(unsigned offset, UINT32 value)
{
	mFpgaKernel->write32(offset, value) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::modifyRegister32(unsigned offset, UINT32 value, UINT32 mask)
{
	mFpgaKernel->modify32(offset, value, mask) ;
}
#endif


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaAntennaRegs(std::shared_ptr<IFpgaAntennaRegs> regs)
{
	mIFpgaAntennaRegs = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaChainRegs(std::shared_ptr<IFpgaChainRegs> regs)
{
	mIFpgaChainRegs = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaCpri(std::shared_ptr<IFpgaCpri> regs)
{
	mIFpgaCpri = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaFibreRegs(std::shared_ptr<IFpgaFibreRegs> regs)
{
	mIFpgaFibreRegs = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaIqRegs(std::shared_ptr<IFpgaIqRegs> regs)
{
	mIFpgaIqRegs = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaOranRegs(std::shared_ptr<IFpgaOranRegs> regs)
{
	mIFpgaOranRegs = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaSystemRegs(std::shared_ptr<IFpgaSystemRegs> regs)
{
	mIFpgaSystemRegs = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaWaveformRegs(std::shared_ptr<IFpgaWaveformRegs> regs)
{
	mIFpgaWaveformRegs = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}


//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::setIFpgaWcdmaRegs(std::shared_ptr<IFpgaWcdmaRegs> regs)
{
	mIFpgaWcdmaRegs = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}



//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaAntennaRegs> FpgaMgr::_getIFpgaAntennaRegs()
{
	return mIFpgaAntennaRegs ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaChainRegs> FpgaMgr::_getIFpgaChainRegs()
{
	return mIFpgaChainRegs ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaCpri> FpgaMgr::_getIFpgaCpri()
{
	return mIFpgaCpri ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaFibreRegs> FpgaMgr::_getIFpgaFibreRegs()
{
	return mIFpgaFibreRegs ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaIqRegs> FpgaMgr::_getIFpgaIqRegs()
{
	return mIFpgaIqRegs ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaOranRegs> FpgaMgr::_getIFpgaOranRegs()
{
	return mIFpgaOranRegs ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaSystemRegs> FpgaMgr::_getIFpgaSystemRegs()
{
	return mIFpgaSystemRegs ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaWaveformRegs> FpgaMgr::_getIFpgaWaveformRegs()
{
	return mIFpgaWaveformRegs ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaWcdmaRegs> FpgaMgr::_getIFpgaWcdmaRegs()
{
	return mIFpgaWcdmaRegs ;
}



//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaKernel> FpgaMgr::_kernel()
{
	return mFpgaKernel ;
}
