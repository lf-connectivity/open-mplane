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

@@//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<@name@> IFpgaMgr::get@name@()
{
	return IFpgaMgr::singleton()->_get@name@() ;
}

@@

//=============================================================================================================
// PUBLIC
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
FpgaMgr::FpgaMgr() :
	mInitComplete(false)
	,mFpgaKernel()
@@	,m@name@()@@
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


@@//-------------------------------------------------------------------------------------------------------------
void FpgaMgr::set@name@(std::shared_ptr<@name@> regs)
{
	m@name@ = regs ;
	if (!mFpgaKernel) mFpgaKernel=regs->kernel() ;
}

@@

//=============================================================================================================
// PROTECTED
//=============================================================================================================

@@//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<@name@> FpgaMgr::_get@name@()
{
	return m@name@ ;
}

@@

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaKernel> FpgaMgr::_kernel()
{
	return mFpgaKernel ;
}
