/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFibre.cpp
 * \brief     The implementation of the common radio CommonFibre class
 *
 *
 * \details   This file contains the implementation of the common radio CommonFibre class
 *
 */

// Includes go here, before the namespace
#include <string>
#include "CommonCpri.h"
#include "CommonFibre.h"

using namespace Mplane;

/**
 * The following provides the common Fibre interface class.
 */
std::shared_ptr<IFibre> CommonFibre::getInterface()
{
    static std::shared_ptr<IFibre> _pInstance(new CommonFibre());

    return _pInstance;
}

#ifdef BUILD_IF_CPRI
// TODO: Ideally this should be somewhere that gets picked up by any apps that use (CPRI) fibre. Then again this
// is meant to be common code so shouldn't have any cpri stuff in it in the first place!
//
// For now I'll just conditionally compile it in for CPRI builds until we've got more time to refactor
//
std::shared_ptr<IFibre> IFibre::getInterface()
{
    return CommonFibre::getInterface();
}
#endif

CommonFibre::CommonFibre():
        Loggable ( "CommonFibre", "CF" ),
        mInitialised ( ReturnType::RT_NOT_INITIALISED),
        mCpri ( 0 )
{
#ifdef BUILD_IF_CPRI
    if (getFibreType() == IFibre::FibreTypeCpri)
    {
        mCpri = std::dynamic_pointer_cast<CommonCpri>(ICpri::getInterface());
    }
#endif
}

void CommonFibre::show()
{
    eventInfo("*** CommonFibre Show ***");

    eventInfo("State [%s], Fibre type [%s]",
             ReturnType::getState(mInitialised), fibreTypeString());

    eventInfo("*** CommonFibre Show End ***");
}

ReturnType::State CommonFibre::initialise(void)
{
#ifdef BUILD_IF_CPRI
    mInitialised = mCpri->initialise();
#endif
    return mInitialised;
}

IFibre::FibreType_t CommonFibre::getFibreType() const
{
    // the common fibre type is CPRI
    return IFibre::FibreTypeCpri;
}

int CommonFibre::getFibreClockSyncSource()
{
#ifdef BUILD_IF_CPRI

    // the common fibre clock source is from the CPRI
    return mCpri->getFibreClockSyncSource();
#else
    return 0 ;
#endif
}

UINT32 CommonFibre::getNumPorts() const
{
#ifdef BUILD_IF_CPRI
    return mCpri->getNumCpriPorts();
#else
    return 0 ;
#endif
}

const char* CommonFibre::fibreTypeString() const
{
    switch (getFibreType())
    {
    case IFibre::FibreTypeCpri:
        return "CPRI";

    case IFibre::FibreTypeObsai:
        return "OBSAI";

    case IFibre::FibreTypeOran:
        return "ORAN";

    default:
    	return "_UNKNOWN_FIBRE_TYPE";
    };

    return "_UNKNOWN_FIBRE_TYPE";
}

CommonCpriPtr CommonFibre::getCpri() const
{
#ifdef BUILD_IF_CPRI
    return mCpri;
#else
    return std::shared_ptr<CommonCpri>() ;
#endif
}
